// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <testlib/TestBase.h>
#include <xml/GXmlDataTypes.h>
#include <memory>


struct  KFEntityDevice;
struct  KFConfig;
class   KFXMLParser;
class   KFConfigurationHandler;

#include <vector>
using std::vector;

class TestKFXML : public TestBase
{

protected:
	void   Parse( const XMLFile_t xml, const XSDFile_t xsd,   KFXMLParser * p  );
	static XMLFile_t fXMLFile;
	static XSDFile_t fXSDFile;
	static vector< std::shared_ptr<KFEntityDevice> > c_v;
	static vector< std::shared_ptr<KFConfig> > c_cfg;
	static KFXMLParser*  p;
	static KFConfigurationHandler* cfg;


};

