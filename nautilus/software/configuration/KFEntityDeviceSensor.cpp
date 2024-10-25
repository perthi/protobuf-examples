// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/
#include "KFEntityDeviceSensor.h"

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>
using std::endl;

KFEntityDeviceSensor::KFEntityDeviceSensor()
{

}

KFEntityDeviceSensor::~KFEntityDeviceSensor()
{

}


string  
KFEntityDeviceSensor::str() const
{
	std::stringstream buffer;
    buffer << KFEntityDevice::str();
    buffer << g_utilities()->TabAlign("HAS_UNIT_CONVERSION ?:") <<  ( fHasUnitConversion == true ? "TRUE" : "FALSE" );
    
    if( fHasUnitConversion == true )
    {
        buffer  <<  fUnitConversion.str();
    }

    buffer  <<  fTresholds.str(); 
    return buffer.str();
}