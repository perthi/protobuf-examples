
/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "TestMBMessage.h"
#include <common/MBMessage.h>
#include <iostream>
#include <string>

#include <common/GComponent.h>
#include <common/MBMessagePayload.h>
#include <common/MBMessagePayloadT.h>
#include <common/MBMessageRequest.h>
#include <common/MBEnums.h>


#include <vector>
using  std::vector;


TEST_F(TestMBMessage, message_id)
{
	MBMessage *msg1 = new MBMessage();
	MBMessage *msg2 = new MBMessage();
	EXPECT_NE( msg1->GetMessageID(), msg2->GetMessageID() );
	EXPECT_NE( msg1->fMessageID, string("") );
	EXPECT_NE( msg2->fMessageID, string("") );
}


//TEST_F( TestMBMessage, extract_payload )
//{
//	MBMessageRequest m1(eMESSAGE_REQUEST::FACTORY_CONFIGDATA);
//	const eMESSAGE_REQUEST * const msg = m1.ExtractRawPayload<eMESSAGE_REQUEST>();
//	EXPECT_NE(nullptr, msg);
//	vector<KDIConfigData> cfg_dta = vector<KDIConfigData>() ;
//	MBMessageT< vector<KDIConfigData > > m2 =  MBMessageT< vector<KDIConfigData > >( cfg_dta );
//	const  vector<KDIConfigData >  * const p =  m2.ExtractRawPayload< vector<KDIConfigData > >() ;
//	EXPECT_NE(nullptr, p);
//	EXPECT_TRUE( m1.HasPayloadType<eMESSAGE_REQUEST>() ); 
//	EXPECT_TRUE( m2.HasPayloadType<  vector<KDIConfigData > >() );
//	EXPECT_FALSE( m2.HasPayloadType<eMESSAGE_REQUEST>() ); 
//	EXPECT_FALSE( m1.HasPayloadType<  vector<KDIConfigData > >() );
//	MBMessageRequestDeviceScan m3;
//	EXPECT_TRUE( m3.HasPayloadType<  eMESSAGE_REQUEST >() );
//}




