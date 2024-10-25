// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GXmlNodeImpl.h"
#include <string>
#include "GXmlEnums.h"

class GXmlCommentNode : public GXmlNodeImpl
{
public:
	GXmlCommentNode(const std::string& comment);
	virtual eXML_NODETYPE GetType() const override;
};