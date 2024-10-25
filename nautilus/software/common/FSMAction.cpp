// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "FSMAction.h"
#include "FSMState.h"
#include <logging/LLogApi.h>


FSMAction::FSMAction(const string command, const string target) : fkCommand(command), fkTargetState(target)
{
	FSM_DEBUG("calling constructor: action = %s\ttarget = %s", fkCommand.c_str(), fkTargetState.c_str() );
}


FSMAction::~FSMAction()
{
	FSM_DEBUG("calling destructor: action = %s\ttarget = %s", fkCommand.c_str(), fkTargetState.c_str());
}


string
FSMAction::GetName()
{
	return fkCommand;
}


string 
FSMAction::GetTargetState()
{
	return fkTargetState;
}


int 
FSMAction::Excec()
{
	FSM_INFO("Excecuting %s, target state is %s", fkCommand.c_str(), fkTargetState.c_str() );
	return 0;
}


