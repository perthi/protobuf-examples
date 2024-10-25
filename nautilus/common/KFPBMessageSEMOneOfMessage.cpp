// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBMessageSEMOneOfMessage.h"







KFPBMessageSEMOneOfMessage::KFPBMessageSEMOneOfMessage() : KFPBMessageSEM (  (pb_field_t *  )SEMOneOfMessage_fields) ,fMessage(),fCommand(),fConfig()
{
   fCommand.Set( &fCmd->payload.sem_command);
   fConfig.Set(  &fCmd->payload.sem_config );
   fConfig.GetDeviceAddress()->Set( &fCmd->payload.sem_config.address );
   fMessage.Set( &fCmd->payload.sem_message );
   fMessage.GetMessageCommandStatusReply()->Set( &fCmd->payload.sem_message.payload.command_reply );
   fMessage.GetMessageConfigurationStatusReply()->Set( &fCmd->payload.sem_message.payload.configuration_reply );
   fMessage.GetMessageMotor()->Set( &fCmd->payload.sem_message.payload.motor_status );
   fMessage.GetMessageSensor()->Set( &fCmd->payload.sem_message.payload.sensor_status );
   fMessage.GetMessageSensorBool()->Set( &fCmd->payload.sem_message.payload.bool_sensor_status );
   fMessage.GetMessageSolenoid()->Set( &fCmd->payload.sem_message.payload.solenoid_status );
   fMessage.GetMessageStatus()->Set( &fCmd->payload.sem_message.payload.sem_status );
   fMessage.GetMMessageXYMotor()->Set( &fCmd->payload.sem_message.payload.xy_motor_status );
   Reset();
}



KFPBMessageSEMOneOfMessage::~KFPBMessageSEMOneOfMessage()
{


}


#if defined( __unix__ )  || defined (_WIN32 )
bool
KFPBMessageSEMOneOfMessage::SerializeFromString(const string  dta )
{
    return  KFPBMessageSEM::SerializeFromString(dta);
}
#endif


bool
KFPBMessageSEMOneOfMessage::SerializeFromString( const  uint8_t * const dta, const int size)
{
    KFPBMessageSEM::SerializeFromString(dta, size);
    SetConfigType (fConfig.GetConfigType());
    bool ret =  KFPBMessageSEM::SerializeFromString(dta, size);
    return ret;
}


void
KFPBMessageSEMOneOfMessage::Reset( SEMOneOfMessage  * /*t*/ )
{

}


void
KFPBMessageSEMOneOfMessage::Reset( )
{
   fCommand.Reset();
   fMessage.Reset();
   fConfig.Reset();
   fCmd->sequence_id = 0;
   fCmd->which_payload = 0;
}


void
KFPBMessageSEMOneOfMessage::SetSequenceID(const int32_t id)
{
   fCmd->sequence_id = id;
}


int32_t
KFPBMessageSEMOneOfMessage::GetSequenceID() const
{
   return fCmd->sequence_id;
}

ePB_ONEOF_TYPE
KFPBMessageSEMOneOfMessage::GetMessageType() const
{
    if( fCmd->which_payload ==  SEMOneOfMessage_sem_config_tag  )
    {
        return ePB_ONEOF_TYPE::CONFIG;
    }
    else
    if (  fCmd->which_payload ==  SEMOneOfMessage_sem_command_tag )
    {
        return ePB_ONEOF_TYPE::COMMAND;
    }
    else
    if(  fCmd->which_payload ==  SEMOneOfMessage_sem_message_tag )
    {
        return ePB_ONEOF_TYPE::MESSAGE;
    }
    else
    {
        return ePB_ONEOF_TYPE::UNKNOWN;
        #if defined( __unix__ )  || defined (_WIN32 )
        G_FATAL("unknown tag %d",  fCmd->which_payload );
        #endif
    }

}



KFPBMessageSEMMessage *
KFPBMessageSEMOneOfMessage::GetPBMessage()
{
    return &fMessage;
}


KFPBMessageSEMCommand  *
KFPBMessageSEMOneOfMessage::GetPBCommand()
{
    return &fCommand;
}


KFPBMessageSEMConfig *
KFPBMessageSEMOneOfMessage::GetPBConfig()
{
    return &fConfig;
}



void
KFPBMessageSEMOneOfMessage::SetMessageType( const ePB_ONEOF_TYPE t )
{
    fCmd->which_payload = (pb_size_t)t;
}





void
KFPBMessageSEMOneOfMessage::SetConfigType( const  eSEM_CONFIGTYPE  type  )
{
   fConfig.SetConfigType( type );
}



#if defined( __unix__ )  || defined (_WIN32 )

string
KFPBMessageSEMOneOfMessage::strOneLine() const
{
   std::stringstream buffer;

   if (fCmd->which_payload == SEMOneOfMessage_sem_config_tag)
   {
       buffer << fConfig.strOneLine();
   }

   if (fCmd->which_payload == SEMOneOfMessage_sem_message_tag)
   {
       buffer << fMessage.strOneLine();
   }

   if (fCmd->which_payload == SEMOneOfMessage_sem_command_tag)
   {
       buffer << fCommand.strOneLine();
   }

   return buffer.str();
}



string
KFPBMessageSEMOneOfMessage::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("SEQUENCE_ID:") << GetSequenceID() << endl;

    if ( fCmd->which_payload ==  SEMOneOfMessage_sem_config_tag  )
    {
        buffer << "MESSAGE TYPE:  CONFIG" << endl;
        buffer << fConfig << endl;
    }

    if ( fCmd->which_payload ==  SEMOneOfMessage_sem_message_tag  )
    {
        buffer << "MESSAGE TYPE:  MESSAGE" << endl;
        buffer << fMessage << endl;
    }

    if ( fCmd->which_payload ==  SEMOneOfMessage_sem_command_tag  )
    {
        buffer << "MESSAGE TYPE:  COMMAND" << endl;
        buffer << fCommand << endl;
    }
    return buffer.str();
}

#endif