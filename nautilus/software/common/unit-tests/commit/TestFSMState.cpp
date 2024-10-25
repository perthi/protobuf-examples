
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSMState.h"
#include <common/FSM_Definitions.h>
#include <common/FSMColor.h>


void TestFSMState::SetUp()
{
	//FORCE_DEBUG("Creating FSM Tp0");
	fFSM = new FSMNode_Debug("state and action test");
	//FORCE_DEBUG("Created FSM Tp1, the name is %s", fFSM->GetName() );
}


void TestFSMState::TearDown()
{	
	delete fFSM;
}



TEST_F(TestFSMState, init)
{
	EXPECT_TRUE(true);
	FSMState_NotReady *s = new FSMState_NotReady(fFSM);
	size_t n1 = s->GetActionHash()->size();
	EXPECT_GT(n1, (size_t)1);
}



TEST_F(TestFSMState, valid_actions_aborting)
{
	FSMState_Aborting *  s = new  FSMState_Aborting(fFSM);
	EXPECT_EQ(false, s->IsEnabledAction("DISCONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONFIGURE"));
	EXPECT_EQ(false, s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(false, s->IsEnabledAction("RESET"));
	EXPECT_EQ(false, s->IsEnabledAction("START"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(false, s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(false, s->IsEnabledAction("ABORT"));

	EXPECT_EQ(C_FSM_FATAL, s->GetColor());
	delete s;
}



TEST_F(TestFSMState, valid_actions_configuring)
{
	FSMState_Configuring *  s = new  FSMState_Configuring(fFSM);
	EXPECT_EQ(false, s->IsEnabledAction("DISCONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONFIGURE"));
	EXPECT_EQ(false, s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(false, s->IsEnabledAction("RESET"));
	EXPECT_EQ(false, s->IsEnabledAction("START"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(false, s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(true,  s->IsEnabledAction("ABORT"));

	EXPECT_EQ(C_FSM_TRANSIENT, s->GetColor());

	delete s;
}



TEST_F(TestFSMState, valid_actions_error)
{
	FSMState_Error *  s = new  FSMState_Error(fFSM);
	EXPECT_EQ(true, s->IsEnabledAction("DISCONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONFIGURE"));
	EXPECT_EQ(false, s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(true, s->IsEnabledAction("RESET"));
	EXPECT_EQ(false, s->IsEnabledAction("START"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(false, s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(false, s->IsEnabledAction("ABORT"));
	EXPECT_EQ(C_FSM_ERROR, s->GetColor());

	delete s;
}



TEST_F(TestFSMState, valid_actions_not_ready)
{
	FSMState_NotReady *  s = new  FSMState_NotReady(fFSM);
	EXPECT_EQ(true,  s->IsEnabledAction("DISCONNECT"));
	EXPECT_EQ(false, s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(true,  s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(true,  s->IsEnabledAction("RESET"));
	EXPECT_EQ(true, s->IsEnabledAction("START"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false, s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(false, s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(false, s->IsEnabledAction("ABORT"));

	EXPECT_EQ(C_FSM_WAITING, s->GetColor());

	delete s;
}



TEST_F(TestFSMState, valid_actions_ready)
{
	FSMState_Ready *  s = new  FSMState_Ready(fFSM);
	EXPECT_EQ(true,   s->IsEnabledAction("DISCONNECT"));
	EXPECT_EQ(false,  s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(false,  s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(true,   s->IsEnabledAction("RESET"));
	EXPECT_EQ(true,   s->IsEnabledAction("START"));
	EXPECT_EQ(false,  s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false,  s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(false,  s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(false,  s->IsEnabledAction("ABORT"));

	EXPECT_EQ(C_FSM_OK, s->GetColor());

	delete s;
}



TEST_F(TestFSMState, valid_actions_running)
{
	FSMState_Running * s = new  FSMState_Running(fFSM);
	EXPECT_EQ(false,   s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(false,   s->IsEnabledAction("CONFIGURE"));
	EXPECT_EQ(false,   s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(false,   s->IsEnabledAction("RESET"));
	EXPECT_EQ(false,   s->IsEnabledAction("START"));
	EXPECT_EQ(false,   s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false,   s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(true,    s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(true,    s->IsEnabledAction("ABORT"));

	EXPECT_EQ(C_FSM_OK, s->GetColor());

	delete s;
}



TEST_F(TestFSMState, valid_actions_unknown)
{
	FSMState_Unknown * s = new  FSMState_Unknown(fFSM);
	EXPECT_EQ(false,   s->IsEnabledAction("DISCONNECT"));
	EXPECT_EQ(true,    s->IsEnabledAction("CONNECT"));
	EXPECT_EQ(false,   s->IsEnabledAction("CONFIGURE"));
	EXPECT_EQ(false,   s->IsEnabledAction("GO_READY"));
	EXPECT_EQ(false,   s->IsEnabledAction("RESET"));
	EXPECT_EQ(false,   s->IsEnabledAction("START"));
	EXPECT_EQ(false,   s->IsEnabledAction("TURN_OFF"));
	EXPECT_EQ(false,   s->IsEnabledAction("TURN_ON"));
	EXPECT_EQ(false,   s->IsEnabledAction("PAUSE"));
	EXPECT_EQ(false,   s->IsEnabledAction("ABORT"));

	EXPECT_EQ(C_FSM_UNKNOWN, s->GetColor());
	delete s;
}


TEST_F( TestFSMState, state_transition )
{
	
	SET_LOGLEVEL("--fsm-debug");
	EXPECT_EQ("UNKNOWN", fFSM->GetCurrentState()->GetName());


	fFSM->Excec("CONNECT");	
	EXPECT_EQ("NOT_READY", fFSM->GetCurrentState()->GetName());

	fFSM->Excec("ABORT"); // Nothing to abort when in state not ready so we expect state to be the same
	EXPECT_EQ("NOT_READY", fFSM->GetCurrentState()->GetName());
	fFSM->Excec("GO_READY");
	EXPECT_EQ("READY", fFSM->GetCurrentState()->GetName());
	fFSM->Excec("RESET");
	EXPECT_EQ("NOT_READY", fFSM->GetCurrentState()->GetName());		

}



TEST_F( TestFSMState, illegal_actions )
{
	std::shared_ptr<FSMState>  s = fFSM->GetCurrentState();
	EXPECT_ANY_THROW(s->Excec("gibberish"));
	EXPECT_EQ("UNKNOWN", fFSM->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_ERROR, fFSM->Excec("GO_READY") );
}


