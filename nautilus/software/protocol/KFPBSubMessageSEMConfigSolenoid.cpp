// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "KFPBSubMessageSEMConfigSolenoid.h"


KFPBSubMessageSEMConfigSolenoid::KFPBSubMessageSEMConfigSolenoid() : KFPBMessageSEM ( ( pb_field_t *  )SEMConfigSolenoid_fields )
{
    Reset();
}

KFPBSubMessageSEMConfigSolenoid::~KFPBSubMessageSEMConfigSolenoid()
{

}



void  
KFPBSubMessageSEMConfigSolenoid::SetMaxCurrent( const float val)
{
    fCmd->max_current = val;
    fCmd->has_max_current = true;
}


void  
KFPBSubMessageSEMConfigSolenoid::SetActivateCurrent( const float val)
{
    fCmd->activate_current = val;
    fCmd->has_activate_current = true;
}


void  
KFPBSubMessageSEMConfigSolenoid::SetHoldCurrent( const float val)
{
    fCmd->hold_current = val;
    fCmd->has_hold_current = true;

}


float  
KFPBSubMessageSEMConfigSolenoid::GetMaxCurrent() const
{
    return fCmd->max_current;
}


float  
KFPBSubMessageSEMConfigSolenoid::GetActivateCurrent() const
{
    return fCmd->activate_current;
}


float  
KFPBSubMessageSEMConfigSolenoid::GetHoldCurrent( ) const
{
    return fCmd->hold_current;
}


void
KFPBSubMessageSEMConfigSolenoid::Reset( SEMConfigSolenoid  * t)
{
    t->activate_current = 0;
    t->has_activate_current = false;
    t->hold_current = 0;
    t->has_hold_current = false;
    t->max_current = 0;
    t->has_max_current = false;
}


void    
KFPBSubMessageSEMConfigSolenoid::Reset( )
{
    Reset( fCmd);
}


#if defined( __unix__ )  || defined (_WIN32 )
string  
KFPBSubMessageSEMConfigSolenoid::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("HAS_MAX_CURRENT?:") << ( fCmd->has_max_current == true ? "TRUE" : "FALSE") << endl;;
    if( fCmd->has_max_current == true  )
    {
        buffer << g_utilities()->TabAlign("MAX_CURRENT:") << fCmd->max_current << endl;
    }

    buffer << g_utilities()->TabAlign("HAS_ACTIVATE_CURRENT?:") << ( fCmd->has_activate_current == true ? "TRUE" : "FALSE") << endl;;
    if( fCmd->has_activate_current == true  )
    {
        buffer << g_utilities()->TabAlign("ACTIVATE_CURRENT:") << fCmd->activate_current << endl;
    }

     buffer << g_utilities()->TabAlign("HAS_HOLD_CURRENT?:") << ( fCmd->has_hold_current == true ? "TRUE" : "FALSE") << endl;;
    if( fCmd->has_hold_current == true  )
    {
        buffer << g_utilities()->TabAlign("HOLD_CURRENT:") << fCmd->hold_current << endl;
    }

    return buffer.str();
}
#endif

