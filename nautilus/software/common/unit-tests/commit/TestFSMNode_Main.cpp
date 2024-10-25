
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSMNode_Main.h"
#include <common/FSM_Definitions.h>



void
TestFSMNode_Main::SetUp()
{
	fFSMMain = new FSMNode_Main();
}


void
TestFSMNode_Main::TearDown()
{
	delete fFSMMain;
}


TEST_F(TestFSMNode_Main, valid_states)
{
	EXPECT_TRUE(fFSMMain->HasState("READY"));
	EXPECT_FALSE(fFSMMain->HasState("ABORTING"));
//	EXPECT_TRUE(fFSMMain->HasState("CONFIGURING"));
	EXPECT_TRUE(fFSMMain->HasState("ERROR"));
	EXPECT_TRUE(fFSMMain->HasState("NOT_READY"));
	EXPECT_FALSE(fFSMMain->HasState("OFF"));
	EXPECT_FALSE(fFSMMain->HasState("ON"));
	EXPECT_TRUE(fFSMMain->HasState("RUNNING"));
	EXPECT_TRUE(fFSMMain->HasState("UNKNOWN"));
	EXPECT_FALSE(fFSMMain->HasState("OK"));
	EXPECT_FALSE(fFSMMain->HasState("WARNING"));
	EXPECT_FALSE(fFSMMain->HasState("BUSY"));
	EXPECT_FALSE(fFSMMain->HasState("gibbersih"));
}


TEST_F(TestFSMNode_Main, name)
{
	EXPECT_EQ("MAIN_FSM", fFSMMain->GetName());
}


TEST_F(TestFSMNode_Main, state_transition)
{	
	EXPECT_EQ("UNKNOWN", fFSMMain->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMMain->Excec("CONNECT"));
	EXPECT_EQ("NOT_READY", fFSMMain->GetCurrentState()->GetName());	
	EXPECT_EQ(FSM_RET_ERROR, fFSMMain->Excec("ABORT"));
	EXPECT_EQ("NOT_READY", fFSMMain->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMMain->Excec("GO_READY"));
	EXPECT_EQ("READY", fFSMMain->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_ERROR, fFSMMain->Excec("ABORT"));
	EXPECT_EQ("READY", fFSMMain->GetCurrentState()->GetName());
 //   EXPECT_EQ(FSM_RET_SUCCESS, fFSMMain->Excec("CONFIGURE"));	
//	EXPECT_EQ("CONFIGURING", fFSMMain->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_ERROR, fFSMMain->Excec("ABORT"));
	EXPECT_EQ("READY", fFSMMain->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMMain->Excec("RESET"));
	EXPECT_EQ("NOT_READY", fFSMMain->GetCurrentState()->GetName());
	EXPECT_EQ(FSM_RET_SUCCESS, fFSMMain->Excec("DISCONNECT"));
	EXPECT_EQ("UNKNOWN", fFSMMain->GetCurrentState()->GetName());
}

