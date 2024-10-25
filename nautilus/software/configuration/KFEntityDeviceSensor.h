// -*- mode: c++ -*-
#ifndef KFEntityDeviceSENSORanalogDIRECT_H
#define KFEntityDeviceSENSORanalogDIRECT_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/


#include "KFEntityDevice.h"
//#include "KFEnums.h"
#include <protocol/KFProtocolEnums.h>
#include "KFSensorUnitConversion.h"
#include "KFSensorThresholds.h"

struct  KFEntityDeviceSensor : public KFEntityDevice
{
    API KFEntityDeviceSensor();
    API virtual ~KFEntityDeviceSensor();

    virtual  string  API str() const override;	
    KFSensorUnitConversion fUnitConversion;
    bool fHasUnitConversion = true;
    
    KFSensorThresholds  fTresholds;
    
    string fDeviceIDAux = ""; //!< Device ID of aucillary sensor
};

#endif

