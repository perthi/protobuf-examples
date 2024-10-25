// -*- mode: c++ -*-
#ifndef KFPBSubMessageSEMConfigSEM_H
#define KFPBSubMessageSEMConfigSEM_H


#include "KFPBMessageSEM.h"

struct KFEntityDevicePWM;

class  KFPBSubMessageSEMConfigSEM : public KFPBMessageSEM<SEMConfigSEM  >
{
	public:
		API KFPBSubMessageSEMConfigSEM();
		virtual API ~KFPBSubMessageSEMConfigSEM();
	//	void   API SetDummy(const char c );
	//	char   API GetDummy( ) const;
		
		// virtual bool   API  SerializeToString( string &msg ) override;
    	// virtual bool   API  SerializeFromString(const string dta) override;
		virtual void   API  Reset(SEMConfigSEM  *t)  override;
		virtual void   API  Reset( )  override;

	#if defined( __unix__ )  || defined (_WIN32 )
		virtual string      str() const override;
	#endif

};

#endif
