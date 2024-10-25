// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNodeImpl.h"
#include <string>

#include "GXmlEnums.h"


class GXmlCDataNode : public GXmlNodeImpl
{
public:
	GXmlCDataNode(const std::string& value);
	virtual eXML_NODETYPE GetType() const override;
};