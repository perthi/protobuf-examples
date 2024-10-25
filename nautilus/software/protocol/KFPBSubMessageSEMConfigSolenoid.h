// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMCONFIGSOLENOID_H
#define KFPBSUBMESSAGESEMCONFIGSOLENOID_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include    "KFPBMessageSEM.h"


class  KFPBSubMessageSEMConfigSolenoid : public KFPBMessageSEM< SEMConfigSolenoid  >
{
	public:
		API KFPBSubMessageSEMConfigSolenoid();
		virtual API ~KFPBSubMessageSEMConfigSolenoid();
		
		virtual void     API    Reset( SEMConfigSolenoid  *)  override;
		virtual void     API    Reset( )  override;

		void API SetMaxCurrent( const float val);
		void API SetActivateCurrent( const float val);
		void API SetHoldCurrent( const float val);
		
		float API GetMaxCurrent() const;
		float API GetActivateCurrent() const;
		float API GetHoldCurrent( ) const;

		#if defined( __unix__ )  || defined (_WIN32 )
		virtual string   API    str() const override;
		#endif
};

#endif
