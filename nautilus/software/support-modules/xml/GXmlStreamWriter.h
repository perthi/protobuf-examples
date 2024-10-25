// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GXmlAttribute.h"
#include <vector>

class GXmlStreamWriter
{
public:
	virtual ~GXmlStreamWriter() {}
	virtual void WriteSingleTag(std::string tag) = 0;
	virtual void WriteSingleTag(std::string tag, std::vector<GXmlAttribute> attributes) = 0;
	virtual void WriteStartTag(std::string tag) = 0;
	virtual void WriteStartTag(std::string tag, std::vector<GXmlAttribute> attributes) = 0;
	virtual void WriteEndTag() = 0;
	virtual void WriteValueTag(std::string tag, std::string value) = 0;
	virtual void WriteValueTag(std::string tag, std::vector<GXmlAttribute> attributes, std::string value) = 0;
	virtual void WriteComment(std::string comment) = 0;
};
