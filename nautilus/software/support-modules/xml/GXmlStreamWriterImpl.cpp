// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlClassFactory.h"
#include "GXmlStreamWriterImpl.h"
#include <utilities/GException.h>
#include <logging/LLogApi.h>
#include <utilities/GException.h>


#define MY_ENCODING "UTF-8"
#define XML(s,m) G_ASSERT_EXCEPTION(s >= 0, m)

GXmlStreamWriterImpl::~GXmlStreamWriterImpl()
{
	XML(xmlTextWriterEndDocument(fWriter),"xmlTextWriterEndDocument: Error at xmlTextWriterStartDocument");
	xmlFreeTextWriter(fWriter);
}

GXmlStreamWriterImpl::GXmlStreamWriterImpl()
{
}

GXmlStreamWriterImpl::GXmlStreamWriterImpl(std::string fileName)
{
	/* Create a new XmlWriter for uri, with no compression. */
	fWriter = xmlNewTextWriterFilename(fileName.c_str(), 0);
	G_ASSERT_EXCEPTION(fWriter != nullptr, "xmlNewTextWriterFilename failed");

	XML(xmlTextWriterSetIndent(fWriter, 1), "testXmlwriterFilename: Error at xmlTextWriterSetIndent");
	XML(xmlTextWriterSetIndentString(fWriter, BAD_CAST "\t"), "Error setting xmlTextWriterSetIndentString");
	XML(xmlTextWriterStartDocument(fWriter, NULL, MY_ENCODING, NULL), "testXmlwriterFilename: Error at xmlTextWriterStartDocument\n");
}

void GXmlStreamWriterImpl::WriteSingleTag(std::string tag)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), "Error writing xmlTextWriterStartDocument");
	XML(xmlTextWriterEndElement(fWriter), "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteSingleTag(std::string tag, std::vector<GXmlAttribute> attributes)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), "Error writing xmlTextWriterStartDocument");
	for (size_t n = 0; n < attributes.size(); n++)
	{
		XML(xmlTextWriterWriteAttribute(fWriter, BAD_CAST attributes.at(n).GetName().c_str(), BAD_CAST attributes.at(n).GetValue().c_str()), "Error writing xmlTextWriterWriteAttribute");
	}
	XML(xmlTextWriterEndElement(fWriter), "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteStartTag(std::string tag)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), "Error writing xmlTextWriterStartDocument");
}

void GXmlStreamWriterImpl::WriteStartTag(std::string tag, std::vector<GXmlAttribute> attributes)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), "Error writing xmlTextWriterStartDocument");
	for (size_t n = 0; n < attributes.size(); n++)
	{
		XML(xmlTextWriterWriteAttribute(fWriter, BAD_CAST attributes.at(n).GetName().c_str(), BAD_CAST attributes.at(n).GetValue().c_str()), "Error writing xmlTextWriterWriteAttribute");
	}
}

void GXmlStreamWriterImpl::WriteEndTag()
{
	XML(xmlTextWriterEndElement(fWriter), "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteValueTag(std::string tag, std::string value)
{
	XML(xmlTextWriterWriteElement(fWriter, BAD_CAST tag.c_str(), BAD_CAST value.c_str()), "Error writing xmlTextWriterWriteElement");
}

void GXmlStreamWriterImpl::WriteValueTag(std::string tag, std::vector<GXmlAttribute> attributes, std::string value)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), "Error writing xmlTextWriterStartDocument");
	for (size_t n = 0; n < attributes.size(); n++)
	{
		XML(xmlTextWriterWriteAttribute(fWriter, BAD_CAST attributes.at(n).GetName().c_str(), BAD_CAST attributes.at(n).GetValue().c_str()), "Error writing xmlTextWriterWriteAttribute");
	}
	XML(xmlTextWriterWriteString(fWriter, BAD_CAST value.c_str()), "Error writing xmlTextWriterWriteString");
	XML(xmlTextWriterEndElement(fWriter), "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteComment(std::string comment)
{
	XML(xmlTextWriterWriteComment(fWriter, BAD_CAST comment.c_str()), "Error writing xmlTextWriterWriteComment");
}
