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


#include "GArgumentParsed.h"

///#include <iostream>
#include <iostream>

using std::endl;
using std::cout;

#include <ostream>
#include <sstream>

string 
GArgumentParsed::ParInfo(const vector<string> par )  const
{
    std::stringstream buffer;  
    buffer << "*** PARAMETERS ***" << endl;
    for(uint16_t i=0; i < par.size(); i++ )
    {
	buffer << "Par[" << i << "] = " << par[i] << endl;
    }
    
    buffer << "*** NB, parameters must be parsed to their appropriate type ***"  << endl;
    
    return buffer.str();
}


string    
GArgumentParsed::str()   const
{
    std::stringstream buffer;  
    buffer << GArgument::str() << endl;
    buffer << ParInfo( fArguments );
    return buffer.str();
}
