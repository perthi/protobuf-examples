// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMCRC_H
#define KFPBSUBMESSAGESEMCRC_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEM.h"

class  KFPBSubMessageSEMCrc : public KFPBMessageSEM< SEMCrc >
{
	public:
		API KFPBSubMessageSEMCrc();
		virtual API ~KFPBSubMessageSEMCrc();
		void API SetCrc(const int32_t crc );
		int32_t API GetCrc() const;

		virtual void   API  Reset(SEMCrc *t)  override;
		virtual void   API  Reset(  )  override;

	#if defined( __unix__ )  || defined (_WIN32 )
		virtual string      str() const override;
	#endif
};

#endif
