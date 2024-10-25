// -*- mode: c++ -*-
#ifndef KFEntityDeviceMOTORXY_H
#define KFEntityDeviceMOTORXY_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/


#include "KFEntityDevice.h"
//#include "KFEnums.h"
#include <protocol/KFProtocolEnums.h>

struct  KFEntityDeviceMotorXY : public KFEntityDevice
{
	
	KFEntityDeviceMotorXY();
	virtual ~KFEntityDeviceMotorXY();
	virtual  string  str() const override;
	string fMotorTranslationID = "";
	string fMotorRotationID = "";
};

#endif
