// -*- mode: c++ -*-
/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no>  http:///www.embc.no ***
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

#include "GCmdWiki.h"

#include  <utilities/GException.h>
#include  <utilities/GFileIOHandler.h>
#include  <logging/LLogApi.h>

#include <utilities/GUtilities.h>
#include <utilities/GString.h>

using namespace LOGMASTER;


GCmdWiki::GCmdWiki()
{

}


GCmdWiki::~GCmdWiki()
{

}


void    
GCmdWiki::GenerateWiki(  vector<GArgument *> *args,  const string  filename  )
{
    FORCE_DEBUG("arguments size = %d", args->size() );
    
    G_ASSERT_EXCEPTION(filename != "", "Filename cannot be empty" );
    std::stringstream buffer;
//    auto args = GetArguments();
    FORCE_DEBUG("arguments size = %d", args->size() );
	
    
    g_file()->Recreate(filename);
    g_file()->Append( filename, "||Command || Usage || Helptex || \n");

    for(size_t i=0; i < args->size(); i ++  )
    {
        string cmd    =  args->at(i)->GetCommand();
        string usage  =  args->at(i)->GetUsage();
        string help   =  args->at(i)->GetHelpText(  );
      //  string subs =  g_utilities()->Vec2String( args->at(i)->GetSubCommands() );

        //subs = "blahhhhh";

        buffer  << "\tcmd = "<< cmd;
        buffer  << "\tusage = "<< usage; 
        buffer  << "\thelptext = " << help;
       // buffer  << "\tsubcommands = " << subs;
      //buffer  << "\tsubcommands = " << subs;

        buffer << endl;
         g_file()->Append( filename,  "|%s | %s | %s |  \n",  cmd.c_str(), usage.c_str(), help.c_str()  );
    }

    FORCE_DEBUG("helptex =\n%s", buffer.str().c_str() ) ;
}

