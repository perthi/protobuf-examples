// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GComponent.h"
#include <logging/LLogging.h>
#include <logging/LLogApi.h>
using namespace LOGMASTER;
#include <mutex>
std::mutex component_mutex;
#include <string>
#include <typeinfo>

#include <common/GIDGenerator.h>
#include <common/MBPostOffice.h>

#include <thread>
using namespace std;

#include <chrono>
//using namespace std::chrono_literals;

#include <common/MBMessageT.h>
#include <common/MBMessageInfo.h>
#include "MBEnums.h"
#include <common/MBDataTypes.h>
#include <common/GlobalRegistry.h>

#undef SendMessage
#undef SendMessageW

#include <utilities/GException.h>

GComponent::GComponent(const string name ) : fThread(nullptr), fSleepTimeMs(100)
{
	SetName(name);
	fMutex = new std::mutex();
  //  fMutex = std::make_shared< std::mutex>();
    GenerateID();
	fComponentID = GIDGenerator::Instance()->CreateUniqueID("COMPONENT_ID:" + name );
	StartComponent();
}

	
GComponent::~GComponent()
{
    DoUnSubscribe("");
    StopComponent();
///	delete fMutex;
}

int
GComponent::DoUnSubscribe( const string channel, const bool exact_match )
{
    MBRequestChannel_t ch( channel );   
   // FORCE_DEBUG("fComponentID = %s", this->fComponentID.c_str() );
    MBComponentID_t component_id( this->fComponentID );
    
    return MBPostOffice::Instance()->RemoveSubscriber(ch, component_id, exact_match);
}


void 
GComponent::GenerateID()
{
   fComponentID = MBComponentID_t (GIDGenerator::Instance()->CreateUniqueID("COMPONENT_ID:" + GetName() ) ); 
}



void
GComponent::StartComponent()
{
	fDoRun = true;
	fThread =  new std::thread(&GComponent::RunComponent, this );
}


void 
GComponent::StopComponent()
{
    G_INFO("stopping %s ",  GetComponentID().c_str() );
    fDoRun = false;
	
    if ( fThread != nullptr )
    {
	//	std::thread *tmp = (std::thread *)fThread;
        if (fThread->joinable() == true )
        {
            fThread->join();
            fIsRunning = false;
        }
    }
    else
    {
        G_ERROR("thread is nullptr !!");
    }
    
    while ( fIsRunning == true ) 
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }
    
    G_INFO("component %s was stopped",  GetComponentID().c_str() );
}


void 
GComponent::QueueMessage( std::shared_ptr<MBMessageInfo> m )
{
    MSG_ASSERT_ERROR( fIsRunning == true, "Componenent is not running, messages will be queued, but not processed" );
    fMessageQueue.push(m);
}


void 
GComponent::RunComponent()
{
    fIsRunning = true;
	
    while ( fDoRun == true )
    {
        if ( fMessageQueue.size() > 0 )
        {
            do
            {
                ((std::mutex *)fMutex)->lock();
                if ( fMessageQueue.size() > 0 )
                {
                    std::shared_ptr<MBMessageInfo> m = fMessageQueue.front();
                    ProcessMessage( m );
                    fMessageQueue.pop();
                }
		
                ((std::mutex *)fMutex)->unlock();
		
            } while ( fMessageQueue.size() > 0 );
        }
        else
        {
            //	FORCE_DEBUG("message queue size = %d, id = %s", fMessageQueue.size(), fComponentID.c_str() );
        }
        std::this_thread::sleep_for(std::chrono::milliseconds( fSleepTimeMs ));
    }
    
    fIsRunning = false;
}


size_t	
GComponent::Size() const
{ 
    return fMessageQueue.size(); 
};


void 
GComponent::ProcessMessage( std::shared_ptr<MBMessageInfo>  message_info )
{
    static thread_local std::mutex mtx;
    std::lock_guard<std::mutex> guard( mtx );
    std::shared_ptr<MBMessage> m =  message_info->fMessage;
  //  G_INFO("Originator %s, name = %s processing messages arriving from %s\trequested reply channel is %s", 
   //        message_info->fMessage->fOriginator.c_str(), GetName().c_str(), message_info->fRequesChannel.c_str(), message_info->fReplyChannel.c_str() );
    
    const  MBTime_t *const timestamp = message_info->fMessage->ExtractRawPayload<MBTime_t>();

    if ( timestamp != nullptr )
    {
        ProcessTimeTick(timestamp);
    }
    else
    {
        if ( message_info->fIsBlocking == false )
        {
      
            ProcessMessageLocal( message_info );
        }
        else
        {
     ///       G_INFO( "%s: This message is blocking (componentID = %s,name =%s)", GetName().c_str(), GetComponentID().c_str(), GetName().c_str() );
            ProcessMessageBlocking( message_info );
        }
    }
    
}


void 
GComponent::ProcessMessageBlocking(std::shared_ptr<MBMessageInfo>  message_info )
{
    G_FATAL("Blocking message handling is not implemenete for this component %s: message source = %s", fName.c_str(),  message_info->fMessage->fOriginator.c_str() );
    std::shared_ptr< MBMessageT<eBLOCKING_ERROR > > reply = std::make_shared< MBMessageT<eBLOCKING_ERROR> >(  eBLOCKING_ERROR::NOT_IMPLEMENTED  );
    message_info->fPromise.set_value( reply );
}


void
GComponent::OnRecieve( std::shared_ptr<MBMessageInfo>  message_info )
{
    auto m = message_info->fMessage;
    G_ASSERT_EXCEPTION(fMutex != nullptr, "mutex is a ZERO pointer");
    ((std::mutex *)fMutex)->lock();
    QueueMessage(message_info);
    ((std::mutex *)fMutex)->unlock();
}


int
GComponent::DoSubscribe( const string  channel, const bool exact_match )
{

    G_INFO( "Name: %s  attempting to subscribe to %s", GetName().c_str(), channel.c_str() );
    if ( MBPostOffice::Instance()->ExistsChannel( MBSubscriberChannel_t( channel ) ) == false )
    {
        G_ERROR( "%s: The channel %s does not exist", GetName().c_str(), channel.c_str() );
    }

    //static thread_local std::mutex mtx;
    static  std::mutex mtx;
    std::lock_guard<std::mutex> guard( mtx );
    std::function< void( std::shared_ptr<MBMessageInfo> msg ) >   testFunc( std::bind( &GComponent::OnRecieve, this, std::placeholders::_1 ) );
    return MBPostOffice::Instance()->AddSubscriber( MBSubscriberChannel_t( channel ), testFunc, GetName(), MBComponentID_t( fComponentID ), exact_match );
}





#undef SendMessage
#undef SendMessageW

void 
GComponent::SendMessage( MBMessage  msg, const string request_channel, const string reply_channel, const bool exact_match ) const
{
    static  thread_local std::mutex mtx;
    std::lock_guard<std::mutex> guard( mtx );
    std::shared_ptr<MBMessage> G_sh = std::make_shared<MBMessage>( msg );
    SendMessage( G_sh, request_channel,  reply_channel,  exact_match  );
}


void 
GComponent::SendMessage( std::shared_ptr<MBMessage> msg, const string request_channel, const string reply_channel, const bool exact_match ) const
{
    static thread_local std::mutex mtx;
    std::lock_guard<std::mutex> guard( mtx );
    std::shared_ptr<MBMessageInfo> G_info= std::make_shared<MBMessageInfo>( msg, request_channel );
    
    {
        static   std::mutex mtx2;
        std::lock_guard<std::mutex> guard2( mtx2 );
        msg->fOriginator = GetName();
        G_info->fReplyChannel = reply_channel;
        G_info->fExactMatch = exact_match;
    }

    {
        static  std::mutex mtx3;
        std::lock_guard<std::mutex> guard3( mtx3 );
        SendMessage( G_info );
    }
}


void 
GComponent::SendMessage( std::shared_ptr<MBMessageInfo> message_info ) const
{
    G_DEBUG("Sending message to channel %s",  message_info->fRequesChannel.c_str() );
    MBPostOffice::Instance()->QueMessage( message_info,  message_info->fExactMatch );
}


std::shared_ptr<MBMessage>
GComponent::SendMessageBlocking( MBMessage  msg, const string channel, const uint32_t timeout) const
{
    G_DEBUG("%s:  recieved blocking message to channel %s", GetName().c_str(), channel.c_str() );
    static thread_local std::mutex mtx;
    std::lock_guard<std::mutex> guard( mtx  );
    std::shared_ptr<MBMessageInfo> G_info= std::make_shared<MBMessageInfo>( std::make_shared<MBMessage>(msg), channel );
    G_info->fExactMatch = true;
    return SendMessageBlocking( G_info, timeout );
}


std::shared_ptr <MBMessage> 
GComponent::SendMessageBlocking(  std::shared_ptr<MBMessageInfo> message_info, const uint32_t  timeout  ) const
{
    G_DEBUG("recived blocking message with timeout %d", timeout );
    message_info->fIsBlocking = true; /// Just in case. Should not be necessary, fIsBlokcing should allready have been set to bloking if it arrives here
    MBPostOffice::Instance()->QueMessage( message_info,  message_info->fExactMatch );
    std::future_status status;
    auto future =  message_info->fPromise.get_future();
    status = future.wait_for( std::chrono::milliseconds( timeout ) );
    

    if ( status == std::future_status::ready )
    {
        G_INFO( "%s: Future is ready, getting it now", GetName().c_str() );
        return future.get();
    }
    else
	{
            eBLOCKING_ERROR error_code = eBLOCKING_ERROR::UNKNOWN;
            
            if ( status == std::future_status::deferred )
            {
                G_FATAL( "%s: Future status is DEFERRED", GetName().c_str() );
                error_code = eBLOCKING_ERROR::DEFERRED;
                //return nullptr;
            }
            else if ( status == std::future_status::timeout )
            {
                error_code = eBLOCKING_ERROR::TIMEOUT;
                G_FATAL( "%s: timeout waiting for future", GetName().c_str()  );
            }
            
            G_FATAL("%s: Waiting for reply returned an error (%s)", GetName().c_str(),  *error_code);
            std::shared_ptr< MBMessageT<eBLOCKING_ERROR > > m = std::make_shared< MBMessageT<eBLOCKING_ERROR> >( error_code );
            return m;
            //	return nullptr;
            
	}
    
    
	return nullptr;
}



void 
GComponent::ProcessTimeTick(  const  MBTime_t *const timestamp  )
{
    G_INFO( "%s:timestamp = %lld us since 1.jan 1970. Not doing anything for the moment",GetName().c_str(), timestamp->GetValue() );
}


