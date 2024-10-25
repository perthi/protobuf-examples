
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSM_StateInfo.h"

#include <common/FSM_StateInfo.h>
#include <common/FSM_Definitions.h> 
#include <utilities/GUtilities.h>

void 
TestFSM_StateInfo::SetUp()
{

}

void 
TestFSM_StateInfo::TearDown()
{

}


TEST_F(TestFSM_StateInfo, actions_ready)
{
	FSMState_Ready *s = new FSMState_Ready(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("READY", i.fName);
	EXPECT_TRUE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}




TEST_F(TestFSM_StateInfo, actions_aborting)
{
	FSMState_Aborting *s = new FSMState_Aborting(0);\
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("ABORTING", i.fName);
	EXPECT_FALSE( g_utilities()->HasElement( string( "DISCONNECT"), i.fActions) );
	EXPECT_FALSE( g_utilities()->HasElement( string( "CONNECT"),  i.fActions) );
	EXPECT_FALSE( g_utilities()->HasElement( string( "GO_READY"),      i.fActions) );
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));
	
	delete s;
}


TEST_F(TestFSM_StateInfo, actions_configuring)
{
	FSMState_Configuring *s = new FSMState_Configuring(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("CONFIGURING", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("ABORT"), i.fActions));
	
	delete s;
}


TEST_F(TestFSM_StateInfo, actions_error)
{
	FSMState_Error *s = new FSMState_Error(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("ERROR", i.fName);
	EXPECT_TRUE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));
	
	delete s;
}


TEST_F(TestFSM_StateInfo, actions_not_ready)
{
	FSMState_NotReady *s = new FSMState_NotReady(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("NOT_READY", i.fName);
	EXPECT_TRUE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));
	
	delete s;
}


TEST_F(TestFSM_StateInfo, actions_off)
{
	FSMState_Off *s = new FSMState_Off(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("OFF", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}


TEST_F(TestFSM_StateInfo, actions_on)
{
	FSMState_On *s = new FSMState_On(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("ON", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}


TEST_F(TestFSM_StateInfo, actions_running)
{
	FSMState_Running *s = new FSMState_Running(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("RUNNING", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}



TEST_F(TestFSM_StateInfo, actions_unknown)
{
	FSMState_Unknown *s = new FSMState_Unknown(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("UNKNOWN", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_TRUE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}


TEST_F(TestFSM_StateInfo, actions_ok)
{
	FSMState_OK *s = new FSMState_OK(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("OK", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}



TEST_F(TestFSM_StateInfo, actions_warning)
{
	FSMState_Warning *s = new FSMState_Warning(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("WARNING", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}



TEST_F(TestFSM_StateInfo, actions_busy)
{
	FSMState_Busy *s = new FSMState_Busy(0); \
	FSM_StateInfo i = s->GetStateInfo();

	EXPECT_EQ("BUSY", i.fName);
	EXPECT_FALSE(g_utilities()->HasElement(string("DISCONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONNECT"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("CONFIGURE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("GO_READY"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("RESET"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("START"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_OFF"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("TURN_ON"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("PAUSE"), i.fActions));
	EXPECT_FALSE(g_utilities()->HasElement(string("ABORT"), i.fActions));

	delete s;
}


