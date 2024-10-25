// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMMessageConfigurationStatusReply.h"


KFPBSubMessageSEMMessageConfigurationStatusReply::KFPBSubMessageSEMMessageConfigurationStatusReply(): 
KFPBMessageSEMMessageCommon ( (pb_field_t *  ) SEMMessageConfigurationStatusReply_fields )
{
    Reset();
}

KFPBSubMessageSEMMessageConfigurationStatusReply::~KFPBSubMessageSEMMessageConfigurationStatusReply()
{

}


void
KFPBSubMessageSEMMessageConfigurationStatusReply::Reset(  )
{
    Reset(fCmd);
}


void
KFPBSubMessageSEMMessageConfigurationStatusReply::Reset( SEMMessageConfigurationStatusReply *t)
{
    t->error_code = 0;
    t->has_error_code= false;
    t->has_error_string = false;

    for(size_t i=0; i < sizeof( t->error_string ); i ++ )
    {
        t->error_string[i] = 0;
    }

}



#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMMessageConfigurationStatusReply::str() const
{
    return   KFPBMessageSEMMessageCommon::str();
}


string
KFPBSubMessageSEMMessageConfigurationStatusReply::strOneLine() const
{
    GText buffer(
        "%-16s]\t\t\t\t\t\t\tE    %s",
        (HasErrorCode() ? KFProtocolUtilities::Enum2String(GetErrorCode()).c_str() : ""),
        (HasErrorString() ? GetErrorString().c_str() : "")
        );

    return buffer.str();
}



#endif
