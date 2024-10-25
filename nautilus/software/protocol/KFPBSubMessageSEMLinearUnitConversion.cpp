// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMLinearUnitConversion.h"


#if defined( __unix__ )  || defined (_WIN32 )
#include <configuration/KFSensorUnitConversion.h>
#endif


KFPBSubMessageSEMLinearUnitConversion::KFPBSubMessageSEMLinearUnitConversion()  : KFPBMessageSEM( ( pb_field_t * )SEMLinearUnitConversion_fields)
{
    Reset();
}


KFPBSubMessageSEMLinearUnitConversion::~KFPBSubMessageSEMLinearUnitConversion()
{

}


#if defined( __unix__ )  || defined (_WIN32 )
void
KFPBSubMessageSEMLinearUnitConversion::SetConfiguration( const KFSensorUnitConversion * const config )
{
    XML_ASSERT_EXCEPTION(config != nullptr, "ZERO POINTER");
    SetMaxInput(config->fMaxInput);
    SetMaxOutput(config->fMaxOutput);
    SetMinInput(config->fMinInput);
    SetMinOutput(config->fMinOutput);
    SetInputType(config->fInputType);
}
#endif


void
KFPBSubMessageSEMLinearUnitConversion::SetInputType( const eSENSOR_INPUT_TYPE  type )
{
    fCmd->input_type = (int32_t)type;
}


eSENSOR_INPUT_TYPE
KFPBSubMessageSEMLinearUnitConversion::GetInputType() const
{
    return (eSENSOR_INPUT_TYPE)fCmd->input_type;
}


float
KFPBSubMessageSEMLinearUnitConversion::GetMinInput() const
{
    return this->fCmd->min_input;
}


float
KFPBSubMessageSEMLinearUnitConversion::GetMaxInput() const
{
    return  this->fCmd->max_input;
}



float
KFPBSubMessageSEMLinearUnitConversion::GetMinOutput() const
{
    return this->fCmd->min_output;
}


float
KFPBSubMessageSEMLinearUnitConversion::GetMaxOutput() const
{
    return this->fCmd->max_output;

}

void
KFPBSubMessageSEMLinearUnitConversion::SetMinInput(const float val)
{
    this->fCmd->min_input = val;
}


void
KFPBSubMessageSEMLinearUnitConversion::SetMaxInput(const float val)
{
    this->fCmd->max_input = val;
}


void
KFPBSubMessageSEMLinearUnitConversion::SetMinOutput(const float val)
{
    this->fCmd->min_output = val;
}



void
KFPBSubMessageSEMLinearUnitConversion::SetMaxOutput(const float val)
{
    this->fCmd->max_output = val;
}



void
KFPBSubMessageSEMLinearUnitConversion::Reset(SEMLinearUnitConversion *t)
{

   t->max_input = 0;
   t->max_output = 0;
   t->min_input = 0;
   t->min_output = 0;
   t->input_type = 0;
}


void
KFPBSubMessageSEMLinearUnitConversion::Reset(  )
{
    Reset(fCmd);
}



#if defined( __unix__ )  || defined (_WIN32 )
 string
 KFPBSubMessageSEMLinearUnitConversion::str( KFPBSubMessageSEMLinearUnitConversion *t )
 {
    return t->str();
 }


string
KFPBSubMessageSEMLinearUnitConversion::str() const
{
    std::stringstream buffer;

	buffer << g_utilities()->TabAlign("INPUT_TYPE:") << this->fCmd->input_type << endl;
    buffer << g_utilities()->TabAlign("MIN_INPUT:")  << this->fCmd->min_input  << endl;
    buffer << g_utilities()->TabAlign("MAX_INPUT:")  << this->fCmd->max_input  << endl;
    buffer << g_utilities()->TabAlign("MIN_OUTPUT:") << this->fCmd->min_output << endl;
    buffer << g_utilities()->TabAlign("MAX_OUTPUT:") << this->fCmd->max_output << endl;

    return buffer.str();
}

#endif