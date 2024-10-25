// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlValidatorImpl.h"
#include <utilities/GFileIOHandler.h>
#include <utilities/GException.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlerror.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <logging/LLogApi.h>
#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

using namespace LOGMASTER;

bool GXmlValidatorImpl::fHasError = false;

// DoError and DoWarning cannot print correct source code correct. Thats why we use this hack.
#define SETPOS() { location = GLocation(__FILE__, __LINE__, __func__); }

static void schemaParseErrorHandler(void *ctx, xmlErrorPtr error)
{
	// PUSH();
	// SET_LOGFORMAT("11111111");
	LOGMASTER::eMSGLEVEL loglevel =   GXmlValidatorImpl::ErrorLevel2Loglevel( error->level );
  //  fprintf(stderr, "Error at line %d, column %d\tint1 %d\n%s\n", error->line, error->int2, error->int1, error->message);

	fprintf(stderr, "filename: %s\n", error->file );

	LLogging::Instance()->Log(loglevel, eMSGSYSTEM::SYS_GENERAL, GLocation(error->file, error->line,  ""  ), "Offending file: %s (error code %d) (from %s line[%d])",
	error->message, error->code, __func__, __LINE__  );
	// PUSH();
	// SET_LOGFORMAT("00000001");
	LLogging::Instance()->Log(loglevel, eMSGSYSTEM::SYS_GENERAL, GLocation(error->file, error->line,  ""  ), "%s line %d contains error(s)  !!!!!!!!",  error->file, error->line );
	// POP();

	GXmlValidatorImpl::SetError(true);
	// POP();

}


// typedef struct _xmlError xmlError;
// typedef xmlError *xmlErrorPtr;
// struct _xmlError {
//     int		domain;	/* What part of the library raised this error */
//     int		code;	/* The error code, e.g. an xmlParserError */
//     char       *message;/* human-readable informative error message */
//     xmlErrorLevel level;/* how consequent is the error */
//     char       *file;	/* the filename */
//     int		line;	/* the line number if available */
//     char       *str1;	/* extra string information */
//     char       *str2;	/* extra string information */
//     char       *str3;	/* extra string information */
//     int		int1;	/* extra number information */
//     int		int2;	/* error column # or 0 if N/A (todo: rename field when we would brk ABI) */
//     void       *ctxt;   /* the parser context if available */
//     void       *node;   /* the node in the tree */
// };



void
GXmlValidatorImpl::SetError(const bool err)
{
	fHasError = err;
}

bool
GXmlValidatorImpl::HasError()
{
	return fHasError;
}

bool
GXmlValidatorImpl::IsValid(std::string xmlFilename, std::string xsdFilename)
{
	int has_schema_errors = 0;

	try
	{
		GLocation location = GLocation(__FILE__, __LINE__, __func__);
		G_ASSERT_EXCEPTION(g_file()->CheckFile(xmlFilename), "Cannot find XML-file %s", xmlFilename.c_str());
		G_ASSERT_EXCEPTION(g_file()->CheckFile(xsdFilename), "Cannot find XSD-file %s", xsdFilename.c_str());
		////////::xmlSetGenericErrorFunc(&location, DoError);
		SETPOS(); xmlSchemaParserCtxtPtr schemaTextParser = ::xmlSchemaNewParserCtxt(xsdFilename.c_str());
		G_ASSERT_EXCEPTION(schemaTextParser != nullptr, "Could not create xmlSchemaParserCtxtPtr");
		////////xmlSchemaSetParserErrors(schemaTextParser, DoError, DoWarning, &location);
		xmlSchemaSetParserStructuredErrors( schemaTextParser, schemaParseErrorHandler, &has_schema_errors);
		SETPOS(); xmlSchemaPtr schema = xmlSchemaParse(schemaTextParser);

		if( HasError() == true )
		{
			SetError(false);
			G_FATAL("Has error = TRUE");
			INVALID_ARGUMENT_EXCEPTION("XML file %s contains errors", xsdFilename.c_str() );
		}

		G_ASSERT_EXCEPTION(schema != nullptr, "Could not parse xmlSchemaPtr");

		xmlSetGenericErrorFunc(&location, DoError );

		SETPOS(); xmlDocPtr doc = xmlReadFile(xmlFilename.c_str(), nullptr, 0);

		G_ASSERT_EXCEPTION(doc != nullptr, "Could not parse %s", xmlFilename.c_str());
		SETPOS(); xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(schema);
		xmlSchemaSetValidStructuredErrors(ctxt, schemaParseErrorHandler, &has_schema_errors);
		G_ASSERT_EXCEPTION( has_schema_errors == false, "XML ore XSD contains errors" );
		G_ASSERT_EXCEPTION(ctxt != nullptr, "Could not Create");
		//////	xmlSchemaSetValidErrors(ctxt, DoError, DoWarning, &location);

		SETPOS(); int ret = xmlSchemaValidateDoc(ctxt, doc);

		if( HasError() == true )
		{
			SetError(false);
			G_FATAL("Has error = TRUE");
			INVALID_ARGUMENT_EXCEPTION("XML file %s contains errors", xmlFilename.c_str() );
		}

		xmlSchemaFreeValidCtxt(ctxt);

		xmlFreeDoc(doc);
		G_ASSERT_EXCEPTION(ret <= 0, "%s failed to validate", xmlFilename.c_str());
		G_ASSERT_EXCEPTION(ret >= 0, "%s validation generated an internal error", xmlFilename.c_str());

		return(ret == 0);
	}
	catch (GException & e)
	{
		G_ERROR("%s", e.what() );
		return false;
	}
	catch( std::exception &e)
	{
		G_ERROR("%s", e.what() );
		CERR << e.what() << endl;
		return false;
	}
	catch(std::string &e)
	{
		CERR << e << endl;
	}
	catch (...)
	{
		G_ERROR("Unknown exception caught !!");
		return false;
	}

	return true;
}



void GXmlValidatorImpl::DoError(void *ctx, const char *msg, ...)
{
///	FORCE_DEBUG("Calling DO ERROR");
	GLocation location = *((GLocation*)ctx);
	char buff[10240];
	va_list ap;
	va_start(ap, msg);

	#ifdef _WIN32
	vsprintf_s(buff, sizeof(buff), msg, ap);
	#else
	vsnprintf (buff, sizeof(buff), msg, ap);
	#endif

	va_end(ap);
	LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_GENERAL, location, buff);
}

void GXmlValidatorImpl::DoWarning(void * ctx, const char * msg, ...)
{
//	FORCE_DEBUG("Calling DO WARNING");
	GLocation location = *((GLocation*)ctx);
	char buff[10240];
	va_list ap;
	va_start(ap, msg);

	#ifdef _WIN32
	vsprintf_s(buff, sizeof(buff), msg, ap);
	#else
	vsnprintf (buff, sizeof(buff), msg, ap);
	#endif

	va_end(ap);
	LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING, eMSGSYSTEM::SYS_GENERAL, location, buff);
}



eMSGLEVEL
GXmlValidatorImpl::ErrorLevel2Loglevel(const int level)
{
	switch (level)
	{
	case XML_ERR_NONE:
		 return eMSGLEVEL::LOG_INFO;
		 break;
	case XML_ERR_WARNING:
		 return eMSGLEVEL::LOG_WARNING;
		 break;
	case XML_ERR_ERROR:
		 return eMSGLEVEL::LOG_ERROR;
		 break;
	case XML_ERR_FATAL:
		 return eMSGLEVEL::LOG_FATAL;
		 break;
	default:
		 return eMSGLEVEL::LOG_DEBUG;
		break;
	}

}
