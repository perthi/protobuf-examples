// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <memory>
#include <string>
using std::string;

#include <vector>
using std::vector;

class FSMState;
class FSMNode;

class FSM_StateEvaluation
{
public:
	static bool IsAllInState(const string state, vector< std::shared_ptr<FSMState> > *v);
	static bool IsAnyInState(const string state, vector<  std::shared_ptr<FSMState>  > *v );
	static bool IsInState( std::shared_ptr<FSMNode> name, const string state);

};

