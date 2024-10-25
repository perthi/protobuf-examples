// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFProtocolUtilities.h"

#include <logging/LLogApi.h>
using namespace LOGMASTER;
#include <utilities/GString.h>
#include <kf.pb.h>



string
KFProtocolUtilities::Enum2String( const  eSEM_COMMAND_PAYLOAD_TYPE  type )
{
    switch (type)
    {
    case eSEM_COMMAND_PAYLOAD_TYPE::FLOAT:
        return "FLOAT";
        break;
    case eSEM_COMMAND_PAYLOAD_TYPE::XY:
        return "XY";
        break;
    case eSEM_COMMAND_PAYLOAD_TYPE::NONE:
        return "NONE";
        break;
    case eSEM_COMMAND_PAYLOAD_TYPE::INVALID:
        return "INVALID";
        break;
    case eSEM_COMMAND_PAYLOAD_TYPE::UNKNOWN:
        return "UNKNOWN";
        break;
    default:
        return "ENUM NOT RECKOGNIZED";
        break;
    }

}


/** @todo use smart ENUMS instead */
string
KFProtocolUtilities::Enum2String(  const eSEM_COMMAND_ID cmd )
{
   switch(cmd)
    {
    case  eSEM_COMMAND_ID::BLINK_LED_ON:
        return  "BLINK_LED_ON";
    case  eSEM_COMMAND_ID::BLINK_LED_OFF:
        return  "BLINK_LED_OFF";
    case  eSEM_COMMAND_ID::MOTOR_DEBUG_ON:
        return  "MOTOR_DEBUG_ON";
    case  eSEM_COMMAND_ID::MOTOR_DEBUG_OFF:
        return  "MOTOR_DEBUG_OFF";
    case  eSEM_COMMAND_ID::SET_SINGLE_VALUE:
       return  "SET SINGLE VALUE";
    case  eSEM_COMMAND_ID::SET_XY_VALUE:
       return  "SET VALUE";
    case  eSEM_COMMAND_ID::MOTOR_XY_SET_POSITION:
       return  "XY_SET_POSITION";
    case  eSEM_COMMAND_ID::MOTOR_XY_SET_SPEED_TRANSLATION:
        return  "XY_SET_SPEED_TRANSLATION";
    case  eSEM_COMMAND_ID::MOTOR_XY_SET_SPEED_ROTATION:
        return  "XY_SET_SPEED_ROTATION";
     case  eSEM_COMMAND_ID::MOTOR_XY_INCREMENT_POSITION:
        return  "XY_INCREMENT_POSITION";
    case  eSEM_COMMAND_ID::MOTOR_XY_START_CONTINUOUS_TRANSLATION:
        return  "XY_START_CONTINUOUS_TRANSLATION";
    case  eSEM_COMMAND_ID::MOTOR_XY_STOP_CONTINUOUS_TRANSLATION:
        return  "XY_STOP_CONTINUOUS_TRANSLATION";
    case  eSEM_COMMAND_ID::MOTOR_XY_START_CONTINUOUS_ROTATION:
        return  "XY_START_CONTINUOUS_ROTATION";
    case  eSEM_COMMAND_ID::MOTOR_XY_STOP_CONTINUOUS_ROTATION:
        return  "STOP_CONTINUOUS_ROTATION";
    case  eSEM_COMMAND_ID::MOTOR_XY_SET_SPEED:
        return "XY_SET_SPEED";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_SET_SPEED:
        return  "MOTOR_STEPPER_SET_SPEED";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_SET_ACCELERATION:
        return  "MOTOR_STEPPER_SET_ACCELERATION";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_SET_CURRENT:
        return  "MOTOR_STEPPER_SET_CURRENT";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_START_GOTO_POSITION:
        return  "MOTOR_STEPPER_SET_POSITION";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_START_INCREMENT_POSITION:
        return "MOTOR_STEPPER_INCREMENT_POSITION";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_HARD:
        return  "MOTOR_STEPPER_STOP_HARD";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_STOP_SOFT:
        return  "MOTOR_STEPPER_STOP_SOFT";
     case   eSEM_COMMAND_ID::MOTOR_STEPPER_START_CONTINIOUS_MOVE:
        return "MOTOR_STEPPER_START_CONTINIOUS_MOVE";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_CONFIGURE_POSITION:
        return  "MOTOR_STEPPER_CONFIGURE_POSITION";
    case  eSEM_COMMAND_ID::MOTOR_STEPPER_SET_INACTIVE_CURRENT:
        return  "MOTOR_STEPPER_SET_INACTIVE_CURRENT";
    case  eSEM_COMMAND_ID::PAUSE:
        return  "PAUSE";
    case  eSEM_COMMAND_ID::RESUME:
        return  "RESUME";
    case  eSEM_COMMAND_ID::REQUEST_FW_VERSION:
        return  "REQUEST_FW_VERSION";
    case  eSEM_COMMAND_ID::REQUEST_CONFIG:
        return  "REQUEST_CONFIG";
    case  eSEM_COMMAND_ID::GO_HOME:
        return  "GO_HOME";
    case  eSEM_COMMAND_ID::CALIBRATE_HOME:
        return  "CALIBRATE_HOME";
    case  eSEM_COMMAND_ID::SOLENOID_ACTIVATE:
        return  "SOLENOID_ACTIVATE";
    case  eSEM_COMMAND_ID::SOLENOID_DE_ACTIVATE:
        return  "SOLENOID_DE_ACTIVATE";
    case  eSEM_COMMAND_ID::PWM_SET:
        return  "PWM_SET";
    case  eSEM_COMMAND_ID::REQUEST_SENSOR_VALUE:
        return "REQUEST_SENSOR_VALUE";
    case  eSEM_COMMAND_ID::REQUEST_MOTOR_POSITION:
        return "REQUEST_MOTOR_POSITION";
    case  eSEM_COMMAND_ID::REQUEST_STATE:   // Request current state of the SEM
        return "REQUEST_STATE";
    case eSEM_COMMAND_ID::DEBUG1:
        return "DEBUG1";
    case eSEM_COMMAND_ID::DEBUG2:
        return "DEBUG2";
    case eSEM_COMMAND_ID::DEBUG3:
        return "DEBUG3";
    case eSEM_COMMAND_ID::INVALID:
        return "INVALID";
    case  eSEM_COMMAND_ID::UNKNOWN:   // Request current state of the SEM
        return "UNKNOWN";
    default:
        return "Illegal command ID: " +  g_string()->ToString((int)cmd );
    }
}


string
KFProtocolUtilities::Enum2String(  const ePB_ONEOF_TYPE type )
{
    switch (type)
    {

    case ePB_ONEOF_TYPE::MESSAGE:
            return "MESSAGE";
    case ePB_ONEOF_TYPE::COMMAND:
            return "COMMAND";
    case ePB_ONEOF_TYPE::CONFIG:
            return "CONFIG";
    case ePB_ONEOF_TYPE::INVALID:
            return "INVALID";
    case ePB_ONEOF_TYPE::UNKNOWN:
            return "UNKNOWN";
    default:
            return "message type not reckognized";
        break;
    }
}


string
KFProtocolUtilities::Enum2String( const ePB_MESSAGE_ONEOF_TYPE type)
{
 switch (type)
    {

    case ePB_MESSAGE_ONEOF_TYPE::SEM_STATUS:
        return "SEM_STATUS";
    case ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS:
        return "SENSOR_STATUS";
    case ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS:
        return "BOOL_SENSOR_STATUS";
    case ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS:
        return "MOTOR_STEPPER_STATUS";
    case ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS:
        return "SOLENOID_STATUS";
    case ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS:
        return "MOTOR_XY_STATUS";
    case ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY:
        return "CONFIGURATION_REPLY";
    case ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY:
        return "COMMAND_REPLY";
    case ePB_MESSAGE_ONEOF_TYPE::INVALID:
        return "INVALID";
    case ePB_MESSAGE_ONEOF_TYPE::UNKNOWN:
        return "UNKNOWN";
      default:
            return "message type  not reckognized";
        break;
    }
}


string
KFProtocolUtilities::Enum2String( const eSEM_SENSOR_STATE type)
{
    switch(type)
    {
    case eSEM_SENSOR_STATE::NOT_CONFIGURED:
        return "NOT_CONFIGURED";
        break;
    case eSEM_SENSOR_STATE::RUNNING:
        return "RUNNING";
        break;
    case eSEM_SENSOR_STATE::ERROR:
        return "ERROR";
        break;
    case eSEM_SENSOR_STATE::UNKNOWN:
        return "UNKNOWN";
        break;
    default:
        return "TYPE_NOT_SUPPORTED";
        break;
    }
}


string
KFProtocolUtilities::Enum2String( const eSEM_SENSOR_ERROR_CODE type)
{
    switch(type)
    {
    case eSEM_SENSOR_ERROR_CODE::COMMUNICATION_ERROR:
        return "COMMUNICATION_ERROR";
        break;
    case eSEM_SENSOR_ERROR_CODE::ERROR:
        return "ERROR";
        break;
    case eSEM_SENSOR_ERROR_CODE::UNKNOWN:
        return "UNKNOWN";
        break;
    default:
        return "TYPE_NOT_SUPPORTED";
        break;
    }
}



string
KFProtocolUtilities::Enum2String( const eSEM_BOOL_SENSOR_STATE type)
{
    switch(type)
    {
    case eSEM_BOOL_SENSOR_STATE::NOT_CONFIGURED:
        return "NOT_CONFIGURED";
        break;
    case eSEM_BOOL_SENSOR_STATE::RUNNING:
        return "RUNNING";
        break;
    case eSEM_BOOL_SENSOR_STATE::ERROR:
        return "ERROR";
        break;
    case eSEM_BOOL_SENSOR_STATE::UNKNOWN:
        return "UNKNOWN";
        break;
    default:
        return "TYPE_NOT_SUPPORTED";
        break;
    }
}


string
KFProtocolUtilities::Enum2String( const  eSEM_BOOL_SENSOR_ERROR_CODE  type )
{
   switch(type)
    {
    case eSEM_BOOL_SENSOR_ERROR_CODE::COMMUNICATION_ERROR:
        return "COMMUNICATION_ERROR";
        break;
    case eSEM_BOOL_SENSOR_ERROR_CODE::ERROR:
        return "ERROR";
        break;
    case eSEM_BOOL_SENSOR_ERROR_CODE::UNKNOWN:
        return "UNKNOWN";
        break;
    default:
        return "TYPE_NOT_SUPPORTED";
        break;
    }

}


string
KFProtocolUtilities::Enum2String( const eSEM_SENSOR_ALARM_STATUS type)
{
    switch(type)
    {

    case eSEM_SENSOR_ALARM_STATUS::NOT_CONFIGURED:
        return "NOT_CONFIGURED";
        break;
    case eSEM_SENSOR_ALARM_STATUS::NO_ALARMS:
        return "NO_ALARMS";
        break;
    case eSEM_SENSOR_ALARM_STATUS::ALARM_LOW:
        return "ALARM_LOW";
        break;
    case eSEM_SENSOR_ALARM_STATUS::WARNING_LOW:
        return "WARNING_LOW";
        break;
    case eSEM_SENSOR_ALARM_STATUS::WARNING_HIGH:
        return "WARNING_HIGH";
        break;
    case eSEM_SENSOR_ALARM_STATUS::ALARM_HIGH:
        return "ALARM_HIGH";
        break;
    default:
        return "TYPE_NOT_SUPPORTED";
        break;
    }
}



string
KFProtocolUtilities::Enum2String( const  eSEM_MOTOR_STATE type )
{
    switch(type)
    {
        case eSEM_MOTOR_STATE::NOT_CONFIGURED:
            return "NOT_CONFIGURED";
            break;
        case eSEM_MOTOR_STATE::RUNNING:
            return "RUNNING";
            break;
        case eSEM_MOTOR_STATE::ERROR:
            return "ERROR";
            break;
        case eSEM_MOTOR_STATE::READY:
            return "READY";
            break;
        case eSEM_MOTOR_STATE::FINISHED:
            return "FINISHED";
            break;
        case eSEM_MOTOR_STATE::ABORTING:
            return "ABORTING";
            break;
        case eSEM_MOTOR_STATE::ABORTED:
            return "ABORTED";
            break;
        case eSEM_MOTOR_STATE::STOPPING:
            return "STOPPING";
            break;
        case eSEM_MOTOR_STATE::STOPPED:
            return "STOPPED";
            break;
        case eSEM_MOTOR_STATE::UNKNOWN:
            return "UNKNOW";
            break;
        default:
            return "value not reckognized";
    };

}





string
KFProtocolUtilities::Enum2String( const  eSEM_MOTOR_ERROR_CODE type )
{
    std::stringstream buffer;

    switch(type)
    {
        case eSEM_MOTOR_ERROR_CODE::NO_ERROR:
            buffer << "0x" << std::hex << (int) type << "(NO_ERROR)";
            break;
        case eSEM_MOTOR_ERROR_CODE::EXECUTION_ERROR:
            buffer << "0x" << std::hex << (int) type << "(EXECUTION_ERROR)";
            break;
        case eSEM_MOTOR_ERROR_CODE::OVER_TEMPERATURE:
            buffer << "0x" << std::hex << (int) type << "(OVER_TEMPERATURE)";
            break;
        case eSEM_MOTOR_ERROR_CODE::OVER_CURRENT:
            buffer << "0x" << std::hex << (int) type << "(OVER_CURRENT)";
            break;
        case eSEM_MOTOR_ERROR_CODE::SHORT_CIRCUIT:
            buffer << "0x" << std::hex << (int) type << "(SHORT_CIRCUIT)";
            break;
        case eSEM_MOTOR_ERROR_CODE::INVALID_COMMAND:
            buffer << "0x" << std::hex << (int) type <<"(INVALID_COMMAND)";
            break;
        case eSEM_MOTOR_ERROR_CODE::INVALID_PARAMETER:
            buffer << "0x" << std::hex << (int) type <<"(INVALID_PARAMETER)";
            break;
        case eSEM_MOTOR_ERROR_CODE::UNSPECIFIED_ERROR:
            buffer << "0x" << std::hex << (int) type << "(UNSPECIFIED_ERROR)";
            break;
        default:
         buffer << "0x" << std::hex << (int) type;
    }

    return buffer.str();
}


string
KFProtocolUtilities::Enum2String( const  eSEM_XY_MOTOR_STATE type )
{
    switch(type)
    {
        case eSEM_XY_MOTOR_STATE::ERROR:
            return "ERROR";
            break;
        case eSEM_XY_MOTOR_STATE::NOT_CONFIGURED:
            return "NOT_CONFIGURED";
            break;
        case eSEM_XY_MOTOR_STATE::READY:
            return "READY";
            break;
        case eSEM_XY_MOTOR_STATE::RUNNING:
            return "RUNNING";
            break;
        case eSEM_XY_MOTOR_STATE::FINISHED:
            return "FINISHED";
            break;
        case eSEM_XY_MOTOR_STATE::ABORTING:
            return "ABORTING";
            break;
        case eSEM_XY_MOTOR_STATE::ABORTED:
            return "ABORTED";
            break;
        case eSEM_XY_MOTOR_STATE::STOPPING:
            return "STOPPING";
            break;
        case eSEM_XY_MOTOR_STATE::STOPPED:
            return "STOPPED";
            break;
        case eSEM_XY_MOTOR_STATE::UNKNOWN:
            return "UNKNOW";
            break;
        default:
            std::stringstream buffer;
            buffer << "value:" << (int)type << "Not reckognized" << endl;
            return buffer.str();
            break;
    }

}



string
KFProtocolUtilities::Enum2String( const  eSEM_XY_MOTOR_ERROR_CODE type )
{
     std::stringstream buffer;

    switch(type)
    {
       case eSEM_XY_MOTOR_ERROR_CODE::NO_ERROR:
            buffer << "0x" << std::hex << (int) type << "(NO_ERROR)";
            break;
       case eSEM_XY_MOTOR_ERROR_CODE::EXCUTION_ERROR:
            buffer << "0x" << std::hex << (int) type << "(EXECUTION_ERROR)";
            break;
       case eSEM_XY_MOTOR_ERROR_CODE::FOLLOW_ERROR:
            buffer << "0x" << std::hex << (int) type << "(FOLLOW_ERROR)";
            break;
       case eSEM_XY_MOTOR_ERROR_CODE::INVALID_COMMAND :
            buffer << "0x" << std::hex << (int) type << "(INVALID_COMMAND)";
            break;
       case eSEM_XY_MOTOR_ERROR_CODE::UNSPECIFIED_ERROR:
            buffer << "0x" << std::hex << (int) type << "(UNSPECIFIED_ERROR)";
            break;
      default:
            buffer << "0x" << std::hex << (int) type;
            break;
    }

    return buffer.str();
}


string
KFProtocolUtilities::Enum2String( const  eSEM_SOLENOID_STATE type )
{
    switch(type)
    {
        case eSEM_SOLENOID_STATE::ERROR:
            return "ERROR";
            break;
        case eSEM_SOLENOID_STATE::NOT_CONFIGURED:
            return "NOT_CONFIGURED";
            break;
        case eSEM_SOLENOID_STATE::READY:
            return "READY";
            break;
        case eSEM_SOLENOID_STATE::RUNNING:
            return "RUNNING";
            break;
        case eSEM_SOLENOID_STATE::UNKNOWN:
            return "UNKNOWN";
            break;
        default:
            std::stringstream buffer;
            buffer << "unknown state value (" << (int) type << ")";
            return buffer.str();
    }
}



string
KFProtocolUtilities::Enum2String( const  eSEM_SOLENOID_ERROR_CODE type )
{
    std::stringstream buffer;

    switch(type)
    {
        case eSEM_SOLENOID_ERROR_CODE::NO_ERROR:
            buffer << "0x" << std::hex << (int) type << "(NO_ERROR)";
            break;
        case eSEM_SOLENOID_ERROR_CODE::EXECUTIOM_ERROR:
            buffer << "0x" << std::hex << (int) type << "(EXECUTION_ERROR)";
            break;
        case eSEM_SOLENOID_ERROR_CODE::OVER_TEMPERATURE:
            buffer << "0x" << std::hex << (int) type << "(OVER_TEMPERATURE)";
            break;
        case eSEM_SOLENOID_ERROR_CODE::OVER_CURRENT:
            buffer << "0x" << std::hex << (int) type << "(OVER_CURRENT)";
            break;
        case eSEM_SOLENOID_ERROR_CODE::SHORT_CIRCUIT:
            buffer << "0x" << std::hex << (int) type << "(SHORT_CIRCUIT)";
            break;
        case eSEM_SOLENOID_ERROR_CODE::INVALID_COMMAND:
            buffer << "0x" << std::hex << (int) type << "(INVALID_COMMAND)";
            break;
        case eSEM_SOLENOID_ERROR_CODE::UNSPECIFIED_ERROR:
            buffer << "0x" << std::hex << (int) type << "(UNSPECIFIED_ERROR)";
            break;
    }

     return buffer.str();

}


string
KFProtocolUtilities::Enum2String( const  eSEM_CONFIGURATION_ERROR_CODE  type )
{
    switch(type)
    {
        case eSEM_CONFIGURATION_ERROR_CODE::ERROR:
            return "ERROR";
        case eSEM_CONFIGURATION_ERROR_CODE::NO_ERROR:
            return "NO_ERROR";
        default:
            return "Unknown error";
    }
}


string
KFProtocolUtilities::Enum2String( const  eSEM_COMMAND_ERROR_CODE  type )
{
    switch(type)
    {
        case eSEM_COMMAND_ERROR_CODE::ERROR:
            return "ERROR";
        case eSEM_COMMAND_ERROR_CODE::NO_ERROR:
            return "NO_ERROR";
        default:
            return "Unknown error";

    }

}


string
KFProtocolUtilities::Enum2String( const  eSEM_ERROR_CODE  type )
{
 switch(type)
    {
        case eSEM_ERROR_CODE::ERROR:
            return "ERROR";
        case eSEM_ERROR_CODE::NO_ERROR:
            return "NO_ERROR";
        case eSEM_ERROR_CODE::UNKNOWN:
             return "UNKOWN";
        default:
            return "Unknown error";

    }
}


string
KFProtocolUtilities::Enum2String( const  eSEM_SEM_STATE  type )
{
    switch(type)
    {
        case eSEM_SEM_STATE::ERROR:
            return "ERROR";
        case eSEM_SEM_STATE::NOT_CONFIGURED:
            return "NOT_CONFIGURED";
        case eSEM_SEM_STATE::READY:
            return "READY";
        case eSEM_SEM_STATE::RUNNING:
            return "RUNNING";
        case eSEM_SEM_STATE::UNKNOWN:
            return "UNKNOWN";
        default:
            return "unknown error";
    }
}
