
#include "KFHMIIndicator.h"



#include <utilities/GException.h>

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;



string
KFHMIIndicator::str() const
{
    std::stringstream buffer;
    buffer <<  fCaption.str();    
    buffer <<  g_utilities()->TabAlign("MIN:") << fMinValue << endl;
    buffer <<  g_utilities()->TabAlign("MAX:") << fMaxValue << endl;
    buffer <<  g_utilities()->TabAlign("DEVICE_ID:") << fDeviceID << endl;
    buffer <<  g_utilities()->TabAlign("ORIENTATION:") << (int)fOrientation << endl;
    buffer << g_utilities()->TabAlign("CAN DECREMENT ?:") << ( fCanDecrement == true ?  "TRUE" : "FALSE") << endl;
    return buffer.str();
}
