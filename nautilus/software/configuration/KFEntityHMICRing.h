#pragma once

#include "KFHMICaption.h"
#include "KFHMIControl.h"
#include "KFHMIIndicator.h"
#include "KFHMIStepNavigator.h"


#include "KFEntityHMI.h"


struct KFEntityHMICRing : public KFEntityHMI
{
	virtual  string API str() const override;

	string fDeviceID = "";

	KFHMIStepNavigator fNavigatorTranslation;
	KFHMIStepNavigator fNavigatorRotation;
	KFHMIIndicator fIndicatorTranslation;
	KFHMIIndicator fIndicatorRotation;
};
