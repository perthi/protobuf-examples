// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMCONFIGSTEPPERMOTOR_H
#define KFPBSUBMESSAGESEMCONFIGSTEPPERMOTOR_H


#include    "KFPBMessageSEM.h"
#include    "KFPBSubMessageSEMStepUnitConversion.h"

class  KFPBSubMessageSEMConfigStepperMotor : public KFPBMessageSEM< SEMConfigStepperMotor >
{
	public:
		API KFPBSubMessageSEMConfigStepperMotor();
		virtual API ~KFPBSubMessageSEMConfigStepperMotor();
		virtual void     API    Reset(SEMConfigStepperMotor *)  override;
		virtual void     API    Reset( )  override;
		virtual void Set( SEMConfigStepperMotor  *ptr) override;

		KFPBSubMessageSEMStepUnitConversion API *  GetStepUnitConversion();
 
		void   API  SetDirectionPositive( const  eDIRECTION dir );
		void   API  SetDirectionHome( const eDIRECTION dir ); 
		
		eDIRECTION GetDirectionHome() const;
		eDIRECTION GetDirectionPositive() const;

		bool   API  HasDirectionHome();


		void   API  SetNegativeEndStop(const float val);
		void   API  SetPositiveEndStop(const float val);
		
		
		
		void   API  SetMaxSpeed(const float val);
		void   API  SetSpeed(const float val);
		void   API  SetMaxAccellleration(const float val);
	    void   API  SetAccellleration(const float val);
		void   API  SetMaxCurrent(const float val);
		void   API  SetCurrent(const float val);
		void   API  SetInactiveTimeout(const float val);
		void   API  SetInativeCurrent(const float val);
		void   API  SetHomeValue(const float val);
		void   API  SetHomeId(const string id);
		void   API  SetNegativeEndStopId(const string id);
		void   API  SetPositiveEndStopId(const string id);

		bool  API  HasNegativeEndstop() const;
		bool  API  HasPositiveEndstop() const;

		float     API  GetNegativeEndStop() const;
		float     API  GetPositiveEndStop() const;
		float     API  GetMaxSpeed() const;
		float     API  GetSpeed() const;
		float     API  GetMaxAccellleration() const;
	    float     API  GetAccellleration() const;
		float     API  GetMaxCurrent() const;
		float     API  GetCurrent() const ;
		float     API  GetInactiveTimeout( ) const;
		float     API  GetInativeCurrent( ) const;
		float     API  GetHomeValue( ) const;
		string    API  GetHomeId( ) const;
		string    API  GetNegativeEndStopId( ) const;
		string    API  GetPositiveEndStopId( ) const;

		#if defined( __unix__ )  || defined (_WIN32 )		
		virtual string   API    str() const override;
		#endif

	private:
		KFPBSubMessageSEMStepUnitConversion fStepUnitConversion;

};

#endif
