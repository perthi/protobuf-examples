
#pragma once


#include <sstream>

#include <string>

using std::string;
#include <utilities/GPrintable.h>
#include <utilities/GUtilities.h>
#include <iomanip>

struct KFDeviceInfo : public GPrintable
{
    string fDeviceId = "NOT_SET";
    string fErrorMsg = "";
    double fEpochTime = -1; // time in seconds since 1.Januar 1970 UTC 00:00:00
    float  fVal1  = -1;
    float  fVal2  = -1;
    int    fState = -1;

    inline virtual string str() const override;

};

 inline  string
 KFDeviceInfo::str() const
 {
     std::stringstream buffer;
     buffer << g_utilities()->TabAlign("DEVICE_ID:")   << fDeviceId << endl;
     buffer << g_utilities()->TabAlign("EPOCH_TIME:")  << std::fixed << std::setprecision(4) <<  fEpochTime  << endl;
     buffer << g_utilities()->TabAlign("VAL1:") <<    fVal1  << endl;
     buffer << g_utilities()->TabAlign("VAL2:") <<    fVal2  << endl;
     buffer << g_utilities()->TabAlign("STATE:") <<   fState << endl;
     buffer << g_utilities()->TabAlign("ERROR_MSG:") << ( fErrorMsg == "" ? "(none)" : fErrorMsg ) << endl;
     return buffer.str();
 }