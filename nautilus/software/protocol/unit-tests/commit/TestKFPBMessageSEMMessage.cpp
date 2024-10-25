// -*- mode: c++ -*-


#include "TestKFPBMessageSEMMessage.h"
#include <protocol/KFPBMessageSEMMessage.h>
#include <protocol/KFProtocolEnums.h>
#include <protocol/KFPBMessageSEMOneOfMessage.h>
#include <memory>


TestKFPBMessageSEMMessage::TestKFPBMessageSEMMessage()
{


} 


TestKFPBMessageSEMMessage::~TestKFPBMessageSEMMessage()
{

} 


void
TestKFPBMessageSEMMessage::SetUp()
{
    fMessage = new KFPBMessageSEMMessage();
}


void
TestKFPBMessageSEMMessage::TearDown()
{
    delete fMessage;

}    



TEST_F( TestKFPBMessageSEMMessage , serialization_sensor_status )
{
    try
    {
        auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
        auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();
        auto m1 = x1->GetPBMessage();
        auto m2 = x2->GetPBMessage();

        x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);

        m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS );
        auto sensor1 = m1->GetMessageSensor();
        auto sensor2 = m2->GetMessageSensor();

        sensor1->SetAlarmStatus( eSEM_SENSOR_ALARM_STATUS::ALARM_HIGH );
        sensor1->SetErrorCode( eSEM_SENSOR_ERROR_CODE::COMMUNICATION_ERROR );
        sensor1->SetState( eSEM_SENSOR_STATE::RUNNING );
        sensor1->SetErrorString("oledoleodff donald duck");
        sensor1->SetValueConverted(678.987);
        sensor1->SetValueRaw(666);
      ///  m1->SetSequenceID(111);
        m1->SetDeviceID("S33");

        string tmp = "";
        x1->SerializeToString(tmp);;
        x2->SerializeFromString(tmp);


        EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::MESSAGE) ;
        EXPECT_EQ( (int)sensor1->GetAlarmStatus(), (int)eSEM_SENSOR_ALARM_STATUS::ALARM_HIGH );
        EXPECT_EQ( (int)sensor1->GetErrorCode(), (int)eSEM_SENSOR_ERROR_CODE::COMMUNICATION_ERROR );
        EXPECT_EQ( (int)sensor1->GetState(), (int)eSEM_SENSOR_STATE::RUNNING );
        EXPECT_EQ( sensor1->GetErrorString(),"oledoleodff donald duck");
        EXPECT_NEAR( sensor1->GetValueConverted(),678.987, 0.001);
        EXPECT_EQ( sensor1->GetValueRaw(),666);
      ///  EXPECT_EQ( m2->GetSequenceID(),111);
        EXPECT_EQ( m2->GetDeviceID(),"S33");

        x2->Reset();
    
        EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::UNKNOWN );
        EXPECT_EQ( (int)sensor2->GetAlarmStatus(), 0 );
        EXPECT_EQ( (int)sensor2->GetErrorCode(), 0 );
        EXPECT_EQ( (int)sensor2->GetState(), 0 );
        EXPECT_EQ( sensor2->GetErrorString(),"");
        EXPECT_NEAR( sensor2->GetValueConverted(),0, 0.001 );
        EXPECT_EQ( sensor2->GetValueRaw(),0 );
    //    EXPECT_EQ( m2->GetSequenceID(),0);
        EXPECT_EQ( m2->GetDeviceID(),"");
    
    
    }
    catch(const std::exception& e)
    {
        CERR << e.what() << '\n';
        throw(3);
    }
    catch( GException &e )
    {
        CERR << e.what() << endl;
        throw(e);
    }

}




TEST_F( TestKFPBMessageSEMMessage , serialization_motor_status )
{
    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto m1 = x1->GetPBMessage();
    auto m2 = x2->GetPBMessage();
    x1->SetSequenceID(222);
    x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS );
    
    auto motor1 = m1->GetMessageMotor();
    auto motor2 = m2->GetMessageMotor();https://se-got-jira01.semcon.se/jira/browse/KFR-698
    
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS );
  //  m1->SetSequenceID(111);
    motor1->SetEndStopReached(true);
    motor1->SetHomePositionReached(true);
    motor1->SetErrorCode( eSEM_MOTOR_ERROR_CODE::SHORT_CIRCUIT );
    motor1->SetSpeed(55.66);
    motor1->SetState( eSEM_MOTOR_STATE::ABORTING );
    motor1->SetPosition(88.99);
    motor1->SetErrorString("hello dolly");
    string tmp = "";
    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);
    EXPECT_EQ( x2->GetMessageType(),ePB_ONEOF_TYPE::MESSAGE);
    EXPECT_EQ( m2->GetMessageType(), ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS );
    EXPECT_EQ( x2->GetSequenceID(),222);
 ///   EXPECT_EQ( m2->GetSequenceID(),111);
    EXPECT_EQ( motor2->IsEndStopReached(),true);
    EXPECT_EQ( motor2->IsHomePositionReached(),true);
    
    EXPECT_EQ( (int)motor2->GetErrorCode(), (int)eSEM_MOTOR_ERROR_CODE::SHORT_CIRCUIT );
    
    EXPECT_NEAR( motor2->GetSpeed(),55.66, 0.001);
    EXPECT_EQ( (int)motor2->GetState(), (int)eSEM_MOTOR_STATE::ABORTING );
    EXPECT_NEAR( motor2->GetPosition(),88.99, 0.001);
    EXPECT_EQ( motor2->GetErrorString(),"hello dolly");
    
    x2->Reset();
    EXPECT_EQ( (int)x2->GetMessageType(),(int)ePB_ONEOF_TYPE::UNKNOWN);
    EXPECT_EQ( (int)m2->GetMessageType(), 0 );
    EXPECT_EQ( x2->GetSequenceID(),0);
///    EXPECT_EQ( m2->GetSequenceID(),0);
    EXPECT_EQ( motor2->IsEndStopReached(),false);
    EXPECT_EQ( motor2->IsHomePositionReached(), false);
    EXPECT_EQ( (int)motor2->GetErrorCode(), 0 );
    EXPECT_NEAR( motor2->GetSpeed(), 0, 0.001);
    EXPECT_EQ( (int)motor2->GetState(), 0 );
    EXPECT_NEAR( motor2->GetPosition(), 0, 0.001);
    EXPECT_EQ( motor2->GetErrorString(),"");
}



TEST_F( TestKFPBMessageSEMMessage , serialization_cmd_status )
{
    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();

    auto m1 = x1->GetPBMessage();
    auto m2 = x2->GetPBMessage();
    auto status1 = m1->GetMessageCommandStatusReply();
    auto status2 = m2->GetMessageCommandStatusReply();

    x1->SetSequenceID(222);
    x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY );
    m1->SetDeviceID("CXX");

    status1->SetErrorCode( eSEM_COMMAND_ERROR_CODE::NO_ERROR );
    
    status1->SetErrorString("No errors");

    string tmp = "";

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);
    EXPECT_EQ( m2->GetDeviceID(), "CXX");
    EXPECT_EQ(x2->GetSequenceID(),222);
    EXPECT_EQ( (int)x2->GetMessageType(),(int)ePB_ONEOF_TYPE::MESSAGE);
    EXPECT_EQ( (int)m2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY );
    EXPECT_EQ( (int)status2->GetErrorCode(),(int)eSEM_COMMAND_ERROR_CODE::NO_ERROR );
  ///  EXPECT_EQ(status2->GetSequenceID(),123);
    EXPECT_EQ(status2->GetErrorString(),"No errors");

    x2->Reset();

    EXPECT_EQ(x2->GetSequenceID(), 0 );
    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::UNKNOWN );
    EXPECT_EQ( (int)m2->GetMessageType(),    0 );
    EXPECT_EQ( (int)status2->GetErrorCode(),0 );
  ///  EXPECT_EQ(status2->GetSequenceID(),0);
    EXPECT_EQ(status2->GetErrorString(),"");
}



TEST_F( TestKFPBMessageSEMMessage , serialization_config_status )
{
  auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto m1 = x1->GetPBMessage();
    auto m2 = x2->GetPBMessage();
    auto status1 = m1->GetMessageConfigurationStatusReply();
    auto status2 = m2->GetMessageConfigurationStatusReply();

    x1->SetSequenceID(222);
    x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY );
    m1->SetDeviceID("CXX");

    status1->SetErrorCode( eSEM_CONFIGURATION_ERROR_CODE::NO_ERROR );
  ///  status1->SetSequenceID(123);
    status1->SetErrorString("No errors");

    string tmp = "";

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);
    EXPECT_EQ( m2->GetDeviceID(), "CXX");
    EXPECT_EQ(x2->GetSequenceID(),222);
    EXPECT_EQ( (int)x2->GetMessageType(),(int)ePB_ONEOF_TYPE::MESSAGE);
    EXPECT_EQ( (int)m2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY );
    EXPECT_EQ( (int)status2->GetErrorCode(),(int)eSEM_COMMAND_ERROR_CODE::NO_ERROR );
  ////  EXPECT_EQ(status2->GetSequenceID(),123);
    EXPECT_EQ(status2->GetErrorString(),"No errors");

    x2->Reset();

    EXPECT_EQ(x2->GetSequenceID(), 0 );
    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::UNKNOWN  );
    EXPECT_EQ( (int)m2->GetMessageType(),    0 );
    EXPECT_EQ( (int)status2->GetErrorCode(),0 );
  ///  EXPECT_EQ(status2->GetSequenceID(),0);
    EXPECT_EQ(status2->GetErrorString(),"");

}


TEST_F( TestKFPBMessageSEMMessage , serialization_sensor_bool_status )
{
    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto m1 = x1->GetPBMessage();
    auto m2 = x2->GetPBMessage();
    auto sensor1 = m1->GetMessageSensorBool();
    auto sensor2 = m2->GetMessageSensorBool();

    x1->SetSequenceID(222);
    x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS );
    m1->SetDeviceID("MOTOR_10A");
 ///   m1->SetSequenceID(888);
    sensor1->SetState(eSEM_BOOL_SENSOR_STATE::RUNNING);
    sensor1->SetValueConverted(234);
    sensor1->SetValueRaw(99);
    
    string tmp = "";

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);
  
    
    EXPECT_EQ( x2->GetSequenceID(),222) ;
    EXPECT_EQ( (int)x2->GetMessageType(),(int)ePB_ONEOF_TYPE::MESSAGE) ;
    EXPECT_EQ( (int)m2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS ) ;
    EXPECT_EQ( m2->GetDeviceID(),"MOTOR_10A") ;
  ///  EXPECT_EQ( m2->GetSequenceID(),888) ;
    EXPECT_EQ( (int)sensor2->GetState(), (int)eSEM_BOOL_SENSOR_STATE::RUNNING) ;
    EXPECT_EQ( sensor2->GetValueConverted(),234 ) ;
    EXPECT_EQ( sensor2->GetValueRaw(),99) ;


    x2->Reset();

    EXPECT_EQ( x2->GetSequenceID(),0) ;
    EXPECT_EQ( (int)x2->GetMessageType(),(int)ePB_ONEOF_TYPE::UNKNOWN) ;
    EXPECT_EQ( (int)m2->GetMessageType(),  0) ;
    EXPECT_EQ( m2->GetDeviceID(),"") ;
  ////  EXPECT_EQ( m2->GetSequenceID(), 0 ) ;
    EXPECT_EQ( (int)sensor2->GetState(), 0) ;
    EXPECT_NEAR( sensor2->GetValueConverted(),0, 0.001) ;
    EXPECT_EQ( sensor2->GetValueRaw(),0) ;
    

}



TEST_F( TestKFPBMessageSEMMessage , serialization_solenoid_status )
{
    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto m1 = x1->GetPBMessage();
    auto m2 = x2->GetPBMessage();
    auto sol1 = m1->GetMessageSolenoid();
    auto sol2 = m2->GetMessageSolenoid();

    x1->SetSequenceID(222);
    x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS );
    m1->SetDeviceID("SOL");
  ////  m1->SetSequenceID(444);
    sol1->SetErrorCode(eSEM_SOLENOID_ERROR_CODE::SHORT_CIRCUIT);
    sol1->SetState( eSEM_SOLENOID_STATE::RUNNING);
    sol1->SetErrorString("Short circuit");

    string tmp = "";

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);
   
    EXPECT_EQ(x2->GetSequenceID(),222);
    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::MESSAGE);
    EXPECT_EQ( (int)m2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS );
    EXPECT_EQ(m2->GetDeviceID(),"SOL");
  ///  EXPECT_EQ(m2->GetSequenceID(),444);
    EXPECT_EQ( (int)sol2->GetErrorCode(), (int)eSEM_SOLENOID_ERROR_CODE::SHORT_CIRCUIT);
    EXPECT_EQ( (int)sol2->GetState(), (int)eSEM_SOLENOID_STATE::RUNNING);
    EXPECT_EQ(sol2->GetErrorString(),"Short circuit");

    x2->Reset();


    EXPECT_EQ(x2->GetSequenceID(),0 );
    EXPECT_EQ( (int)x2->GetMessageType(), (int)ePB_ONEOF_TYPE::UNKNOWN);
    EXPECT_EQ( (int)m2->GetMessageType(),   0 );
    EXPECT_EQ(m2->GetDeviceID(),"");
  ///  EXPECT_EQ(m2->GetSequenceID(),0);
    EXPECT_EQ( (int)sol2->GetErrorCode(), 0);
    EXPECT_EQ( (int)sol2->GetState(),     0);
    EXPECT_EQ(sol2->GetErrorString(),"");

}



TEST_F( TestKFPBMessageSEMMessage , serialization_xy_motor_status )
{
    auto x1 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 = std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto m1 = x1->GetPBMessage();
    auto m2 = x2->GetPBMessage();
    auto motor1 = m1->GetMMessageXYMotor();
    auto motor2 = m2->GetMMessageXYMotor();

    x1->SetSequenceID(222);
    x1->SetMessageType(ePB_ONEOF_TYPE::MESSAGE);
    m1->SetMessageType( ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS );
    m1->SetDeviceID("VXY-747");
    motor1->SetErrorCode( eSEM_XY_MOTOR_ERROR_CODE::FOLLOW_ERROR );
    motor1->SetState( eSEM_XY_MOTOR_STATE::STOPPING );
    motor1->SetXYPosition(12.34, 56.78);
    motor1->SetErrorString("LOREM IPSUM");
   
    string tmp = "";

    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    EXPECT_EQ( x2->GetSequenceID(),222) ;
    EXPECT_EQ( (int)x2->GetMessageType(),(int)ePB_ONEOF_TYPE::MESSAGE) ;
    EXPECT_EQ( (int)m2->GetMessageType(), (int)ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS ) ;
    EXPECT_EQ( m2->GetDeviceID(),"VXY-747") ;
    EXPECT_EQ( (int)motor2->GetErrorCode(), (int)eSEM_XY_MOTOR_ERROR_CODE::FOLLOW_ERROR ) ;
    EXPECT_EQ( (int)motor2->GetState(), (int)eSEM_XY_MOTOR_STATE::STOPPING ) ;
    float X = 0, Y = 0;
    motor2->GetXYPosition( X, Y);
    EXPECT_NEAR( X, 12.34, 0.001 ) ;
    EXPECT_NEAR( Y, 56.78, 0.001) ;
    EXPECT_EQ( motor2->GetErrorString(),"LOREM IPSUM") ;

    x2->Reset();

    EXPECT_EQ( x2->GetSequenceID(), 0 );
    EXPECT_EQ( x2->GetMessageType(),ePB_ONEOF_TYPE::UNKNOWN) ;
    EXPECT_EQ( (int)m2->GetMessageType(), 0 ) ;
    EXPECT_EQ( m2->GetDeviceID(),"") ;
    EXPECT_EQ( (int)motor2->GetErrorCode(), 0 ) ;
    EXPECT_EQ( (int)motor2->GetState(), 0 ) ;
    X = 0;
    Y = 0;
    motor2->GetXYPosition( X, Y);
    EXPECT_NEAR( X, 0, 0.001 ) ;
    EXPECT_NEAR( Y, 0, 0.001) ;
    EXPECT_EQ( motor2->GetErrorString(),"") ;

}


