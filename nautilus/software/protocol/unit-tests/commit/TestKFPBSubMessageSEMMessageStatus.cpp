// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMMessageStatus.h"

#include <protocol/KFPBSubMessageSEMMessageStatus.h> 

#include <memory>

TestKFPBSubMessageSEMMessageStatus::TestKFPBSubMessageSEMMessageStatus()
{

}

TestKFPBSubMessageSEMMessageStatus::~TestKFPBSubMessageSEMMessageStatus()
{

}



TEST_F( TestKFPBSubMessageSEMMessageStatus, serialize1 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMMessageStatus>();
    auto m2 = std::make_shared< KFPBSubMessageSEMMessageStatus>();

    m1->SetState( eSEM_SEM_STATE::READY);
    m1->SetConfigurationCRC(123456);
    m1->SetErrorString("lorem ipsum");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
 
    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_SEM_STATE::READY);
    EXPECT_EQ( m2->GetConfigurationCRC(),123456);
    EXPECT_EQ( m2->GetErrorString(),"lorem ipsum");

    EXPECT_TRUE( m2->HasErrorString());
    EXPECT_TRUE( m2->HasErrorString());

    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ( m2->GetConfigurationCRC(), 0 );
    EXPECT_EQ( m2->GetErrorString(),"");

    EXPECT_FALSE( m2->HasErrorString());
    EXPECT_FALSE( m2->HasErrorString());
}


TEST_F( TestKFPBSubMessageSEMMessageStatus, serialize2 )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMMessageStatus>();
    auto m2 = std::make_shared< KFPBSubMessageSEMMessageStatus>();

    m1->SetState( eSEM_SEM_STATE::READY);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
 
    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_SEM_STATE::READY);

    EXPECT_FALSE( m2->HasErrorString());
    EXPECT_FALSE( m2->HasErrorString());

    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ( m2->GetConfigurationCRC(), 0 );
    EXPECT_EQ( m2->GetErrorString(),"");

    EXPECT_FALSE( m2->HasErrorString());
    EXPECT_FALSE( m2->HasErrorString());

}


