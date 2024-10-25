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

#include "GSystem.h"
#include <boost/algorithm/string/replace.hpp>

#ifdef _WIN32
#include <boost/filesystem.hpp>
#else
#include </usr/include/boost/filesystem.hpp>
#endif

//#include <boost/system>

using namespace boost::filesystem;


string
GSystem::getenv(const string  var  )
{
    char *tmp  = std::getenv( (char *)var.c_str()  );
    
    if( tmp != nullptr )
    {
         return string(tmp);
    }
    else
    {
        return var + ": no such env variable found";
    }

}


/** mkdir =   Make Directory (that is a folder in Windows terms), Unix/bash style
*   @param    dirname The directory to create
*   @return   true if the directory exists, or if it doesnt allready exists, but was
*   successfully created
*   @return false if the directory doesnt exist, and it also cannot be created (for instance if
*   the program is running under a user that doesnt have write access to the currnt directory)
*   @throw Exception if the directory doesnt exist and it cannot be created.*/
bool
GSystem::mkdir(const string dirname)
{
    //  using            boost::system::error_code;
    //    using namespace  boost::filesystem;
    char dir_path[512];
    snprintf(dir_path, 512, "%s", dirname.c_str());
    boost::filesystem::path dir(dir_path);
    //./GSystem.cpp:67:34: error: no matching function for call to ‘create_directories(boost::filesystem::path&, std::error_code&)
    if (exists(dir))
    {
        G_INFO("The directory %s allready exists (thats OK), doing nothing", dirname.c_str());
        return true;
    }
    else
    {
        boost::system::error_code e;
        //   create_directories(dir, e);
        create_directories(dir, e);
   
        if (e.value() == 0)
        {
            return true;
        }
        else
        {
            EXCEPTION("The directory \"%s\" could not be created,.. please check that you have write + exce permissions to the directory ....aborting (message from boost %s\")", dirname.c_str(), e.message().c_str());
            return false;
        }
    }
}




bool
GSystem::Exists(const string filepath)
{
	return boost::filesystem::exists(filepath);
}



string
GSystem::GetDirectory(const string filepath)
{
	const char* filepathCp = filepath.c_str();
	const char* charPtr = filepathCp + filepath.length() - 1;
	if ((*charPtr == '/') || (*charPtr == '\\'))
	{
		--charPtr;
	}
	while ((charPtr > filepathCp) && (*charPtr != '/') && (*charPtr != '\\'))
	{
		--charPtr;
	}
	if (charPtr > filepathCp)
	{
		size_t returnLen = charPtr - filepathCp;
		return filepath.substr(0, returnLen);
	}
	return "";
}


string
GSystem::GetProcessID()
{
    std::stringstream buffer;
#ifdef _WIN32
	buffer << GetCurrentProcessId();
#else
    buffer << getpid();
#endif
    return buffer.str();
}


/** @return Returns the name of rootdir */

#ifdef _WIN32
char*
GSystem::GetHomeDir()
{
    static char* buf;
    buf = GetExePath();
    PathRemoveFileSpecA(buf);
    string path = string(buf);
    static string dir;
    static string fout;
    g_tokenizer()->StripPath(path, dir, fout);
    static string homedir = fout + "\\..\\..\\";
    return  (char *)homedir.c_str(); 
   // inline  void API StripPath(const string fin, string &dir, string &fout, const bool keep_trailing_slash = KEEP_TRAILING_SEPARATOR ); 	
    SPRINTF(buf, 1024, "%s\\..\\..\\", buf); // CRAP PTH
	return buf;
}
#endif
