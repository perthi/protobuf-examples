// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMSTEPUNITCONVERSION_H
#define KFPBSUBMESSAGESEMSTEPUNITCONVERSION_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include    "KFPBMessageSEM.h"


class  KFPBSubMessageSEMStepUnitConversion : public    KFPBMessageSEM< SEMStepUnitConversion >  
{
	public:
		API KFPBSubMessageSEMStepUnitConversion();
		virtual API  ~KFPBSubMessageSEMStepUnitConversion();
		virtual void      API   Reset( SEMStepUnitConversion *t) override;
		virtual void      API   Reset( ) override;
		
		void   API  SetSIUnit( const int unit );
		
		int    API  GetSIUnit() const;
		
		void   API  SetUnitPerStep( const float factor );
		float  API  GetUnitPerStep( ) const; 

#if defined( __unix__ )  || defined (_WIN32 )
		virtual string    API   str() const override;
		static  string    API   str(SEMStepUnitConversion *t); 		
#endif

};

#endif
