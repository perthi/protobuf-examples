// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMConfigVirtualXYMotors.h"


KFPBSubMessageSEMConfigVirtualXYMotors::KFPBSubMessageSEMConfigVirtualXYMotors() : KFPBMessageSEM( ( pb_field_t *  )SEMConfigVirtualXYMotors_fields )
{
    Reset();
}


KFPBSubMessageSEMConfigVirtualXYMotors::~KFPBSubMessageSEMConfigVirtualXYMotors()
{

}
 

void  
KFPBSubMessageSEMConfigVirtualXYMotors::SetDeviceX( const string device )
{
    KFPBMessageSEM::SetString(  fCmd->device_id_x,  sizeof( fCmd->device_id_x), device.c_str() );
}


void  
KFPBSubMessageSEMConfigVirtualXYMotors::SetDeviceY( const string device )
{
    KFPBMessageSEM::SetString(  fCmd->device_id_y,  sizeof( fCmd->device_id_y), device.c_str() );
}
		

string   
KFPBSubMessageSEMConfigVirtualXYMotors::GetDeviceX() const 
{
    return  string( fCmd->device_id_x );
}


string   
KFPBSubMessageSEMConfigVirtualXYMotors::GetDeviceY() const
{
    return  string( fCmd->device_id_y );
}


void  
KFPBSubMessageSEMConfigVirtualXYMotors::Reset( SEMConfigVirtualXYMotors *t) 
{
    for(size_t i=0; i< sizeof(t->device_id_x); i++)
    {
        t->device_id_x[i] = 0;
    } 
    for(size_t i=0; i< sizeof( t->device_id_y); i++)
    {
        t->device_id_y[i] = 0;
    } 

}


void   
KFPBSubMessageSEMConfigVirtualXYMotors::Reset(  )
{
    Reset(fCmd);
}


#if defined( __unix__ )  || defined (_WIN32 )
string     
KFPBSubMessageSEMConfigVirtualXYMotors::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("DEVICE_ID_X:") << fCmd->device_id_x << endl;
    buffer << g_utilities()->TabAlign("DEVICE_ID_Y:") << fCmd->device_id_y << endl;
    return buffer.str();
}
#endif