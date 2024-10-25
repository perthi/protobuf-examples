// -*- mode: c++ -*-
#ifndef KFPBMESSAGESEMONEOFMESSAGE_H
#define KFPBMESSAGESEMONEOFMESSAGE_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEM.h"
#include    "KFPBMessageSEMMessage.h"
#include    "KFPBMessageSEMCommand.h"
#include    "KFPBMessageSEMConfig.h"


class  KFPBMessageSEMOneOfMessage : public  KFPBMessageSEM< SEMOneOfMessage >
{
	public:
		KFPBMessageSEMOneOfMessage();
		virtual ~KFPBMessageSEMOneOfMessage();


		KFPBMessageSEMMessage   API  * GetPBMessage();
		KFPBMessageSEMCommand   API  * GetPBCommand();
		KFPBMessageSEMConfig    API  * GetPBConfig();
  		virtual void  API    Reset( SEMOneOfMessage  *t) override;
    	virtual void  API    Reset () override;
		ePB_ONEOF_TYPE API  GetMessageType() const;
		void    API SetMessageType( const ePB_ONEOF_TYPE message_type );
		void SetConfigType( eSEM_CONFIGTYPE type );

		void SetSequenceID(const int32_t id);
		int32_t GetSequenceID() const;


  	#if defined( __unix__ )  || defined (_WIN32 )
    	virtual string      str() const override;
		virtual string strOneLine() const override;

		virtual bool   SerializeFromString( const string  dta ) override;
    #endif
		virtual bool   SerializeFromString( const  uint8_t * const dta, const int size) override;

	private:
		KFPBMessageSEMMessage  fMessage;
		KFPBMessageSEMCommand  fCommand;
		KFPBMessageSEMConfig   fConfig;
};

#endif
