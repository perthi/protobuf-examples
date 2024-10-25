

#include "KFHMIControlGroup.h"
#include <utilities/GException.h>
#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;



string
KFHMIControlGroup::str() const
{
    std::stringstream buffer;
    buffer << fControl << endl;
    buffer << fIndicator << endl;
    return buffer.str();
}