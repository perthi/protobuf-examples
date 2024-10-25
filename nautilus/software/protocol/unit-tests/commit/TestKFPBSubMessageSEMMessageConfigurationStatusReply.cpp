// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMMessageConfigurationStatusReply.h"
#include <protocol/KFPBSubMessageSEMMessageConfigurationStatusReply.h>
#include <memory>


TestKFPBSubMessageSEMMessageConfigurationStatusReply::TestKFPBSubMessageSEMMessageConfigurationStatusReply()
{

}

TestKFPBSubMessageSEMMessageConfigurationStatusReply::~TestKFPBSubMessageSEMMessageConfigurationStatusReply()
{

}


TEST_F(TestKFPBSubMessageSEMMessageConfigurationStatusReply, serialize1  )
{
    auto m1 = std::make_shared<KFPBSubMessageSEMMessageConfigurationStatusReply>( );
    auto m2 = std::make_shared<KFPBSubMessageSEMMessageConfigurationStatusReply>( );

    m1->SetErrorCode( eSEM_CONFIGURATION_ERROR_CODE::ERROR );
    m1->SetErrorString("dolores sit amet");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);

    EXPECT_EQ( (int)m2->GetErrorCode(),  (int)eSEM_COMMAND_ERROR_CODE::ERROR );
    EXPECT_EQ( m2->GetErrorString(), "dolores sit amet");

    EXPECT_TRUE( m2->HasErrorString() );
    EXPECT_TRUE( m2->HasErrorCode() );

    m2->Reset();


    EXPECT_EQ( (int)m2->GetErrorCode(),  0 );
    EXPECT_EQ( m2->GetErrorString(), "");

    EXPECT_FALSE( m2->HasErrorString() );
    EXPECT_FALSE( m2->HasErrorCode() );

}

