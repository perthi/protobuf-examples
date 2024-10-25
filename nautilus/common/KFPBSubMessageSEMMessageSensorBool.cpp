// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMMessageSensorBool.h"
//#include <utilities/GUtilities.h>
#include <sstream>

KFPBSubMessageSEMMessageSensorBool::KFPBSubMessageSEMMessageSensorBool() : KFPBMessageSEMMessageCommon ( (pb_field_t *  )SEMMessageSensorBool_fields )
{
        Reset();
}

KFPBSubMessageSEMMessageSensorBool::~KFPBSubMessageSEMMessageSensorBool()
{

}


void
KFPBSubMessageSEMMessageSensorBool::SetValueConverted( int32_t val)
{
    fCmd->value_converted = val;
}


void
KFPBSubMessageSEMMessageSensorBool::SetValueRaw( const int32_t raw_value )
{
    fCmd->value_raw = raw_value;
    fCmd->has_value_raw = true;
}


int32_t
KFPBSubMessageSEMMessageSensorBool::GetValueConverted( ) const
{
    return fCmd->value_converted;
}


int32_t
KFPBSubMessageSEMMessageSensorBool::GetValueRaw(  ) const
{
    return fCmd->value_raw;

}


bool
KFPBSubMessageSEMMessageSensorBool::HasValueRaw() const
{
    return fCmd->has_value_raw;
}


void
KFPBSubMessageSEMMessageSensorBool::Reset(  )
{
    Reset( fCmd );
}


void
KFPBSubMessageSEMMessageSensorBool::Reset( SEMMessageSensorBool *t)
{
    t->has_value_raw = false;
    t->state = 0;
    t->value_converted = 0;
    t->value_raw = 0;
}

#if defined( __unix__ )  || defined (_WIN32 )

string
KFPBSubMessageSEMMessageSensorBool::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("STATE:") << KFProtocolUtilities::Enum2String(GetState()) << endl;
    buffer << g_utilities()->TabAlign("VALUE_CONVERTED:") << GetValueConverted() << endl;

    buffer << g_utilities()->TabAlign("HAS_RAW_VALUE ?:") << ( HasValueRaw() == true ? "TRUE" : "FALSE") << endl;
    if( HasValueRaw() == true )
    {
        buffer << g_utilities()->TabAlign("RAW VALUE:") << GetValueRaw() <<  endl;
    }

    buffer << KFPBMessageSEMMessageCommon::str();

    return buffer.str();
}


string
KFPBSubMessageSEMMessageSensorBool::strOneLine() const
{

    GText buffer(
        "%-16s] VAL[%4d]\tRAW[%-8s]",
        KFProtocolUtilities::Enum2String(GetState()).c_str(),
        GetValueConverted(),
        (HasValueRaw() ? std::to_string(GetValueRaw()).c_str() : "FALSE"));

    return buffer.str();
}


#endif
