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


#include "TestLConfig.h"

#include <logging/LHashMaps.h>
#include <utilities/GUtilities.h>
#include <utilities/GNumbers.h>

#include <bitset>

void 
TestLConfig::SetUp()
{
	fConfig = new LConfig();
	s_v	=	LHashMaps::Instance()->GetSystemEnums();
	l_v	=	LHashMaps::Instance()->GetLevelEnums();
	t_v =   LHashMaps::Instance()->GetTargetEnums();
	g_utilities()->FilterOut( s_v, { eMSGSYSTEM::SYS_NONE, eMSGSYSTEM::SYS_ALL, eMSGSYSTEM::SYS_EX, eMSGSYSTEM::SYS_ALARM } );
	g_utilities()->FilterOut( l_v, { eMSGLEVEL::LOG_FORCE_DEBUG  } );
	g_utilities()->FilterOut( t_v, { eMSGTARGET::TARGET_OFF, eMSGTARGET::TARGET_ALL } );
//	g_utilities()->FilterOut( t_v, { eMSGTARGET::TARGET_OFF } );
}


void 
TestLConfig::TearDown()
{
	//delete fConfig;
}



/*
TEST_F( TestLConfig, binary_string )
{
	fConfig->SetLogLevel("--all-off" );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_GEN ),  eMSGLEVEL::LOG_OFF  );
	
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_SQL ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_REPORT ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_ALL ), eMSGLEVEL::LOG_OFF );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_REPORT ), eMSGLEVEL::LOG_OFF );

	fConfig->SetLogLevel( "--db-sql-warning" );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_GEN ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_SQL ),  PAD(eMSGLEVEL::LOG_WARNING)  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_REPORT ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_ALL ), eMSGLEVEL::LOG_OFF );

	fConfig->SetLogLevel("--all-off" );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_GEN ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_SQL ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_REPORT ),  eMSGLEVEL::LOG_OFF  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_ALL ),  eMSGLEVEL::LOG_OFF );


	
	fConfig->SetLogLevel("--all-off");
	fConfig->SetLogLevel( "--db-sql-warning" );
	fConfig->SetLogLevel( "--db-report-error" );
	fConfig->SetLogLevel( "--db-gen-info"  );
	
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_GEN ),  PAD(eMSGLEVEL::LOG_INFO)  );
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_SQL ),  PAD(eMSGLEVEL::LOG_WARNING)  );
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_REPORT ),  PAD(eMSGLEVEL::LOG_ERROR)  );
	EXPECT_EQ( fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_ALL ),  eMSGLEVEL::LOG_OFF  );
	
	
	fConfig->SetLogLevel("--all-off");
	fConfig->SetLogLevel("--db-warning");
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_GEN ),  PAD(eMSGLEVEL::LOG_WARNING)  );
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_SQL ),  PAD(eMSGLEVEL::LOG_WARNING)  );
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_REPORT ),  PAD(eMSGLEVEL::LOG_WARNING)  );
	EXPECT_EQ( (int64_t)fConfig->GetLogLevel( eMSGSYSTEM::SYS_DB_ALL ),  PAD(eMSGLEVEL::LOG_WARNING)  );
	
	}
*/


TEST_F( TestLConfig, target_all )
{
	LLogging *log = LLogging::Instance();
	//log->SetLogLevel( eMSGLEVEL::LOG_OFF, GLOCATION );

	log->SetLogLevel( "--off");

	for ( size_t t = 0; t < t_v.size(); t++ )
	{
		for ( size_t s = 0; s < s_v.size(); s++ )
		{
			for ( size_t l = 0; l < l_v.size(); l++ )
			{
				EXPECT_FALSE( log->CheckLevel( s_v[s], l_v[l], t_v[t] ) );
			}
		}
	}
}


// TEST_F(TestLConfig, loglevels)
// {
//     vector<string> levels = LHashMaps::GetLogLevelTags();
//     vector<string> prefix = { "all",  "ana", "analysis", "data", "ex", "driver", "gen", "user", "fsm", "db", "msg", "te" };
//     vector<string> postfix = { "off", "fatal", "error", "warning", "info", "debug", "all" };
// 	LConfig *c = new LConfig();

// 	for ( size_t i = 0; i < prefix.size(); i++)
//     {
//         for (size_t j = 0; j < postfix.size(); j++)
//         {
//             string tag = "--" + prefix[i] + "-" + postfix[j];
//             EXPECT_TRUE(g_utilities()->HasElement(tag, levels));
// 		}
//     }
// }


TEST_F(TestLConfig, format)
{
	vector<string> format = LHashMaps::Instance()->GetLogFormatTags();
	EXPECT_TRUE(g_utilities()->HasElement(string("--prefix-none"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--msg-type"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--time-stamp"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--file-path"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--file-name"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--func-name"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--line-no"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--msg-body"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--short"), format));
	EXPECT_TRUE(g_utilities()->HasElement(string("--prefix-all"), format));
}


TEST_F(TestLConfig, targets)
{
	vector<string> targets = LHashMaps::Instance()->GetLogTargetTags();

	EXPECT_TRUE( g_utilities()->HasElement(string("--target-off"), targets));
	EXPECT_TRUE( g_utilities()->HasElement(string("--target-subscriber"), targets));
	EXPECT_TRUE( g_utilities()->HasElement(string("--target-file"), targets));
	EXPECT_TRUE( g_utilities()->HasElement(string("--target-stdout"), targets));
	EXPECT_TRUE( g_utilities()->HasElement(string("--target-all"), targets));
}



TEST_F(TestLConfig, apply_get_level)
{
	LConfig *c = new LConfig();
	EXPECT_EQ( (int64_t)c->GetLogLevel(eMSGSYSTEM::SYS_EX),  PAD(eMSGLEVEL::LOG_ERROR ) );
	EXPECT_EQ( (int64_t)c->GetLogLevel( eMSGSYSTEM::SYS_USER), PAD(eMSGLEVEL::LOG_WARNING) );
	EXPECT_EQ( (int64_t)c->GetLogLevel( eMSGSYSTEM::SYS_FSM), PAD(eMSGLEVEL::LOG_WARNING) );
	EXPECT_EQ( (int64_t)c->GetLogLevel( eMSGSYSTEM::SYS_GENERAL), PAD(eMSGLEVEL::LOG_WARNING) );
	delete c;
}


// TEST_F(TestLConfig, apply_get_level_llogging)
// {
// 	PUSH();
// 	LLogging *l = LLogging::Instance();
	
// 	vector<eMSGTARGET> targets = LHashMaps::GetTargetEnums();
// 	vector<eMSGSYSTEM> systems = LHashMaps::GetSystemEnums();

// 	SET_LOGLEVEL( "--all-off --all-warning --user-info --ana-info " );

// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_NONE,		eMSGTARGET::TARGET_FILE), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_EX,			eMSGTARGET::TARGET_FILE), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_USER,		eMSGTARGET::TARGET_FILE), 				PAD(eMSGLEVEL::LOG_INFO));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_FSM,		eMSGTARGET::TARGET_FILE), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_GENERAL,	eMSGTARGET::TARGET_FILE), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_NONE,		eMSGTARGET::TARGET_STDOUT), 			PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_EX,			eMSGTARGET::TARGET_STDOUT), 			PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_USER,		eMSGTARGET::TARGET_STDOUT), 			PAD(eMSGLEVEL::LOG_INFO));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_FSM,		eMSGTARGET::TARGET_STDOUT), 			PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_GENERAL,	eMSGTARGET::TARGET_STDOUT), 			PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_NONE,		eMSGTARGET::TARGET_GUI), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_EX,			eMSGTARGET::TARGET_GUI), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_USER,		eMSGTARGET::TARGET_GUI), 				PAD(eMSGLEVEL::LOG_INFO));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_FSM,		eMSGTARGET::TARGET_GUI), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_GENERAL,	eMSGTARGET::TARGET_GUI), 				PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_NONE,		eMSGTARGET::TARGET_SUBSCRIBERS), 		PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_EX,			eMSGTARGET::TARGET_SUBSCRIBERS), 		PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_USER,		eMSGTARGET::TARGET_SUBSCRIBERS), 		PAD(eMSGLEVEL::LOG_INFO));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_FSM,		eMSGTARGET::TARGET_SUBSCRIBERS), 		PAD(eMSGLEVEL::LOG_WARNING));
// 	EXPECT_EQ((int64_t)l->GetLogLevel(	eMSGSYSTEM::SYS_GENERAL,	eMSGTARGET::TARGET_SUBSCRIBERS), 		PAD(eMSGLEVEL::LOG_WARNING));

// 	POP();
// }
