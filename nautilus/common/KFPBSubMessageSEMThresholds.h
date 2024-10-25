// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMTHRESHOLDS_H
#define KFPBSUBMESSAGESEMTHRESHOLDS_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include   "KFPBMessageSEM.h"

class  KFPBSubMessageSEMThresholds : public KFPBMessageSEM< SEMThresholds >
{
	public:
	API KFPBSubMessageSEMThresholds();
	virtual API  ~KFPBSubMessageSEMThresholds();

	virtual void   API  Reset(SEMThresholds *t)  override;
	virtual void   API  Reset( )  override;

	void   API  SetALarmLow( const float val, const bool has_value  );
	void   API  SetWarningLow(const float val, const bool has_value    );
	void   API  SetWarningHigh( const float val,   const bool has_value   );
	void   API  SetAlarmHigh( const float val, const bool has_value    );
	float  API  GetALarmLow(  );
	float  API  GetWarningLow( );
	float  API  GetWarningHigh( );
	float  API  GetAlarmHigh(  );

	bool   API  HasALarmLow( ) const;
	bool   API  HasWarningLow( ) const;
	bool   API  HasWarningHigh( ) const;
	bool   API  HasAlarmHigh( ) const;

	void   API  SetHasALarmLow( const bool val );
	void   API  SetHasWarningLow( const bool val );
	void   API  SetHasWarningHigh( const bool val );
	void   API  SetHasAlarmHigh( const bool val );


#if defined( __unix__ )  || defined (_WIN32 )
	virtual string   API   str() const override;
	static  string   API    str( KFPBSubMessageSEMThresholds *t );
#endif

};

#endif
