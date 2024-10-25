// -*- mode: c++ -*-

#include "TestKFPBSubMessageSEMStepUnitConversion.h"
#include <protocol/KFPBSubMessageSEMStepUnitConversion.h>

TestKFPBSubMessageSEMStepUnitConversion::TestKFPBSubMessageSEMStepUnitConversion()
{

}

TestKFPBSubMessageSEMStepUnitConversion::~TestKFPBSubMessageSEMStepUnitConversion()
{

}


TEST_F( TestKFPBSubMessageSEMStepUnitConversion, set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMStepUnitConversion >();
   
    m->SetSIUnit(4);
    m->SetUnitPerStep((float)33.22);

    EXPECT_EQ( m->GetSIUnit(), 4 );
    EXPECT_NEAR( m->GetUnitPerStep(), 33.22, 0.01 );

    m->Reset();
  
    EXPECT_EQ( m->GetSIUnit(), 0 );
    EXPECT_NEAR( m->GetUnitPerStep(), 0, 0.01 );
}



TEST_F(TestKFPBSubMessageSEMStepUnitConversion , serialize )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMStepUnitConversion >();
    auto m2 = std::make_shared< KFPBSubMessageSEMStepUnitConversion >();
    
    m1->SetSIUnit(5);
    m1->SetUnitPerStep( (float)55.123);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);

    EXPECT_EQ(   m2->GetSIUnit(), 5 );
    EXPECT_NEAR( m2->GetUnitPerStep(), 55.123, 0.01 );
}
