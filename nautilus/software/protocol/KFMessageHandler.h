// -*- mode: c++ -*-
#ifndef KFMESSAGEHANDLER_H
#define KFMESSAGEHANDLER_H

#include <utilities/GDefinitions.h>
#include <logging/LLogApi.h>
using namespace LOGMASTER;

#include <kf-common/KFDeviceInfo.h>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>





class KFPBSubMessageSEMMessageConfigurationStatusReply;
class KFPBSubMessageSEMMessageCommandStatusReply;
class KFPBMessageSEMOneOfMessage;
class KFPBMessageSEMMessage;

#include <protocol/KFProtocolEnums.h>
class  KFMessageHandler
{
public:
    API  KFMessageHandler();
    virtual API ~KFMessageHandler();
    static void API SetVerbose(const bool verbose);
    static void API Mute(const bool val);

    string API MessageHandlerServer(const string msg) const;
    string API MessageHandlerClient(const string msg) const;
    string API MessageHandler(const string msg) const;
    string API MessageHandlerFromSEM(const string msg) const;

    template<typename T>
    inline  string API GenerateStatusReply(const bool status, const int32_t sequence_id, const string msg = "" ) const;

    template<typename T>
    inline  bool API IsStatusReply( const string msg) const;

    void RegisterSubscriber(  void(  *funct)(const  std::shared_ptr<KFDeviceInfo>  ));


private:
    bool   API   HandleMessage(  std::shared_ptr< KFPBMessageSEMOneOfMessage >  message, const string msg ) const ;
    bool   API   HandleMessage(  std::shared_ptr< KFPBMessageSEMMessage >       message, const string msg ) const ;

    void Print(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg  ) const ;
    void UpdateSubscribers(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg  ) const;

    std::shared_ptr<KFDeviceInfo >  GenrateDeviceInfo(  std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg  ) const;

    ///  template <class T>
    //  string GenerateOutputStr(T *pMessage ) const;
    string GenerateOutputStr(   std::shared_ptr<KFPBMessageSEMOneOfMessage> oneof_msg  ) const;
    static bool fgVerbose;
    static bool fgMute;
    static vector< void(*)(const std::shared_ptr<KFDeviceInfo >   ) > fSubscribers;

};


template<typename T>
string
KFMessageHandler::GenerateStatusReply(const bool status, const int32_t sequence_id, const string msg )  const
{
    auto reply = std::make_shared<T>();

    reply->SetSequenceID( sequence_id );

    if(status == true)
    {
        reply->SetStatusCode( eSEM_COMMAND_ERROR_CODE::NO_ERROR );

        if(msg == "" )
        {
            reply->SetErrorString("Jippi!! There are no errors");
        }
        else
        {
            reply->SetErrorString( msg );
        }

    }
    else
    {
        reply->SetStatusCode( eSEM_COMMAND_ERROR_CODE::NO_ERROR );
        if(msg == "" )
        {
            reply->SetErrorString("There have been errors");
        }
        else
        {
           reply->SetErrorString( msg );
        }

    }

    string tmp = "";
    reply->SerializeToString(tmp);
    return tmp;
}



template<typename T>
inline  bool
KFMessageHandler::IsStatusReply( const string msg ) const
{
    // PUSH();
    // SET_LOGLEVEL("--all-off");
    COM_INFO("trying %s",  typeid(  T).name() );
    auto r = std::make_shared<T>();
    bool ret = r->SerializeFromString(msg);

    COM_INFO("Wether or not message is of type %s ? %s", typeid( T).name(),  (ret == true ? "TRUE" : "FALSE" ) );
    if( ret == true )
    {
      //  sequence_id = r->GetSequenceID();
       // return msg;
        COM_INFO("%s\n", r->str().c_str() );
    }
    // POP();

    return ret;
}



#endif