#pragma once


#include "KFHMICaption.h"
#include "KFHMIControl.h"
#include "KFHMIStepNavigator.h"


#include <vector>

using std::vector;

#include "KFEntityHMI.h"

struct KFEntityHMIHabitat : public KFEntityHMI
{
    virtual  string  str() const override;
    KFHMIStepNavigator  fForeNavigator;
    KFHMIStepNavigator  fAftNavigator;
    KFHMIControl fLedExtControl;
    KFHMIControl fLedIntControl;
    KFHMIControl fM1Control;
    KFHMIControl fM2Control;
};
