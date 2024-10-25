// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "TestKFPBSubMessageSEMMessageXYMotor.h"

#include <protocol/KFPBSubMessageSEMMessageXYMotor.h>
#include <memory>

TestKFPBSubMessageSEMMessageXYMotor::TestKFPBSubMessageSEMMessageXYMotor()
{

}


TestKFPBSubMessageSEMMessageXYMotor::~TestKFPBSubMessageSEMMessageXYMotor()
{

}


TEST_F( TestKFPBSubMessageSEMMessageXYMotor, serialize1 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMMessageXYMotor >();
    auto m2 = std::make_shared< KFPBSubMessageSEMMessageXYMotor >();

    m1->SetState( eSEM_XY_MOTOR_STATE::RUNNING );
    m1->SetErrorCode( eSEM_XY_MOTOR_ERROR_CODE::FOLLOW_ERROR );
    m1->SetErrorString("lorem ipsum");

    m1->SetXYPosition(12.34, 56.78);


    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_XY_MOTOR_STATE::RUNNING );
    EXPECT_EQ( (int)m2->GetErrorCode(), (int)eSEM_XY_MOTOR_ERROR_CODE::FOLLOW_ERROR);
    EXPECT_EQ( m2->GetErrorString(),"lorem ipsum");
    EXPECT_TRUE(m2->HasErrorCode());
    EXPECT_TRUE(m2->HasErrorString());

    float x = 0, y = 0;
    m2->GetXYPosition(x, y);
    EXPECT_NEAR(x, 12.34, 0.001);
    EXPECT_NEAR(y, 56.78, 0.001);

    m2->Reset();
    
    m2->GetXYPosition(x, y);
    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ( (int)m2->GetErrorCode(), 0 );
    EXPECT_EQ( m2->GetErrorString(),"");
    EXPECT_FALSE(m2->HasErrorCode());
    EXPECT_FALSE(m2->HasErrorString());
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 0);

    

}


TEST_F( TestKFPBSubMessageSEMMessageXYMotor, serialize2 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMMessageXYMotor >();
    auto m2 = std::make_shared< KFPBSubMessageSEMMessageXYMotor >();

    m1->SetState( eSEM_XY_MOTOR_STATE::RUNNING );
  //  m1->SetErrorCode( eSEM_XY_MOTOR_ERROR_CODE::OVER_TEMPERATURE );
  //  m1->SetErrorString("lorem ipsum");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


    EXPECT_EQ( m2->GetState(), eSEM_XY_MOTOR_STATE::RUNNING );
    EXPECT_EQ( (int)m2->GetErrorCode(),  0 );
    EXPECT_EQ( m2->GetErrorString(),"");
    EXPECT_FALSE(m2->HasErrorCode());
    EXPECT_FALSE(m2->HasErrorString());
    

}




