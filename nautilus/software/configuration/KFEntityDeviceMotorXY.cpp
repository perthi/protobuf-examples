// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/
#include "KFEntityDeviceMotorXY.h"

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>
using std::endl;


KFEntityDeviceMotorXY::KFEntityDeviceMotorXY()
{
	fDeviceType= eDEVICE_TYPE::MOTOR_VIRTUAL_XY;
}


KFEntityDeviceMotorXY::~KFEntityDeviceMotorXY()
{

}


string  
KFEntityDeviceMotorXY::str() const
{
	std::stringstream buffer;
	buffer << KFEntityDevice::str();
	buffer << g_utilities()->TabAlign("MOTOR_TRANSLATION_ID:") << fMotorTranslationID << endl;
    buffer << g_utilities()->TabAlign("MOTOR_ROTATION_ID:") << fMotorRotationID << endl;
	return buffer.str();
}

