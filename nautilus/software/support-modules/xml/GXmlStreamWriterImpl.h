// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GXmlStreamWriter.h"
#include "GXmlStreamWriterImpl.h"
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <string>

class GXmlStreamWriterImpl :public GXmlStreamWriter
{
public:
	virtual ~GXmlStreamWriterImpl();
	GXmlStreamWriterImpl(std::string fileName);
private:
	GXmlStreamWriterImpl operator = (const GXmlStreamWriterImpl & );
	GXmlStreamWriterImpl( const GXmlStreamWriterImpl & );

	
	// Only the class factory can create this class
	friend GXmlStreamWriter* GXmlClassFactory::CreateStreamWriter(std::string fileName);

	xmlTextWriterPtr fWriter;

	GXmlStreamWriterImpl();
	virtual void WriteSingleTag(std::string tag) override;
	virtual void WriteSingleTag(std::string tag, std::vector<GXmlAttribute> attributes) override;
	virtual void WriteStartTag(std::string tag) override;
	virtual void WriteStartTag(std::string tag, std::vector<GXmlAttribute> attributes) override;
	virtual void WriteEndTag() override;
	virtual void WriteValueTag(std::string tag, std::string value) override;
	virtual void WriteValueTag(std::string tag, std::vector<GXmlAttribute> attributes, std::string value) override;
	virtual void WriteComment(std::string comment) override;
};
