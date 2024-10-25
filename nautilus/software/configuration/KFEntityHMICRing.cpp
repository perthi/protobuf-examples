

#include "KFEntityHMICRing.h"
#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;




string
KFEntityHMICRing::str() const
{
    std::stringstream buffer;
    buffer << KFEntityHMI::str() << endl;
    buffer << g_utilities()->TabAlign("DEVICE_ID:") << fDeviceID << endl;
    buffer << "**** NAVIGATOR TRANSLATION ********" << endl;
    buffer << fNavigatorTranslation << endl;
    buffer << "**** NAVIGATOR ROTATION ***********" << endl;
    buffer << fNavigatorRotation << endl;
    buffer << "**** INDICATOR TRANSLATION ********" << endl;
    buffer << fIndicatorTranslation << endl;
    buffer << "**** INDICATOR ROTATION ***********" << endl;
    buffer <<  fIndicatorRotation << endl;
    return buffer.str();
}