// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GXmlClassFactory.h"
#include "GXmlStreamReader.h"
#include "GXmlNode.h"

#include <libxml/xmlreader.h>

#include <string>


/// implementation if GXmlStreamReader
class GXmlStreamReaderImpl : public GXmlStreamReader
{
public:
	/// Open file and prepare reader.
	GXmlStreamReaderImpl(const std::string& fileName);
	virtual ~GXmlStreamReaderImpl();

	/// See documentation for GXmlStreamReader::ReadNode
	virtual GXmlNode* ReadNode() override;
	virtual GXmlNode  * GetCurrentNode() override;
	virtual int  API GetLineNumber()    const  override;
	virtual int  API GetColumnNumber()  const  override;

private:
	GXmlStreamReaderImpl operator = (const GXmlStreamReaderImpl & );
	GXmlStreamReaderImpl( const GXmlStreamReaderImpl & );

	/// Allow only the factory to construct objects of this class
	friend GXmlStreamReader* GXmlClassFactory::CreateStreamReader(const std::string& filename);

	/*! @brief Create a node
		Allocates a specific node type based on input parameters.
		@param type node type. If type is invalid or not implemented, an exception is thrown.
		@param name node name
		@param value node value
		@param empty If Zero, then a single tag node is created
		@param attributes attributes associated with node. Only applicable for open tags and single tags
		@return A pointer to a node object, or nullptr if object is unwanted (for instance whitespace or significant whitespace) */
	GXmlNode* CreateNodeFromType(const int type, const char* name, const char* value, const int empty, const std::vector<GXmlAttribute>& attributes) const;

	static void  DoError(void *ctx, const char *msg, ...);

	const std::string fFilename;   /*!< Filename (potentially with path) to XML file */
	xmlTextReaderPtr fReader;      /*!< libxml2 reader */
};