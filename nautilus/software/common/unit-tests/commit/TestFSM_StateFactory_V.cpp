/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSM_StateFactory_V.h"
#include <common/FSM_StateFactory.h>
#include <common/FSMState.h>
#include <common/FSMNode.h>

void 
TestFSM_StateFactory_V::SetUp()
{
	fFactory = FSM_StateFactory::Instance();
}

void TestFSM_StateFactory_V::TearDown()
{
///
}


TEST_P(TestFSM_StateFactory_V, walid_states)
{
	FSMState *s = fFactory->Spawn(GetParam(), 0 );
	
	EXPECT_NE(0, (size_t)s);
	if (s != 0)
	{
		EXPECT_EQ(GetParam(), s->GetName());
	}
	
}