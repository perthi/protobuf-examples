// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBSubMessageSEMCrc.h"


KFPBSubMessageSEMCrc::KFPBSubMessageSEMCrc() : KFPBMessageSEM(  ( pb_field_t *  )SEMCrc_fields )
{
    Reset();
}
 
 
KFPBSubMessageSEMCrc::~KFPBSubMessageSEMCrc()
{

}

void
KFPBSubMessageSEMCrc::SetCrc(const int32_t crc )
{
    fCmd->crc = crc;
}


int32_t 
KFPBSubMessageSEMCrc::GetCrc() const
{
    return fCmd->crc;
}



void    
KFPBSubMessageSEMCrc::Reset( SEMCrc *t )
{
    t->crc = 0;
}
 

void  
KFPBSubMessageSEMCrc::Reset( )
{
     Reset(fCmd);
}
 

 #if defined( __unix__ )  || defined (_WIN32 )
 string     
 KFPBSubMessageSEMCrc::str() const
 {
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("CRC:") <<  fCmd->crc << endl;
    return buffer.str();
 }
 #endif