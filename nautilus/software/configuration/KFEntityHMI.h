// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include <string>
using std::string;

#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>

#include "KFEntity.h"
#include "KFDeviceAddress.h"
#include <protocol/KFProtocolEnums.h>


struct  KFEntityHMI : public KFEntity
{
	API KFEntityHMI();
	virtual API ~KFEntityHMI();
	virtual  string API str() const override = 0;
	eHMI_TYPE fType = eHMI_TYPE::UNKNOWN;
	string fTitle = "";
	string fHMIID = "";

};

