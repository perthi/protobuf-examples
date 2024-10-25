// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/
#include "KFMessageHandler.h"


#include <logging/LLogApi.h>
using  namespace LOGMASTER;
#include <protocol/KFPBMessageSEMCommand.h>
#include <protocol/KFPBSubMessageSEMConfigStepperMotor.h>
#include <protocol/KFPBMessageSEMConfig.h>
#include <protocol/KFPBMessageSEMOneOfMessage.h>
#include <protocol/KFPBSubMessageSEMMessageConfigurationStatusReply.h>
#include <protocol/KFPBSubMessageSEMMessageCommandStatusReply.h>
#include <protocol/KFPBMessageSEMMessage.h>
#include <kf-common/KFDeviceInfo.h>

#include <utilities/GTime.h>


#include <memory>


bool  KFMessageHandler::fgVerbose = false;
bool  KFMessageHandler::fgMute = false;


vector< void(*)(const std::shared_ptr<KFDeviceInfo >   ) >   KFMessageHandler::fSubscribers;


KFMessageHandler::KFMessageHandler()
{

}


KFMessageHandler::~KFMessageHandler()
{

}


void
KFMessageHandler::SetVerbose(const bool verbose)
{
    fgVerbose = verbose;
}


void
KFMessageHandler::Mute(const bool val )
{
    fgMute = val;
}



string
KFMessageHandler::MessageHandlerServer(const string msg) const
{
    // PUSH();
    // SET_LOGLEVEL("--all-info");
    string ret = MessageHandler(msg);
    // POP();
    return ret;
}


string
KFMessageHandler::MessageHandlerClient(const string msg) const
{
   COM_DEBUG("Recvied message = %s  (size = %d )", msg.c_str(), msg.size() );
   return MessageHandler( msg);
}



bool
KFMessageHandler::HandleMessage(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg, const string msg )  const
{
 ///  FORCE_DEBUG("Recvied message = %s  (size = %d )", msg.c_str(), msg.size() );

    if( msg.size()  == 0)
    {
        G_FATAL( "Message is empty");
        return false;
    }
    else
    {
        // PUSH();
        // SET_LOGLEVEL("--all-off");
        bool ret = oneof_msg->SerializeFromString(msg);
        // POP();

        if(ret == false)
        {
            COM_INFO("Failed to deserialize message (msg = %s) of type %", msg.c_str(),  typeid(KFPBMessageSEMOneOfMessage ).name() );
        }
        else
        {
            if(fgMute == false)
            {
                Print( oneof_msg );
            }
            else
            {
                COM_ERROR("COM HandleMessage Muted");
            }

            UpdateSubscribers(oneof_msg);
        }
        return ret;
    }
}


void
KFMessageHandler::Print(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg  )  const
{
    // PUSH();
    // SET_LOGLEVEL("--all-off --sensor-info");
    // SET_LOGFORMAT("11111111");
    ePB_ONEOF_TYPE msg_type = oneof_msg->GetMessageType();
    COM_INFO( "Message type = %s ",  KFProtocolUtilities::Enum2String( msg_type ).c_str() );

    string tmp =  GenerateOutputStr(  oneof_msg);

    SENSOR_INFO("XXX (size = %d) %s",  tmp.size(),  tmp.c_str());
    // POP();
}


string
KFMessageHandler::GenerateOutputStr(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg ) const
{
    if(fgVerbose == true )
    {
        return oneof_msg->str();
    }
    else
    {
        return oneof_msg->strOneLine();
    }
}



std::shared_ptr<KFDeviceInfo >
KFMessageHandler::GenrateDeviceInfo(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg  ) const
{
 auto info = std::make_shared<KFDeviceInfo>();

    ePB_ONEOF_TYPE msg_type = oneof_msg->GetMessageType();

    if (msg_type == ePB_ONEOF_TYPE::MESSAGE)
    {
        auto message = oneof_msg->GetPBMessage();

        info->fDeviceId = message->GetDeviceID();
        info->fEpochTime = g_time()->GetEpochTime();

        ePB_MESSAGE_ONEOF_TYPE type = message->GetMessageType();
        switch (type)
        {
        case ePB_MESSAGE_ONEOF_TYPE::SEM_STATUS:
        {
            auto tmp = message->GetMessageStatus();
            info->fErrorMsg = tmp->GetErrorString();
            info->fState = (int)tmp->GetState();
        }
        break;
        case ePB_MESSAGE_ONEOF_TYPE::SENSOR_STATUS:
        {
            auto tmp = message->GetMessageSensor();
            info->fVal1 = tmp->GetValueConverted();
            info->fErrorMsg = tmp->GetErrorString();
            info->fState = (int)tmp->GetState();
        }
        break;
        case ePB_MESSAGE_ONEOF_TYPE::BOOL_SENSOR_STATUS:
        {
            auto tmp = message->GetMessageSensorBool();
            info->fVal1 = tmp->GetValueConverted();
            info->fState = (int)tmp->GetState();
        }
        break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_STEPPER_STATUS:
        {
            auto tmp = message->GetMessageMotor();
            info->fVal1 = tmp->GetPosition();
            info->fVal2 = tmp->GetSpeed();
            info->fErrorMsg = tmp->GetErrorString();
            info->fState = (int)tmp->GetState();
        }
        break;
        case ePB_MESSAGE_ONEOF_TYPE::SOLENOID_STATUS:
        {
            auto tmp = message->GetMessageSolenoid();
            info->fErrorMsg = tmp->GetErrorString();
            info->fState = (int)tmp->GetState();
        }
        break;
        case ePB_MESSAGE_ONEOF_TYPE::MOTOR_XY_STATUS:
        {
            auto tmp = message->GetMMessageXYMotor();
            info->fErrorMsg = tmp->GetErrorString();
            info->fVal1 = tmp->GetValueXPosition();
            info->fVal2 = tmp->GetValueYPosition();
            info->fState = (int)tmp->GetState();
        }
        break;
        case ePB_MESSAGE_ONEOF_TYPE::CONFIGURATION_REPLY:
        case ePB_MESSAGE_ONEOF_TYPE::COMMAND_REPLY:
        case ePB_MESSAGE_ONEOF_TYPE::INVALID:
        case ePB_MESSAGE_ONEOF_TYPE::UNKNOWN:
        default:
            ENGINE_ERROR("message type %s cannot be handled here", KFProtocolUtilities::Enum2String(type).c_str());
            break;
        }
    }

    return info;

}


void
KFMessageHandler::UpdateSubscribers(std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg)  const
{
    std::shared_ptr<KFDeviceInfo> info =  GenrateDeviceInfo( oneof_msg );

    for(size_t i=0; i< fSubscribers.size(); i++ )
    {
      void(  *funct)(const  std::shared_ptr<KFDeviceInfo> )  =  fSubscribers.at(i);
        funct( info );
    }
}



string
KFMessageHandler::MessageHandler(const string msg) const
{
    bool ret = false;
    std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg =  std::make_shared< KFPBMessageSEMOneOfMessage >();
    ret = HandleMessage(oneof_msg, msg);

    bool ret2 = IsStatusReply<KFPBSubMessageSEMMessageCommandStatusReply>(msg);
    bool ret3 = IsStatusReply<KFPBSubMessageSEMMessageConfigurationStatusReply>(msg);

    ret = (ret2 == true || ret3 == true) ? true : false;
    COM_ASSERT_WARNING(ret != false,  "message type not reckognized, deserailization failed for all known protobuf message types");
    return "";
}



string
KFMessageHandler::MessageHandlerFromSEM(const string msg) const
{
    COM_ASSERT_ERROR( msg.size() > 0,  "recieved empty message ");
    std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg =  std::make_shared< KFPBMessageSEMOneOfMessage >();
    HandleMessage(oneof_msg, msg);

    // if(ret == false)
    // {
    //     std::shared_ptr< KFPBMessageSEMMessage> message =  std::make_shared< KFPBMessageSEMMessage >();
    //     ret = HandleMessage( message, msg);
    // }

    return "";
}


 void
 KFMessageHandler::RegisterSubscriber(  void(  *funct)(const  std::shared_ptr<KFDeviceInfo>  ))
 {
     fSubscribers.push_back(funct);
 }