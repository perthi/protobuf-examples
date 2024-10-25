// -*- mode: c++ -*-
/***********************************************************************************
 * This file is property of and copyright by Kongsberg Ferrotech  2019             *
 *                                                                                 *
 * Author: Per Thomas Hille <pth@embc.no> for Semcon Devotek & Konsgberg Ferrotech *
 * Contributors are mentioned in the code where appropriate.                       *
 * Please report bugs to pth@embc.no                                               *
 ***********************************************************************************/

#include "KFPBMessageSEMConfig.h"


#if defined( __unix__ )  || defined (_WIN32 )
#include  <configuration/KFEntityDevice.h>
#include  <configuration/KFEntityDeviceSensorAnalogDirect.h>
#include  <configuration/KFEntityDeviceSensorBoolDirect.h>
#include  <configuration/KFEntityDeviceSensorLocal.h>
// #include  <configuration/KFEntityDeviceSensorVolume.h>
// #include  <configuration/KFEntityDeviceSensorTemperature.h>
#include  <configuration/KFEntityDevicePWM.h>
#include  <configuration/KFEntityDevicePWMPower.h>
#include  <configuration/KFEntityDevicePWMSignal.h>
#include  <configuration/KFEntityDeviceMotorStepper.h>
#include  <configuration/KFEntityDeviceMotorXY.h>
#include  <configuration/KFEntityDeviceSolenoid.h>
#include  <configuration/KFSensorUnitConversion.h>
#include  <configuration/KFSensorThresholds.h>
#endif

#include "KFProtocolUtilities.h"
#include "KFPBSubMessageSEMLinearUnitConversion.h"
#include "KFPBSubMessageSEMThresholds.h"

KFPBMessageSEMConfig::KFPBMessageSEMConfig() : KFPBMessageSEM(  ( pb_field_t *  )SEMConfig_fields ), fDeviceAddress(),
                                                fConfigPWM(), 
                                                fConfigSensoranalog(), 
                                                fConfigSolenoid(), 
                                                fConfigVirtualXY(), 
                                                fConfigSEM(), 
                                                fConfigSensorBool(), 
                                                fConfigStepper()
{
    fDeviceAddress.Set( &fCmd->address);
    fConfigPWM.Set( &fCmd->device.pwm) ;
    fConfigSensoranalog.Set(&fCmd->device.sensor_analog);
    fConfigSolenoid.Set(&fCmd->device.solenoid);
    fConfigVirtualXY.Set(&fCmd->device.motor_xy);
    fConfigSEM.Set( &fCmd->device.sem);
    fConfigSensorBool.Set( &fCmd->device.sensor_bool);
    fConfigStepper.Set(&fCmd->device.motor_stepper);
    Reset();
}



KFPBMessageSEMConfig::~KFPBMessageSEMConfig()
{

}


void   
KFPBMessageSEMConfig::SetConfigType( const eSEM_CONFIGTYPE type )
{
    fCmd->which_device = (pb_size_t)type;

    switch(type)
    {
        case eSEM_CONFIGTYPE::SENSOR_ANALOG:
            fConfigSensoranalog.Set( &fCmd->device.sensor_analog ); 
            break;
        case eSEM_CONFIGTYPE::SEM:
            fConfigSEM.Set( &fCmd->device.sem);
            break;
        case eSEM_CONFIGTYPE::MOTOR_STEPPER:
            fConfigStepper.Set( &fCmd->device.motor_stepper );
            break;
        case eSEM_CONFIGTYPE::MOTOR_XY:
            fConfigVirtualXY.Set(&fCmd->device.motor_xy);
            break;
        case eSEM_CONFIGTYPE::SOLENOID:
            fConfigSolenoid.Set(&fCmd->device.solenoid); 
            break;
        case eSEM_CONFIGTYPE::PWM:
            fConfigPWM.Set( &fCmd->device.pwm);
            break;
        case eSEM_CONFIGTYPE::SENSOR_BOOL:
             fConfigSensorBool.Set( &fCmd->device.sensor_bool);
             break;
        case eSEM_CONFIGTYPE::INVALID:
        case eSEM_CONFIGTYPE::UNKNOWN:
        
        default:
            //MESSAGE_ERROR("Unknown type %d", (int)type );
            break;
    }
}



eSEM_CONFIGTYPE  
KFPBMessageSEMConfig::GetConfigType() const
{
    return (eSEM_CONFIGTYPE)fCmd->which_device;  
}



KFPBSubMessageSEMDeviceAddress *  
KFPBMessageSEMConfig::GetDeviceAddress()
{
    return &fDeviceAddress;
}



KFPBSubMessageSEMConfigPWM  *  
KFPBMessageSEMConfig::GetConfigPWM()
{
    return &fConfigPWM;
}


KFPBSubMessageSEMConfigSensorAnalog   *
KFPBMessageSEMConfig::GetConfigSensorAnalog()
{
    return &fConfigSensoranalog;
}


KFPBSubMessageSEMConfigSolenoid  *  
KFPBMessageSEMConfig::GetConfigSolenoid()
{
    return  &fConfigSolenoid;
}


KFPBSubMessageSEMConfigVirtualXYMotors  *  
KFPBMessageSEMConfig::GetConfigXY()
{
    return &fConfigVirtualXY;
}


KFPBSubMessageSEMConfigSEM    *  
KFPBMessageSEMConfig::GetConfigSEM()
{
    return &fConfigSEM;
}


KFPBSubMessageSEMConfigSensorBool  *  
KFPBMessageSEMConfig::GetConfigSensorBool()
{
    return &fConfigSensorBool;
}


KFPBSubMessageSEMConfigStepperMotor   *  
KFPBMessageSEMConfig::GetConfigStepper()
{
    return  &fConfigStepper;
}


void 
KFPBMessageSEMConfig::Reset(  SEMConfig  * t )
{
    t->which_device  = (int)eSEM_CONFIGTYPE::UNKNOWN;
    fDeviceAddress.Reset();
    fConfigPWM.Reset();
	fConfigSensoranalog.Reset(); 
	fConfigSolenoid.Reset();    
	fConfigVirtualXY.Reset();
	fConfigSEM.Reset();
	fConfigSensorBool.Reset();  
	fConfigStepper.Reset();
}


void 
KFPBMessageSEMConfig::Reset(  )
{
    Reset(fCmd);
}


/// Functions used only on Windows and Linux
#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBMessageSEMConfig::str() const
{
    std::stringstream buffer;
    
    buffer << fDeviceAddress.str() << endl;;
    
    switch( fCmd->which_device )
    {
        case SEMConfig_pwm_tag:
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "PWM" << endl;
            buffer << fConfigPWM.str();
            break;
        case SEMConfig_sensor_analog_tag:
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "analog SENSOR" << endl;
            buffer << fConfigSensoranalog.str(); 
            break;
        case SEMConfig_solenoid_tag:    
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "SOLENOID" << endl;
            buffer << fConfigSolenoid.str();
            break;
        case SEMConfig_motor_xy_tag:
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "VIRTUAL XY MOTOR" << endl;
            buffer << fConfigVirtualXY.str();
            break;
        case SEMConfig_sem_tag:
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "SEM" << endl;
	        buffer << fConfigSEM.str();
            break;
        case SEMConfig_sensor_bool_tag:
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "BOOLEAN SENSOR" << endl;
            buffer << fConfigSensorBool.str();  
            break;
	    case SEMConfig_motor_stepper_tag:
            buffer << g_utilities()->TabAlign("CONFIG_TYPE:") << "STEPPER MOTOR" << endl;
            buffer << fConfigStepper.str();
            break;
        default:
            buffer << "ERROR, unknown config type" << fCmd->which_device << endl;
            break;
    }
	return buffer.str();
}


/**@{*/ 
/** Functions for mapping of configurations from the configuaration manager. These configurations
 * are read in from an XML files
 * @param dev[in] Device enity retrieved form the configuration manager. Please not that these functions can only be used
 * under Windows or Linux (not embedded) */
bool
KFPBMessageSEMConfig::SetConfiguration(  std::shared_ptr<KFEntityDevice> dev )
{
  ///  XML_ASSERT_EXEPTION(dev != nullptr, "Dev = zerop pointer");
    fDeviceAddress.SetConfiguration( &dev->fAddress,   dev->fDeviceType  );

    std::shared_ptr<KFEntityDeviceMotorStepper>  stepper = std::dynamic_pointer_cast< KFEntityDeviceMotorStepper>(dev);


    if(stepper != nullptr)
    {
        SetConfiguration(  stepper  );
        return true;
    }

    std::shared_ptr<KFEntityDeviceMotorXY> xy =  std::dynamic_pointer_cast< KFEntityDeviceMotorXY>(dev);

    if( xy!= nullptr )
    {
       SetConfiguration(xy);
       return true;
    }


    std::shared_ptr<KFEntityDeviceSolenoid> solenoid =  std::dynamic_pointer_cast< KFEntityDeviceSolenoid>(dev);

    if(solenoid != nullptr )
    {
       SetConfiguration(solenoid);
    }


    std::shared_ptr<KFEntityDeviceSensorAnalogDirect> s_a =  std::dynamic_pointer_cast< KFEntityDeviceSensorAnalogDirect>(dev);

    if(s_a != nullptr )
    {
       SetConfiguration( s_a );
    }

    std::shared_ptr<KFEntityDeviceSensorLocal> s_l =  std::dynamic_pointer_cast< KFEntityDeviceSensorLocal>(dev);

    if(s_l != nullptr )
    {
       SetConfiguration( s_l );
    }


    std::shared_ptr<KFEntityDeviceSensorBoolDirect> s_b =  std::dynamic_pointer_cast< KFEntityDeviceSensorBoolDirect >(dev);

    if(s_b != nullptr )
    {
       SetConfiguration( s_b );
    }


    // std::shared_ptr<KFEntityDeviceSensorVolume> s_v =  std::dynamic_pointer_cast< KFEntityDeviceSensorVolume >(dev);

    // if(s_v != nullptr )
    // {
    //    SetConfiguration( s_v );
    // }

    // std::shared_ptr<KFEntityDeviceSensorTemperature> s_t =  std::dynamic_pointer_cast< KFEntityDeviceSensorTemperature >(dev);

    // if(s_t != nullptr )
    // {
    //    SetConfiguration( s_t );
    // }


    std::shared_ptr<KFEntityDevicePWM> pwm =  std::dynamic_pointer_cast< KFEntityDevicePWM>(dev);

    if(pwm != nullptr)
    {
        SetConfiguration(pwm);
    }
    return true;
}


void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<  KFEntityDeviceMotorStepper >   dev )
{
    XML_ASSERT_EXCEPTION(dev != nullptr, "Zero pointer");
    SetConfigType( eSEM_CONFIGTYPE::MOTOR_STEPPER );

    

    //dev->fAddress

    // fConfigStepper.   

    fConfigStepper.GetStepUnitConversion()->SetSIUnit( (int)dev->fUnit );
    fConfigStepper.GetStepUnitConversion()->SetUnitPerStep( (float)dev->fUnitConversion );

    if( dev->fConfig.fHasEndStopNegative  == true )
    {
        fConfigStepper.SetNegativeEndStop( dev->fConfig.fEndStopNegative );
    }

    if( dev->fConfig.fHasEndStopPositive == true )
    {
        fConfigStepper.SetPositiveEndStop(  dev->fConfig.fEndStopPositive );
    }

    if( dev->fConfig.fHasDirectionHome == true )
    {  
        fConfigStepper.SetDirectionHome( dev->fConfig.fDirectionHome );
    }

    fConfigStepper.SetDirectionPositive( dev->fConfig.fDirectionPositive );


    fConfigStepper.SetMaxSpeed( dev->fConfig.fMaxSpeed);
    fConfigStepper.SetSpeed( dev->fConfig.fSpeed );
    fConfigStepper.SetMaxAccellleration( dev->fConfig.fMaxAccelleration );
    fConfigStepper.SetAccellleration( dev->fConfig.fAccelleration );
    fConfigStepper.SetMaxCurrent( dev->fConfig.fMaxCurrent );
    fConfigStepper.SetCurrent( dev->fConfig.fCurrent );
    fConfigStepper.SetInactiveTimeout( dev->fConfig.fInactiveTimeout );
    fConfigStepper.SetInativeCurrent( dev->fConfig.fInactiveCurrent );
    fConfigStepper.SetHomeValue( dev->fConfig.fHomeValue );
    fConfigStepper.SetHomeId( dev->fConfig.fHomeDeviceID);
    fConfigStepper.SetNegativeEndStopId( dev->fConfig.fEndStopNegativeID );
    fConfigStepper.SetPositiveEndStopId( dev->fConfig.fEndStopPositiveID );

}


void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceMotorXY> dev )
{
    XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
    SetConfigType( eSEM_CONFIGTYPE::MOTOR_XY );
    fConfigVirtualXY.SetDeviceX(  dev->fMotorTranslationID );
    fConfigVirtualXY.SetDeviceY(  dev->fMotorRotationID );
}


void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceSensorAnalogDirect>  dev ) 
{
      SetConfigType ( eSEM_CONFIGTYPE::SENSOR_ANALOG );  
      fConfigSensoranalog.SetInputType( dev->fUnitConversion.fInputType );
      XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");

      auto conversion = fConfigSensoranalog.GetConversion();
      auto thresholds =  fConfigSensoranalog.GetThresholds();

      SetUnitConversion(  &dev->fUnitConversion, conversion  );  
      SetThresholds(      &dev->fTresholds, thresholds );  

     fConfigSensoranalog.SetDeviceIDAux(  dev->fDeviceIDAux  );
}



void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceSensorLocal>  dev )
{
    SetConfigType ( eSEM_CONFIGTYPE::SENSOR_ANALOG  );    
    fConfigSensoranalog.SetInputType( dev->fUnitConversion.fInputType );
    XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
    auto conversion = fConfigSensoranalog.GetConversion();
    auto thresholds =  fConfigSensoranalog.GetThresholds();
    SetUnitConversion(  &dev->fUnitConversion, conversion  );  
    SetThresholds(      &dev->fTresholds, thresholds );  
     fConfigSensoranalog.SetDeviceIDAux( dev->fDeviceIDAux );
}



void  
KFPBMessageSEMConfig::SetThresholds( const  KFSensorThresholds * const input,  KFPBSubMessageSEMThresholds  *output )
{
    output->SetALarmLow( input->fAlarmLow, input->fHasAlarmLow );
    output->SetWarningLow(input->fWarningLow, input->fHasWarningLow  );
    output->SetWarningHigh( input->fWarningHigh, input->fHasWarningHigh );
    output->SetAlarmHigh( input->fAlarmHigh, input->fHasAlarmHigh );
}


void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceSensorBoolDirect>  dev )
{ 
    XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
    SetConfigType ( eSEM_CONFIGTYPE::SENSOR_BOOL );  
    
    fConfigSensorBool.SetDeviceIDAux( dev->fDeviceIDAux );
    fConfigSensorBool.SetActiveHigh( dev->fIsActiveHigh );
    fConfigSensorBool.SetAlarm( dev->fIsAlarm );  
    fConfigSensorBool.SetSignalType( dev->fUnitConversion.fInputType );
 
}



// void 
// KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceSensorVolume>   dev )
// {
//   XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
//   SetConfigType ( eSEM_CONFIGTYPE::SENSOR_analog  );    
//   fConfigSensoranalog.SetDeviceIDAux( dev->fStepperDeviceID );
//   fConfigSensoranalog.GetConversion()->SetOutputSIUnit( dev->fUnitConversion.fOutputUnit);
// }
// /**@}*/



// void 
// KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceSensorTemperature>  dev  )
// {
//   XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
//   SetConfigType ( eSEM_CONFIGTYPE::SENSOR_analog  );    
//   fConfigSensoranalog.SetDeviceIDAux ( dev->fDeviceIDAux );
//   auto conversion = fConfigSensoranalog.GetConversion();
//   auto thresholds = fConfigSensoranalog.GetThresholds();
//   conversion->SetInputType (dev->fUnitConversion.fInputType );
//   conversion->SetOutputSIUnit(dev->fUnitConversion.fOutputUnit );
//   SetThresholds( &dev->fTresholds, thresholds  );  
 
// }



void 
KFPBMessageSEMConfig::SetUnitConversion( const  KFSensorUnitConversion * const input, KFPBSubMessageSEMLinearUnitConversion *output )
{
    output->SetConfiguration( input );
}



void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDevicePWM>  dev )
{
    XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
    SetConfigType ( eSEM_CONFIGTYPE::PWM  );    
    //fConfigPWM.SetLevel( dev->fLevel);
    fConfigPWM.SetMaxLevel( dev->fMaxLevel );
    fConfigPWM.SetMinLevel( dev->fMinLevel );

    SetUnitConversion( &dev->fUnitConversion,  fConfigPWM.GetConversion() );
}


void 
KFPBMessageSEMConfig::SetConfiguration( std::shared_ptr<KFEntityDeviceSolenoid>  dev )
{
    XML_ASSERT_EXCEPTION( dev != nullptr, "Zero pointer");
    SetConfigType ( eSEM_CONFIGTYPE::SOLENOID  );    
    fConfigSolenoid.SetMaxCurrent(dev->fMaxCurrent);
    fConfigSolenoid.SetActivateCurrent( dev->fActivateCurrent  );
    fConfigSolenoid.SetHoldCurrent( dev->fHoldCurrent);
}



#endif