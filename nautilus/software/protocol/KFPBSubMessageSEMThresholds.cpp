// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBSubMessageSEMThresholds.h"


KFPBSubMessageSEMThresholds::KFPBSubMessageSEMThresholds() : KFPBMessageSEM(  ( pb_field_t *  ) SEMThresholds_fields)
{
    Reset();
}


KFPBSubMessageSEMThresholds::~KFPBSubMessageSEMThresholds()
{

}



void  
KFPBSubMessageSEMThresholds::SetALarmLow( const float val, const bool has_value )
{
    this->fCmd->alarm_low = val;
    this->fCmd->has_alarm_low = has_value;
}


void  
KFPBSubMessageSEMThresholds::SetWarningLow(const float val, const bool has_value )
{
    this->fCmd->warning_low = val;
    this->fCmd->has_warning_low = has_value;
}


void
KFPBSubMessageSEMThresholds::SetWarningHigh( const float val, const bool has_value  )
{
    this->fCmd->warning_high = val;
    this->fCmd->has_warning_high = has_value;
}


void  
KFPBSubMessageSEMThresholds::KFPBSubMessageSEMThresholds::SetAlarmHigh( const float val,  const bool has_value  )
{
    this->fCmd->alarm_high = val;
    this->fCmd->has_alarm_high = has_value;
}


float  
KFPBSubMessageSEMThresholds::GetALarmLow(  )
{
    return fCmd->alarm_low;
}


float  
KFPBSubMessageSEMThresholds::GetWarningLow( )
{
    return this->fCmd->warning_low;
}


float  
KFPBSubMessageSEMThresholds::GetWarningHigh( )
{
   return this->fCmd->warning_high; 
}


float  
KFPBSubMessageSEMThresholds::GetAlarmHigh(  )
{
    return this->fCmd->alarm_high;
}


bool  
KFPBSubMessageSEMThresholds::HasALarmLow( ) const
{
    return this->fCmd->has_alarm_low;
}


bool  
KFPBSubMessageSEMThresholds::HasWarningLow( ) const
{
    return this->fCmd->has_warning_low;
}


bool  
KFPBSubMessageSEMThresholds::HasWarningHigh( ) const
{
    return this->fCmd->has_warning_high;
}


bool  
KFPBSubMessageSEMThresholds::HasAlarmHigh( ) const
{
    return this->fCmd->has_alarm_high;
}


void  
KFPBSubMessageSEMThresholds::SetHasALarmLow( const bool val )
{
    this->fCmd->has_alarm_low = val;
}


void  
KFPBSubMessageSEMThresholds::SetHasWarningLow( const bool val ) 
{
    this->fCmd->has_warning_low = val;
}


void  
KFPBSubMessageSEMThresholds::SetHasWarningHigh( const bool val )
{
    this->fCmd->has_warning_high = val;
}


void  
KFPBSubMessageSEMThresholds::SetHasAlarmHigh( const bool val )
{
    this->fCmd->has_alarm_high = val;
}



void 
KFPBSubMessageSEMThresholds::Reset( SEMThresholds *t)
{
    t->has_alarm_low = 0;
    t->alarm_low = 0;
    t->has_warning_low = 0;
    t->warning_low = 0;
    t->has_warning_high = 0;
    t->warning_high = 0;
    t->has_alarm_high = 0;
    t->alarm_high = 0;
}


void 
KFPBSubMessageSEMThresholds::Reset( )
{
    Reset(fCmd); 
}



#if defined( __unix__ )  || defined (_WIN32 )
string   
KFPBSubMessageSEMThresholds::str( KFPBSubMessageSEMThresholds *t ) 
{
    return t->str();
}


string   
KFPBSubMessageSEMThresholds::str() const
{
    std::stringstream buffer;
    auto t = this->fCmd;

    buffer << g_utilities()->TabAlign("HAS ALARM_LOW ?: ") <<  (t->has_alarm_low == true ? "TRUE" : "FALSE") << endl;

    if(t->has_alarm_low == true)
    {
        buffer << g_utilities()->TabAlign("ALARM_LOW:") << t->alarm_low;
    }
    
     buffer << g_utilities()->TabAlign("HAS WARNING_LOW ?: ") <<  (t->has_warning_low == true ? "TRUE" : "FALSE") << endl;

    if(t->has_warning_low == true)
    {
        buffer << g_utilities()->TabAlign("WARNING_LOW:") << t->warning_low;
    }

    buffer << g_utilities()->TabAlign("HAS WARNING_HIGH ?: ") <<  (t->has_warning_high == true ? "TRUE" : "FALSE") << endl;

    if(t->has_warning_high == true)
    {
        buffer << g_utilities()->TabAlign("WARNING_HIGH:") << t->warning_high;
    }

    buffer << g_utilities()->TabAlign("HAS ALARM_HIGH ?: ") <<  (t->has_alarm_high == true ? "TRUE" : "FALSE") << endl;

    if(t->has_alarm_high == true)
    {
        buffer << g_utilities()->TabAlign("ALARM_HIGH:") << t->alarm_high;
    }

    return buffer.str();
}

#endif



