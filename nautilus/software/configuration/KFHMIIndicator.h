#pragma once


#include "KFHMICaption.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

//#include "KFEnums.h"
#include <protocol/KFProtocolEnums.h>
#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>

struct KFHMIIndicator : public GPrintable
{
	virtual  string API  str() const override;	
	KFHMICaption fCaption;
	int fMinValue = 0;
	int fMaxValue = 0;
	string fDeviceID = "";
	eORIENTATION fOrientation = eORIENTATION::HORIZONTAL;
	bool fCanDecrement = true;
};
