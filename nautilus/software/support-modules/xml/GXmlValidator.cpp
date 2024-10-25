// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlValidator.h"
#include "GXmlValidatorImpl.h"

bool GXmlValidator::IsValid(std::string xmlFilename, std::string xsdFilename)
{
	return(GXmlValidatorImpl::IsValid(xmlFilename, xsdFilename));
}
