// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once


#include "FSMAction.h"
#include <common/FDefinitions.h>
#include <utilities/GPrintable.h>
#include <utilities/GTokenizer.h>
#include <logging/LLogging.h>
using namespace LOGMASTER;

#include <tuple>
#include <string>
using std::string;
#include <map>
#include <vector>
using std::vector;

#define ENABLED  true
#define DISABLED false

class FSMAction;
class FSMNode;

#include "FSM_StateInfo.h"


class FSMState : public GPrintable
{
public:
    API  FSMState(  );
	API  FSMState( FSMNode *fsm );
	virtual				API		~FSMState();
	virtual const char	API	  *	GetClassType() = 0;	
	virtual string		API		GetName() const;
	void				API		SetName(const string name);
	void				API		SetColor(const int color);
	int					API     GetColor() const;
	FSM_StateInfo		API		GetStateInfo() const;
    void				API		SetFSM( FSMNode *fsm);
    FSMNode  API *	GetFSM();

	vector< std::tuple<string, string> >	API	GetValidActions() const;
	static vector<string>	API		GetAllActions( std::map<FSMAction *, bool > *hash );
	virtual	string			API		str() const override;
	static string			API		GetValidActionsString( const vector< std::tuple<string, string> >  &a) ;
	string					API		GetValidActionsString( ) const;
	static void				API		EnableAction(const string action,  std::map<FSMAction *, bool > *hash);
	static void				API		EnableActions(const string action, std::map<FSMAction *, bool > *hash, FSM_StateInfo *sinfo);
	void					API     EnableAction(const string action);
	bool					API		IsValid(const string action) const;
	bool					API		IsValidAction(const string action) const;
	bool					API		IsEnabledAction(const string action, FSMAction ** = 0) const;
	virtual int				API		Excec(const string cmnd) const;
	std::map<FSMAction *, bool >  API * GetActionHash();

protected:
	FSM_StateInfo fStateInfo;
	std::map<FSMAction *, bool >  fActionHash;

private:
	void Init();
    FSMNode *fFSM = nullptr;

};



