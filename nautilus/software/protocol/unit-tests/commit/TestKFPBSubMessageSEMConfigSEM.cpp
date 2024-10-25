// -*- mode: c++ -*-
#include "TestKFPBSubMessageSEMConfigSEM.h"
#include  <protocol/KFPBSubMessageSEMConfigSEM.h>

TestKFPBSubMessageSEMConfigSEM::TestKFPBSubMessageSEMConfigSEM()
{

}

TestKFPBSubMessageSEMConfigSEM::~TestKFPBSubMessageSEMConfigSEM()
{

}


/*
TEST_F( TestKFPBSubMessageSEMConfigSEM, set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMConfigSEM >();
    m->SetDummy(123);
    
    EXPECT_EQ ( m->GetDummy(), 123 );
    m->Reset();
    EXPECT_EQ ( m->GetDummy(), 0 );

}
*/



// TEST_F( TestKFPBSubMessageSEMConfigSEM , serialize )
// {
//     auto m1 = std::make_shared< KFPBSubMessageSEMConfigSEM >();
//     auto m2 = std::make_shared< KFPBSubMessageSEMConfigSEM >();

//     m1->SetDummy(4);

//     string tmp = "";

//     m1->SerializeToString(tmp);
//     m2->SerializeFromString(tmp);

//     EXPECT_EQ ( m2->GetDummy(),4 );

// }

