// -*- mode: c++ -*-
#include "TestKFPBSubMessageSEMConfigVirtualXYMotors.h"

#include <protocol/KFPBSubMessageSEMConfigVirtualXYMotors.h>


TestKFPBSubMessageSEMConfigVirtualXYMotors::TestKFPBSubMessageSEMConfigVirtualXYMotors()
{

}

TestKFPBSubMessageSEMConfigVirtualXYMotors::~TestKFPBSubMessageSEMConfigVirtualXYMotors()
{

}



TEST_F( TestKFPBSubMessageSEMConfigVirtualXYMotors, set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMConfigVirtualXYMotors  >();
   
    m->SetDeviceX("L4-M88");
    m->SetDeviceY("L6-M33");

    EXPECT_EQ( m->GetDeviceX(), "L4-M88" );
    EXPECT_EQ( m->GetDeviceY(), "L6-M33" );

    m->Reset();
    

    EXPECT_EQ( m->GetDeviceX(), "" );
    EXPECT_EQ( m->GetDeviceY(), "" );


}


TEST_F(TestKFPBSubMessageSEMConfigVirtualXYMotors , serialize )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMConfigVirtualXYMotors >();
    auto m2 = std::make_shared< KFPBSubMessageSEMConfigVirtualXYMotors >();

     
    m1->SetDeviceX("L44-M88X");
    m1->SetDeviceY("L66-M33X");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);
  
    EXPECT_EQ( m2->GetDeviceX(), "L44-M88X" );
    EXPECT_EQ( m2->GetDeviceY(), "L66-M33X" );

    m2->Reset();

    EXPECT_EQ( m2->GetDeviceX(), "" );
    EXPECT_EQ( m2->GetDeviceY(), "" );


}
