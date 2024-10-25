// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMCrc.h"
#include <protocol/KFPBSubMessageSEMCrc.h>

TestKFPBSubMessageSEMCrc::TestKFPBSubMessageSEMCrc()
{

}

TestKFPBSubMessageSEMCrc::~TestKFPBSubMessageSEMCrc()
{

}


TEST_F( TestKFPBSubMessageSEMCrc,  set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMCrc>();
    m->SetCrc(123);
    EXPECT_EQ( m->GetCrc(), 123 );
    m->Reset();
    EXPECT_EQ( m->GetCrc(), 0 );
}



TEST_F( TestKFPBSubMessageSEMCrc, serialize )
{
    auto m1 = std::make_shared<  KFPBSubMessageSEMCrc >();
    auto m2 = std::make_shared<  KFPBSubMessageSEMCrc  >();
    m1->SetCrc(456);
    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);

    EXPECT_EQ( m2->GetCrc(), 456 );
}
