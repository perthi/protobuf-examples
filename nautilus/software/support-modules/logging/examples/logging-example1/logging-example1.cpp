// -*- mode: c++ -*-

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no> http:///www.embc.no  ***
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

//#include <version-info/GMenu.h>
#include <boost/regex.hpp>

#define G_STANDALONE

#include  <iostream>
#include  <logging/LLogging.h>
#include  <logging/LLogTest.h>
#include  <logging/LMessage.h>
#include  <logging/LConfig.h>
#include  <cmdline/GLogApplication.h>

#include <utilities/GException.h>

using std::cout;
using std::endl;
using namespace LOGMASTER;


#include <map>

int
main(int  /*argc*/, const char ** /*argv*/ )
{
	try
	{
		SET_LOGLEVEL("--off --all-debug");
        SET_LOGTARGET("1111");

		LLogTest::WriteMessages();

		//SET_LOGLEVEL("111111110000000000001000");
		SET_LOGLEVEL("000000000000000000000000");
	//	SET_LOGLEVEL("111111111111111111111111");

	}
	catch (GException &e)
	{
		cout << "exception caucht:" << e.what() << endl;
	}
	catch (std::exception &e)
	{
		cout << "std::exception caught: " << e.what() << endl;
	}
	catch(string &e)
	{
		CERR << e << endl;
	}
	catch (...)
	{
		cout << "unknown exception caught" << endl;
	}
    return 0;

}
