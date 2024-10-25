// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "FSM_StateEvaluation.h"
#include <common/FSMState.h>
#include <common/FSMNode.h>
#include <common/FDefinitions.h>
#include <utilities/GTokenizer.h>
#include <mutex>


bool
FSM_StateEvaluation::IsAllInState( const string state, vector< std::shared_ptr<FSMState> > *v )
{
//	static std::mutex l_mutex;
//	std::lock_guard<std::mutex> guard( l_mutex );

	vector<string> states_v = g_tokenizer()->Tokenize( state, { " ", ",", ";", "\t" } );

	for ( size_t i = 0; i < v->size(); i++ )
	{
		string tmp = v->at( i )->GetName();

		bool found = false;
		for ( size_t j = 0; j < states_v.size(); j++ )
		{
			if ( tmp == states_v[j] )
			{
				found = true;
			}
		}
		if ( found == false )
		{
			return false;
		}
	}
	return true;
}


bool
FSM_StateEvaluation::IsAnyInState( const string state, vector< std::shared_ptr<FSMState> > *v )
{
	//	fsm_state_evaluation.lock();
	for ( size_t i = 0; i < v->size(); i++ )
	{
		if ( v->at( i )->GetName() == state )
		{
			//	fsm_state_evaluation.unlock();
			return true;
		}
	}

	//	fsm_state_evaluation.unlock();
	return false;
}


bool 
FSM_StateEvaluation::IsInState( std::shared_ptr<FSMNode> name, const string state)
{
	if (name->GetCurrentState()->GetName() == state)
	{
		return true;
	}
	else 
	{
		return false;
	}	
}
