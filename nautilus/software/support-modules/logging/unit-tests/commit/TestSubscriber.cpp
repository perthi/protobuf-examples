// -*- mode: c++ -*-

/* ****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
***************************************************************************** */

/* ****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) Per Thomas Hille <pth@embc.no>  http:///www.embc.no      ***
*** all rights reserved                                                    ***
***                                                                        ***
*** logmaster is free software: you can redistribute it and/or modify      ***
*** it under the terms of the Lesser GNU General Public License (LGPL)     ***
*** as published by the Free Software Foundation, either version 3 of the  ***
*** License, or (at your option) any later version.                        ***
***                                                                        ***
*** logmaster is distributed in the hope that it will be useful,           ***
*** but WITHOUT ANY WARRANTY; without even the implied warranty of         ***
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          ***
*** GNU General Public License for more details.                           ***
***                                                                        ***
*** You should have received a copy of the Lesser GNU General Public       ***
*** License along with logmaster in the README file in the source code     ***
*** directory. If not, see <http://www.gnu.org/licenses/>.                 ***
******************************************************************************
******************************************************************************/


#include "TestSubscriber.h"
#include <logging/LMessage.h>
#include <logging/LPublisher.h>
#include <utilities/GException.h>

std::shared_ptr<LMessage>   TestSubscriber::fMsg1 = nullptr;
std::shared_ptr<LMessage>   TestSubscriber::fMsg2 = nullptr;


void TestSubscriber::SetUp()
{
    TestLogging::SetUp();
	l->RegisterSubscriber(TestSubscriber::Subscriber1);
    l->RegisterSubscriber(TestSubscriber::Subscriber2);
}


void TestSubscriber::TearDown()
{
    TestLogging::TearDown();
	l->ClearSubscribers();
}


void 
TestSubscriber::Subscriber1( const std::shared_ptr<LMessage>  msg  )
{
//	fMsg1 = const_cast<  std::shared_ptr<LMessage> >(msg);
	fMsg1 = msg;
}


void 
TestSubscriber::Subscriber2( const  std::shared_ptr<LMessage> msg  )
{
//	fMsg2 = const_cast<  LMessage *>(msg);
	fMsg2 = msg;
}



TEST_F(TestSubscriber, LogFilter)
{
	SET_LOGTARGET("--target-subscriber");
    SET_LOGFORMAT("00000001");
    ALARM_FATAL("a fatal QA message");
    //DB_ERROR("a DB Error message");
}



TEST_F(TestSubscriber, functionRegistration)
{
   SET_LOGTARGET("--target-subscriber");
   SET_LOGFORMAT("00000001");
   G_ERROR("Hello Dolly, 12345");
   EXPECT_STREQ( fMsg1->fMsgBody, "Hello Dolly, 12345");
   EXPECT_STREQ( fMsg2->fMsgBody, "Hello Dolly, 12345");
   SET_LOGFORMAT("01000001");
   G_ERROR("Hello Chuck, 12345");
   EXPECT_STREQ(fMsg1->fMsg, "<Error:General>          \tHello Chuck, 12345\n");
   EXPECT_STREQ(fMsg2->fMsg, "<Error:General>          \tHello Chuck, 12345\n");
}




/// Here we want check that we can sete the log targets correctly. So that if we specify just an 
/// Subscriber, then the message opnly ends up there etc, and not to the logfile or standard output.
/// We also want to chet that we can set any other combiantions of log targets.
TEST_F(TestSubscriber, setTargetTest )
{
	LPublisher::DisableColor();
    PUSH();
	fStrCout.str( "" );
    SET_LOGFORMAT("01000001");
	SET_LOGLEVEL("--all-warning");
    
	SET_LOGTARGET("--target-off");
    SET_LOGTARGET( "--target-subscriber");   

	G_WARNING("\tThe answer to the UNivers is NOT %d but %d", 43, 42);
    EXPECT_STREQ(fMsg1->fMsg, "<Warning:General>        \t\tThe answer to the UNivers is NOT 43 but 42\n");
    EXPECT_STREQ(fMsg2->fMsg, "<Warning:General>        \t\tThe answer to the UNivers is NOT 43 but 42\n");

	EXPECT_EQ(fStrCout.str(), "");
	
//	SET_LOGTARGET( eMSGTARGET::TARGET_SUBSCRIBERS | eMSGTARGET::TARGET_STDOUT  );
	SET_LOGTARGET( "1111"  );
    G_WARNING("Dunbars Number is between %d and %d", 100, 250);
    EXPECT_STREQ( fMsg2->fMsg, "<Warning:General>        \tDunbars Number is between 100 and 250\n");
    EXPECT_EQ( fStrCout.str(),  string("<Warning:General>        \tDunbars Number is between 100 and 250\n") );
    EXPECT_NE( FileIOTest(),   "<Warning:General>\t\tDunbars Number is between 100 and 250");
    POP();
	LPublisher::EnableColor();
}



TEST_F(TestSubscriber, setTargetFileTest)
{
	PUSH();
	SET_LOGFORMAT("01000001");
	SET_LOGTARGET( "--target-off" );
    SET_LOGTARGET( "--target-file" ) ;
	SET_LOGLEVEL("--all-warning");

    G_WARNING("Dunbars Number is between %d and %d", 50, 200);
	EXPECT_EQ(FileIOTest(), string("<Warning:General>        \tDunbars Number is between 50 and 200") );
	EXPECT_STREQ(fMsg1->fMsg, "");
	EXPECT_STREQ(fMsg2->fMsg, "");
	EXPECT_EQ(fStrCout.str(), "");
	POP();
}



TEST_F(TestSubscriber, cmdLine  )
{  
	this->InitLogArgs();
	LPublisher::DisableColor();

	try
	{
		fStrCout.str("");
		this->ScanArguments("-logtarget    --target-off    --target-subscriber  -logformat 00000001");
		
		SET_LOGLEVEL("--all-warning");
		G_WARNING("Hello Chuck Norris");
		EXPECT_STREQ(fMsg1->fMsgBody, "Hello Chuck Norris");
		EXPECT_STREQ(fMsg2->fMsgBody, "Hello Chuck Norris");
		EXPECT_EQ(fStrCout.str(), "");

		this->ScanArguments("-logtarget --target-stdout --target-subscriber");
		G_ERROR("Hello Dolly");
		EXPECT_STREQ(fMsg1->fMsgBody, "Hello Dolly");
		EXPECT_EQ(fStrCout.str(), "\tHello Dolly\n");

		fStrCout.str("");
		this->ScanArguments("-logtarget 0000 --target-subscriber");

		fMsg1->fMsgBody[0] = 0;
		fMsg2->fMsgBody[0] = 0;
		this->ScanArguments("-logtarget  --target-subscriber");
		G_ERROR("Hello Dolly");
		EXPECT_STREQ(fMsg1->fMsgBody, "Hello Dolly");
		EXPECT_STREQ(fMsg2->fMsgBody, "Hello Dolly");
		
		EXPECT_EQ("", fStrCout.str());
		fStrCout.str("");

		SET_LOGTARGET("1111");
		SET_LOGFORMAT("00000001");
		fStrCout.str("");

		G_ERROR("Hello Chuck");
		EXPECT_STREQ("Hello Chuck", fMsg1->fMsgBody);
		EXPECT_STREQ("Hello Chuck", fMsg2->fMsgBody);
		EXPECT_EQ("\tHello Chuck\n", fStrCout.str());

		fStrCout.str("");
		SET_LOGTARGET("0000 --target-subscriber");

		G_ERROR("Hello Dolly");
		EXPECT_STREQ("Hello Dolly", fMsg1->fMsgBody);
		EXPECT_STREQ("Hello Dolly", fMsg2->fMsgBody );
		EXPECT_EQ("", fStrCout.str());

		fStrCout.str("");
		SET_LOGTARGET("0110");
		G_ERROR("Hello Donald");
		EXPECT_STREQ("Hello Donald", fMsg1->fMsgBody);
		EXPECT_STREQ("Hello Donald", fMsg2->fMsgBody);
		EXPECT_EQ("\tHello Donald\n", fStrCout.str());

		fStrCout.str("");
		SET_LOGTARGET("0000");
		this->ScanArguments("-logtarget 1000 --target-subscriber");
		G_ERROR("Hello PTH");
		EXPECT_STREQ("Hello PTH", fMsg1->fMsgBody);
		EXPECT_STREQ("Hello PTH", fMsg2->fMsgBody);
		EXPECT_EQ("", fStrCout.str());
	}
	catch (GException & e)
	{
		cerr << e.what() << endl;
		throw(e);
	}
	
	LPublisher::EnableColor();
}


