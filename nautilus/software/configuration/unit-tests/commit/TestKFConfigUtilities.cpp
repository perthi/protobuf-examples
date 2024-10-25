// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFConfigUtilities.h"
#include <configuration/KFConfigUtilities.h>
#include <xml/GXmlDataTypes.h>


TestKFConfigUtilities::TestKFConfigUtilities()
{

}

TestKFConfigUtilities::~TestKFConfigUtilities()
{

}



TEST_F(TestKFConfigUtilities, filenames )
{
    XMLFile_t xml;
    XSDFile_t xsd;
    auto u =  KFConfigUtilities::Instance(); 


    string xml_fname_generated = u->GenerateFilePath() + "pth_test.xml";     

    u->InitFileXML("pth_test.xml", xml);

    EXPECT_EQ( xml.str(), xml_fname_generated );




  //  EXPECT_FALSE(true);
    
}