// -*- mode: c++ -*-

#include "TestKFPBSubMessageSEMDeviceAddress.h"
#include <protocol/KFPBSubMessageSEMDeviceAddress.h>


TestKFPBSubMessageSEMDeviceAddress::TestKFPBSubMessageSEMDeviceAddress()
{

}

TestKFPBSubMessageSEMDeviceAddress::~TestKFPBSubMessageSEMDeviceAddress()
{


}


TEST_F( TestKFPBSubMessageSEMDeviceAddress, set_get )
{
    auto m = std::make_shared< KFPBSubMessageSEMDeviceAddress>();
    m->SetCardID(3);
    m->SetDeviceID("LXV333");
    m->SetDeviceName("Power IO");
    m->SetDeviceType( (eDEVICE_TYPE)42);
    m->SetDevicePortNo(4);

    EXPECT_EQ( m->GetCardID(), 3 );
    EXPECT_EQ ( m->GetDeviceID(), "LXV333" );
    EXPECT_EQ ( m->GetDeviceName(), "Power IO" );
    EXPECT_EQ( (int)m->GetDeviceType(), 42 );
    EXPECT_EQ( m->GetDevicePortNo(),4 );

    m->Reset();
  
    EXPECT_EQ( m->GetCardID(), 0 );
    EXPECT_EQ ( m->GetDeviceID(), "" );
    EXPECT_EQ ( m->GetDeviceName(), "" );
    EXPECT_EQ( (int)m->GetDeviceType(), 0 );
    EXPECT_EQ( m->GetDevicePortNo(), 0 );

}



TEST_F( TestKFPBSubMessageSEMDeviceAddress, serialize )
{
    auto m1 = std::make_shared< KFPBSubMessageSEMDeviceAddress>();
    auto m2 = std::make_shared< KFPBSubMessageSEMDeviceAddress>();

    m1->SetCardID(3);
    m1->SetDeviceID("LXVABC");
    m1->SetDeviceName("Solenoid");
    m1->SetDeviceType( (eDEVICE_TYPE)33);
    m1->SetDevicePortNo(5);

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);


    EXPECT_EQ( m2->GetCardID(), 3 );
    EXPECT_EQ ( m2->GetDeviceID(), "LXVABC" );
    EXPECT_EQ ( m2->GetDeviceName(), "Solenoid" );
    EXPECT_EQ( (int)m2->GetDeviceType(), 33 );
    EXPECT_EQ( m2->GetDevicePortNo(),5 );

}


