// -*- mode: c++ -*-

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

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

#include "LColorMap.h"
#include <utilities/GColor.h>



LColorMap::LColorMap() : fMap()
{
    Init();
}



LColorMap* LColorMap::Instance()
{
	static  LColorMap *instance = new LColorMap();
	return instance;
}

 
/** Get the color in RGB (Red, Gren, Blue) format for a given loglevel
*   level l[in] The level to get the color for
*   @return the RGB color code if a color code exists for this loglevel 
*   othervise the default color which is CYAN*/
int
LColorMap::GetRGB( const eMSGLEVEL l)
{
    if (fMap.find(l) != fMap.end())
    {
        return std::get<1>(fMap.find(l)->second);
    }
    else
    {
        return C_CYAN;
    }
}



/** Get the color in Windows Console Color (CC)  format for a given loglevel
*   level l[in] The level to get the color for
*   @return the CC color code if a color code exists for this loglevel 
*   othervise the default color which is T_CYAN*/
int
LColorMap::GetCColor( const eMSGLEVEL l)
{
    if (fMap.find(l) != fMap.end())
    {
        return std::get<2>(fMap.find(l)->second);
    }
    else
    {
        return  T_CYAN;
    }
}

int
LColorMap::GetAnsiColor(eMSGLEVEL l)
{
    Init();
    if (fMap.find(l) != fMap.end())
    {
        return std::get<3>(fMap.find(l)->second);
    }
    else
    {
        return  A_CYAN;
    }
}

void
LColorMap::Init()
{
      fMap.emplace(eMSGLEVEL::LOG_FORCE_DEBUG, std::make_tuple(string("FORCE_DEBUG"), C_ORANGE, T_ORANGE, A_ORANGE));
      fMap.emplace(eMSGLEVEL::LOG_DEBUG, std::make_tuple(string("DEBUG"), C_CYAN, T_CYAN, A_CYAN));
      fMap.emplace(eMSGLEVEL::LOG_INFO, std::make_tuple(string("INFO"), C_GREEN, T_GREEN, A_GREEN));
      fMap.emplace(eMSGLEVEL::LOG_WARNING, std::make_tuple(string("WARNING"), C_YELLOW, T_YELLOW, A_YELLOW));
      fMap.emplace(eMSGLEVEL::LOG_ERROR, std::make_tuple(string("ERROR"), C_RED, T_RED, A_RED));
      fMap.emplace(eMSGLEVEL::LOG_FATAL, std::make_tuple(string("FATAL"), C_PURPLE, T_PURPLE, A_PURPLE));
      fMap.emplace(eMSGLEVEL::LOG_ALL, std::make_tuple(string("ALL"), C_DARK_GREEN, T_DARK_GREEN, A_DARK_GREEN));
    //    isinitialized = true;
    /*
	fMap.emplace(eMSGLEVEL::LOG_FORCE_DEBUG, std::make_tuple(string("FORCE_DEBUG"), C_ORANGE, T_ORANGE));
   // fMap.emplace(eMSGLEVEL::LOG_DEBUG, std::make_tuple(string("DEBUG"), C_BLUE, T_BLUE));
	fMap.emplace(eMSGLEVEL::LOG_DEBUG, std::make_tuple(string("DEBUG"), C_CYAN, T_CYAN));
    fMap.emplace(eMSGLEVEL::LOG_INFO, std::make_tuple(string("INFO"), C_GREEN, T_GREEN));
    fMap.emplace(eMSGLEVEL::LOG_WARNING, std::make_tuple(string("WARNING"), C_YELLOW, T_YELLOW));
    fMap.emplace(eMSGLEVEL::LOG_ERROR, std::make_tuple(string("ERROR"), C_RED, T_RED));
    fMap.emplace(eMSGLEVEL::LOG_FATAL, std::make_tuple(string("FATAL"), C_PURPLE, T_PURPLE));
    fMap.emplace(eMSGLEVEL::LOG_ALL, std::make_tuple(string("ALL"), C_DARK_GREEN, T_DARK_GREEN));
*/
}
