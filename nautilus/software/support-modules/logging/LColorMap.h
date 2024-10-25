// -*- mode: c++ -*-

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#pragma once



#include "LLogApi.h"
#include <utilities/GDefinitions.h>
#include <utilities/GColor.h>
#include <tuple>
#include <map>
#include <string>

using namespace LOGMASTER;

/**  @brief Color definitions for the logging system  
 *   @details  this class holds information about
 *   which colors various log messages is displayed with when printing them out to the console  */ 
class LColorMap
{
 public:
    static LColorMap API* Instance ();
    std::map<eMSGLEVEL, std::tuple < string, int, int, int > >  const API * GetMap() { return &fMap; }
    int API  GetRGB( const eMSGLEVEL l);
    int API  GetCColor( const eMSGLEVEL l);
    int API GetAnsiColor ( const eMSGLEVEL l);

 private:
    LColorMap();
    ~LColorMap() {};
    void API Init();
    std::map<eMSGLEVEL, std::tuple < string, int, int, int > > fMap;
};
