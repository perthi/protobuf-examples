// -*- mode: c++ -*-

#include "TestKFPBSubMessageSEMConfigSolenoid.h"
#include <protocol/KFPBSubMessageSEMConfigSolenoid.h>

TestKFPBSubMessageSEMConfigSolenoid::TestKFPBSubMessageSEMConfigSolenoid()
{

}

TestKFPBSubMessageSEMConfigSolenoid::~TestKFPBSubMessageSEMConfigSolenoid()
{

}


TEST_F(  TestKFPBSubMessageSEMConfigSolenoid , set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMConfigSolenoid >();
   
    m->SetActivateCurrent((float)12.34);
    m->SetHoldCurrent((float)555.777);
    m->SetMaxCurrent((float)999.888);

    EXPECT_NEAR(m->GetActivateCurrent(), 12.34, 0.01);
    EXPECT_NEAR(m->GetHoldCurrent(), 555.777, 0.01);
    EXPECT_NEAR(m->GetMaxCurrent(), 999.888, 0.01);

    m->Reset();
  
    EXPECT_NEAR(m->GetActivateCurrent(), 0, 0.01);
    EXPECT_NEAR(m->GetHoldCurrent(), 0, 0.01);
    EXPECT_NEAR(m->GetMaxCurrent(), 0, 0.01);

}



TEST_F( TestKFPBSubMessageSEMConfigSolenoid, serialize )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMConfigSolenoid >();
    auto m2 = std::make_shared< KFPBSubMessageSEMConfigSolenoid >();
    
    m1->SetActivateCurrent((float)12.34);
    m1->SetHoldCurrent((float)555.777);
    m1->SetMaxCurrent((float)999.888);
    
    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
    
    EXPECT_NEAR(m2->GetActivateCurrent(), 12.34, 0.01);
    EXPECT_NEAR(m2->GetHoldCurrent(), 555.777, 0.01);
    EXPECT_NEAR(m2->GetMaxCurrent(), 999.888, 0.01);

}
