// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBSubMessageSEMDeviceAddress.h"

#if defined( __unix__ )  || defined (_WIN32 )
#include <configuration/KFDeviceAddress.h>
#endif


#include <string.h>
#include <stdio.h>
#include <stdlib.h>


KFPBSubMessageSEMDeviceAddress::KFPBSubMessageSEMDeviceAddress() : KFPBMessageSEM( (pb_field_t * )SEMDeviceAddress_fields )
{
     Reset();
}

KFPBSubMessageSEMDeviceAddress::~KFPBSubMessageSEMDeviceAddress()
{

}

#if defined( __unix__ )  || defined (_WIN32 )
void 
 KFPBSubMessageSEMDeviceAddress::SetConfiguration( const KFDeviceAddress *  const address,  eDEVICE_TYPE type )
 {
     SetDeviceID (   address->fDeviceID );
     SetDeviceName(  address->fName  );
     SetDeviceType(  type );
     SetDevicePortNo( address->fCard.fPort );
     SetCardID( address->fCard.fCardID );
 }
#endif	

#if defined( __unix__ )  || defined (_WIN32 )
int 
KFPBSubMessageSEMDeviceAddress::SetDeviceID(const string id )
{
   KFPBMessageSEM::SetString(   fCmd->device_id,  sizeof( fCmd->device_id) ,  id.c_str() ); 
    return CMD_OK;
}



string  
KFPBSubMessageSEMDeviceAddress::GetDeviceID() const
{
    return string( fCmd->device_id );
}


void    
KFPBSubMessageSEMDeviceAddress::SetDeviceName(const string name) 
{
    KFPBMessageSEM::SetString(   fCmd->device_name,  sizeof( fCmd->device_name ) , name.c_str() ); 
    fCmd->has_device_name = true;
}

		
string  
KFPBSubMessageSEMDeviceAddress::GetDeviceName()
{
    return fCmd->device_name;
}
#endif



inline int
 KFPBSubMessageSEMDeviceAddress::GetDeviceID(char *id, const size_t max_size) const
{
    int n = max_size < sizeof( this->fCmd->device_id) ? max_size : sizeof( this->fCmd->device_id);
    // errno_t strcpy_s(char *restrict dest, rsize_t destsz, const char *restrict src);
    strncpy( id, (const char *)this->fCmd->device_id, n );
    return CMD_OK;
}

inline int 
 KFPBSubMessageSEMDeviceAddress::SetDeviceID(const char  *id, size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->device_id) ? max_size : sizeof( this->fCmd->device_id);
    strncpy( this->fCmd->device_id, id, n );
    return CMD_OK;
}


inline int
 KFPBSubMessageSEMDeviceAddress::GetDeviceName(char *id, const size_t max_size) const
{
    int n = max_size < sizeof( this->fCmd->device_name) ? max_size : sizeof( this->fCmd->device_name );
    // errno_t strcpy_s(char *restrict dest, rsize_t destsz, const char *restrict src);
    strncpy( id, (const char *)this->fCmd->device_name, n );
    return CMD_OK;
}


inline int 
 KFPBSubMessageSEMDeviceAddress::SetDeviceName(const char  *id, size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->device_name) ? max_size : sizeof( this->fCmd->device_name );
    strncpy( this->fCmd->device_name, id, n );
    return CMD_OK;
}



void    
KFPBSubMessageSEMDeviceAddress::SetDeviceType(const  eDEVICE_TYPE type)
{
    fCmd->device_type = (int32_t)type;
    fCmd->has_device_type = true;
}


eDEVICE_TYPE     
KFPBSubMessageSEMDeviceAddress::GetDeviceType() const
{
    return  ( eDEVICE_TYPE )fCmd->device_type;
}


void    
KFPBSubMessageSEMDeviceAddress::SetDevicePortNo(const int device_no)
{
    fCmd->device_port_no = device_no;
}


int     
KFPBSubMessageSEMDeviceAddress::GetDevicePortNo() const
{
    return fCmd->device_port_no;
}


void    
KFPBSubMessageSEMDeviceAddress::SetCardID(const int id)
{
    fCmd->card_id = id;
}


int 
KFPBSubMessageSEMDeviceAddress::GetCardID() const
{
    return fCmd->card_id;
}




void 
KFPBSubMessageSEMDeviceAddress::Reset(SEMDeviceAddress *t)
{
    t->card_id = 0;

    for(size_t i = 0; i < sizeof( t->device_id ); i++ )
    {
       t->device_id[i] = 0;       
    }

    for(size_t i = 0; i < sizeof(t->device_name ); i++ )
    {
       t->device_name[i] = 0;       
    }

    t->device_port_no = 0;
    t->device_type = 0;
    t->has_device_name = 0;
    t->has_device_type = 0;
}


void 
KFPBSubMessageSEMDeviceAddress::Reset(  )
{ 
    Reset(fCmd);
}




#if defined( __unix__ )  || defined (_WIN32 )
string      
KFPBSubMessageSEMDeviceAddress::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("DEVICE_ID:") << this->fCmd->device_id << endl;
    buffer << g_utilities()->TabAlign("CARD_ID:") << this->fCmd->card_id << endl;
    buffer << g_utilities()->TabAlign("DEVICE_NO:")  <<   this->fCmd->device_port_no << endl;
    buffer << g_utilities()->TabAlign("HAS_DEVICE_NAME:") << ( this->fCmd->has_device_name == true ? "TRUE" : "FALSE") << endl;
    if(this->fCmd->has_device_name == true)
    {
        buffer << g_utilities()->TabAlign("DEVICE_NAME:") << this->fCmd->device_name << endl;
    }
    
    buffer << g_utilities()->TabAlign("HAS_DEVICE_TYPE:") << ( this->fCmd->has_device_type == true ? "TRUE" : "FALSE") << endl;

    if(this->fCmd->has_device_type == true)
    {
        buffer << g_utilities()->TabAlign("DEVICE_NAME:") << this->fCmd->device_type << endl;
    }
    return buffer.str();
}
#endif

