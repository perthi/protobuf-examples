// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMCONFIGVIRTUALXYMOTORS_H
#define KFPBSUBMESSAGESEMCONFIGVIRTUALXYMOTORS_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEM.h"

class  KFPBSubMessageSEMConfigVirtualXYMotors :public KFPBMessageSEM< SEMConfigVirtualXYMotors >
{
	public:
		API KFPBSubMessageSEMConfigVirtualXYMotors();
		virtual API ~KFPBSubMessageSEMConfigVirtualXYMotors();
		
		void    API SetDeviceX( const string device ) ;
		void    API SetDeviceY( const string device ) ;
		string    API GetDeviceX() const ;
		string    API GetDeviceY() const ;

		virtual void   API  Reset( SEMConfigVirtualXYMotors *t)  override;
		virtual void   API  Reset(  )  override;
	
	#if defined( __unix__ )  || defined (_WIN32 )
		virtual string   API    str() const override;
	#endif
	
};

#endif
