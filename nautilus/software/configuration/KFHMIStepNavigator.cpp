
#include "KFHMIStepNavigator.h"


#include <utilities/GException.h>

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;


string
KFHMIStepNavigator::str() const
{
    std::stringstream buffer;
    buffer <<  fCaption  <<  endl;
    buffer <<  g_utilities()->TabAlign("DEVICE_ID:")  << fDeviceID << endl;
    buffer <<  g_utilities()->TabAlign("STEPS:") << g_utilities()->Vec2String(fSteps, ",") << endl;
    buffer <<  g_utilities()->TabAlign("ORIENTATION:") << (int)fOrientation << endl;

    return buffer.str();
}

