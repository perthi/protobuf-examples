// -*- mode: c++ -*-

#pragma once

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/



/** @class LOGMASTER::LValidateArgs 
*   @brief Functions for validation of commandline arguments for the logging system.
*
*   This class provide functions that verifies that sub-parameters and sub-commands used with te 3 main swicthces "-loglevel",  "-logtarget" and "-logformat"
*   are legal ones. For instance, if the command line is -loglevel \<subcommand\> then it is checked that \<subcommand\>  is present in the hash table of valid
*   subcommands. These functins are called automatically by the command line handling system*/

//#include <common/include/KGDefinitions.h>
#include <utilities/GDefinitions.h>
#include <logging/LEnums.h>
#include <vector>
#include <string>


using std::string;
using std::vector;


namespace LOGMASTER
{
    class LLogging;

   
    class LValidateArgs
    {
        friend LLogging;
        
    public:
        LValidateArgs();
        ~LValidateArgs();
        static bool        API CAPIValidateSubCommands( const string cmd,  const string args_s,  const vector<string> level,    const vector<string> pars = vector<string>() );
        static bool        API CAPIValidateTargets    ( const string cmd,  const string args_s,  const vector<string> targets,  const vector<string> pars = vector<string>() );
        static bool        API CAPIValidateFormat     ( const string cmd,  const string args_s,  const vector<string> targets,  const vector<string> pars = vector<string>() );
    };

}

