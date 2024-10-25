// -*- mode: c++ -*-

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

#include "LValidateArgs.h"
#include "LDoc.h"
#include <exception>
#include <stdexcept>
#include <logging/LLogging.h>


namespace LOGMASTER
{
    LValidateArgs::LValidateArgs()
    {

    }


    LValidateArgs::~LValidateArgs()
    {

    }


    bool
    LValidateArgs::CAPIValidateSubCommands(const string cmd,  const string args_s, const vector<string> sub, const vector<string> par)
    {
        if (sub.size() == 0 && par.size() == 0)
        {
            throw(std::invalid_argument((cmd + "expects at least one subcommand, a binary, or a hex number to set the loglevel:\n," + LDoc::Instance()->Help()).c_str()));
        }

        LLogging::Instance()->SetLogLevel( args_s );
        return true;
    }


    bool 
    LValidateArgs::CAPIValidateTargets(const string cmd,  const string args_s, const vector<string> targets, const vector<string> par)
    {
        if (targets.size() == 0 && par.size() == 0)
        {
            throw(std::invalid_argument(    (cmd +": You must spcify at least eiter one parameter or one subcommand").c_str() )  );
        }
        else
        {
            LLogging::Instance()->SetLogTarget( args_s );
        }
            
        return true;
    }
        
        
    bool
    LValidateArgs::CAPIValidateFormat(const string /*cmd*/,  const string  args_s,  const vector<string> /*sub*/, const vector<string> /*par*/ )
    {
        LLogging::Instance()->SetLogFormat( args_s );
        return true;
    }

}
