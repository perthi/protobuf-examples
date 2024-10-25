// -*- mode: c++ -*-
#ifndef KFEntityDeviceSOLENOID_H
#define KFEntityDeviceSOLENOID_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/


#include "KFEntityDevice.h"

struct  KFEntityDeviceSolenoid : public KFEntityDevice
{
	virtual  string  str() const override;
	float fMaxCurrent = 0;
	float fActivateCurrent = 0;
	float fHoldCurrent = 0;
};


#endif
