// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlAttribute.h"

GXmlAttribute::GXmlAttribute(const std::string& name, const std::string& value)
	: fName(name), fValue(value)	
{
}

std::string GXmlAttribute::GetName() const 
{ 
	return fName;
}

std::string GXmlAttribute::GetValue() const 
{ 
	return fValue;
}