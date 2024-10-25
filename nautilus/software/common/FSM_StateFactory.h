// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <common/FDefinitions.h>

#include <map>
#include <string>
using std::string;

#include <functional>

class FSMState;
class FSMNode;

class FSM_StateFactory
{
public:
    static  FSM_StateFactory API * Instance();
	FSMState API * Spawn(const string name,  FSMNode  *fsm);
	bool HasState(const string state_name);
	string      API  GetStates();

private:
//   static std::map<string, std::function<FSMState *(FSMNode *)> > fStates;
   static std::map<string, FSMState *(*)(  FSMNode *  ) > fStates;  //! < Hash map over all possible states in the system
   FSM_StateFactory();
   ~FSM_StateFactory();
};

