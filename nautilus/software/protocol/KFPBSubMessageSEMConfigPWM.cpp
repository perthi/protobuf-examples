// -*- mode: c++ -*-


#include "KFPBSubMessageSEMConfigPWM.h"


KFPBSubMessageSEMConfigPWM::KFPBSubMessageSEMConfigPWM() : KFPBMessageSEM (  (pb_field_t *  )SEMConfigPWM_fields),  fLinearUnitConversion()
{
    fLinearUnitConversion.Set( &fCmd->conversion );
    Reset();
}


KFPBSubMessageSEMConfigPWM::~KFPBSubMessageSEMConfigPWM()
{

}


void 
KFPBSubMessageSEMConfigPWM::Set( SEMConfigPWM *t)
{
    fCmd = t;
    fLinearUnitConversion.Set( &fCmd->conversion );
}


KFPBSubMessageSEMLinearUnitConversion * 
KFPBSubMessageSEMConfigPWM::GetConversion()
{
    return &fLinearUnitConversion;
}


void  
KFPBSubMessageSEMConfigPWM::SetMinLevel(const float val)
{
    fCmd->min_level = val;
    fCmd->has_min_level = true;
}


void   
KFPBSubMessageSEMConfigPWM::SetMaxLevel( const float val)
{
    fCmd->max_level = val;
    fCmd->has_max_level = true;
}

	

float  
KFPBSubMessageSEMConfigPWM::GetMinLevel() const
{
    return fCmd->min_level;
}


float  
KFPBSubMessageSEMConfigPWM::GetMaxLevel() const
{
    return fCmd->max_level;
}

bool 
KFPBSubMessageSEMConfigPWM::HasMaxLevel() const
{
    return fCmd->has_max_level;
}


bool 
KFPBSubMessageSEMConfigPWM::HasMinLevel() const
{
    return fCmd->has_max_level;
}


// bool         
// KFPBSubMessageSEMConfigPWM::HasConversion() const
// {
//     return true; // CRAP PTH
// }


bool 
KFPBSubMessageSEMConfigPWM::HasUnitConversion() const
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
KFPBSubMessageSEMConfigPWM::Reset( SEMConfigPWM  * t )
{   
    fLinearUnitConversion.Reset();
    t->has_max_level = false;
    t->has_min_level = false;
    t->max_level = 0;
    t->min_level = 0;

}


void    
KFPBSubMessageSEMConfigPWM::Reset( )
{
    Reset(fCmd);
}

#if defined( __unix__ )  || defined (_WIN32 )
string 
KFPBSubMessageSEMConfigPWM::str() const
{
    std::stringstream buffer;

    buffer << g_utilities()->TabAlign("HAS_MIN_LEVEL?:") <<  (fCmd->has_min_level == true ? "TRUE" : "FALSE") << endl;
    if( fCmd->has_min_level == true )
    {
        buffer << g_utilities()->TabAlign("MIN_LEVEL:")  << fCmd->min_level << endl;     
    }

      buffer << g_utilities()->TabAlign("HAS_MAX_LEVEL?:") <<  (fCmd->has_max_level == true ? "TRUE" : "FALSE") << endl;
    if( fCmd->has_max_level == true )
    {
        buffer << g_utilities()->TabAlign("MAX_LEVEL:")  << fCmd->max_level << endl;     
    }


    return buffer.str();
}
#endif

