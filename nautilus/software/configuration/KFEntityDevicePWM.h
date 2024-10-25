
#pragma once


#include "KFEntityDevice.h"
#include "KFSensorUnitConversion.h"



struct KFEntityDevicePWM : public KFEntityDevice
{
	KFEntityDevicePWM() : fUnitConversion() {};
	virtual ~KFEntityDevicePWM() {};
	virtual  string API str() const override;
	
	KFSensorUnitConversion fUnitConversion;
	bool fHasUnitConversion = true;
	
	float fMinLevel = -1;
	float fMaxLevel = -1;
	//float fLevel = -1;
};

