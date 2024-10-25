
#pragma once

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <testlib/TestBase.h>

class FSM_StateFactory;
class FSMNode;

class TestFSM_StateFactory_V : public ::testing::WithParamInterface< string>, public TestBase
{
public:
	virtual void SetUp() override;
	virtual void TearDown() override;
	
protected:
	FSM_StateFactory *fFactory;
};



INSTANTIATE_TEST_CASE_P(spawn, TestFSM_StateFactory_V, ::testing::Values("READY", "ABORTING", "CONFIGURING", "ERROR", "NOT_READY", "OFF", "ON", "RUNNING", "UNKNOWN", "OK", "WARNING"));


//INSTANTIATE_TEST_CASE_P(spawn, TestFSM_StateFactory_V, ::testing::Values("READY", "ABORTING", "CONFIGURING", "ERROR", "NOT_READY", "RUNNING", "UNKNOWN", "OK", "WARNING"));

