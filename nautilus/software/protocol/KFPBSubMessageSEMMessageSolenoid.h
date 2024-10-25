// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGESOLENOID_H
#define KFPBSUBMESSAGESEMMESSAGESOLENOID_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEMMessageCommon.h"
#include   "KFProtocolEnums.h"


class  KFPBSubMessageSEMMessageSolenoid : 
public KFPBMessageSEMMessageCommon < SEMMessageSolenoid,  
eSEM_SOLENOID_ERROR_CODE,  eSEM_SOLENOID_STATE >
{
	public:
		KFPBSubMessageSEMMessageSolenoid();
		virtual ~KFPBSubMessageSEMMessageSolenoid();
		virtual  void   Reset(  ) override;
		virtual  void   Reset( SEMMessageSolenoid *t) override;

	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override;

	#endif
};

#endif
