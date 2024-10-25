// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "FSMState.h"
#include "FSMAction.h"
#include "FSMNode.h"
#include "FSM_Definitions.h"
#include <utilities/GException.h>
#include <utilities/GString.h>
#include <logging/LLogging.h>

#include <tuple>

using namespace LOGMASTER;

#include <typeinfo>
#include "FSMNode.h"
#include <mutex>
//std::mutex fsm_action;



FSMState::FSMState(  ) : fFSM(nullptr)
{
	fStateInfo.fName = "NOT_SET";
	Init();
}


FSMState::FSMState( FSMNode *fsm ) : fFSM( fsm )
{
	fStateInfo.fName = "NOT_SET";
	Init();
}


FSMState::~FSMState()
{
	FSM_DEBUG("Calling destructor, name = %s", GetName().c_str() );
}



void FSMState::Init()
{
	fActionHash.emplace((FSMAction *)(new FSMAction_Reset()),     DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_Connect()),   DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_DisConnect()), DISABLED);
	fActionHash.emplace((FSMAction *)(new FSMAction_Configure()), DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_GoReady()),   DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_Start()),     DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_TurnOff()),   DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_TurnOn()),    DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_Pause()),     DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_Abort()),     DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_Skip()),      DISABLED );
	fActionHash.emplace((FSMAction *)(new FSMAction_Continue()),  DISABLED );
}



string
FSMState::GetName() const
{
    return fStateInfo.fName;
}


void 
FSMState::SetName(const string name)
{
	fStateInfo.fName = name;
  //  fName = name;
}


void  
FSMState::SetColor(const int color)
{
	fStateInfo.fColor = color;
}

int 
FSMState::GetColor() const
{
	return fStateInfo.fColor;
}


FSM_StateInfo 
FSMState::GetStateInfo() const
{
	return fStateInfo;
}


void  
FSMState::SetFSM( FSMNode  *fsm)
{
    if (fsm == 0)
    {
		FSM_INFO("FSM pointer is ZERO");
    }
    else
    {  
		fFSM = fsm;
		FSM_INFO("Setting FSM to %s", fFSM->GetName().c_str());
    }
}



FSMNode  * 
FSMState::GetFSM()
{
    return fFSM;
}


/* @return Actions valid in this state*/
vector< std::tuple<string, string > >
FSMState::GetValidActions() const
{
	vector< std::tuple<string, string> >  tmp;

	for (auto it = fActionHash.begin(); it != fActionHash.end(); it++)
	{
		if (it->second == true)
		{
			std::shared_ptr<FSMState> new_state = 0;

			if (fFSM != 0)
			{
				it->first->GetName();
				try
				{		
					const string target_state = it->first->GetTargetState();
					if ( fFSM->IsValidState(target_state) )
					{
						FSM_DEBUG("%s: Target state %s is valid", fFSM->GetName().c_str(), target_state.c_str() );
						new_state = fFSM->GetStateObject(target_state);
					}
					else
					{
						FSM_INFO("%s: Target state %s is invalid", fFSM->GetName().c_str(), target_state.c_str());
					}
				}
				catch (GException &e)
				{
					CERR << "exception caught for  " << it->first->GetName() <<  " in state "<<  fStateInfo.fName << endl;
					cout << e.what() << endl;
				}
				catch (std::exception &e)
				{
					CERR << it->first->GetName() << " std::exception caught: " << e.what() << endl;
				}
				catch (...)
				{
					CERR << "Unknown exception caught for  " << it->first->GetName() << endl;
				}
			}
		if (new_state != 0)
			{
				std::tuple<string, string> e = std::make_tuple(it->first->GetName(), it->first->GetTargetState());
				tmp.push_back(e);
			}
		}
	}
	return tmp;	
}



/* @return A list of all actions valid in any state*/
vector<string> 
FSMState::GetAllActions(std::map<FSMAction *, bool > *hash )
{
	vector<string>  tmp;
	for (auto it = hash->begin(); it != hash->end(); it++)
	{
		string element = it->first->GetName() + "->" + it->first->GetTargetState();
		element += (it->second == true ? "(ENABLED)" : "DISABLED");
		tmp.push_back(element);
	}
	return tmp;
}



void 
FSMState::EnableAction(const string action, std::map<FSMAction *, bool > *hash) 
{
	//std::lock_guard<std::mutex> guard(fsm_action);
//	fsm_action.lock();
	bool found = false;

	for (auto it = hash->begin(); it != hash->end(); it++)
	{
		if (it->first->GetName() == action)
		{
			FSM_INFO("Enabling action \"%s\"", action.c_str()  );
			found = true;
			it->second = true;
		}
	}
//	fsm_action.unlock();
   	FSM_ASSERT_EXCEPTION(found != false, "Invalid action %s, this is not a valid action in any state, possible actions are %s", action.c_str(),  g_string()->ToString(GetAllActions(hash)).c_str()  );	
}



void 
FSMState::EnableActions(const string actions, std::map<FSMAction*, bool>* hash, FSM_StateInfo * sinfo)
{
//	std::lock_guard<std::mutex> guard(fsm_action);
//	fsm_action.lock();
	vector<string> tmp = g_tokenizer()->Tokenize(actions, { " ", ",", ";", "\t" },false); 
	for (size_t i = 0; i < tmp.size(); i++) 
	{	
		EnableAction(tmp.at(i), hash);  
		sinfo->fActions.push_back(tmp.at(i)); 
	}	
}


void 
FSMState::EnableAction(const string action)
{	
	EnableAction(action, &fActionHash);
}



/* Checks if the state "action" is a valid for any state, that is, if the action is known to the system. 
 * It is NOT take into consideration wether or not "action" is valid for this particular state
 * @param action[in] The action to check validity for
 * @return true if the action is valid for any state, false othervise */
bool  
FSMState::IsValidAction(const string action) const
{
	for (auto it = fActionHash.begin(); it != fActionHash.end(); it++)
	{
		if (it->first->GetName() == action)
		{
			return true;
		}
	}
	return false;
}



/* Checks if the "action" is a valid  for this state 
 * @param action[in] The action to check validity for
 * @param a[in|out] If the action is enabled, then the action object associcated 
 * with "action" is return in this pointer, providede that the input argument is non-zero.
 * @return true if the action is valid for this state, false othervise */
bool
FSMState::IsEnabledAction(const string action, FSMAction **a) const
{
	if (IsValidAction(action) == false )
	{
		FSM_FATAL("Unknown action %s is not present in the action hash table", action.c_str());
		return false;
	}
	else
	{
		for (auto it = fActionHash.begin(); it != fActionHash.end(); it++)
		{
			if (it->first->GetName() == action)
			{
				if (a != 0)
				{
					*a = it->first;
				}
				return  it->second;
			}
		}
		return false;
	}
}


bool
FSMState::IsValid(const string action)  const
{
	if (IsEnabledAction(action) && IsValidAction(action) )
	{
		return true;
	}
	else
	{
		return false;
	}
}


/* Excecute an action associcated with this state. If the action is not valid for this state, or if it is invalid for any state, then a
 * FATAL/ERROR log messaeg is issued and the function returnes with an error. Othervise a state transition occurs from the current
 * state to the target state of the action
 * @param cmd[in] The state transition / command  to execute
 * @return FSM_RET_SUCCESS upon a successfull transition, FSM_RET_ERROR othervise. */
int 
FSMState::Excec(const string action) const
{
	if (IsValidAction(action) == false)
	{
		FSM_EXCEPTION("The action  %s is not a reckognized/valid action in any state", action.c_str());
		return FSM_RET_ERROR;
	}
	else
	{
		FSMAction *a;
		if ( IsEnabledAction(action, &a )  )
		{
			FSM_ASSERT_EXCEPTION( a != 0, "Pointer to FSMAction object is  ZERO !!!");
			FSM_DEBUG("Excecuting  %s,  attempting state transistion  %s -> %s", action.c_str(), GetName().c_str(), a->GetName().c_str()  );
		
			string target_state_name = a->GetTargetState();
			std::shared_ptr<FSMState> new_state = fFSM->GetStateObject(target_state_name);

			if (new_state == 0)
			{			
				FSM_INFO("Node: %s, current state is:%s   action: %s. Could not find invalid target state %s, command ignored", fFSM->GetName().c_str(), fStateInfo.fName.c_str(), action.c_str(), target_state_name.c_str()  );
				return FSM_RET_ERROR;
			}
			else
			{
				FSM_INFO("Node: %s, current state is:%s   action: %s. Target state %s", fFSM->GetName().c_str(), fStateInfo.fName.c_str(), action.c_str(), target_state_name.c_str());				
				a->Excec();
				fFSM->StateTransition(new_state->GetName());
				return FSM_RET_SUCCESS;
			}
		}
		else
		{
			string valid_actions =  g_string()->ToString(GetValidActionsString( GetValidActions() ));
			FSM_INFO("The action \"%s\" is not valid in this state (%s). Valid actions are\n %s", action.c_str(), GetName().c_str(), valid_actions.c_str() );

			if (a != 0 && GetName()  == a->GetTargetState() )
			{
				FSM_INFO("Current state and target state is the same ( %s )", GetName().c_str() );
			}
			return FSM_RET_ERROR;
		}
	}
}


std::map<FSMAction*, bool> * 
FSMState::GetActionHash()
{
	return &fActionHash;
}



string 
FSMState::GetValidActionsString( const vector< std::tuple<string, string> >  &a)
{
	std::stringstream buffer;
	buffer << "\t\tValid actions: " << (a.size() != 0 ? "\n" : " This state has no valid actions");

	for (size_t i = 0; i < a.size(); i++)
	{
		buffer << "\t\t" << std::get<0>(a[i]) << " -> " << std::get<1>(a[i]) << endl;;
	}
	return buffer.str();
}


string  
FSMState::GetValidActionsString() const
{
	return GetValidActionsString(GetValidActions());
}


string
FSMState::str() const
{
	std::stringstream buffer;
	//	buffer.clear();
	buffer << "\n***********************************************************" << endl;
	buffer << "******\tACTIONS AND TARGET STATES FOR STATE  \"" << fStateInfo.fName << "\"  ********" << endl;
	buffer << "*********************************************************" << endl;
	buffer << "******\tACTION   *****\tTARGET STATE ***************" << endl;
	buffer << "*****************************************************" << endl;

	for (auto it = fActionHash.begin(); it != fActionHash.end(); it++)
	{
		buffer << "\t" << it->first->GetName() << (it->first->GetName().size() < 8 ? "\t\t" : "\t") << it->first->GetTargetState() << "  " << (it->second == true ? "ENABLED" : "DISABLED") << endl;
	}

	buffer << "*****************************************************" << endl;
	buffer << "*********************  DONE   ***********************" << endl;
	buffer << "*****************************************************" << endl;

	return buffer.str();
}