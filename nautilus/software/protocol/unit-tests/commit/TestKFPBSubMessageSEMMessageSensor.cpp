// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "TestKFPBSubMessageSEMMessageSensor.h"

#include <protocol/KFPBSubMessageSEMMessageSensor.h>
#include <protocol/KFPBMessageSEMMessage.h>

#include <memory>


TestKFPBSubMessageSEMMessageSensor::TestKFPBSubMessageSEMMessageSensor()
{

}

TestKFPBSubMessageSEMMessageSensor::~TestKFPBSubMessageSEMMessageSensor()
{

}


TEST_F( TestKFPBSubMessageSEMMessageSensor, serialize1 )
{

    std::shared_ptr< KFPBMessageSEMMessage >   x1 =  std::make_shared< KFPBMessageSEMMessage   >();
    std::shared_ptr< KFPBMessageSEMMessage >   x2 =  std::make_shared< KFPBMessageSEMMessage   >();

    x1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS );

    auto   m1 = x1->GetMessageSensor();
    auto   m2 = x2->GetMessageSensor();

   // std::shared_ptr<KFPBSubMessageSEMMessageSensor> m1 = std::make_shared<KFPBSubMessageSEMMessageSensor>(  );
   // std::shared_ptr<KFPBSubMessageSEMMessageSensor> m2 = std::make_shared<KFPBSubMessageSEMMessageSensor>(  );

    m1->SetState( eSEM_SENSOR_STATE::NOT_CONFIGURED );
    m1->SetValueConverted(67.89);
    m1->SetValueRaw(77);
    m1->SetAlarmStatus(eSEM_SENSOR_ALARM_STATUS::WARNING_HIGH);
    m1->SetErrorCode( eSEM_SENSOR_ERROR_CODE::COMMUNICATION_ERROR);
    m1->SetErrorString("Lorem ipsum");

    string tmp = "";

    //m1->SerializeToString(tmp);
    //m2->SerializeFromString(tmp);

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_SENSOR_STATE::NOT_CONFIGURED );
    EXPECT_NEAR(m2->GetValueConverted(),67.89, 0.001);
    EXPECT_EQ(m2->GetValueRaw(),77);
    EXPECT_EQ( (int)m2->GetAlarmStatus(), (int)eSEM_SENSOR_ALARM_STATUS::WARNING_HIGH);
    EXPECT_EQ( (int)m2->GetErrorCode(), (int)eSEM_SENSOR_ERROR_CODE::COMMUNICATION_ERROR);
    EXPECT_EQ(m2->GetErrorString(), "Lorem ipsum");
    EXPECT_TRUE( m2->HasErrorCode() );
    EXPECT_TRUE( m2->HasErrorString());
    EXPECT_TRUE( m2->HasValueRaw());

    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ(m2->GetValueConverted(), 0);
    EXPECT_EQ(m2->GetValueRaw(), 0);
    EXPECT_EQ( (int)m2->GetAlarmStatus(), 0 );
    EXPECT_EQ( (int)m2->GetErrorCode(),  0);
    EXPECT_EQ(m2->GetErrorString(), "");
    EXPECT_FALSE( m2->HasErrorCode() );
    EXPECT_FALSE( m2->HasErrorString());
    EXPECT_FALSE( m2->HasValueRaw());
} 



TEST_F( TestKFPBSubMessageSEMMessageSensor, serialize2 )
{
    std::shared_ptr<KFPBSubMessageSEMMessageSensor> m1 = std::make_shared<KFPBSubMessageSEMMessageSensor>(  );
    std::shared_ptr<KFPBSubMessageSEMMessageSensor> m2 = std::make_shared<KFPBSubMessageSEMMessageSensor>(  );

    m1->SetState( eSEM_SENSOR_STATE::NOT_CONFIGURED );
    m1->SetValueConverted(99.99);
    m1->SetValueRaw(123);
    m1->SetAlarmStatus(eSEM_SENSOR_ALARM_STATUS::WARNING_HIGH);
   // m1->SetErrorCode( eSEM_SENSOR_ERROR_CODE::COMMUNICATION_ERROR);
   // m1->SetErrorString("Lorem ipsum");

    string tmp = "";

    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);

    EXPECT_EQ( (int)m2->GetState(), (int)eSEM_SENSOR_STATE::NOT_CONFIGURED );
    EXPECT_NEAR(m2->GetValueConverted(), 99.99, 0.001);
    EXPECT_EQ(m2->GetValueRaw(),123);
    EXPECT_EQ( (int)m2->GetAlarmStatus(), (int)eSEM_SENSOR_ALARM_STATUS::WARNING_HIGH);
    EXPECT_EQ( (int)m2->GetErrorCode(), 0 );
    EXPECT_EQ(m2->GetErrorString(), "");
    EXPECT_FALSE( m2->HasErrorCode() );
    EXPECT_FALSE( m2->HasErrorString());
    EXPECT_TRUE( m2->HasValueRaw());

    m2->Reset();

    EXPECT_EQ( (int)m2->GetState(), 0 );
    EXPECT_EQ(m2->GetValueConverted(), 0);
    EXPECT_EQ(m2->GetValueRaw(), 0);
    EXPECT_EQ( (int)m2->GetAlarmStatus(), 0);
    EXPECT_EQ( (int)m2->GetErrorCode(),  0);
    EXPECT_EQ(m2->GetErrorString(), "");
    EXPECT_FALSE( m2->HasErrorCode() );
    EXPECT_FALSE( m2->HasErrorString());
    EXPECT_FALSE( m2->HasValueRaw());
} 


