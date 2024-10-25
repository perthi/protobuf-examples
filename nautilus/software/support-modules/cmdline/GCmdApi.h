// -*- mode: c++ -*-

#pragma once

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


#include <utilities/GDefinitions.h>
#include <vector>
#include <string>
using std::vector;
using std::string;

/** @brief scanning of boolean argumenst (used by the command line system )*/
class GCmdApi
{
public:
    GCmdApi();
    virtual ~GCmdApi();
    static bool API bool2( const string cmnd, const string args_s, const vector<string> subs, const vector<string> args);
};

