// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNodeImpl.h"
#include <string>
#include "GXmlEnums.h"


class GXmlProcInstructNode : public GXmlNodeImpl
{
public:
	GXmlProcInstructNode(const std::string& target, const std::string& content);

	virtual eXML_NODETYPE GetType() const override;
};