// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBSubMessageSEMConfigSensorBool.h"


KFPBSubMessageSEMConfigSensorBool::KFPBSubMessageSEMConfigSensorBool() : KFPBMessageSEM( ( pb_field_t * )SEMConfigSensorBool_fields)
{
    Reset();
}

KFPBSubMessageSEMConfigSensorBool::~KFPBSubMessageSEMConfigSensorBool()
{

}


void  
KFPBSubMessageSEMConfigSensorBool::SetSignalType(const eSENSOR_INPUT_TYPE type )
{
    fCmd->signal_type = (int32_t)type;
    fCmd->has_signal_type = true;

}


void  
KFPBSubMessageSEMConfigSensorBool::SetActiveHigh(const bool val )
{
    fCmd->active_high = val;
    fCmd->has_active_high = true;
} 


void  
KFPBSubMessageSEMConfigSensorBool::SetAlarm(const bool val)
{
    fCmd->alarm = val;
    fCmd->has_alarm = true;
}


#if defined( __unix__ )  || defined (_WIN32 )
void  
KFPBSubMessageSEMConfigSensorBool::SetDeviceIDAux( const string device_id )
{
    KFPBMessageSEM::SetString( fCmd->device_id_aux, sizeof(fCmd->device_id_aux), device_id.c_str()  );
    fCmd->has_device_id_aux = true;
}


string  
KFPBSubMessageSEMConfigSensorBool::GetDeviceIDAux() const
{
    return  string(fCmd->device_id_aux);
}
#endif


void
KFPBSubMessageSEMConfigSensorBool::GetDeviceIDAux(char *id, const size_t max_size) const
{
    int n = max_size < sizeof( this->fCmd->device_id_aux ) ? max_size : sizeof( this->fCmd->device_id_aux );
    strncpy( id, (const char *)this->fCmd->device_id_aux, n );
}


void
 KFPBSubMessageSEMConfigSensorBool::SetDeviceIDAux(const char  *id, size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->device_id_aux ) ? max_size : sizeof( this->fCmd->device_id_aux);
    strncpy( this->fCmd->device_id_aux, id, n );
}



eSENSOR_INPUT_TYPE  
KFPBSubMessageSEMConfigSensorBool::GetSignalType() const
{
    return (eSENSOR_INPUT_TYPE)fCmd->signal_type;
}


bool     
KFPBSubMessageSEMConfigSensorBool::GetActiveHigh() const
{
    return fCmd->active_high;
}


bool     
KFPBSubMessageSEMConfigSensorBool::GetAlarm( ) const
{
    return fCmd->alarm;
}

bool 
KFPBSubMessageSEMConfigSensorBool::HasSignalType(  ) const
{
    return fCmd->has_signal_type;
}

bool 
KFPBSubMessageSEMConfigSensorBool::HasActiveHigh(  ) const
{
    return fCmd->has_active_high;
}

bool 
KFPBSubMessageSEMConfigSensorBool::HasAlarm( ) const
{
    return fCmd->has_alarm;
}

bool 
KFPBSubMessageSEMConfigSensorBool::HasDeviceIDAux( ) const
{
    return fCmd->has_device_id_aux;
}


void    
KFPBSubMessageSEMConfigSensorBool::Reset( SEMConfigSensorBool  *t )
{
    for(size_t i = 0; i < sizeof(t->device_id_aux)  ; i++ )
    {
        t->device_id_aux[i] = 0;
    }

    t->alarm = false;
    t->active_high = false;
    t->signal_type = 0;
    t->has_device_id_aux = false;
    t->has_alarm = false;
    t->has_active_high = false;
    t->has_signal_type = false;
}


void   
KFPBSubMessageSEMConfigSensorBool::Reset( )
{
    Reset(fCmd);
}


#if defined( __unix__ )  || defined (_WIN32 )
string   
KFPBSubMessageSEMConfigSensorBool::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("HAS_DEVICE_ID?:") << ( fCmd->has_device_id_aux == true ? "TRUE" : "FALSE" ) << endl;
    if( fCmd->has_device_id_aux == true )
    {
        buffer << g_utilities()->TabAlign("DEVICE_ID:") << fCmd->device_id_aux << endl;
    } 

    buffer << g_utilities()->TabAlign("HAS_ACTIVE_HIGH?:") << ( fCmd->has_active_high == true ? "TRUE" : "FALSE" ) << endl;
    if( fCmd->has_active_high == true )
    {
      buffer << g_utilities()->TabAlign("ACTIVE_HIGH?:") << ( fCmd->has_active_high == true ? "TRUE" : "FALSE (ACTIVE LOW)" ) << endl;  
    }

    buffer << g_utilities()->TabAlign("HAS_ALARM?:") << ( fCmd->has_alarm == true ? "TRUE" : "FALSE" ) << endl;
    if( fCmd->has_alarm == true )
    {
      buffer << g_utilities()->TabAlign("ALARM?:") << ( fCmd->alarm == true ? "TRUE" : "FALSE" ) << endl;  
    }

    buffer << g_utilities()->TabAlign("HAS_SIGNAL_TYPE?:") << ( fCmd->has_signal_type == true ? "TRUE" : "FALSE" ) << endl;
    if( fCmd->has_signal_type == true )
    {
        buffer << g_utilities()->TabAlign("SIGNAL_TYPE:") << fCmd->signal_type << endl;
    } 

    return buffer.str();
}
#endif