
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSMNode_V.h"

#include <common/FSM_Definitions.h>

void TestFSMNode_V::SetUp()
{
	fFSM = new FSMNode_Debug( "FSM_UNIT_TESTS");
}

void TestFSMNode_V::TearDown()
{
	delete fFSM;
}


INSTANTIATE_TEST_CASE_P(fsm_base_class, TestFSMNode_V, ::testing::Values( "UNKNOWN", "ERROR", 
																       "READY", "NOT_READY"));




TEST_P(TestFSMNode_V, statenames)
{
	std::shared_ptr< FSMState> s = fFSM->GetStateObject(GetParam());
	if (s != 0)
	{
		EXPECT_EQ(GetParam(), s->GetName());
	}
	else
	{
		FAIL();
	}
}


TEST_P(TestFSMNode_V, valid_states)
{
	EXPECT_TRUE(fFSM->HasState(GetParam()));
}