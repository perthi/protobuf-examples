// -*- mode: c++ -*-
#pragma once


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <string>
#include <protocol/KFProtocolEnums.h>
#include <configuration/KFPositionCamera.h>
#include <utilities/GDefinitions.h>
#include "KFConfig.h"

using std::string;

struct KFConfigCamera : public KFConfig
{
	KFConfigCamera() : fPosition() {};
	string API GetExposureTypeS();

	virtual  string  API str() const override;
	string fID = "";
	string fName = "";
	bool  fIsEnabled = true;
	eEXPOSURE_TYPE fExposutreType = eEXPOSURE_TYPE::AUTO;
	KFPositionCamera fPosition;
};

