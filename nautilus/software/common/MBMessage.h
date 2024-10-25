// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


///////////////////////////////////////////////////////////
//  MBMessage.h
//  Implementation of the Class MBMessage
//  Created on:      13-mar-2018 14.38.46
//  Original author: pth
///////////////////////////////////////////////////////////

#pragma once

#include <common/FDefinitions.h>
#include <vector>
using   std::vector;

#include  <common/MBMessagePayload.h>
#include  <common/MBMessagePayloadT.h> 
#include  <common/GIDGenerator.h>
#include  <utilities/GException.h>
#include  <logging/LLogApi.h>

using namespace LOGMASTER;

#include <common/MBEnums.h>
#include <common/MBDataTypes.h>
#include <utilities/GPrintable.h>
#include <utilities/GUtilities.h>


class   MBMessage : public GPrintable
{
	public:
	inline API  MBMessage( const string dummy_message = "" );
	virtual  inline  string str() const override;
	inline virtual std::shared_ptr<MBMessagePayload> 	API 	GetPayload() { return fPayload; };

	template<typename T>
        inline  T   *  	ExtractRawPayload( ) const;
	
	template<typename T>
	inline bool HasPayloadType() const;

	inline bool                 IsRequestType( const eMESSAGE_REQUEST request );
	inline void	                SetPayload( std::shared_ptr<MBMessagePayload>  dta ) { fPayload = dta; };
	inline int			        GetConversationID() const;
	inline string		        GetMessageID() const { return fMessageID;  };
	inline void		            SetConversationID( const int id ) { fConversationID = id; }
	inline string		        GetDummyMessage() const { return fMessage; }; /*!< For debugging only */
	
	MBComponentID_t fComponentID;       /*!<  Component ID of the originator of this message   */
	vector<string> fComponentIDHistory;  /*!<  History in case the message travles through several components */
	string fMessage = " ";               /*!<  Arbritrary message ID > */
	string fMessageID = "";              /*!<  Unique message ID > */	
	string fOriginator = "";             /*!< The name of the component that genegerated this message> */


	/** The conversation ID keeps is used to make sure that we keep track of which
	 * conversation this message is a reply to */
	int fConversationID = 0;
	std::shared_ptr<MBMessagePayload> fPayload = nullptr; /*!< Optionally the user can attach payload data to the message >*/
};


MBMessage::MBMessage(const string  message_s ) : fComponentID(), 
											fComponentIDHistory(),
											fMessage(message_s), fMessageID(""),
											fOriginator(""),
											fConversationID(0),
											fPayload(nullptr)
{
	fMessageID = GIDGenerator::Instance()->CreateUniqueID("MESSAGE_ID");
}


inline string 
MBMessage::str() const
{
	std::stringstream buffer;
	buffer <<  g_utilities()->TabAlign( "component ID of originator:" )    <<  fComponentID.str() << "\n";
	buffer <<  g_utilities()->TabAlign( "Originator Name;" ) <<  fOriginator << "\n";	
	buffer <<  g_utilities()->TabAlign( "Message ID" )  << fMessageID << "\n" ;
	buffer <<  g_utilities()->TabAlign( "Converation ID" ) << fConversationID <<  "\n";
	buffer <<  g_utilities()->TabAlign( "Debug message:" )   <<  fMessage << "\n";
	
	if ( fPayload != nullptr )
	{
		buffer << g_utilities()->TabAlign( "PayloadType:" ) << fPayload->fPayloadType << "\n";
	}
	else
	{
		buffer << g_utilities()->TabAlign( "PayloadType:" ) << "[nullptr]" << "\n";
	}

	return buffer.str();
}




/** Return a raw pointer to the payload or a zero pointr if the 
actual paylaod and the requested payload differs*/
template<typename T>
T * 
MBMessage::ExtractRawPayload() const
{
    std::shared_ptr<MBMessagePayloadT<T> >  payload = std::dynamic_pointer_cast<MBMessagePayloadT< T   >>  (fPayload);
    if ( payload == nullptr )
    {
        G_INFO("Dynamic pointer cast failed attemting cast to (type = %s)", typeid(T).name() );
        return nullptr;
    }
    else
    {
        std::shared_ptr<T> payload_shrptr = (*payload).fPayload;
        
        if ( payload_shrptr == nullptr )
        {
            G_WARNING("Zero pointer");
            return nullptr;
        }
        else
        {
            return payload_shrptr.get();
        }
        
    }
    return nullptr;
}



template<typename T>
inline bool 
MBMessage::HasPayloadType() const
{
	return  ExtractRawPayload<T>() == nullptr ? false : true;
}



inline bool 
MBMessage::IsRequestType( const eMESSAGE_REQUEST request )
{
	if ( HasPayloadType< eMESSAGE_REQUEST>() == false )
	{
		return false;
	}
	else
	{
		const eMESSAGE_REQUEST * const tmp = ExtractRawPayload<eMESSAGE_REQUEST>();

		return *tmp == request ? true : false;
	}
}



int
MBMessage::GetConversationID() const
{
	return fConversationID;
}

