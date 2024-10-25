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


#include "GCmdApi.h"
#include <utilities/GException.h>


GCmdApi::GCmdApi()
{

}


GCmdApi::~GCmdApi()
{

}


/** Command line API for scanning boolean GArguments
* @param cmnd the command line tag for this boolean parameter
* @param args_s subs and pars concatenated into one string
* @param subs sub-commands (must be zero or one in this case)
* @param args parameters for this command line tag, this vector must always be of zero size for
* boolean GArguments, nevertheless the GArgument must be present in order to match the function
* pointer signature for the command line API ( and since its allready present we might as weel check the size ). */
bool
GCmdApi::bool2( const string cmnd, const string /*args_s*/, const vector<string> subs, const vector<string> args)
{
    if (subs.size() == 0 && args.size() == 0)
    {
        return true;
    }

    if (args.size() != 0)
    {
        EXCEPTION("The command \"%s\" does not take any argumenst, you can use the subcommand \"--true\" or \"--false\"", cmnd.c_str());
    }

    if (subs.size() == 1)
    {
        if (subs[0] == "--true")
        {
            return true;
        }
        else
            if (subs[0] == "--false")
            {
                return false;
            }
            else
            {
                EXCEPTION("Invalid subcommand, the only valid subcommand to \"%s\" is --true or --false", cmnd.c_str());
            }
    }
    else
        if (subs.size() > 1)
        {
            EXCEPTION("Too many subcommands to  \"%s\", this command takes either no subcommand or exactly ONE subcommand which must be either\"--true\" or \"--false\"", cmnd.c_str());
        }

    return true;
}

