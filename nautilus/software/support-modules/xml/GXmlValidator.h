// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifndef GXMLVALIDATOR_H
#define GXMLVALIDATOR_H

#include <utilities/GDefinitions.h>

class GXmlValidator
{
public:
	static bool API IsValid(std::string xmlFilename, std::string xsdFilename);
};

#endif // !GXMLVALIDATOR_H
