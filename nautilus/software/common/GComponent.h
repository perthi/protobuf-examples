// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once



#include "FDefinitions.h"
#include <string> 
using std::string;
#include <logging/LLogApi.h>
using namespace LOGMASTER;

#include <queue>
#include <memory>
#include <functional>

#undef SendMessage

struct MBMessageInfo;
class MBMessagePayload;
enum class eMESSAGE_REQUEST;

#include <common/MBMessageT.h>
#include <common/MBDataTypes.h>

#include <thread>
#include <mutex>
#include <memory>

#undef SendMessage
#undef SendMessageW

class GComponent
{
public:
	API GComponent(const string name);
///	API		GComponent();
	virtual			                API		~GComponent();
	virtual void                    API     StartComponent() final ;
	virtual void                    API     StopComponent() final;
	inline  MBComponentID_t 		API     GetComponentID() { return  fComponentID; };
	virtual string	                API		GetName() const final { return fName; };
	virtual void	                API		SetName(const string name) final { fName = name; };
	virtual void	                API		SetAlias( const string alias ) final { fAlias = alias; };
	virtual string 	                API		GetAlias() const { return fAlias; };
	void			                API		QueueMessage( std::shared_ptr<MBMessageInfo> m); /*! < Adds a message to the message queue */
	size_t			                API		Size() const;
	virtual void	                API		OnRecieve( std::shared_ptr<MBMessageInfo> m) final;
 	virtual int		                API		DoSubscribe(  const string channel,  const bool exact_match  = false );
	virtual int		                API		DoUnSubscribe(  const string channel, const bool exact_match  = false );
	template<typename T>
	void			                API		SendMessageRaw( T  &payload, const string request_channel, const string reply_channel = "", const bool exact_matcg = false ) const;
	void			                API		SendMessage( MBMessage  msg, const string request_channel, const string reply_channel = "", const bool exact_matcg = false ) const;
	void			                API		SendMessage( std::shared_ptr<MBMessage>  msg, const string request_channel, const string reply_channel = "", const bool exact_matcg = false ) const;
	std::shared_ptr<MBMessage>		API	 	SendMessageBlocking( MBMessage  msg, const string channel, const uint32_t timeout = UINT_MAX ) const;
	virtual void                    API     SetSleepTimeMs( const int sleep_time ) final { fSleepTimeMs = sleep_time; };
	virtual int                     API     GetSleepTimeMs()  const final { return fSleepTimeMs; };
	virtual  bool inline            API     IsRunning() const { return  fIsRunning ; };
	inline    string                API     IsRunningS() const { return  fIsRunning == true ? "TRUE" : "FALSE"; };

protected:
	virtual void                    API     ProcessMessage( std::shared_ptr<MBMessageInfo>  msg) final;
	virtual void                    API     ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg) = 0;
	virtual void                    API     ProcessMessageBlocking( std::shared_ptr<MBMessageInfo>  msg);
	template<typename T> 
	inline bool CheckPayload( const T * const );
	
//	std::queue <  std::shared_ptr<MBMessageInfo> >	fMessageQueue; /*!< Buffer/queue for incoming messages */
	
//	string fComponentID;
	string fClassName = "";
	string fAlias = "";
	string fName = "Base Component";



///	void   *fThread = nullptr;  /*!< std::thread which must be declared void in the header file for managed C++/.NET compability */
//	void   *fMutex  = nullptr;  /*!< std::mutex  which must be declared void in the header file for managed C++/.NET compability */

	std::thread  *fThread = nullptr;  /*!< std::thread which must be declared void in the header file for managed C++/.NET compability */
	std::mutex  * fMutex = nullptr;  /*!< std::mutex  which must be declared void in the header file for managed C++/.NET compability */

//	std::shared_ptr<std::thread>  fThread = nullptr;  /*!< std::thread which must be declared void in the header file for managed C++/.NET compability */
//	std::shared_ptr<std::mutex>   fMutex = nullptr;  /*!< std::mutex  which must be declared void in the header file for managed C++/.NET compability */


private:	
	GComponent(const GComponent& );
	GComponent & operator = (const GComponent& );
	void GenerateID(  );
	std::queue <  std::shared_ptr<MBMessageInfo> >	fMessageQueue; /*!< Buffer/queue for incoming messages */

	bool fDoRun = true;
	bool fIsRunning = false;
	virtual void					API		RunComponent() final;
	void							API		SendMessage( std::shared_ptr<MBMessageInfo>  message_info ) const;
	std::shared_ptr<MBMessage>		API	 	SendMessageBlocking(	std::shared_ptr< MBMessageInfo> message_info,  const uint32_t timeout = 100 ) const;
	virtual void					API     ProcessTimeTick( const  MBTime_t *const timestamp );
	int    fSleepTimeMs = 150; /*!< The duration to wait between each time incomming messagees are processed*/

	MBComponentID_t fComponentID =  MBComponentID_t("");
};


#undef SendMessage
#undef SendMessageW


template<typename T>
inline void  
GComponent::SendMessageRaw( T  &payload, const string  request_channel, const string   reply_channel, const bool   exact_match ) const
{
	MBMessageT<T> msg( payload );
	SendMessage( msg, request_channel, reply_channel, exact_match );
}


template<typename T>
inline bool
GComponent::CheckPayload( const T * const payload )
{
	if ( payload == nullptr )
	{
		G_FATAL("Invalid datatype");
		return false;
	}
	else
	{
		return true;
	}
}
