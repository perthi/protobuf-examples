// -*- mode: c++ -*-


#include "TestKFPBSubMessageSEMConfigPWM.h"
#include <protocol/KFPBSubMessageSEMConfigPWM.h>
#include <protocol/KFPBSubMessageSEMLinearUnitConversion.h>

#include <protocol/KFPBMessageSEMOneOfMessage.h>


TestKFPBSubMessageSEMConfigPWM::TestKFPBSubMessageSEMConfigPWM()
{

}



TestKFPBSubMessageSEMConfigPWM::~TestKFPBSubMessageSEMConfigPWM()
{

}



TEST_F( TestKFPBSubMessageSEMConfigPWM,  set_get )
{
//    auto x = std::make_shared<KFPBMessageSEMOneOfMessage>();
 ///   auto m = x->GetPBConfig()->GetConfigPWM();

    auto m = std::make_shared< KFPBSubMessageSEMConfigPWM>();

  //  m->SetLevel((float)12.34);
    m->SetMaxLevel(100);
    m->SetMinLevel((float)-123.456);
//    m->SetSignalType(3);

    auto conversion =  m->GetConversion();
    conversion->SetMaxInput(150);
    conversion->SetMaxOutput(2000);
    conversion->SetMinInput(10);
    conversion->SetMinOutput(250);
	conversion->SetInputType(eSENSOR_INPUT_TYPE::PWM_DUTY);

  //  EXPECT_NEAR( m->GetLevel(), 12.34, 0.001);
    EXPECT_NEAR( m->GetMaxLevel(), 100, 0.001);
    EXPECT_NEAR( m->GetMinLevel(),-123.456, 0.001);
 //   EXPECT_EQ( m->GetSignalType(), 3);

    EXPECT_EQ( conversion->GetMaxInput(), 150);
    EXPECT_EQ( conversion->GetMaxOutput(), 2000);
    EXPECT_EQ( conversion->GetMinInput(), 10);
    EXPECT_EQ( conversion->GetMinOutput(), 250);

	EXPECT_EQ((int)conversion->GetInputType(), (int)eSENSOR_INPUT_TYPE::PWM_DUTY);

    m->Reset();

  //  EXPECT_NEAR( m->GetLevel(), 0, 0.001);
    EXPECT_NEAR( m->GetMaxLevel(), 0, 0.001);
    EXPECT_NEAR( m->GetMinLevel(),0, 0.001);
  //  EXPECT_EQ( m->GetSignalType(), 0);

	EXPECT_EQ(conversion->GetMaxInput(), 0 );
	EXPECT_EQ(conversion->GetMaxOutput(), 0 );
	EXPECT_EQ(conversion->GetMinInput(), 0 );
	EXPECT_EQ(conversion->GetMinOutput(), 0 );

	EXPECT_EQ((int)conversion->GetInputType(), 0);
}



TEST_F(TestKFPBSubMessageSEMConfigPWM, serialize )
{
    auto x1   =  std::make_shared<KFPBMessageSEMOneOfMessage>();
    x1->SetConfigType(  eSEM_CONFIGTYPE::PWM );

    auto x2   =  std::make_shared<KFPBMessageSEMOneOfMessage>();


    x1->SetMessageType (ePB_ONEOF_TYPE::CONFIG );
   // x1->SetConfigType( eSEM_CONFIGTYPE::PWM );
    auto m1 =  x1->GetPBConfig()->GetConfigPWM();
    auto m2 =  x2->GetPBConfig()->GetConfigPWM();
    auto conversion1 =  m1->GetConversion();
    auto conversion2 =  m2->GetConversion();


    // m1->SetLevel((float)12.34);
    // m1->SetSignalType(3);
    m1->SetMaxLevel(100);
    m1->SetMinLevel((float)-123.456);
    conversion1->SetMaxInput(150);
    conversion1->SetMaxOutput(2000);
    conversion1->SetMinInput(10);
    conversion1->SetMinOutput(250);
    conversion1->SetInputType(eSENSOR_INPUT_TYPE::PWM_RC);

    string tmp = "";
    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);


    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::CONFIG  );
    EXPECT_EQ( (int)x2->GetPBConfig()->GetConfigType(), (int )eSEM_CONFIGTYPE::PWM );

  ///  FORCE_DEBUG( "\n%s", x1->GetPBConfig()->GetConfigPWM()->str().c_str() );
  ////  FORCE_DEBUG( "\n%s", x2->GetPBConfig()->GetConfigPWM()->str().c_str() );


  //  EXPECT_NEAR(  m2->GetLevel(), 12.34, 0.001);
    EXPECT_NEAR(  m2->GetMaxLevel(), 100, 0.001);
    EXPECT_NEAR(  m2->GetMinLevel(),-123.456, 0.001);
    EXPECT_EQ( conversion2->GetMaxInput(), 150);
    EXPECT_EQ( conversion2->GetMaxOutput(), 2000);
    EXPECT_EQ( conversion2->GetMinInput(), 10);
    EXPECT_EQ( conversion2->GetMinOutput(), 250);
	EXPECT_EQ( (int)conversion2->GetInputType(), (int)eSENSOR_INPUT_TYPE::PWM_RC);


    m2->Reset();

  //  EXPECT_NEAR(  m2->GetLevel(), 0, 0.001);
    EXPECT_NEAR(  m2->GetMaxLevel(), 0, 0.001);
    EXPECT_NEAR(  m2->GetMinLevel(), 0, 0.001);
    EXPECT_EQ( conversion2->GetMaxInput(), 0);
    EXPECT_EQ( conversion2->GetMaxOutput(), 0 );
    EXPECT_EQ( conversion2->GetMinInput(), 0 );
    EXPECT_EQ( conversion2->GetMinOutput(), 0 );
	EXPECT_EQ((int)conversion2->GetInputType(), 0 );


}
