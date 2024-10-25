// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGESENSOR_H
#define KFPBSUBMESSAGESEMMESSAGESENSOR_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/



#include    "KFPBMessageSEMMessageCommon.h"
#include    "KFProtocolEnums.h"


class  KFPBSubMessageSEMMessageSensor :  public KFPBMessageSEMMessageCommon < SEMMessageSensor, eSEM_SENSOR_ERROR_CODE, eSEM_SENSOR_STATE  >
{
	public:
		KFPBSubMessageSEMMessageSensor();
		virtual ~KFPBSubMessageSEMMessageSensor();
		void SetValueConverted( float val);
		void SetValueRaw( const int32_t raw_value );
		void SetAlarmStatus( eSEM_SENSOR_ALARM_STATUS status);
		float                     GetValueConverted( ) const;
		int32_t                   GetValueRaw(  ) const;
		eSEM_SENSOR_ALARM_STATUS  GetAlarmStatus() const;
		bool  HasValueRaw() const;
		virtual  void   API   Reset(  ) override;
    	virtual  void   API   Reset( SEMMessageSensor *t) override;
	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override;

	#endif
};

#endif
