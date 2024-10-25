
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestFSMNode.h"
#include <common/FSM_Definitions.h>
#include <utilities/GException.h>

FSMNode_Debug * TestFSMNode::fFSM = nullptr;


void 
TestFSMNode::SetUp()
{
	
}


void 
TestFSMNode::TearDown()
{
	
}



void TestFSMNode::SetUpTestCase()
{
	// fFSM = new FSMNode_Debug(0, "FSM google test");
}

void TestFSMNode::TearDownTestCase()
{
	//delete fFSM;
}


TEST_F(TestFSMNode, initial_state)
{
	//EXPECT_EQ("UNKNOWN", fFSM->GetCurrentState()->GetName());
}


TEST_F( TestFSMNode, recursive_addchild_NSR2987 )
{
	std::shared_ptr<FSMNode>  m = std::make_shared< FSMNode_Main>("PTH");
	std::shared_ptr<FSMNode> c1 = std::shared_ptr<FSMNode_Debug>(new FSMNode_Debug("CHILD1") );
	std::shared_ptr<FSMNode> c2 = std::make_shared< FSMNode_Debug>("CHILD2");
	EXPECT_EQ( FSM_RET_SUCCESS,  m->AddChild(c1) );
	EXPECT_EQ( FSM_RET_SUCCESS,  m->AddChild(c2) );
	EXPECT_EQ( "PTH", c1->GetMother()->GetName() );

	std::shared_ptr<FSMNode> test1 = m->GetChildNode( "CHILD1" );
	std::shared_ptr<FSMNode> test2 = m->GetChildNode( "CHILD2" );
	ASSERT_NE( test1, nullptr );
	ASSERT_NE( test2, nullptr );
	EXPECT_EQ( "PTH", test1->GetMother()->GetName() );
	EXPECT_EQ( "PTH", test2->GetMother()->GetName()  );
	ASSERT_NE( m->GetChildNode("CHILD1"), nullptr)  ;
	ASSERT_NE( m->GetChildNode("CHILD2"), nullptr) ;
	EXPECT_EQ( "PTH",  c1->GetMother( )->GetName() );
	EXPECT_EQ( "PTH",  c2->GetMother( )->GetName()  ) ;
	EXPECT_TRUE( m->HasChild("CHILD1") );
	EXPECT_TRUE( m->HasChild("CHILD2") );
	EXPECT_TRUE( m->RemoveChild("CHILD1") );
	EXPECT_FALSE( m->HasChild("CHILD1") );
	EXPECT_TRUE( m->HasChild("CHILD2") );
	EXPECT_TRUE (m->RemoveChild("CHILD2") );
	EXPECT_FALSE( m->HasChild("CHILD1") );
	EXPECT_FALSE( m->HasChild("CHILD2") );
	EXPECT_FALSE( m->RemoveChild( "CHILD1" ) );
	EXPECT_FALSE( m->RemoveChild( "CHILD2" ) );
	EXPECT_EQ( FSM_RET_SUCCESS,  m->AddChild(c1) );
	EXPECT_EQ( FSM_RET_SUCCESS,  m->AddChild(c2) );
	EXPECT_TRUE( m->HasChild("CHILD1") );
	EXPECT_TRUE( m->HasChild("CHILD2") );
}





TEST_F(TestFSMNode, constructors )
{
//	for ( int i = 0; i < 10000; i++ )
	{
	//	if ( i % 10 == 0 )
		{
	//		FORCE_DEBUG("i = %d", i );
		}

		FSMNode_Debug *n = new FSMNode_Debug("lorem ipsum" );
		EXPECT_EQ( "lorem ipsum", n->GetName() );
		delete n;
		n = new FSMNode_Debug( "TEST_CONSTRUCTOR", "ERROR;NOT_READY;READY;UNKNOWN" );
		EXPECT_EQ( "TEST_CONSTRUCTOR", n->GetName() );
		EXPECT_TRUE( n->HasState( "ERROR" ) );
		EXPECT_TRUE( n->HasState( "NOT_READY" ) );
		EXPECT_TRUE( n->HasState( "READY" ) );
		EXPECT_TRUE( n->HasState( "UNKNOWN" ) );
		EXPECT_FALSE( n->HasState( "OK" ) );
		EXPECT_FALSE( n->HasState( "ON" ) );
		//	EXPECT_FALSE(n->HasState("CONFIGURING"));
		EXPECT_FALSE( n->HasState( "ABORTING" ) );
		delete n;
	}
}


TEST_F(TestFSMNode,  mother)
{
	std::shared_ptr<FSMNode_Debug>  mother =  std::shared_ptr<FSMNode_Debug>(  new FSMNode_Debug( "mother") );
	std::shared_ptr<FSMNode_Debug>  child =   std::shared_ptr<FSMNode_Debug>( new  FSMNode_Debug( "child") ) ;
	
	mother->AddChild(child);

	
	EXPECT_EQ("mother", child->GetMother()->GetName() );
	FSMNode_Debug  *mother2 =  new FSMNode_Debug("mother2");
	child->SetMother(mother2);
	EXPECT_EQ("mother2", child->GetMother()->GetName());
}



TEST_F(TestFSMNode, add_child)
{
	std::shared_ptr<FSMNode_Debug>  m  =  std::make_shared<FSMNode_Debug>("mother");
	std::shared_ptr<FSMNode_Debug>  c1 =  std::make_shared<FSMNode_Debug>("child1");
	std::shared_ptr<FSMNode_Debug>  c2 =  std::make_shared<FSMNode_Debug>("child2");
	std::shared_ptr<FSMNode_Debug>  c3 =  std::make_shared<FSMNode_Debug>("child3");

	m->AddChild(c1);
	m->AddChild(c2);
	m->AddChild(c3);

	vector< std::shared_ptr<FSMNode> > children = m->GetChildNodes();
	EXPECT_EQ(3, children.size());
	EXPECT_EQ("child1", children[0]->GetName());
	EXPECT_EQ("child2", children[1]->GetName());
	EXPECT_EQ("child3", children[2]->GetName());
}



TEST_F(TestFSMNode, add_mother_self)
{	
	FSMNode_Debug *n =new FSMNode_Debug( "test" );
	EXPECT_THROW(n->SetMother(n), GFSMException);
}


TEST_F(TestFSMNode, add_child_self)
{
	FSMNode_Debug *n =  new FSMNode_Debug( "test");
	EXPECT_THROW(n->SetMother(n), GFSMException);
}


TEST_F(TestFSMNode, add_child_duplicate)
{
	std::shared_ptr<FSMNode_Debug> n = std::make_shared< FSMNode_Debug > ("test");
	std::shared_ptr<FSMNode_Debug> c = std::make_shared< FSMNode_Debug > ("child1");
	n->AddChild(c);
	EXPECT_EQ(FSM_RET_ERROR, n->AddChild(c));
	std::shared_ptr<FSMNode_Debug> c2 =std::make_shared<FSMNode_Debug>("child1"); // another child node with the same name, now we also expectan exeption
	EXPECT_EQ(FSM_RET_ERROR, n->AddChild(c2));
}






TEST_F(TestFSMNode, constructor_bug_KFR_152)
{
	std::shared_ptr<FSMNode_Debug> mother = std::make_shared< FSMNode_Debug >("test_mother");
	std::shared_ptr<FSMNode_Debug> c1 = std::make_shared< FSMNode_Debug >("child1");
	std::shared_ptr<FSMNode_Debug> c2 = std::make_shared< FSMNode_Debug >("child2");

	mother->AddChild(c1);
	mother->AddChild(c2);

	EXPECT_EQ(2, mother->GetChildNodes().size());

}
