// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGEXYMOTOR_H
#define KFPBSUBMESSAGESEMMESSAGEXYMOTOR_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEMMessageCommon.h"
#include   "KFProtocolEnums.h"

class  KFPBSubMessageSEMMessageXYMotor : 
public KFPBMessageSEMMessageCommon < 
			SEMMessageXYMotor,   
			eSEM_XY_MOTOR_ERROR_CODE, eSEM_XY_MOTOR_STATE >
{
	public:
		KFPBSubMessageSEMMessageXYMotor();
		virtual ~KFPBSubMessageSEMMessageXYMotor();
		void SetXYPosition( const float x, const float y);
		void GetXYPosition( float &x, float &y);
		float GetValueXPosition() const { return fCmd->value_x_position; };
		float GetValueYPosition() const { return fCmd->value_y_position; };
		virtual  void   Reset(  ) override;
		virtual  void   Reset( SEMMessageXYMotor *t) override;

	 #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
		virtual string strOneLine() const override;


	#endif

};

#endif
