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

#include "TestLogging.h"
#include <logging/LMessageGenerator.h>
#include <logging/LMessage.h>
#include <logging/LConfig.h>
#include <logging/LPublisher.h>

#include <utilities/GTime.h>
#include <utilities/GRegexp.h>
#include <utilities/GNumbers.h>
#include <utilities/GTokenizer.h>
#include <utilities/GString.h>
#include <utilities/GFileIOHandler.h>
#include <utilities/GSystem.h>
#include <utilities/GException.h>


#include <typeinfo>

string  TestLogging::fMessage = "";
std::streambuf*    TestLogging::fOldBuf;
ostringstream TestLogging::fStrCout;


TestLogging::TestLogging() : TestBase()
{

}


TestLogging::~TestLogging()
{

}

void 
TestLogging::SetUpTestCase()
{
///	FORCE_DEBUG("setting up testcases");
}



void 
TestLogging::SetUp() 
{
	InitLogArgs();
	TestBase::SetUp();
	SET_LOGTARGET( "0000 --target-file" );
	fOldBuf = cout.rdbuf();
	cout.rdbuf( fStrCout.rdbuf() );
	fStrCout.str( "" );
}


void TestLogging::TearDown()
{
    TestBase::TearDown();
    cout.rdbuf(fOldBuf);
}


void
TestLogging::Subscriber(const   std::shared_ptr<LOGMASTER::LMessage>  msg  )
{
    fMessage = string(msg->fMsg);
}



#if defined NDEBUG && defined _WIN64
TEST_F( TestLogging, performance )
{
	int n = 5134032;

	LMessage *l = new LMessage();

	clock_t begin = clock();	
	for ( int i = 0; i < n; i++ )
	{
		/// The LMessage::Clear content is critical to optimize since it is called every time a log macro is used
		l->ClearContent();
	}
	clock_t end = clock();
	double elapsed_secs = double( (double)end - (double)begin );
	double average = 1000000*(elapsed_secs / n);
	//ASSERT_TRUE( average < 0.05 );
	printf("Average time for clear content is %4.8f micro seconds \n", average  );
	ASSERT_TRUE( average < 5 );
}
#endif


#if defined NDEBUG && defined _WIN64
TEST_F( TestLogging, performance2 )
{
	SET_LOGTARGET("0000");
//	SET_LOGFORMAT("1000111");

	clock_t begin = clock();
	int n = 10000;
	int i = 0;
	double time = 50.0; // use this value on local computer
		
	for ( i = 0; i < n; ++i )
	{
		/// A typical eror message that will pass the loglve check, and use all the facilities to generate a message
		//DRIVER_ERROR( "This is atest message, a = %d and b  %d", 1, 2 );
	}

	clock_t end = clock();
	double elapsed_secs = double( (double)end - (double)begin );
	double average = 1000*(elapsed_secs / n);

	
	if ( g_string()->Contains( g_system()->GetHostName(), "UKNW") )
	{
		time = 500.0; // Use longer time for Jenkins as Jenkins might be busy with many opperations at once.
	}

	printf("Average time for loggemacro is %.6f milli seconds, time is %.6f milli seconds\n", average, time);

	ASSERT_TRUE( average < time);
}
#endif



TEST_F(TestLogging, set_logtarget_g_logapplication )
{
		this->ScanArguments("-logtarget --target-off --target-subscriber -logformat 00000001");
		EXPECT_EQ( (int)(eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_SUBSCRIBERS),  (int)l->GetLogTarget());
		this->ScanArguments("-logtarget --target-off -logformat 00000001");
		EXPECT_EQ((int)(eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION ), (int)l->GetLogTarget());
}



TEST_F( TestLogging, set_logtarget )
{
		SET_LOGTARGET("--target-off --target-subscriber");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_SUBSCRIBERS);
		SET_LOGTARGET("--target-off --target-subscriber --target-stdout ");
		EXPECT_EQ(l->GetLogTarget(), (eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_SUBSCRIBERS | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_STDOUT));
		SET_LOGTARGET("--target-subscriber --target-stdout --target-off");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_OFF);
		SET_LOGTARGET("--target-all");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_ALL);
		SET_LOGTARGET("--target-all --target-off");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_OFF);
		SET_LOGTARGET("--target-off --target-all");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_ALL);
		SET_LOGTARGET("--target-off --target-file");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_FILE);
		SET_LOGTARGET("0000 --target-file");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_FILE);
		SET_LOGTARGET("0000 --target-gui");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_GUI);
		SET_LOGTARGET("0000 --target-stdout");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_STDOUT);
		SET_LOGTARGET("0000 --target-subscriber");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_SUBSCRIBERS);
		SET_LOGTARGET("0000 0001");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_FILE);
		SET_LOGTARGET("0000 1000");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_GUI);
		SET_LOGTARGET("0000 0010");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_STDOUT);
		SET_LOGTARGET("0000  0100");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_SUBSCRIBERS);
		SET_LOGTARGET("0000  0110");
		EXPECT_EQ(l->GetLogTarget(), (eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_STDOUT | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_SUBSCRIBERS));
		SET_LOGTARGET("0000  --target-all");
		EXPECT_EQ((int)l->GetLogTarget(), (int)(eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_ALL));
		SET_LOGTARGET("0000");
		SET_LOGTARGET("0000 1001");
		EXPECT_EQ(l->GetLogTarget(), (eMSGTARGET::TARGET_TESTING | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_GUI | eMSGTARGET::TARGET_EXCEPTION | eMSGTARGET::TARGET_FILE));
		SET_LOGTARGET("0000 1000 0100 0010 0001");
		EXPECT_EQ(l->GetLogTarget(), eMSGTARGET::TARGET_ALL);
}



TEST_F(TestLogging, level_to_string )
{
	EXPECT_EQ( "Error",       LMessageGenerator::Instance()->ToString( eMSGLEVEL::LOG_ERROR ));
	EXPECT_EQ( "Fatal",       LMessageGenerator::Instance()->ToString(eMSGLEVEL::LOG_FATAL));
	EXPECT_EQ( "Fatal|Error", LMessageGenerator::Instance()->ToString(eMSGLEVEL::LOG_ERROR | eMSGLEVEL::LOG_FATAL));
}
	



// TEST_F(TestLogging, system_to_string)
// {
// 	EXPECT_EQ("Analysis", LMessageGenerator::ToString(eMSGSYSTEM::SYS_ANALYSIS ) );
// 	EXPECT_EQ("Exeption", LMessageGenerator::ToString(eMSGSYSTEM::SYS_EX ));
// 	EXPECT_EQ("Analysis|Exeption", LMessageGenerator::ToString( eMSGSYSTEM::SYS_ANALYSIS | eMSGSYSTEM::SYS_EX) );
// }



// TEST_F(TestLogging, to_string)
// {
// 	EXPECT_EQ("<Fatal:Analysis>", LMessageGenerator::ToString(eMSGSYSTEM::SYS_ANALYSIS, eMSGLEVEL::LOG_FATAL));
// 	EXPECT_EQ("<Fatal|Error:Analysis|Exeption>", LMessageGenerator::ToString( eMSGSYSTEM::SYS_ANALYSIS | eMSGSYSTEM::SYS_EX,    eMSGLEVEL::LOG_ERROR | eMSGLEVEL::LOG_FATAL ));
// }




// TEST_F(TestLogging, levels)
// {
// 	PUSH();
// 	LConfig *c = LLogging::Instance()->GetConfig( eMSGTARGET::TARGET_STDOUT );
// 	EXPECT_TRUE(c->IsInitialized() );
// 	c->InitHash(eMSGLEVEL::LOG_WARNING );
// 	EXPECT_TRUE( LLogging::Instance()->CheckLevel(	eMSGSYSTEM::SYS_DATA,	eMSGLEVEL::LOG_WARNING, eMSGTARGET::TARGET_STDOUT ));
// 	EXPECT_FALSE(LLogging::Instance()->CheckLevel(	eMSGSYSTEM::SYS_DATA,	eMSGLEVEL::LOG_INFO, eMSGTARGET::TARGET_FILE ));
// 	EXPECT_TRUE(LLogging::Instance()->CheckLevel(   eMSGSYSTEM::SYS_DATA,   eMSGLEVEL::LOG_ERROR, eMSGTARGET::TARGET_SUBSCRIBERS ));
// //	LLogging::Instance()->SetLogLevel(				eMSGSYSTEM::SYS_DATA,	eMSGLEVEL::LOG_FATAL, GLOCATION );
// 	LLogging::Instance()->SetLogLevel("--data-fatal");

// 	SET_LOGLEVEL( "--data-fatal" );
// 	EXPECT_FALSE(LLogging::Instance()->CheckLevel( eMSGSYSTEM::SYS_DATA,   eMSGLEVEL::LOG_ERROR, eMSGTARGET::TARGET_GUI ));
// 	SET_LOGLEVEL("--driver-info");
// 	EXPECT_TRUE(LLogging::Instance()->CheckLevel(  eMSGSYSTEM::SYS_DRIVER, eMSGLEVEL::LOG_ERROR, eMSGTARGET::TARGET_STDOUT ));
// 	POP();
// }



TEST_F(TestLogging, stdoutIO)
{
	LPublisher::DisableColor();
    PUSH();
	SET_LOGLEVEL("--all-warning");
	SET_LOGFORMAT("00000001");
	//SET_LOGFORMAT("0000001", eMSGTARGET::TARGET_STDOUT);
	fStrCout.str("");
	SET_LOGTARGET("--target-stdout");
	G_ERROR("Test message with parameters: a = %d, b = %d", 1, 2);
	EXPECT_EQ(fStrCout.str(), "\tTest message with parameters: a = 1, b = 2\n");
	
	SET_LOGFORMAT("00000000");
	fStrCout.str("");
    G_INFO("Test message with parameters: a = %d, b = %d", 1, 2);
    EXPECT_EQ(fStrCout.str(), "");
	
	SET_LOGFORMAT("00000001");
	fStrCout.str("");
	G_WARNING("Test message with parameters: a = %d, b = %d", 1, 2);
    EXPECT_EQ(fStrCout.str(), "\tTest message with parameters: a = 1, b = 2\n");
    fStrCout.str("");
	SET_LOGFORMAT("01000001");
    LPublisher::EnableColor();
	POP();
}



TEST_F(TestLogging, exeptions)
{
	SET_LOGTARGET("0000 --target-file");
    EXPECT_ANY_THROW(ScanArguments("-gibberish"));
    EXPECT_ANY_THROW(ScanArguments("-loglevel -gibberish"));
    EXPECT_ANY_THROW(ScanArguments("-loglevel --gibberish"));
    EXPECT_ANY_THROW(ScanArguments("-loglevel gibberish"));
}



TEST_F(TestLogging, messageBody)
{
    SET_LOGFORMAT("00000001");
	SET_LOGTARGET("--target-off --target-file");
	SET_LOGLEVEL("--off --warning");
	EXPECT_STREQ("\tTest\n", G_ERROR("Test")->at(eMSGTARGET::TARGET_FILE)->fMsg);
	EXPECT_STREQ("", G_INFO("ignorme")->at(eMSGTARGET::TARGET_STDOUT)->fMsg);
	EXPECT_STREQ( "\tTesting integer parameters: a = 1, b = 3\n", G_ERROR( "Testing integer parameters: a = %d, b = %d", 1, 3 )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	EXPECT_STREQ( "\tTesting float parameters: a = 4.55, b = 3.333\n", G_ERROR( "Testing float parameters: a = %0.2f, b = %0.3f", 4.55, 3.333 )->at(eMSGTARGET::TARGET_FILE)->fMsg );
}



// TEST_F(TestLogging, messageType)
// {
// 	SET_LOGLEVEL("--off --warning");
//     SET_LOGFORMAT("01000000"); //We mask out only the mesage typ, all other fields ar empty
//     EXPECT_STREQ("<Fatal:General>          \t\n",  G_FATAL("doesent matter")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     EXPECT_STREQ("<Error:Data>             \t\n",     DATA_ERROR("doesnt matter")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     EXPECT_STREQ("", G_INFO("ignore, since loglevel is set to WARNING")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     EXPECT_STREQ("", G_DEBUG("ignore, since loglevel is set to WARNING")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// }



TEST_F(TestLogging, loglevels)
{
	PUSH();
	SET_LOGLEVEL("--all-warning");
	SET_LOGFORMAT( "11111111" ); //We mask out only the mesage typ, all other fields ar empty
	EXPECT_GT( string( G_FATAL( "a message" )->at( eMSGTARGET::TARGET_FILE )->fMsg ).size(), (size_t)0 );
	EXPECT_GT( string( G_ERROR( "a message" )->at( eMSGTARGET::TARGET_FILE )->fMsg ).size(), (size_t)0 );
	EXPECT_GT( string( G_WARNING( "a message" )->at( eMSGTARGET::TARGET_FILE )->fMsg ).size(), (size_t)0 );
	EXPECT_EQ( (size_t)0, string( G_INFO( "a message" )->at( eMSGTARGET::TARGET_FILE )->fMsg ).size() );
	EXPECT_EQ( (size_t)0, string( G_DEBUG( "a message" )->at( eMSGTARGET::TARGET_FILE )->fMsg ).size() );
	POP();
}



TEST_F(TestLogging, logBinary)
{
	SET_LOGFORMAT( "01000001"); //
	SET_LOGLEVEL( "--all-off" );
	// EXPECT_STREQ( "", DB_DEBUG( "This is a db DEBUG message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DB_INFO( "This is a db  INFO  message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DB_WARNING( "This is a db WARNING message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DB_ERROR( "This is a db ERROR message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DB_FATAL( "This is a db FATAL message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	
	EXPECT_STREQ( "", ALL_DEBUG( "This is a db DEBUG message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	EXPECT_STREQ( "", ALL_INFO( "This is a db INFO message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
///	EXPECT_STREQ( "", ALL_WARNING( "This is a ALL_WARNING message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", ALL_ERROR( "This is a ALL_ERROR message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", ALL_FATAL( "This is a ALL_FATAL message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	
	// EXPECT_STREQ( "", DATA_DEBUG( "This is a data DEBUG message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DATA_INFO( "This is a data INFO message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DATA_WARNING( "This is a data WARNING message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DRIVER_WARNING( "This is a data DRIVER message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );

        //	EXPECT_STREQ( "", EX_WARNING( "This is a data EXCEPTION message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DATA_ERROR( "This is a data ERROR message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DATA_FATAL( "This is a data FATAL message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );

	// Here we expect exactly a message only at loglevel SYS_DB_ALL warning, but not for higher levels such as ERROR and fatal
	SET_LOGLEVEL( "000001000000000111000000" );
    
	// EXPECT_STREQ("", DB_DEBUG("This is a db DEBUG message")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
	// EXPECT_STREQ( "", DB_INFO( "This is a db  INFO  message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "<Warning:Database_All>   \tThis is a db WARNING message\n", DB_WARNING( "This is a db WARNING message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DB_ERROR( "This is a db ERROR message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", DB_FATAL( "This is a db FATAL message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", ALL_DEBUG( "This is a db DEBUG message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "", ALL_INFO( "This is a db INFO message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	// EXPECT_STREQ( "<Warning:ALL systems>    \tThis is a ALL_WARNING message\n", ALL_WARNING( "This is a ALL_WARNING message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", ALL_ERROR( "This is a ALL_ERROR message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", ALL_FATAL( "This is a ALL_FATAL message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DATA_DEBUG( "This is a data DEBUG message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DATA_INFO( "This is a data INFO message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
	

 //	EXPECT_STREQ( "", DATA_WARNING( "This is a data WARNING message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DRIVER_WARNING( "This is a data DRIVER message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", EX_WARNING( "This is a data EXCEPTION message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DATA_ERROR( "This is a data ERROR message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
//	EXPECT_STREQ( "", DATA_FATAL( "This is a data FATAL message" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
}


TEST_F(TestLogging, fileIO)
{
	PUSH();
	SET_LOGTARGET ( "--target-file");
	SET_LOGFORMAT("00000001");
	SET_LOGFILENAME("googletest_logging_file_io.log");

	EXPECT_EQ("googletest_logging_file_io.log", l->GetLogFileName( eMSGTARGET::TARGET_FILE));
	SET_LOGLEVEL("--all-warning");
	G_ERROR("Test message");
	FileIOTest();
	EXPECT_EQ("\tTest message", FileIOTest());
	SET_LOGTARGET("--target-off"); // not really neccessary, maybe test fixture takes care of this ?
	POP();
}


TEST_F(TestLogging, timeStamp)
{
	SET_LOGTARGET( "--target-off");
	SET_LOGTARGET(" --target-stdout --target-file");
	SET_LOGFORMAT("00100000");
    SET_LOGLEVEL("--all-warning");
    EXPECT_EQ(true,  g_time()->IsValidDateString(G_FATAL("Ignore")->at(eMSGTARGET::TARGET_FILE)->fMsg ) );
	EXPECT_EQ(true,    g_time()->IsValidDateString( G_ERROR("Ignore")->at(eMSGTARGET::TARGET_FILE)->fMsg  ));
	EXPECT_EQ(true,    g_time()->IsValidDateString( G_WARNING("Ignore")->at(eMSGTARGET::TARGET_FILE)->fMsg ));
    EXPECT_EQ(false,   g_time()->IsValidDateString( G_INFO("Ignore")->at(eMSGTARGET::TARGET_FILE)->fMsg  ));
    EXPECT_EQ(false,   g_time()->IsValidDateString( G_DEBUG("Ignore")->at(eMSGTARGET::TARGET_FILE)->fMsg  ));  
}



// TEST_F(TestLogging, messageFormatNSR238)
// {
// 	EXPECT_NO_THROW (SET_LOGFORMAT( "--all-off" ));
//     EXPECT_NO_THROW(SET_LOGFORMAT("--short" ));
//     string dir, file;
//     g_tokenizer()->StripPath(string(__FILE__), dir, file);
//     string tmp = "<Fatal:Analysis>         " + file + "; [line " +  g_string()->ToString(__LINE__ + 1) + "]\t" + "Hello Dolly\n";
//     EXPECT_EQ(tmp ,    string(ANALYSIS_FATAL("Hello Dolly")->at(eMSGTARGET::TARGET_FILE)->fMsg  ) );
//     SET_LOGFORMAT("00000001");
// 	EXPECT_STREQ("\tHello Chuck\n", ANALYSIS_ERROR("Hello Chuck")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	ScanArguments("-logformat --all-off --msg-type --msg-body");
// 	EXPECT_STREQ("<Fatal:Analysis>         \tHello Dolly\n" , ANALYSIS_FATAL("Hello Dolly")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// }



/// Testing for feature request NSR-218
TEST_F(TestLogging, NSR218)
{
//	PUSH();
//	SET_LOGTARGET("111");
	EXPECT_NO_THROW( ScanArguments( "-loglevel --debug" ) );
	EXPECT_NO_THROW( ScanArguments( "-loglevel --info" ) );
	EXPECT_NO_THROW( ScanArguments( "-loglevel --warning" ) );
	EXPECT_NO_THROW( ScanArguments( "-loglevel --error" ) );
	EXPECT_NO_THROW( ScanArguments( "-loglevel --fatal" ) );
	 
	// POP();

	SET_LOGFORMAT("01000001");
    EXPECT_STREQ("",  G_ERROR("This is a test" )->at(eMSGTARGET::TARGET_FILE)->fMsg );
    EXPECT_STREQ("<Fatal:General>          \tThis is a test\n", G_FATAL("This is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
   // EXPECT_STREQ("", DRIVER_ERROR("Hello Dolly")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
   // EXPECT_STREQ("<Fatal:Driver>           \tHello Dolly\n", DRIVER_FATAL("Hello Dolly")->at(eMSGTARGET::TARGET_FILE)->fMsg );

   }



TEST_F(TestLogging, NSR219)
{
    EXPECT_NO_THROW(SET_LOGFORMAT("01111111" ) );
    EXPECT_NO_THROW(SET_LOGFORMAT("01000001") );
    EXPECT_NO_THROW(SET_LOGFORMAT("00000000") );
    EXPECT_ANY_THROW( SET_LOGFORMAT("0100001" ) );
    EXPECT_ANY_THROW(SET_LOGFORMAT("1111" ));
    EXPECT_ANY_THROW(SET_LOGFORMAT("gibberish"));
    EXPECT_ANY_THROW(SET_LOGFORMAT("0xabc" ));

}



// NSR-207 binary commands for log targets
TEST_F(TestLogging, NSR207)
{
    EXPECT_NO_THROW(SET_LOGTARGET("1111"));
    EXPECT_NO_THROW(ScanArguments("-logtarget 1111"));
    //EXPECT_NO_THROW(SET_LOGTARGET((eMSGTARGET)0x7));
    EXPECT_ANY_THROW(SET_LOGTARGET("111"));
  //  EXPECT_ANY_THROW(SET_LOGTARGET( (eMSGTARGET)0x123));

    EXPECT_NO_THROW(SET_LOGTARGET("0000"));
    fStrCout.str("");
	SET_LOGFORMAT("00000001");
    G_ERROR("Hello Dolly");
    EXPECT_EQ("", fStrCout.str());
    EXPECT_NE("\t\tHello Dolly\n", FileIOTest());
	EXPECT_EQ("", fMessage);
    l->RegisterSubscriber(Subscriber);
    EXPECT_NO_THROW(SET_LOGTARGET("1111"));    

	SET_LOGLEVEL("--all-debug");
	G_ERROR("\tHello Chuck");
    EXPECT_EQ("\t\tHello Chuck\n", fMessage) << "logfilename = " <<  	l->GetLogFileName() << endl;
	
 
 }


//	SET_LOGTARGET( "0000 --target-file" );


// /// Tests tthat the bitvis or-ing of binary commands works as expected 
// TEST_F(TestLogging, BinaryOrNSR250)
//  {
// 	  ScanArguments("-logtarget --target-off --target-stdout --target-file -logformat 01000000");
// 	  // Here we issue two arbritary commands to turn of two message s types, the firs command is debug messages from the DATA subsystem,
// 	  // The second command turns on WARNING messages from the DRIVER sub-system 
// 	  //00010000 00000010  00000100 00001000
// 	ScanArguments("-loglevel  --off  000100000000000000000010    000001000000000000001000");
//      // First we chcekc that message for ALL_SYSTEMS appears both for DEBUG and WARNING, but for  ONLY for those systems 

// 	 EXPECT_STREQ("<Warning:ALL systems>    \t\n",  ALL_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	 EXPECT_STREQ("", ALL_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg);
// 	 EXPECT_STREQ("", ALL_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg);

//      // Now we check the particular subsystems, first that we get ONLY DEBUG messages from the Data system and WARNING messages from the DRIVER system
//      EXPECT_STREQ("<Debug:Data>             \t\n",   DATA_DEBUG("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("",                   DATA_INFO("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DATA_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DATA_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DATA_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DRIVER_DEBUG("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DRIVER_INFO("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("<Warning:Driver>         \t\n", DRIVER_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DRIVER_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",                   DRIVER_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
 
//      ///lets check the orher subsystems too, just in case//
//      EXPECT_STREQ("",            ANALYSIS_DEBUG("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("",            ANALYSIS_INFO("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            ANALYSIS_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            ANALYSIS_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            ANALYSIS_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            EX_DEBUG("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            EX_INFO("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            EX_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("",            EX_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            EX_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            DB_DEBUG("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("",            DB_INFO("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            DB_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            DB_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            DB_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            G_DEBUG("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            G_INFO("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            G_WARNING("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("",            G_ERROR("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("",            G_FATAL("ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//  }
 


///  We format the message to contain only the line number using the "--line-no" switch, whe then
/// expect the message to contain excatly on number, namely the line where the message is generated.
///  We verify the line number by using the __LINE__ macro wich is placed two lines below
///  i.e we expect line to be equal to log_line + 2. This unit test verify bug NSR785 where
///  the function name was displayed instead of the line number due to an error  during the initialization
///  of the hash tables for the logging system ( See LHashMaps.cpp for details ) 
/*
TEST_F(TestLogging, linNoBugNSR785)
{
  //  LLogging::Instance()->SetLogFormat(0, GLocation(__FILE__, __LINE__, __FUNCTION__));
    SET_LOGFORMAT("--all-off    --line-no");
    G_ERROR("This is a test");
	string msg = string(LMessageGenerator::Instance()->GetLastMsg()->fMsg);
    int line = __LINE__;
    vector<string> num =  g_regexp()->ScanNumber(msg, "1,10");
    EXPECT_EQ(1, num.size());

    if (num.size() == 1)
    {
        long long int log_line = g_numbers()->ToInteger(num[0]);        
        EXPECT_EQ(line, log_line + 2);
    }
}
*/


TEST_F(TestLogging, NSR790HugeMessage)
{
    SET_LOGFORMAT("--all-off --msg-body");
    SET_LOGLEVEL("--all");
    SET_LOGTARGET("--target-off --target-file ");

    string loremipsum =  "Lorem ipsum dolor sit amet, cu brute habemus has, mei suas debitis ea.Per ex oportere prodesset, per eu tota soleat inimicus.Sint eros menandri quo eu.Cum an inani mundi aliquip, omittam liberavisse an mel, dolorum albucius aliquando nam eu.Sit id expetenda interesset, has placerat invenire eu, ut mea stet nusquam.Pri ad percipit ullamcorper.An sit lucilius delicatissimi, justo consequat ea pro. \
        No unum denique noluisse pro, mei autem nominati iracundia no.Ei eius platonem mea, tota solum detracto cum at, dicam essent et usu.An commune mediocritatem ius, ad erant volutpat rationibus usu.Mei at prima suscipit, ius illud dignissim ne, cu mel assentior democritum reprimique.Vel ex admodum eleifend abhorreant, ius purto impetus ut, detracto aliquando eos ut.Ut sed molestiae intellegat, eos omnes fastidii ex, \
        sea philosophia theophrastus ut.Ad nam omnium facilisi, tritani insolens dissentiet at per. Te vel diam nominati pertinacia, et vix omnes contentiones.Vis cu viderer debitis, sea eripuit tibique epicuri ad.Duo adhuc postea nonumes ex, te discere euripidis mei.Ad ancillae propriae deterruisset vel. \
        Pri at probo sensibus mandamus.Adipisci mandamus qui eu, et quo alia mucius option.Eirmod ancillae id mei, id meis antiopam eam, ius ex congue alienum.Eos eu sale delicata, commune principes adolescens ex his. \
        An vix suscipit voluptua referrentur, mel te tollit bonorum apeirian, et pro esse interpretaris.Vero lobortis forensibus in ius, eu vix dicat etiam consectetuer, per ea luptatum electram interpretaris.Cu sed eius salutatus.Eos meis similique disputando ex.Est quas adipisci signiferumque ea.\n";

    EXPECT_EQ("\t" + loremipsum + "\n",  G_INFO(loremipsum.c_str() )->at(eMSGTARGET::TARGET_FILE)->fMsg );
}



// TEST_F(TestLogging, NSR803MultipleLevels)
// {
//     SET_LOGTARGET("--target-off --target-file");
//     SET_LOGFORMAT("01000000");
//     SET_LOGLEVEL("--all");
// 	EXPECT_STREQ("<Error:Analysis>         \t\n", G_LOG(eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_ANALYSIS, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	EXPECT_STREQ("<Fatal|Error:Driver>     \t\n", G_LOG(eMSGLEVEL::LOG_ERROR | eMSGLEVEL::LOG_FATAL, eMSGSYSTEM::SYS_DRIVER, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     ScanArguments("-loglevel --off --db-error");
//     EXPECT_STREQ("<Error|Info:Analysis|Database_General|Database_SQL|Database_Report>\t\n", G_LOG(eMSGLEVEL::LOG_INFO | eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_ANALYSIS | eMSGSYSTEM::SYS_DB_ALL, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// }



// TEST_F(TestLogging, NSR853MultipleArguments)
// {
//     SET_LOGTARGET("--target-off --target-file");
//     SET_LOGFORMAT("01000000");
//     SET_LOGLEVEL("--all");

//     EXPECT_STREQ("<Error:Analysis>         \t\n", G_LOG( eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_ANALYSIS, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     EXPECT_STREQ("<Fatal|Error:Driver>     \t\n", G_LOG( eMSGLEVEL::LOG_ERROR | eMSGLEVEL::LOG_FATAL, eMSGSYSTEM::SYS_DRIVER, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	EXPECT_STREQ("<Warning|Info:Analysis|Driver>\t\n", G_LOG(eMSGLEVEL::LOG_INFO | eMSGLEVEL::LOG_WARNING, eMSGSYSTEM::SYS_ANALYSIS | eMSGSYSTEM::SYS_DRIVER, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     SET_LOGLEVEL("--off --db-error");
//     EXPECT_STREQ("<Error|Info:Analysis|Database_General|Database_SQL|Database_Report>\t\n", G_LOG(eMSGLEVEL::LOG_INFO | eMSGLEVEL::LOG_ERROR, eMSGSYSTEM::SYS_ANALYSIS | eMSGSYSTEM::SYS_DB_ALL, "ignore me")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// }



TEST_F(TestLogging, NSR724ForceDebug)
{
    SET_LOGLEVEL("--all");
    SET_LOGFORMAT("01000001");

    //If we use the force debug macro we shall generate a message regardless of the configuration of the logging system
    EXPECT_STREQ("<Force_Debug:General>    \tForcing the logging system to write a message\n",   FORCE_DEBUG("Forcing the logging system to write a message")->at(eMSGTARGET::TARGET_FILE)->fMsg );
}



// TEST_F(TestLogging, NSR964SetGet)
// {
//     SET_LOGLEVEL("--all-off --all-warning");
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT ));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DATA, eMSGTARGET::TARGET_STDOUT));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_EX, eMSGTARGET::TARGET_STDOUT));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DRIVER, eMSGTARGET::TARGET_STDOUT));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DB_ALL, eMSGTARGET::TARGET_STDOUT));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_GENERAL, eMSGTARGET::TARGET_STDOUT));
// //	EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_ALL, eMSGTARGET::TARGET_STDOUT));
//     SET_LOGLEVEL("--driver-off");
//     EXPECT_EQ(BIN("0000000000000000"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DRIVER, eMSGTARGET::TARGET_STDOUT));

// 	EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT));
// 	EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DATA, eMSGTARGET::TARGET_STDOUT));
// 	EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_EX, eMSGTARGET::TARGET_STDOUT));
// 	EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DB_ALL, eMSGTARGET::TARGET_STDOUT));
// 	EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_GENERAL, eMSGTARGET::TARGET_STDOUT));
// }


// TEST_F(TestLogging, NSR963ConfigurationStack)
// {  
//     SET_LOGLEVEL("--all-warning");
//     l->Push(   ); // push the current configuration onto the stack
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DRIVER, eMSGTARGET::TARGET_STDOUT));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DB_ALL, eMSGTARGET::TARGET_STDOUT));
//     SET_LOGLEVEL("--driver-off");
//     EXPECT_EQ(BIN("0000000000000000"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DRIVER, eMSGTARGET::TARGET_STDOUT));
//     EXPECT_EQ(BIN("00000111"), (int)l->GetLogLevel(eMSGSYSTEM::SYS_DB_ALL, eMSGTARGET::TARGET_STDOUT));
//  }




TEST_F(TestLogging, NSR939Subscribers)
{
    SET_LOGTARGET("--target-off");
    EXPECT_EQ(BIN("0000000000110000"), (int)l->GetLogTarget());
	SET_LOGTARGET("--target-subscriber --target-file");
    EXPECT_EQ(BIN("0000000000110101"), (int)l->GetLogTarget());
    SET_LOGTARGET("--target-off");
    EXPECT_EQ(BIN("0000000000110000"), (int)l->GetLogTarget());
    SET_LOGTARGET("--target-file");
    EXPECT_EQ(BIN("0000000000110001"), (int)l->GetLogTarget());
    SET_LOGTARGET("--target-subscriber");
    EXPECT_EQ(BIN("0000000000110101"), (int)l->GetLogTarget());
    SET_LOGTARGET("--target-stdout");
    EXPECT_EQ(BIN("0000000000110111"), (int)l->GetLogTarget());
 
    SET_LOGTARGET("--target-off --target-subscriber --target-file");
    EXPECT_EQ(BIN("0000000000110101"), (int)l->GetLogTarget());

	SET_LOGTARGET("--target-all");
    EXPECT_EQ(BIN("0000000000111111"), (int)l->GetLogTarget());
    
	SET_LOGTARGET("--target-off");
    EXPECT_EQ(BIN("0000000000110000"), (int)l->GetLogTarget());
 
    SET_LOGTARGET("0011");
    EXPECT_EQ(BIN("0000000000110011"), (int)l->GetLogTarget());
 
    SET_LOGTARGET("0111");
    EXPECT_EQ(BIN("0000000000110111"), (int)l->GetLogTarget());
 
    SET_LOGTARGET("--target-off 0101");
    EXPECT_EQ(BIN("0000000000110101"), (int)l->GetLogTarget());

}



//  TEST_F(TestLogging, NSR1121binary_commands_set_all)
//  {
//      PUSH();
// 	 SET_LOGFORMAT("00000001");
//      SET_LOGLEVEL("--all-off");
//      EXPECT_STREQ("", DB_ERROR("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", DRIVER_WARNING("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", EX_INFO("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", ANALYSIS_FATAL("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	 SET_LOGLEVEL("111111111111111111111111");
// 	 SET_LOGFORMAT("--target-file --all-off --msg-body");
//      EXPECT_STREQ("\tthis is a test1\n",  DB_ERROR( "this is a test1")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	 EXPECT_STREQ("\tthis is a test2\n",  DRIVER_WARNING( "this is a test2")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("\tthis is a test3\n",  EX_INFO(     "this is a test3")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("\tthis is a test4\n",  ANALYSIS_FATAL("this is a test4")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("\tthis is a test5\n",  ANALYSIS_ERROR("this is a test5")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("\tthis is a test6\n",  ANALYSIS_WARNING("this is a test6")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("\tthis is a test7\n",  ANALYSIS_INFO("this is a test7")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//      EXPECT_STREQ("\tthis is a test8\n",  ANALYSIS_DEBUG("this is a test8")->at(eMSGTARGET::TARGET_FILE)->fMsg );

//      POP();
//  }
 


// TEST_F(TestLogging, NSR1121)
// {
//     SET_LOGFORMAT("00000001" );
//     SET_LOGLEVEL("--all-off");
//     SET_LOGLEVEL("--ana-error");
//     EXPECT_STREQ("", G_ERROR("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     EXPECT_STREQ("\tthis is a test\n", A_ERROR("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg  );
//     EXPECT_STREQ("\tthis is a test2xx\n", A_FATAL("this is a test2xx")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//     EXPECT_STREQ("", A_WARNING("this is a test3")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// }







//  TEST_F(TestLogging, NSR1121binary_commands)
//  {
//      PUSH();
//  	 SET_LOGFORMAT("00000001");
//      SET_LOGLEVEL("--all-off");
//      EXPECT_STREQ("", G_ERROR("this is a test 123456")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      SET_LOGLEVEL("111111111111111111111111");
//      EXPECT_STREQ("\tthis is a test_a\n", G_ERROR("this is a test_a")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//  	 SET_LOGLEVEL("--all-off");
//      SET_LOGLEVEL("000001110000000000000001");  

//      EXPECT_STREQ("", DB_ERROR("\tthis is a test_b\n")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//  	 EXPECT_STREQ("", DRIVER_WARNING("this is a test_c\n")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//  	 EXPECT_STREQ("", EX_INFO("this is a test_d\n")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("\tthis is a test_e\n", A_FATAL("this is a test_e")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//  	 EXPECT_STREQ("\tthis is a test_f\n", A_ERROR("this is a test_f")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("\tthis is a test_g\n", A_WARNING("this is a test_g")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", A_INFO("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", A_DEBUG("this is a test")->at(eMSGTARGET::TARGET_FILE)->fMsg );
     
	 
// 	 SET_LOGLEVEL("000001110000000000000010");
//      EXPECT_STREQ("\tthis is a test1\n", DATA_FATAL("this is a test1")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("\tthis is a test2\n", DATA_ERROR("this is a test2")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("\tthis is a test3\n", DATA_WARNING("this is a test3")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", DB_ERROR("this is a test4")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("", DRIVER_WARNING("this is a test5")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("", EX_INFO("this is a test6")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("\tthis is a test7\n", A_FATAL("this is a test7")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("\tthis is a test8\n", A_ERROR("this is a test8")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("\tthis is a test9\n", A_WARNING("this is a test9")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("", A_INFO("this is a test10")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", A_DEBUG("this is a test11")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      SET_LOGLEVEL("000000000000000000111111");
//      EXPECT_STREQ("", DATA_FATAL("this is a test12")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", DATA_ERROR("this is a test13")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", DATA_WARNING("this is a test14")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", DB_ERROR("this is a test15")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", DRIVER_WARNING("this is a test16")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", EX_INFO("this is a test17")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", A_FATAL("this is a test18")->at(eMSGTARGET::TARGET_FILE)->fMsg );
//      EXPECT_STREQ("", A_ERROR("this is a test19")->at(eMSGTARGET::TARGET_FILE)->fMsg);
//      EXPECT_STREQ("", A_WARNING("this is a test20")->at(eMSGTARGET::TARGET_FILE)->fMsg );
// 	 POP();
//  }


