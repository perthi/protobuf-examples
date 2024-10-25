// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

///////////////////////////////////////////////////////////
//  KMBPostOffice.cpp
//  Implementation of the Class KMBPostOffice
//  Created on:      13-mar-2018 14.38.47
//  Original author: pth
///////////////////////////////////////////////////////////


#include "MBPostOffice.h"
#include "MBMessage.h"
#include <utilities/GString.h>
#include <utilities/GTime.h>
#include <logging/LLogApi.h>
using namespace LOGMASTER;
#include <thread>
#include <chrono>
#include <utilities/GUtilities.h>
#include <common/MBMessageInfo.h>
#include <common/MBPostOfficeConfig.h>
#include <common/MBMessageT.h>


MBPostOffice *
MBPostOffice::Instance(   )
{
	static MBPostOffice *instance = new MBPostOffice( ) ;
	return instance;
}



MBPostOffice::MBPostOffice(  ) : fDispatcher(nullptr), fMsgCnt(0), fDoRunPo(false), fIsRunningPo(false), fDoPause(false)
{
	static std::mutex m;
	std::lock_guard<std::mutex> guard( m );
	CreateMessageChannels();
	StateTransition("NOT_READY");
	DoSubscribe("OUT::TIMER", GetComponentID() );
	StateTransition("OK");
	StartPostOffice();
}


MBPostOffice::~MBPostOffice()
{
	static std::mutex m;
	std::lock_guard<std::mutex> guard( m );
	StopPostOffice();

	if ( fDispatcher != nullptr )
	{
		fDispatcher->join();
		delete fDispatcher;
		fDispatcher = nullptr;
	}
}


/** @brief main thread
*   @details This function runs in a seprate thread and its main
*   function is to dispatch messages to the subscribers.
*   The thread will run is as long as DoRun() retyrn true
*   that is until Stop() is called */
void
MBPostOffice::RunOffice()
{
	fDoRunPo = true;

	while (   fDoRunPo  == true )
	{
		if ( fDoPause == true )
		{
			fIsRunningPo = false;
		}
		else
		{
			fIsRunningPo = true;
			DispatchMessages();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	G_FATAL("Reached end of endless loop");
}


/** @brief Start the dispatching of messages and transitions the PostOffice to RUNNING */
void
MBPostOffice::StartPostOffice()
{
	G_INFO("Starting");
	StartComponent();

	fDoRunPo = true;
	if ( fDispatcher == nullptr )
	{
		G_INFO("Starting new dispatcher");

		{
			static  std::mutex m;
			std::lock_guard<std::mutex> guard( m );
			fDispatcher = new std::thread( &MBPostOffice::RunOffice, this );
			fDoRunPo = true;
			fIsRunningPo = true;

		}

		G_DEBUG("Transitioning to running");
		StateTransition("RUNNING");
///		FORCE_DEBUG("current state = %s", fStateCurrent->str().c_str() );
		G_INFO("Done");
	}
	else
	{
		fDoRunPo = true;
		fIsRunningPo = true;
		G_INFO("Post Office is allready running, doing nothing( fIsRunning = %s",  ( fIsRunningPo == true ? "TRUE" : "FALSE") );
	}
};


/** @brief Stops the dispatching of messages and transition the PostOffice to PAUSED*/
void
MBPostOffice::StopPostOffice()
{
	G_INFO("Stopping Post Office");
	StopComponent();

	fDoRunPo = false;
	if ( fDispatcher != nullptr )
	{
		if ( fDispatcher->joinable() == true )
		{
			{
                static  std::mutex m;
				std::lock_guard<std::mutex> guard(  m );
				fDispatcher->join();
				delete fDispatcher;
				fDispatcher = nullptr;
				fIsRunningPo = false;
			}

			G_DEBUG("TRansitioning to PAUSED");
			StateTransition("PAUSED");
		}
		else
		{
			FORCE_DEBUG("Thread is not joinable");
		}
	}
}


void
MBPostOffice::Pause()
{
	fDoPause = true;
	while ( fIsRunningPo == true )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}
	StateTransition("PAUSED");
}


void
MBPostOffice::Resume()
{
	fDoPause = false;
}


void
MBPostOffice::ProcessTimeTick( const MBTime_t * const /*timestamp*/ )
{
	CheckMessageQueues();
}


void
MBPostOffice::CheckMessageQueues()
{
	if ( fDeadLetters.size() > MAX_DEAD_LETTERS )
	{
		G_WARNING( "Dead Letters Pileup: size = %d", fDeadLetters.size() );
		Purge( fDeadLetters,  std::ref(G_queue_mutex_dead) , "dead_letters.log" );
	}
	if ( fInvalidLetters.size() > MAX_INVALID_LETTERS )
	{
		Purge( fInvalidLetters, std::ref(G_queue_mutex_invalid),  "invalid_letters.log" );
		G_WARNING( "Invalid Letters Pileup: size = %d", fInvalidLetters.size() );
	}

	if ( fLostLetters.size() > 0 )
	{
		Purge( fLostLetters, std::ref( G_queue_mutex_lost ), "lost_letters.log" );
	}
}


void
MBPostOffice::ProcessMessageLocal(std::shared_ptr<MBMessageInfo> /*msg*/)
{
	FORCE_DEBUG("Not yet implemented");
}


int
MBPostOffice::ExcecLocal( const string command )
{
	std::thread t;

	G_DEBUG("cmd = %s", command.c_str() );
	if ( command == "CONTINUE" )
	{
		Resume();
	}
	else if ( command == "PAUSE" )
	{
		Pause();
	}
	else
	{
		G_WARNING("unknown command %s", command.c_str()  );
	}

	G_INFO("Current state is %s", GetCurrentState()->GetName().c_str() );
	return 0;
}



int
MBPostOffice::AddSubscriber( const MBSubscriberChannel_t & channel, std::function<void( std::shared_ptr<MBMessageInfo> msg )> func, const bool exact_match )
{
	return AddSubscriber( channel, func, "NO NAME", MBComponentID_t( "Not a component" ), exact_match );
}


/** @brief   Adds a subscriber to a message channel.
 *  @details The subscribes adds the callback function to be called by the message system upon the arrival of a message
 *  to this channel. If the channel does not exist then the callback function will be added to the channel called "INVALID_CHANNEL". This is a feature mainly targeted at debugging
 *	@param[in]     channel  The channel name
 *  @param[in]     func     Pointer to the callback function
 *  @param[in]     name     Optional name
 *  @param[in]     id       The ID of the component that registered this callback function if applicable. Please note that this parameter is optiononal, however if
 *  it is set to anything else than the empty string (""), then the system will require that it is unique. The ID string is then used to remove duplicate subscribers
 *  so that each component/entity that has at most one calback function registered. This is done in order to make the message handling more efficient by avoid
 *  calling the same callback function several times wihc is usually a mistake.
 *  @param[in] exact_match If set to TRUE: The parameter "channel" must match exactly one of the available channels. If set to FALSE the the requirement is only that the  available
 *  channel begins with the string represented by "channel".
 *  @return  - CH_ADD_SUBSCRIBER_OK if the subscriber was sucessfully added to one or more channels matching "channel"
 *            - CH_DONT_EXISTS_ERROR if the subscriber could not be added because the channel does not exist. Please note that the subscriber
 *  is still added to the channel "INVALID_CHANNEL"  */
int
MBPostOffice::AddSubscriber( const MBSubscriberChannel_t &  channel, std::function< void(   std::shared_ptr<MBMessageInfo> msg)>  func, const string name,  const MBComponentID_t  &id,  const bool exact_match )
{
	std::lock_guard<std::timed_mutex>  s_guard( G_queue_mutex );
	int iret  = CH_DONT_EXISTS_ERROR;
	SubscriberInfo s_info;
	s_info.fComponetID = id;
	s_info.fName = name;
	s_info.fCallBack = func;

	if ( exact_match   == false)
	{
		for (auto it = fChahnelMap.begin(); it != fChahnelMap.end(); it++)
		{
			if ( g_string()->BeginsWith(it->first.str(), channel.str() ) == true)
			{
				G_DEBUG("adding callback function to the channel: \"%s\"", channel.c_str());
				it->second.push_back( s_info );

				iret = CH_ADD_SUBSCRIBER_OK;
			}
		}

	}
	else if (exact_match == true)
	{
		auto it = fChahnelMap.find(channel);

		if ( it != fChahnelMap.end() )
		{
			G_DEBUG( "adding callback function to the channel: \"%s\"", channel.c_str() );
			it->second.push_back( s_info );
			iret = CH_ADD_SUBSCRIBER_OK;
		}
	}


	if ( iret == CH_DONT_EXISTS_ERROR )
	{
		G_ERROR("The channel\"%s\"  does not exist, adding subscriber to INVALID_CHANNEL", channel.c_str());
		AddToInvalidChannel(s_info);
	}
	return iret;
}


int
MBPostOffice::RemoveSubscriber( const MBRequestChannel_t &  ch, const MBComponentID_t &  id, const bool  exact_match )
{
	for ( auto it = fChahnelMap.begin(); it != fChahnelMap.end(); it++ )
	{
		if ( IsMatch( ch, it->first, exact_match )  == true )
		{
			vector<SubscriberInfo> &tmp = it->second;
			for ( auto it2 =  tmp.begin() ; it2 != tmp.end(); it2 ++ )
			{
				if ( it2->fComponetID == id )
				{
					bool ret = G_queue_mutex.try_lock_for( std::chrono::milliseconds( 1000 ) );
					if ( ret == false )
					{
						return -1;
					}
					else
					{
		//				FORCE_DEBUG("aguired lock for erasing lock erasing ........");
//						FORCE_DEBUG("Componet name = %s", it2->fName.c_str() );
//						FORCE_DEBUG("id = %s, it2->fComponetID = %s", id.c_str(), it2->fComponetID.str().c_str() );
				///		it->second.
						//it->second.
						tmp.erase( it2, it2 + 1 );
						G_queue_mutex.unlock();
					}
					return CH_REMOVAL_OK;
				}
			}
		}
		else
		{
		//	FORCE_DEBUG("IS MATCH returned FALSE");
		}
	}

	return CH_DONT_EXISTS_ERROR;
}




/** @brief If a component tries to subscribe to a channlel that doesnt exist, then it is set to
  *	subscribe to the "INVALID_CHANNEL" channel*/
void
MBPostOffice::AddToInvalidChannel( SubscriberInfo  element )
{
	auto  it = fChahnelMap.find( MBSubscriberChannel_t("INVALID_CHANNEL") );

	if (it != fChahnelMap.end())
	{
		MBSubscriberChannel_t channel = it->first;
		G_WARNING("ADDING subscriber for %s to the >INVALID CHANNEL !!!!!!", channel.c_str() );
		it->second.push_back( element );
	}
	else
	{
		G_ERROR("The INVALID_CHANNEL (the channel for invalid channel descriptors), does not exist");
	}
}


bool
MBPostOffice::IsMatch( const MBRequestChannel_t & req_ch, const MBSubscriberChannel_t & subs_ch, const bool exact_match )
{
	if ( exact_match == true )
	{
		return req_ch.str() == subs_ch.str() ? true : false;
	}
	else
	{
		return  g_string()->BeginsWith( subs_ch.str(), req_ch.str() ) == true ? true : false;
	}
}


bool
MBPostOffice::IsSubscriber( const MBComponentID_t &id, const MBRequestChannel_t & req_ch, const bool exact_match )
{
	for ( auto it = fChahnelMap.begin(); it != fChahnelMap.end(); it++ )
	{
		if ( IsMatch( req_ch, it->first, exact_match ) == true )
		{
			vector<SubscriberInfo> info = it->second;

			for ( size_t i = 0; i < info.size(); i++ )
			{
				if ( id == info.at( i ).fComponetID )
				{
					return true;
				}
			}

		}
	}
	return false;
}


void
MBPostOffice::SendBlockingErrorReply( std::shared_ptr<MBMessageInfo> G_info, eBLOCKING_ERROR error_code )
{
	std::shared_ptr <MBMessageT<eBLOCKING_ERROR> > m = std::make_shared< MBMessageT<eBLOCKING_ERROR> >( error_code );
	G_WARNING("Blocking error (%d)", (int)error_code );
	G_info->SetPromise(m);
}


/**  @brief Adds a message to the message queue. The messages can then later be despatched calling DispatchMessages()
 *   @param[in]  message
 *   @param[in]  exact_match Wether or not an exact match is required beetween the "cannel" parameter and any vailable channels
 *   If set to false the it is only required that a channel begins with "channel" */
void
MBPostOffice::QueMessage( std::shared_ptr< MBMessageInfo>    message , const bool  exact_match  )
{
//	FORCE_DEBUG("queing message_ %s", message->str().c_str()  );

	if ( fWireTap != nullptr )
	{
		fWireTap( message );
	}


	message->fExactMatch = exact_match;
	{
		std::lock_guard<std::timed_mutex> guard( G_queue_mutex );
		fMessages.push( message );
	}
	fMsgCnt++;
}


void
MBPostOffice::QueMessage( MBMessage  & msg, const string  channel, const bool  exact_match )
{
	std::shared_ptr<MBMessageInfo> G_info= std::make_shared<MBMessageInfo>( std::make_shared<MBMessage>(msg), channel );
	G_info->fExactMatch = exact_match;
	QueMessage( G_info, exact_match );
}


void
MBPostOffice::SetWireTap( std::function<void( std::shared_ptr<MBMessageInfo>msg )> funct )
{
	fWireTap = funct;
}


/**  @brief   Lets the PostOffice susbcribe to one of its own channels
 *   @details In order to let the KMBPostOffice subscribe to one of its own channels
 *   we need to override the DoSubscribe function in the GComponent class.
 *   The reason is that the default implementation calls KMBPostOffice::Intance(). This
 *   will  ot work in the special case when the component that and subscribes  and the
 *   KMBPostOffice::Intance() is the same object. It would imply calling  KMBPostOffice::Intance() within
 *   KMBPostOffice::Intance() which would yield undefined behaviour.
 *   @param[in] channel The channel(s) to subscribe to
 *   @param[in] exact_match Wether an exact match is required or if the component should subscribe to
 *   all channels that begins with "channel"
 *   @return  CH_ADDITION_OK if the subscription was successfull oterwise CH_DONT_EXISTS_ERROR */
int
MBPostOffice::DoSubscribe( const string  channel, MBComponentID_t id, const bool exact_match )
{
	G_INFO( "Name: %s  attempting to subscribe to %s", GetName().c_str(), channel.c_str() );
	if ( ExistsChannel( MBSubscriberChannel_t( channel ) ) == false )
	{
		G_ERROR( "%s: The channel %s does not exist", GetName().c_str(), channel.c_str() );
	}

	std::function< void( std::shared_ptr<MBMessageInfo> msg ) >   testFunc( std::bind( &GComponent::OnRecieve, this, std::placeholders::_1 ) );
	return AddSubscriber( MBSubscriberChannel_t( channel ), testFunc, "Post Office", id , exact_match );
}



/** @brief Finds the number fo subscribers to a ginve channel. The match must be exact
*   @param[in] ch The channel to match
*   @return  The number of subscribers to this channel  */
size_t
MBPostOffice::GetSubscriberCount( const MBSubscriberChannel_t & ch )
{
	auto it = fChahnelMap.find( ch );

	if ( it == fChahnelMap.end() )
	{
		return 0;
	}
	else
	{
		return it->second.size();
	}
}



/** @brief Sends qued messagess to the subscribers amd removes them from the message que.
  * If the message does not have any subscribers thme it is added to "Dead Letters" */
void
MBPostOffice::DispatchMessages()
{
	if ( fMessages.size() == 0 ) { return; }
	std::queue< std::shared_ptr < MBMessageInfo > > tmp_messages;

		bool ret = G_queue_mutex.try_lock_for( std::chrono::milliseconds( 200 ) );
		if ( ret == false )
		{
			G_FATAL("Failed to aquire mutex after 200 ms");
			return;
		}
		else
		{
			std::swap( tmp_messages, fMessages );
			G_queue_mutex.unlock();
		}

	while ( tmp_messages.size() > 0 )
	{
		bool delivered = false;
		bool invalid = false;
		std::shared_ptr<MBMessageInfo> element = nullptr;
		{
			element = tmp_messages.front();
			tmp_messages.pop();
			fMsgCntProcessed++;
		}

		string ch_name = element->fRequesChannel;
		bool exact_match = element->fExactMatch;
		vector< string > channel_vec;

		{
			channel_vec = GetChannels( ch_name, exact_match );
		}

		if ( channel_vec.size() == 0 )
		{
			invalid = true;
		}

		if ( element->fIsBlocking == true && channel_vec.size() == 0 )
		{
			SendBlockingErrorReply( element, eBLOCKING_ERROR::NO_MATCING_CHANNELS );
		}
		else
		{

			for ( size_t i = 0; i < channel_vec.size(); i++ )
			{
				auto it = fChahnelMap.find( MBSubscriberChannel_t( channel_vec.at( i ) ) );

				if ( it != fChahnelMap.end() )
				{
					auto  cm_entry = it->second;
					if ( element->fIsBlocking == true && cm_entry.size() == 0 )
					{
						SendBlockingErrorReply( element, eBLOCKING_ERROR::NO_SUBSCRIBERS );
					}
					else if ( element->fIsBlocking == true && cm_entry.size() > 1 )
					{
						SendBlockingErrorReply( element, eBLOCKING_ERROR::MULTIPLE_SUBSCRIBERS );
					}
					else
					{

						for ( size_t j = 0; j < cm_entry.size(); j++ )
						{
							MBComponentID_t  id = cm_entry.at( j ).fComponetID;
							std::function< void( std::shared_ptr< MBMessageInfo > ) >  func = cm_entry.at( j ).fCallBack;

							if(func != nullptr)
							{
								func( element );
							}

							fMsgCntDelivered++;
							delivered = true;
						}
					}
				}
			}
		}

		if ( delivered == false )
		{
			std::lock_guard<std::timed_mutex> guard( G_queue_mutex );
			fDeadLetters.push( element );
		}

		if ( invalid == true )
		{
			std::lock_guard<std::timed_mutex> guard( G_queue_mutex );
			fInvalidLetters.push( element );
		}
	}
}


vector< std::shared_ptr<MBMessage> >
MBPostOffice::ExtractMessages()
{
	vector< std::shared_ptr<MBMessage> > messages;
	auto tmp = fMessages;
	G_DEBUG("fMessages.size() = %d",  tmp.size() );

	if (tmp.size() > 0)
	{
		do
		{
			std::shared_ptr<MBMessageInfo> item = tmp.front();
			messages.push_back( item->fMessage );
			tmp.pop();
		}
		while ( tmp.size() != 0);
	}
	return messages;
}



/** @brief adds a message channel to the list of available channels
* @param[in] channel
* @return
*  - CH_ADDITION_OK   The operation was successfull.
*  - CH_EXISTS_ERROR  The channel could not be added because it allready exists
*  - CH_FORMAT_ERROR  The channel could not be added because the format is wrong */
int
MBPostOffice::AddMessageChannel( const MBSubscriberChannel_t   &channel)
{
	if (IsValidFormat(channel.str()) == false )
	{
		G_ERROR("The channel name \"%s\" is invalid", channel.c_str() );
		return  CH_FORMAT_ERROR;
	}
	else
	{
		vector< SubscriberInfo  >  tmp;
		fChahnelMap.emplace( channel, tmp );
		fChannels.push_back( channel.str() );
	}
	return 0;
}


/** Removes the message channel "channel" from the list of valid
  * message channels.
  * @param[in] channel The name of the channel to remove. The match must
  * be exact.
  * @return  CH_REMOVAL_OK (0), if the channel was successfully removed
  * or CH_DONT_EXISTS_ERROR (2) if the channel could not be removed (presumably because it dont existst) */
 int
 MBPostOffice::RemoveMessageChannel( const MBSubscriberChannel_t  &channel )
 {
 	auto it = fChahnelMap.find(channel);
	int ret = 0;

 	if ( it  == fChahnelMap.end())
 	{
 		G_WARNING("The channel \"%s\" is was not found", channel.c_str());
 		ret = CH_DONT_EXISTS_ERROR;
 	}
 	else
 	{
 		G_INFO("Removed channels \"%s\"", channel.c_str());

		{
			std::lock_guard<std::mutex> guard( ch_mutex );
			fChahnelMap.erase( channel );
		}

		ret = CH_REMOVAL_OK;
 	}
 	return ret;
 }


  /** Helper function to std:sort in order to sort the subscribers according to the component ID. This
 is in order to facilitate quick lookup of duplicate subscribers*/
 bool
 MBPostOffice::CompareEqual( const SubscriberInfo  &i,  const SubscriberInfo  &j   )
 {
 	if ( i.fComponetID.GetValue()  == "" || j.fComponetID.GetValue() == "" )
 	{
 		return false;
 	}
 	else if(  i.fComponetID  !=  j.fComponetID )
 	{
 		return false;
 	}
 	else
 	{
 		return true;
 	}
	 // return true;
 }


 /** Helper function to std:sort in order to sort the subscribers according to the component ID. This
 is in order to facilitate quick lookup of duplicate subscribers*/
 bool
 MBPostOffice::CompareLess(  const SubscriberInfo  &i,  const SubscriberInfo  &j   )
 {
 	return  i.fComponetID.str()  < j.fComponetID.str() ? true : false;
 }


 /** For performance reason its only allowed for a given component to have onse subscriber to a message channels. If
 by accident a subscriber is added more than once, then this function takes care of removing any duplicates*/
 int
 MBPostOffice::RemoveDuplicateSubcribers()
 {
	auto it = fChahnelMap.begin();

	std::lock_guard<std::mutex> guard( ch_mutex );
 	for (it = fChahnelMap.begin(); it != fChahnelMap.end(); it++)
 	{
		std::function< bool(  const MBPostOffice::SubscriberInfo  &i,  const MBPostOffice::SubscriberInfo  &j   )     >   less(std::bind(&MBPostOffice::CompareLess, this, std::placeholders::_1, std::placeholders::_2 ));
		auto myvector = it->second;
 		std::sort(myvector.begin(), myvector.end(),  less );
		std::vector<   SubscriberInfo  >::iterator  it2;
		std::function< bool(  const MBPostOffice::SubscriberInfo  &i,  const MBPostOffice::SubscriberInfo  &j   )     >   equal(std::bind(&MBPostOffice::CompareEqual, this, std::placeholders::_1, std::placeholders::_2 ));
		it2 = std::unique(myvector.begin(), myvector.end(), equal);
		myvector.resize(std::distance(myvector.begin(), it2 )); //
 		it->second = myvector;

	}
	return 0;
 }


 /** @brief Wether or not channel with name "channel" exists. The match must be exact*/
 bool
 MBPostOffice::ExistsChannel( const MBSubscriberChannel_t &channel)
 {
 	if (fChahnelMap.find( channel) != fChahnelMap.end())
 	{
 		G_INFO("The channel: \"%s\" exists", channel.c_str());
 		return true;
 	}
 	else
 	{
 		G_INFO("The channel: \"%s\" does not exist exist", channel.c_str());
 		return false;
 	}
 }


 /** @brief Discard all messages */
void
MBPostOffice::Purge()
{
	 G_DEBUG("Purging messages");
	 Purge( fMessages,       std::ref( G_queue_mutex ), "messages.log" );
	 Purge( fDeadLetters,    std::ref(G_queue_mutex_dead), "dead_letters.log"  );
	 Purge( fInvalidLetters, std::ref(G_queue_mutex_invalid), "invalid_letters.log" );
	 Purge( fLostLetters,    std::ref(G_queue_mutex_lost), "lost_letters.log" );
	 G_DEBUG("DONE");
}


/** @brief Discard all messages in q
 *  @param[in]  q the messages to purge
 *  @param[in]  mtx The mutrex that muts be locked when purging this queue
 *  @param[in]  fname File where the information about the purged messages should be written */
 void
MBPostOffice::Purge( std::queue< std::shared_ptr<MBMessageInfo> > &q, std::timed_mutex &mtx,  const string   fname )
 {
	 std::queue< std::shared_ptr < MBMessageInfo > > tmp_messages;

	 {
		std::lock_guard<std::timed_mutex> guard( mtx );
		std::swap( tmp_messages, q );
		std::swap( tmp_messages, q );
	}

	 try
	 {
		// PUSH();
		// SET_LOGLEVEL( "--all-off --target-file --all-info --target-stdout --msg-fatal" );
		G_INFO( "********* PRINTING PURGED MESSAGES *********" );
		// SET_LOGFORMAT( "00000001" );
		// SET_LOGFILENAME( fname );

		int index = 0;

		try
		{

		 }
		catch ( std::exception &e )
		{
			CERR << "could not pause. Reason: " << e.what() << endl;
		}

		while ( q.empty() == false )
		{
			std::shared_ptr<MBMessageInfo> msg = nullptr;
			msg = q.front();
			index++;
			q.pop();
			G_INFO( "index = %d\n%s", index, msg->str().c_str() );
		}

		G_INFO( "****************** DONE ********************" );
		// POP();
	 }
	 catch ( GException &e )
	 {
		 cout << e.what() << endl;
		 throw(e);
	 }
	 catch ( std::exception  &e )
	 {
		 CERR << e.what() << endl;
		 throw(e);
	 }
	 catch ( ... )
	 {
		 CERR << "Unknown exception caught" << endl;
		 throw("unknown exception");
	 }
 }



 /** @brief Retrives a vector of message channles that matches a given pattern
  *  @param[in] pattern The pattern to match agains
  *  @param[in] exact_match wether or not the match must be exact, that is the channel
  *  name is identical to pattern. If exact match is FALSE, then the function return all channels
  *  The begins with "pattern". NB! No wildcard must be used
  *  @return a vector of channels that matches "pattern" */
 vector< string >
 MBPostOffice::GetChannels(const string &pattern, const bool exact_match)
 {
	static std::mutex m;
	std::lock_guard<std::mutex> guard( m );
	vector<string> tmp;

 	for (auto it = fChannels.begin(); it != fChannels.end(); it++)
 	{
 		string name = *it;

 		if (exact_match == true)
 		{
 			if (name == pattern)
 			{
 				tmp.push_back(name);
 			}
 		}
 		else
 		{
 			if ( g_string()->BeginsWith(name, pattern))
 			{
 				tmp.push_back(name);
 			}
 		}
 	}
	 return tmp;
 }


const std::queue< std::shared_ptr<MBMessageInfo> >   *
MBPostOffice::GetDeadLetters()  const
{
	return &fDeadLetters;
}


vector<std::function<void( std::shared_ptr<MBMessageInfo> )>>
MBPostOffice::GetSubscriberFunctions( const string channel )
{
	return  GetSubscriberFunctions( MBSubscriberChannel_t (channel) );
}



/**  @brief Retrieves a list of subscribers for given channel
  *  @param[in] channel The channel name for which to retrieve the assocated callback functions
  *  @return The list of callback functions for channel "channel" */
 vector<std::function<void(  std::shared_ptr<MBMessageInfo> )> >
 MBPostOffice::GetSubscriberFunctions( const MBSubscriberChannel_t &channel )
 {
	vector<std::function<void(  std::shared_ptr< MBMessageInfo> )>> function_list;
 	auto it = fChahnelMap.find(channel);

 	if (it != fChahnelMap.end())
 	{
 		auto tmp = it->second;

 		for (size_t i = 0; i < tmp.size(); i++)
 		{
 			function_list.push_back(  it->second.at(i).fCallBack );
 		}
 	}

 	return function_list;
 }


 /** @brief Initializes a default list of message channels. Please note that in the future this map should be initialized from a XML file or
 *   similar */
 void
 MBPostOffice::CreateMessageChannels()
 {
	MBPostOfficeConfig* messageSystemInfo = MBPostOfficeConfig::Instance();
	vector<string> channels = messageSystemInfo->GetChannels();
	{
		std::lock_guard<std::mutex> guard( ch_mutex );
		fChahnelMap.erase( fChahnelMap.begin(), fChahnelMap.end() );
		fChannels.erase( fChannels.begin(), fChannels.end() );

		for ( string channel : channels )
		{
			AddMessageChannel( MBSubscriberChannel_t( channel ) );
		}
	}

	DoSubscribe("OUT::TIMER", GetComponentID() );
 }


 /** @brief Clears all message channels*/
 void
 MBPostOffice::DeleteMessageChannels()
 {
	 std::lock_guard<std::mutex> guard( ch_mutex );
	 fChahnelMap.clear();
 }


 /** @brief Clears all subscribers form all message channels*/
 void
 MBPostOffice::ResetSubscriberLists()
 {
	 std::lock( G_queue_mutex, ch_mutex );
	 std::lock_guard<std::timed_mutex> lk1( G_queue_mutex, std::adopt_lock );
	 std::lock_guard<std::mutex> lk2( ch_mutex, std::adopt_lock );

	 for ( auto it = fChahnelMap.begin(); it != fChahnelMap.end(); it++ )
	 {
		 it->second.erase( it->second.begin(), it->second.end() );
	 }
 }


size_t
MBPostOffice::Size() const
{
	 return fMessages.size();
}


size_t
MBPostOffice::SizeDead() const
{
	return fDeadLetters.size();
}


size_t
MBPostOffice::SizeInvalid() const
{
	return fInvalidLetters.size();
}



string
MBPostOffice::str() const
{
	std::lock_guard<std::mutex> guard1( ch_mutex );
	std::lock_guard<std::timed_mutex> guard2( G_queue_mutex );
	std::stringstream buffer;
	buffer << FSMNode::str() << endl;
	auto ch_map = fChahnelMap;

	for ( auto it = ch_map.begin(); it != ch_map.end(); it++ )
	{
		vector<SubscriberInfo>  subs = it->second;
		buffer << "**** CHANNEL: " << g_utilities()->TabAlign(it->first.str(), 4 ) <<  g_utilities()->TabAlign ( "*********** Number of subscribers =  ") << subs.size()  << endl;

		for ( size_t i = 0; i < subs.size(); i++ )
		{
			buffer << "\tsubscriber " << i << endl;
			buffer << "\tName\t\t" << subs.at( i ).fName << endl;
			buffer << "\tComponent IDt" << subs.at( i ).fComponetID.str() << endl;;
		}
	}

	return buffer.str();
}

