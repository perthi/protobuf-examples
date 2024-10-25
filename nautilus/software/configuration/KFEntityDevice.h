// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include <string>
using std::string;


#include <utilities/GDefinitions.h>

#include "KFEntity.h"
#include "KFDeviceAddress.h"
//#include "KFEnums.h"
#include <protocol/KFProtocolEnums.h>

struct  KFEntityDevice : public KFEntity
{
    API KFEntityDevice();
    virtual API ~KFEntityDevice();
    virtual  string API str() const override = 0;
    KFDeviceAddress fAddress;
    eDEVICE_TYPE   fDeviceType = eDEVICE_TYPE::UNKNOWN;
    string fDeviceTypeS = "";

};

