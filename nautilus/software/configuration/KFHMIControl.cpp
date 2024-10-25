
#include "KFHMIControl.h"


#include <utilities/GException.h>

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;



string
KFHMIControl::str() const
{
    std::stringstream buffer;
    buffer <<  fCaption.str();    
    buffer <<  g_utilities()->TabAlign("MIN:") << fMinValue << endl;
    buffer <<  g_utilities()->TabAlign("MAX:") << fMaxValue << endl;
    buffer <<  g_utilities()->TabAlign("DEVICE_ID:") << fDeviceID << endl;
    buffer <<  g_utilities()->TabAlign("ORIENTATION:") << (int)fOrientation << endl;
    buffer <<  g_utilities()->TabAlign("STEPS:") << g_utilities()->Vec2String(fSteps, ",");
    return buffer.str();
}