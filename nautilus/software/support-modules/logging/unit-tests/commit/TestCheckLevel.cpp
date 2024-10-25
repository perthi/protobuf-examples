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

#include "TestCheckLevel.h"



TestCheckLevel::TestCheckLevel()
{
}


TestCheckLevel::~TestCheckLevel()
{
}


// TEST_F( TestCheckLevel, check_level )
// {
// 	PUSH();
// 	SET_LOGTARGET("1111");
// 	SET_LOGLEVEL("--all-off --all-warning --ana-info");

// 	EXPECT_TRUE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_WARNING, eMSGTARGET::TARGET_FILE ) );
// 	EXPECT_TRUE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_WARNING, eMSGTARGET::TARGET_STDOUT ) );
// 	EXPECT_TRUE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_WARNING, eMSGTARGET::TARGET_GUI ) );
// 	EXPECT_TRUE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_WARNING, eMSGTARGET::TARGET_SUBSCRIBERS ) );
// 	EXPECT_FALSE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_INFO, eMSGTARGET::TARGET_GUI ) );
// 	EXPECT_FALSE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_DEBUG, eMSGTARGET::TARGET_SUBSCRIBERS ) );


// 	l->SetLogLevel( "--target-stdout --fsm-fatal" );
// 	l->SetLogFormat( "--target-file 01000001" );


// 	EXPECT_FALSE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_WARNING, eMSGTARGET::TARGET_STDOUT ) );
// 	EXPECT_FALSE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_ERROR, eMSGTARGET::TARGET_STDOUT ) );
// 	EXPECT_TRUE( l->CheckLevel( eMSGSYSTEM::SYS_FSM, eMSGLEVEL::LOG_FATAL, eMSGTARGET::TARGET_STDOUT ) );

// 	POP();
// }
