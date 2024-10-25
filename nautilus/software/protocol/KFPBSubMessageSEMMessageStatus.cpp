// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "KFPBSubMessageSEMMessageStatus.h"

KFPBSubMessageSEMMessageStatus::KFPBSubMessageSEMMessageStatus() : KFPBMessageSEMMessageCommon ( (pb_field_t *  )SEMMessageStatus_fields )
{
    Reset();
}




KFPBSubMessageSEMMessageStatus::~KFPBSubMessageSEMMessageStatus()
{

}


// void
// KFPBSubMessageSEMMessageStatus::SetState( const eSEM_SEM_STATE state )
// {
//     fCmd->state = (int)state;
// }


void
KFPBSubMessageSEMMessageStatus::SetConfigurationCRC(const int32_t crc)
{
    fCmd->configuration_crc = crc;
    fCmd->has_configuration_crc = true;
}



// eSEM_SEM_STATE
// KFPBSubMessageSEMMessageStatus::GetState() const
// {
//     return  (eSEM_SEM_STATE)fCmd->state;
// }


int32_t
KFPBSubMessageSEMMessageStatus::GetConfigurationCRC() const
{
    return fCmd->configuration_crc;
}


bool
KFPBSubMessageSEMMessageStatus::HasConfigurationCRC() const
{
    return fCmd->has_configuration_crc;
}



void
KFPBSubMessageSEMMessageStatus::Reset(  )
{
    Reset(fCmd);
}


void
KFPBSubMessageSEMMessageStatus::Reset( SEMMessageStatus *t)
{
    t->configuration_crc = 0;
    t->has_configuration_crc = false;
    t->has_error_string = 0;
    t->state = 0;

    for( size_t i = 0; i  < sizeof(t->error_string); i++ )
    {
        t->error_string[i] = 0;
    }
}



#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMMessageStatus::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("STATE:") << KFProtocolUtilities::Enum2String(GetState()) << endl;
    buffer << g_utilities()->TabAlign("HAS_CRC ?:") << ( HasErrorString() == true ? "TRUE" : "FALSE") << endl;

    if( HasConfigurationCRC() == true )
    {
        buffer << g_utilities()->TabAlign("CRC:") << GetConfigurationCRC() << endl;
    }

    buffer << KFPBMessageSEMMessageCommon::str();

    return buffer.str();

}
#endif