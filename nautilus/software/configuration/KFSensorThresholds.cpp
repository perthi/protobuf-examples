// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/
#include "KFSensorThresholds.h"

#include <utilities/GException.h>

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;


KFSensorThresholds::KFSensorThresholds()
{

}

KFSensorThresholds::~KFSensorThresholds()
{

}


string
KFSensorThresholds::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("HAS_ALARM_LOW ?:") << ( fHasAlarmLow == true ? "TRUE" : "FALSE" )<< endl ;
    if( fHasAlarmLow == true  )
    {
        buffer << g_utilities()->TabAlign("ALARM_LOW:")     <<  fAlarmLow     <<  endl;
    }
    

    buffer << g_utilities()->TabAlign("HAS_WARNING_LOW ?:") << ( fHasWarningLow == true ? "TRUE" : "FALSE" )<< endl ;
    
    if( fHasWarningLow == true )
    {
        buffer << g_utilities()->TabAlign("WARNING_LOW:")   <<  fWarningLow   <<  endl;
    }

    buffer << g_utilities()->TabAlign("HAS_WARNING_HIGH ?:") << ( fHasWarningHigh == true ? "TRUE" : "FALSE" )<< endl ;
    
     
    if( fHasWarningHigh == true )
    {
        buffer << g_utilities()->TabAlign("WARNING_HIGH:")   <<  fWarningHigh   <<  endl;
    }
    
    buffer << g_utilities()->TabAlign("HAS_ALARM_HIGH ?:") << ( fHasAlarmHigh == true ? "TRUE" : "FALSE" )<< endl ;
    if( fHasAlarmHigh == true )
    {
        buffer << g_utilities()->TabAlign("ALARM_HIGH:")   <<  fAlarmHigh   <<  endl;
    }
    
    return buffer.str();
}


void 
KFSensorThresholds::ValidateThresholds()
{
    ENGINE_ASSERT_EXCEPTION(  fAlarmLow    <=  fWarningLow,   "expected  ALARM_LOW < WARNING_LOW, got ALARM_LOW = %d and WARNING_LOW = %s",        fAlarmLow, fWarningLow );
    ENGINE_ASSERT_EXCEPTION(  fWarningLow  <=  fWarningHigh,  "expected  WARNING_LOW < WARNING_HIGH, got WARNING_LOW = %d and WARNING_HIGH = %d",  fWarningLow, fWarningHigh );
    ENGINE_ASSERT_EXCEPTION(  fWarningHigh <=  fAlarmHigh,    "expected  WARNING_HIGH < ALARM_HIGH, got WARNING_HIGH = %d and ALARM_HIGH = %d",    fWarningHigh, fAlarmHigh );
}

