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


#include "LLoggingInternal.h"
#include <utilities/GTime.h>
#include <utilities/GString.h>
#include <logging/LConfig.h>
#include <utilities/GFileIOHandler.h>
#include <logging/LLogging.h>

#include <errno.h>

#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#endif


namespace LOGMASTER
{
    void
    LLoggingInternal::Log(GLocation local, GLocation caller, GFileName_t fname, const string message )
    {
        string msg;
		std::stringstream buffer;
		buffer << local.fFileName + "::" + local.fFunctName + "(line " << local.fLineNo << ")" << endl;
		buffer << "modified from : " + caller.fFileName + "::" + caller.fFunctName + "(line " << caller.fLineNo << ")" << endl;
		buffer << "\tsettings applied: " + message << endl;
        FILE *fp;
        
#ifdef _WIN32
        int err = fopen_s(&fp, fname.c_str(), "a");	
        #else
        fp =  fopen(fname.c_str(), "a");	
#endif
        if (fp != 0)
        {
#ifdef _WIN32
			//g_file()->SetAttribute(fname.str(), FILE_ATTRIBUTE_HIDDEN);
#endif
			fprintf(fp, "%s\n", msg.c_str());
			fclose(fp);
		}
		else
        {
			cerr << "Could not open file:" << fname.str() << "  for writing" << endl;
        }      
    }

}

