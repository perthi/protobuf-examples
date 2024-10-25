#include "KFEntityDeviceSensorBoolDirect.h"

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>
using std::endl;


string 
KFEntityDeviceSensorBoolDirect::str() const
{
	std::stringstream buffer;
	buffer << KFEntityDevice::str() << endl;
	buffer << g_utilities()->TabAlign("INPUT_TYPE:")      <<  fUnitConversion.fInputTypeS << "(" << (int)fUnitConversion.fInputType << ")" << endl;
	buffer << g_utilities()->TabAlign("ACTIVE_HIGH ?: ")  <<  ( fIsActiveHigh == true ? "TRUE" : "FALSE") << endl;
        buffer << g_utilities()->TabAlign("ALARM ?: ")  <<  ( fIsAlarm == true ? "TRUE" : "FALSE") << endl;
	return buffer.str();
}
