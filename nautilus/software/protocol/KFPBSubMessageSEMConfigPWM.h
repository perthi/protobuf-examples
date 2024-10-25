// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMCONFIGPWM_H
#define KFPBSUBMESSAGESEMCONFIGPWM_H

#include    "KFPBMessageSEM.h"
#include    "KFPBSubMessageSEMLinearUnitConversion.h"


class  KFPBSubMessageSEMConfigPWM :  public  KFPBMessageSEM<  SEMConfigPWM>
{
	public:
		API  KFPBSubMessageSEMConfigPWM();
		API  virtual ~KFPBSubMessageSEMConfigPWM();
		KFPBSubMessageSEMLinearUnitConversion API * GetConversion();
		virtual void     API     Set( SEMConfigPWM *t) override;
		void             API   SetMinLevel(const float val);
		void             API   SetMaxLevel( const float val);
		float            API   GetMinLevel() const;
		float            API   GetMaxLevel() const ;
		
		bool 			API     HasMaxLevel() const;
		bool            API     HasMinLevel() const;

		bool            API    HasUnitConversion() const;
		
		virtual void     API    Reset( SEMConfigPWM  *)  override;
		virtual void     API    Reset( )  override;
	
	#if defined( __unix__ )  || defined (_WIN32 )
		virtual string   API    str() const override;
	#endif


	private:
		KFPBSubMessageSEMLinearUnitConversion fLinearUnitConversion;	
};

#endif
