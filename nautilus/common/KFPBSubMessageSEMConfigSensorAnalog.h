// -*- mode: c++ -*-
#ifndef KFPBSubMessageSEMConfigSensorAnalog_H
#define KFPBSubMessageSEMConfigSensorAnalog_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEM.h"
#include    "KFPBSubMessageSEMThresholds.h"
#include    "KFPBSubMessageSEMLinearUnitConversion.h"

class  KFPBSubMessageSEMConfigSensorAnalog : public KFPBMessageSEM< SEMConfigSensorAnalog >
{
	public:
		API  KFPBSubMessageSEMConfigSensorAnalog();
		API  virtual ~KFPBSubMessageSEMConfigSensorAnalog();
		KFPBSubMessageSEMThresholds API * GetThresholds();
		KFPBSubMessageSEMLinearUnitConversion API * GetConversion();
		void API    SetInputType( const eSENSOR_INPUT_TYPE  input );
		eSENSOR_INPUT_TYPE API GetInputType() const;

		bool HasUnitConversion() const;

#if defined( __unix__ )  || defined (_WIN32 )
		string  API GetDeviceIDAux() const;
		void API SetDeviceIDAux( const string device_id );
#endif
		virtual void     GetDeviceIDAux(char *id, const size_t max_size ) const;
        virtual void     SetDeviceIDAux(const char *id, const size_t max_size );

		bool API  HasInputType() const  		  { return fCmd->has_input_type; };
		bool API  HasThresholds() const 		  { return fCmd->has_thresholds; };
		bool API  HasDeviceId()  const  		  { return fCmd->has_device_id_aux; };
		bool API  HasLinearUnitConversion() const { return fCmd->has_conversion; };

		virtual void     API    Reset( SEMConfigSensorAnalog  *)  override;
		virtual void     API    Reset( )  override;
		virtual void    API     Set( SEMConfigSensorAnalog *t) override;

#if defined( __unix__ )  || defined (_WIN32 )
		virtual string   API    str() const override;
#endif

	private:
		KFPBSubMessageSEMThresholds fThresholds;
		KFPBSubMessageSEMLinearUnitConversion fLinearUnitConversion;

};

#endif
