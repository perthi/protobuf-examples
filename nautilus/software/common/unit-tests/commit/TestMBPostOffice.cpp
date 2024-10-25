
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestMBPostOffice.h"
#include <common/MBMessage.h>
#include <common/MBPostOffice.h>
#include <common/GComponentDummyA.h>
#include <common/GComponentDummyB.h>
#include <common/GComponentDummyC.h>
#include <common/MBMessageInfo.h>
#include <common/MBMessageRequest.h>
#include <common/MBEnums.h>
#include <memory>

#include <utilities/GException.h>

MBPostOffice *TestMBPostOffice::po = nullptr;


void
TestMBPostOffice::SetUpTestCase()
{
	po = MBPostOffice::Instance();
	po->DeleteMessageChannels();
}


void
TestMBPostOffice::SetUp()
{
	po->CreateMessageChannels();
	MBPostOffice::Instance();
	G_DEBUG("staring post office");
	ASSERT_TRUE( MBPostOffice::Instance()->IsRunning() ) << " POST OFFICE IS NOT RUNNING !!!!!!!!"; 
	MBPostOffice::Instance()->StartPostOffice();
}


void 
TestMBPostOffice::TearDown()
{
	try
	{
		po->DeleteMessageChannels();
	}
	catch (std::exception e)
	{
		FORCE_DEBUG("Exception caught delting channels: %s", e.what() );
	}
}






// TEST_F(TestMBPostOffice, start_stop )
// {
// 	for(int i=0; i < 10; i++)
// 	{
// 		//	FORCE_DEBUG( "i = %d", i );
// 		po->Stop();
// 		po->Start();
// 		po->Stop();
// 		po->Start();
// 		po->Start();
// 		po->Stop();
// 		po->Stop();
// 		po->Start();
// 	}
// }




TEST_F(TestMBPostOffice,  total_channels )
{
	for ( int i = 0; i < 5; i++ )
	{
		po->CreateMessageChannels();
		po->CreateMessageChannels();
		po->CreateMessageChannels();
		po->CreateMessageChannels();
		auto tmp = po->GetChannelMap();
		EXPECT_EQ( 13, tmp->size() );
		po->DeleteMessageChannels();
		tmp = po->GetChannelMap();
		EXPECT_EQ( 0, tmp->size() );
	}
	po->CreateMessageChannels();
}



TEST_F(TestMBPostOffice, get_channels)
{
	vector<string > channels = po->GetChannels("FSM");
	EXPECT_EQ( 3, channels.size() );
	channels = po->GetChannels("FSM", true);
	EXPECT_EQ(1, channels.size());
}


TEST_F(TestMBPostOffice, subscriber_registration  )
{
	GComponentDummyA *ca = new GComponentDummyA();
	GComponentDummyB *cb = new GComponentDummyB();
	ca->DoSubscribe("FSM");   /// Subscribe to FSM and all sub channels
	cb->DoSubscribe("FSM");   /// Subscribe to FSM and all sub channels
	auto func = po->GetSubscriberFunctions("FSM");
	EXPECT_EQ(2, func.size() );
	func = po->GetSubscriberFunctions("FSM::MAIN");
	EXPECT_EQ(2, func.size());	
	cb->DoSubscribe("FSM::MAIN");
	func = po->GetSubscriberFunctions("FSM::MAIN");  /// Subscribe to FSM::MAIN and all sub channels	
	EXPECT_EQ(3, func.size());
	func = po->GetSubscriberFunctions("FSM::MAIN::SEM");
	EXPECT_EQ(3, func.size());
	delete ca;
	delete cb;
}



TEST_F(TestMBPostOffice, subscriber_registration_exact_match)
{
	po->ResetSubscriberLists();
	GComponentDummyA *ca = new GComponentDummyA();
	GComponentDummyB *cb = new GComponentDummyB();
	ca->DoSubscribe("FSM", EXACT_MATCH );   /// Subscribe to FSM and all sub channels
	cb->DoSubscribe("FSM", EXACT_MATCH );   /// Subscribe to FSM and all sub channels
	auto func = po->GetSubscriberFunctions("FSM");
	EXPECT_EQ(2, func.size());

	func = po->GetSubscriberFunctions("FSM::MAIN");
	EXPECT_EQ(0, func.size());

	cb->DoSubscribe("FSM::MAIN", EXACT_MATCH );
	func = po->GetSubscriberFunctions("FSM::MAIN");  /// Subscribe to FSM::MAIN and all sub channels	
	EXPECT_EQ(1, func.size());
}



TEST_F(TestMBPostOffice, subscriber_duplicate_removal)
{
//	for ( int i = 0; i < 10; i++  )
	{
		po->ResetSubscriberLists();
		GComponentDummyA *ca = new GComponentDummyA();
		GComponentDummyB *cb = new GComponentDummyB();
		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		cb->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		auto func = po->GetSubscriberFunctions( "FSM" );
		EXPECT_EQ( 2, func.size() );

		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		cb->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		func = po->GetSubscriberFunctions( "FSM" );
		EXPECT_EQ( 4, func.size() );

		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels
		ca->DoSubscribe( "FSM" );   /// Subscribe to FSM and all sub channels

		func = po->GetSubscriberFunctions( "FSM" );
		EXPECT_EQ( 10, func.size() );

		po->RemoveDuplicateSubcribers();

		func = po->GetSubscriberFunctions( "FSM" );
		EXPECT_EQ( 2, func.size() );

	//	FORCE_DEBUG("done, i = %d", i );
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds( 10 ) )  ;
}



TEST_F(TestMBPostOffice, message_registration)
{
	MBMessage m1( "m1 message");
	MBMessage m2( "m2 message");
	MBMessage m3( "m3 message");
	MBMessage m4( "m4 message");
	MBMessage m5( "m5 message");

	
	GComponentDummyA  *nodeA = new GComponentDummyA();
	GComponentDummyB  *nodeB = new GComponentDummyB();
	GComponentDummyC  *nodeC = new GComponentDummyC();

//	for ( int i = 0; i < 10; i++ )
	{
		
		po->Purge();
		EXPECT_EQ( 0, po->ExtractMessages().size() );
		po->StopPostOffice();
		po->QueMessage( m1, "FSM",	ANY_MATCH);
		po->QueMessage( m2, "FSM", ANY_MATCH );
		EXPECT_EQ( 2, po->GetMessages().size() );
		po->QueMessage( m3, "FSM::MAIN",	ANY_MATCH );
		po->QueMessage( m4, "FSM::DRIVER",  ANY_MATCH );
		po->QueMessage( m5, "SCHEDULER",    EXACT_MATCH );
		po->QueMessage( m3, "FSM::MAIN",    ANY_MATCH );
		po->QueMessage( m4, "FSM::DRIVER",  ANY_MATCH  );
		po->QueMessage( m5, "SCHEDULER",	EXACT_MATCH );
		EXPECT_EQ( 8, po->GetMessages().size() );
		po->StartPostOffice();
		po->DispatchMessages();
		std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
		EXPECT_EQ( 0, po->ExtractMessages().size() );
		EXPECT_EQ( 0, po->GetMessages().size() );
		nodeA->DoSubscribe( "FSM" );
		

		nodeA->DoSubscribe( "blahhh" );
		
		
		nodeA->DoSubscribe( "blahhh" );
		nodeA->DoSubscribe( "blahhh" );
		nodeB->DoSubscribe( "FSM" );
		nodeB->DoSubscribe( "blahhh" );
		nodeB->DoSubscribe( "blahhh" );
		nodeB->DoSubscribe( "blahhh" );
		nodeC->DoSubscribe( "FSM::DRIVER" );
		nodeC->DoSubscribe( "SCHEDULER" );
		po->DispatchMessages();
		EXPECT_EQ( 0, po->ExtractMessages().size() );
		EXPECT_EQ( 0, po->GetMessages().size() );
		po->DispatchMessages();
	
	}

	delete nodeA;
	delete nodeB;
	delete nodeC;
}



/// Now lets ens som messages to invalid channels to check that they end up in the dead l�etters channels
TEST_F(TestMBPostOffice,  dead_letters )
{
	try
	{
		po->Purge();
		EXPECT_EQ( 0, po->GetDeadLetters()->size() );
		MBMessage m1( "m1 message" );
		po->QueMessage( m1, "blahhhhh", ANY_MATCH );
		po->DispatchMessages();
		EXPECT_EQ( 1, po->GetDeadLetters()->size() );
		po->StopPostOffice();
		po->QueMessage( m1, "blahhhhh", ANY_MATCH );
		po->QueMessage( m1, "blahhhhh1", ANY_MATCH );
		po->QueMessage( m1, "blahhhhh2", ANY_MATCH );
		po->StartPostOffice();
			
		po->DispatchMessages();
		std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
		po->GetDeadLetters();
		std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
	}
	catch ( GException &e )
	{
		cout << e.what();
	}
	catch ( std::exception &e )
	{
		CERR << e.what();
	}
	catch ( ... )
	{
		CERR << "Unkown exception" << endl;
	}
}	



TEST_F(TestMBPostOffice, is_match )
{
	EXPECT_TRUE( po->IsMatch(   MBRequestChannel_t( "DEBUG" ), MBSubscriberChannel_t( "DEBUG" ) ) );
	EXPECT_FALSE( po->IsMatch(  MBRequestChannel_t( "DE" ),    MBSubscriberChannel_t( "DEBUG" ) ) );
	EXPECT_TRUE( po->IsMatch(   MBRequestChannel_t( "DE" ),    MBSubscriberChannel_t( "DEBUG" ), ANY_MATCH  ) );
}



TEST_F(TestMBPostOffice, is_subscriber )
{
	GComponentDummyB nodeB;
	EXPECT_FALSE( po->IsSubscriber( nodeB.GetComponentID(), MBRequestChannel_t("DEBUG") ) );
	nodeB.DoSubscribe("DEBUG");
	EXPECT_TRUE( po->IsSubscriber( nodeB.GetComponentID(), MBRequestChannel_t("DEBUG") ) );

}




TEST_F(TestMBPostOffice, send_blocking_invalid )
{
	ASSERT_TRUE( MBPostOffice::Instance()->IsRunning() ) << " POST OFFICE IS NOT RUNNING !!!!!!!!"; 
	 std::this_thread::sleep_for(std::chrono::milliseconds(500));
	MBMessageRequest m(eMESSAGE_REQUEST::FSM_STATE);
	auto reply = po->SendMessageBlocking(m, "FSM", 1000);
	ASSERT_NE(reply, nullptr);
	/// We expect nobody to listen for device scan on the FSM channel so the post office should return a blokcing error
	EXPECT_TRUE( reply->HasPayloadType<eBLOCKING_ERROR>() ) ;

	const  eBLOCKING_ERROR * const content = reply->ExtractRawPayload<eBLOCKING_ERROR>();

	ASSERT_NE( content, nullptr) << "content is a zero pointer" << endl;

	EXPECT_EQ( (int)(*content), (int)eBLOCKING_ERROR::NO_SUBSCRIBERS );


	GComponentDummyA nodeA;
	GComponentDummyB nodeB;

	nodeA.DoSubscribe("DEBUG");
	nodeB.DoSubscribe("DEBUG");

	EXPECT_EQ( 2, po->GetSubscriberCount( MBSubscriberChannel_t("DEBUG") ) );
	reply = po->SendMessageBlocking(m, "DEBUG", 1000);
	ASSERT_NE(reply, nullptr);
	/// We expect nobody to listen for device scan on the FSM channel so the post office should return a blokcing error
	EXPECT_TRUE( reply->HasPayloadType<eBLOCKING_ERROR>() );
	const  eBLOCKING_ERROR * const content2 = reply->ExtractRawPayload<eBLOCKING_ERROR>();
	EXPECT_EQ( (int)(*content2), (int)eBLOCKING_ERROR::MULTIPLE_SUBSCRIBERS );
	EXPECT_EQ( CH_REMOVAL_OK,   nodeA.DoUnSubscribe("DEBUG") );
	EXPECT_EQ( 1, po->GetSubscriberCount( MBSubscriberChannel_t("DEBUG") ) );
	reply = po->SendMessageBlocking( m, "DEBUG", 1000 );
	const  eBLOCKING_ERROR * const content3 = reply->ExtractRawPayload<eBLOCKING_ERROR>();
	EXPECT_EQ( (int)(*content3), (int)eBLOCKING_ERROR::NOT_IMPLEMENTED );
	reply = po->SendMessageBlocking( m, "DEBUG", 0 );
	const  eBLOCKING_ERROR * const content4 = reply->ExtractRawPayload<eBLOCKING_ERROR>();
	EXPECT_EQ( (int)(*content4), (int)eBLOCKING_ERROR::TIMEOUT );


}


TEST_F(TestMBPostOffice, pause_resume )
{
	po->Pause();
	po->Resume();
	std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	po->Pause();
	po->Resume();
	po->Pause();
	po->Pause();
	po->Resume();

}
