// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "TestKFPBSubMessageSEMMessageMotor.h"

#include <protocol/KFPBSubMessageSEMMessageMotor.h>
#include <protocol/KFPBMessageSEMMessage.h>

#include <memory>

TestKFPBSubMessageSEMMessageMotor::TestKFPBSubMessageSEMMessageMotor()
{

}

TestKFPBSubMessageSEMMessageMotor::~TestKFPBSubMessageSEMMessageMotor()
{

}


TEST_F( TestKFPBSubMessageSEMMessageMotor, serailaize1)
{
    std::shared_ptr< KFPBMessageSEMMessage >   x1 =  std::make_shared< KFPBMessageSEMMessage   >();
    std::shared_ptr< KFPBMessageSEMMessage >   x2 =  std::make_shared< KFPBMessageSEMMessage   >();

    x1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS );

    auto   m1 = x1->GetMessageMotor();
    auto   m2 = x2->GetMessageMotor();

    x1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS );
    x1->SetDeviceID("L77-XX");
////    x1->SetSequenceID(789);

    m1->SetState( eSEM_MOTOR_STATE::RUNNING );
    m1->SetSpeed(  123.456 );
    m1->SetEndStopReached(true);
    m1->SetHomePositionReached(true);
    m1->SetErrorCode( eSEM_MOTOR_ERROR_CODE::OVER_CURRENT );
    m1->SetErrorString("lorem ipsum");

    string tmp = "";

  //  m1->SerializeToString(tmp);
  //  m2->SerializeFromString(tmp);
    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    EXPECT_EQ( x2->GetDeviceID(),"L77-XX");
   /// EXPECT_EQ( x2->GetSequenceID(),789);
    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS );
    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_MOTOR_STATE::RUNNING );
    EXPECT_NEAR( m2->GetSpeed(), 123.456, 0.001);
    EXPECT_TRUE(m2->IsEndStopReached() );
    EXPECT_TRUE(m2->HasEndStopReached() );
    EXPECT_TRUE(m2->IsHomePositionReached() );
    EXPECT_TRUE(m2->HasHomePositionReached() );
    EXPECT_TRUE(m2->HasErrorString() );
    EXPECT_EQ( m2->GetErrorString(), "lorem ipsum" );


    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(),  0 );
    EXPECT_NEAR( m2->GetSpeed(), 0, 0.001);
    EXPECT_FALSE(m2->IsEndStopReached() );
    EXPECT_FALSE(m2->HasEndStopReached() );
    EXPECT_FALSE(m2->IsHomePositionReached() );
    EXPECT_FALSE(m2->HasHomePositionReached() );
    EXPECT_FALSE(m2->HasErrorString() );
    EXPECT_EQ( m2->GetErrorString(), "" );

}


TEST_F( TestKFPBSubMessageSEMMessageMotor, serailaize2)
{
    std::shared_ptr<KFPBSubMessageSEMMessageMotor>   m1 =  std::make_shared< KFPBSubMessageSEMMessageMotor >();
    std::shared_ptr<KFPBSubMessageSEMMessageMotor>   m2 =  std::make_shared< KFPBSubMessageSEMMessageMotor >();

    m1->SetState( eSEM_MOTOR_STATE::RUNNING );
    m1->SetSpeed(  123.456 );
    m1->SetEndStopReached(false);
    m1->SetHomePositionReached(true);
    m1->SetErrorCode( eSEM_MOTOR_ERROR_CODE::OVER_CURRENT );
    m1->SetErrorString("dolores sit amet");

    string tmp = "";

    m1->SerializeToString(tmp);

    m2->SerializeFromString(tmp);

    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_MOTOR_STATE::RUNNING );
    EXPECT_NEAR( m2->GetSpeed(), 123.456, 0.001);
    
    EXPECT_FALSE(m2->IsEndStopReached() );
    EXPECT_TRUE(m2->HasEndStopReached() );
    
    EXPECT_TRUE(m2->IsHomePositionReached() );
    EXPECT_TRUE(m2->HasHomePositionReached() );
    EXPECT_TRUE(m2->HasErrorString() );
    EXPECT_EQ( m2->GetErrorString(), "dolores sit amet" );


    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(),  0 );
    EXPECT_NEAR( m2->GetSpeed(), 0, 0.001);
    EXPECT_FALSE(m2->IsEndStopReached() );
    EXPECT_FALSE(m2->HasEndStopReached() );
    EXPECT_FALSE(m2->IsHomePositionReached() );
    EXPECT_FALSE(m2->HasHomePositionReached() );
    EXPECT_FALSE(m2->HasErrorString() );
    EXPECT_EQ( m2->GetErrorString(), "" );

}


TEST_F( TestKFPBSubMessageSEMMessageMotor, serailaize3)
{
    std::shared_ptr<KFPBSubMessageSEMMessageMotor>   m1 =  std::make_shared< KFPBSubMessageSEMMessageMotor >();
    std::shared_ptr<KFPBSubMessageSEMMessageMotor>   m2 =  std::make_shared< KFPBSubMessageSEMMessageMotor >();

    m1->SetState( eSEM_MOTOR_STATE::RUNNING );
    m1->SetSpeed(  123.456 );
    m1->SetEndStopReached(true);
    //m1->SetHomePositionReached(false);
    m1->SetErrorCode( eSEM_MOTOR_ERROR_CODE::OVER_CURRENT );
    m1->SetErrorString("Lorem ipsum dolor sit amet, consectetur adipiscing elit,\
     sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
     Ut enim ad minim veniam, quis nostruddolores sit amet");

    string tmp = "";

    m1->SerializeToString(tmp);

    m2->SerializeFromString(tmp);

    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_MOTOR_STATE::RUNNING );
    EXPECT_NEAR( m2->GetSpeed(), 123.456, 0.001);
    EXPECT_TRUE(m2->IsEndStopReached() );
    EXPECT_TRUE(m2->HasEndStopReached() );
  //  EXPECT_FALSE(m2->IsHomePositionReached() );
    EXPECT_FALSE(m2->HasHomePositionReached() );
    EXPECT_TRUE(m2->HasErrorString() );
    EXPECT_EQ( m2->GetErrorString(), "Lorem ipsum dolor sit amet, co" );


    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(),  0 );
    EXPECT_NEAR( m2->GetSpeed(), 0, 0.001);
    EXPECT_FALSE(m2->IsEndStopReached() );
    EXPECT_FALSE(m2->HasEndStopReached() );
    EXPECT_FALSE(m2->IsHomePositionReached() );
    EXPECT_FALSE(m2->HasHomePositionReached() );
    EXPECT_FALSE(m2->HasErrorString() );
    EXPECT_EQ( m2->GetErrorString(), "" );

}
