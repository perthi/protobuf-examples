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

#include "TestLTargets.h"
#include <utilities/GNumbers.h>
#include <utilities/GUtilities.h>

#include <logging/LHashMaps.h>


TestLTargets::TestLTargets()
{

}


TestLTargets::~TestLTargets()
{

}


void 
TestLTargets::SetUp()
{
	InitLogArgs();
}


void 
TestLTargets::TearDown()
{

}



TEST_F(TestLTargets, configure_format_specific_target)
{
		
		SET_LOGFORMAT("--target-file 00000001");
		EXPECT_EQ(eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		SET_LOGFORMAT("--target-stdout 01000000");
		EXPECT_EQ(eMSGFORMAT::MESSAGE_TYPE, l->GetLogFormat(eMSGTARGET::TARGET_STDOUT));
		EXPECT_EQ(eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		SET_LOGFORMAT("11111111");
		SET_LOGFORMAT("--target-file 00000001");
		EXPECT_EQ(eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		SET_LOGFORMAT("--target-stdout 01000000");
		EXPECT_EQ(eMSGFORMAT::MESSAGE_TYPE, l->GetLogFormat(eMSGTARGET::TARGET_STDOUT));
		EXPECT_EQ(eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		SET_LOGFORMAT("11111111");
		EXPECT_EQ(eMSGFORMAT::PREFIX_ALL, l->GetLogFormat(eMSGTARGET::TARGET_STDOUT));
		EXPECT_EQ(eMSGFORMAT::PREFIX_ALL, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		
		SET_LOGFORMAT("00000000");
		EXPECT_EQ(eMSGFORMAT::ALL_FIELDS_OFF, l->GetLogFormat(eMSGTARGET::TARGET_STDOUT));
		EXPECT_EQ(eMSGFORMAT::ALL_FIELDS_OFF, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		
	

		ScanArguments("-logformat --target-stdout 00000001");
		EXPECT_EQ(eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_STDOUT));
		
		ScanArguments("-logformat --target-stdout 00000001");
		
		EXPECT_EQ(eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_STDOUT));
		ScanArguments("-logformat --target-file 01000001");
		EXPECT_EQ(eMSGFORMAT::MESSAGE_TYPE | eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat(eMSGTARGET::TARGET_FILE));
		ScanArguments("-logformat --target-stdout 00000001");
		ScanArguments("-logformat --target-stdout 01111111");
		SET_LOGLEVEL("--target-file --off --fatal");
		SET_LOGLEVEL("--target-stdout --off --debug");
		G_DEBUG("This a debug message");
		G_INFO("This a info message");
		G_WARNING("This a warning message");
		G_ERROR("This an error warning message");
		G_FATAL("This a fatal message");
		

}



TEST_F( TestLTargets, configure_level_specific_target )
{
	vector<eMSGSYSTEM> e_s = LHashMaps::Instance()->GetSystemEnums();
	vector<eMSGTARGET> e_t = LHashMaps::Instance()->GetTargetEnums();
	ScanArguments( "-loglevel --all-debug");
//	EXPECT_EQ(PAD(eMSGLEVEL::LOG_DEBUG),  (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT ));
	EXPECT_EQ(PAD(eMSGLEVEL::LOG_WARNING),  (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ALARM, eMSGTARGET::TARGET_STDOUT ));

	ScanArguments( "-loglevel --all-warning");
	g_utilities()->FilterOut( e_s, { eMSGSYSTEM::SYS_ALL, eMSGSYSTEM::SYS_NONE, eMSGSYSTEM::SYS_ALARM, eMSGSYSTEM::SYS_EX } );
	g_utilities()->FilterOut( e_t, { eMSGTARGET::TARGET_ALL, eMSGTARGET::TARGET_OFF  } );
	
	for ( size_t s = 0; s < e_s.size(); s++ )
	{
		for ( size_t t = 0; t < e_t.size(); t++ )
		{
			EXPECT_EQ( PAD( eMSGLEVEL::LOG_WARNING ), (int64_t)l->GetLogLevel( e_s[s],  e_t[t] ) );
		}
	}

	ScanArguments( "-loglevel --all-debug");

	for ( size_t s = 0; s < e_s.size(); s++ )
	{
		for ( size_t t = 0; t < e_t.size(); t++ )
		{
			EXPECT_EQ( PAD( eMSGLEVEL::LOG_DEBUG ), (int64_t)l->GetLogLevel( e_s[s],  e_t[t] ) );
		}
	}
	
	ScanArguments( "-loglevel --off --all-error" );
	ScanArguments( "-loglevel --target-stdout --all-info" );
	g_utilities()->FilterOut( e_t, { eMSGTARGET::TARGET_STDOUT } );
	
	for ( size_t s = 0; s < e_s.size(); s++ )
	{
		for ( size_t t = 0; t < e_t.size(); t++ )
		{
			EXPECT_EQ( PAD( eMSGLEVEL::LOG_ERROR ), (int64_t)l->GetLogLevel( e_s[s],  e_t[t] ) );
		}
	}
	
	// EXPECT_EQ(PAD(eMSGLEVEL::LOG_INFO), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT ));
	// EXPECT_EQ(PAD(eMSGLEVEL::LOG_INFO), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT ));
	// EXPECT_EQ(PAD(eMSGLEVEL::LOG_INFO), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT ));
	// EXPECT_EQ(PAD(eMSGLEVEL::LOG_INFO), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ANALYSIS, eMSGTARGET::TARGET_STDOUT ));
	
	EXPECT_EQ(PAD(eMSGLEVEL::LOG_WARNING), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ALARM, eMSGTARGET::TARGET_STDOUT ));
	EXPECT_EQ(PAD(eMSGLEVEL::LOG_WARNING), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ALARM, eMSGTARGET::TARGET_STDOUT ));
	EXPECT_EQ(PAD(eMSGLEVEL::LOG_WARNING), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ALARM, eMSGTARGET::TARGET_STDOUT ));
	EXPECT_EQ(PAD(eMSGLEVEL::LOG_WARNING), (int64_t)l->GetLogLevel(eMSGSYSTEM::SYS_ALARM, eMSGTARGET::TARGET_STDOUT ));

}

