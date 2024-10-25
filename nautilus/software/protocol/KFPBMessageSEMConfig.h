// -*- mode: c++ -*-
#ifndef KFPBMESSAGESEMCONFIG_H
#define KFPBMESSAGESEMCONFIG_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBMessageSEM.h"


#include "KFPBSubMessageSEMDeviceAddress.h"
#include "KFPBSubMessageSEMDeviceAddress.h"
#include "KFPBSubMessageSEMConfigPWM.h"  
#include "KFPBSubMessageSEMConfigSensorAnalog.h"
#include "KFPBSubMessageSEMConfigSolenoid.h"      
#include "KFPBSubMessageSEMConfigVirtualXYMotors.h"
#include "KFPBSubMessageSEMConfigSEM.h"  
#include "KFPBSubMessageSEMConfigSensorBool.h"
#include "KFPBSubMessageSEMConfigStepperMotor.h"
#include "KFPBSubMessageSEMLinearUnitConversion.h"

#if defined( __unix__ )  || defined (_WIN32 )
struct KFEntityDevice;
struct KFEntityDeviceMotorStepper;
struct KFEntityDeviceMotorXY;
struct KFEntityDeviceSensorAnalogDirect;
struct KFEntityDeviceSensorBoolDirect;
struct KFEntityDeviceSensorLocal;
// struct KFEntityDeviceSensorVolume;
// struct KFEntityDeviceSensorTemperature;
struct KFEntityDevicePWM;
struct KFEntityDevicePWMPower;
struct KFEntityDevicePWMSignal;
struct KFEntityDeviceSolenoid;
struct KFSensorUnitConversion;
struct KFSensorThresholds;
#endif


class KFPBSubMessageSEMLinearUnitConversion;
class KFPBSubMessageSEMThresholds;


class  KFPBMessageSEMConfig : public KFPBMessageSEM< SEMConfig >
{
	public:
		API KFPBMessageSEMConfig();
		API virtual ~KFPBMessageSEMConfig();

        #if defined( __unix__ )  || defined (_WIN32 )
		bool API SetConfiguration( std::shared_ptr<KFEntityDevice>  config);
        #endif

		void API SetConfigType( const eSEM_CONFIGTYPE type );
		eSEM_CONFIGTYPE  API GetConfigType() const;

		KFPBSubMessageSEMDeviceAddress          API  *  GetDeviceAddress();
		KFPBSubMessageSEMConfigPWM              API  *  GetConfigPWM();
		KFPBSubMessageSEMConfigSensorAnalog   API  *  GetConfigSensorAnalog(); 
		KFPBSubMessageSEMConfigSolenoid         API  *  GetConfigSolenoid();    
		KFPBSubMessageSEMConfigVirtualXYMotors  API  *  GetConfigXY();
		KFPBSubMessageSEMConfigSEM              API  *  GetConfigSEM();
		KFPBSubMessageSEMConfigSensorBool       API  *  GetConfigSensorBool();  
		KFPBSubMessageSEMConfigStepperMotor     API  *  GetConfigStepper();

		virtual void     API   Reset( ) override;	
		virtual void     API   Reset( SEMConfig *t) override;	
		
		#if defined( __unix__ )  || defined (_WIN32 )
		virtual string   API   str() const override;
		#endif

	private:
		KFPBSubMessageSEMDeviceAddress fDeviceAddress;
		KFPBSubMessageSEMConfigPWM  fConfigPWM;
		KFPBSubMessageSEMConfigSensorAnalog  fConfigSensoranalog; 
		KFPBSubMessageSEMConfigSolenoid  fConfigSolenoid;    
		KFPBSubMessageSEMConfigVirtualXYMotors fConfigVirtualXY;
		KFPBSubMessageSEMConfigSEM        fConfigSEM;
		KFPBSubMessageSEMConfigSensorBool   fConfigSensorBool;  
		KFPBSubMessageSEMConfigStepperMotor fConfigStepper;


		#if defined( __unix__ )  || defined (_WIN32 )
		
		void  SetUnitConversion( const   KFSensorUnitConversion * const input, KFPBSubMessageSEMLinearUnitConversion *output );
        void  SetThresholds( const  KFSensorThresholds * const input,  KFPBSubMessageSEMThresholds *output ); 
		
//		void  SetUnitConversion( std::shared_ptr<KFSensorUnitConversion> input,  std::shared_ptr<KFPBSubMessageSEMLinearUnitConversion> output );
//        void  SetThresholds(     std::shared_ptr<KFSensorThresholds>     input,  std::shared_ptr<KFPBSubMessageSEMThresholds> output ); 
		
		void  SetConfiguration( std::shared_ptr<KFEntityDeviceMotorStepper >  config);
		void  SetConfiguration( std::shared_ptr<KFEntityDeviceMotorXY> dev );
		void  SetConfiguration( std::shared_ptr<KFEntityDeviceSensorAnalogDirect> dev);
		void  SetConfiguration( std::shared_ptr<KFEntityDeviceSensorLocal> dev);
		void  SetConfiguration( std::shared_ptr<KFEntityDeviceSensorBoolDirect> dev);
//		void  SetConfiguration( std::shared_ptr<KFEntityDeviceSensorVolume> dev);
//		void  SetConfiguration( std::shared_ptr<KFEntityDeviceSensorTemperature> dev);
		void  SetConfiguration( std::shared_ptr<KFEntityDevicePWM> dev);
		void  SetConfiguration( std::shared_ptr<KFEntityDeviceSolenoid> dev);
		#endif

};


#endif
