
#include "KFEntityHMIOperation.h"

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;




string
KFEntityHMIOperation::str() const
{
    std::stringstream buffer;
    buffer << KFEntityHMI::str() << endl;
    buffer << fNavigatorMain.str() << endl;
    buffer << fIndicatorMain.str() << endl;

    for(size_t i =0; i<  fControls.size(); i++  )
    {
        buffer << "******** CONTROL#" << i << "***********" << endl;
        buffer << fControls.at(i).str() << endl;
    }
    return buffer.str();
}