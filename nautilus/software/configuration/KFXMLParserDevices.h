// -*- mode: c++ -*-
#ifndef KFXMLPARSERDEVICES_H
#define KFXMLPARSERDEVICES_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFXMLParser.h"

struct   KFEntityDevice;
// struct   KFEntityDeviceSensor;
struct   KFEntityDeviceMotor;
struct   KFDeviceAddress;
struct   KFConfigMotor;
struct   KFEntityDeviceMotorStepper;
struct   KFEntityDeviceMotorXY;
struct   KFEntityDeviceSolenoid;

//struct   KFEntityDeviceSensorAnalogDirect;
struct   KFSensorUnitConversion;
struct   KFSensorThresholds;

#include "KFEntityDeviceSensor.h"
#include "KFEntityDeviceSensorAnalogDirect.h"
#include "KFEntityDeviceSensorBoolDirect.h"
#include "KFEntityDeviceSensorLocal.h"
// #include "KFEntityDeviceSensorTemperature.h"
// #include "KFEntityDeviceSensorVolume.h"

#include "KFEntityDevicePWM.h"
#include "KFEntityDevicePWMSignal.h"
#include "KFEntityDevicePWMSignal.h"


class    GXmlStreamReader;
class    GXmlNode;


///#include "KFEnums.h"
#include <memory>
#include <map>

#include <vector>
using   std::vector;


#include <type_traits>


class  KFXMLParserDevices : public KFXMLParser
{
public:
	API KFXMLParserDevices();
	virtual API ~KFXMLParserDevices();
	virtual vector< std::shared_ptr<KFEntity> >  API ParseXML( const XMLFile_t  xml, const XSDFile_t xsd ) override;


private:
	void API         ParseXMLCommon(std::shared_ptr<GXmlStreamReader> xmlReader,   std::shared_ptr<KFEntityDevice>  entity  );
	API  std::shared_ptr<KFEntityDeviceMotorStepper>   ParseXMLMotorStepper(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);
	API  std::shared_ptr<KFEntityDeviceMotorXY>        ParseXMLMotorXY(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);
	API  std::shared_ptr<KFEntityDeviceSolenoid>      ParseXMLSolenoid(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);

	template<typename T>
	inline  std::shared_ptr<T>         ParseXMLSensor(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);

	template<typename T>
	inline  std::shared_ptr<T>         ParseXMLPWM(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);

	bool       ParseXMLSensorUnitConversion( std::shared_ptr<GXmlStreamReader> xmlReader, KFSensorUnitConversion *unit_conversion );
	void       ParseXMLSensorThresholds(std::shared_ptr<GXmlStreamReader> xmlReader,  KFSensorThresholds *, const bool read_node = true );

	void API   ParseXMLDeviceAddress( std::shared_ptr<GXmlStreamReader> xmlReader,  KFDeviceAddress * );
	void API   ParseXMLMotorConfig(   std::shared_ptr<GXmlStreamReader> xmlReader,  KFConfigMotor   * );
	void InitHashMaps();

	void AddEntity( std::shared_ptr<KFEntityDevice> entity );

	std::map<string, eDEVICE_TYPE>  fDeviceTypes;
	std::map<string, eSTEP_UNIT >   fStepUnits;
	std::map<string, eSENSOR_INPUT_TYPE>  fInputTypes;
};



template<typename T>
inline std::shared_ptr<T>
KFXMLParserDevices::ParseXMLSensor(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag)
{
	static_assert(std::is_base_of<KFEntityDeviceSensor, T>::value, "T must inherit from KFEntityDeviceSensor");
	auto sensor = std::make_shared<T>();
	ParseXMLCommon(xmlReader, sensor );
	bool ret = ParseXMLSensorUnitConversion(xmlReader, &sensor->fUnitConversion );
	sensor->fHasUnitConversion = ret;
	ParseXMLSensorThresholds(xmlReader, &sensor->fTresholds, ret );
	sensor->fDeviceIDAux =  GetTagValue<string>(xmlReader, "DEVICE_ID_AUX", GLOCATION);
	AssertTagCloseGroup( xmlReader, closing_tag, GLOCATION  );
	return sensor;
}


template< >
inline std::shared_ptr<KFEntityDeviceSensorBoolDirect >
KFXMLParserDevices::ParseXMLSensor(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag)
{
	static_assert(std::is_base_of< KFEntityDeviceSensor, KFEntityDeviceSensorBoolDirect>::value, "KFEntityDeviceSensorBoolDirect must inherit from KFEntityDeviceSensor");
	auto sensor = std::make_shared<KFEntityDeviceSensorBoolDirect >();
	ParseXMLCommon(xmlReader, sensor );
	string tmp = GetTagValue<string>(xmlReader, "INPUT_TYPE", GLOCATION );

	sensor->fUnitConversion.fInputType  = String2Enum(tmp, &fInputTypes);
	sensor->fUnitConversion.fInputTypeS = tmp;

	sensor->fIsActiveHigh = GetTagValue<bool>(xmlReader, "ACTIVE_HIGH", GLOCATION);
	sensor->fIsAlarm = GetTagValue<bool>(xmlReader, "ALARM", GLOCATION);
	sensor->fDeviceIDAux =  GetTagValue<string>(xmlReader, "DEVICE_ID_AUX", GLOCATION);
	AssertTagCloseGroup( xmlReader, closing_tag, GLOCATION  );
	return sensor;
}



template<typename T>
inline  std::shared_ptr<T>
KFXMLParserDevices::ParseXMLPWM(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag)
{
	static_assert(std::is_base_of< KFEntityDevicePWM, T>::value, "T must inherit from KFEntityDevicePWM");
	auto pwm = std::make_shared< T >();
	ParseXMLCommon(xmlReader, pwm );
	bool ret = ParseXMLSensorUnitConversion(xmlReader, &pwm->fUnitConversion );
	
	pwm->fHasUnitConversion = ret;

	pwm->fMinLevel = GetTagValue<float>( xmlReader, "MIN_LEVEL", GLOCATION, ret);
	pwm->fMaxLevel = GetTagValue<float>( xmlReader, "MAX_LEVEL", GLOCATION);
//	pwm->fLevel    = GetTagValue<float>( xmlReader, "LEVEL", GLOCATION);

	AssertTagCloseGroup( xmlReader, closing_tag, GLOCATION  );

	return pwm;
}


#endif
