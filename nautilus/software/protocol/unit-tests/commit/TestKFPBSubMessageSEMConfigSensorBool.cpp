// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMConfigSensorBool.h"

#include  <protocol/KFPBSubMessageSEMConfigSensorBool.h>

TestKFPBSubMessageSEMConfigSensorBool::TestKFPBSubMessageSEMConfigSensorBool()
{

}

TestKFPBSubMessageSEMConfigSensorBool::~TestKFPBSubMessageSEMConfigSensorBool()
{
    
}


TEST_F( TestKFPBSubMessageSEMConfigSensorBool,  set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();
   
    m->SetAlarm(true);
    m->SetDeviceIDAux("BLAHH");
    m->SetSignalType( (eSENSOR_INPUT_TYPE)32);
    m->SetActiveHigh(true);

    EXPECT_EQ(m->GetAlarm(), true );
    EXPECT_EQ(m->GetDeviceIDAux(), "BLAHH");
    EXPECT_EQ( (int)m->GetSignalType(),32);
    EXPECT_EQ(m->GetActiveHigh(), true);

    EXPECT_TRUE(m->HasSignalType() );
    EXPECT_TRUE(m->HasActiveHigh() );
    EXPECT_TRUE(m->HasAlarm() );
    EXPECT_TRUE(m->HasDeviceIDAux() );

    m->Reset();
    
    EXPECT_EQ(m->GetAlarm(), false );
    EXPECT_EQ(m->GetDeviceIDAux(), "");
    EXPECT_EQ( (int)m->GetSignalType(),0);
    EXPECT_EQ(m->GetActiveHigh(), false);

   

}



TEST_F(  TestKFPBSubMessageSEMConfigSensorBool, serialize1 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();
    auto m2 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();

     
    m1->SetAlarm(true);
    m1->SetDeviceIDAux("LOREMIPSUM");
    m1->SetSignalType( (eSENSOR_INPUT_TYPE)35);
    m1->SetActiveHigh(true);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
 
    EXPECT_EQ(m2->GetAlarm(), true );
    EXPECT_EQ(m2->GetDeviceIDAux(), "LOREMIPSUM");
    EXPECT_EQ((int)m2->GetSignalType(),35);
    EXPECT_EQ(m2->GetActiveHigh(), true);

    EXPECT_TRUE(m2->HasSignalType() );
    EXPECT_TRUE(m2->HasActiveHigh() );
    EXPECT_TRUE(m2->HasAlarm() );
    EXPECT_TRUE(m2->HasDeviceIDAux() );

}



TEST_F(  TestKFPBSubMessageSEMConfigSensorBool, serialize2 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();
    auto m2 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();

     
    m1->SetAlarm(true);
    m1->SetDeviceIDAux("LOREMIPSUM");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
 
    EXPECT_EQ(m2->GetAlarm(), true );
    EXPECT_EQ(m2->GetDeviceIDAux(), "LOREMIPSUM");

    EXPECT_FALSE(m2->HasSignalType() );
    EXPECT_FALSE(m2->HasActiveHigh() );
    EXPECT_TRUE(m2->HasAlarm() );
    EXPECT_TRUE(m2->HasDeviceIDAux() );

}

TEST_F(  TestKFPBSubMessageSEMConfigSensorBool, serialize3 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();
    auto m2 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();

    m1->SetSignalType( (eSENSOR_INPUT_TYPE)35);
    m1->SetActiveHigh(true);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
 
    EXPECT_EQ((int)m2->GetSignalType(),35);
    EXPECT_EQ(m2->GetActiveHigh(), true);

    EXPECT_TRUE(m2->HasSignalType() );
    EXPECT_TRUE(m2->HasActiveHigh() );
    EXPECT_FALSE(m2->HasAlarm() );
    EXPECT_FALSE(m2->HasDeviceIDAux() );

}


TEST_F(  TestKFPBSubMessageSEMConfigSensorBool, serialize4 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();
    auto m2 = std::make_shared< KFPBSubMessageSEMConfigSensorBool >();

     
  //  m1->SetAlarm(false);
    m1->SetDeviceIDAux("LOREMIPSUM");
    m1->SetSignalType( (eSENSOR_INPUT_TYPE)35);
   // m1->SetActiveHigh(false);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
 
 //   EXPECT_EQ(m2->GetAlarm(), false );
    EXPECT_EQ(m2->GetDeviceIDAux(), "LOREMIPSUM");
    EXPECT_EQ((int)m2->GetSignalType(),35);
//    EXPECT_EQ(m2->GetActiveHigh(), false);

    EXPECT_TRUE(m2->HasSignalType() );
    EXPECT_FALSE(m2->HasActiveHigh() );
    EXPECT_FALSE(m2->HasAlarm() );
    EXPECT_TRUE(m2->HasDeviceIDAux() );

}



