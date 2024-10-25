
#include "KFEntityHMIHabitat.h"

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;




string
KFEntityHMIHabitat::str() const
{
    std::stringstream buffer;
    buffer << KFEntityHMI::str() << endl;
    buffer << fForeNavigator.str() << endl;
    buffer << fAftNavigator.str() << endl;
    buffer << fLedExtControl.str() << endl;
    buffer << fLedIntControl.str() << endl;
    buffer << fM1Control.str() << endl;
    buffer << fM2Control.str() << endl;
    return buffer.str();
}