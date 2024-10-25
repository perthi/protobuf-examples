// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMStepUnitConversion.h"



KFPBSubMessageSEMStepUnitConversion::KFPBSubMessageSEMStepUnitConversion() : KFPBMessageSEM (  ( pb_field_t *  ) SEMStepUnitConversion_fields) 
{
    Reset();
}

KFPBSubMessageSEMStepUnitConversion::~KFPBSubMessageSEMStepUnitConversion()
{

}




void
KFPBSubMessageSEMStepUnitConversion::SetSIUnit( const int unit )
{
    
    fCmd->si_unit = unit;
}


int
KFPBSubMessageSEMStepUnitConversion::GetSIUnit() const
{
    return fCmd->si_unit;
}


void
KFPBSubMessageSEMStepUnitConversion::SetUnitPerStep( const float factor )
{
    fCmd->unit_per_step = factor;
}


float
KFPBSubMessageSEMStepUnitConversion::GetUnitPerStep( ) const
{
    return fCmd->unit_per_step;
}


void 
KFPBSubMessageSEMStepUnitConversion::Reset( SEMStepUnitConversion *t)
{
    t->si_unit = 0;
    t->unit_per_step = 0;
}


void 
KFPBSubMessageSEMStepUnitConversion::Reset(  )
{
    Reset(fCmd);
}


#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMStepUnitConversion::str() const

{   
    return str(this->fCmd);
}


string
KFPBSubMessageSEMStepUnitConversion::str( SEMStepUnitConversion *t )
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("SI_UNIT:") << t->si_unit << endl;
    buffer << g_utilities()->TabAlign("CONVERSION (unit per step):") << t->unit_per_step << endl;
    return buffer.str();
}
#endif