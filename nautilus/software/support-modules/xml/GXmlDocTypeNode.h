// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNodeImpl.h"
#include <string>

#include "GXmlEnums.h"

class GXmlDocTypeNode : public GXmlNodeImpl
{
public:
	GXmlDocTypeNode(const std::string& name);

	virtual eXML_NODETYPE GetType() const override;
};