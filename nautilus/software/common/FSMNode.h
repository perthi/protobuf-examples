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
#include <utilities/GPrintable.h>
#include <common/GComponent.h>
#include <map>
#include <vector>
using std::vector;
#include <string>
using std::string;

class FSMState;
class TestFSMNode_Debug;

#include<memory>

#define FSM_RET_SUCCESS 0
#define FSM_RET_ERROR   1



class   TestFSMNode_mother_Test;
class   TestFSMNode_add_mother_self_Test;
class   TestFSMNode_add_child_self_Test;


/** @brief   The abstract base class for all FSM (Finit State Machines) nodes 
 *  @details This is one of the tree basic building block for the FSM (The other two are KFSMAction and KFSMNode )  */
class FSMNode : public GComponent, public GPrintable

{
	friend   TestFSMNode_mother_Test;
	friend   TestFSMNode_add_mother_self_Test;
	friend   TestFSMNode_add_child_self_Test;

public:
	///API FSMNode() {} ;
    API FSMNode( const string name, const string states = "UNKNOWN ERROR READY NOT_READY" );
    virtual			API		~FSMNode();
	virtual			API		string  str() const override;
    static void		API		StateChanged(const string name, const string previous_state, const string new_state );
    static void		API		RegisterSubscriber(void(*funct)( ));
    static void		API		UpdateSubscribers( );
    virtual int		API		MapChildStates();
    virtual int		API		Excec(const string command);
	virtual int		API		Excec( std::shared_ptr<FSMNode>  node, const string action);
	virtual int		API		ExcecLocal(const string command)  = 0;
	virtual void	API		Update() = 0;
	//std::shared_ptr<KFSMNode>			API 	GetTopNode();

	FSMNode 			API * 	GetTopNode();
	std::shared_ptr<FSMState>			API 	GetStateObject(const string name);
	string				API		GetStates() const;
	string				API		GetId() const;
/// std::shared_ptr<KFSMNode>			API GetMother() const;
	FSMNode       API   * GetMother() const;
	std::shared_ptr< FSMNode>		API  	GetChildNode(const string name);
	vector< std::shared_ptr< FSMNode> >	API		GetChildNodes() const;
	int					API		GetLevel() const;
	std::shared_ptr< FSMState>			API 	GetCurrentState() const;
	string				API		GetCurrentStateName() const;
	vector< std::shared_ptr< FSMState>  >  GetCurrentChildStates() const;
	std::map < string, std::shared_ptr< FSMState>  > API * GetStateHash();

	bool			API		HasMother() const;
	bool            API     HasChild(const string name);
	int				API		AddChild(  std::shared_ptr< FSMNode>   child);
	bool            API     RemoveChild(const string name);
	bool			API		HasState(const string state)  { return IsValidState(state); };
	bool			API		IsValidState(const string state);
	int				API		StateTransition(const string target_state);
	int				API		StateTransition( std::shared_ptr< FSMState> target_state);

protected:
	virtual void API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg)  override;
	std::shared_ptr<FSMState> fStateCurrent = nullptr;					  //!< The current state of this node 
	std::map<string, std::shared_ptr<FSMState>  >  fStateHashTable;  //!< Hash map of valid states for this FSM NODE */			
//	std::shared_ptr<KFSMNode> fMother = nullptr;                            //!< The one and only mother node of this FSM. If Zero thne it can be assumed that your are on the top of the heriarchy*/ 
	FSMNode *fMother = nullptr;                            //!< The one and only mother node of this FSM. If Zero thne it can be assumed that your are on the top of the heriarchy*/ 
	vector< std::shared_ptr<FSMNode> > fChildren;                     //!< List of child nodes of this FSM*/
	//std::shared_ptr<KFSMNode> fThis =  shared_from_this();

private:
//	void	API 	SetMother( std::shared_ptr<KFSMNode>  mother);
	void	API 	SetMother( FSMNode  *mother);

	string GenerateUniqueID() const;
    static vector< void(*)( ) > fSubscribers;  //!< List of subscriber functions to call on state changes */

};

