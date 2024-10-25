// -*- mode: c++ -*-

#include "TestKFPBSubMessageSEMThresholds.h"

#include <protocol/KFPBSubMessageSEMThresholds.h>

#include <memory>

TestKFPBSubMessageSEMThresholds::TestKFPBSubMessageSEMThresholds()
{

}

TestKFPBSubMessageSEMThresholds::~TestKFPBSubMessageSEMThresholds()
{

}


TEST_F( TestKFPBSubMessageSEMThresholds , set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMThresholds >();
   
    m->SetAlarmHigh(2, true);
    m->SetALarmLow(-10, true);
    m->SetWarningHigh((float)44.55, true);
    m->SetWarningLow((float)77.88, true);

    EXPECT_NEAR( m->GetAlarmHigh(), 2, 0.01);
    EXPECT_NEAR( m->GetALarmLow(),-10, 0.01);
    EXPECT_NEAR( m->GetWarningHigh(), 44.55, 0.01);
    EXPECT_NEAR( m->GetWarningLow(), 77.88, 0.01 );

    m->Reset();

    EXPECT_NEAR( m->GetAlarmHigh(), 0, 0.01);
    EXPECT_NEAR( m->GetALarmLow(), 0, 0.01);
    EXPECT_NEAR( m->GetWarningHigh(), 0, 0.01);
    EXPECT_NEAR( m->GetWarningLow(), 0, 0.01 );
}



TEST_F( TestKFPBSubMessageSEMThresholds , serialize )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMThresholds >();
    auto m2 = std::make_shared< KFPBSubMessageSEMThresholds >();

    m1->SetAlarmHigh(2, true );
    m1->SetALarmLow(-10, true );
    m1->SetWarningHigh((float)44.55, true );
    m1->SetWarningLow((float)66.77, true);
    
    string tmp = "";
    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


    EXPECT_NEAR( m2->GetAlarmHigh(), 2, 0.01);
    EXPECT_NEAR( m2->GetALarmLow(),-10, 0.01);
    EXPECT_NEAR( m2->GetWarningHigh(), 44.55, 0.01);
    EXPECT_NEAR( m2->GetWarningLow(), 66.77, 0.01 );


}
