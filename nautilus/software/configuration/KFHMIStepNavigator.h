#pragma once


#include "KFHMICaption.h"
///#include "KFEnums.h"

#include <protocol/KFProtocolEnums.h>
#include <string>
using std::string;
#include <vector>
using std::vector;

#include <utilities/GPrintable.h>


struct KFHMIStepNavigator : public GPrintable
{
    virtual  string  str() const override;	
    KFHMICaption fCaption;
    string fDeviceID = "";
    vector<int> fSteps;
    eORIENTATION fOrientation = eORIENTATION::HORIZONTAL;
};
