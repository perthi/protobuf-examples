// -*- mode: c++ -*-


#include "TestKFPBMessageSEMCommand.h"
#include <protocol/KFPBMessageSEMCommand.h>
#include <protocol/KFProtocolEnums.h>
#include <protocol/KFPBMessageSEMOneOfMessage.h>

#include <memory>


TestKFPBMessageSEMCommand::TestKFPBMessageSEMCommand()
{

} 

TestKFPBMessageSEMCommand::~TestKFPBMessageSEMCommand()
{

}


void
 TestKFPBMessageSEMCommand::SetUp()
{
    fMessage = new KFPBMessageSEMCommand();
}



void
 TestKFPBMessageSEMCommand::TearDown()
{
    delete fMessage;

}    

 

TEST_F( TestKFPBMessageSEMCommand, set_device_id )
{
    auto m1 = std::make_shared<KFPBMessageSEMCommand>(); 
    auto m2 = std::make_shared<KFPBMessageSEMCommand>(); 

    m1->SetDeviceID("ABC");
    EXPECT_EQ( m1->GetDeviceID(), "ABC" );
 
    string tmp = "";    
    m1->SerializeToString(tmp);
    m2->SerializeFromString(tmp);

    EXPECT_EQ( m2->GetDeviceID(), "ABC" );
 
}



TEST_F( TestKFPBMessageSEMCommand, set_cmd )
{
    
    vector<eSEM_COMMAND_ID>  cmds = {  eSEM_COMMAND_ID::MOTOR_XY_START_CONTINUOUS_TRANSLATION,
                                    eSEM_COMMAND_ID::MOTOR_XY_STOP_CONTINUOUS_TRANSLATION,   
                                    eSEM_COMMAND_ID::MOTOR_XY_START_CONTINUOUS_ROTATION,
                                    eSEM_COMMAND_ID::MOTOR_XY_STOP_CONTINUOUS_ROTATION ,      
                                    eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_HARD,
                                    eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_SOFT,
                                    eSEM_COMMAND_ID::GO_HOME,
                                    eSEM_COMMAND_ID::CALIBRATE_HOME,
                                    eSEM_COMMAND_ID::SOLENOID_ACTIVATE,
                                    eSEM_COMMAND_ID::SOLENOID_DE_ACTIVATE,
                                    eSEM_COMMAND_ID::REQUEST_SENSOR_VALUE,
                                    eSEM_COMMAND_ID::REQUEST_MOTOR_POSITION,    
                                    eSEM_COMMAND_ID::REQUEST_STATE,
                                    eSEM_COMMAND_ID::REQUEST_FW_VERSION};


    for(size_t i=0; i < cmds.size(); i++ )
    {
       auto x1 =  std::make_shared<KFPBMessageSEMOneOfMessage>();
       auto x2 =  std::make_shared<KFPBMessageSEMOneOfMessage>();
       x1->SetMessageType( ePB_ONEOF_TYPE::COMMAND );
       auto m1 = x1->GetPBCommand(); 
       auto m2 = x2->GetPBCommand(); 
       m1->SetFields("ABC", cmds.at(i));
       string tmp = "";    
       x1->SerializeToString(tmp);
       x2->SerializeFromString(tmp);
       EXPECT_EQ( m2->GetDeviceID(), "ABC" );
       ASSERT_NE( m2, nullptr ) << "M2 is a ZERO pointer" ;
       EXPECT_EQ( (int)m2->GetCommandID(), (int)cmds.at(i));
    }
}




TEST_F( TestKFPBMessageSEMCommand, set_val )
{
    vector<eSEM_COMMAND_ID>  cmds = {  eSEM_COMMAND_ID::MOTOR_XY_SET_SPEED_ROTATION,
                                    eSEM_COMMAND_ID::MOTOR_STEPPER_SET_ACCELERATION,   
                                    eSEM_COMMAND_ID::MOTOR_STEPPER_SET_CURRENT,
                                    eSEM_COMMAND_ID::PWM_SET };     

    for(size_t i=0; i < cmds.size(); i++ )
    {
        {
            auto x1 =  std::make_shared<KFPBMessageSEMOneOfMessage>();
            x1->SetMessageType( ePB_ONEOF_TYPE::COMMAND );
            auto x2 =  std::make_shared<KFPBMessageSEMOneOfMessage>();
            auto m1 = x1->GetPBCommand();
            auto m2 = x2->GetPBCommand();
            int val = 1 + 3*i;
            m1->SetFieldsFloat("ABC", cmds.at(i), val);
            string tmp = "";    
            x1->SerializeToString(tmp);
            x2->SerializeFromString(tmp);
            EXPECT_EQ( x2->GetMessageType(), ePB_ONEOF_TYPE::COMMAND );    
            EXPECT_EQ( m2->GetDeviceID(), "ABC" );
            EXPECT_EQ( m2->GetValue(), val );
            EXPECT_EQ( (int)m2->GetCommandID(), (int)cmds.at(i));
        }
    }
}



TEST_F( TestKFPBMessageSEMCommand, set_val_xy_1 )
{
    vector<eSEM_COMMAND_ID>  cmds = {  eSEM_COMMAND_ID::MOTOR_XY_SET_POSITION,
                                    eSEM_COMMAND_ID::MOTOR_XY_INCREMENT_POSITION,   
                                    eSEM_COMMAND_ID::DEBUG1,
                                    eSEM_COMMAND_ID::DEBUG2 };     

    for(size_t i=0; i < cmds.size(); i++ )
    {
        {
            auto x1 =  std::make_shared<KFPBMessageSEMOneOfMessage>();
            x1->SetMessageType( ePB_ONEOF_TYPE::COMMAND);
            x1->GetPBCommand()->SetPayloadType(  eSEM_COMMAND_PAYLOAD_TYPE::XY  );
              
            auto x2 =  std::make_shared<KFPBMessageSEMOneOfMessage>();

            auto m1 = x1->GetPBCommand();
            auto m2 = x2->GetPBCommand();

            int valx = 1 + 3*i;
            int valy = 3.3*valx; 

            //m1->SetFieldsXY("ABC", cmds.at(i), valx, valy);
            m1->SetFieldsXY("ABC", cmds.at(i), valx, valy);

            string tmp = "";    
            
            x1->SerializeToString(tmp);
            x2->SerializeFromString(tmp);

           // EXPECT_EQ( x2->GetMessageType(), ePB_ONEOF_TYPE::MESSAGE );     
            EXPECT_EQ( m2->GetDeviceID(), "ABC" );
            EXPECT_EQ( m2->GetValueX(), valx );
            EXPECT_EQ( m2->GetValueY(), valy );
            EXPECT_EQ( (int)m2->GetCommandID(), (int)cmds.at(i));
        }
    }
}



TEST_F( TestKFPBMessageSEMCommand, set_val_xy_2 )
{
    auto x1 =  std::make_shared<KFPBMessageSEMOneOfMessage>();
    auto x2 =  std::make_shared<KFPBMessageSEMOneOfMessage>();

    x1->SetMessageType( ePB_ONEOF_TYPE::COMMAND);
    x1->GetPBCommand()->SetPayloadType(  eSEM_COMMAND_PAYLOAD_TYPE::XY );

    auto m1 = x1->GetPBCommand();
    auto m2 = x2->GetPBCommand();

    m1->SetFieldsXY("ABC",   eSEM_COMMAND_ID::MOTOR_XY_SET_POSITION, 22, 33 );
   
    string tmp = "";    
    x1->SerializeToString(tmp);
    x2->SerializeFromString(tmp);

    EXPECT_EQ( x2->GetMessageType(), ePB_ONEOF_TYPE::COMMAND );     

    EXPECT_EQ( m2->GetDeviceID(), "ABC" );
    
    EXPECT_NEAR( m2->GetValueX(), 22, 0.001 );
    EXPECT_NEAR( m2->GetValueY(), 33, 0.001 );
    EXPECT_EQ( (int)m2->GetCommandID(),   (int)eSEM_COMMAND_ID::MOTOR_XY_SET_POSITION );

}



TEST_F( TestKFPBMessageSEMCommand, set_raw )
{
    SEMOneOfMessage m1 = SEMOneOfMessage_init_default;
    SEMOneOfMessage m2 = SEMOneOfMessage_init_default; 

    m1.which_payload = SEMOneOfMessage_sem_command_tag;
    m1.payload.sem_command.which_payload = SEMCommand_xy_tag;

    m1.payload.sem_command.cmd_id = 4;
  //  m1.payload.sem_command.has_sequence_id = true;
  //  m1.payload.sem_command.sequence_id = 100; 
    sprintf( m1.payload.sem_command.device_id, "ABC" );

    m1.payload.sem_command.payload.xy.x = 22;
    m1.payload.sem_command.payload.xy.y = 33;

    uint8_t buffer[256] = {0};

    pb_ostream_t stream = pb_ostream_from_buffer( buffer,  sizeof(buffer)  );
  
    bool status = pb_encode(&stream,  SEMOneOfMessage_fields, &m1 );
    size_t message_length = stream.bytes_written;

    EXPECT_TRUE(status);
    if( status == false )
    {
        FORCE_DEBUG("Decoding failed: %s\n", PB_GET_ERROR(&stream) );
    }

    pb_istream_t stream2 = pb_istream_from_buffer( buffer,  sizeof(buffer) );
    bool status2 = pb_decode(&stream2, SEMOneOfMessage_fields, &m2 );
    
    EXPECT_TRUE(status2);
  
    if( status2 == false )
    {
        FORCE_DEBUG("Decoding failed: %s\n", PB_GET_ERROR(&stream2) );
    }

    EXPECT_EQ( m2.payload.sem_command.cmd_id, 4);
 //   EXPECT_EQ( m2.payload.sem_command.has_sequence_id,true);
 //   EXPECT_EQ( m2.payload.sem_command.sequence_id,100 );
    EXPECT_EQ(string(m1.payload.sem_command.device_id), "ABC" );
    
    EXPECT_NEAR(m2.payload.sem_command.payload.xy.x, 22, 0.001);
    EXPECT_NEAR(m2.payload.sem_command.payload.xy.y,33,0.001);

}
