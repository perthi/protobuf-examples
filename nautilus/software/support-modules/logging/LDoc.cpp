// -*- mode: c++ -*-
/* ****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
***************************************************************************** */

/* ****************************************************************************
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

#include "LDoc.h"
#include "LLogging.h"
#include "LConfig.h"
#include  "LHashMaps.h"
#include <utilities/GUtilities.h>
#include <fstream>
using std::ofstream;

#include <bitset>


namespace LOGMASTER
{
 
    
    string
    LDoc::UsageError(const string cmnd, const string sub, map <string, std::tuple<  eMSGSYSTEM, eMSGLEVEL > >  m)
    {
        std::stringstream buffer;
        buffer << "Invalid/bad combination command/subcommand: " << sub << " To " << cmnd << ".\nValid subcommands are:" << 
			g_utilities()->Hash2String(&m);
        buffer << Help();
        return buffer.str();
    }


    string
    LDoc::logTargetDoc()
    {
        return string("[logtarget]\n")
            + string("\t\tLogtarget can be either a field with 3 bits or any of the following\n\t\t")
            + g_utilities()->Hash2String (LHashMaps::GetTargetHash( ));
    }


    string
    LDoc::logLevelDoc()
    {
        return string("[loglevel]\n")
            + string("\t\tLoglevel can be any of the following\n\t\t")
            + g_utilities()->Hash2String(LHashMaps::GetSubCmdHash())
            + "\t\tThe loglevel to use,the subcommand (starting with --) has two terms,\
the first one denotes the\n\t\tsubsystem the second one the loglevel for that subsystem.\n\t\t \
Example 1) --all-debug = All subsystem is using loglevel debug\n\t\tExample 2) --ana-error Error messages form the QA subsystem system, etc..";
    }


    string
    LDoc::logFormatDoc()
    {
        return string("[logformat]\n")
            + string("\t\tlogformat can be any of the following\n\t\t")
            + g_utilities()->Hash2String(LHashMaps::GetFormatHash());
    }


    void 
    LDoc::PrintLogLevels(bool toconsole)
    {
        ostringstream s;
        std::ofstream f;
        f.open("loglevels.txt");

		auto hash = LHashMaps::GetSubCmdHash();
	
        for (auto it = hash->begin(); it != hash->end(); it ++ )
        {
            std::bitset<16>  b( (int32_t)std::get<0>(it->second) );

            if (it->first.size() < 8)
            {
                s << it->first  <<  "\t\t\t" <<  b  <<  "\t0x"  <<  std::hex << (int32_t)std::get<0>(it->second) << endl;
            }
            else if (it->first.size() < 16)
            {
                s << it->first  <<  "\t\t"   <<  b  <<  "\t0x"  <<  std::hex <<  (int32_t)std::get<0>(it->second)  << endl;
            }
            else
            {
                s << it->first << "\t" << b << "\t0x" << std::hex << std::hex << (int32_t)std::get<0>(it->second)  << endl;
            }
        }
        if (toconsole == true)
        {
            cout << s.str() << endl;
        }
        f << s.str();
        f.close();
    }


    string
    LDoc::Help()
    {
        std::stringstream buffer;
        buffer << "*** USAGE ***" << endl;
        buffer << "1) Either Use any number of subcommands ( starting with --)" << endl;
        buffer << "2) OR: Specify a number indicating the loglevel" << endl;
        buffer << "3) If on number form the number must be either a string of  ZERO and ONES containing exactly 16 bits" << endl;
        buffer << "\tOr a hex number starting with 0x and  having exactly 4 fields" << endl;
        buffer << "Available subcommands are: Valid sub-commands are\n" << g_utilities()->Hash2String (LHashMaps::GetSubCmdHash() ) << endl;
        return buffer.str();
    }


}
