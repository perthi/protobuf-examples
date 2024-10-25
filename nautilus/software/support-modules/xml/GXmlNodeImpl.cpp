// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlNodeImpl.h"
#include <string>

GXmlNodeImpl::GXmlNodeImpl(const std::string& name, const std::string& value)
	: fkName(name), fkValue(value)
{
}

std::string GXmlNodeImpl::GetValue() const
{
	return fkValue;
}

std::string GXmlNodeImpl::GetName() const
{
	return fkName;
}

std::vector<GXmlAttribute> GXmlNodeImpl::GetAttributes() const
{
	return {};
}

GXmlNodeImpl::~GXmlNodeImpl()
{
}

