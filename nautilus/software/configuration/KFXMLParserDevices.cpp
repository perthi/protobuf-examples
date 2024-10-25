// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "KFXMLParserDevices.h"

#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <xml/GXmlClassFactory.h>
#include <xml/GXmlStreamWriter.h>
#include <xml/GXmlStreamReader.h>
#include <xml/GXmlValidator.h>
#include <utilities/GException.h>

#include "KFEntityDeviceMotorStepper.h"
#include "KFEntityDeviceMotorXY.h"
#include "KFEntityDeviceSensor.h"
#include "KFEntityDeviceSolenoid.h"
#include "KFEntityDevicePWM.h"
#include "KFEntityDevicePWMSignal.h"
#include "KFEntityDevicePWMPower.h"
#include "KFSensorThresholds.h"

#include "KFConfigurationHandler.h"


KFXMLParserDevices::KFXMLParserDevices()
{
	InitHashMaps();
}

KFXMLParserDevices::~KFXMLParserDevices()
{

}


vector< std::shared_ptr<KFEntity> >
KFXMLParserDevices::ParseXML(const XMLFile_t xml, const XSDFile_t xsd)
{
	ENGINE_ASSERT_EXCEPTION(GXmlValidator::IsValid(xml.str(), xsd.str()), "Faild to validate XML file %s against %s",  
	xml.str().c_str(), xsd.str().c_str());
	std::shared_ptr<GXmlStreamReader> xmlReader = GXmlClassFactory::CreateStreamReaderSmartPtr(xml.str());
	GXmlNode* node = xmlReader->ReadNode();
	vector< std::shared_ptr<KFEntity> > tmp;

	while (node != nullptr)
	{
		string tag = node->GetName();

		if (tag == "FERROTECH" && node->GetType() == eXML_NODETYPE::EOpenTagNode)
		{
			ENGINE_INFO("node name is FERROTECH");
		}
		else
		{
			if (tag == "MOTOR_STEPPER")
			{
				tmp.push_back(  ParseXMLMotorStepper(xmlReader, tag)  );
			}
			else if( tag == "MOTOR_VIRTUAL_XY" )
			{
				tmp.push_back ( ParseXMLMotorXY( xmlReader, tag  ) );
			}
			else if( tag == "SENSOR_ANALOG_DIRECT" )
			{
				tmp.push_back ( ParseXMLSensor<KFEntityDeviceSensorAnalogDirect>( xmlReader, tag ) );
			}
			else if( tag == "SENSOR_BOOL_DIRECT" )
			{
				tmp.push_back ( ParseXMLSensor<KFEntityDeviceSensorBoolDirect>( xmlReader, tag  ) );
			}
			else if( tag == "SENSOR_LOCAL" )
			{
				tmp.push_back ( ParseXMLSensor<KFEntityDeviceSensorLocal>( xmlReader, tag  ) );
			}
			else if( tag == "SOLENOID" )
			{
				tmp.push_back ( ParseXMLSolenoid(xmlReader, tag) ) ;
			}
			else if( tag == "PWM_SIGNAL" )
			{
				tmp.push_back ( ParseXMLPWM<KFEntityDevicePWMSignal>(  xmlReader, tag ) );
			}
			else if( tag == "PWM_POWER" )
			{
				tmp.push_back ( ParseXMLPWM< KFEntityDevicePWMPower>(  xmlReader, tag ) );
			}
			else
			{
				//ENGINE_EXCEPTION("unreckognized tag %s", tag.c_str()  );
			}
		}
		node = xmlReader->ReadNode();void AddEntity( std::shared_ptr<KFEntityDevice> entity );
	}

	return tmp;
}



void
KFXMLParserDevices::ParseXMLCommon(std::shared_ptr<GXmlStreamReader> xmlReader,  std::shared_ptr<KFEntityDevice>  entity  )
{
	ParseXMLDeviceAddress(xmlReader, &entity->fAddress );
	string type_s = GetTagValue<string>( xmlReader, "DEVICE_TYPE", GLOCATION);
	eDEVICE_TYPE type = String2Enum<eDEVICE_TYPE>(type_s, &fDeviceTypes );
	entity->fDeviceTypeS = type_s;
	entity->fDeviceType = type;
}



std::shared_ptr<KFEntityDeviceMotorStepper>
KFXMLParserDevices::ParseXMLMotorStepper(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag )
{
	auto motor = std::make_shared<KFEntityDeviceMotorStepper>();
	ParseXMLCommon(xmlReader, motor );

	AssertTagOpenGroup( xmlReader,"STEP_UNIT_CONVERSION", GLOCATION  );
	{
		string unit_s = GetTagValue<string>( xmlReader, "UNIT", GLOCATION);
		eSTEP_UNIT unit = String2Enum(unit_s, &fStepUnits );
		motor->fUnitS = unit_s;

	//	FORCE_DEBUG("%s outputs unit set to %d", motor->fUnitS.c_str(),  (int)unit );

		ENGINE_ASSERT_EXCEPTION(unit != eSTEP_UNIT::UNKNOWN, "unit type %s not reckognized", unit_s.c_str() );
		motor->fUnit = unit;
		motor->fUnitConversion = GetTagValue<float>( xmlReader, "UNIT_PER_STEP", GLOCATION);
		ENGINE_INFO("unit = %d", (int)unit);
	}
	AssertTagCloseGroup( xmlReader,"STEP_UNIT_CONVERSION", GLOCATION  );

	ParseXMLMotorConfig(xmlReader, &motor->fConfig );
	AssertTagCloseGroup( xmlReader, closing_tag, GLOCATION  );
	return motor;
}



std::shared_ptr<KFEntityDeviceMotorXY>
KFXMLParserDevices::ParseXMLMotorXY(std::shared_ptr<GXmlStreamReader> xmlReader, const string  closing_tag  )
{
	auto motor = std::make_shared<KFEntityDeviceMotorXY>();
	motor->fAddress.fIPAddress =  GetTagValue<string>( xmlReader, "IP_ADDRESS", GLOCATION );
	motor->fAddress.fDeviceID =   GetTagValue<string>( xmlReader, "DEVICE_ID", GLOCATION);
	string type_s = GetTagValue<string>( xmlReader, "DEVICE_TYPE", GLOCATION);
	eDEVICE_TYPE type = String2Enum<eDEVICE_TYPE>(type_s, &fDeviceTypes );
	motor->fDeviceTypeS = type_s;

//	ENGINE_ASSERT_EXCEPTION(type ==  motor->fDeviceType, "Invalid type %s, expected %s", *type, *motor->fDeviceType );
	ENGINE_ASSERT_EXCEPTION(type ==  motor->fDeviceType, "Invalid type %d, expected %d", (int)type, (int)motor->fDeviceType );

	motor->fAddress.fName =       GetTagValue<string>( xmlReader, "DEVICE_NAME", GLOCATION);
	motor->fMotorTranslationID =  GetTagValue<string>( xmlReader, "MOTOR_TRANSLATION", GLOCATION );
	motor->fMotorRotationID =     GetTagValue<string>( xmlReader, "MOTOR_ROTATION", GLOCATION );
	AssertTagCloseGroup( xmlReader, closing_tag, GLOCATION  );
 	return motor;
}


void
KFXMLParserDevices::ParseXMLDeviceAddress(std::shared_ptr<GXmlStreamReader> xmlReader, KFDeviceAddress* addr)
{
	AssertTagOpenGroup( xmlReader,"DEVICE_ADDRESS", GLOCATION  );
	{
		addr->fDeviceID = GetTagValue<string>( xmlReader, "DEVICE_ID", GLOCATION);
		addr->fName = GetTagValue<string>( xmlReader, "DEVICE_NAME", GLOCATION);
    	addr->fIPAddress = GetTagValue<string>( xmlReader, "IP_ADDRESS", GLOCATION);

		AssertTagOpenGroup( xmlReader,"CARD", GLOCATION  );
		{
			addr->fCard.fManufacturerID  =  GetTagValue<string>( xmlReader, "MANUFACTURER_ID", GLOCATION);
			addr->fCard.fCardName        =  GetTagValue<string>(      xmlReader, "CARD_NAME", GLOCATION);
			addr->fCard.fCardID          =  GetTagValue<int>( xmlReader, "CARD_ID", GLOCATION);
			addr->fCard.fPort            =  GetTagValue<int>( xmlReader, "DEVICE_PORT_NO", GLOCATION);
		}
		AssertTagCloseGroup( xmlReader,"CARD", GLOCATION  );
	}
	AssertTagCloseGroup( xmlReader,"DEVICE_ADDRESS", GLOCATION  );
}





bool
KFXMLParserDevices::ParseXMLSensorUnitConversion(std::shared_ptr<GXmlStreamReader> xmlReader, KFSensorUnitConversion *uc )
{
	GXmlNode *node = xmlReader->ReadNode();
	if( node->GetName() != "UNIT_CONVERSION")
	{
		return false;
	}

	AssertTagOpenGroup( xmlReader, "UNIT_CONVERSION", GLOCATION, false);
	{
		uc->ValidateInputs();
		string input_type_s = GetTagValue<string>(xmlReader, "INPUT_TYPE", GLOCATION);
		uc->fInputTypeS = input_type_s;
		uc->fInputType  = String2Enum( input_type_s, &fInputTypes );
		uc->fMinInput   = GetTagValueOrNothing<float>( xmlReader,  "MIN_INPUT",   GLOCATION, &uc->fHasMinInput);
		uc->fMaxInput   = GetTagValueOrNothing<float>( xmlReader,  "MAX_INPUT",   GLOCATION, &uc->fHasMaxInput);
		uc->fMinOutput  = GetTagValueOrNothing<float>( xmlReader,  "MIN_OUTPUT",  GLOCATION, &uc->fHasMinOutput);
		uc->fMaxOutput  = GetTagValueOrNothing<float>( xmlReader,  "MAX_OUTPUT",  GLOCATION, &uc->fHasMaxOutput);
	}
	AssertTagCloseGroup( xmlReader,"UNIT_CONVERSION", GLOCATION  );
	return true;
}



void
KFXMLParserDevices::ParseXMLSensorThresholds(std::shared_ptr<GXmlStreamReader> xmlReader,  KFSensorThresholds * t, const bool read_node )
{
	AssertTagOpenGroup( xmlReader,"THRESHOLDS", GLOCATION, read_node  );
	{
		t->fAlarmLow =    GetTagValueOrNothing<float>(xmlReader,     "ALARM_LOW", GLOCATION,   &t->fHasAlarmLow    );
		t->fWarningLow =  GetTagValueOrNothing<float>(xmlReader,   "WARNING_LOW", GLOCATION,   &t->fHasWarningLow   );
		t->fWarningHigh = GetTagValueOrNothing<float>(xmlReader,    "WARNING_HIGH", GLOCATION, &t->fHasWarningHigh  );
		t->fAlarmHigh =   GetTagValueOrNothing<float> (xmlReader,   "ALARM_HIGH", GLOCATION,   &t->fHasAlarmHigh   );

	}
	AssertTagCloseGroup( xmlReader,"THRESHOLDS", GLOCATION  );

}


void
KFXMLParserDevices::ParseXMLMotorConfig( std::shared_ptr<GXmlStreamReader> xmlReader,  KFConfigMotor   *cfg )
{
	AssertTagOpenGroup( xmlReader,"MOTOR_CONFIG" ,GLOCATION  );
	{
		string tmp =  GetTagValue<string>( xmlReader,  "DIRECTION_POSITIVE",  GLOCATION);

		if(tmp == "CW" )
		{
			cfg->fDirectionPositive = eDIRECTION::CW;
		}
		else if ( tmp == "CCW")
		{
			cfg->fDirectionPositive = eDIRECTION::CCW;
		}
		else
		{
			cfg->fDirectionPositive = eDIRECTION::INVALID;
		}


//		cfg->fDirectionRotation =  (eDIRECTION)GetTagValueOrNothing<int>( xmlReader,  "DIRECTION_ROTATIONAL",  GLOCATION, &cfg->fHasEndStopPositive  );

		cfg->fEndStopPositive = GetTagValueOrNothing<float>( xmlReader,  "ENDSTOP_SOFT_POSITIVE",  GLOCATION, &cfg->fHasEndStopPositive  );
		cfg->fEndStopNegative = GetTagValueOrNothing<float>( xmlReader,  "ENDSTOP_SOFT_NEGATIVE",  GLOCATION, &cfg->fHasEndStopNegative  );

		cfg->fMaxSpeed            =   GetTagValue<float>(    xmlReader, "MAX_SPEED", GLOCATION);
		cfg->fSpeed               =   GetTagValue<float>(    xmlReader, "SPEED", GLOCATION);
		cfg->fMaxAccelleration    =   GetTagValue<float>(    xmlReader, "MAX_ACCELERATION", GLOCATION);
		cfg->fAccelleration       =   GetTagValue<float>(    xmlReader, "ACCELERATION", GLOCATION);
		cfg->fMaxCurrent          =   GetTagValue<float>(    xmlReader, "MAX_CURRENT", GLOCATION);
		cfg->fCurrent             =   GetTagValue<float>(    xmlReader, "CURRENT", GLOCATION);
		cfg->fInactiveTimeout     =   GetTagValue<float>(  xmlReader, "INACTIVE_TIMEOUT", GLOCATION);
		cfg->fInactiveCurrent     =   GetTagValue<float>(  xmlReader, "INACTIVE_CURRENT", GLOCATION);
		cfg->fHomeDeviceID        =   GetTagValue<string>( xmlReader, "HOME_DEVICE_ID", GLOCATION);
		cfg->fHomeValue           =   GetTagValue<float>(    xmlReader, "HOME_VALUE", GLOCATION);


		tmp =  GetTagValue<string>( xmlReader,  "HOME_DIRECTION",  GLOCATION);

		if(tmp == "POSITIVE" )
		{
			cfg->fDirectionHome = eDIRECTION::POSITIVE;
			cfg->fHasDirectionHome = true;
		}
		else if ( tmp == "NEGATIVE")
		{
			cfg->fDirectionHome = eDIRECTION::NEGATIVE;
			cfg->fHasDirectionHome = true;
		}
		else if (tmp == "" )
		{
			cfg->fDirectionHome = eDIRECTION::UNKNOWN;
			cfg->fHasDirectionHome = false;
		}
		else
		{
			cfg->fDirectionHome = eDIRECTION::INVALID;
			cfg->fHasDirectionHome = false;
			XML_FATAL("Unknwon direction %s found for tag  HOME_DIRECTION", tmp.c_str() );
		}

		cfg->fEndStopPositiveID   =   GetTagValue<string>( xmlReader, "ENDSTOP_DEVICE_ID_POSITIVE", GLOCATION);
		cfg->fEndStopNegativeID   =   GetTagValue<string>( xmlReader, "ENDSTOP_DEVICE_ID_NEGATIVE", GLOCATION);
	}
	AssertTagCloseGroup( xmlReader,"MOTOR_CONFIG", GLOCATION  );
}


std::shared_ptr<KFEntityDeviceSolenoid>
KFXMLParserDevices::ParseXMLSolenoid(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag)
{
	auto solenoid = std::make_shared<KFEntityDeviceSolenoid>();
	ParseXMLCommon(xmlReader, solenoid );
	solenoid->fMaxCurrent = GetTagValue<float>(xmlReader, "MAX_CURRENT", GLOCATION);
	solenoid->fActivateCurrent = GetTagValue<float>(xmlReader, "ACTIVATE_CURRENT", GLOCATION);
	solenoid->fHoldCurrent = GetTagValue<float>(xmlReader, "HOLD_CURRENT", GLOCATION);
	AssertTagCloseGroup( xmlReader, closing_tag, GLOCATION  );
	return solenoid;
}


void
KFXMLParserDevices::InitHashMaps()
{
	fDeviceTypes.emplace("SEM",                   eDEVICE_TYPE::SEM );
	fDeviceTypes.emplace("MotorStepper",          eDEVICE_TYPE::MOTOR_STEPPER );
	fDeviceTypes.emplace("MotorVirtualXY",        eDEVICE_TYPE::MOTOR_VIRTUAL_XY);
	fDeviceTypes.emplace("Solenoid",              eDEVICE_TYPE::SOLENOID );
	fDeviceTypes.emplace("PWMSignal",             eDEVICE_TYPE::PWM_SIGNAL );
	fDeviceTypes.emplace("PWMPower",              eDEVICE_TYPE::PWM_POWER );
	fDeviceTypes.emplace("SensorAnalogDirect",    eDEVICE_TYPE::SENSOR_ANALOG_DIRECT );
	fDeviceTypes.emplace("SensorLocal",           eDEVICE_TYPE::SENSOR_LOCAL );
	fDeviceTypes.emplace("SensorBoolDirect",      eDEVICE_TYPE::SENSOR_BOOL_DIRECT);
//	fDeviceTypes.emplace("SensorTemperature",     eDEVICE_TYPE::SENSOR_TEMPERATURE);
//	fDeviceTypes.emplace("SensorVolume",          eDEVICE_TYPE::SENSOR_VOLUME);

	fStepUnits.emplace("angle_deg",   eSTEP_UNIT::ANGLE_DEGREES );
	fStepUnits.emplace("mm",          eSTEP_UNIT::MM);

	fInputTypes.emplace("PNP",             eSENSOR_INPUT_TYPE::PNP );
	fInputTypes.emplace("0-20mA",          eSENSOR_INPUT_TYPE::MA_0_20 );
	fInputTypes.emplace("4-20mA",          eSENSOR_INPUT_TYPE::MA_4_20 );
	fInputTypes.emplace("0-10V",           eSENSOR_INPUT_TYPE::V0_10 );
	fInputTypes.emplace("PWM-RC",          eSENSOR_INPUT_TYPE::PWM_RC );
	fInputTypes.emplace("PWM-duty_cycle",  eSENSOR_INPUT_TYPE::PWM_DUTY );
	fInputTypes.emplace("SPI",             eSENSOR_INPUT_TYPE::SPI );
	fInputTypes.emplace("I2C",             eSENSOR_INPUT_TYPE::I2C );
}

