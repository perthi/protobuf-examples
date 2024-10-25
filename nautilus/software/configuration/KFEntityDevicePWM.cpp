#include "KFEntityDevicePWM.h"


#include "KFEntityDeviceSolenoid.h"
#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>
using std::endl;


string 
KFEntityDevicePWM::str() const
{
	std::stringstream buffer;
	buffer << KFEntityDevice::str();
	buffer << g_utilities()->TabAlign("MIN_LEVEL:") << fMinLevel << endl;
	buffer << g_utilities()->TabAlign("MAX_LEVEL:") << fMaxLevel << endl;
//	buffer << g_utilities()->TabAlign("LEVEL:") << fLevel << endl;
	return buffer.str();
}
