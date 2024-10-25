// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <string>
using std::string;

#include <future>
#include <common/MBMessage.h>
#include <utilities/GPrintable.h>

class MBMessage;

#include <memory>


struct MBMessageInfo : public GPrintable
{
	inline MBMessageInfo(std::shared_ptr<MBMessage> msg, const string request, const string reply =  "" );
	virtual  inline  string str() const override;
	inline void SetPromise(MBMessage &m);
	inline void SetPromise(std::shared_ptr<MBMessage> m);
	string fRequesChannel; /*!< The channel of this request, i.e the originating channel of the message */

	 /*!< The channel where the sender expect a reply. If not, set the reply channel equal to the request channel. The
	 reciver is free to ignore the reply channel and send the respons over another channel*/
	string fReplyChannel; 
	
	bool   fExactMatch = false;
	bool   fIsBlocking = false; /*!< Wether or not the recipient must reply to this message(i.e the call is blocking for the sender) */
	std::shared_ptr<MBMessage>  fMessage;
	std::promise<  std::shared_ptr<MBMessage > >  fPromise;
};


inline 
MBMessageInfo::MBMessageInfo( std::shared_ptr<MBMessage> msg, const string request, const string reply )  : 
	fRequesChannel( request ), 
	fReplyChannel(reply),
	fMessage( msg ),
	fPromise()
{
    if (reply == "")
    {
        fReplyChannel = request;
    }
}


inline string 
MBMessageInfo::str() const
{
    std::stringstream buffer;
    buffer  <<   g_utilities()->TabAlign("Out channel:") << fRequesChannel << endl;
    buffer  <<   g_utilities()->TabAlign( "Reply channle:" ) << fReplyChannel << endl;
    buffer  <<   fMessage->str() << endl;
    return buffer.str();
}


inline void 
MBMessageInfo::SetPromise( MBMessage & m )
{
    fPromise.set_value(std::make_shared<MBMessage>(m) );
}


inline void 
MBMessageInfo::SetPromise( std::shared_ptr<MBMessage> m )
{
    fPromise.set_value(m);
}


