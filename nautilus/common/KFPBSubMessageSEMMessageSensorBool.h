// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGESENSORBOOL_H
#define KFPBSUBMESSAGESEMMESSAGESENSORBOOL_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEMMessageCommon.h"
#include   "KFProtocolEnums.h"

class  KFPBSubMessageSEMMessageSensorBool : 
public  KFPBMessageSEMMessageCommon < SEMMessageSensorBool,  
eSEM_BOOL_SENSOR_ERROR_CODE, eSEM_BOOL_SENSOR_STATE  >
{
	public:
		KFPBSubMessageSEMMessageSensorBool();
		virtual ~KFPBSubMessageSEMMessageSensorBool();
		void SetValueConverted( int32_t val);
		void SetValueRaw( const int32_t raw_value );
		int32_t                     GetValueConverted( ) const;
		int32_t                   GetValueRaw(  ) const;
		bool  HasValueRaw() const;

		virtual  void   API   Reset(  ) override;
    	virtual  void   API   Reset( SEMMessageSensorBool *t) override;

	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override;

	#endif

};

#endif
