// -*- mode: c++ -*-

#pragma once

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
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


#include <logging/LLogging.h>
#include <logging/LLogTest.h>
#include <logging/LMessage.h>
#include <common/include/KGDefinitions.h>

//#include <utilities/GException.h>
//#include <exception/GException.cpp>

#include "logging.h"

using namespace  LOGMASTER;


#define CONFIGURE_LOGGING( c_command, command) \
 int c_command##(const char * s) \
{  \
    FORCE_DEBUG("running command: c_cmd = %s,,  macro = %s, loglevel attempted set to: %s",  #c_command, #command, s ); \
    try \
	{ \
       command(s); \
        return 0; \
} \
catch (std::exception &e) \
{ \
G_ERROR("Standard Exception Caught, message: %s", e.what()); \
return EXCECUTION_ERROR; \
} \
catch (...) \
{ \
G_ERROR("Unknown Exception Caught!"); \
return EXCECUTION_ERROR; \
} \
return 0; \
}




extern "C"
{
    CONFIGURE_LOGGING( set_loglevel,   SET_LOGLEVEL  );
    //CONFIGURE_LOGGING( set_logtarget,  SET_LOGTARGET );
  //  CONFIGURE_LOGGING( set_logformat,  SET_LOGFORMAT );
    CONFIGURE_LOGGING( set_logfilename, SET_LOGFILENAME);


	int set_logformat(const char * s, eMSGTARGET target )
	{
		FORCE_DEBUG("running command: c_cmd = set_logformat");
		try
		{
		//	SET_LOGFORMAT(s, target );
			return 0;
		}
		catch (std::exception &e)
		{
			G_ERROR("Standard Exception Caught, message: %s", e.what());
			return EXCECUTION_ERROR;
		}
		catch (...)
		{
			G_ERROR("Unknown Exception Caught!");
			return EXCECUTION_ERROR;
		}
		return 0;
}


	int set_logtarget(const char * s )
	{
		FORCE_DEBUG("running command: c_cmd =set_logtarget,,  loglevel attempted set to: %s", s );
		try
		{
			SET_LOGTARGET(s);
			return 0;
		}
		catch (std::exception &e)
		{
			G_ERROR("Standard Exception Caught, message: %s", e.what());
			return EXCECUTION_ERROR;
		}
		catch (...)
		{
			G_ERROR("Unknown Exception Caught!");
			return EXCECUTION_ERROR;
		}
		return 0;
	}



    void log_test(void)
    {
        LLogTest::WriteMessages();
    }


    void register_subscriber(void(*funct)(const LMessage *const))
    {
        LLogging::Instance()->RegisterSubscriber( funct );
        G_INFO("Subscriber registration complete");
    }

    int   push(void)
    {
        ALL_INFO("Popping the current configuration from the stack");
        int ret = POP();
        ALL_INFO("..done");
        return ret;
    }

    int  pop(void)
    {
        ALL_INFO("Pushing the current configuration onto the stack");
        int ret = PUSH();
        ALL_INFO("..done");
        return ret;
      //  LLogging::Instance()->Pop();
    }

}