// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBMessageSEMMessage.h"
#include "KFProtocolUtilities.h"


KFPBMessageSEMMessage::KFPBMessageSEMMessage() : KFPBMessageSEM( (pb_field_t *  )SEMMessage_fields ),fSEMMessageStatus(),
        fSEMMessageSensor(),
        fSEMMessageSensorBool(),
        fSEMMessageMotor(),
        fSEMMessageSolenoid(),
        fSEMMessageXYMotor(),
        fSEMMessageConfigurationStatusReply(),
        fSEMMessageCommandStatusReply()
{
    fSEMMessageStatus.Set( &fCmd->payload.sem_status ) ;
    fSEMMessageSensor.Set( &fCmd->payload.sensor_status ) ;
    fSEMMessageSensorBool.Set( &fCmd->payload.bool_sensor_status );
    fSEMMessageMotor.Set( &fCmd->payload.motor_status ) ;
    fSEMMessageSolenoid.Set( &fCmd->payload.solenoid_status ) ;
    fSEMMessageXYMotor.Set( &fCmd->payload.xy_motor_status) ;
    fSEMMessageConfigurationStatusReply.Set(  &fCmd->payload.configuration_reply ) ;
    fSEMMessageCommandStatusReply.Set( &fCmd->payload.command_reply ) ;
    Reset();
}

KFPBMessageSEMMessage::~KFPBMessageSEMMessage()
{

}


  KFPBSubMessageSEMMessageStatus *
  KFPBMessageSEMMessage::GetMessageStatus()
  {
      return  &fSEMMessageStatus;
  }


  KFPBSubMessageSEMMessageSensor *
  KFPBMessageSEMMessage::GetMessageSensor()
  {
      return &fSEMMessageSensor;
  }


  KFPBSubMessageSEMMessageSensorBool *
  KFPBMessageSEMMessage::GetMessageSensorBool()
  {
      return &fSEMMessageSensorBool;
  }


  KFPBSubMessageSEMMessageMotor *
  KFPBMessageSEMMessage::GetMessageMotor()
  {
      return  &fSEMMessageMotor;
  }


  KFPBSubMessageSEMMessageSolenoid *
  KFPBMessageSEMMessage::GetMessageSolenoid()
  {
      return  &fSEMMessageSolenoid;
  }

  KFPBSubMessageSEMMessageXYMotor *
  KFPBMessageSEMMessage::GetMMessageXYMotor()
  {
      return  &fSEMMessageXYMotor;
  }


  KFPBSubMessageSEMMessageConfigurationStatusReply *
  KFPBMessageSEMMessage::GetMessageConfigurationStatusReply()
  {
     return  &fSEMMessageConfigurationStatusReply;
  }


  KFPBSubMessageSEMMessageCommandStatusReply *
  KFPBMessageSEMMessage::GetMessageCommandStatusReply()
  {
    return  &fSEMMessageCommandStatusReply;
  }



ePB_MESSAGE_ONEOF_TYPE
 KFPBMessageSEMMessage::GetMessageType() const
 {
    return  (ePB_MESSAGE_ONEOF_TYPE)fCmd->which_payload;

 }


// int32_t
// KFPBMessageSEMMessage::GetSequenceID() const
// {
//     return fCmd->sequence_id;
// }


void
KFPBMessageSEMMessage::SetMessageType(  const  ePB_MESSAGE_ONEOF_TYPE  cmd  )
{
    fCmd->which_payload = (int)cmd;

    switch (cmd)
    {
        case ePB_MESSAGE_ONEOF_TYPE::SEM_STATUS:
            fSEMMessageStatus.Set( &fCmd->payload.sem_status ) ;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS:
            fSEMMessageSensor.Set( &fCmd->payload.sensor_status ) ;
            break;
        case  ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS:
            fSEMMessageSensorBool.Set( &fCmd->payload.bool_sensor_status );
            break;
        case  ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS:
            fSEMMessageMotor.Set( &fCmd->payload.motor_status ) ;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS:
            fSEMMessageSolenoid.Set( &fCmd->payload.solenoid_status ) ;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS:
            fSEMMessageXYMotor.Set( &fCmd->payload.xy_motor_status) ;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY:
            fSEMMessageConfigurationStatusReply.Set(  &fCmd->payload.configuration_reply ) ;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY:
            fSEMMessageCommandStatusReply.Set( &fCmd->payload.command_reply ) ;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::UNKNOWN:
        case ePB_MESSAGE_ONEOF_TYPE::INVALID:
        default:
            break;
    }

}

// void
// KFPBMessageSEMMessage::SetSequenceID( int32_t id)
// {
//     fCmd->sequence_id = id;
// }


#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBMessageSEMMessage::GetDeviceID() const
{
    return string( fCmd->device_id );
}
#endif


int
KFPBMessageSEMMessage::GetDeviceID(char *id, const size_t max_size) const
{
    int n = max_size < sizeof( this->fCmd->device_id) ? max_size : sizeof( this->fCmd->device_id);
    // errno_t strcpy_s(char *restrict dest, rsize_t destsz, const char *restrict src);
    strncpy( id, (const char *)this->fCmd->device_id, n );
    return CMD_OK;
   /// return fCmd->device_id;
}




#if defined( __unix__ )  || defined (_WIN32 )
int
KFPBMessageSEMMessage::SetDeviceID(const string  id )
{
    KFPBMessageSEM::SetString( this->fCmd->device_id, sizeof( this->fCmd->device_id), id.c_str() );
    return CMD_OK;
}
#endif


int
KFPBMessageSEMMessage::SetDeviceID(const char  *id, size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->device_id) ? max_size : sizeof( this->fCmd->device_id);
    strncpy( this->fCmd->device_id, id, n );
    ////return ret;

   // KFPBMessageSEM<T>::SetString( this->fCmd->device_id, sizeof( this->fCmd->device_id), id.c_str() );
    return CMD_OK;
}






void
KFPBMessageSEMMessage::Reset(SEMMessage *  t)
{
    fSEMMessageStatus.Reset();
    fSEMMessageSensor.Reset();
    fSEMMessageSensorBool.Reset();
    fSEMMessageMotor.Reset();
    fSEMMessageSolenoid.Reset();
    fSEMMessageXYMotor.Reset();
    fSEMMessageConfigurationStatusReply.Reset();
    fSEMMessageCommandStatusReply.Reset();

    t->which_payload = 0;
   //// t->sequence_id = 0;

    for(size_t i=0; i < sizeof (t->device_id ); i++ )
    {
        t->device_id[i] = 0;
    }
}


void
KFPBMessageSEMMessage::Reset()
{
    Reset( fCmd );
}



#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBMessageSEMMessage::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("DEVICE_ID:") << GetDeviceID() << endl;
 ///   buffer << g_utilities()->TabAlign("Sequence ID:") << GetSequenceID() << endl;
    buffer << g_utilities()->TabAlign("Message type:") << KFProtocolUtilities::Enum2String (GetMessageType() )  << endl;

    ePB_MESSAGE_ONEOF_TYPE type = GetMessageType();

    switch (type)
    {
        case ePB_MESSAGE_ONEOF_TYPE::SEM_STATUS:
            buffer << fSEMMessageStatus;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS:
            buffer << fSEMMessageSensor;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS:
            buffer << fSEMMessageSensorBool;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS:
            buffer << fSEMMessageMotor;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS:
            buffer << fSEMMessageSolenoid;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS:
            buffer << fSEMMessageXYMotor;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY:
            buffer << fSEMMessageConfigurationStatusReply;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY:
            buffer << fSEMMessageCommandStatusReply.str();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::INVALID:
            buffer << "Message type is invalid" << endl;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::UNKNOWN:
            buffer << "Message type is unknown" << endl;
            break;
        default:
            buffer << "Message type not reckognized" << endl;
            break;
    }

    return buffer.str();
}

string
KFPBMessageSEMMessage::strOneLine() const
{
    std::stringstream buffer;
    ePB_MESSAGE_ONEOF_TYPE type = GetMessageType();

    std::string devID = GetDeviceID();
    std::string msgType = KFProtocolUtilities::Enum2String(GetMessageType());
    //  int seqID = GetSequenceID();

    // GText buf(
    //     "[%-8s] [%02d] [%-20s : ",
    //     devID.c_str(),
    //     seqID,
    //     msgType.c_str());

      GText buf(
        "[%-8s] [ %-16s : ",
        devID.c_str(),
        msgType.c_str());


    buffer << buf.c_str();

    switch (type)
    {
        case ePB_MESSAGE_ONEOF_TYPE::SEM_STATUS:
            buffer << fSEMMessageStatus.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS:
            buffer << fSEMMessageSensor.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS:
            buffer << fSEMMessageSensorBool.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS:
            buffer << fSEMMessageMotor.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS:
            buffer << fSEMMessageSolenoid.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS:
            buffer << fSEMMessageXYMotor.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY:
            buffer << fSEMMessageConfigurationStatusReply.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY:
            buffer << fSEMMessageCommandStatusReply.strOneLine();
            break;
        case ePB_MESSAGE_ONEOF_TYPE::INVALID:
            buffer << "Message type is invalid" << endl;
            break;
        case ePB_MESSAGE_ONEOF_TYPE::UNKNOWN:
            buffer << "Message type is unknown" << endl;
            break;
        default:
            buffer << "Message type not reckognized" << endl;
            break;
    }

    return buffer.str();
    // return "TEST";
}

#endif
