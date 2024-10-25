
#pragma once


#include "KFEntityDevice.h"
#include "KFDeviceAddress.h"
//#include "KFEnums.h"
#include "KFConfigMotor.h"
#include <protocol/KFProtocolEnums.h>

struct 
KFEntityDeviceMotorStepper : public KFEntityDevice
{
public:
	KFEntityDeviceMotorStepper();
	virtual  string API str() const override;

	eSTEP_UNIT    fUnit;
	string fUnitS = "";
	float  fUnitConversion = 0;
	KFConfigMotor fConfig;
};

