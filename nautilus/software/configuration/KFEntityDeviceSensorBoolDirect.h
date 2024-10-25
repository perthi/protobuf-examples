#pragma once
#include "KFEntityDeviceSensor.h"

struct KFEntityDeviceSensorBoolDirect : public KFEntityDeviceSensor
{
	KFEntityDeviceSensorBoolDirect() {};
	virtual ~KFEntityDeviceSensorBoolDirect() {};

	virtual  string  str() const override;

	bool fIsActiveHigh = false;
    bool fIsAlarm = false;

};

