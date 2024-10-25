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


#include "TestGCmdScan.h"
#include <utilities/GNumbers.h>
#include <cmdline/GCmdApi.h>
#include <cmdline/GCmdScan.h>
#include <cmdline/GArgumentParsed.h>
#include <string>
#include <vector>

using std::vector;
using std::string;


TestGCmdScan::TestGCmdScan() : TestBase()
{

}


TestGCmdScan::~TestGCmdScan()
{

}


void TestGCmdScan::SetUp()
{

}


void TestGCmdScan::TearDown()
{

}


bool  callback_test( const string  cmd, const vector<string>  sub, const vector<string>  par )
{
    FORCE_DEBUG("callback function invoced");
    FORCE_DEBUG("cmd = %s", cmd.c_str() );
    FORCE_DEBUG("parameters = %s",   g_utilities()->Vec2String(par).c_str() );
    FORCE_DEBUG("subcommands = %s",  g_utilities()->Vec2String(sub).c_str() );
    return true;
}


void print_info(GArgumentParsed *arg);


TEST_F(TestGCmdScan, scanning_bug_GRIM415)
{

#define NARGS 13
  //  int argc = 14;
    char *argv[NARGS];

    for(int i=0; i < NARGS; i++)
    {
        argv[i] = new char[100];
        argv[i][0] = 0; 
    }


    SPRINTF( argv[0],  100, "program_name" );
    SPRINTF( argv[1],  100, "-set-speed" );
    SPRINTF( argv[2],  100, "--msc0" );
    SPRINTF( argv[3],  100, "--msc1" );
    SPRINTF( argv[4],  100, "--msc2" );
    SPRINTF( argv[5],  100, "11" );
    SPRINTF( argv[6],  100, "22" );
    SPRINTF( argv[7],  100, "33" );
    SPRINTF( argv[8],  100, "44" );
    SPRINTF( argv[9],  100, "-set-torque" );
    SPRINTF( argv[10], 100, "--msc0" );
    SPRINTF( argv[11], 100, "66" );
    SPRINTF( argv[12], 100, "33" );
    vector<GArgumentParsed> scanned_arguments = g_cmdscan()->SplitCommands(NARGS, (const char **)argv);
    //FORCE_DEBUG("scanned_arguments.size() = %d", scanned_arguments.size() );
    EXPECT_EQ(2, scanned_arguments.size() );

    if( scanned_arguments.size()  == 2 )
    { 
        vector<string> subs0 =  scanned_arguments[0].GetSubCommands(); 
        vector<string> subs1 =  scanned_arguments[1].GetSubCommands(); 

        vector<string> pars0 =  scanned_arguments[0].GetArguments(); 
        vector<string> pars1 =  scanned_arguments[1].GetArguments(); 

        EXPECT_EQ( 3, subs0.size() );
        EXPECT_EQ( 4, pars0.size() );
        EXPECT_EQ( 1, subs1.size() );
        EXPECT_EQ( 2, pars1.size() );

        EXPECT_EQ("-set-speed", scanned_arguments[0].GetCommand() );
        EXPECT_EQ("--msc0", subs0[0]);
        EXPECT_EQ("--msc1", subs0[1]); 
        EXPECT_EQ("--msc2", subs0[2]);
        EXPECT_EQ("11", pars0[0]);
        EXPECT_EQ("22", pars0[1]);
        EXPECT_EQ("33", pars0[2]);
        EXPECT_EQ("44", pars0[3]);

        EXPECT_EQ("-set-torque", scanned_arguments[1].GetCommand() );
        EXPECT_EQ("--msc0", subs1[0]);
        EXPECT_EQ("66", pars1[0]);
        EXPECT_EQ("33", pars1[1]);
    }
}


void 
print_info(GArgumentParsed *arg)
{
    FORCE_DEBUG("cmdname = %s", arg->GetCommand().c_str() );
    vector<string> subs =  arg->GetSubCommands();
    vector<string> pars =  arg->GetArguments();

    for(uint i=0; i < subs.size(); i++ )
    {
        FORCE_DEBUG("subcmd[%d] = \t%s", i, subs[i].c_str()    );
    }   
   
    for(uint i=0; i < pars.size(); i++ )
    {
        FORCE_DEBUG("par[%d] = \t%s", i, pars[i].c_str()    );
    }   
    

}