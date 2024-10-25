// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "TestKFSensor.h"
#include <configuration/KFSensor.h>



TEST_F(TestKFSensor, constructor)
{
	EXPECT_NO_THROW ( KFSensor("some id", "192.168.1.7", eSENSOR_TYPE::HUMIDITY) );   /// Invalid device ID
	EXPECT_ANY_THROW( KFSensor("some id", "192.168.1.256", eSENSOR_TYPE::HUMIDITY) ); /// invalid IP address
}


TEST_F(TestKFSensor, set_get)
{
	KFSensor s("some id", "192.168.1.13", eSENSOR_TYPE::CURRENT );
	EXPECT_EQ("some id",  s.GetSensorId() );
	EXPECT_EQ( "192.168.1.13", s.GetIPAddress() );
	EXPECT_EQ( (int)eSENSOR_TYPE::CURRENT, (int)s.GetSensorType());
	s.SetSensorId("another id");
	s.SetIPAddress("192.168.2.2");
	EXPECT_EQ("another id", s.GetSensorId());
	EXPECT_EQ("192.168.2.2", s.GetIPAddress());
	EXPECT_ANY_THROW(s.SetIPAddress("gibberish")  );
	EXPECT_ANY_THROW(s.SetIPAddress("123456"));
	EXPECT_ANY_THROW(s.SetIPAddress("192.168.1.1.1"));
	EXPECT_NO_THROW(s.SetIPAddress("192.168.1.1"));
	EXPECT_NO_THROW(s.SetIPAddress("127.0.0.1"));
}

