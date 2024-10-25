#include "KFDeviceAddress.h"


#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>
using std::endl;



string 
KFDeviceAddress::str() const
{
	std::stringstream buffer;
	buffer << g_utilities()->TabAlign("DEVICE_ID:") << fDeviceID << endl;
	buffer << g_utilities()->TabAlign("NAME:") << fName << endl;
	buffer << g_utilities()->TabAlign("IP_ADDRESS") << fIPAddress << endl;
	buffer << fCard.str();
	return buffer.str();
}
