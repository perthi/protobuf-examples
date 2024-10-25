// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge                                 *
***************************************************/
#include "KFPBSubMessageSEMConfigSensorAnalog.h"


KFPBSubMessageSEMConfigSensorAnalog::KFPBSubMessageSEMConfigSensorAnalog() :  KFPBMessageSEM( ( pb_field_t * )SEMConfigSensorAnalog_fields ), fThresholds(),
                                                                             fLinearUnitConversion()
{
    fCmd->has_thresholds = true;
    fCmd->has_conversion = true;
    fThresholds.Set( &fCmd->thresholds );
    fLinearUnitConversion.Set( &fCmd->conversion );

    Reset();
    fCmd->has_thresholds = true;
    fCmd->has_conversion = true;
}


KFPBSubMessageSEMConfigSensorAnalog::~KFPBSubMessageSEMConfigSensorAnalog()
{


}

void
KFPBSubMessageSEMConfigSensorAnalog::Set( SEMConfigSensorAnalog *t)
{
    fCmd = t;
    fCmd->has_thresholds = true;
    fCmd->has_conversion = true;
    fThresholds.Set( &fCmd->thresholds );
    fLinearUnitConversion.Set( &fCmd->conversion );
}



KFPBSubMessageSEMThresholds *
KFPBSubMessageSEMConfigSensorAnalog::GetThresholds()
{
    return  &fThresholds;
}


KFPBSubMessageSEMLinearUnitConversion *
KFPBSubMessageSEMConfigSensorAnalog::GetConversion()
{
    return  &fLinearUnitConversion;
}


bool 
KFPBSubMessageSEMConfigSensorAnalog::HasUnitConversion() const
{
    if( fLinearUnitConversion.GetMaxInput() == 0 &&
         fLinearUnitConversion.GetMinInput() ==  0 &&
         fLinearUnitConversion.GetMaxOutput() == 0 &&
         fLinearUnitConversion.GetMinOutput() == 0 )
         {
             return false;
         }
     else
     {
         return true;
     }

    ///fLinearUnitConversi

}


void
KFPBSubMessageSEMConfigSensorAnalog::SetInputType(const eSENSOR_INPUT_TYPE input_type)
{
    fCmd->input_type = (int32_t)input_type;
    fCmd->has_input_type = true;
}


#if defined( __unix__ )  || defined (_WIN32 )
void
KFPBSubMessageSEMConfigSensorAnalog::SetDeviceIDAux( const string device_id )
{
   SetString( fCmd->device_id_aux, sizeof( fCmd->device_id_aux ), device_id.c_str() );
  fCmd->has_device_id_aux = true;
}


string
KFPBSubMessageSEMConfigSensorAnalog::GetDeviceIDAux() const
{
    return fCmd->device_id_aux;
}
#endif



void
 KFPBSubMessageSEMConfigSensorAnalog::GetDeviceIDAux(char *id, const size_t max_size) const
{
    int n = max_size < sizeof( this->fCmd->device_id_aux ) ? max_size : sizeof( this->fCmd->device_id_aux );
    strncpy( id, (const char *)this->fCmd->device_id_aux, n );
}


void
 KFPBSubMessageSEMConfigSensorAnalog::SetDeviceIDAux(const char  *id, size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->device_id_aux ) ? max_size : sizeof( this->fCmd->device_id_aux);
    strncpy( this->fCmd->device_id_aux, id, n );
}



eSENSOR_INPUT_TYPE
KFPBSubMessageSEMConfigSensorAnalog::GetInputType() const
{
    return  (eSENSOR_INPUT_TYPE)fCmd->input_type;
}



void
KFPBSubMessageSEMConfigSensorAnalog::Reset( SEMConfigSensorAnalog   *t)
{
    fThresholds.Reset();
	fLinearUnitConversion.Reset();

    for ( size_t i = 0; i <  sizeof( t->device_id_aux ); i++ )
    {
        t->device_id_aux[i] = 0;
    }

    t->has_device_id_aux = false;
    t->has_input_type = false;
    t->input_type = false;
    t->has_thresholds = true;
    t->has_conversion = true;
}


void
KFPBSubMessageSEMConfigSensorAnalog::Reset( )
{
    Reset(fCmd);
}

#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMConfigSensorAnalog::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("HAS_DEVICE_ID ?:") <<  ( fCmd->has_device_id_aux == true ? "TRUE" : "FALSE" )  << endl;

    if(  fCmd->has_device_id_aux == true  )
    {
        buffer << g_utilities()->TabAlign("DEVICE_ID:") << fCmd->device_id_aux << endl;
    }

    buffer << g_utilities()->TabAlign("INPUT_TYPE:") << fCmd->has_input_type << endl;

    if(fCmd->has_thresholds == true)
    {
        buffer << "*************   THRESHOLDS  BEGIN **************"  << endl;
        buffer << fThresholds.str() << endl;
        buffer << "*************   THRESHOLDS  END *****************"  << endl;
    }
    if(fCmd->has_conversion == true)
    {
        buffer << "*************   UNIT CONVERSION BEGIN **********"  <<  endl;
        buffer << fLinearUnitConversion.str() << endl;
        buffer << "*************   UNIT CONVERSION END **********"  <<  endl;
    }
    return buffer.str();
}
#endif
