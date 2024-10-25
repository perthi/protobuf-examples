
#pragma once

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <testlib/TestBase.h>

class FSMNode_Debug;


class TestFSMNode_Debug : public TestBase
{
public:
	virtual void SetUp() override;
	virtual void TearDown() override;

protected:
	FSMNode_Debug *fFSMDebug;
	
};

