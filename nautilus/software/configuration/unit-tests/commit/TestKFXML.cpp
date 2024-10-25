// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFXML.h"
#include <utilities/GSystem.h>

#include  <configuration/KFXMLParser.h>
#include  <configuration/KFConfigurationHandler.h>

#include <configuration/KFEntityDevice.h>
#include <configuration/KFConfig.h>

#include <kf-main/KFGlobals.h>


XMLFile_t				TestKFXML::fXMLFile;
XSDFile_t				TestKFXML::fXSDFile;
vector< std::shared_ptr<KFEntityDevice> >			TestKFXML::c_v;
vector< std::shared_ptr<KFConfig> >	        TestKFXML::c_cfg;

KFXMLParser*  TestKFXML::p = nullptr;
KFConfigurationHandler*  TestKFXML::cfg = nullptr;


void 
TestKFXML::Parse(const XMLFile_t xml, const XSDFile_t xsd, KFXMLParser*  p )
{
	try
	{
		cfg = KFConfigurationHandler::Instance();
		auto tmp = p->ParseXML(fXMLFile, fXSDFile);
		cfg->AddEntities(tmp);
	}
	catch (GException& e)
	{
		CERR << e.what() << endl;
		FAIL();
	}
	catch (std::exception& e)
	{
		CERR << e.what() << endl;
		FAIL();
	}
	catch (string& e)
	{
		CERR << e << endl;
		FAIL();
	}
	catch (...)
	{
		CERR << "Unknown exception caught" << endl;
		FAIL();
	}
}

