// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMConfigSensorAnalog.h"
#include <protocol/KFPBSubMessageSEMConfigSensorAnalog.h>
#include <protocol/KFPBSubMessageSEMThresholds.h>
#include <protocol/KFPBSubMessageSEMLinearUnitConversion.h>
#include <protocol/KFPBMessageSEMOneOfMessage.h>


TestKFPBSubMessageSEMConfigSensorAnalog::TestKFPBSubMessageSEMConfigSensorAnalog()
{

}



TestKFPBSubMessageSEMConfigSensorAnalog::~TestKFPBSubMessageSEMConfigSensorAnalog()
{

}





TEST_F( TestKFPBSubMessageSEMConfigSensorAnalog, set_get )
{

    auto m = std::make_shared< KFPBSubMessageSEMConfigSensorAnalog >();
    auto conversion = m->GetConversion();
    auto thresholds = m->GetThresholds();

    m->SetDeviceIDAux("LX-123");
    m->SetInputType( (eSENSOR_INPUT_TYPE)32);
    conversion->SetMaxInput(1);
    conversion->SetMaxOutput((float)33.33);
    conversion->SetMinInput((float)12.34 );
    conversion->SetMinOutput((float)333.444);
	conversion->SetInputType(eSENSOR_INPUT_TYPE::MA_4_20);

    thresholds->SetAlarmHigh((float)123.33, true );
    thresholds->SetALarmLow((float)10.123, true );
    thresholds->SetWarningHigh((float)35.35, true );
    thresholds->SetWarningLow((float)-10.88, true);

    EXPECT_EQ(m->GetDeviceIDAux(), "LX-123");
    EXPECT_EQ( (int)m->GetInputType(), 32 );


    EXPECT_EQ(conversion->GetMaxInput(),  1 );
    EXPECT_NEAR(conversion->GetMaxOutput(), 33.33, 0.001);
    EXPECT_NEAR(conversion->GetMinInput(), 12.34, 0.001);
    EXPECT_NEAR(conversion->GetMinOutput(), 333.444, 0.001);
	EXPECT_EQ((int)conversion->GetInputType(), (int)eSENSOR_INPUT_TYPE::MA_4_20);

    EXPECT_NEAR(thresholds->GetAlarmHigh(), 123.33, 0.001);
    EXPECT_NEAR(thresholds->GetALarmLow(), 10.123, 0.001);
    EXPECT_NEAR(thresholds->GetWarningHigh(),35.35, 0.001);
    EXPECT_NEAR(thresholds->GetWarningLow(), -10.88, 0.001);

    m->Reset();

    EXPECT_EQ(m->GetDeviceIDAux(), "");
    EXPECT_EQ( (int)m->GetInputType(), 0  );
    EXPECT_EQ(conversion->GetMaxInput(), 0 );
    EXPECT_NEAR(conversion->GetMaxOutput(), 0, 0.01);
    EXPECT_NEAR(conversion->GetMinInput(), 0, 0.01);
    EXPECT_NEAR(conversion->GetMinOutput(), 0, 0.01);
	EXPECT_EQ((int)conversion->GetInputType(), 0);


    EXPECT_NEAR(thresholds->GetAlarmHigh(), 0, 0.001);
    EXPECT_NEAR(thresholds->GetALarmLow(), 0, 0.001);
    EXPECT_NEAR(thresholds->GetWarningHigh(), 0, 0.001 );
    EXPECT_NEAR(thresholds->GetWarningLow(), 0, 0.001);

}



TEST_F( TestKFPBSubMessageSEMConfigSensorAnalog, serialize )
{
    auto x1   =  std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2   =  std::make_shared<KFPBMessageSEMOneOfMessage>();
    x1->SetConfigType(  eSEM_CONFIGTYPE::SENSOR_ANALOG );
    x1->SetMessageType( ePB_ONEOF_TYPE::CONFIG );

    auto m1 = x1->GetPBConfig()->GetConfigSensorAnalog();
    auto m2 = x2->GetPBConfig()->GetConfigSensorAnalog();

    //auto m2 = std::make_shared< KFPBSubMessageSEMConfigSensorAnalog  >();

    //auto m1 = std::make_shared< KFPBSubMessageSEMConfigSensorAnalog  >();
    //auto m2 = std::make_shared< KFPBSubMessageSEMConfigSensorAnalog  >();

    auto conversion1 = m1->GetConversion();
    auto conversion2 = m2->GetConversion();
    auto thresholds1 = m1->GetThresholds();
    auto thresholds2 = m2->GetThresholds();

    m1->SetDeviceIDAux("LX-123");
    m1->SetInputType( (eSENSOR_INPUT_TYPE)32);
    conversion1->SetMaxInput(1);
    conversion1->SetMaxOutput((float)33.33);
    conversion1->SetMinInput((float)12.34);
    conversion1->SetMinOutput((float)333.444);
	conversion1->SetInputType(eSENSOR_INPUT_TYPE::MA_0_20);
    thresholds1->SetAlarmHigh((float)123.33, true );
    thresholds1->SetALarmLow((float)10.123, true);
    thresholds1->SetWarningHigh((float)35.35, true);
    thresholds1->SetWarningLow((float)-10.88, true );

    string tmp = "";

  //  m1->SerializeToString(tmp);
  //  m2->SerializeFromString(tmp);

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    EXPECT_EQ(m2->GetDeviceIDAux(), "LX-123");
    EXPECT_EQ( (int)m2->GetInputType(), 32 );
    EXPECT_NEAR(conversion2->GetMaxInput(),  1.00, 0.001 );
    EXPECT_NEAR(conversion2->GetMaxOutput(), 33.33, 0.001);
    EXPECT_NEAR(conversion2->GetMinInput(), 12.34, 0.001);
    EXPECT_NEAR(conversion2->GetMinOutput(), 333.444, 0.001);
	EXPECT_EQ( (int)conversion2->GetInputType(), (int)eSENSOR_INPUT_TYPE::MA_0_20);
	EXPECT_NEAR(thresholds2->GetAlarmHigh(), 123.33, 0.001);
    EXPECT_NEAR(thresholds2->GetALarmLow(), 10.123, 0.001);
    EXPECT_NEAR(thresholds2->GetWarningHigh(),35.35, 0.001);
    EXPECT_NEAR(thresholds2->GetWarningLow(), -10.88, 0.001);
}

