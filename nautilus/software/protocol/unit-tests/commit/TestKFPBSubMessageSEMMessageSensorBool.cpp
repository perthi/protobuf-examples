// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMMessageSensorBool.h"

#include <protocol/KFPBSubMessageSEMMessageSensorBool.h>



TestKFPBSubMessageSEMMessageSensorBool::TestKFPBSubMessageSEMMessageSensorBool()
{

}



TestKFPBSubMessageSEMMessageSensorBool::~TestKFPBSubMessageSEMMessageSensorBool()
{

}


TEST_F( TestKFPBSubMessageSEMMessageSensorBool, serialize1 )
{
    auto m1 = std::make_shared<KFPBSubMessageSEMMessageSensorBool>(  ); 
    auto m2 = std::make_shared<KFPBSubMessageSEMMessageSensorBool>(  ); 

    m1->SetState(eSEM_BOOL_SENSOR_STATE::ERROR);
    m1->SetValueRaw(888);
    m1->SetValueConverted(33);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
  
    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_BOOL_SENSOR_STATE::ERROR);
    EXPECT_EQ(m2->GetValueRaw(),888);
    EXPECT_EQ(m2->GetValueConverted(),33 );
    EXPECT_TRUE(m2->HasValueRaw() );

    m2->Reset();
   
    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ(m2->GetValueRaw(),0 );
    EXPECT_EQ(m2->GetValueConverted(),0 );
    EXPECT_FALSE(m2->HasValueRaw() );



}
