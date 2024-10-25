// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "TestKFPBSubMessageSEMMessageSolenoid.h"

#include <protocol/KFPBSubMessageSEMMessageSolenoid.h>
#include <memory>

TestKFPBSubMessageSEMMessageSolenoid::TestKFPBSubMessageSEMMessageSolenoid()
{

}


TestKFPBSubMessageSEMMessageSolenoid::~TestKFPBSubMessageSEMMessageSolenoid()
{

}


TEST_F( TestKFPBSubMessageSEMMessageSolenoid, serialize1 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMMessageSolenoid >();
    auto m2 = std::make_shared< KFPBSubMessageSEMMessageSolenoid >();

    m1->SetState( eSEM_SOLENOID_STATE::RUNNING );
    m1->SetErrorCode( eSEM_SOLENOID_ERROR_CODE::OVER_TEMPERATURE );
    m1->SetErrorString("lorem ipsum");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_SOLENOID_STATE::RUNNING );
    EXPECT_EQ( (int)m2->GetErrorCode(), (int)eSEM_SOLENOID_ERROR_CODE::OVER_TEMPERATURE );
    EXPECT_EQ( m2->GetErrorString(),"lorem ipsum");
    EXPECT_TRUE(m2->HasErrorCode());
    EXPECT_TRUE(m2->HasErrorString());

    m2->Reset();
    
    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ( (int)m2->GetErrorCode(), 0 );
    EXPECT_EQ( m2->GetErrorString(),"");
    EXPECT_FALSE(m2->HasErrorCode());
    EXPECT_FALSE(m2->HasErrorString());

    

}


TEST_F( TestKFPBSubMessageSEMMessageSolenoid, serialize2 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMMessageSolenoid >();
    auto m2 = std::make_shared< KFPBSubMessageSEMMessageSolenoid >();

    m1->SetState( eSEM_SOLENOID_STATE::RUNNING );
  //  m1->SetErrorCode( eSEM_SOLENOID_ERROR_CODE::OVER_TEMPERATURE );
  //  m1->SetErrorString("lorem ipsum");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


    EXPECT_EQ( m2->GetState(), eSEM_SOLENOID_STATE::RUNNING );
    EXPECT_EQ( (int)m2->GetErrorCode(),  0 );
    EXPECT_EQ( m2->GetErrorString(),"");
    EXPECT_FALSE(m2->HasErrorCode());
    EXPECT_FALSE(m2->HasErrorString());
    

}




