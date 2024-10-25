// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


///////////////////////////////////////////////////////////
//  KMBPostOffice.h
//  Implementation of the Class KMBPostOffice
//  Created on:      13-mar-2018 14.38.47
//  Original author: pth
///////////////////////////////////////////////////////////

#pragma once

#define CH_EXISTS_ERROR  1
#define CH_DONT_EXISTS_ERROR  2
#define CH_FORMAT_ERROR 3
#define CH_ADDITION_OK 0
#define CH_ADD_SUBSCRIBER_OK 0
#define CH_REMOVAL_OK 0

#define EXACT_MATCH true
#define ANY_MATCH   false

#define  MAX_DEAD_LETTERS     100   /// Maximun number of dead letters allowed before the queue is purged
#define  MAX_INVALID_LETTERS  100   /// Maximun number of invalid letters allowed before the queue is purged

#include <common/FDefinitions.h>
#include <common/FSM_Definitions.h>
#include <common/MBDataTypes.h>
#include <common/MBEnums.h>
#include <utilities/GPrintable.h>


#include <vector>
using std::vector;
#include <string>
using std::string;
#include <queue>
#include <tuple>
#include <functional>
#include <map>
using std::map;
#include <mutex>
#include <thread>
using std::thread;
#include <atomic>
#include <memory>


class MBMessage;
class TestMBPostOffice_start_stop_Test;
class TestMBPostOffice_message_registration_Test;
class TestMBPostOffice_dead_letters_Test;
class TestMBPostOffice_is_match_Test;
class TestMBPostOffice_is_subscriber_Test;


/* @brief   Central hub for processing of all messages.
 * @details The PostOffice is responsible for receiving messages and send them to
 * registered subscribers  */
class MBPostOffice : public  FSMNode_PostOffice
{

	friend TestMBPostOffice_start_stop_Test;
	friend TestMBPostOffice_message_registration_Test;
	friend TestMBPostOffice_dead_letters_Test;
	friend TestMBPostOffice_is_match_Test;
	friend TestMBPostOffice_is_subscriber_Test;
	friend GComponent;

	friend void test1( int id, int sleeptime, int *inout );
	friend void test2( int id, int sleeptime, int *inout );
	

	friend int  main( int argc, const char **argv );


public:

        struct SubscriberInfo
        {
                MBComponentID_t fComponetID  = MBComponentID_t("");
                string  fName = "not set";
                std::function< void( std::shared_ptr<MBMessageInfo> ) > fCallBack;
        };

    static		API		MBPostOffice * Instance( );
	virtual         API     string str() const override;
	virtual void	API		ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg)  override;
	virtual int		API		ExcecLocal(const string command)  override;
	virtual  bool			API		IsRunning() const override  { return fIsRunningPo; };
	int				API		RemoveSubscriber(    const  MBRequestChannel_t  &ch, const MBComponentID_t &id, const bool exact_match = false );
	size_t          API		GetSubscriberCount(  const  MBSubscriberChannel_t  &ch );
	void	        API		DispatchMessages();
	size_t			API		Size() const;
	size_t          API     SizeDead() const;
	size_t          API     SizeInvalid() const;
	unsigned long	API		GetMsgCountRecived()   {  return fMsgCnt; };
	unsigned long	API		GetMsgCountProcessed() {  return fMsgCntProcessed ; };
	unsigned long	API		GetMsgCountDelivered() {  return fMsgCntDelivered ; };
	void			API		CreateMessageChannels();
	void			API     DeleteMessageChannels();
	void			API     ResetSubscriberLists();
        std::map< MBSubscriberChannel_t, vector<SubscriberInfo> > API  *   GetChannelMap() { return &fChahnelMap; };
	int				API		AddMessageChannel(  const  MBSubscriberChannel_t   &channel );
	int				API		RemoveMessageChannel( const  MBSubscriberChannel_t &channel );
	int				API		RemoveDuplicateSubcribers();
	bool			API		ExistsChannel( const  MBSubscriberChannel_t  &channel );
	void			API		Purge();
	vector<string >	API     GetChannels(const string &pattern, const bool exact_match = false );
	void            API     SetWireTap( std::function< void( std::shared_ptr< MBMessageInfo> msg ) >  funct );
	virtual  void	API		StartPostOffice() final;
	virtual  void	API     StopPostOffice()  final;
	void            API     Pause();
	void            API     Resume();
	
	std::queue< std::shared_ptr< MBMessageInfo> >	 API	GetMessages() {  return fMessages; };
	vector< std::shared_ptr<MBMessage> >			 API	ExtractMessages();
	const std::queue<  std::shared_ptr< MBMessageInfo > >  API *  GetDeadLetters() const;
	vector < std::function< void(   std::shared_ptr< MBMessageInfo> ) > >  API GetSubscriberFunctions( const string channel);
	vector < std::function< void(   std::shared_ptr< MBMessageInfo> ) > >  API GetSubscriberFunctions( const MBSubscriberChannel_t  &channel);

private:
	MBPostOffice(  );
	virtual  ~MBPostOffice();

	virtual void    API     ProcessTimeTick( const  MBTime_t *const timestamp ) override;
	void            API     CheckMessageQueues();
//							AddSubscriber( const MBSubscriberChannel_t & channel, std::function<void( std::shared_ptr<MBMessageInfo> msg )> func, const bool exact_match )
	virtual  int	API		AddSubscriber( const MBSubscriberChannel_t &  channel, std::function< void( std::shared_ptr<MBMessageInfo> msg )> func, const bool exact_match = false );
	virtual  int	API		AddSubscriber( const MBSubscriberChannel_t &  channel, std::function< void( std::shared_ptr<MBMessageInfo> msg )> func, const string name, const MBComponentID_t &id, const bool exact_match = false );
	
	virtual int		API		DoSubscribe( const string channel,  MBComponentID_t id,  const bool exact_match = false );
	bool			API     IsMatch( const MBRequestChannel_t & req_ch,   const MBSubscriberChannel_t & sub_ch, const bool exact_match  = true  );
	bool			API     IsSubscriber(  const MBComponentID_t &id,  const MBRequestChannel_t & req_ch, const bool exact_match  = true );
	void			API     SendBlockingErrorReply( std::shared_ptr<MBMessageInfo>,  eBLOCKING_ERROR  error_code );
	void			API		QueMessage( MBMessage &msg,  const string ch, const bool exact_match  );
	void			API		QueMessage( std::shared_ptr<MBMessageInfo>  message,  const bool exact_match  );
	
	void			API		RunOffice();
	void			API		Purge( std::queue<  std::shared_ptr<MBMessageInfo> >  &q, std::timed_mutex &mtx,  const string fname);
	bool					CompareEqual( const SubscriberInfo  &i,  const SubscriberInfo  &j );
	bool					CompareLess(  const SubscriberInfo  &i,  const SubscriberInfo  &j );
	void					AddToInvalidChannel( SubscriberInfo );
	bool					IsValidFormat(const  string channel_name ) { return true; }; /// @todo, implement this

	std::function< void( std::shared_ptr<MBMessageInfo> msg ) > fWireTap = nullptr;
	std::queue< std::shared_ptr < MBMessageInfo > >	fMessages;			    //!< Ordinary messages */
	std::queue< std::shared_ptr < MBMessageInfo > >	fDeadLetters;		    //!< Messages delivered to channels that does not have any subscribers */
	std::queue< std::shared_ptr < MBMessageInfo > >	fInvalidLetters;	    //!< Messages delviered to an non existing channel, or to a  subscrieber that could not recieve the message */ 
	std::queue< std::shared_ptr < MBMessageInfo > >	fLostLetters;		    //!< Messages that could not be delivered due to failure of PostOffice */
	std::map< MBSubscriberChannel_t,   vector<SubscriberInfo> > fChahnelMap;   //!< The Message channels */
	vector<string> fChannels;		               //!< string vector of all channels contained in the fChahnelMap. This is a helper variable intended to boost performance */
	std::thread *fDispatcher = nullptr;


	std::atomic_bool  fDoRunPo;
	std::atomic_bool  fIsRunningPo;
	std::atomic_bool  fDoPause;


	unsigned long fMsgCnt = 0;
	unsigned long fMsgCntProcessed = 0;
	unsigned long fMsgCntDelivered = 0;

	std::timed_mutex mutable G_queue_mutex;
	std::timed_mutex mutable G_queue_mutex_dead;
	std::timed_mutex mutable G_queue_mutex_invalid;
	std::timed_mutex mutable G_queue_mutex_lost;
	std::mutex mutable ch_mutex;

};
