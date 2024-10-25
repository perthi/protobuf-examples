// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifndef GXMLVALIDATORIMPL_H
#define GXMLVALIDATORIMPL_H

#include <string>

#include <libxml/xmlerror.h>

//struct xmlError;
//extern void schemaParseErrorHandler(void *arg, xmlErrorPtr error);

#include <logging/LEnums.h>

using namespace LOGMASTER;

#include <utilities/GDefinitions.h>

class GXmlValidatorImpl
{
public:
	static bool  API  IsValid(std::string xmlFilename, std::string xsdFilename);
	static void  API  SetError(const bool err);
	static bool  API  HasError();
	static eMSGLEVEL  ErrorLevel2Loglevel(const int level);

private:
	static void  DoError(void *ctx, const char *msg, ...);
	static void  DoWarning(void *ctx, const char *msg, ...);

	static bool fHasError;

};

#endif // !GXMLVALIDATORIMPL_H
