#pragma once

#include "KFCard.h"


#include <string>
using std::string;
#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>

struct KFDeviceAddress : public GPrintable
{
    virtual  string API str() const override;
    string  fDeviceID = "";
    string  fName = "";
    string  fIPAddress = "";
    KFCard  fCard;
};
