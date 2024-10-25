// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#include "GXmlStreamReaderImpl.h"
#include "GXmlNode.h"
#include "GXmlOpenTagNode.h"
#include "GXmlCloseTagNode.h"
#include "GXmlSingleTagNode.h"
#include "GXmlTextNode.h"
#include "GXmlCommentNode.h"
#include "GXmlProcInstructNode.h"
#include "GXmlDocTypeNode.h"
#include "GXmlCDataNode.h"

#include <libxml/xmlreader.h>

#include <vector>
#include <algorithm>

#include <utilities/GException.h>
#include <logging/LLogging.h>


#define XML_SUCCESS_ASSERT(returnvalue, ...) DATA_ASSERT((returnvalue) == NULL, __VA_ARGS__);


// Convert libxml2 nodetype identifier to readable string
std::string NodeTypeToString(const int t)
{
	switch (t)
	{
	case XML_READER_TYPE_NONE: return "none";
	case XML_READER_TYPE_ELEMENT: return "element";
	case XML_READER_TYPE_ATTRIBUTE: return "attribute";
	case XML_READER_TYPE_TEXT: return "text";
	case XML_READER_TYPE_CDATA: return "cdata";
	case XML_READER_TYPE_ENTITY_REFERENCE: return "entity_reference";
	case XML_READER_TYPE_ENTITY: return "entity";
	case XML_READER_TYPE_PROCESSING_INSTRUCTION: return "processing_instruction";
	case XML_READER_TYPE_COMMENT: return "comment";
	case XML_READER_TYPE_DOCUMENT: return "document";
	case XML_READER_TYPE_DOCUMENT_TYPE: return "document_type";
	case XML_READER_TYPE_DOCUMENT_FRAGMENT: return "document_fragment";
	case XML_READER_TYPE_NOTATION: return "notation";
	case XML_READER_TYPE_WHITESPACE: return "whitespace";
	case XML_READER_TYPE_SIGNIFICANT_WHITESPACE: return "significant_whitespace";
	case XML_READER_TYPE_END_ELEMENT: return "end_element";
	case XML_READER_TYPE_END_ENTITY: return "end_entity";
	case XML_READER_TYPE_XML_DECLARATION: return "xml_declaration";
	}


	EXCEPTION("error determining xml node type for type %i", t);

	return "ERROR_TYPE";
}


/** Open file and set up libxml2 reader. Fails if file doesn't exist
 *  @param filename The XMK file
 *  @exception GException If the file does not exists or it could not be opened */
GXmlStreamReaderImpl::GXmlStreamReaderImpl(const std::string& filename)
	: fFilename(filename)
{
	fReader = xmlReaderForFile(fFilename.c_str(), "UTF-8", 0);
	G_ASSERT_EXCEPTION(fReader != NULL, "xml open failed: %s", filename.c_str());
}


/** Shut down the reader
 *  @exception GException If the reader could not be closed */
GXmlStreamReaderImpl::~GXmlStreamReaderImpl()
{
	//G_ASSERT_EXCEPTION(xmlTextReaderClose(fReader), "close failed");
}


/*! @brief Read node from xml file and set up for next read
	@return pointer to node if success. nullptr on end of file or failure */
GXmlNode* GXmlStreamReaderImpl::ReadNode()
{
	GXmlNode* node = nullptr;

	static GLocation l = GLocation(__FILE__, __LINE__, __func__);
	xmlSetGenericErrorFunc(&l, DoError );

	while (node == nullptr)
	{

		const int readerValid = xmlTextReaderIsValid(fReader);
		const int returncode = xmlTextReaderRead(fReader);

		if (returncode != 1)
		{
			if (returncode != 0)
			{
				G_ERROR("Read failed");
			}

			break;
		}

		const int depth = xmlTextReaderDepth(fReader);
		const xmlChar* name = xmlTextReaderConstName(fReader);
		const xmlChar* value = xmlTextReaderConstValue(fReader);
		const int type = xmlTextReaderNodeType(fReader);
		const int empty = xmlTextReaderIsEmptyElement(fReader);
		const int attributeCount = xmlTextReaderAttributeCount(fReader);
		std::vector<GXmlAttribute> attributes;
		for (int i = 0; i < attributeCount; i++)
		{
			xmlTextReaderMoveToNextAttribute(fReader);

			xmlChar* attrName = xmlTextReaderName(fReader);
			xmlChar* attrValue = xmlTextReaderValue(fReader);
			attributes.push_back( GXmlAttribute((char*)attrName, (char*)attrValue) );
			xmlFree(attrValue);
			xmlFree(attrName);
		}


		node = CreateNodeFromType(type, (char*)name, (char*)value, empty, attributes);
	}

	fCurrentNode = node;
	return node;
}

GXmlNode* GXmlStreamReaderImpl::CreateNodeFromType(const int nodetype, const char* name, const char* value, const int empty, const std::vector<GXmlAttribute>& attributes) const
{
	GXmlNode* node = nullptr;

	switch (nodetype)
	{
	case XML_READER_TYPE_NONE:
		break;
	case XML_READER_TYPE_ELEMENT:
		if (empty)
		{
			node = new GXmlSingleTagNode(name);
		}
		else
		{
			node = new GXmlOpenTagNode(name);
		}

		std::for_each(attributes.cbegin(), attributes.cend(),
			[&](const GXmlAttribute& attr) { dynamic_cast<GXmlTagNode*>(node)->AddAttribute(attr); }
		);

		break;
	//case XML_READER_TYPE_ATTRIBUTE: return "attribute";
	case XML_READER_TYPE_TEXT:
		node = new GXmlTextNode(value);
		break;
	case XML_READER_TYPE_CDATA:
		node = new GXmlCDataNode(value);
		break;
	//case XML_READER_TYPE_ENTITY_REFERENCE: return "entity_reference";
	//case XML_READER_TYPE_ENTITY: return "entity";
	case XML_READER_TYPE_PROCESSING_INSTRUCTION:
		node = new GXmlProcInstructNode(name, value);
		break;
	case XML_READER_TYPE_COMMENT:
		break;
	//case XML_READER_TYPE_DOCUMENT: return "document";
	case XML_READER_TYPE_DOCUMENT_TYPE:
		node = new GXmlDocTypeNode(name);
		break;
	//case XML_READER_TYPE_DOCUMENT_FRAGMENT: return "document_fragment";
	//case XML_READER_TYPE_NOTATION: return "notation";
	case XML_READER_TYPE_WHITESPACE: break;
	case XML_READER_TYPE_SIGNIFICANT_WHITESPACE: break;
	case XML_READER_TYPE_END_ELEMENT:
		node = new GXmlCloseTagNode(name);
		break;
	//case XML_READER_TYPE_END_ENTITY: return "end_entity";
	//case XML_READER_TYPE_XML_DECLARATION: return "xml_declaration";
	default:
		// document has a node type which is not implemented.
		EXCEPTION("Node with type %i (%s) not found", nodetype, NodeTypeToString(nodetype));
	}

	return node;
}


GXmlNode  *
GXmlStreamReaderImpl::GetCurrentNode()
{
	return fCurrentNode;
}


int
GXmlStreamReaderImpl::GetLineNumber()    const
{
	return xmlTextReaderGetParserLineNumber( fReader );
}


int
GXmlStreamReaderImpl::GetColumnNumber()  const
{
	return xmlTextReaderGetParserColumnNumber(fReader);
}


void
GXmlStreamReaderImpl::DoError(void *ctx, const char *msg, ...)
{
//	FORCE_DEBUG("Calling DO ERROR XXXXXXXX, ctx = 0x%x", ctx );
	GLocation location = *((GLocation*)ctx);
	char buff[10240];
	va_list ap;
	va_start(ap, msg);
	#ifdef _WIN32
	vsprintf_s(buff, sizeof(buff), msg, ap);
	#else
	vsnprintf (buff, sizeof(buff), msg, ap);
	#endif
	va_end(ap);
//	XML_ERROR("%s", buff );

	LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_GENERAL, location, buff);
}
