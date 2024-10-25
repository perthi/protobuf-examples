// -*- mode: c++ -*-

#include "TestKFPBMessageSEMConfig.h"

#include <protocol/KFPBMessageSEMConfig.h>
#include <protocol/KFPBSubMessageSEMLinearUnitConversion.h>
#include <protocol/KFPBSubMessageSEMThresholds.h>
#include <protocol/KFPBMessageSEMOneOfMessage.h>

#include <configuration/KFConfigurationHandler.h>


//#include <configuration/KFEntityDeviceMotorStepper.h>
//#include <configuration/KFEntityDevicePWM.h>
//#include <configuration/KFEntityDeviceSensorAnalogDirect.h>
///#include <configuration/KFEntityDeviceSensorTemperature.h>

#include <kf-main/KFGlobals.h>


TestKFPBMessageSEMConfig::TestKFPBMessageSEMConfig()
{

}

TestKFPBMessageSEMConfig::~TestKFPBMessageSEMConfig()
{

}

void
TestKFPBMessageSEMConfig::SetUpTestCase()
{
    auto cfg =  KFConfigurationHandler::Instance();
    cfg->ParseConfigDevices(  XMLFile_t("kf_config_unittest.xml" ), KFGlobals::Instance()->GetXSDFilenameDevices()   );
  //  cfg->ParseConfigHmi(  XMLFile_t("kf_hmi_test.xml"), KFGlobals::Instance()->GetXSDFilenameHmi()  );
 }


TEST_F( TestKFPBMessageSEMConfig, serialize_stepper )
{
    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();

    auto m1 = x1->GetPBConfig();
    auto m2 = x2->GetPBConfig();

    x1->SetMessageType(ePB_ONEOF_TYPE::CONFIG );
   // auto m1 = std::make_shared< KFPBMessageSEMConfig >();
  //  auto m2 = std::make_shared< KFPBMessageSEMConfig >();

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();

    auto stepper1 = m1->GetConfigStepper();
    auto stepper2 = m2->GetConfigStepper();

    auto conversion1 = stepper1->GetStepUnitConversion();
    auto conversion2 = stepper2->GetStepUnitConversion();

    m1->SetConfigType( eSEM_CONFIGTYPE::MOTOR_STEPPER );

    address1->SetCardID(2);
    address1->SetDeviceID("L3-M33");
    address1->SetDeviceName("Sem");
    address1->SetDevicePortNo(99);
    address1->SetDeviceType( (eDEVICE_TYPE)6);
    stepper1->SetAccellleration((float)22.33);
    stepper1->SetMaxAccellleration((float)9.89);
    stepper1->SetMaxSpeed((float)44.44);
    stepper1->SetSpeed((float)20);
    stepper1->SetHomeId("L9-M55");
    stepper1->SetHomeValue(33);
    stepper1->SetInactiveTimeout(123);
    stepper1->SetInativeCurrent( (float)6.7);
    stepper1->SetMaxCurrent( (float)6.9);
    stepper1->SetCurrent((float)4.1);
    stepper1->SetNegativeEndStop((float)55);
    stepper1->SetNegativeEndStopId("L3-L7");
    stepper1->SetPositiveEndStop(88);
    stepper1->SetPositiveEndStopId("L6-M99");

    conversion1->SetSIUnit(7);
    conversion1->SetUnitPerStep((float)4.44);

    string tmp = "";

  //  m1->SerializeToString(tmp);
  //  m2->SerializeFromString(tmp);

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    m1->Reset();

   // EXPECT_EQ(true, false);

    EXPECT_EQ ( (int)x1->GetMessageType(),  (int)ePB_ONEOF_TYPE::CONFIG );
    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::MOTOR_STEPPER );
    EXPECT_EQ( address2->GetCardID(), 2);
    EXPECT_EQ( address2->GetDeviceID(), "L3-M33");
    EXPECT_EQ( address2->GetDeviceName(), "Sem");
    EXPECT_EQ( address2->GetDevicePortNo(), 99);
    EXPECT_EQ( (int)address2->GetDeviceType(), 6);
    EXPECT_NEAR( stepper2->GetAccellleration(), 22.33, 0.001);
    EXPECT_NEAR( stepper2->GetMaxAccellleration(), 9.89, 0.001);
    EXPECT_NEAR( stepper2->GetMaxSpeed(), 44.44, 0.001);
    EXPECT_NEAR( stepper2->GetSpeed(),20, 0.001);
    EXPECT_EQ(   stepper2->GetHomeId(), "L9-M55");
    EXPECT_EQ(   stepper2->GetHomeValue(), 33 );
    EXPECT_EQ(   stepper2->GetInactiveTimeout(),123 );
    EXPECT_NEAR( stepper2->GetInativeCurrent(), 6.7, 0.001);
    EXPECT_NEAR( stepper2->GetMaxCurrent(), 6.9, 0.001);
    EXPECT_NEAR( stepper2->GetCurrent(), 4.1, 0.001);
    EXPECT_NEAR( stepper2->GetNegativeEndStop(), 55, 0.001);
    EXPECT_EQ(   stepper2->GetNegativeEndStopId(), "L3-L7");
    EXPECT_NEAR( stepper2->GetPositiveEndStop(),88, 0.001);
    EXPECT_EQ(   stepper2->GetPositiveEndStopId(),"L6-M99");
    EXPECT_EQ(   conversion2->GetSIUnit(),7);
    EXPECT_NEAR( conversion2->GetUnitPerStep(), 4.44, 0.001);

   // m2->Reset();
    x2->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0 );
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(), 0);
    EXPECT_NEAR( stepper2->GetAccellleration(), 0, 0.001);
    EXPECT_NEAR( stepper2->GetMaxAccellleration(), 0, 0.001);
    EXPECT_NEAR( stepper2->GetMaxSpeed(), 0, 0.001);
    EXPECT_NEAR( stepper2->GetSpeed(), 0, 0.001);
    EXPECT_EQ(   stepper2->GetHomeId(), "");
    EXPECT_EQ(   stepper2->GetHomeValue(), 0 );
    EXPECT_EQ(   stepper2->GetInactiveTimeout(),0 );
    EXPECT_NEAR( stepper2->GetInativeCurrent(), 0, 0.001);
    EXPECT_NEAR( stepper2->GetMaxCurrent(), 0, 0.001);
    EXPECT_NEAR( stepper2->GetCurrent(), 0, 0.001);
    EXPECT_NEAR( stepper2->GetNegativeEndStop(), 0, 0.001);
    EXPECT_EQ(   stepper2->GetNegativeEndStopId(), "");
    EXPECT_NEAR( stepper2->GetPositiveEndStop(),0 , 0.001);
    EXPECT_EQ(   stepper2->GetPositiveEndStopId(),"");
    EXPECT_EQ(   conversion2->GetSIUnit(),0);
    EXPECT_NEAR( conversion2->GetUnitPerStep(), 0, 0.001);
}


TEST_F( TestKFPBMessageSEMConfig, serialize_xy )
{
    auto m1 = std::make_shared< KFPBMessageSEMConfig  >();
    auto m2 = std::make_shared< KFPBMessageSEMConfig >();

    auto xy1 = m1->GetConfigXY();
    auto xy2 = m2->GetConfigXY();

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();

    m1->SetConfigType(eSEM_CONFIGTYPE::MOTOR_XY);

    address1->SetCardID(4);
    address1->SetDeviceID("L3-M332");
    address1->SetDeviceName("Sem2");
    address1->SetDevicePortNo(99);
    address1->SetDeviceType( (eDEVICE_TYPE)6);

    xy1->SetDeviceX("L1-XX");
    xy1->SetDeviceY("L1-YY");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
    m1->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::MOTOR_XY );
    EXPECT_EQ( xy2->GetDeviceX(), "L1-XX" );
    EXPECT_EQ( xy2->GetDeviceY(), "L1-YY" );
    EXPECT_EQ( address2->GetCardID(), 4);
    EXPECT_EQ( address2->GetDeviceID(), "L3-M332");
    EXPECT_EQ( address2->GetDeviceName(), "Sem2");
    EXPECT_EQ( address2->GetDevicePortNo(), 99);
    EXPECT_EQ( (int)address2->GetDeviceType(), 6);

    m2->Reset();


    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( xy2->GetDeviceX(), "" );
    EXPECT_EQ( xy2->GetDeviceY(), "" );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(), 0);
}



TEST_F( TestKFPBMessageSEMConfig, serialize_solenoid )
{
    auto m1 = std::make_shared< KFPBMessageSEMConfig  >();
    auto m2 = std::make_shared< KFPBMessageSEMConfig >();
    auto solenoid1 = m1->GetConfigSolenoid();
    auto solenoid2 = m2->GetConfigSolenoid();
    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    m1->SetConfigType(eSEM_CONFIGTYPE::SOLENOID);

    address1->SetCardID(4);
    address1->SetDeviceID("L3-M332");
    address1->SetDeviceName("Sem2");
    address1->SetDevicePortNo(99);
    address1->SetDeviceType( (eDEVICE_TYPE) 6 );

    solenoid1->SetActivateCurrent((float)12.23);
    solenoid1->SetHoldCurrent((float)44.44);
    solenoid1->SetMaxCurrent((float)77);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
    m1->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::SOLENOID );
    EXPECT_EQ( address2->GetCardID(), 4);
    EXPECT_EQ( address2->GetDeviceID(), "L3-M332");
    EXPECT_EQ( address2->GetDeviceName(), "Sem2");
    EXPECT_EQ( address2->GetDevicePortNo(), 99);
    EXPECT_EQ( (int)address2->GetDeviceType(), 6);

    EXPECT_NEAR(solenoid2->GetActivateCurrent(), 12.23, 0.001);
    EXPECT_NEAR(solenoid2->GetHoldCurrent(),44.44, 0.001);
    EXPECT_NEAR(solenoid2->GetMaxCurrent(), 77, 0.001);

    m2->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(), 0);

    EXPECT_NEAR(solenoid2->GetActivateCurrent(), 0, 0.001);
    EXPECT_NEAR(solenoid2->GetHoldCurrent(),0, 0.001);
    EXPECT_NEAR(solenoid2->GetMaxCurrent(), 0, 0.001);
}



TEST_F( TestKFPBMessageSEMConfig, pwm )
{
    auto m1 = std::make_shared< KFPBMessageSEMConfig  >();
    auto m2 = std::make_shared< KFPBMessageSEMConfig >();
    auto pwm1 = m1->GetConfigPWM();
    auto pwm2 = m2->GetConfigPWM();
    auto conversion1 = pwm1->GetConversion();
    auto conversion2 = pwm2->GetConversion();
    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();

    m1->SetConfigType(eSEM_CONFIGTYPE::PWM );
    address1->SetCardID(4);
    address1->SetDeviceID("L3-M332");
    address1->SetDeviceName("Sem2");
    address1->SetDevicePortNo(99);
    address1->SetDeviceType( (eDEVICE_TYPE)6);

   // pwm1->SetLevel( (float)123.456);
    pwm1->SetMaxLevel( (float)999.99);
    pwm1->SetMinLevel( (float)-22.44);

    conversion1->SetMaxInput(333);
    conversion1->SetMaxOutput(444);
    conversion1->SetMinInput(99);
    conversion1->SetMinOutput(10);

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );
    m1->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::PWM );
    EXPECT_EQ( address2->GetCardID(), 4);
    EXPECT_EQ( address2->GetDeviceID(), "L3-M332");
    EXPECT_EQ( address2->GetDeviceName(), "Sem2");
    EXPECT_EQ( address2->GetDevicePortNo(), 99);
    EXPECT_EQ( (int)address2->GetDeviceType(), 6);

   // EXPECT_NEAR( pwm2->GetLevel(), 123.456, 0.001);
    EXPECT_NEAR( pwm2->GetMaxLevel(), 999.99, 0.001);
    EXPECT_NEAR( pwm2->GetMinLevel(),-22.44, 0.001);

    EXPECT_EQ(conversion2->GetMaxInput(), 333);
    EXPECT_EQ(conversion2->GetMaxOutput(), 444);
    EXPECT_EQ(conversion2->GetMinInput(), 99);
    EXPECT_EQ(conversion2->GetMinOutput(),10);

    m2->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(), 0);

  //  EXPECT_NEAR( pwm2->GetLevel(), 0, 0.001);
    EXPECT_NEAR( pwm2->GetMaxLevel(), 0, 0.001);
    EXPECT_NEAR( pwm2->GetMinLevel(), 0, 0.001);

    EXPECT_EQ(conversion2->GetMaxInput(),  0 );
    EXPECT_EQ(conversion2->GetMaxOutput(), 0 );
    EXPECT_EQ(conversion2->GetMinInput(),  0 );
    EXPECT_EQ(conversion2->GetMinOutput(), 0 );
}



TEST_F( TestKFPBMessageSEMConfig , sensor_analog )
{
    auto m1 = std::make_shared< KFPBMessageSEMConfig  >();
    auto m2 = std::make_shared< KFPBMessageSEMConfig >();

    auto sensor1 = m1->GetConfigSensorAnalog();
    auto sensor2 = m2->GetConfigSensorAnalog();

    auto thresholds1 = sensor1->GetThresholds();
    auto thresholds2 = sensor2->GetThresholds();

    auto conversion1 = sensor1->GetConversion();
    auto conversion2 = sensor2->GetConversion();

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();

    m1->SetConfigType(eSEM_CONFIGTYPE::SENSOR_ANALOG );

    sensor1->SetDeviceIDAux("APBC");
    sensor1->SetInputType( (eSENSOR_INPUT_TYPE )2);

    address1->SetCardID(4);
    address1->SetDeviceID("L3-M332");
    address1->SetDeviceName("Sem2");
    address1->SetDevicePortNo(99);
    address1->SetDeviceType( (eDEVICE_TYPE)6);

    thresholds1->SetAlarmHigh(1, true);
    thresholds1->SetALarmLow(2, true);
    thresholds1->SetWarningHigh(56, true);
    thresholds1->SetWarningLow(22, true);

    conversion1->SetMaxInput(100);
    conversion1->SetMaxOutput(2000);
    conversion1->SetMinInput(-199);
    conversion1->SetMinOutput(1);

    EXPECT_TRUE( sensor1->HasInputType() );
	  EXPECT_TRUE( sensor1->HasThresholds() );
	  EXPECT_TRUE( sensor1->HasDeviceId() );
    EXPECT_TRUE( sensor1->HasLinearUnitConversion() );

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );
    m1->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::SENSOR_ANALOG );

    EXPECT_EQ( address2->GetCardID(), 4);
    EXPECT_EQ( address2->GetDeviceID(), "L3-M332");
    EXPECT_EQ( address2->GetDeviceName(), "Sem2");
    EXPECT_EQ( address2->GetDevicePortNo(), 99);
    EXPECT_EQ( (int)address2->GetDeviceType(), 6);

    EXPECT_EQ( sensor2->GetDeviceIDAux(),  "APBC" );
    EXPECT_TRUE( sensor2->HasInputType() );
	EXPECT_TRUE( sensor2->HasThresholds() );
	EXPECT_TRUE( sensor2->HasDeviceId() );

    EXPECT_NEAR(thresholds2->GetAlarmHigh(),1, 0.001);
    EXPECT_NEAR(thresholds2->GetALarmLow(),2, 0.001);
    EXPECT_NEAR(thresholds2->GetWarningHigh(),56, 0.001);
    EXPECT_NEAR(thresholds2->GetWarningLow(),22, 0.001);

    EXPECT_NEAR(conversion2->GetMaxInput(),100, 0.001);
    EXPECT_NEAR(conversion2->GetMaxOutput(),2000, 0.001);
    EXPECT_NEAR(conversion2->GetMinInput(),-199, 0.001);
    EXPECT_NEAR(conversion2->GetMinOutput(),1, 0.001);

    m2->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(), 0);

    EXPECT_NEAR(thresholds2->GetAlarmHigh(), 0, 0.001);
    EXPECT_NEAR(thresholds2->GetALarmLow(),0, 0.001);
    EXPECT_NEAR(thresholds2->GetWarningHigh(),0, 0.001);
    EXPECT_NEAR(thresholds2->GetWarningLow(),0, 0.001);
    EXPECT_NEAR(conversion2->GetMaxInput(),0, 0.001);
    EXPECT_NEAR(conversion2->GetMaxOutput(),0, 0.001);
    EXPECT_NEAR(conversion2->GetMinInput(),0, 0.001);
    EXPECT_NEAR(conversion2->GetMinOutput(),0, 0.001);
}



TEST_F( TestKFPBMessageSEMConfig , sensor_bool )
{
    auto m1 = std::make_shared< KFPBMessageSEMConfig  >();
    auto m2 = std::make_shared< KFPBMessageSEMConfig >();

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();

    auto bool1 = m1->GetConfigSensorBool();
    auto bool2 = m2->GetConfigSensorBool();

    m1->SetConfigType(eSEM_CONFIGTYPE::SENSOR_BOOL );
    address1->SetCardID(5);
    address1->SetDeviceID("L7-M332");
    address1->SetDeviceName("Sem3");
    address1->SetDevicePortNo(98);
    address1->SetDeviceType( (eDEVICE_TYPE)7);

    bool1->SetActiveHigh(true);
    bool1->SetAlarm(true);
    bool1->SetDeviceIDAux("LXYZ");
    bool1->SetSignalType( (eSENSOR_INPUT_TYPE) 3);

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );
    m1->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::SENSOR_BOOL );
    EXPECT_EQ( address2->GetCardID(), 5);
    EXPECT_EQ( address2->GetDeviceID(), "L7-M332");
    EXPECT_EQ( address2->GetDeviceName(), "Sem3");
    EXPECT_EQ( address2->GetDevicePortNo(), 98);
    EXPECT_EQ( (int)address2->GetDeviceType(), 7);

    EXPECT_EQ(bool2->GetActiveHigh(), true);
    EXPECT_EQ(bool2->GetAlarm(),true);
    EXPECT_EQ(bool2->GetDeviceIDAux(),"LXYZ");
    EXPECT_EQ( (int)bool2->GetSignalType(),3);

    m2->Reset();

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(), 0);

    EXPECT_EQ(bool2->GetActiveHigh(), false);
    EXPECT_EQ(bool2->GetAlarm(),false);
    EXPECT_EQ(bool2->GetDeviceIDAux(),"");
    EXPECT_EQ( (int)bool2->GetSignalType(),0);
}




TEST_F( TestKFPBMessageSEMConfig , xml_config_stepper_l1_M42 )
{
   // PUSH();
   // SET_LOGTARGET("--target-stdout");

    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L1-M42");

    ASSERT_NE (d, nullptr)  << "could not find device with id L1-M42";

    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    EXPECT_TRUE( m1->SetConfiguration(d) );

    auto stepper1 =  m1->GetConfigStepper();
    auto stepper2 =  m2->GetConfigStepper();

    ASSERT_NE(stepper1, nullptr) << "stpper is a ZERO pointer !!!!" ;
    ASSERT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::MOTOR_STEPPER );

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto conversion1 = stepper1->GetStepUnitConversion();
    auto conversion2 = stepper2->GetStepUnitConversion();
    ASSERT_NE(conversion1, nullptr);

    EXPECT_EQ( address1->GetCardID(), 1);
    EXPECT_EQ( address1->GetDeviceID(), "L1-M42");
    EXPECT_EQ( address1->GetDeviceName(), "180 C-ring rotation");
    EXPECT_EQ( address1->GetDevicePortNo(),2);
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::MOTOR_STEPPER );
    EXPECT_EQ(   conversion1->GetSIUnit(), (int)eSTEP_UNIT::ANGLE_DEGREES );
    EXPECT_NEAR( conversion1->GetUnitPerStep(), 1.7, 0.001);


    EXPECT_EQ( stepper1->GetDirectionPositive(), eDIRECTION::CW );
    EXPECT_NEAR( stepper1->GetAccellleration(), 24.24, 0.001);
    EXPECT_NEAR( stepper1->GetMaxAccellleration(),75.75, 0.001);
    EXPECT_NEAR( stepper1->GetMaxSpeed(), 50.50, 0.001);
    EXPECT_NEAR( stepper1->GetSpeed(),20.20, 0.001);
    EXPECT_EQ(   stepper1->GetHomeId(), "S32");
    EXPECT_NEAR(   stepper1->GetHomeValue(), 10.10, 0.001 );
    EXPECT_NEAR(   stepper1->GetInactiveTimeout(),500.5, 0.001 );
    EXPECT_NEAR( stepper1->GetInativeCurrent(), 0.2, 0.001);
    EXPECT_NEAR( stepper1->GetMaxCurrent(), 5.5, 0.001);
    EXPECT_NEAR( stepper1->GetCurrent(),3.3, 0.001);

    EXPECT_FALSE(stepper1->HasNegativeEndstop());

    EXPECT_EQ( (int)stepper1->GetDirectionHome(), (int)eDIRECTION::POSITIVE );
    EXPECT_TRUE( stepper1->HasDirectionHome() );

    EXPECT_EQ(   stepper1->GetNegativeEndStopId(), "L1-M62");
    EXPECT_TRUE( stepper1->HasPositiveEndstop()  );
    EXPECT_NEAR( stepper1->GetPositiveEndStop(), 190.190, 0.001);
    EXPECT_EQ(   stepper1->GetPositiveEndStopId(),"L1-M61");

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );
    m1->Reset();

    EXPECT_EQ( address2->GetCardID(), 1);
    EXPECT_EQ( address2->GetDeviceID(), "L1-M42");
    EXPECT_EQ( address2->GetDeviceName(), "180 C-ring rotation");
    EXPECT_EQ( address2->GetDevicePortNo(),2);
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::MOTOR_STEPPER );
    EXPECT_EQ(   conversion2->GetSIUnit(), (int)eSTEP_UNIT::ANGLE_DEGREES );
    EXPECT_NEAR( conversion2->GetUnitPerStep(), 1.7, 0.001);

     EXPECT_EQ( stepper2->GetDirectionPositive(), eDIRECTION::CW );
    EXPECT_NEAR( stepper2->GetAccellleration(), 24.24, 0.001);
    EXPECT_NEAR( stepper2->GetMaxAccellleration(),75.75, 0.001);
    EXPECT_NEAR( stepper2->GetMaxSpeed(), 50.50, 0.001);
    EXPECT_NEAR( stepper2->GetSpeed(),20.20, 0.001);
    EXPECT_EQ(   stepper2->GetHomeId(), "S32");
    EXPECT_NEAR(   stepper2->GetHomeValue(), 10.10, 0.001 );
    EXPECT_NEAR(   stepper2->GetInactiveTimeout(),500.5, 0.001 );
    EXPECT_NEAR( stepper2->GetInativeCurrent(), 0.2, 0.001);
    EXPECT_NEAR( stepper2->GetMaxCurrent(), 5.5, 0.001);
    EXPECT_NEAR( stepper2->GetCurrent(),3.3, 0.001);

    EXPECT_FALSE(stepper2->HasNegativeEndstop());

    EXPECT_EQ( (int)stepper2->GetDirectionHome(), (int)eDIRECTION::POSITIVE );
    EXPECT_TRUE( stepper2->HasDirectionHome() );
   // EXPECT_NEAR( stepper2->GetNegativeEndStop(), -190, 0.001);
    EXPECT_EQ(   stepper2->GetNegativeEndStopId(), "L1-M62");

     EXPECT_TRUE( stepper2->HasPositiveEndstop()  );
    EXPECT_NEAR( stepper2->GetPositiveEndStop(), 190.190, 0.001);
    EXPECT_EQ(   stepper2->GetPositiveEndStopId(),"L1-M61");
  //  POP();
}



TEST_F( TestKFPBMessageSEMConfig , xml_config_stepper_l1_M44 )
{
    PUSH();
    SET_LOGTARGET("--target-stdout");
    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L1-M44");
    ASSERT_NE (d, nullptr)  << "could not find device with id L1-M44";

    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();

    auto m1 = x1->GetPBConfig();
    auto m2 = x2->GetPBConfig();

    x1->SetMessageType(ePB_ONEOF_TYPE::CONFIG);
   // x2->SetMessageType(ePB_MESSAGE_ONEOF_TYPE::)

   // std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
   // std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    EXPECT_TRUE( m1->SetConfiguration(d) );

    auto stepper1 =  m1->GetConfigStepper();
    auto stepper2 =  m2->GetConfigStepper();

    ASSERT_NE(stepper1, nullptr) << "stpper is a ZERO pointer !!!!" ;
    ASSERT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::MOTOR_STEPPER );

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto conversion1 = stepper1->GetStepUnitConversion();
    auto conversion2 = stepper2->GetStepUnitConversion();
    ASSERT_NE(conversion1, nullptr);

    EXPECT_EQ( address1->GetCardID(), 1);
    EXPECT_EQ( address1->GetDeviceID(), "L1-M44");
    EXPECT_EQ( address1->GetDeviceName(), "180 C-ring translation");
    EXPECT_EQ( address1->GetDevicePortNo(),2);
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::MOTOR_STEPPER );
    EXPECT_EQ(   conversion1->GetSIUnit(), (int)eSTEP_UNIT::MM );
    EXPECT_NEAR( conversion1->GetUnitPerStep(), 1, 0.001);

    EXPECT_EQ( stepper1->GetDirectionPositive(), eDIRECTION::CCW );


    EXPECT_NEAR( stepper1->GetAccellleration(), 22, 0.001);
    EXPECT_NEAR( stepper1->GetMaxAccellleration(),55, 0.001);
    EXPECT_NEAR( stepper1->GetMaxSpeed(), 55, 0.001);


    EXPECT_NEAR( stepper1->GetSpeed(),22, 0.001);
    EXPECT_EQ(   stepper1->GetHomeId(), "S33");
    EXPECT_NEAR(   stepper1->GetHomeValue(), 100.99, 0.001 );
    EXPECT_EQ(   stepper1->GetInactiveTimeout(),600 );
    EXPECT_NEAR( stepper1->GetInativeCurrent(), 0.5, 0.001);


    EXPECT_NEAR( stepper1->GetMaxCurrent(), 6, 0.001);
    EXPECT_NEAR( stepper1->GetCurrent(),3, 0.001);

    EXPECT_TRUE(stepper1->HasNegativeEndstop());


    //EXPECT_EQ( (int)stepper1->GetDirectionHome(), (int)eDIRECTION::POSITIVE );
    EXPECT_FALSE( stepper1->HasDirectionHome() );


    EXPECT_EQ(   stepper1->GetNegativeEndStopId(), "L2-M64");
    EXPECT_TRUE( stepper1->HasPositiveEndstop()  );
    EXPECT_NEAR( stepper1->GetPositiveEndStop(), 185, 0.001);
    EXPECT_EQ(   stepper1->GetPositiveEndStopId(),"L1-M63");

    string tmp = "";

    // m1->SerializeToString( tmp );
    // m2->SerializeFromString( tmp );
    // m1->Reset();

    x1->SerializeToString( tmp );
    x2->SerializeFromString( tmp );
    x1->Reset();

    ASSERT_NE(conversion2, nullptr);

    EXPECT_EQ( address2->GetCardID(), 1);
    EXPECT_EQ( address2->GetDeviceID(), "L1-M44");
    EXPECT_EQ( address2->GetDeviceName(), "180 C-ring translation");
    EXPECT_EQ( address2->GetDevicePortNo(),2);
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::MOTOR_STEPPER );
    EXPECT_EQ(   conversion2->GetSIUnit(), (int)eSTEP_UNIT::MM );
    EXPECT_NEAR( conversion2->GetUnitPerStep(), 1, 0.001);

    EXPECT_EQ( stepper2->GetDirectionPositive(), eDIRECTION::CCW );


    EXPECT_NEAR( stepper2->GetAccellleration(), 22, 0.001);
    EXPECT_NEAR( stepper2->GetMaxAccellleration(),55, 0.001);
    EXPECT_NEAR( stepper2->GetMaxSpeed(), 55, 0.001);


    EXPECT_NEAR( stepper2->GetSpeed(),22, 0.001);
    EXPECT_EQ(   stepper2->GetHomeId(), "S33");
    EXPECT_NEAR(   stepper2->GetHomeValue(), 100.99, 0.001 );
    EXPECT_EQ(   stepper2->GetInactiveTimeout(),600 );
    EXPECT_NEAR( stepper2->GetInativeCurrent(), 0.5, 0.001);


    EXPECT_NEAR( stepper2->GetMaxCurrent(), 6, 0.001);
    EXPECT_NEAR( stepper2->GetCurrent(),3, 0.001);

    EXPECT_TRUE(stepper2->HasNegativeEndstop());


    //EXPECT_EQ( (int)stepper2->GetDirectionHome(), (int)eDIRECTION::POSITIVE );
    EXPECT_FALSE( stepper2->HasDirectionHome() );


    EXPECT_EQ(   stepper2->GetNegativeEndStopId(), "L2-M64");
    EXPECT_TRUE( stepper2->HasPositiveEndstop()  );
    EXPECT_NEAR( stepper2->GetPositiveEndStop(), 185, 0.001);
    EXPECT_EQ(   stepper2->GetPositiveEndStopId(),"L1-M63");


}






TEST_F( TestKFPBMessageSEMConfig , xml_config_xy )
{
    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L2-VXY2");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L2-VXY2";

    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    m2->Reset();

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();

    EXPECT_TRUE( m1->SetConfiguration(d) );
    EXPECT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::MOTOR_XY );
    EXPECT_EQ( m1->GetConfigXY()->GetDeviceX(), "L2-M46");
    EXPECT_EQ( m1->GetConfigXY()->GetDeviceY(), "L2-M47");
    EXPECT_EQ( address1->GetDeviceID(), "L2-VXY2");
    EXPECT_EQ( (int)address1->GetDeviceType( ), (int)eDEVICE_TYPE::MOTOR_VIRTUAL_XY);
    EXPECT_EQ( address1->GetDeviceName(),  "VirtualMotor");

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::MOTOR_XY );
    EXPECT_EQ( m2->GetConfigXY()->GetDeviceX(), "L2-M46");
    EXPECT_EQ( m2->GetConfigXY()->GetDeviceY(), "L2-M47");
    EXPECT_EQ( address2->GetDeviceID(), "L2-VXY2");
    EXPECT_EQ( (int)address2->GetDeviceType( ), (int)eDEVICE_TYPE::MOTOR_VIRTUAL_XY);
    EXPECT_EQ( address2->GetDeviceName(),  "VirtualMotor");
}



TEST_F( TestKFPBMessageSEMConfig , xml_solenoid )
{
    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L22-SOL2");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L22-SOL2";
    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();
    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto sol1 = m1->GetConfigSolenoid();
    auto sol2 = m2->GetConfigSolenoid();

    EXPECT_TRUE( m1->SetConfiguration(d) );
    EXPECT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::SOLENOID );

    EXPECT_EQ( address1->GetCardID(), 1);
    EXPECT_EQ( address1->GetDeviceID(), "L22-SOL2");
    EXPECT_EQ( address1->GetDeviceName(), "Air Input");
    EXPECT_EQ( address1->GetDevicePortNo(),1);
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::SOLENOID );

    EXPECT_NEAR( sol1->GetMaxCurrent(), 3.3, 0.001);
    EXPECT_NEAR( sol1->GetActivateCurrent(), 2.2, 0.001);
    EXPECT_NEAR( sol1->GetHoldCurrent(), 1.1, 0.001 );

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_EQ( address2->GetCardID(), 1);
    EXPECT_EQ( address2->GetDeviceID(), "L22-SOL2");
    EXPECT_EQ( address2->GetDeviceName(), "Air Input");
    EXPECT_EQ( address2->GetDevicePortNo(),1);
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::SOLENOID );
    EXPECT_NEAR( sol2->GetMaxCurrent(), 3.3, 0.001);
    EXPECT_NEAR( sol2->GetActivateCurrent(), 2.2, 0.001);
    EXPECT_NEAR( sol2->GetHoldCurrent(), 1.1, 0.001 );
}



TEST_F( TestKFPBMessageSEMConfig , xml_pwm_signal )
{

    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L33-PWM1");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L33-PWM1";

    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    EXPECT_TRUE( m1->SetConfiguration(d) );
    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto pwm1 = m1->GetConfigPWM();
    auto pwm2 = m2->GetConfigPWM();
    auto conversion1 = pwm1->GetConversion();
    auto conversion2 = pwm2->GetConversion();

    EXPECT_NEAR( conversion1->GetMinInput(), 0.5, 0.001 );
    EXPECT_NEAR( conversion1->GetMinOutput(), 35.6, 0.001 );
    EXPECT_NEAR( conversion1->GetMaxInput(), 100.9, 0.001 );
    EXPECT_NEAR( conversion1->GetMaxOutput(), 300.2, 0.001 );

    EXPECT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::PWM );
    EXPECT_EQ( address1->GetCardID(), 3);
    EXPECT_EQ( address1->GetDeviceID(), "L33-PWM1");
    EXPECT_EQ( address1->GetDeviceName(), "External LED");
    EXPECT_EQ( address1->GetDevicePortNo(),4);
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::PWM_SIGNAL );

   // EXPECT_NEAR( pwm1->GetLevel(), 50.5, 0.001 );
    EXPECT_NEAR( pwm1->GetMaxLevel(), 100.7, 0.001) ;
    EXPECT_NEAR( pwm1->GetMinLevel(), 0.1, 0.001);

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_NEAR( conversion2->GetMinInput(), 0.5, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 35.6, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 100.9, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 300.2, 0.001 );

    EXPECT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::PWM );
    EXPECT_EQ( address2->GetCardID(), 3);
    EXPECT_EQ( address2->GetDeviceID(), "L33-PWM1");
    EXPECT_EQ( address2->GetDeviceName(), "External LED");
    EXPECT_EQ( address2->GetDevicePortNo(),4);
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::PWM_SIGNAL );


  //  EXPECT_NEAR( pwm2->GetLevel(), 50.5, 0.001 );
    EXPECT_NEAR( pwm2->GetMaxLevel(), 100.7, 0.001) ;
    EXPECT_NEAR( pwm2->GetMinLevel(), 0.1, 0.001);

    m2->Reset();

    EXPECT_NEAR( conversion2->GetMinInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 0, 0.001 );

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(),  0 );

  //  EXPECT_NEAR( pwm2->GetLevel(), 0, 0.001 );
    EXPECT_NEAR( pwm2->GetMaxLevel(), 0, 0.001) ;
    EXPECT_NEAR( pwm2->GetMinLevel(), 0, 0.001);
}



TEST_F( TestKFPBMessageSEMConfig , xml_pwm_power )
{
     auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L35-PWM1");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L35-PWM1";

    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    EXPECT_TRUE( m1->SetConfiguration(d) );

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto pwm1 = m1->GetConfigPWM();
    auto pwm2 = m2->GetConfigPWM();
    auto conversion1 = pwm1->GetConversion();
    auto conversion2 = pwm2->GetConversion();

    EXPECT_EQ(   (int)conversion1->GetInputType(), (int)eSENSOR_INPUT_TYPE::PWM_DUTY);
    EXPECT_NEAR( conversion1->GetMinInput(), 10, 0.001 );
    EXPECT_NEAR( conversion1->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion1->GetMaxInput(), 100, 0.001 );
    EXPECT_NEAR( conversion1->GetMaxOutput(), 2000, 0.001 );

    EXPECT_EQ ( (int)m1->GetConfigType(), (int)eSEM_CONFIGTYPE::PWM );
    EXPECT_EQ( address1->GetCardID(), 1);
    EXPECT_EQ( address1->GetDeviceID(), "L35-PWM1");
    EXPECT_EQ( address1->GetDeviceName(), "RoughBoy Spindle");
    EXPECT_EQ( address1->GetDevicePortNo(),1);
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::PWM_POWER );

    ///FORCE_DEBUG("level = %f",  pwm1->GetLevel() );
  ///  EXPECT_NEAR( pwm1->GetLevel(), 70, 0.001 );
    EXPECT_NEAR( pwm1->GetMaxLevel(), 80, 0.001) ;
    EXPECT_NEAR( pwm1->GetMinLevel(), 0, 0.001);

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_EQ(   (int)conversion2->GetInputType(), (int)eSENSOR_INPUT_TYPE::PWM_DUTY);
    EXPECT_NEAR( conversion2->GetMinInput(), 10, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 100, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 2000, 0.001 );

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::PWM );
    EXPECT_EQ( address2->GetCardID(), 1);
    EXPECT_EQ( address2->GetDeviceID(), "L35-PWM1");
    EXPECT_EQ( address2->GetDeviceName(), "RoughBoy Spindle");
    EXPECT_EQ( address2->GetDevicePortNo(),1);
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::PWM_POWER );

  //  EXPECT_NEAR( pwm2->GetLevel(), 70, 0.001 );
    EXPECT_NEAR( pwm2->GetMaxLevel(), 80, 0.001) ;
    EXPECT_NEAR( pwm2->GetMinLevel(), 0, 0.001);

    m2->Reset();

    EXPECT_EQ(   (int)conversion2->GetInputType(),    0 );
    EXPECT_NEAR( conversion2->GetMinInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 0, 0.001 );

    EXPECT_EQ ( (int)m2->GetConfigType(), (int)eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(), 0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ( address2->GetDeviceName(), "");
    EXPECT_EQ( address2->GetDevicePortNo(), 0);
    EXPECT_EQ( (int)address2->GetDeviceType(),  0 );

  //  EXPECT_NEAR( pwm2->GetLevel(), 0, 0.001 );
    EXPECT_NEAR( pwm2->GetMaxLevel(), 0, 0.001) ;
    EXPECT_NEAR( pwm2->GetMinLevel(), 0, 0.001);
}



TEST_F( TestKFPBMessageSEMConfig , xml_sensor_analog  )
{
    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L43-S25");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L43-S25";

    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    EXPECT_TRUE( m1->SetConfiguration(d) );

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto sensor1 = m1->GetConfigSensorAnalog();
    auto sensor2 = m2->GetConfigSensorAnalog();
    auto thresholds1 =  sensor1->GetThresholds();
    auto thresholds2 =  sensor2->GetThresholds();
    auto conversion1 = sensor1->GetConversion();
    auto conversion2 = sensor2->GetConversion();

    EXPECT_EQ( m1->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_ANALOG );
    EXPECT_EQ( address1->GetCardID(), 2) ;
    EXPECT_EQ( address1->GetDevicePortNo(),3 );
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_ANALOG_DIRECT );
    EXPECT_EQ( address1->GetDeviceID(), "L43-S25");
    EXPECT_EQ(address1->GetDeviceName(), "Habitat Internal Temperature" );

    EXPECT_EQ( thresholds1->GetALarmLow(), -2 );
    EXPECT_EQ( thresholds1->GetWarningLow(), -1 );
    EXPECT_EQ( thresholds1->GetWarningHigh(), 1 );
    EXPECT_EQ( thresholds1->GetAlarmHigh(), 2 );

    EXPECT_EQ(   (int)conversion1->GetInputType(), (int)eSENSOR_INPUT_TYPE::MA_4_20 );

    EXPECT_NEAR( conversion1->GetMinInput(), 1.5 , 0.001 );
    EXPECT_NEAR( conversion1->GetMinOutput(), 3, 0.001 );
    //EXPECT_NEAR( conversion1->GetMaxInput(), 10, 0.001 );
    //EXPECT_NEAR( conversion1->GetMaxOutput(), 30, 0.001 );

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_ANALOG );

    EXPECT_EQ( address2->GetCardID(), 2) ;
    EXPECT_EQ( address2->GetDevicePortNo(),3 );
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_ANALOG_DIRECT );
    EXPECT_EQ( address2->GetDeviceID(), "L43-S25");
    EXPECT_EQ(address2->GetDeviceName(), "Habitat Internal Temperature" );

    EXPECT_EQ( thresholds1->GetALarmLow(), -2 );
    EXPECT_EQ( thresholds1->GetWarningLow(), -1 );
    EXPECT_EQ( thresholds1->GetWarningHigh(), 1 );
    EXPECT_EQ( thresholds1->GetAlarmHigh(), 2 );

    EXPECT_EQ(   (int)conversion2->GetInputType(), (int)eSENSOR_INPUT_TYPE::MA_4_20 );

    EXPECT_NEAR( conversion2->GetMinInput(), 1.5, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 3, 0.001 );

    // EXPECT_NEAR( conversion2->GetMaxInput(), 10, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 30, 0.001 );

    m2->Reset();

    EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(),  0) ;
    EXPECT_EQ( address2->GetDevicePortNo(), 0 );
    EXPECT_EQ( (int)address2->GetDeviceType(),  0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ(address2->GetDeviceName(), "" );
    EXPECT_EQ( thresholds2->GetALarmLow(), 0);
    EXPECT_EQ( thresholds2->GetAlarmHigh(), 0);
    EXPECT_EQ( thresholds2->GetWarningLow(), 0);
    EXPECT_EQ( thresholds2->GetWarningHigh(), 0);
    EXPECT_EQ(   (int)conversion2->GetInputType(), 0);
    EXPECT_NEAR( conversion2->GetMinInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 0, 0.001 );
}



TEST_F( TestKFPBMessageSEMConfig , xml_sensor_local  )
{
    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L33-S66");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L33-S66";
    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();
    EXPECT_TRUE( m1->SetConfiguration(d) );
    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto sensor1 = m1->GetConfigSensorAnalog();
    auto sensor2 = m2->GetConfigSensorAnalog();
    auto thresholds1 =  sensor1->GetThresholds();
    auto thresholds2 =  sensor2->GetThresholds();
    auto conversion1 = sensor1->GetConversion();
    auto conversion2 = sensor2->GetConversion();

    EXPECT_EQ( m1->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_ANALOG );
    EXPECT_EQ( sensor1->GetDeviceIDAux(), "L55-S11" );

    EXPECT_EQ( address1->GetCardID(), 1) ;
    EXPECT_EQ( address1->GetDevicePortNo(),1 );
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_LOCAL );
    EXPECT_EQ( address1->GetDeviceID(), "L33-S66");
    EXPECT_EQ(address1->GetDeviceName(), "24VIN" );

    EXPECT_EQ( thresholds1->GetALarmLow(), 18 );
    EXPECT_EQ( thresholds1->GetWarningLow(), 20 );
    EXPECT_EQ( thresholds1->GetWarningHigh(), 28 );
    EXPECT_EQ( thresholds1->GetAlarmHigh(), 30 );

    EXPECT_EQ(   (int)conversion1->GetInputType(), (int)eSENSOR_INPUT_TYPE::V0_10);

    EXPECT_NEAR( conversion1->GetMinInput(), 0, 0.001 );
    EXPECT_NEAR( conversion1->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion1->GetMaxInput(), 10, 0.001 );
    EXPECT_NEAR( conversion1->GetMaxOutput(), 30, 0.001 );

    string tmp = "";

    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_ANALOG );
    EXPECT_EQ( sensor2->GetDeviceIDAux(), "L55-S11" );

    EXPECT_EQ( address2->GetCardID(), 1) ;
    EXPECT_EQ( address2->GetDevicePortNo(),1 );
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_LOCAL );
    EXPECT_EQ( address2->GetDeviceID(), "L33-S66");
    EXPECT_EQ( address2->GetDeviceName(), "24VIN" );

    EXPECT_EQ( thresholds2->GetALarmLow(), 18 );
    EXPECT_EQ( thresholds2->GetWarningLow(), 20 );
    EXPECT_EQ( thresholds2->GetWarningHigh(), 28 );
    EXPECT_EQ( thresholds2->GetAlarmHigh(), 30 );

    EXPECT_EQ(   (int)conversion2->GetInputType(), (int)eSENSOR_INPUT_TYPE::V0_10);

    EXPECT_NEAR( conversion2->GetMinInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 10, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 30, 0.001 );

    m2->Reset();

    EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::UNKNOWN );

    EXPECT_EQ( address2->GetCardID(),  0) ;
    EXPECT_EQ( address2->GetDevicePortNo(), 0 );
    EXPECT_EQ( (int)address2->GetDeviceType(),  0);
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ(address2->GetDeviceName(), "" );

    EXPECT_EQ( thresholds2->GetALarmLow(), 0);
    EXPECT_EQ( thresholds2->GetAlarmHigh(), 0);
    EXPECT_EQ( thresholds2->GetWarningLow(), 0);
    EXPECT_EQ( thresholds2->GetWarningHigh(), 0);

    EXPECT_EQ(   (int)conversion2->GetInputType(), 0);

    EXPECT_NEAR( conversion2->GetMinInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMinOutput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxInput(), 0, 0.001 );
    EXPECT_NEAR( conversion2->GetMaxOutput(), 0, 0.001 );
}



TEST_F( TestKFPBMessageSEMConfig , xml_sensor_bool  )
{
    auto cfg = KFConfigurationHandler::Instance();
    std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L22-S32");
    ASSERT_NE (d, nullptr)  << "could not find device with id  L22-S32";

    std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
    std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

    EXPECT_TRUE( m1->SetConfiguration(d) );

    auto address1 = m1->GetDeviceAddress();
    auto address2 = m2->GetDeviceAddress();
    auto sensor1 = m1->GetConfigSensorBool();
    auto sensor2 = m2->GetConfigSensorBool();

    EXPECT_EQ( m1->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_BOOL );
    EXPECT_EQ( address1->GetCardID(), 3) ;
    EXPECT_EQ( address1->GetDevicePortNo(),6 );
    EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_BOOL_DIRECT );
    EXPECT_EQ( address1->GetDeviceID(), "L22-S32");
    EXPECT_EQ(address1->GetDeviceName(), "180 C-Ring control" );
    EXPECT_EQ( sensor1->GetDeviceIDAux(), "L11-X33");
    EXPECT_EQ( sensor1->GetActiveHigh(), true );
    EXPECT_EQ( sensor1->GetAlarm(), true );

    string tmp = "";
    m1->SerializeToString( tmp );
    m2->SerializeFromString( tmp );

    EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_BOOL );
    EXPECT_EQ( address2->GetCardID(), 3) ;
    EXPECT_EQ( address2->GetDevicePortNo(),6 );
    EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_BOOL_DIRECT );
    EXPECT_EQ( address2->GetDeviceID(), "L22-S32");
    EXPECT_EQ(address2->GetDeviceName(), "180 C-Ring control" );
    EXPECT_EQ( sensor2->GetDeviceIDAux(), "L11-X33");
    EXPECT_EQ( sensor2->GetActiveHigh(), true );
    EXPECT_EQ( sensor2->GetAlarm(), true );

    m2->Reset();

    EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::UNKNOWN );
    EXPECT_EQ( address2->GetCardID(),  0) ;
    EXPECT_EQ( address2->GetDevicePortNo(), 0 );
    EXPECT_EQ( (int)address2->GetDeviceType(),  0 );
    EXPECT_EQ( address2->GetDeviceID(), "");
    EXPECT_EQ(address2->GetDeviceName(), "" );

    EXPECT_EQ( sensor2->GetDeviceIDAux(), "");
    EXPECT_EQ( sensor2->GetActiveHigh(), false );
    EXPECT_EQ( sensor2->GetAlarm(), false );
}



// TEST_F( TestKFPBMessageSEMConfig , xml_sensor_volume  )
// {
//     auto cfg = KFConfigurationHandler::Instance();
//     std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L11-VDQ1");
//     ASSERT_NE (d, nullptr)  << "could not find device with id  L11-VDQ1";
//     std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
//     std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();
//     EXPECT_TRUE( m1->SetConfiguration(d) );
//     auto address1 = m1->GetDeviceAddress();
//     auto address2 = m2->GetDeviceAddress();
//     auto sensor1 = m1->GetConfigSensorAnalog();
//     auto sensor2 = m2->GetConfigSensorAnalog();
//     auto conversion1 = sensor1->GetConversion();
//     auto conversion2 = sensor2->GetConversion();

//     EXPECT_EQ( m1->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_analog );
//     EXPECT_EQ( sensor1->GetDeviceIDAux(), "L11-M32");
//     EXPECT_EQ( conversion1->GetOutputSIUnit(), eOUTPUT_SI_UNIT::ML);
//     EXPECT_EQ( address1->GetCardID(), 1) ;
//     EXPECT_EQ( address1->GetDevicePortNo(), 0 );
//     EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_VOLUME );
//     EXPECT_EQ( address1->GetDeviceID(), "L11-VDQ1");
//     EXPECT_EQ(address1->GetDeviceName(), "Coating Volume" );

//     string tmp = "";

//     m1->SerializeToString( tmp );
//     m2->SerializeFromString( tmp );

//     EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_analog );
//     EXPECT_EQ( sensor2->GetDeviceIDAux(), "L11-M32");
//     EXPECT_EQ( conversion2->GetOutputSIUnit(), eOUTPUT_SI_UNIT::ML);
//     EXPECT_EQ( address2->GetCardID(), 1) ;
//     EXPECT_EQ( address2->GetDevicePortNo(), 0 );
//     EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_VOLUME );
//     EXPECT_EQ( address2->GetDeviceID(), "L11-VDQ1");
//     EXPECT_EQ(address2->GetDeviceName(), "Coating Volume" );

//     m2->Reset();

//     EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::UNKNOWN );
//     EXPECT_EQ( sensor2->GetDeviceIDAux(), "");
//     EXPECT_EQ( (int)conversion2->GetOutputSIUnit(), 0 );
//     EXPECT_EQ( address2->GetCardID(), 0 ) ;
//     EXPECT_EQ( address2->GetDevicePortNo(), 0 );
//     EXPECT_EQ( (int)address2->GetDeviceType(),  0 );
//     EXPECT_EQ( address2->GetDeviceID(), "");
//     EXPECT_EQ(address2->GetDeviceName(), "" );
// }


// TEST_F( TestKFPBMessageSEMConfig , xml_sensor_temperature  )
// {
//     auto cfg = KFConfigurationHandler::Instance();
//     std::shared_ptr<KFEntityDevice> d = cfg->GetDeviceByID("L6-M77");
//     ASSERT_NE (d, nullptr)  << "could not find device with id  L6-M77";

//     std::shared_ptr<KFPBMessageSEMConfig> m1 = std::make_shared< KFPBMessageSEMConfig  >();
//     std::shared_ptr<KFPBMessageSEMConfig> m2 = std::make_shared< KFPBMessageSEMConfig  >();

//     EXPECT_TRUE( m1->SetConfiguration(d) );

//     auto address1 = m1->GetDeviceAddress();
//     auto address2 = m2->GetDeviceAddress();
//     auto sensor1 = m1->GetConfigSensorAnalog();
//     auto sensor2 = m2->GetConfigSensorAnalog();
//     auto thresholds1 =  sensor1->GetThresholds();
//     auto thresholds2 =  sensor2->GetThresholds();
//     auto conversion1 = sensor1->GetConversion();
//     auto conversion2 = sensor2->GetConversion();

//     EXPECT_EQ( m1->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_analog );
//     EXPECT_EQ( sensor1->GetDeviceIDAux(), "L1-M11" );
//     EXPECT_EQ( address1->GetCardID(), 3) ;
//     EXPECT_EQ( address1->GetDevicePortNo(), 4 );
//     EXPECT_EQ( (int)address1->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_TEMPERATURE );
//     EXPECT_EQ( address1->GetDeviceID(), "L6-M77");
//     EXPECT_EQ( address1->GetDeviceName(), "Test" );
//     EXPECT_EQ( thresholds1->GetALarmLow(), -10 );
//     EXPECT_EQ( thresholds1->GetWarningLow(), -1 );
//     //EXPECT_EQ( thresholds1->GetWarningHigh(), 5 );
//     EXPECT_EQ( thresholds1->GetAlarmHigh(), 100.5 );

//     EXPECT_FALSE( thresholds1->HasWarningHigh() );
//     EXPECT_TRUE ( thresholds1->HasAlarmHigh() );
//     EXPECT_TRUE ( thresholds1->HasWarningLow() );
//     EXPECT_TRUE ( thresholds1->HasALarmLow() );

//     EXPECT_EQ(   (int)conversion1->GetInputType(), (int)eSENSOR_INPUT_TYPE::MA_4_20);
//     EXPECT_EQ(   (int)conversion1->GetOutputSIUnit(), (int)eOUTPUT_SI_UNIT::CELCIUS);

//     string tmp = "";

//     m1->SerializeToString( tmp );
//     m2->SerializeFromString( tmp );

//     EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::SENSOR_analog );
//     EXPECT_EQ( sensor2->GetDeviceIDAux(), "L1-M11" );
//     EXPECT_EQ( address2->GetCardID(), 3) ;
//     EXPECT_EQ( address2->GetDevicePortNo(), 4 );
//     EXPECT_EQ( (int)address2->GetDeviceType(),  (int)eDEVICE_TYPE::SENSOR_TEMPERATURE );
//     EXPECT_EQ( address2->GetDeviceID(), "L6-M77");
//     EXPECT_EQ( address2->GetDeviceName(), "Test" );
//     EXPECT_EQ( thresholds2->GetALarmLow(), -10 );
//     EXPECT_EQ( thresholds2->GetWarningLow(), -1 );
//   //  EXPECT_EQ( thresholds2->GetWarningHigh(), 5 );
//    // EXPECT_EQ( thresholds2->GetAlarmHigh(), 100 );

//     EXPECT_EQ( thresholds1->GetAlarmHigh(), 100.5 );

//     EXPECT_FALSE( thresholds2->HasWarningHigh() );
//     EXPECT_TRUE ( thresholds2->HasAlarmHigh() );
//     EXPECT_TRUE ( thresholds2->HasWarningLow() );
//     EXPECT_TRUE ( thresholds2->HasALarmLow() );

//     EXPECT_EQ( (int)conversion2->GetInputType(), (int)eSENSOR_INPUT_TYPE::MA_4_20);
//     EXPECT_EQ( (int)conversion2->GetOutputSIUnit(), (int)eOUTPUT_SI_UNIT::CELCIUS);

//     m2->Reset();

//     EXPECT_EQ( m2->GetConfigType(), eSEM_CONFIGTYPE::UNKNOWN );
//     EXPECT_EQ( sensor2->GetDeviceIDAux(), "" );
//     EXPECT_EQ( address2->GetCardID(), 0) ;
//     EXPECT_EQ( address2->GetDevicePortNo(), 0 );
//     EXPECT_EQ( (int)address2->GetDeviceType(),  0 );
//     EXPECT_EQ( address2->GetDeviceID(), "");
//     EXPECT_EQ( address2->GetDeviceName(), "" );
//     EXPECT_EQ( thresholds2->GetALarmLow(), 0 );
//     EXPECT_EQ( thresholds2->GetWarningLow(), 0 );
//     EXPECT_EQ( thresholds2->GetWarningHigh(), 0 );
//     EXPECT_EQ( thresholds2->GetAlarmHigh(), 0 );
//     EXPECT_EQ( (int)conversion2->GetInputType(),  0 );
//     EXPECT_EQ( (int)conversion2->GetOutputSIUnit(), 0 );
// }



