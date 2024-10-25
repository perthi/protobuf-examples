// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "KFPBSubMessageSEMMessageSensor.h"

KFPBSubMessageSEMMessageSensor::KFPBSubMessageSEMMessageSensor() : KFPBMessageSEMMessageCommon ( (pb_field_t *  )SEMMessageSensor_fields )
{
    Reset();
}

KFPBSubMessageSEMMessageSensor::~KFPBSubMessageSEMMessageSensor()
{

}


void
KFPBSubMessageSEMMessageSensor::SetValueConverted( float val)
{
    fCmd->value_converted = val;

}


void
KFPBSubMessageSEMMessageSensor::SetValueRaw( const int32_t raw_value )
{
    fCmd->value_raw = raw_value;
    fCmd->has_value_raw = true;
}


void
KFPBSubMessageSEMMessageSensor::SetAlarmStatus( eSEM_SENSOR_ALARM_STATUS status)
{
    fCmd->alarm_status =  (int)status;
}


float
KFPBSubMessageSEMMessageSensor::GetValueConverted( ) const
{
    return fCmd->value_converted;
}


int32_t
KFPBSubMessageSEMMessageSensor::GetValueRaw( ) const
{
    return fCmd->value_raw;
}


eSEM_SENSOR_ALARM_STATUS
KFPBSubMessageSEMMessageSensor::GetAlarmStatus() const
{
    return  ( eSEM_SENSOR_ALARM_STATUS )fCmd->alarm_status;

}


bool
KFPBSubMessageSEMMessageSensor::HasValueRaw() const
{
    return fCmd->has_value_raw;
}


void
KFPBSubMessageSEMMessageSensor::Reset(  )
{
    Reset(fCmd);
}


void
KFPBSubMessageSEMMessageSensor::Reset( SEMMessageSensor *t)
{
    t->state = 0;
    t->value_converted = 0;
    t->has_value_raw = false;
    t->value_raw = 0;
    t->alarm_status = 0;
    t->has_error_code = false;
    t->error_code = 0;
    t->has_error_string = false;

    for(size_t i=0; i < sizeof( t->error_string ); i++  )
    {
        t->error_string[i] = 0;
    }

}



#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMMessageSensor::str() const
{
    std::stringstream buffer;

    buffer << g_utilities()->TabAlign("STATE:") <<  KFProtocolUtilities::Enum2String(GetState()) << endl;
    buffer << g_utilities()->TabAlign("VALUE_CONVERTED:") << GetValueConverted() << endl;
    buffer << g_utilities()->TabAlign("ALARM_STATUS:") << KFProtocolUtilities::Enum2String(GetAlarmStatus()) << endl;

    buffer << g_utilities()->TabAlign("HAS_RAW_VALUE ?:") << ( HasValueRaw() == true ? "TRUE" : "FALSE") << endl;

    if( HasValueRaw() == true )
    {
        buffer << g_utilities()->TabAlign("RAW VALUE:") << GetValueRaw() <<  endl;
    }

    buffer << KFPBMessageSEMMessageCommon::str();
    return buffer.str();
}


string
KFPBSubMessageSEMMessageSensor::strOneLine() const
{

    GText buffer(
        "%-16s] VAL[%-07.2f]\tRAW[%-8s]\tA[%-20s] E[%s]%s",
        KFProtocolUtilities::Enum2String(GetState()).c_str(),
        GetValueConverted(),
        (HasValueRaw() ? std::to_string(GetValueRaw()).c_str() : "--------"),
        KFProtocolUtilities::Enum2String(GetAlarmStatus()).c_str(),
        (HasErrorCode() ? KFProtocolUtilities::Enum2String(GetErrorCode()).c_str() : "-"),
        (HasErrorString() ? GetErrorString().c_str() : "")
        );

    return buffer.str();
}



#endif