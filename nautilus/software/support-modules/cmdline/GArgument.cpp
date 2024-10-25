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



#include "GArgument.h"
#include <utilities/GException.h>
#include <logging/LLogging.h>
#include <utilities/GUtilities.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using namespace LOGMASTER;

#include <utilities/GException.h>



int     GArgument::fNTabs = 4;    


GArgument::GArgument(): fCmd("Unknown"),
                        fSubCmds(),
                        fIsMandatory(false),
                        fTypeId("Unknown"), 
                        fTypeIdBase("No Base"),
                        fUsage("NOT SET"),
                        fHelpText("NOT SET"),
                        fExecName("NOT SET"),
                        ValidateCommands(0)
{
   

}


GArgument::GArgument(const string name,
    const string usage,
    const string help,
    const bool ismandatory,
    std::function< bool(const string cmnd, const string args_s, const vector<string> sub, const vector<string> par) >  funct ) : fCmd(name),  
        fSubCmds(), 
        fIsMandatory(ismandatory), 
        fTypeId("Unknown"), 
        fTypeIdBase("No Base"), 
        fUsage(usage), 
        fHelpText(help), 
        fExecName("NOT SET"), 
        ValidateCommands(funct)
{

}




bool 
GArgument::Verify()
{
    if(ValidateCommands == 0 )
    {
	  G_INFO("Validation function is ZERO");
    }
    else
    {
		return ValidateCommands (fCmd, "", fSubCmds, vector<string> () );
    }
    return false;
}


void   
GArgument::AddSubCommand(const string cmd)
{
    fSubCmds.push_back(cmd); 
}




string 
GArgument::str(const bool subcommands ) const
{   
    std::stringstream buffer;  

    buffer << "\t" << g_utilities()->TabAlign(fCmd, fNTabs)  << fUsage;    

    if( subcommands  == true )
    {
        buffer << ";\t" <<  fHelpText;

        G_INFO("%s", buffer.str().c_str()); //CRAP PTH
    
        if(  fSubCmds.size() > 0  && subcommands == true )
        {
            buffer << "*** SUBCOMMANDS ****" << endl;
	        for(size_t i=0; i < fSubCmds.size(); i++ )
	        {
	            buffer << "Subcommand[" << i << "] = " << fSubCmds[i] << endl;
	        }
        }
    }
    return buffer.str();
}



string   
GArgument::GetHelpText(const bool subcommands) const
{
    string msg =  str(subcommands);
    //cout << msg;
    return msg;
}



void 
GArgument::SetExcecName(const char *name)
{
    if(name !=0)
    {
	    fExecName = string(name);
    }
    else
    {
	    EXCEPTION("ZERO POINTER !!!!");
    }
}


//void 
//GArgument::SetValidationFunction( bool (*funct) (const string cmd, const vector<string> sub, const vector<string> par)  )

void 
GArgument::SetValidationFunction(  std::function< bool(const string cmd, const string args_s, const vector<string> sub, const vector<string> par )> funct )
{
    ValidateCommands = funct;
}



/** The number of tabs to use when aligning the help menu*/
void
GArgument::SetNTabs( const int n )
{
    fNTabs = n;
} 

 //vector<string> &  GetSubCommands()  { return fSubCmds; };
string        
GArgument::GetSubCommandsS()
{
    return g_utilities()->Vec2String(fSubCmds, " " );
}