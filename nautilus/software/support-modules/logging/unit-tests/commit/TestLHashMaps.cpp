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


#include "TestLHashMaps.h"


#include <utilities/GUtilities.h>
#include <logging/LHashMaps.h>

#include <vector>

using std::vector;

TestLHashMaps::TestLHashMaps()
{
}


TestLHashMaps::~TestLHashMaps()
{
}


void 
TestLHashMaps::SetUp()
{

}

void 
TestLHashMaps::TearDown()
{

}


TEST_F( TestLHashMaps, IsTargetHash )
{
	EXPECT_TRUE(  LHashMaps::Instance()->IsTargetHash("--target-off") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsTargetHash("--target-subscriber") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsTargetHash("--target-file") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsTargetHash("--target-stdout") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsTargetHash("--target-gui") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsTargetHash("--target-all") );
	EXPECT_FALSE( LHashMaps::Instance()->IsTargetHash( "--gibberish" ) );
	EXPECT_FALSE( LHashMaps::Instance()->IsTargetHash( "gibberish" ) );
}


TEST_F( TestLHashMaps, IsFormatHash )
{
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--all-off") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--msg-type") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--time-stamp") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--file-path") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--func-name") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--line-no") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--prefix-none") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--msg-body") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--short") );
	EXPECT_TRUE(  LHashMaps::Instance()->IsFormatHash("--prefix-all") );
	EXPECT_FALSE( LHashMaps::Instance()->IsFormatHash( "--gibberish" ) );
	EXPECT_FALSE( LHashMaps::Instance()->IsFormatHash( "gibberish" ) );
}


/*
TEST_F( TestLHashMaps, IsSubCmdhash )
{

	    EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-off"));          
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--off"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fatal"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--error"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--warning"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--info"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--debug"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--all"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ana-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-off"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-fatal"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-error"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-warning"));
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-info"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-debug"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--analysis-all"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--data-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-off"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-warning"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--ex-all"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-fatal"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-error"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-info"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-debug"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--driver-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--gen-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--user-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--fsm-all"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-off"));			
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-fatal"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-error"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-warning"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-info"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-debug"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-all"));			
        EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-fatal"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-error"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-info"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-debug"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-sql-all"));		
        EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-off"));		
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-fatal"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-error"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-warning"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-info"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-debug"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-gen-all"));		
        EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-off"));	
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-fatal"));
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-error"));
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-warning"));
        EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-info"));   
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-debug"));
		EXPECT_TRUE(LHashMaps::IsSubCmdHash("--db-report-all"));	
		EXPECT_FALSE(LHashMaps::IsSubCmdHash("--gibberish"));
		EXPECT_FALSE(LHashMaps::IsSubCmdHash("gibberish"));	
}
*/



TEST_F(TestLHashMaps, contains_targes_enums )
{
	EXPECT_TRUE(true);

	vector<eMSGTARGET>  targets = LHashMaps::Instance()->GetTargetEnums();

	EXPECT_TRUE( g_utilities()->Contains( targets, eMSGTARGET::TARGET_FILE) );
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_STDOUT));
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_SUBSCRIBERS));

	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_OFF));
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_ALL));
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_GUI));

	g_utilities()->FilterOut(targets, { eMSGTARGET::TARGET_OFF, eMSGTARGET::TARGET_ALL });


	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_FILE));
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_STDOUT));
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_SUBSCRIBERS));

	EXPECT_FALSE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_OFF));
	EXPECT_FALSE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_ALL));
	EXPECT_TRUE(g_utilities()->Contains(targets, eMSGTARGET::TARGET_GUI));

}


TEST_F(TestLHashMaps, contains_format_enums)
{
	EXPECT_TRUE(true);
	vector<eMSGFORMAT>  formats = LHashMaps::Instance()->GetFormatEnums();
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::PREFIX_OFF));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::MESSAGE_TYPE));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::TIME_STAMP));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::FILE_PATH));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::FILE_NAME));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::FUNCTION_NAME));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::LINE_NO));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::MESSAGE_BODY));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::SHORT_MSG));
	EXPECT_TRUE(g_utilities()->Contains(formats, eMSGFORMAT::PREFIX_ALL));

}


/*
TEST_F(TestLHashMaps, contains_system_enums)
{
	EXPECT_TRUE(true);
	vector<eMSGSYSTEM>  systems = LHashMaps::GetSystemEnums();
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_NONE));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_ANALYSIS));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DATA));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_EX));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DRIVER));
	
    EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_GEN));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_SQL));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_REPORT));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_ALL));

	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_USER));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_FSM));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_GENERAL));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_ALL));

	g_utilities()->FilterOut(systems, { eMSGSYSTEM::SYS_NONE, eMSGSYSTEM::SYS_ALL } );

	EXPECT_FALSE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_NONE));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_ANALYSIS));	
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DATA));
	
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_EX));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DRIVER));

	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_GEN));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_SQL));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_REPORT));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_DB_ALL));

	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_USER));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_FSM));
	EXPECT_TRUE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_GENERAL));
	EXPECT_FALSE(g_utilities()->Contains(systems, eMSGSYSTEM::SYS_ALL));
}
*/



TEST_F(TestLHashMaps, contains_levle_enums)
{
	EXPECT_TRUE(true);
	vector<eMSGLEVEL>  levels = LHashMaps::Instance()->GetLevelEnums();
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_OFF));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_FORCE_DEBUG));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_DEBUG));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_INFO));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_WARNING));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_ERROR));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_FATAL));
	EXPECT_TRUE(g_utilities()->Contains(levels, eMSGLEVEL::LOG_ALL));
	
}