// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBSubMessageSEMMessageSolenoid.h"


KFPBSubMessageSEMMessageSolenoid::KFPBSubMessageSEMMessageSolenoid() : KFPBMessageSEMMessageCommon ( (pb_field_t *  )SEMMessageSolenoid_fields )
{
    Reset();
}



KFPBSubMessageSEMMessageSolenoid::~KFPBSubMessageSEMMessageSolenoid()
{

}


void
KFPBSubMessageSEMMessageSolenoid::Reset(  )
{
    Reset(fCmd);
}


void
KFPBSubMessageSEMMessageSolenoid::Reset( SEMMessageSolenoid *t)
{
    t->error_code = 0;
    t->has_error_code= false;
    t->has_error_string = false;
    t->state = 0;

    for(size_t i=0; i < sizeof( t->error_string ); i ++ )
    {
        t->error_string[i] = 0;
    }

}



#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMMessageSolenoid::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("STATE:") << KFProtocolUtilities::Enum2String(GetState()) << endl;
    buffer << KFPBMessageSEMMessageCommon::str();
    return buffer.str();
}


string
KFPBSubMessageSEMMessageSolenoid::strOneLine() const
{

    GText buffer(
        "%-16s]\t\t\t\t\t\t\tE[%s]%s",
        KFProtocolUtilities::Enum2String(GetState()).c_str(),
        (HasErrorCode() ? KFProtocolUtilities::Enum2String(GetErrorCode()).c_str() : "FALSE"),
        (HasErrorString() ? GetErrorString().c_str() : "")
        );

    return buffer.str();
}


#endif