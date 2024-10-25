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


#include "TestLFormat.h"



TestLFormat::TestLFormat()
{
	
}


TestLFormat::~TestLFormat()
{

}


TEST_F( TestLFormat, dummy )
{
	SET_LOGFORMAT("--target-file 00000001");
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );
	SET_LOGFORMAT("--target-file 00000000");
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF, l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file --short-user");
	EXPECT_EQ( eMSGFORMAT::USER_SHORT_MSG, l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file  --all-off --msg-body --time-short");
	EXPECT_EQ(  (eMSGFORMAT::MESSAGE_BODY | eMSGFORMAT::TIME_STAMP_SHORT), l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file  --all-off --msg-body --time-short");
	EXPECT_EQ(  eMSGFORMAT::USER_SHORT_MSG, l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file  --all-off --msg-body --line-no --func-name --file-name --file-path --time-stamp --msg-type --time-short");
	EXPECT_EQ(  eMSGFORMAT::PREFIX_ALL, l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file  --all-off --file-name");
	EXPECT_EQ(  eMSGFORMAT::FILE_NAME, l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file  --msg-body");
	EXPECT_EQ(  (eMSGFORMAT::FILE_NAME  | eMSGFORMAT::MESSAGE_BODY) , l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );

	SET_LOGFORMAT("--target-file  --all-off --time-short");
	EXPECT_EQ(  eMSGFORMAT::TIME_STAMP_SHORT , l->GetLogFormat( eMSGTARGET::TARGET_FILE ) );


	SET_LOGFORMAT("--target-gui 00000001");
	EXPECT_EQ( eMSGFORMAT::MESSAGE_BODY, l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );
	
	SET_LOGFORMAT("--target-gui 00000000");
	EXPECT_EQ( eMSGFORMAT::ALL_FIELDS_OFF, l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui --short-user");
	EXPECT_EQ( eMSGFORMAT::USER_SHORT_MSG, l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui  --all-off --msg-body --time-short");
	EXPECT_EQ(  (eMSGFORMAT::MESSAGE_BODY | eMSGFORMAT::TIME_STAMP_SHORT), l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui  --all-off --msg-body --time-short");
	EXPECT_EQ(  eMSGFORMAT::USER_SHORT_MSG, l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui  --all-off --msg-body --line-no --func-name --file-name --file-path --time-stamp --msg-type --time-short");
	EXPECT_EQ(  eMSGFORMAT::PREFIX_ALL, l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui  --all-off --file-name");
	EXPECT_EQ(  eMSGFORMAT::FILE_NAME, l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui  --msg-body");
	EXPECT_EQ(  (eMSGFORMAT::FILE_NAME  | eMSGFORMAT::MESSAGE_BODY) , l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

	SET_LOGFORMAT("--target-gui  --all-off --time-short");
	EXPECT_EQ(  eMSGFORMAT::TIME_STAMP_SHORT , l->GetLogFormat( eMSGTARGET::TARGET_GUI ) );

}