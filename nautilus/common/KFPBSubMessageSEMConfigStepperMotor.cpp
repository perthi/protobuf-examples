// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMConfigStepperMotor.h"
#include "KFPBSubMessageSEMStepUnitConversion.h"


KFPBSubMessageSEMConfigStepperMotor::KFPBSubMessageSEMConfigStepperMotor() : KFPBMessageSEM(  ( pb_field_t * ) SEMConfigStepperMotor_fields), fStepUnitConversion()
{
    Reset();
    fStepUnitConversion.Set( &fCmd->conversion );
}

KFPBSubMessageSEMConfigStepperMotor::~KFPBSubMessageSEMConfigStepperMotor()
{

}
 

void 
KFPBSubMessageSEMConfigStepperMotor::Set( SEMConfigStepperMotor  *ptr)
{
    fCmd = ptr;
    fStepUnitConversion.Set( &fCmd->conversion );
}


KFPBSubMessageSEMStepUnitConversion * 
KFPBSubMessageSEMConfigStepperMotor::GetStepUnitConversion()
{
     return &fStepUnitConversion;
}


void   
KFPBSubMessageSEMConfigStepperMotor::SetDirectionPositive( const  eDIRECTION dir )
{
    fCmd->direction_positive = (int)dir;

}


void   
KFPBSubMessageSEMConfigStepperMotor::SetDirectionHome( const eDIRECTION dir )
{
    fCmd->direction_home = (int)dir;
    fCmd->has_direction_home = true;
}


bool   
KFPBSubMessageSEMConfigStepperMotor::HasDirectionHome()
{
    return fCmd->has_direction_home;
}


eDIRECTION  
KFPBSubMessageSEMConfigStepperMotor::GetDirectionHome() const
{
   return  (eDIRECTION)fCmd->direction_home;
}


eDIRECTION  
KFPBSubMessageSEMConfigStepperMotor::GetDirectionPositive() const
{
   return  (eDIRECTION)fCmd->direction_positive;
}

void     
KFPBSubMessageSEMConfigStepperMotor::SetNegativeEndStop(const float val)
{
    fCmd->negative_soft_endstop = val;
    fCmd->has_negative_soft_endstop = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetPositiveEndStop(const float val)
{
    fCmd->positive_soft_endstop = val;
    fCmd->has_positive_soft_endstop = true;  
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetMaxSpeed(const float val)
{
    fCmd->max_speed = val;
    fCmd->has_max_speed = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetSpeed(const float val)
{
    fCmd->speed = val;
    fCmd->has_speed = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetMaxAccellleration(const float val)
{
    fCmd->max_acceleration = val;
    fCmd->has_max_acceleration = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetAccellleration(const float val)
{
    fCmd->acceleration = val;
    fCmd->has_acceleration = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetMaxCurrent(const float val)
{
    fCmd->max_current = val;
    fCmd->has_max_current = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetCurrent(const float val)
{
    fCmd->current = val;
    fCmd->has_current = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetInactiveTimeout(const float val)
{
    fCmd->inactive_timeout = val;
    fCmd->has_inactive_timeout = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetInativeCurrent(const float val)
{
    fCmd->inactive_current = val;
    fCmd->has_inactive_current = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetHomeValue(const float val)
{
    fCmd->home_value = val;
    fCmd->has_home_value = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetHomeId(const string id)
{
    KFPBMessageSEM::SetString(fCmd->home_device_id,  sizeof( fCmd->home_device_id), id.c_str() ); 
    fCmd->has_home_device_id = true;
}


void     
KFPBSubMessageSEMConfigStepperMotor::SetNegativeEndStopId(const string id)
{
    KFPBMessageSEM::SetString(fCmd->negative_soft_endstop_id,  sizeof( fCmd->negative_soft_endstop_id), id.c_str() ); 
    fCmd->has_negative_soft_endstop_id = true; 

}


void     
KFPBSubMessageSEMConfigStepperMotor::SetPositiveEndStopId(const string id)
{
    KFPBMessageSEM::SetString(fCmd->positive_soft_endstop_id,  sizeof( fCmd->positive_soft_endstop_id), id.c_str() );
    fCmd->has_positive_soft_endstop_id = true; 
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetNegativeEndStop() const
{
    return fCmd->negative_soft_endstop;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetPositiveEndStop() const
{
    return fCmd->positive_soft_endstop;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetMaxSpeed() const
{
    return fCmd->max_speed;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetSpeed() const
{
    return fCmd->speed;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetMaxAccellleration() const
{
    return fCmd->max_acceleration;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetAccellleration() const
{
    return fCmd->acceleration;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetMaxCurrent() const
{
    return fCmd->max_current;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetCurrent() const
{
    return fCmd->current;
}


float     
KFPBSubMessageSEMConfigStepperMotor::GetInactiveTimeout( ) const
{
    return fCmd->inactive_timeout;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetInativeCurrent( ) const
{
    return fCmd->inactive_current;
}


float    
KFPBSubMessageSEMConfigStepperMotor::GetHomeValue( ) const
{
    return fCmd->home_value;
}


string   
KFPBSubMessageSEMConfigStepperMotor::GetHomeId( ) const
{
    return string(fCmd->home_device_id) ;
}


string   
KFPBSubMessageSEMConfigStepperMotor::GetNegativeEndStopId( ) const
{
    return string(fCmd->negative_soft_endstop_id);

}


string   
KFPBSubMessageSEMConfigStepperMotor::GetPositiveEndStopId( ) const
{
    return string(fCmd->positive_soft_endstop_id);

}


bool  
KFPBSubMessageSEMConfigStepperMotor::HasNegativeEndstop() const
{
    return fCmd->has_negative_soft_endstop;
}



bool  
KFPBSubMessageSEMConfigStepperMotor::HasPositiveEndstop() const
{
    return fCmd->has_positive_soft_endstop;
}



void    
KFPBSubMessageSEMConfigStepperMotor::Reset(SEMConfigStepperMotor * t) 
{
    KFPBSubMessageSEMStepUnitConversion u;
    u.Reset( &t->conversion );
    t->direction_home = 0;
    t->direction_positive = 0;
    t->has_direction_home = false;
    t->has_negative_soft_endstop = false;
    t->negative_soft_endstop = 0;
    t->has_positive_soft_endstop =false;
    t->positive_soft_endstop = 0;
    t->has_max_speed = false;
    t->max_speed = 0;    
    t->has_speed = false;
    t->speed = 0;
    t->has_max_acceleration = false;
    t->max_acceleration = 0;
    t->has_acceleration = 0;
    t->acceleration = 0;
    t->has_max_current = false;
    t->max_current  = 0;
    t->has_current = false;
    t->current = 0;
    t->has_inactive_timeout = false;
    t->inactive_timeout = 0;
    t->has_inactive_current = false;
    t->inactive_current = 0;
    t->has_home_value = false;
    t->home_value = 0;
    t->has_home_device_id = false;
    
    
    for(size_t i=0; i < sizeof( t->home_device_id); i++ )
    {
       t->home_device_id[i]  = 0;
    }
    
    t->has_negative_soft_endstop_id = false;
    
    for(size_t i=0; i < sizeof( t->negative_soft_endstop_id ); i ++ )
    {
       t->negative_soft_endstop_id[i] = 0; 
    }

    t->has_positive_soft_endstop_id = false;

    for( size_t i=0; i < sizeof(t->positive_soft_endstop_id); i++ )
    {
        t->positive_soft_endstop_id[i] = 0;
    }
}


void    
KFPBSubMessageSEMConfigStepperMotor::Reset(  ) 
{
	Reset( fCmd );
}



#if defined( __unix__ )  || defined (_WIN32 )	
string   
KFPBSubMessageSEMConfigStepperMotor::str() const
{
    auto t = this->fCmd;
    std::stringstream buffer;
    buffer << KFPBSubMessageSEMStepUnitConversion::str( &t->conversion ) << endl;

    buffer << g_utilities()->TabAlign("HAS_NEGATIVE_ENDSTOP?:") <<  ( t->has_negative_soft_endstop == true ? "TRUE" : "FALSE" ) << endl;
    if( t->has_negative_soft_endstop == true )
    {
        buffer << g_utilities()->TabAlign("NEGATIVE_EMDSTOP:") << t->negative_soft_endstop << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_POSITIVE_ENDSTOP?:") <<  ( t->has_positive_soft_endstop  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_positive_soft_endstop == true )
    {
        buffer << g_utilities()->TabAlign("NEGATIVE_EMDSTOP:") << t->positive_soft_endstop << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_NEGATIVE_ENDSTOP_ID?:") <<  ( t->has_negative_soft_endstop_id == true ? "TRUE" : "FALSE" ) << endl;
    if( t->has_negative_soft_endstop_id == true )
    {
        buffer << g_utilities()->TabAlign("NEGATIVE_EMDSTOP_ID:") << t->negative_soft_endstop_id << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_POSITIVE_ENDSTOP_ID?:") <<  ( t->has_positive_soft_endstop_id  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_positive_soft_endstop_id == true )
    {
        buffer << g_utilities()->TabAlign("POSITIVE_EMDSTOP_ID:") << t->positive_soft_endstop_id << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_HOME_DEVICE_ID?:") <<  ( t->has_home_device_id  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_home_device_id == true )
    {
        buffer << g_utilities()->TabAlign("NEGATIVE_EMDSTOP_ID:") << t->home_device_id << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_MAX_SPEED ?:") <<  ( t->has_max_speed  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_max_speed == true )
    {
        buffer << g_utilities()->TabAlign("MAX_SPEED:") << t->max_speed << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_SPEED ?:") <<  ( t->has_speed  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_speed == true )
    {
        buffer << g_utilities()->TabAlign("MAX_SPEED:") << t->speed << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_MAX_ACCELLERATION?:") <<  ( t->has_max_speed  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_max_speed == true )
    {
        buffer << g_utilities()->TabAlign("MAX_ACCELLERATION:") << t->max_acceleration << endl;
    }



    buffer << g_utilities()->TabAlign("HAS_MAX_ACCELLERATION?:") <<  ( t->has_max_acceleration  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_max_acceleration == true )
    {
        buffer << g_utilities()->TabAlign("MAX_ACCELLERATION:") << t->max_acceleration << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_ACCELLERATION?:") <<  ( t->has_acceleration  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_acceleration == true )
    {
        buffer << g_utilities()->TabAlign("ACCELLERATION:") << t->acceleration << endl;
    }

    buffer << g_utilities()->TabAlign("HAS_MAX_CURRENT?:") <<  ( t->has_max_current  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_max_current == true )
    {
        buffer << g_utilities()->TabAlign("MAX_CURRENT:") << t->max_current << endl;
    }

    buffer << g_utilities()->TabAlign("HAS_CURRENT?:") <<  ( t->has_current  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_current == true )
    {
        buffer << g_utilities()->TabAlign("CURRENT:") << t->current << endl;
    }

       
    buffer << g_utilities()->TabAlign("HAS_INACTIVE_TMEOUT?:") <<  ( t->has_inactive_timeout  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_inactive_timeout == true )
    {
        buffer << g_utilities()->TabAlign("INACTIVE_TIMEOUT:") << t->inactive_timeout << endl;
    }


    buffer << g_utilities()->TabAlign("HAS_INACTIVE_CURRENT?:") <<  ( t->has_inactive_current  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_inactive_current == true )
    {
        buffer << g_utilities()->TabAlign("INACTIVE_CURRENT:") << t->inactive_current << endl;
    }

     buffer << g_utilities()->TabAlign("HOME_VALUE?:") <<  ( t->has_home_value  == true  ? "TRUE" : "FALSE" ) << endl;
    if( t->has_home_value == true )
    {
        buffer << g_utilities()->TabAlign("HOME_VALUE:") << t->home_value << endl;
    }
    return buffer.str();

}
#endif