#pragma once


#include "KFHMICaption.h"
#include "KFHMIControl.h"
#include "KFHMIIndicator.h"
#include "KFHMIStepNavigator.h"
#include "KFHMIControlGroup.h"

#include <vector>

using std::vector;

#include "KFEntityHMI.h"

struct KFEntityHMIOperation : public KFEntityHMI
{
    virtual  string  str() const override;
    KFHMIStepNavigator  fNavigatorMain;
    KFHMIIndicator      fIndicatorMain;
    vector<KFHMIControlGroup> fControls;
};
