// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/

#include "KFEntityDeviceSolenoid.h"
#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>
using std::endl;


string KFEntityDeviceSolenoid::str() const
{
	std::stringstream buffer;
	buffer << KFEntityDevice::str();
	buffer << g_utilities()->TabAlign("MAX_CURRENT:") << fMaxCurrent << endl;
	buffer << g_utilities()->TabAlign("ACTIVATE_CURRENT:") << fActivateCurrent << endl;
	buffer << g_utilities()->TabAlign("HOLD_CURRENT:") << fHoldCurrent << endl;
	return buffer.str();
}
