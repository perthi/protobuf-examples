// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGECOMMANDSTATUSREPLY_H
#define KFPBSUBMESSAGESEMMESSAGECOMMANDSTATUSREPLY_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/



#include    "KFPBMessageSEMMessageCommon.h"
#include   "KFProtocolEnums.h"


class  KFPBSubMessageSEMMessageCommandStatusReply : 
public KFPBMessageSEMMessageCommon< SEMMessageCommandStatusReply, eSEM_COMMAND_ERROR_CODE  >
{
	public:
		KFPBSubMessageSEMMessageCommandStatusReply();
		virtual ~KFPBSubMessageSEMMessageCommandStatusReply();
		bool  HasStatusCode() const;
		virtual  void   Reset(  ) override;
		virtual  void   Reset( SEMMessageCommandStatusReply *t) override;

	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override;


	#endif
};

#endif
