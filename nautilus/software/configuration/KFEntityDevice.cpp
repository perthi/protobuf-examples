// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFEntityDevice.h"
#include <iostream>

#include <utilities/GUtilities.h>

KFEntityDevice::KFEntityDevice()
{

}

KFEntityDevice::~KFEntityDevice()
{

}

string 
KFEntityDevice::str() const
{
	std::stringstream buffer;
	buffer << fAddress.str();
	buffer << g_utilities()->TabAlign("DEVICE_TYPE:") << fDeviceTypeS  <<  " (" << (int)fDeviceType << ")" << endl;
	return buffer.str();
}
