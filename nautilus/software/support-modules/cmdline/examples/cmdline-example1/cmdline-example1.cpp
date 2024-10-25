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

// cmndlineexample1.cpp : Defines the entry point for the console application.

#ifdef _WIN32
#include <windows.h>
#endif


#include <logging/LMessage.h>
#include <logging/LMessageGenerator.h>
#include <logging/LLogging.h>
#include <utilities/GSystem.h>
#include <cmdline/GArgument.h>
#include <cmdline/GCommandLineArgument.h>
#include <cmdline/GLogApplication.h>
#include <utilities/GNumbers.h>
#include <utilities/GConstants.h>
#include <utilities/GException.h>

using namespace GCONSTANTS;
using namespace LOGMASTER;

#include <string>
using std::string;

#include <vector>
using std::vector;

bool 
callback_test1(const string cmd, const string, const vector<string> subs, const vector<string> pars)
{
    /// You can do additional checks here
    FORCE_DEBUG("cmd = %s, subs size = %d, + pars size = %d", cmd.c_str(),  subs.size(), pars.size() );
    return true;
}



bool 
callback_test2(const string cmd, const string, const vector<string> subs, const vector<string> pars)
{
    /// You can do additional checks ob the
    if( pars.size() !=2 && subs.size() != 0 )
    {   
        
    }
    FORCE_DEBUG("cmd = %s, subs size = %d, + pars size = %d", cmd.c_str(),  subs.size(), pars.size() );
    return true;
}




int main(const int argc, const char** argv )
{ 
    cerr << "The hostname is: " << g_system()->GetHostName() << endl;

    SET_LOGFORMAT("11111111");
    SET_LOGTARGET("1111");
   // SET_LOGLEVEL("1111111111111111");
  //  G_ERROR("This is a error message, the answeer to the univers is  %d", 42);
    
    int test1 = 0;
    int test2 = 0;
    double test3 = 0;
    string test4 = "";
    vector<string> test5 = vector<string>();

    vector<GArgument *> arguments;


    GArgument *a1  =  new GCommandLineArgument< int>("-myint1", 
                                                    "-myint1 [value]",
                                                    "sets the value of  myint1",
                                                     &test1, fgkOPTIONAL,  callback_test1 );
    

/// Simlified version, no callback function, the argumen is assumed to be optional
    GArgument *a2  =  new GCommandLineArgument< int>("-mydouble", 
                                                    "-mydouble [value]",
                                                    "sets the second value",
                                                     &test2);
    
    
    GArgument *a3  =  new GCommandLineArgument< double>("-mydouble", 
                                                    "-mydouble [value]",
                                                    "sets the value of mydouble",
                                                     &test3, fgkOPTIONAL,  callback_test2 );
    

    GArgument *a4  =  new GCommandLineArgument< string>("-mystring", 
                                                    "-myval1 [value]",
                                                    "sets the second value",
                                                     &test4, fgkMANDATORY,  callback_test2 );
    

    
    GArgument *a5  =  new GCommandLineArgument< vector<string> >("-mystring", 
                                                    "-myval1 [value]",
                                                    "sets the second value",
                                                     &test5, fgkMANDATORY,  callback_test2 );

    
    arguments.push_back(a1);
    arguments.push_back(a2);
    arguments.push_back(a3);
    arguments.push_back(a4);
    arguments.push_back(a5);

    //(GLogApplication(argc, argv, &arguments);

    GLogApplication *g = new GLogApplication();
    g->ScanArguments(argc, argv, &arguments );
   // cout << "test1 = "<< test1  << endl;

    return 0;
}


