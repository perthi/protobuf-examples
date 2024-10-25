/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSMController.h"

void 
TestAPIFSMController::SetUp()
{
	/*
	static bool isfirst = true;

	fController = APIFSMController::Instance();

	if (isfirst == true)
	{
		fController->GenerateMocFSM();
	}
	*/
}


void 
TestAPIFSMController::TearDown()
{
 
}


/*
TEST_F(TestFSMController, fsm_node_check)
{
	EXPECT_EQ(0, (int)fController->GetFSM("blahh"));
	EXPECT_NE(0, (int)fController->GetFSM("MAIN_FSM"));
	EXPECT_NE(0, (int)fController->GetFSM("DATABASE"));
	EXPECT_NE(0, (int)fController->GetFSM("ENVIRONMENT"));
	EXPECT_NE(0, (int)fController->GetFSM("DMM_1"));
	EXPECT_NE(0, (int)fController->GetFSM("DMM_2"));
	EXPECT_NE(0, (int)fController->GetFSM("RFGEN_1"));
	EXPECT_NE(0, (int)fController->GetFSM("DCPOW_1"));
}


TEST_F(TestFSMController, fsm_node_check2)
{
	EXPECT_EQ(0, (int)fController->GetFSM("blahh"));
	EXPECT_NE(0, (int)fController->GetFSM("MAIN_FSM"));
	EXPECT_NE(0, (int)fController->GetFSM("DATABASE"));
	EXPECT_NE(0, (int)fController->GetFSM("ENVIRONMENT"));
	EXPECT_NE(0, (int)fController->GetFSM("DMM_1"));
	EXPECT_NE(0, (int)fController->GetFSM("DMM_2"));
	EXPECT_NE(0, (int)fController->GetFSM("RFGEN_1"));
	EXPECT_NE(0, (int)fController->GetFSM("DCPOW_1"));
}

*/