// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGESTATUS_H
#define KFPBSUBMESSAGESEMMESSAGESTATUS_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEMMessageCommon.h"
#include    "KFProtocolEnums.h"


class  KFPBSubMessageSEMMessageStatus : 
public KFPBMessageSEMMessageCommon  < SEMMessageStatus, 
	eSEM_ERROR_CODE,  eSEM_SEM_STATE  >
{
	public:
		KFPBSubMessageSEMMessageStatus();
		virtual ~KFPBSubMessageSEMMessageStatus();
		void SetConfigurationCRC(const int32_t crc);
		int32_t                GetConfigurationCRC() const;
		bool  HasConfigurationCRC() const;

		virtual  void   Reset(  ) override;
		virtual  void   Reset( SEMMessageStatus *t) override;

	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override {return "MessageStatus"; };
	#endif
};

#endif
