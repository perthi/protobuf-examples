// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGECONFIGURATIONDSTATUSREPLY_H
#define KFPBSUBMESSAGESEMMESSAGECONFIGURATIONDSTATUSREPLY_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/




#include    "KFPBMessageSEMMessageCommon.h"
#include   "KFProtocolEnums.h"


class  KFPBSubMessageSEMMessageConfigurationStatusReply : 
public KFPBMessageSEMMessageCommon< SEMMessageConfigurationStatusReply, eSEM_CONFIGURATION_ERROR_CODE  >
{
	public:
		KFPBSubMessageSEMMessageConfigurationStatusReply();
		virtual ~KFPBSubMessageSEMMessageConfigurationStatusReply();
		virtual  void   Reset(  ) override;
		virtual  void   Reset( SEMMessageConfigurationStatusReply  *t) override;

	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override;

	#endif
};




#endif
