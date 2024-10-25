// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "FSM_StateFactory.h"
#include "FSMState.h"
#include "FSM_Definitions.h"
#include <utilities/GUtilities.h>
#include <typeinfo>
#include <mutex>

std::map<string, FSMState *(*)(   FSMNode * ) >  FSM_StateFactory::fStates;


FSM_StateFactory * 
FSM_StateFactory::Instance()
{
    static FSM_StateFactory *instance = new FSM_StateFactory();
    return instance;    
}


FSMState * 
FSM_StateFactory::Spawn(const string name, FSMNode  *fsm)
{
	auto it = fStates.find(name);
	if (it != fStates.end())
	{
		FSM_DEBUG("Spawning state %s", name.c_str() );
		FSMState *(*funct)( FSMNode * ) =  it->second;
		return funct(fsm);
	}

	else
	{
		FSM_ERROR("could not find any state with name %s,  returning ZERO pointer", name.c_str());
		return 0;
	}

	return 0;
}



bool 
FSM_StateFactory::HasState(const string state_name)
{
	auto it = fStates.find(state_name);
	if (it != fStates.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}


string 
FSM_StateFactory::GetStates()
{
	return g_utilities()->Hash2String(&fStates, 1);
}


FSM_StateFactory::FSM_StateFactory()
{

	FSMState_Aborting      aborting(0);
	FSMState_Configuring   configuring(0);
	FSMState_Error	       error(0);
	FSMState_Ready         ready(0);
	FSMState_NotReady      not_ready(0);
	FSMState_Off           off(0);
	FSMState_On			   on(0);
	FSMState_Running       running(0);
	FSMState_Unknown       unknown(0);
	FSMState_OK		       ok(0);
	FSMState_Warning       warning(0);
	FSMState_Busy          busy(0);
	
	FSMState_NotLoggedOn	notLoggedOn(nullptr);
//	FSMState_LoggedOn		loggedOn(nullptr);
	FSMState_NotConfig		notConfigured(nullptr);
	FSMState_Configured	configured(nullptr);
	FSMState_Done			done(0);
//	FSMState_Soaking		soaking(nullptr);
	FSMState_Paused		paused(nullptr);

	fStates.emplace(configuring.GetName(),	FSMState_Configuring::Spawn);
	fStates.emplace(aborting.GetName(),		FSMState_Aborting::Spawn);
	fStates.emplace(error.GetName(),		FSMState_Error::Spawn);
	fStates.emplace(ready.GetName(),		FSMState_Ready::Spawn);
	fStates.emplace(not_ready.GetName(),	FSMState_NotReady::Spawn);
	fStates.emplace(off.GetName(),			FSMState_Off::Spawn);
	fStates.emplace(on.GetName(),			FSMState_On::Spawn);
	fStates.emplace(running.GetName(),		FSMState_Running::Spawn);
	fStates.emplace(unknown.GetName(),		FSMState_Unknown::Spawn);
	fStates.emplace(ok.GetName(),			FSMState_OK::Spawn);
	fStates.emplace(warning.GetName(),		FSMState_Warning::Spawn);
	fStates.emplace(busy.GetName(),			FSMState_Busy::Spawn);
//	fStates.emplace(notLoggedOn.GetName(),	FSMState_NotLoggedOn::Spawn);
//	fStates.emplace(loggedOn.GetName(),		FSMState_LoggedOn::Spawn);
	fStates.emplace(notConfigured.GetName(),FSMState_NotConfig::Spawn);
	fStates.emplace(configured.GetName(),	FSMState_Configured::Spawn);
	fStates.emplace(done.GetName(),			FSMState_Done::Spawn);
//	fStates.emplace(soaking.GetName(),		FSMState_Soaking::Spawn);
	fStates.emplace(paused.GetName(),		FSMState_Paused::Spawn);
}


FSM_StateFactory::~FSM_StateFactory()
{

}
