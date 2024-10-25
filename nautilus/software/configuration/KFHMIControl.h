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


struct KFHMIControl : public  GPrintable
{
	virtual  string  API str() const override;	

	KFHMICaption fCaption;
	int fMinValue = 0;
	int fMaxValue = 0;
	string fDeviceID = "";
	vector<int> fSteps;
	eORIENTATION fOrientation = eORIENTATION::HORIZONTAL;
};
