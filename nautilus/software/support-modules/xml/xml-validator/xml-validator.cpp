// -*- mode: c++ -*-

#include <logging/LLogApi.h>
#include <utilities/GDefinitions.h>

using namespace LOGMASTER;
#include <iostream>
using std::cout;
using std::endl;

#ifndef _WIN32
#include <version-info/GVersionMenu.h>
#endif


#include <cmdline/GLogApplication.h>
#include <cmdline/GArgument.h>
#include <cmdline/GCommandLineArgument.h>

#include <memory>
#include <functional>

#include <utilities/GString.h>
//#include <utilities/GTokenizer.h>

#include <xml/GXmlDataTypes.h>
#include <xml/GXmlValidator.h>


#include <utilities/GException.h>



bool help( );


auto g = std::make_shared<GLogApplication>();

int main(int argc, const char **  argv )
{
    LLogging::Instance()->SetLogFileName("xml-validator.log");

#ifndef _WIN32
	GVersionMenu::Instance()->ScanArguments(argc, argv);
#endif

	g->InitLogArgs();

    string xml;
    string xsd;

    vector<string> tokens = g_tokenizer()->Tokenize(argc, argv);

    auto  xml_arg =  new  GCommandLineArgument < string >("-xml", "-xml [XML filename]", "The XML filename to use", &xml, fgkMANDATORY, 0 );
    auto  xsd_arg =  new  GCommandLineArgument < string >("-xsd", "-xsd [XSD filename]", "The XSD filename to use", &xsd, fgkMANDATORY, 0 );
    g->AddArgument(xml_arg);
    g->AddArgument(xsd_arg);


    if( g_string()->Contains(tokens, "-help") )
    {
        help();
        return 0;
    }

    g->ScanArguments(argc, argv);

    // PUSH();
    // SET_LOGLEVEL("--all-off --all-info --xml-info");
	// SET_LOGFORMAT("--target-stdout 01101111");

	// PUSH();
	// SET_LOGFORMAT("--target-stdout 00000001");
	XML_INFO("XML file set to: %s", xml.c_str() );
    XML_INFO("XSD file set to: %s", xsd.c_str() );
	// POP();

    bool has_error = false;

    auto  validator = std::make_shared<GXmlValidator>();

    try
    {


        if( validator->IsValid(xml, xsd) ==  true )
        {
			// PUSH();
			// SET_LOGFORMAT("--target-stdout 00000001");
            XML_INFO("SUCCSESS !!, %s is well formed and validated against %s", xml.c_str(), xsd.c_str() );
			// POP();
        }
        else
        {
            help();
            XML_FATAL("Failed to validate %s against %s", xml.c_str(), xsd.c_str() );
            has_error = true;
            return -1;
        }
    }
    catch( GException  &e)
    {
        help();
        XML_FATAL("%s", e.what() );
        has_error = true;
    }
    catch(const std::exception& e)
    {
        help();
        XML_FATAL("%s", e.what() );
        has_error = true;
    }
    catch( const string e)
    {
        help();
        XML_FATAL("%s", e.c_str() ) ;
        has_error = true;
    }
    catch(...)
    {
        help();
        XML_FATAL( "Unknown exception caught parsing files: xml = %s\txsd = %s", xml.c_str(), xsd.c_str()  );
        has_error = true;
    }

    if( has_error == true )
    {
        XML_INFO("see logfile: %s  for details",  LLogging::Instance()->GetLogFileName().c_str());
        return -1;
    }
    else
    {
        return -1;
    }

    // POP();

    return 0;

}



bool
help(  )
{
    // PUSH();
    // SET_LOGLEVEL("--xml-info");
    // SET_LOGFORMAT("00000001");
    XML_INFO("\n%s\n",  g->Help().c_str() );
    // POP();
    return true;
}