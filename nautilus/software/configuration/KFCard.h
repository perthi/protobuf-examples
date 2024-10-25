#pragma once

#include <string>

using std::string;


#include <utilities/GPrintable.h>

#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>

struct KFCard : public GPrintable
{
    virtual  string API str() const override;
    string fManufacturerID = "";
    string fCardName = "";
    int    fCardID = 0;
    int    fPort = 0;
};
