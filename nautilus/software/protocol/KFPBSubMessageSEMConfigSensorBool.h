// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMCONFIGSENSORBOOL_H
#define KFPBSUBMESSAGESEMCONFIGSENSORBOOL_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEM.h"

class  KFPBSubMessageSEMConfigSensorBool : public KFPBMessageSEM< SEMConfigSensorBool >
{
	public:
		API KFPBSubMessageSEMConfigSensorBool();
		virtual API ~KFPBSubMessageSEMConfigSensorBool();

		void API SetSignalType( const eSENSOR_INPUT_TYPE  type );
		void API SetActiveHigh(const bool val ); 
		void API SetAlarm(const bool val);
		
		bool API HasSignalType(  ) const;
		bool API HasActiveHigh(  ) const; 
		bool API HasAlarm( ) const;
		bool API HasDeviceIDAux( ) const;

	#if defined( __unix__ )  || defined (_WIN32 )
		void API SetDeviceIDAux( const string device_id );
		string  API  GetDeviceIDAux() const;
	#endif
   		virtual void     GetDeviceIDAux(char *id, const size_t max_size ) const;
        virtual void     SetDeviceIDAux(const char *id, const size_t max_size );

		eSENSOR_INPUT_TYPE API  GetSignalType() const;
		bool    API  GetActiveHigh() const; 
		bool    API  GetAlarm( ) const;
		virtual void     API    Reset(  SEMConfigSensorBool  *)  override;
		virtual void     API    Reset( )  override;

#if defined( __unix__ )  || defined (_WIN32 )
	    virtual string   API    str() const override;
#endif

};

#endif
