#pragma once

#include "KFConfig.h"
#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>


#include <protocol/KFProtocolEnums.h>


struct KFConfigMotor : public KFConfig
{
	virtual  string API str() const override;
	float  fEndStopPositive = 0;
	float  fEndStopNegative = 0;
	bool fHasEndStopPositive = false;
	bool fHasEndStopNegative = false;
	float fMaxSpeed = 0;
	float fSpeed = 0;
	float fMaxAccelleration = 0;
	float fAccelleration = 0;
	float fMaxCurrent = 0;
	float fCurrent = 0;
	float fInactiveTimeout = 0;
	float fInactiveCurrent = 0;
	string fHomeDeviceID = "";
	float fHomeValue = 0;
	string  fEndStopPositiveID = "";
	string  fEndStopNegativeID = "";
	bool fHasDirectionHome = true;
	eDIRECTION fDirectionHome = eDIRECTION::UNKNOWN;
	eDIRECTION fDirectionPositive =  eDIRECTION::UNKNOWN;

};

