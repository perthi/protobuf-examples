
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestGComponentID.h"
#include <common/GIDGenerator.h>
// #include <common/include/GComponentID.h>

#include <common/MBPayloadDummyA.h>
#include <common/MBPayloadDummyB.h>
#include <common/MBPayloadDummyC.h>
#include <common/GComponentDummyA.h>
#include <common/GComponentDummyB.h>
#include <common/GComponentDummyC.h>


TestGComponentID::TestGComponentID()
{
	fIdGenerator = GIDGenerator::Instance();
}


TestGComponentID::~TestGComponentID()
{
}


TEST_F(TestGComponentID, operator_equal)
{
	string id1 = fIdGenerator->CreateUniqueID("TEST");
	string id2 = fIdGenerator->CreateUniqueID("TEST");

	EXPECT_FALSE ( id1 ==  id2 );
	EXPECT_TRUE  ( id1 ==  id1 );

}



TEST_F( TestGComponentID, actual_components )
{
	GComponentDummyA  *nodeA = new GComponentDummyA();
	GComponentDummyB  *nodeB = new GComponentDummyB();
	GComponentDummyC  *nodeC = new GComponentDummyC();

	EXPECT_NE( nodeA->GetComponentID(), nodeB->GetComponentID() );
	EXPECT_NE( nodeB->GetComponentID(), nodeC->GetComponentID() );

	delete nodeA;
	delete nodeB;
	delete nodeC;
}
