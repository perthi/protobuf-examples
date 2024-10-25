
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestGComponent.h"
#include <common/GComponent.h>
#include <common/GComponentDummyA.h>
#include <common/MBPayloadDummyA.h>
#include <common/MBPayloadDummyB.h>
#include <common/MBPayloadDummyC.h>
#include <common/MBMessage.h>
#include <common/MBPostOffice.h>
#include <common/GComponentTimer.h>
#include <common/MBDataTypes.h>

#include <memory>

TestGComponent::TestGComponent()
{
}


TestGComponent::~TestGComponent()
{

}

void
 TestGComponent::SetUpTestCase()
 {
	if( MBPostOffice::Instance()->GetChannelMap()->size() == 0 )
	{
		MBPostOffice::Instance()->CreateMessageChannels();
	}
 }


TEST_F( TestGComponent, is_type )
{
	KMBPayloadDummyA d_a;
//	auto d_a = std::make_shared<KMBPayloadDummyA>();
	auto d_b = std::make_shared<KMBPayloadDummyB>();
	auto d_c = std::make_shared<KMBPayloadDummyC>();

	auto p_a = std::make_shared<MBMessagePayloadT<KMBPayloadDummyA> >(d_a);
	auto m = std::make_shared<MBMessage>();
	m->SetPayload(p_a);
	auto c =  std::make_shared<GComponentDummyA>();
	EXPECT_FALSE( m->HasPayloadType<int>() );
	EXPECT_TRUE( m->HasPayloadType<KMBPayloadDummyA>() );

///	EXPECT_TRUE(  c->IsType< KMBPayloadDummyA >( p_a ) ) ;
//	EXPECT_FALSE( c->IsType< KMBPayloadDummyB >( p_a ) ) ;
}







TEST_F( TestGComponent, subscribe_unsubscribe )
{
	GComponentTimer::Instance();
	auto p = MBPostOffice::Instance(); 
	p->StartPostOffice();
	GComponentDummyA *dummy = new GComponentDummyA();
	dummy->DoSubscribe("OUT::TIMER");
	EXPECT_EQ ( 2, p->GetSubscriberCount( MBSubscriberChannel_t("OUT::TIMER") ) );
	dummy->DoUnSubscribe("");
	EXPECT_EQ ( 1, p->GetSubscriberCount( MBSubscriberChannel_t("OUT::TIMER") ) );
}

