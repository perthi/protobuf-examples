// -*- mode: c++ -*-

// xml-example1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <xml/GXmlClassFactory.h>
#include <xml/GXmlStreamWriter.h>
#include <xml/GXmlStreamReader.h>
#include <xml/GXmlValidator.h>
//#include <iostream>
#include <utilities/GSystem.h>
#include <utilities/GException.h>
#include <configuration/KFXMLParser.h>
#include <configuration/KFXMLParserHMI.h>
#include <configuration/KFXMLWriter.h>
#include <configuration/KFEntityCamera.h>
#include <configuration/KFConfigCamera.h>
#include  <xml/GXmlDataTypes.h>

#include <logging/LLogApi.h>

using namespace LOGMASTER;


#include <vector>
using std::vector;

#include <memory>
 

#include <configuration/KFXMLParserDevices.h>


void parse(XMLFile_t file_xml, XSDFile_t file_xsd);


#include<configuration/KFEntityHMI.h>
#include <configuration/KFEntityHMICRing.h>

#include  <configuration/KFEntityDevice.h>
#include  <configuration/KFEntityDeviceSolenoid.h>


int main()
{
//	static_assert(std::is_base_of<KFEntityHMI,KFEntityHMICRing >::value, "KFEntityHMICRing must inherit from  KFEntityHMI ");	
//	static_assert(std::is_base_of<KFEntityDevice,  KFEntityDeviceSolenoid >::value, "KFEntityDevice must inherit from  KFEntityDeviceSolenoid ");	
	//static_assert(std::is_base_of<KFEntityDevice, KFEntityHMICRing  >::value, "KFEntityDevice must inherit from  KFEntityDeviceSolenoid ");	
//	static_assert(std::is_base_of<A, B>::value, "T must inherit from KFEntityDeviceSensor");	


//	SET_LOGLEVEL("--all-info");
	SET_LOGFORMAT("10001111");
	KFXMLParserHMI* p = new KFXMLParserHMI();

	string xml = "kf_hmi.xml";
	string xsd = "kf_hmi.xsd";

#ifdef _WIN32
	std::string exedir = g_system()->GetExeDir();
	XMLFile_t file_xml = XMLFile_t(exedir + "..\\..\\config\\" + xml);
	XSDFile_t file_xsd = XSDFile_t(exedir + "..\\..\\config\\" + xsd);
#else
	string ferrotech_home = "FERROTECH_HOME";
	char *tmp =  getenv(ferrotech_home.c_str()  );	
	G_ASSERT_EXCEPTION(tmp != nullptr, "could not find environmen variable %s", ferrotech_home.c_str()  );
	string base = string(tmp);
	XMLFile_t file_xml = XMLFile_t(base + "/config/" + xml);
	XSDFile_t file_xsd = XSDFile_t(base + "/config/" + xsd);
#endif

	bool ret = GXmlValidator::IsValid(file_xml.str(), file_xsd.str());



	try
	{
		G_ASSERT_EXCEPTION(ret != false, "Faild to validate XML file %s against %s", file_xml.str().c_str(), file_xsd.str().c_str());
		parse(file_xml, file_xsd);
	}
	catch (GException &e)
	{
		cout << e.what() << endl;
	}
	catch( std::exception &e)
	{	
		CERR << e.what() << endl;
	}
	catch( string &e)
	{
		CERR << e << endl;
	}
	catch(...)
	{
		G_FATAL("Unknown exception caught validation XML file");
	}

	PUSH();
	SET_LOGFORMAT("11000001");
	SET_LOGLEVEL("--all-info");
	if (ret == true)
	{
		G_INFO("*********************************************************");
		G_INFO("************** VALIDATION PASSED !!! ********************");
		G_INFO("*********************************************************");
	}
	else
	{ 
		G_ERROR("*********************************************************");
		G_ERROR("************** VALIDATION FAILED !!! ********************");
		G_ERROR("*********************************************************");
	}

	POP();

//	delete r;
	return 0;
}


void parse(XMLFile_t file_xml, XSDFile_t file_xsd)
{
	///KFXMLParserDevices* parser = new KFXMLParserDevices();
	KFXMLParserHMI* parser = new KFXMLParserHMI();
	parser->ParseXML(file_xml, file_xsd);
	delete parser;
}
