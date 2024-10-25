// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/

#include "TestKFXMLParserDevices.h"
#include <utilities/GSystem.h>

#include <xml/GXmlValidator.h>
#include <configuration/KFEntityDeviceMotorStepper.h>
#include <configuration/KFEntityDeviceMotorXY.h>
#include <configuration/KFEntityDevicePWM.h>
#include <configuration/KFEntityDevicePWMPower.h>
#include <configuration/KFEntityDevicePWMSignal.h>
#include <configuration/KFEntityDeviceSensor.h>
#include <configuration/KFEntityDeviceSensorAnalogDirect.h>
#include <configuration/KFEntityDeviceSensorBoolDirect.h>
#include <configuration/KFEntityDeviceSensorLocal.h>
//#include <configuration/KFEntityDeviceSensorVolume.h>
#include <configuration/KFEntityDeviceSolenoid.h>

#include <configuration/KFXMLParserDevices.h>
#include <configuration/KFConfigurationHandler.h>
#include <configuration/KFConfigUtilities.h>

#include <kf-main/KFGlobals.h>


 void
 TestKFXMLParserDevices::SetUpTestCase()
 {
	 PUSH();
	 SET_LOGTARGET("--target-off --target-file");
	 KFConfigUtilities::Instance()->InitFileXML("kf_config_unittest.xml", fXMLFile );
	 KFConfigUtilities::Instance()->InitFileXSD( KFGlobals::Instance()->GetXSDFilenameDevices().str() , fXSDFile );
//	 InitFiles("kf_config_test.xml", "kf_config_test.xsd");
	 p = new KFXMLParserDevices();
	 cfg = KFConfigurationHandler::Instance();

	POP();
 }


void
TestKFXMLParserDevices::TearDownTestCase()
{
	delete p;
}


void
TestKFXMLParserDevices::SetUp()
{
	PUSH();
	SET_LOGTARGET("--target-off --target-file");
//	FORCE_DEBUG("Parsing files");
	Parse(fXMLFile, fXSDFile, p);
//	FORCE_DEBUG("Done...");
	POP();
}



void
TestKFXMLParserDevices::TearDown()
{
	cfg->Purge();
	EXPECT_EQ( cfg->GetEntitiesDevices().size(), 0 );
}


TEST_F(TestKFXMLParserDevices, validation )
{
	PUSH();
	SET_LOGTARGET("--target-off --target-file");
	EXPECT_TRUE ( GXmlValidator::IsValid( fXMLFile.str(), fXSDFile.str()) );
	POP();
}


TEST_F(TestKFXMLParserDevices, no_entities )
{
	EXPECT_EQ( cfg->GetEntitiesDevices().size(), 14 );
	cfg->Purge();
	EXPECT_EQ( cfg->GetEntitiesDevices().size(), 0 );
}


TEST_F(TestKFXMLParserDevices, devices )
{
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L1-M42")  );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L1-M44")  );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L1-VXY1") );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L43-S25") );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L22-S32")  );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L33-S66")  );
//	EXPECT_NE( nullptr, cfg->GetDeviceByID("L11-VDQ1") );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L22-SOL2") );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L33-PWM1") );
	EXPECT_NE( nullptr, cfg->GetDeviceByID("L35-PWM1") );
	EXPECT_EQ( nullptr, cfg->GetDeviceByID("") );
	EXPECT_EQ( nullptr, cfg->GetDeviceByID("blahhhhh") );
}




TEST_F(TestKFXMLParserDevices, get_by_type  )
{
	auto steppers_v = cfg->GetByClassType<KFEntityDeviceMotorStepper>();
	EXPECT_EQ( steppers_v.size(), 5 );
	auto xy_v = cfg->GetByClassType<KFEntityDeviceMotorXY>();
	EXPECT_EQ(xy_v.size(), 2);
	auto s_v = cfg->GetByClassType<KFEntityDeviceSensor>();
	EXPECT_EQ(s_v.size(), 4);
	auto s_an_v = cfg->GetByClassType<KFEntityDeviceSensorAnalogDirect>();
	EXPECT_EQ(s_an_v.size(), 1);
	auto s_bool_v = cfg->GetByClassType<KFEntityDeviceSensorBoolDirect>();
	EXPECT_EQ(s_bool_v.size(), 1);
	auto s_local_v = cfg->GetByClassType<KFEntityDeviceSensorLocal>();
	EXPECT_EQ(s_local_v.size(), 2 );
//	auto s_vol_v = cfg->GetByClassType<KFEntityDeviceSensorVolume>();
//	EXPECT_EQ(s_vol_v.size(), 1);
	auto sol_v =  cfg->GetByClassType<KFEntityDeviceSolenoid>();
	EXPECT_EQ( sol_v.size(), 1);
	auto pwm_v =  cfg->GetByClassType<KFEntityDevicePWM>();
	EXPECT_EQ( pwm_v.size(), 2 );
	auto pwm_sig_v =  cfg->GetByClassType<KFEntityDevicePWMSignal>();
	EXPECT_EQ( pwm_sig_v.size(), 1 );
	auto pwm_pow_v =  cfg->GetByClassType<KFEntityDevicePWMPower>();
	EXPECT_EQ( pwm_pow_v.size(), 1 );
}


TEST_F(TestKFXMLParserDevices,  fields_stepper  )
{
	auto motor = std::dynamic_pointer_cast<KFEntityDeviceMotorStepper>(cfg->GetDeviceByID("L1-M42") );

	ASSERT_NE(nullptr, motor );
	EXPECT_EQ( motor->fAddress.fDeviceID, "L1-M42" );
	EXPECT_EQ( motor->fAddress.fName, "180 C-ring rotation");
	EXPECT_EQ( motor->fAddress.fIPAddress, "127.0.0.1");
	EXPECT_EQ( motor->fAddress.fCard.fManufacturerID, "X-NUCLEO-IHM03A1" );
	EXPECT_EQ( motor->fAddress.fCard.fCardName, "MotorStepperCard-C-RING-180" );
	EXPECT_EQ( motor->fAddress.fCard.fCardID, 1 );
	EXPECT_EQ( motor->fAddress.fCard.fPort,  2 );

	EXPECT_EQ( (int)motor->fDeviceType, (int)eDEVICE_TYPE::MOTOR_STEPPER );
	EXPECT_EQ( motor->fDeviceTypeS, "MotorStepper"  );
	EXPECT_EQ( (int)motor->fUnit, (int)eSTEP_UNIT::ANGLE_DEGREES );
	EXPECT_EQ(  motor->fUnitS, "angle_deg" );
	EXPECT_NEAR(  motor->fConfig.fEndStopPositive,  190.190, 0.001 );
	EXPECT_EQ(  motor->fConfig.fHasEndStopPositive, true );
	EXPECT_EQ(  motor->fConfig.fHasEndStopNegative, false );
	EXPECT_NEAR ( motor->fConfig.fHomeValue, 10.10, 0.001 );

	/// EXPECT_EQ( motor->fConfig.fEndStopNegative, -190 );


	EXPECT_EQ( (int)motor->fConfig.fDirectionPositive, (int)eDIRECTION::CW);

	EXPECT_NEAR( motor->fConfig.fMaxSpeed, 50.50, 0.001 );
	EXPECT_NEAR( motor->fConfig.fSpeed, 20.20, 0.001 );
	EXPECT_NEAR( motor->fConfig.fMaxAccelleration, 75.75, 0.001 );
	EXPECT_NEAR( motor->fConfig.fAccelleration, 24.24, 0.001);
	EXPECT_NEAR( motor->fConfig.fMaxCurrent, 5.5, 0.001 );
	EXPECT_NEAR( motor->fConfig.fCurrent, 3.3, 0.001 );
	EXPECT_NEAR( motor->fConfig.fInactiveTimeout, 500.5, 0.001 );
	EXPECT_NEAR( motor->fConfig.fInactiveCurrent, 0.2, 0.01 );


	EXPECT_EQ( motor->fConfig.fHomeDeviceID, "S32" );

	EXPECT_TRUE( motor->fConfig.fHasDirectionHome );
	EXPECT_EQ( (int)motor->fConfig.fDirectionHome, (int)eDIRECTION::POSITIVE);
	EXPECT_EQ( motor->fConfig.fEndStopPositiveID, "L1-M61");
	EXPECT_EQ( motor->fConfig.fEndStopNegativeID, "L1-M62");





	motor = std::dynamic_pointer_cast<KFEntityDeviceMotorStepper>(cfg->GetDeviceByID("L1-M44") );

	EXPECT_EQ( motor->fAddress.fDeviceID, "L1-M44" );
	EXPECT_EQ( motor->fAddress.fName, "180 C-ring translation");
	EXPECT_EQ( motor->fAddress.fIPAddress, "192.168.1.17");
	EXPECT_EQ( motor->fAddress.fCard.fManufacturerID, "X-NUCLEO-IHM03A1" );
	EXPECT_EQ( motor->fAddress.fCard.fCardName, "dolore sit amet" );
	EXPECT_EQ( motor->fAddress.fCard.fCardID, 1 );
	EXPECT_EQ( motor->fAddress.fCard.fPort,  2 );

	EXPECT_EQ( (int)motor->fDeviceType, (int)eDEVICE_TYPE::MOTOR_STEPPER );
	EXPECT_EQ( motor->fDeviceTypeS, "MotorStepper"  );
	EXPECT_EQ( (int)motor->fUnit, (int)eSTEP_UNIT::MM );
	EXPECT_EQ( motor->fUnitS, "mm" );
	EXPECT_EQ( motor->fConfig.fEndStopPositive,  185 );
	EXPECT_EQ( motor->fConfig.fEndStopNegative, -185 );

	EXPECT_NEAR( motor->fConfig.fHomeValue, 100.99, 0.001 );
//	EXPECT_NEAR( motor->fConfig.fHomeValue, 100, 0.001 );

	EXPECT_EQ( motor->fConfig.fMaxSpeed, 55 );
	EXPECT_EQ( motor->fConfig.fSpeed, 22 );
	EXPECT_EQ( motor->fConfig.fMaxAccelleration, 55);
	EXPECT_EQ( motor->fConfig.fAccelleration, 22);
	EXPECT_EQ( motor->fConfig.fMaxCurrent, 6 );
	EXPECT_EQ( motor->fConfig.fCurrent, 3 );
	EXPECT_EQ( motor->fConfig.fInactiveTimeout, 600 );

	EXPECT_NEAR( motor->fConfig.fInactiveCurrent, 0.5, 0.01);
	EXPECT_EQ( motor->fConfig.fHomeDeviceID, "S33" );
	EXPECT_FALSE( motor->fConfig.fHasDirectionHome );
//	EXPECT_EQ( motor->fConfig.fDirectionHome, (int)eDIRECTION::UNKNOWN) ;
	EXPECT_EQ( motor->fConfig.fEndStopPositiveID, "L1-M63");
	EXPECT_EQ( motor->fConfig.fEndStopNegativeID, "L2-M64");
}


TEST_F(TestKFXMLParserDevices,  fields_xy  )
{

	auto motor = std::dynamic_pointer_cast<KFEntityDeviceMotorXY>(cfg->GetDeviceByID("L1-VXY1") );
	ASSERT_NE( nullptr, motor );
	EXPECT_EQ( (int)motor->fDeviceType, (int)eDEVICE_TYPE::MOTOR_VIRTUAL_XY );
	EXPECT_EQ( motor->fDeviceTypeS, "MotorVirtualXY" );
	EXPECT_EQ( motor->fAddress.fName, "VirtualMotor" );
	EXPECT_EQ( motor->fMotorTranslationID, "L2-M46" );
	EXPECT_EQ( motor->fMotorRotationID, "L2-M47");
}


TEST_F(TestKFXMLParserDevices,  fields_sensor_analoge_direct   )
{
	auto sensor =   std::dynamic_pointer_cast<KFEntityDeviceSensorAnalogDirect>(cfg->GetDeviceByID("L43-S25") );
	ASSERT_NE( nullptr, sensor );

	EXPECT_EQ( sensor->fAddress.fDeviceID, "L43-S25" );
	EXPECT_EQ( sensor->fAddress.fName, "Habitat Internal Temperature");
	EXPECT_EQ( sensor->fAddress.fIPAddress, "192.168.1.2");
	EXPECT_EQ( sensor->fAddress.fCard.fManufacturerID, "Semcon" );
	EXPECT_EQ( sensor->fAddress.fCard.fCardName, "PowerIO" );
	EXPECT_EQ( sensor->fAddress.fCard.fCardID, 2 );
	EXPECT_EQ( sensor->fAddress.fCard.fPort,  3 );

	EXPECT_EQ( (int)sensor->fDeviceType, (int)eDEVICE_TYPE::SENSOR_ANALOG_DIRECT );
	EXPECT_EQ( sensor->fDeviceTypeS, "SensorAnalogDirect"  );

	EXPECT_EQ( (int)sensor->fUnitConversion.fInputType, (int)eSENSOR_INPUT_TYPE::MA_4_20);
	EXPECT_EQ( sensor->fUnitConversion.fInputTypeS, "4-20mA" );


	EXPECT_NEAR( sensor->fUnitConversion.fMinInput, 1.5, 0.001 );

	//EXPECT_EQ( sensor->fUnitConversion.fMaxInput, 10 );

	EXPECT_EQ( sensor->fUnitConversion.fMinOutput, 3 );
	EXPECT_EQ( sensor->fUnitConversion.fMaxOutput, 30 );

	EXPECT_EQ( sensor->fTresholds.fAlarmLow, -2);
	EXPECT_EQ( sensor->fTresholds.fWarningLow, -1);

	EXPECT_EQ( sensor->fTresholds.fWarningHigh, 1);
	EXPECT_EQ( sensor->fTresholds.fAlarmHigh, 2);
}


TEST_F(TestKFXMLParserDevices,  fields_sensor_local   )
{
	auto sensor =   std::dynamic_pointer_cast<KFEntityDeviceSensorLocal>(cfg->GetDeviceByID("L33-S66") );
	ASSERT_NE( nullptr, sensor );

	EXPECT_EQ( sensor->fAddress.fDeviceID, "L33-S66" );
	EXPECT_EQ( sensor->fAddress.fName, "24VIN");
	EXPECT_EQ( sensor->fAddress.fIPAddress, "192.168.1.7");
	EXPECT_EQ( sensor->fAddress.fCard.fManufacturerID, "Lorem Ipsum" );
	EXPECT_EQ( sensor->fAddress.fCard.fCardName, "PowerIO" );
	EXPECT_EQ( sensor->fAddress.fCard.fCardID, 1 );
	EXPECT_EQ( sensor->fAddress.fCard.fPort,  1 );

	EXPECT_EQ( (int)sensor->fDeviceType, (int)eDEVICE_TYPE::SENSOR_LOCAL );
	EXPECT_EQ( sensor->fDeviceTypeS, "SensorLocal"  );

	EXPECT_EQ( (int)sensor->fUnitConversion.fInputType, (int)eSENSOR_INPUT_TYPE::V0_10 );
	EXPECT_EQ( sensor->fUnitConversion.fInputTypeS, "0-10V" );

	// EXPECT_EQ( (int)sensor->fUnitConversion.fOutputUnit, (int)eOUTPUT_SI_UNIT::VOLT );
	// EXPECT_EQ( sensor->fUnitConversion.fOutputUnitS, "V" );

	EXPECT_EQ( sensor->fUnitConversion.fMinInput, 0 );
	EXPECT_EQ( sensor->fUnitConversion.fMaxInput, 10 );

	EXPECT_EQ( sensor->fUnitConversion.fMinOutput, 0 );
	EXPECT_EQ( sensor->fUnitConversion.fMaxOutput, 30 );

	EXPECT_EQ( sensor->fTresholds.fAlarmLow, 18);
	EXPECT_EQ( sensor->fTresholds.fWarningLow, 20);

	EXPECT_EQ( sensor->fTresholds.fWarningHigh, 28);
	EXPECT_EQ( sensor->fTresholds.fAlarmHigh, 30);
}


TEST_F(TestKFXMLParserDevices,  fields_sensor_bool_direct   )
{
	auto sensor =   std::dynamic_pointer_cast<KFEntityDeviceSensorBoolDirect>(cfg->GetDeviceByID("L22-S32") );
	ASSERT_NE( nullptr, sensor );
	EXPECT_EQ( sensor->fAddress.fDeviceID, "L22-S32" );
	EXPECT_EQ( sensor->fAddress.fName, "180 C-Ring control");
	EXPECT_EQ( sensor->fAddress.fIPAddress, "192.168.0.1");
	EXPECT_EQ( sensor->fAddress.fCard.fManufacturerID, "LoremIpsum" );
	EXPECT_EQ( sensor->fAddress.fCard.fCardName, "PowerIO" );
	EXPECT_EQ( sensor->fAddress.fCard.fCardID, 3 );
	EXPECT_EQ( sensor->fAddress.fCard.fPort,  6 );
	EXPECT_EQ( (int)sensor->fDeviceType, (int)eDEVICE_TYPE::SENSOR_BOOL_DIRECT );
	EXPECT_EQ( sensor->fDeviceTypeS, "SensorBoolDirect"  );
	EXPECT_EQ( (int)sensor->fUnitConversion.fInputType, (int)eSENSOR_INPUT_TYPE::PNP  );
	EXPECT_EQ( sensor->fUnitConversion.fInputTypeS, "PNP" );
	EXPECT_EQ( sensor->fIsActiveHigh, true);
}



// TEST_F(TestKFXMLParserDevices,  fields_sensor_volume  )
// {
// 	auto sensor =   std::dynamic_pointer_cast<KFEntityDeviceSensorVolume>(cfg->GetDeviceByID("L11-VDQ1") );
// 	ASSERT_NE( nullptr, sensor );
// 	EXPECT_EQ( sensor->fAddress.fDeviceID, "L11-VDQ1" );
// 	EXPECT_EQ( sensor->fAddress.fName, "Coating Volume");
// 	EXPECT_EQ( sensor->fAddress.fIPAddress, "192.168.1.1");
// 	EXPECT_EQ( sensor->fAddress.fCard.fManufacturerID, "Semcon" );
// 	EXPECT_EQ( sensor->fAddress.fCard.fCardName, "SensorVolumeDevice" );
// 	EXPECT_EQ( sensor->fAddress.fCard.fCardID, 1 );
// 	EXPECT_EQ( sensor->fAddress.fCard.fPort,  0 );
// 	EXPECT_EQ( (int)sensor->fDeviceType, (int)eDEVICE_TYPE::SENSOR_VOLUME );
// 	EXPECT_EQ( sensor->fDeviceTypeS, "SensorVolume" );
// 	EXPECT_EQ( (int)sensor->fUnitConversion.fOutputUnit, (int)eOUTPUT_SI_UNIT::ML );
// 	EXPECT_EQ( sensor->fUnitConversion.fOutputUnitS, "mL" );
// 	EXPECT_EQ( sensor->fStepperDeviceID, "L11-M32");
// }



TEST_F(TestKFXMLParserDevices,  fields_solenoide  )
{
	auto  solenoid =   std::dynamic_pointer_cast< KFEntityDeviceSolenoid >(cfg->GetDeviceByID("L22-SOL2") );
	ASSERT_NE( nullptr, solenoid );
	EXPECT_EQ( solenoid->fAddress.fDeviceID, "L22-SOL2" );
	EXPECT_EQ( solenoid->fAddress.fName, "Air Input");
	EXPECT_EQ( solenoid->fAddress.fIPAddress, "192.168.0.1");
	EXPECT_EQ( solenoid->fAddress.fCard.fManufacturerID, "Semcon" );
	EXPECT_EQ( solenoid->fAddress.fCard.fCardName, "PowerIO" );
	EXPECT_EQ( solenoid->fAddress.fCard.fCardID, 1 );
	EXPECT_EQ( solenoid->fAddress.fCard.fPort,  1 );
	EXPECT_EQ( (int)solenoid->fDeviceType, (int)eDEVICE_TYPE::SOLENOID );
	EXPECT_EQ( solenoid->fDeviceTypeS, "Solenoid" );

	EXPECT_NEAR( solenoid->fMaxCurrent, 3.3, 0.001);
	EXPECT_NEAR( solenoid->fActivateCurrent, 2.2, 0.001);
	EXPECT_NEAR( solenoid->fHoldCurrent, 1.1, 0.001);
}



TEST_F(TestKFXMLParserDevices,  fields_pwm_signal  )
{
	auto  pwm =   std::dynamic_pointer_cast< KFEntityDevicePWMSignal >(cfg->GetDeviceByID("L33-PWM1") );
	ASSERT_NE( nullptr, pwm );
	EXPECT_EQ( pwm->fAddress.fDeviceID, "L33-PWM1" );
	EXPECT_EQ( pwm->fAddress.fName, "External LED");
	EXPECT_EQ( pwm->fAddress.fIPAddress, "192.168.1.2");
	EXPECT_EQ( pwm->fAddress.fCard.fManufacturerID, "Semcon" );
	EXPECT_EQ( pwm->fAddress.fCard.fCardName, "PowerIO" );
	EXPECT_EQ( pwm->fAddress.fCard.fCardID, 3 );
	EXPECT_EQ( pwm->fAddress.fCard.fPort,  4 );
	EXPECT_EQ( (int)pwm->fDeviceType, (int)eDEVICE_TYPE::PWM_SIGNAL );
	EXPECT_EQ( pwm->fDeviceTypeS, "PWMSignal" );

	EXPECT_EQ( (int)pwm->fUnitConversion.fInputType, (int)eSENSOR_INPUT_TYPE::PWM_RC );
	EXPECT_EQ( pwm->fUnitConversion.fInputTypeS, "PWM-RC" );

	// EXPECT_EQ( (int)pwm->fUnitConversion.fOutputUnit, (int)eOUTPUT_SI_UNIT::PERCENT );
	// EXPECT_EQ( pwm->fUnitConversion.fOutputUnitS, "percent" );

	EXPECT_NEAR( pwm->fUnitConversion.fMinInput, 0.5, 0.001 );
	EXPECT_NEAR( pwm->fUnitConversion.fMaxInput, 100.9, 0.001 );
	EXPECT_NEAR( pwm->fUnitConversion.fMinOutput, 35.6, 0.001 );
	EXPECT_NEAR( pwm->fUnitConversion.fMaxOutput, 300.2, 0.001 );

	EXPECT_NEAR(pwm->fMinLevel, 0.1, 0.001);
	EXPECT_NEAR(pwm->fMaxLevel, 100.7, 0.001);
	///EXPECT_NEAR(pwm->fLevel, 50.5, 0.001);
}



TEST_F(TestKFXMLParserDevices,  fields_pwm_power  )
{
	auto  pwm =   std::dynamic_pointer_cast< KFEntityDevicePWMPower>(cfg->GetDeviceByID("L35-PWM1") );
	ASSERT_NE( nullptr, pwm );
	EXPECT_EQ( pwm->fAddress.fDeviceID, "L35-PWM1" );
	EXPECT_EQ( pwm->fAddress.fName, "RoughBoy Spindle");
	EXPECT_EQ( pwm->fAddress.fIPAddress, "192.168.1.5");
	EXPECT_EQ( pwm->fAddress.fCard.fManufacturerID, "Unknown" );
	EXPECT_EQ( pwm->fAddress.fCard.fCardName, "PowerIO" );
	EXPECT_EQ( pwm->fAddress.fCard.fCardID, 1 );
	EXPECT_EQ( pwm->fAddress.fCard.fPort,  1 );
	EXPECT_EQ( (int)pwm->fDeviceType, (int)eDEVICE_TYPE::PWM_POWER );
	EXPECT_EQ( pwm->fDeviceTypeS, "PWMPower" );

	EXPECT_EQ( (int)pwm->fUnitConversion.fInputType, (int)eSENSOR_INPUT_TYPE::PWM_DUTY );
	EXPECT_EQ( pwm->fUnitConversion.fInputTypeS, "PWM-duty_cycle" );

	// EXPECT_EQ( (int)pwm->fUnitConversion.fOutputUnit, (int)eOUTPUT_SI_UNIT::RPM );
	// EXPECT_EQ( pwm->fUnitConversion.fOutputUnitS, "RPM" );

	EXPECT_EQ( pwm->fUnitConversion.fMinInput, 10 );
	EXPECT_EQ( pwm->fUnitConversion.fMaxInput, 100 );
	EXPECT_EQ( pwm->fUnitConversion.fMinOutput, 0 );
	EXPECT_EQ( pwm->fUnitConversion.fMaxOutput, 2000 );

	EXPECT_EQ(pwm->fMinLevel, 0 );
	EXPECT_EQ(pwm->fMaxLevel, 80 );
	//EXPECT_EQ(pwm->fLevel, 70 );
}
