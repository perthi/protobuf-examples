// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#include "TestGXmlValidatorImpl.h"
#include <xml/GXmlValidator.h>
#include <utilities/GSystem.h>
 
 #include <cstdlib>



 
 string  TestGXmlValidatorImpl::fDataDir = "";


 void TestGXmlValidatorImpl::SetUpTestCase()
 {
	 #ifdef _WIN32
	 	fDataDir = std::string( g_system()->GetHomeDir()) + std::string("modules\\support-modules\\xml\\unit-tests\\commit\\data\\");
	 #else
			string home = getenv("FERROTECH_HOME");
			fDataDir =  home + "/modules/support-modules/xml/unit-tests/commit/data/";
	 #endif
	
 }



// TEST_F(TestGXmlValidatorImpl, Ok)
// {
// 	std::string xmlFilename = fDataDir + "INM6_S52824_NOR_SNO12_PVT_IRL_J13_J113_2018-10-01T135945.xml";
// 	std::string xsdFilename = fDataDir + "EUR3.SP.00057.DG.ASTR.V10.xsd";
// 	EXPECT_TRUE(GXmlValidator::IsValid(xmlFilename, xsdFilename));
// }


// TEST_F(TestGXmlValidatorImpl, WrongXmlFileName)
// {
// 	std::string xmlFilename = fDataDir + "zz.xml";
// 	std::string xsdFilename = fDataDir + "EUR3.SP.00057.DG.ASTR.V10.xsd";
// 	EXPECT_FALSE(GXmlValidator::IsValid(xmlFilename, xsdFilename));
// }

// TEST_F(TestGXmlValidatorImpl, WrongXmlContent)
// {
// 	std::string xmlFilename = fDataDir + "error.xml";
// 	std::string xsdFilename = fDataDir  + "EUR3.SP.00057.DG.ASTR.V10.xsd";
// 	EXPECT_FALSE(GXmlValidator::IsValid(xmlFilename, xsdFilename));
// }

// TEST_F(TestGXmlValidatorImpl, ValidationFails)
// {
// 	std::string xmlFilename = fDataDir  + "no_remark.xml";
// 	std::string xsdFilename = fDataDir  + "EUR3.SP.00057.DG.ASTR.V10.xsd";
// 	EXPECT_FALSE(GXmlValidator::IsValid(xmlFilename, xsdFilename));
// }
