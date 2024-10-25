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


#include "TestLConversion.h"

#include <logging/LEnums.h>
#include <logging/LConversion.h>
#include <logging/LHashMaps.h>

using namespace  LOGMASTER;

TestLConversion::TestLConversion()
{

}


TestLConversion::~TestLConversion()
{

}



// #ifdef _WIN32
// TEST_F( TestLConversion, SplitByTarget )
// {
// 	string s = "--target-stdout --all-off --db-debug";
// 	auto m = LConversion::SplitByTarget(s);
// 	ASSERT_EQ( 1, m.size() );
// 	auto it = m.find(eMSGTARGET::TARGET_STDOUT);
// 	EXPECT_NE( it, m.end() );
// 	EXPECT_EQ(  eMSGTARGET::TARGET_STDOUT,   it->first  );
// 	EXPECT_EQ(" --all-off --db-debug", it->second );
// 	s   =   "--target-stdout --all-off --db-debug --target-file --fsm-fatal  --target-gui --db-error --fsm-info --target-subscriber --all-info";
// 	m   =    LConversion::SplitByTarget(s);
// 	ASSERT_EQ( 4, m.size() );
// 	auto it_m = m.begin();
// 	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT, it_m->first );
// 	EXPECT_EQ(" --all-off --db-debug", it_m->second );

// 	it_m++;
// 	EXPECT_EQ(  eMSGTARGET::TARGET_FILE,   it_m->first  );
// 	EXPECT_EQ(" --fsm-fatal", it_m->second );

// 	it_m++;
// 	EXPECT_EQ(  eMSGTARGET::TARGET_GUI,   it_m->first  );
// 	EXPECT_EQ(" --db-error --fsm-info", it_m->second );

// 	it_m++;
// 	EXPECT_EQ(  eMSGTARGET::TARGET_SUBSCRIBERS,   it_m->first  );
// 	EXPECT_EQ(" --all-info", it_m->second );

// 	m = LConversion::SplitByTarget("--target-gui --target-gui --target-file --target-file");

// 	EXPECT_EQ(0, m.size() );

// 	s =    "--all-off --db-debug --fsm-fatal --db-error --fsm-info --all-info";
// 	m = LConversion::SplitByTarget(s);

// 	ASSERT_EQ(1, m.size() );

// 	it_m = m.begin();

// 	EXPECT_EQ( eMSGTARGET::TARGET_ALL, it_m->first );
// 	EXPECT_EQ("--all-off --db-debug --fsm-fatal --db-error --fsm-info --all-info", it_m->second  );

// //	EXPECT_EQ()
// }
// #endif


TEST_F( TestLConversion, HexString2Target )
{
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,          LConversion::Instance()->HexString2Target("0x0")  );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,         LConversion::Instance()->HexString2Target( "0x1" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,       LConversion::Instance()->HexString2Target( "0x2" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS,  LConversion::Instance()->HexString2Target( "0x4" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,          LConversion::Instance()->HexString2Target( "0x8" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_ALL,          LConversion::Instance()->HexString2Target( "0x3f" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,          LConversion::Instance()->HexString2Target("0x00")  );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,         LConversion::Instance()->HexString2Target( "0x01" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,       LConversion::Instance()->HexString2Target( "0x002" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS,  LConversion::Instance()->HexString2Target( "0x0004" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,          LConversion::Instance()->HexString2Target( "0x08" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_ALL,          LConversion::Instance()->HexString2Target( "0x00003f" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,          LConversion::Instance()->HexString2Target( "gibberish")  );
	EXPECT_NE( eMSGTARGET::TARGET_FILE,         LConversion::Instance()->HexString2Target( "gibberish" ) );
	EXPECT_NE( eMSGTARGET::TARGET_STDOUT,       LConversion::Instance()->HexString2Target( "gibberish" ) );
	EXPECT_NE( eMSGTARGET::TARGET_SUBSCRIBERS,  LConversion::Instance()->HexString2Target( "gibberish" ) );
	EXPECT_NE( eMSGTARGET::TARGET_GUI,          LConversion::Instance()->HexString2Target( "gibberish" ) );
	EXPECT_NE( eMSGTARGET::TARGET_ALL,          LConversion::Instance()->HexString2Target( "gibberish" ) );
}



TEST_F( TestLConversion, HexString2Format )
{
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,		LConversion::Instance()->HexString2Format("0x00") );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_TYPE,		LConversion::Instance()->HexString2Format("0x40") );
	EXPECT_EQ( eMSGFORMAT::TIME_STAMP,			LConversion::Instance()->HexString2Format("0x20") );
	EXPECT_EQ( eMSGFORMAT::FILE_PATH,			LConversion::Instance()->HexString2Format("0x10") );
	EXPECT_EQ( eMSGFORMAT::FILE_NAME,			LConversion::Instance()->HexString2Format("0x08") );
	EXPECT_EQ( eMSGFORMAT::FUNCTION_NAME,		LConversion::Instance()->HexString2Format("0x04") );
	EXPECT_EQ( eMSGFORMAT::LINE_NO,				LConversion::Instance()->HexString2Format("0x02") );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY,		LConversion::Instance()->HexString2Format("0x01") );
	EXPECT_EQ( eMSGFORMAT::PREFIX_OFF,			LConversion::Instance()->HexString2Format("0x01") );
	EXPECT_EQ( eMSGFORMAT::SHORT_MSG,			LConversion::Instance()->HexString2Format("0x4b") );
	EXPECT_EQ( eMSGFORMAT::PREFIX_ALL,			LConversion::Instance()->HexString2Format("0xff") );
	EXPECT_EQ( eMSGFORMAT::SHORT_MSG,			LConversion::Instance()->HexString2Format("0x4B") );
	//EXPECT_EQ( eMSGFORMAT::PREFIX_ALL,			LConversion::HexString2Format("0x7F") );

}



TEST_F(TestLConversion,  String2Format )
{
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,   LConversion::Instance()->String2Format( "00000000" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_TYPE,     LConversion::Instance()->String2Format( "01000000" ) );
	EXPECT_EQ( eMSGFORMAT::TIME_STAMP,       LConversion::Instance()->String2Format( "00100000" ) );
	EXPECT_EQ( eMSGFORMAT::FILE_PATH,        LConversion::Instance()->String2Format( "00010000" ) );
	EXPECT_EQ( eMSGFORMAT::FILE_NAME,        LConversion::Instance()->String2Format( "00001000" ) );
	EXPECT_EQ( eMSGFORMAT::FUNCTION_NAME,    LConversion::Instance()->String2Format( "00000100" ) );
	EXPECT_EQ( eMSGFORMAT::LINE_NO,          LConversion::Instance()->String2Format( "00000010" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY,     LConversion::Instance()->String2Format( "00000001" ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_OFF,       LConversion::Instance()->String2Format( "00000001" ) );
	EXPECT_EQ( eMSGFORMAT::SHORT_MSG,        LConversion::Instance()->String2Format( "01001011" ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_ALL,       LConversion::Instance()->String2Format( "11111111" ) );

	EXPECT_EQ( (eMSGFORMAT::MESSAGE_TYPE | eMSGFORMAT::FILE_NAME), LConversion::Instance()->String2Format( "01001000" ) );

	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,   LConversion::Instance()->String2Format( "--all-off" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_TYPE,     LConversion::Instance()->String2Format( "--msg-type" ) );
	EXPECT_EQ( eMSGFORMAT::TIME_STAMP,       LConversion::Instance()->String2Format( "--time-stamp" ) );
	EXPECT_EQ( eMSGFORMAT::FILE_PATH,        LConversion::Instance()->String2Format( "--file-path" ) );
	EXPECT_EQ( eMSGFORMAT::FILE_NAME,        LConversion::Instance()->String2Format( "--file-name" ) );
	EXPECT_EQ( eMSGFORMAT::FUNCTION_NAME,    LConversion::Instance()->String2Format( "--func-name" ) );
	EXPECT_EQ( eMSGFORMAT::LINE_NO,          LConversion::Instance()->String2Format( "--line-no" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY,     LConversion::Instance()->String2Format( "--prefix-none" ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_OFF,       LConversion::Instance()->String2Format( "--msg-body" ) );
	EXPECT_EQ( eMSGFORMAT::SHORT_MSG,        LConversion::Instance()->String2Format( "--short" ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_ALL,       LConversion::Instance()->String2Format( "--prefix-all" ) );
}



TEST_F(TestLConversion,  String2Target )
{
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,         LConversion::Instance()->String2Target( "--target-off" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS, LConversion::Instance()->String2Target( "--target-subscriber" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,        LConversion::Instance()->String2Target( "--target-file" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,      LConversion::Instance()->String2Target( "--target-stdout" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,         LConversion::Instance()->String2Target( "--target-gui" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_ALL,         LConversion::Instance()->String2Target( "--target-all" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,         LConversion::Instance()->String2Target( "0000" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS, LConversion::Instance()->String2Target( "0100" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,        LConversion::Instance()->String2Target( "0001" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,      LConversion::Instance()->String2Target( "0010" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,         LConversion::Instance()->String2Target( "1000" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,         LConversion::Instance()->String2Target( "0x0" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS, LConversion::Instance()->String2Target( "0x4" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,        LConversion::Instance()->String2Target( "0x1" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,      LConversion::Instance()->String2Target( "0x2" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,         LConversion::Instance()->String2Target( "0x8" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_ALL,         LConversion::Instance()->String2Target( "0x3f" ) );
}



// TEST_F(TestLConversion,  String2Level )
// {
// 	EXPECT_EQ( eMSGLEVEL::LOG_FORCE_DEBUG, LConversion::String2Level( "001000000000000000000000" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_DEBUG,       LConversion::String2Level( "000100000000000000000001" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_INFO,        LConversion::String2Level( "000010000000000000000010" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_WARNING,     LConversion::String2Level( "000001000000000000000100" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_ERROR,       LConversion::String2Level( "000000100000000000001000" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_FATAL,       LConversion::String2Level( "000000010000000000010000" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_OFF,         LConversion::String2Level( "000000000000000000100000" ) );
// 	EXPECT_EQ( eMSGLEVEL::LOG_ALL,         LConversion::String2Level( "111111110000000001000000" ) );


	
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_ERROR ),		(int)LConversion::String2Level( "--ana-error" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_WARNING ),	(int)LConversion::String2Level( "--data-warning" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_DEBUG ),     (int)LConversion::String2Level( "--ex-debug" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_ERROR ),		(int)LConversion::String2Level( "--driver-error" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_FATAL ),     (int)LConversion::String2Level( "--user-fatal" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_INFO ),      (int)LConversion::String2Level( "--fsm-info" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_WARNING ),   (int)LConversion::String2Level( "--db-gen-warning" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_WARNING ),   (int)LConversion::String2Level( "--db-sql-warning" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_INFO ),		(int)LConversion::String2Level( "--db-report-info" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_INFO ),		(int)LConversion::String2Level( "--db-info" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_INFO ),		(int)LConversion::String2Level( "--db-gen-info" ) );
// 	EXPECT_EQ( PAD( eMSGLEVEL::LOG_ERROR ),     (int)LConversion::String2Level( "--all-error" ) );	
// }



// TEST_F(TestLConversion,  String2System )
// {
// 	EXPECT_EQ( eMSGSYSTEM::SYS_NONE,      LConversion::String2System( "000000000000000000000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::String2System( "000000000000000000000100" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::String2System( "000000000000000000010000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::String2System( "000000000000000000100000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::String2System( "000000000000001000000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::String2System( "000000001111111111111111" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::String2System( "000000110000000000000100" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::String2System( "000001100000000000010000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::String2System( "001000000000000000100000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::String2System( "000000010000001000000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::String2System( "000100001111111111111111" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_NONE,      LConversion::String2System( "0x000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::String2System( "0x000004" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::String2System( "0x000010" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::String2System( "0x000020" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::String2System( "0x000200" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::String2System( "0x00ffff" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_NONE,      LConversion::String2System( "0x0f0000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::String2System( "0x010004" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::String2System( "0xe00010" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::String2System( "0xdc0020" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::String2System( "0x0f0200" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::String2System( "0xffffff" ) );	
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::String2System( "--ex-debug" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::String2System( "--user-fatal" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::String2System( "--fsm-info" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::String2System( "--all-error" ) );	
// }



// TEST_F( TestLConversion, BinaryString2System )
// {
// 	EXPECT_EQ( eMSGSYSTEM::SYS_NONE,      LConversion::BinaryString2System( "000000000000000000000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::BinaryString2System( "000000000000000000000100" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::BinaryString2System( "000000000000000000010000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::BinaryString2System( "000000000000000000100000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::BinaryString2System( "000000000000001000000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::BinaryString2System( "000000001111111111111111" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::BinaryString2System( "000000110000000000000100" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::BinaryString2System( "000001100000000000010000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::BinaryString2System( "001000000000000000100000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::BinaryString2System( "000000010000001000000000" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::BinaryString2System( "000100001111111111111111" ) );
	
// 	// eMSGSYSTEM combo = eMSGSYSTEM::SYS_DATA | eMSGSYSTEM::SYS_DRIVER | eMSGSYSTEM::SYS_DB_GEN;
// 	// EXPECT_EQ( combo, LConversion::BinaryString2System(  "000000000000000001001010" ) );
//     // EXPECT_ANY_THROW(  LConversion::BinaryString2System( "0000000000000000000000000" ));
// 	// EXPECT_ANY_THROW(  LConversion::BinaryString2System( "0000000000000000000000002" ));
// 	// EXPECT_ANY_THROW(  LConversion::BinaryString2System( "111" ));
// 	// EXPECT_ANY_THROW(  LConversion::BinaryString2System( "0x5" ));
	
// }



// TEST_F( TestLConversion, HexString2System )
// {
// 	EXPECT_EQ( eMSGSYSTEM::SYS_NONE,      LConversion::HexString2System( "0x000000" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_ANALYSIS,  LConversion::HexString2System( "0x000001" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DATA,      LConversion::HexString2System( "0x000002" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::HexString2System( "0x000004" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DRIVER,    LConversion::HexString2System( "0x000008" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::HexString2System( "0x000010" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::HexString2System( "0x000020" ) );
	
	
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_GEN,    LConversion::HexString2System( "0x000040" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_SQL,    LConversion::HexString2System( "0x000080" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_REPORT, LConversion::HexString2System( "0x000100" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_ALL,    LConversion::HexString2System( "0x0001c0" ) );
	

// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::HexString2System( "0x000200" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::HexString2System( "0x00ffff" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_NONE,      LConversion::HexString2System( "0x0f0000" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_ANALYSIS,  LConversion::HexString2System( "0x000001" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DATA,      LConversion::HexString2System( "0xc00002" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_EX,        LConversion::HexString2System( "0x010004" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DRIVER,    LConversion::HexString2System( "0xf00008" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_USER,      LConversion::HexString2System( "0xe00010" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,       LConversion::HexString2System( "0xdc0020" ) );
	
	
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_GEN,    LConversion::HexString2System( "0x0a0040" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_SQL,    LConversion::HexString2System( "0xa00080" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_REPORT, LConversion::HexString2System( "0x000100" ) );
// //	EXPECT_EQ( eMSGSYSTEM::SYS_DB_ALL,    LConversion::HexString2System( "0x1001c0" ) );
	

// 	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,   LConversion::HexString2System( "0x0f0200" ) );
// 	EXPECT_EQ( eMSGSYSTEM::SYS_ALL,       LConversion::HexString2System( "0xffffff" ) );											  
// }



TEST_F( TestLConversion, BinaryString2Level )
{																   
	EXPECT_EQ( eMSGLEVEL::LOG_FORCE_DEBUG, LConversion::Instance()->BinaryString2Level( "001000000000000000000000" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_DEBUG,       LConversion::Instance()->BinaryString2Level( "000100000000000000000001" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_INFO,        LConversion::Instance()->BinaryString2Level( "000010000000000000000010" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_WARNING,     LConversion::Instance()->BinaryString2Level( "000001000000000000000100" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_ERROR,       LConversion::Instance()->BinaryString2Level( "000000100000000000001000" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_FATAL,       LConversion::Instance()->BinaryString2Level( "000000010000000000010000" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_OFF,         LConversion::Instance()->BinaryString2Level( "000000000000000000100000" ) );
	EXPECT_EQ( eMSGLEVEL::LOG_ALL,         LConversion::Instance()->BinaryString2Level( "111111110000000001000000" ) );
	eMSGLEVEL combo = eMSGLEVEL::LOG_DEBUG | eMSGLEVEL::LOG_WARNING;
	EXPECT_EQ( combo,      LConversion::Instance()->BinaryString2Level( "000101000000000000000001" ) );
}



TEST_F( TestLConversion, BinaryString2Target )
{
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,          LConversion::Instance()->BinaryString2Target("0000")  );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,         LConversion::Instance()->BinaryString2Target("0001")  );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,       LConversion::Instance()->BinaryString2Target("0010" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS,  LConversion::Instance()->BinaryString2Target("0100")  );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,          LConversion::Instance()->BinaryString2Target("1000" ) );
//	EXPECT_EQ( eMSGTARGET::TARGET_ALL,          LConversion::BinaryString2Target("1111")  );
	eMSGTARGET combo =  eMSGTARGET::TARGET_FILE  | eMSGTARGET::TARGET_SUBSCRIBERS;
	EXPECT_EQ( combo,  LConversion::Instance()->BinaryString2Target("0101")  );
}



TEST_F( TestLConversion, BinaryString2Format )
{
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,   LConversion::Instance()->BinaryString2Format( "00000000" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_TYPE,     LConversion::Instance()->BinaryString2Format( "01000000" ) );
	EXPECT_EQ( eMSGFORMAT::FILE_PATH,        LConversion::Instance()->BinaryString2Format( "00010000" ) );
	EXPECT_EQ( eMSGFORMAT::TIME_STAMP,       LConversion::Instance()->BinaryString2Format( "00100000" ) );
	EXPECT_EQ( eMSGFORMAT::FILE_NAME,        LConversion::Instance()->BinaryString2Format( "00001000" ) );
	EXPECT_EQ( eMSGFORMAT::FUNCTION_NAME,    LConversion::Instance()->BinaryString2Format( "00000100" ) );
	EXPECT_EQ( eMSGFORMAT::LINE_NO,          LConversion::Instance()->BinaryString2Format( "00000010" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY,     LConversion::Instance()->BinaryString2Format( "00000001" ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_OFF,       LConversion::Instance()->BinaryString2Format( "00000001" ) );
	EXPECT_EQ( eMSGFORMAT::SHORT_MSG,        LConversion::Instance()->BinaryString2Format( "01001011" ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_ALL,       LConversion::Instance()->BinaryString2Format( "11111111" ) );
}



TEST_F( TestLConversion, Hash2System )
{
//	EXPECT_EQ( eMSGSYSTEM::SYS_ANALYSIS,     LConversion::Instance()->Hash2System( "--ana-fatal" ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_DATA,         LConversion::Instance()->Hash2System( "--data-warning" ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_EX,           LConversion::Instance()->Hash2System( "--ex-debug" ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_DRIVER,       LConversion::Instance()->Hash2System( "--driver-all"  ) );
	EXPECT_EQ( eMSGSYSTEM::SYS_USER,         LConversion::Instance()->Hash2System( "--user-off"  ) );
	EXPECT_EQ( eMSGSYSTEM::SYS_FSM,          LConversion::Instance()->Hash2System( "--fsm-error"  ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_DB_GEN,       LConversion::Instance()->Hash2System( "--db-gen-warning"  ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_DB_SQL,       LConversion::Instance()->Hash2System( "--db-sql-fatal"  ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_DB_REPORT,    LConversion::Instance()->Hash2System( "--db-report-info"  ) );
//	EXPECT_EQ( eMSGSYSTEM::SYS_DB_ALL,       LConversion::Instance()->Hash2System( "--db-debug"  ) );
	EXPECT_EQ( eMSGSYSTEM::SYS_GENERAL,      LConversion::Instance()->Hash2System( "--gen-fatal"  ) );
}



// TEST_F( TestLConversion, Hash2Level )
// {
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_FATAL),      (int)LConversion::Hash2Level( "--ana-fatal"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_WARNING),    (int)LConversion::Hash2Level( "--data-warning"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_DEBUG),      (int)LConversion::Hash2Level( "--ex-debug"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_ALL),        (int)LConversion::Hash2Level( "--driver-all"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_OFF),        (int)LConversion::Hash2Level( "--user-off"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_ERROR),      (int)LConversion::Hash2Level( "--fsm-error"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_WARNING),    (int)LConversion::Hash2Level( "--db-warning"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_FATAL),      (int)LConversion::Hash2Level( "--db-sql-fatal"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_INFO),       (int)LConversion::Hash2Level( "--db-report-info"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_DEBUG),      (int)LConversion::Hash2Level( "--db-debug"  ) );
// 	EXPECT_EQ( PAD(eMSGLEVEL::LOG_FATAL),      (int)LConversion::Hash2Level( "--gen-fatal"  ) );
// }


TEST_F( TestLConversion, Hash2Target )
{
	EXPECT_EQ( eMSGTARGET::TARGET_OFF,          LConversion::Instance()->Hash2Target( "--target-off" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_SUBSCRIBERS,  LConversion::Instance()->Hash2Target( "--target-subscriber" ) );
	EXPECT_EQ( eMSGTARGET::TARGET_FILE,         LConversion::Instance()->Hash2Target( "--target-file"  ) );
	EXPECT_EQ( eMSGTARGET::TARGET_STDOUT,       LConversion::Instance()->Hash2Target( "--target-stdout"  ) );
	EXPECT_EQ( eMSGTARGET::TARGET_GUI,          LConversion::Instance()->Hash2Target( "--target-gui"  ) );
	EXPECT_EQ( eMSGTARGET::TARGET_ALL,          LConversion::Instance()->Hash2Target( "--target-all"  ) );
}



TEST_F( TestLConversion, Hash2Format )
{
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,    LConversion::Instance()->Hash2Format( "--all-off" ) );
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,    LConversion::Instance()->Hash2Format( "--off" ) );
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF,    LConversion::Instance()->Hash2Format( "--none" ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_TYPE,      LConversion::Instance()->Hash2Format( "--msg-type" ) );
	EXPECT_EQ( eMSGFORMAT::TIME_STAMP,        LConversion::Instance()->Hash2Format( "--time-stamp"  ) );
	EXPECT_EQ( eMSGFORMAT::FILE_PATH,         LConversion::Instance()->Hash2Format( "--file-path"  ) );
	EXPECT_EQ( eMSGFORMAT::FILE_NAME,         LConversion::Instance()->Hash2Format( "--file-name"  ) );
	EXPECT_EQ( eMSGFORMAT::FUNCTION_NAME,     LConversion::Instance()->Hash2Format( "--func-name"  ) );
	EXPECT_EQ( eMSGFORMAT::LINE_NO,           LConversion::Instance()->Hash2Format( "--line-no"  ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_OFF,        LConversion::Instance()->Hash2Format( "--prefix-none"  ) );
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY,      LConversion::Instance()->Hash2Format( "--prefix-none"  ) );
	EXPECT_EQ( eMSGFORMAT::SHORT_MSG,         LConversion::Instance()->Hash2Format( "--short"  ) );
	EXPECT_EQ( eMSGFORMAT::PREFIX_ALL,        LConversion::Instance()->Hash2Format( "--prefix-all"  ) );
}
