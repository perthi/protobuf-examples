
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSMNode_Debug.h"
#include <common/FSMState.h>
#include <common/FSM_Definitions.h>

void 
TestFSMNode_Debug::SetUp()
{
	fFSMDebug = new FSMNode_Debug( );
}


void 
TestFSMNode_Debug::TearDown()
{
	delete fFSMDebug;
}



TEST_F(TestFSMNode_Debug, valid_states)
{
	EXPECT_TRUE(fFSMDebug->HasState("READY"));
	EXPECT_TRUE(fFSMDebug->HasState("ABORTING"));
	EXPECT_TRUE(fFSMDebug->HasState("CONFIGURING"));
	EXPECT_TRUE(fFSMDebug->HasState("ERROR"));
	EXPECT_TRUE(fFSMDebug->HasState("NOT_READY"));
	EXPECT_TRUE(fFSMDebug->HasState("OFF"));
	EXPECT_TRUE(fFSMDebug->HasState("ON"));
	EXPECT_TRUE(fFSMDebug->HasState("RUNNING"));
	EXPECT_TRUE(fFSMDebug->HasState("UNKNOWN"));
	EXPECT_TRUE(fFSMDebug->HasState("OK"));
	EXPECT_TRUE(fFSMDebug->HasState("WARNING"));
	EXPECT_TRUE(fFSMDebug->HasState("BUSY"));
	EXPECT_FALSE(fFSMDebug->HasState("gibbersih"));
}



TEST_F(TestFSMNode_Debug, state_transitions)
{
	EXPECT_EQ("UNKNOWN", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_ERROR, fFSMDebug->Excec("TURN_ON"));
	EXPECT_EQ("UNKNOWN", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMDebug->Excec("CONNECT"));
	EXPECT_EQ("NOT_READY", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMDebug->Excec("GO_READY"));
	fFSMDebug->GetCurrentState()->GetName();
	EXPECT_EQ("READY", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMDebug->Excec("CONFIGURE"));
	EXPECT_EQ("CONFIGURING", fFSMDebug->GetCurrentState()->GetName());
	fFSMDebug->StateTransition("READY");

	EXPECT_EQ("READY", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMDebug->Excec("START"));
	EXPECT_EQ("RUNNING", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMDebug->Excec("ABORT"));
	EXPECT_EQ("ERROR", fFSMDebug->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMDebug->Excec("RESET"));
	EXPECT_EQ("NOT_READY", fFSMDebug->GetCurrentState()->GetName());

}


TEST_F(TestFSMNode_Debug, name)
{
	EXPECT_EQ("FSM_DEBUG", fFSMDebug->GetName());
}
