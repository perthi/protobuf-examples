

#include "KFEntityDeviceMotorStepper.h"
#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;



KFEntityDeviceMotorStepper::KFEntityDeviceMotorStepper() 
{
	fDeviceType= eDEVICE_TYPE::MOTOR_STEPPER;
}


string 
KFEntityDeviceMotorStepper::str() const
{
	std::stringstream buffer;
 	buffer << KFEntityDevice::str();
	buffer << g_utilities()->TabAlign("UNIT:") <<  fUnitS << " (" << (int)fUnit  << ")" << endl;
	buffer << g_utilities()->TabAlign("UNIT_CONVERSION:") << fUnitConversion << endl;
	buffer << fConfig.str() << endl;
	
	return buffer.str();
}
