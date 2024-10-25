// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/
#include "KFSensorUnitConversion.h"

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;

KFSensorUnitConversion::KFSensorUnitConversion()
{

}

KFSensorUnitConversion::~KFSensorUnitConversion()
{

}

string
KFSensorUnitConversion::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("INPUT_TYPE:") <<  fInputTypeS <<  "(" << (int)fInputType << ")"   <<  endl;
    buffer << g_utilities()->TabAlign("MIN_INPUT:")  <<  fMinInput   <<  endl;
    buffer << g_utilities()->TabAlign("MIN_INPUT:")  <<  fMaxInput   <<  endl;
    buffer << g_utilities()->TabAlign("MIN_OUTPUT:") <<  fMinOutput  <<  endl;
    buffer << g_utilities()->TabAlign("MAX_OUTPUT:") <<  fMaxOutput  <<  endl;

    return buffer.str();
}

void
KFSensorUnitConversion::ValidateInputs()
{
    if( (fMinInput == 0)  && (fMaxInput == 0) &&
        (fMinOutput == 0) && (fMaxOutput == 0) )
        {
            fHasMinInput = false;
            fHasMaxInput = false;
            fHasMinOutput = false;
            fHasMaxOutput = false;
            fHasInputType = false;
        }
        else
        {
            fHasMinInput = true;
            fHasMaxInput = true;
            fHasMinOutput = true;
            fHasMaxOutput = true;
            fHasInputType = true;
        }
}




