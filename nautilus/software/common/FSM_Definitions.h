// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

/** @file
 *  Generation of Finit State Machine (FSM) entities using macros.
 *  A FSM constitutes the following
 * - For each FSM (KFSMNode): a list of child nodes
 * - Zero or one mother nodes
 * - A predefined set of states
 * - For each state: a given set of actions
 * Thus, and FSM node is composed of 3 parts. KFSMNode, KFSMState and KFSMAction.
 * In order to simplify the implemenation the states and actiosn are uniquely defined, that
 * is, a given state has a given set of actions regardless of which FSM node it is a part of. **/


#include "FSMState.h"
#include "FSMAction.h"
#include "FSMNode.h"
#include "FSMColor.h"
#include "FSM_StateFactory.h"
#include <typeinfo>
#include <logging/LLogApi.h>
#include <utilities/GDefinitions.h>

#include <memory>


#define GENERATE_FSM_STATE(classname, state_name, enabled_actions, color) \
class classname : public FSMState \
{  \
public: \
	classname( FSMNode  *fsm) : FSMState( ) \
	{  \
		SetFSM(fsm); \
		SetName(state_name); \
		SetColor(color); \
		EnableActions(enabled_actions, &fActionHash, &fStateInfo); \
; \
	}  \
static FSMState API * Spawn( FSMNode *fsm)  \
	{  \
		return new classname(fsm);  \
	} \
	virtual const char * GetClassType()  \
    {   \
		static char buf[1024]; \
		snprintf(buf, 1024, "%s",  typeid(this).name()); \
		return buf; \
	}   \
	static const char* GetStateName()  \
	{ \
		return state_name; \
	} \
};




#define GENERATE_FSM_ACTION(classname, action_name, target_state) \
class classname : public FSMAction \
{\
public: \
	API classname() : FSMAction(action_name, target_state)  \
{ \
} \
};


#define GENERATE_FSM_NODE(classname, default_fsm_name, default_states ) \
class classname : public FSMNode \
{ \
public: \
	API classname ( ) : FSMNode( default_fsm_name, default_states) \
	{ \
			\
	} \
	API classname ( const string name) : FSMNode(name, default_states) \
	{ \
			\
	} \
	API classname (  const string name, const string states) : FSMNode(name, states) \
	{ \
			\
	} \
    API ~classname ( ) \
	{ \
		FSM_DEBUG("%s: Calling destrunctor", default_fsm_name );	\
	} \
    virtual int API ExcecLocal(const string) override\
	{ \
		FSM_INFO("%s:\tUpdate NOT_IMPLEMENTED !!", GetName().c_str() ); \
		return FSM_RET_SUCCESS; \
	} \
    virtual void API Update( ) override\
	{ \
		FSM_DEBUG("%s:\tUpdating children !!!", GetName().c_str() ); \
		for (size_t i = 0; i < fChildren.size(); i++) \
		{ \
			fChildren[i]->Update(); \
		} \
			GetTopNode()->MapChildStates(); \
		} \
	static const char* GetFsmName()  \
	{ \
		return default_fsm_name; \
	} \
};


/******************************************************************************************************************************
 ******************************************** Available states ****************************************************************
 ******************************************************************************************************************************
 ****************** Classname *************  State name *******  Valid actions ************************ Color (used by GUI only) ******/
GENERATE_FSM_STATE(FSMState_Ready, 				"READY",		"DISCONNECT;CONFIGURE;RESET;START", 			C_GREEN)
GENERATE_FSM_STATE(FSMState_Aborting,			"ABORTING", 	"",												C_FSM_FATAL)
GENERATE_FSM_STATE(FSMState_Configuring,		"CONFIGURING",	"ABORT",										C_FSM_TRANSIENT)
GENERATE_FSM_STATE(FSMState_Error,				"ERROR",		"RESET;DISCONNECT",								C_FSM_ERROR)
GENERATE_FSM_STATE(FSMState_NotReady,			"NOT_READY",	"DISCONNECT;CONFIGURE;GO_READY;RESET;START",	C_FSM_WAITING)
GENERATE_FSM_STATE(FSMState_Off,				"OFF",			"TURN_ON",										C_FSM_WAITING)
GENERATE_FSM_STATE(FSMState_On,					"ON",			"TURN_OFF",										C_FSM_OK)
GENERATE_FSM_STATE(FSMState_Running,			"RUNNING",		"PAUSE;ABORT",									C_FSM_OK)
GENERATE_FSM_STATE(FSMState_Unknown,			"UNKNOWN",		"CONNECT",										C_FSM_UNKNOWN)
GENERATE_FSM_STATE(FSMState_OK,					"OK",			"",												C_FSM_OK)
GENERATE_FSM_STATE(FSMState_Warning,			"WARNING",		"", 											C_FSM_WARNING)
GENERATE_FSM_STATE(FSMState_Busy,				"BUSY",			"",												C_FSM_TRANSIENT)
GENERATE_FSM_STATE(FSMState_NotLoggedOn,		"NOT_LOGGED_ON","",												C_FSM_WAITING)
GENERATE_FSM_STATE(FSMState_LoggedOn,			"LOGGED_ON",	"",												C_FSM_OK)
GENERATE_FSM_STATE(FSMState_NotConfig,			"NOT_CONFIGURED","",											C_FSM_WAITING)
GENERATE_FSM_STATE(FSMState_Configured,			"CONFIGURED", 	"",												C_FSM_OK)
GENERATE_FSM_STATE(FSMState_Done,				"DONE",			"GO_READY RESET CONFIGURE", 					C_FSM_WAITING)
//GENERATE_FSM_STATE(KFSMState_Soaking,			"SOAKING",		"SKIP",											C_FSM_WAITING)
GENERATE_FSM_STATE(FSMState_Paused,				"PAUSED",		"CONTINUE",										C_FSM_PAUSED)


/******************************************************************************************************************************
******************************************** Available actions ****************************************************************
*******************************************************************************************************************************
********************** Classname *************  Action name  **** Target state ************************************************/
GENERATE_FSM_ACTION(FSMAction_DisConnect,	"DISCONNECT",		"UNKNOWN")
GENERATE_FSM_ACTION(FSMAction_Connect,		"CONNECT",			"NOT_READY")
GENERATE_FSM_ACTION(FSMAction_Configure,	"CONFIGURE",		"CONFIGURING")
GENERATE_FSM_ACTION(FSMAction_GoReady,		"GO_READY",			"READY")
GENERATE_FSM_ACTION(FSMAction_Reset,		"RESET",			"NOT_READY")
GENERATE_FSM_ACTION(FSMAction_Start,		"START",			"RUNNING")
GENERATE_FSM_ACTION(FSMAction_TurnOff,		"TURN_OFF",			"OFF")
GENERATE_FSM_ACTION(FSMAction_TurnOn,		"TURN_ON",			"ON")
GENERATE_FSM_ACTION(FSMAction_Pause,		"PAUSE",			"PAUSED")
GENERATE_FSM_ACTION(FSMAction_Abort,		"ABORT",			"ERROR")
GENERATE_FSM_ACTION(FSMAction_Skip,		    "SKIP",				"RUNNING")
GENERATE_FSM_ACTION(FSMAction_Continue,	    "CONTINUE",			"RUNNING")


/*******************************************************************************************************************************
******************************************** Available nodes *******************************************************************
********************************************************************************************************************************
********************** Classname *************   FSN Name  ***************** States ********************************************/
GENERATE_FSM_NODE(FSMNode_Main,					"MAIN_FSM",					"ERROR;NOT_READY;READY;UNKNOWN;PAUSED;RUNNING;CONFIGURING")
GENERATE_FSM_NODE(FSMNode_Debug,				"FSM_DEBUG",				"UNKNOWN;OK;WARNING;ERROR;READY;NOT_READY;ON;OFF;CONFIGURING;RUNNING;ABORTING;BUSY")
GENERATE_FSM_NODE(FSMNode_UserLogin,			"USER_LOGIN",				"UNKNOWN;NOT_LOGGED_ON;LOGGED_ON;ERROR;")
GENERATE_FSM_NODE(FSMNode_Environment,	 		"ENVIRONMENT",				"OK;ERROR;WARNING")
GENERATE_FSM_NODE(FSMNode_Engine,				"ENGINE",					"OK;ERROR;WARNING")
GENERATE_FSM_NODE(FSMNode_Sensors,				"SENSORS",					"OK;ERROR;WARNING")
///GENERATE_FSM_NODE( KFSMNode_PostOffice,      "MESSAGE_SYSTEM",			"UNKNOWN;NOT_READY;READY;ERROR;WARNING")
GENERATE_FSM_NODE(FSMNode_PostOffice,        	"MESSAGE_SYSTEM",			"UNKNOWN;OK;RUNNING;NOT_READY;ERROR")
GENERATE_FSM_NODE(FSMNode_Operation,			"OPERATIONS",				"UNKNOWN;NOT_READY;READY;RUNNING;PAUSED;ERROR;WARNING")

