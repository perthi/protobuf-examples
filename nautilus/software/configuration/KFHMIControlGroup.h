
#pragma once

#include "KFHMIControl.h"
#include "KFHMIIndicator.h"


#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>

struct KFHMIControlGroup : public GPrintable
{
	virtual  string  API str() const override;	
	KFHMIControl    fControl;
	KFHMIIndicator  fIndicator;
};
