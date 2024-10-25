// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNodeImpl.h"
#include <string>
#include "GXmlEnums.h"


class GXmlTextNode : public GXmlNodeImpl
{
public:
	GXmlTextNode(const std::string& text);
	virtual eXML_NODETYPE GetType() const override;
};