// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "MBMessageRequestUserInput.h"



MBMessageRequestUserInput::MBMessageRequestUserInput() : MBMessageRequest ( eMESSAGE_REQUEST::USER_INPUT, "Request for user input")
{

}


MBMessageRequestUserInput::~MBMessageRequestUserInput()
{
}
