// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMMessageCommandStatusReply.h"
#include <protocol/KFPBSubMessageSEMMessageCommandStatusReply.h>
#include <protocol/KFPBMessageSEMMessage.h>

#include <memory>


TestKFPBSubMessageSEMMessageCommandStatusReply::TestKFPBSubMessageSEMMessageCommandStatusReply()
{

}

TestKFPBSubMessageSEMMessageCommandStatusReply::~TestKFPBSubMessageSEMMessageCommandStatusReply()
{

}


TEST_F(TestKFPBSubMessageSEMMessageCommandStatusReply, serialize1  )
{
    auto x1 = std::make_shared<KFPBMessageSEMMessage>( );
    auto x2 = std::make_shared<KFPBMessageSEMMessage>( );

 //   auto m1 = std::make_shared<KFPBSubMessageSEMMessageCommandStatusReply>( );
 //   auto m2 = std::make_shared<KFPBSubMessageSEMMessageCommandStatusReply>( );
    
    auto m1 = x1->GetMessageCommandStatusReply();
    auto m2 = x2->GetMessageCommandStatusReply();

    x1->SetDeviceID("L77-XX");
  ///  x1->SetSequenceID(789);
    x1->SetMessageType(ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY);
    m1->SetErrorCode( eSEM_COMMAND_ERROR_CODE::ERROR );
    m1->SetErrorString("dolores sit amet");

    string tmp = "";

  //  m1->SerializeToString(tmp);
  //  m2->SerializeFromString(tmp);
    
    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    EXPECT_EQ( x2->GetDeviceID(),"L77-XX");
 ///   EXPECT_EQ( x2->GetSequenceID(),789);
    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY );
    EXPECT_EQ( (int)m2->GetErrorCode(),  (int)eSEM_COMMAND_ERROR_CODE::ERROR );
    EXPECT_EQ( m2->GetErrorString(), "dolores sit amet");

    EXPECT_TRUE( m2->HasErrorString() );
    EXPECT_TRUE( m2->HasStatusCode() );

    x2->Reset();

    EXPECT_EQ( x2->GetDeviceID(),"");
 ////   EXPECT_EQ( x2->GetSequenceID(),0);
    EXPECT_EQ( (int)x2->GetMessageType(), 0 );

    EXPECT_EQ( (int)m2->GetErrorCode(),  0 );
    EXPECT_EQ( m2->GetErrorString(), "");

    EXPECT_FALSE( m2->HasErrorString() );
    EXPECT_FALSE( m2->HasStatusCode() );


}

