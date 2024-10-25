// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "FSM_Definitions.h"
#include <utilities/GString.h>
#include <utilities/GUtilities.h>
#include <utilities/GTokenizer.h>
#include <utilities/GException.h>
#include <common/FSM_StateFactory.h>
#include <common/FSM_StateEvaluation.h>
#include <common/FSM_Definitions.h>


vector< void(*)(void) >    FSMNode::fSubscribers;


/** @brief Main constructor
* @param[in] name The FSM name of the node
* @param[in] states semicolon separated lits of valid states for this node */
FSMNode::FSMNode( const string name, const string states) :  GComponent(name) 
{
	SetName( name );
	/*if ( mother != nullptr )
	{
		SetMother( mother.get() );
	}*/

	vector<string> tokens = g_tokenizer()->Tokenize( states, { " ", ",", "\t", ";" } );
	for (size_t i = 0; i < tokens.size(); i++)
	{
		std::shared_ptr<FSMState> s = std::shared_ptr< FSMState>(FSM_StateFactory::Instance()->Spawn( tokens[i], this ) );
		
		if (s == 0)
		{
			FSM_EXCEPTION("Can not create state with invalid name %s", s->GetName().c_str() );
		}
		else
		{
			fStateHashTable.emplace(s->GetName(), s);
		}
	}
	
	string unknown = "UNKNOWN";

	if (fStateHashTable.find(unknown) != fStateHashTable.end())
	{
		fStateCurrent = fStateHashTable.find(unknown)->second;
	}
	else if ( fStateHashTable.find("READY") != fStateHashTable.end())
	{
		fStateCurrent  = fStateHashTable.find("READY")->second ;
		//FSM_EXCEPTION( "Could not find/spawn state %s", unknown.c_str() );
	}
	else if (fStateHashTable.find("OK") != fStateHashTable.end())
	{
		fStateCurrent = fStateHashTable.find("OK")->second;
		//FSM_EXCEPTION( "Could not find/spawn state %s", unknown.c_str() );
	}
	else
	{
		FSM_EXCEPTION( "State table must contain one of  either UNKNOWN, OK or READY" );
	}
}



FSMNode::~FSMNode()
{

}



string 
FSMNode::str() const
{
	std::stringstream buffer;
	buffer << "FSM_NAME:\t\t\t" << GetName()<< " (level " << GetLevel() << ")" << endl;
	buffer << "Current state:\t\t" << GetCurrentStateName() << endl;
	buffer << "Mother:\t\t\t" << (fMother == 0 ? "This node has no mother" : fMother->GetName()) << endl;
	buffer << "Number of children:\t" << fChildren.size() << endl;
	buffer << fStateCurrent->GetValidActionsString(  );
	
	if (fChildren.size() > 0)
	{
		buffer << "*****  Child nodes for " << GetName() << "   follows" << endl;
		for (size_t i = 0; i < fChildren.size(); i++)
		{
			buffer << fChildren[i]->str() << endl;
		}
	}
	return buffer.str();
}


void 
FSMNode::StateChanged(const string name, const string previous_state, const string new_state)
{
    FSM_DEBUG("State changed called by %s: transitioning from %s to %s", name.c_str(), previous_state.c_str(), new_state.c_str() );
	UpdateSubscribers();
}


std::shared_ptr<FSMState>    
FSMNode::GetCurrentState() const
{ 
	return fStateCurrent;
}


string
FSMNode::GetCurrentStateName() const
{
	return fStateCurrent->GetName();
}


vector<  std::shared_ptr<FSMState> > 
FSMNode::GetCurrentChildStates() const
{
	vector< std::shared_ptr<FSMState> > tmp;
	for (size_t i = 0; i < fChildren.size(); i++)
	{
		tmp.push_back(fChildren[i]->GetCurrentState() );
	}
	return tmp;
}


/** Executes an action for this FSM node. The action must be
 *  valid for the given state. Otherwise an error will be issued
 *  @param[in] action The action to execute.
 *  @return FSM_RET_SUCCESS if the action was executed successfully, otherwise FSM_RET_ERROR */
int 
FSMNode::Excec(const string action)
{
	FSM_DEBUG("%s:\tExecuting %s\tcurrent state is %s", GetName().c_str(), action.c_str(), fStateCurrent->GetName().c_str());
	int iret = 0;;

	if (fChildren.size() == 0)
	{
		if (fStateCurrent->IsValid(action) != true)
		{
			fStateCurrent->GetValidActionsString();
			FSM_DEBUG("%s: The commad %s is invalid in this state (%s): Valid actions are %s", GetName().c_str(), action.c_str(), fStateCurrent->GetName().c_str(), fStateCurrent->GetValidActionsString().c_str() );
			iret = FSM_RET_ERROR;
		}
		else
		{
			if ( fStateCurrent->Excec(action) == FSM_RET_SUCCESS )
			{
				if (ExcecLocal(action) == FSM_RET_ERROR)
				{
					FSM_INFO("%s:\tThe command %s resulted in an error", GetName().c_str(),  action.c_str());
					iret = FSM_RET_ERROR;
				}
				else
				{
					FSM_INFO("%s:\tSuccessfully executed %s: Current state is %s",  GetName().c_str(), action.c_str(), fStateCurrent->GetName().c_str() );
					iret =  FSM_RET_SUCCESS;
				}
			}
			else
			{
				FSM_INFO("%s:\tThe command %s resulted in an error", GetName().c_str(), action.c_str());
				iret = FSM_RET_ERROR;
			}		
		}
	}
	else
	{
		for (size_t i = 0; i < fChildren.size(); i++)
        {
			fStateCurrent->Excec(action);
			fChildren.at(i)->Excec(action);
        }
	}

	GetTopNode()->MapChildStates();
	return iret;
}


/** Executes an action for a specific FSM node. The action must be
*  valid for the given state. Otherwise an error will be issued
*  @param[in] node action The FSM Node to execute.
*  @param[in] action The action to execute.
*  @return FSM_RET_SUCCESS if the action was executed successfully, otherwise FSM_RET_ERROR */
int 
FSMNode::Excec( std::shared_ptr<FSMNode>  node, const string action)
{	
	FSM_INFO("the name %s", node->GetName().c_str());
	return node->Excec(action);
}	


/* The rules for how to map child node states to the mother node state.
 * This function defines the default behaviour of the FSM, but it should in general be
 * overwritten by a derived class. The rules are as follows, applied in the given order
 *  - If any child node is in state ERROR, the mother node should go to the state ERROR
 *  - If every child node is in state NOT_READY, the mother node should go to the state NOT_READY
 *  - If any child node is in state UNKNOWN, the mother node should go to the state UNKNOWN
 *  - If any child node is in state CONFIGURING, the mother node should go to the state CONFIGURING
 *  - If any child node is in state NOT_READY, the mother node should go to the state NOT_READY
 *  - If all child node is in one of the following states, OK, READY, RUNNING or  ON", the mother node should go to the state READY
 * @return FSM_RET_SUCCESS if the transition to the resulting target state can be reached by the mother or if there are no children. 
 * Othevise FSM_RET_ERROR */
int 
FSMNode::MapChildStates()
{

	if (fChildren.size() == 0)
	{
		return  FSM_RET_SUCCESS;;
	}

    for (size_t i = 0; i < fChildren.size(); i++)
    {
        fChildren[i]->MapChildStates();
    }

    vector<std::shared_ptr<FSMState>  > child_states = GetCurrentChildStates();

	if (FSM_StateEvaluation::IsAnyInState("ERROR", &child_states))
	{
		return StateTransition("ERROR");
	}
    else if (FSM_StateEvaluation::IsAllInState("NOT_READY", &child_states))
    {
		return StateTransition("NOT_READY");
	}

	else if (FSM_StateEvaluation::IsAnyInState("NOT_CONFIGURED", &child_states))
	{
		if (IsValidState("NOT_READY"))
		{
			return StateTransition("NOT_READY");
		}
		else if (IsValidState("NOT_CONFIGURED"))
		{
			return StateTransition("NOT_CONFIGURED");
		}
	}
	else if (FSM_StateEvaluation::IsAnyInState("UNKNOWN", &child_states))
    {
		return StateTransition("UNKNOWN");
    }	
	else if (FSM_StateEvaluation::IsAnyInState("CONFIGURING", &child_states))
	{
		return StateTransition("CONFIGURING");
	} 
	else if (FSM_StateEvaluation::IsAnyInState("RUNNING", &child_states))
	{
		return StateTransition("RUNNING");
	}
	else if (FSM_StateEvaluation::IsAnyInState("PAUSED", &child_states))
	{
		return StateTransition("PAUSED");
	}
	else if (FSM_StateEvaluation::IsAnyInState("DONE", &child_states))
	{
		if (IsValidState("DONE") )
		{
			return StateTransition("NOT_READY");
		}
		else if ( IsValidState("READY" ) )
		{
			return StateTransition("NOT_READY");
		}

		return StateTransition("DONE");
	}
	else if (FSM_StateEvaluation::IsAnyInState("WARNING", &child_states))
	{
		return StateTransition("WARNING");
	}
	else if (FSM_StateEvaluation::IsAnyInState("NOT_READY", &child_states))
    {
		return StateTransition("NOT_READY");
    }
    else if (FSM_StateEvaluation::IsAllInState("OK READY RUNNING ON CONFIGURED LOGGED_ON", &child_states))
    {
		if (IsValidState("READY"))
		{
			return StateTransition("READY");
		}
		else if (IsValidState("CONFIGURED"))
		{
			return StateTransition("CONFIGURED");
		}
	}
	else if (FSM_StateEvaluation::IsAnyInState("PAUSED", &child_states))
	{
		return StateTransition("PAUSED");
	}

	return FSM_RET_SUCCESS;

	return FSM_RET_SUCCESS;
}


int
FSMNode::StateTransition( std::shared_ptr<FSMState>  target_state)
{
	if (target_state == 0)
	{
//		FSM_FATAL("%s: The target state is ZERO", GetName().c_str());
		return FSM_RET_ERROR;
	}
	else
	{
		const  string nt = target_state->GetName();
		const  string nc = fStateCurrent->GetName();

		if (IsValidState(nt) == false )
		{
///			FSM_DEBUG("%s:\tcould not move from %s to %s because the target state (%s) is illegal for this node", GetName().c_str(), nc.c_str(), nt.c_str(), nt.c_str() );
			return FSM_RET_ERROR;
		}
		else
		{
///			FSM_INFO("%s:Moving from state: %s\tto state: %s",  GetName().c_str(), nc.c_str(), nt.c_str());
			fStateCurrent = target_state;
			return FSM_RET_SUCCESS;
		}
	}
//    return 0;	
}


void 
FSMNode::ProcessMessageLocal(std::shared_ptr<MBMessageInfo> /*msg*/)
{
	FORCE_DEBUG("Not yet implemented");
}


int
FSMNode::StateTransition(const string target_state)
{
	if (IsValidState(target_state) == false)
	{
	//	FSM_WARNING("%s:\tcould not move from %s to %s because the target state is illegal for this node", GetName().c_str(), fStateCurrent->GetName().c_str(), target_state.c_str());
		return FSM_RET_ERROR;
	}
	else
	{
		if ( fStateCurrent->GetName() ==  target_state )
		{
		//	G_LOG(eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_DRIVER | eMSGSYSTEM::SYS_FSM ,"%s says: recived request to move to state %s. but I am allready in this state, request ignored", GetName().c_str(), target_state.c_str() );
			return FSM_RET_SUCCESS;
		}

		if (fStateHashTable.find(target_state) != fStateHashTable.end())
		{
			string previous_state  = fStateCurrent->GetName();
            string new_state = fStateHashTable.find(target_state)->first;
            int  iret = StateTransition( fStateHashTable.find(target_state)->second   );
            StateChanged( GetName(), previous_state, new_state );

			if (iret == FSM_RET_ERROR)
			{
//				G_LOG(eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_DRIVER | eMSGSYSTEM::SYS_FSM, "%s: could not move from %s to %s", GetName().c_str(), previous_state.c_str(), target_state.c_str() );
			}
			else
			{
	//			G_LOG(eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_DRIVER | eMSGSYSTEM::SYS_FSM, "%s: Sucessfully moved from %s to %s", GetName().c_str(), previous_state.c_str() , target_state.c_str() );
			}

			return iret;
		}
		else
		{
		//	G_LOG( eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_DRIVER | eMSGSYSTEM::SYS_FSM, "%s: could not move from %s to %s", GetName().c_str(), fStateCurrent->GetName().c_str(), target_state.c_str());
			return FSM_RET_ERROR;
		}
		return FSM_RET_SUCCESS;
	}
}


void 
FSMNode::RegisterSubscriber(void(*funct)( ))
{
    fSubscribers.push_back(funct);
}


void 
FSMNode::UpdateSubscribers()
{
    for (size_t i = 0; i < fSubscribers.size(); i++)
    {
       void(*Subscriberfunct)( ) = fSubscribers.at(i);
	   Subscriberfunct();
   }  
}



/**@return the FSM node that is on the top of the FSM hierarchy that this FSM is a part of, i.e the "MAIN" FSM.
 * If the node is allready on the top then the pointer to "this" FSM is returned */
//std::shared_ptr<FSMNode>  
FSMNode * 
FSMNode::GetTopNode()
{
	FSMNode * n = this;
	bool has_mother = HasMother();

	while ( has_mother == true )
	{
		n = n->GetMother();
		has_mother = n->HasMother();
	}

	return n;
}


/**  Returns the state object with name "name"
@param[in] name  The name of the state 
* @return A pointer the state object corresponding tho the state with name "name" if it exists, othervise a zero pointer */
std::shared_ptr<FSMState>  
FSMNode::GetStateObject(const string name)
{
//	FSM_ASSERT_EXCEPTION(fStateHashTable != 0, "fStateHashTable = ZERO !!!!!!!");
	if (fStateHashTable.find(name) != fStateHashTable.end())
	{
		return (fStateHashTable)[name];
	}
	else
	{	
		string this_valid_states = GetStates();
		string all_valid_states = FSM_StateFactory::Instance()->GetStates();
		FSM_INFO("NODE: %s the state \"%s\" is not valid for this FSM,  returning a ZERO pointer: valid states for this node are; %s",  GetName().c_str(), name.c_str(), this_valid_states.c_str());

		if (FSM_StateFactory::Instance()->HasState(name) == true)
		{
			FSM_INFO("NODE: %s the state \"%s\" is known to the system but is not valid for this FSM", GetName().c_str(), name.c_str() );
		}
		else
		{
			FSM_FATAL("NODE: %s, the state \"%s\" is not known to the system. All known states are:  %s", GetName().c_str(), name.c_str(), all_valid_states.c_str() );
		}
		FSM_ASSERT_EXCEPTION( FSM_StateFactory::Instance()->HasState(name), "Unkown state %s", name.c_str() );
		return 0;
	}
//	return 0;
}


string 
FSMNode::GetStates() const
{
	return g_utilities()->Hash2String(&fStateHashTable, 100, ";");
}


//string 
//FSMNode::GetName() const
//{
//	return fkName;
//}


string 
FSMNode::GetId() const
{
	return GenerateUniqueID();
}


bool 
FSMNode::HasMother() const
{
	return fMother == 0 ? false : true;
}


bool 
FSMNode::HasChild( const string name )
{
	auto tmp = GetChildNode(name);
	return tmp == nullptr ? false : true;
}


//std::shared_ptr<FSMNode>
FSMNode  *
FSMNode::GetMother() const
{
	return fMother;
}


/**@return a pointer the child node with name "name"  if it exists, a zero pointer othervise*/
std::shared_ptr<FSMNode>  
FSMNode::GetChildNode(const string name)
{
	FSM_DEBUG("Current node = %s\tInput node = %s. childeren sze = %d",  GetName().c_str(), name.c_str(), fChildren.size()  );

	for (size_t i = 0; i < fChildren.size(); i++)
	{
		FSM_DEBUG("name = %s\t children->getname() = %s", name.c_str(), fChildren[i]->GetName().c_str() );
		if (fChildren[i]->GetName() == name)
		{	
			return fChildren[i];
		}
	
		auto cn = fChildren[i]->GetChildNodes();

		FSM_DEBUG("%s: the number of child nodes is %d", GetName().c_str(),  cn.size());

		for (size_t j = 0; j < cn.size(); j++)
		{

			if (cn[j]->GetName() == name)
			{
				return cn[j];
			}
		}	
	}
	return 0;
}



vector< std::shared_ptr<FSMNode> >
FSMNode::GetChildNodes() const
{
	return fChildren;
}


/* @return The level in the FSM heriarchy this FSM node is at, where ZERO is the top level (main FSM)*/
int 
FSMNode::GetLevel() const
{
	int level = 0;
//	std::shared_ptr<FSMNode> m = fMother;
	FSMNode *m = fMother;

	while (m != 0)
	{
		m = m->GetMother();
		level++;
	}

	return level;	
}


bool 
FSMNode::IsValidState(const string state)
{
	string tmp = g_utilities()->Hash2String(&fStateHashTable, 20, ",");
	FSM_DEBUG("Valid target states are : %s", tmp.c_str() );
	bool contains = (g_utilities()->Contains<string, std::shared_ptr<FSMState>  >( &fStateHashTable, state) == true);
	FSM_DEBUG("Returning %s", (contains == true ? "TRUE" : "FALSE"));
	return contains;
}


std::map<string,  std::shared_ptr<FSMState>  >  *
FSMNode::GetStateHash()
{
	return &fStateHashTable;
}


int 
FSMNode::AddChild(std::shared_ptr<FSMNode>  child)
{


	FSM_ASSERT_EXCEPTION(child != nullptr, "could not add child node becuase the pointer is ZERO");

	if (child.get() == this)
	{
		FSM_ERROR("You can not add %s as a child of itself", child->GetName().c_str());
		return FSM_RET_ERROR;
	}
	else
	{
		for (size_t i = 0; i < fChildren.size(); i++)
		{
			if (child == fChildren[i])
			{
				FSM_WARNING("fsm node with name %s allready registered as a child of this node %s, remove it first", child->GetName().c_str(), this->GetName().c_str() );
				return FSM_RET_ERROR;
			}
			if ( child->GetName() == fChildren[i]->GetName() )
			{
				FSM_WARNING("fsm child node names must be unique: \"%s\" is allready present in the list of child nodes for this node (\"%s\"), remove it first", child->GetName().c_str(), this->GetName().c_str() );
				return FSM_RET_ERROR;
			}
		}

		fChildren.push_back(child);
		child->SetMother( this  );
		return FSM_RET_SUCCESS;
	}
	

	return 0;
}


bool
FSMNode::RemoveChild( const string name )
{

	for ( auto it = fChildren.begin(); it != fChildren.end(); it++ )
	{
		if ( (*it)->GetName() == name )
		{
			fChildren.erase(it, it+1);
			return true;
		}
	}

	return false;
}


void 
FSMNode::SetMother( FSMNode  *mother)
{
	if (mother == nullptr)
	{
		FSM_INFO("mother of %s is a ZERO pointer", GetName().c_str() );
	}
	
	else if ( mother == this )
	{
		FSM_EXCEPTION("You cannot add %s as its own mother", mother->GetName().c_str() );
	}
	else
	{
		fMother = mother;
		//mother->AddChild(this);
	}

}



string 
FSMNode::GenerateUniqueID() const
{
	std::stringstream buffer;
	buffer << "0x" << std::hex << this;
	return buffer.str();
}

