// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <string>


#include <common/FDefinitions.h>

using std::string;


/* @class FSMAction class for actions associcated with state transitions.
 * Each command has its corresponding action function. For instance
 * "GO_READY" is associated with GoReady(), "RESET" with Reset() etc.. */

class FSMAction
{
public:
	API FSMAction(const string command, const string target);
	API ~FSMAction();
	string API	GetName();
	string API  GetTargetState();
	int API Excec();

private:
	API FSMAction() {};
	const string fkCommand; /* !< The name command associated with this action */
	const string fkTargetState;
};



