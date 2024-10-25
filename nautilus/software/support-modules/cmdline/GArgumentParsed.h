// -*- mode: c++ -*-
#ifndef PARSEDGArgument_H
#define PARSEDGArgument_H

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


#include "GArgument.h"
#include <utilities/GDefinitions.h>
#include <vector>
#include <string>
using std::vector;
using std::string;


/** @brief Helper class for the commanline system. Holds the argument after parsing. The commandline argumen is parsed according to 
 *  tokens beginning with "-". Subcommands are identified with the "--" and parameters is assumed to be
 *  anything that doesn start with "-" or "--" 
 * 
 * example: -myarg1 --sub1 --sub2 1 2 3 -myarg2 --sub3 --sub3 4 5 6 wil genrate two instances of
 * GArgumentParsed
 *  - First argument:    -myarg1 vector<string>{--sub1, --sub2} vector<string>{"1","2","3"}
 *  - Second argument:   -myarg2 vector<string>{--sub2, --sub3} vector<string>{"4","5","6"} */
class GArgumentParsed : public GArgument
{
public:
    GArgumentParsed() : fArguments() { }
    void AddParameter( const string par) {   fArguments.push_back(par); } ;
    string ParInfo( const vector<string> par ) const;
    virtual string    API str()   const;
    vector<string> GetArguments() const { return fArguments; } ;
  
private:
    vector<string> fArguments;
};


#endif

