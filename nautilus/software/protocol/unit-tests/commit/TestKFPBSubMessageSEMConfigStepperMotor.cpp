// -*- mode: c++ -*-
#include "TestKFPBSubMessageSEMConfigStepperMotor.h"
#include <protocol/KFPBSubMessageSEMConfigStepperMotor.h>
#include <protocol/KFPBSubMessageSEMStepUnitConversion.h>

#include <protocol/KFPBMessageSEMOneOfMessage.h>

TestKFPBSubMessageSEMConfigStepperMotor::TestKFPBSubMessageSEMConfigStepperMotor()
{

}

TestKFPBSubMessageSEMConfigStepperMotor::~TestKFPBSubMessageSEMConfigStepperMotor()
{

}


TEST_F(  TestKFPBSubMessageSEMConfigStepperMotor, set_get )
{
    auto   m = std::make_shared< KFPBSubMessageSEMConfigStepperMotor>();
    KFPBSubMessageSEMStepUnitConversion    *u =  m->GetStepUnitConversion();

    u->SetSIUnit(7);
    u->SetUnitPerStep((float)0.33);
	 m->SetNegativeEndStop((float)1234.56);
	 m->SetPositiveEndStop((float)3456.789);
	 m->SetMaxSpeed((float)11.33);
     m->SetSpeed((float)55.66);
	 m->SetMaxAccellleration((float)77.88);
	 m->SetAccellleration((float)88.99);
	 m->SetMaxCurrent((float)98.98);
	 m->SetCurrent((float)13.13);
	 m->SetInactiveTimeout(333);
	 m->SetInativeCurrent((float)4.5);
	 m->SetHomeValue((float)100.9);
	 m->SetHomeId("L1-M32");
	 m->SetNegativeEndStopId("L2-M33");
	 m->SetPositiveEndStopId("L3-M34");
	 
     EXPECT_NEAR( m->GetNegativeEndStop(), 1234.56, 0.01);
	 EXPECT_NEAR( m->GetPositiveEndStop(),3456.789, 0.01);
     EXPECT_NEAR( m->GetMaxSpeed(),11.33, 0.01);
     EXPECT_NEAR( m->GetSpeed(),55.66, 0.01);
     EXPECT_NEAR( m->GetMaxAccellleration(),77.88, 0.01);
     EXPECT_NEAR( m->GetAccellleration(), 88.99, 0.01);
	 EXPECT_NEAR( m->GetMaxCurrent(), 98.98, 0.01);
	 EXPECT_NEAR( m->GetCurrent(), 13.13, 0.01) ;
	 EXPECT_EQ  ( m->GetInactiveTimeout(), 333);
	 EXPECT_NEAR( m->GetInativeCurrent(),4.5, 0.01);
	 EXPECT_NEAR( m->GetHomeValue(),100.9, 0.01) ;
	 EXPECT_EQ( m->GetHomeId(), "L1-M32" );
	 EXPECT_EQ( m->GetNegativeEndStopId(), "L2-M33");
     EXPECT_EQ( m->GetPositiveEndStopId(), "L3-M34");

     EXPECT_EQ( u->GetSIUnit(), 7);
     EXPECT_NEAR( u->GetUnitPerStep(), 0.33, 0.01);

	m->Reset();


     EXPECT_NEAR( m->GetNegativeEndStop(), 0, 0.01);
	 EXPECT_NEAR( m->GetPositiveEndStop(), 0, 0.01);
     EXPECT_NEAR( m->GetMaxSpeed(),0, 0.01);
     EXPECT_NEAR( m->GetSpeed(), 0, 0.01);
     EXPECT_NEAR( m->GetMaxAccellleration(), 0, 0.01);
     EXPECT_NEAR( m->GetAccellleration(), 0, 0.01);
	 EXPECT_NEAR( m->GetMaxCurrent(), 0, 0.01);
	 EXPECT_NEAR( m->GetCurrent(), 0, 0.01) ;
	 EXPECT_EQ  ( m->GetInactiveTimeout(), 0);
	 EXPECT_NEAR( m->GetInativeCurrent(), 0, 0.01);
	 EXPECT_NEAR( m->GetHomeValue(),0, 0.01) ;
	 EXPECT_EQ( m->GetHomeId(), "" );
	 EXPECT_EQ( m->GetNegativeEndStopId(), "");
     EXPECT_EQ( m->GetPositiveEndStopId(), "");

     EXPECT_EQ( u->GetSIUnit(), 0);
     EXPECT_NEAR( u->GetUnitPerStep(), 0, 0.01);



}




TEST_F( TestKFPBSubMessageSEMConfigStepperMotor, serialize )
{
	 auto x1   =  std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2   =  std::make_shared<KFPBMessageSEMOneOfMessage>();
    x1->SetConfigType(  eSEM_CONFIGTYPE::MOTOR_STEPPER );
    x1->SetMessageType( ePB_ONEOF_TYPE::CONFIG );

    auto m1 = x1->GetPBConfig()->GetConfigStepper();
    auto m2 = x2->GetPBConfig()->GetConfigStepper();


  //  auto m1 = std::make_shared<KFPBSubMessageSEMConfigStepperMotor>();
  //  auto m2 = std::make_shared<KFPBSubMessageSEMConfigStepperMotor>();
    KFPBSubMessageSEMStepUnitConversion    *u1 =  m1->GetStepUnitConversion();
    KFPBSubMessageSEMStepUnitConversion    *u2 =  m2->GetStepUnitConversion();

	///m1->fCmd->

	auto address1 = x1->GetPBConfig()->GetDeviceAddress();
	auto address2 = x2->GetPBConfig()->GetDeviceAddress();
	address1->SetCardID(99);

	
     u1->SetSIUnit(6);
     u1->SetUnitPerStep((float)0.44);
	 m1->SetNegativeEndStop((float)1234.56);
	 m1->SetPositiveEndStop((float)3456.789);
	 m1->SetMaxSpeed((float)11.33);
     m1->SetSpeed((float)55.66);
	 m1->SetMaxAccellleration((float)77.88);
	 m1->SetAccellleration((float)88.99);
	 m1->SetMaxCurrent((float)98.98);
	 m1->SetCurrent((float)13.13);
	 m1->SetInactiveTimeout(333);
	 m1->SetInativeCurrent((float)4.5);
	 m1->SetHomeValue((float)100.9);
	 m1->SetHomeId("XL1-M32");
	 m1->SetNegativeEndStopId("XL2-M33");
	 m1->SetPositiveEndStopId("XL3-M34");

//	EXPECT_TRUE(false);

    string tmp = "";

  //  m1->SerializeToString(tmp);
  //  m2->SerializeFromString(tmp);
 	x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

	 EXPECT_EQ( address2->GetCardID(), 99 );

     EXPECT_EQ( u2->GetSIUnit(), 6);
     EXPECT_NEAR( u2->GetUnitPerStep(), 0.44, 0.01);

     EXPECT_NEAR( m2->GetNegativeEndStop(), 1234.56, 0.01);
	 EXPECT_NEAR( m2->GetPositiveEndStop(),3456.789, 0.01);
     EXPECT_NEAR( m2->GetMaxSpeed(),11.33, 0.01);
     EXPECT_NEAR( m2->GetSpeed(),55.66, 0.01);
     EXPECT_NEAR( m2->GetMaxAccellleration(),77.88, 0.01);
     EXPECT_NEAR( m2->GetAccellleration(), 88.99, 0.01);
	 EXPECT_NEAR( m2->GetMaxCurrent(), 98.98, 0.01);
	 EXPECT_NEAR( m2->GetCurrent(), 13.13, 0.01) ;
	 EXPECT_EQ  ( m2->GetInactiveTimeout(), 333);
	 EXPECT_NEAR( m2->GetInativeCurrent(),4.5, 0.01);
	 EXPECT_NEAR( m2->GetHomeValue(),100.9, 0.01) ;
	 EXPECT_EQ( m2->GetHomeId(), "XL1-M32" );
	 EXPECT_EQ( m2->GetNegativeEndStopId(), "XL2-M33");
     EXPECT_EQ( m2->GetPositiveEndStopId(), "XL3-M34");

}

