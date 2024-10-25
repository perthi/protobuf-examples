// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBSubMessageSEMMessageCommandStatusReply.h"


KFPBSubMessageSEMMessageCommandStatusReply::KFPBSubMessageSEMMessageCommandStatusReply():
KFPBMessageSEMMessageCommon ( (pb_field_t *  ) SEMMessageCommandStatusReply_fields )
{
    Reset();
}

KFPBSubMessageSEMMessageCommandStatusReply::~KFPBSubMessageSEMMessageCommandStatusReply()
{

}


bool
KFPBSubMessageSEMMessageCommandStatusReply::HasStatusCode() const
{
    return fCmd->has_error_code;
}


void
KFPBSubMessageSEMMessageCommandStatusReply::Reset(  )
{
    Reset(fCmd);
}


void
KFPBSubMessageSEMMessageCommandStatusReply::Reset( SEMMessageCommandStatusReply *t)
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
KFPBSubMessageSEMMessageCommandStatusReply::str() const
{
    return  KFPBMessageSEMMessageCommon::str();
}


string
KFPBSubMessageSEMMessageCommandStatusReply::strOneLine() const
{
    GText buffer(
        "%-16s]\t\t\t\t\t\t\tE    %s",
        (HasErrorCode() ? KFProtocolUtilities::Enum2String( this->GetErrorCode()).c_str() : ""),
        (HasErrorString() ? GetErrorString().c_str() : "")
        );

    return buffer.str();
}


#endif
