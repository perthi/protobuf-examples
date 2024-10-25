// -*- mode: c++ -*-

/* ****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
***************************************************************************** */

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



#include "LHashMaps.h"
#include <utilities/GNumbers.h>
#include <utilities/GUtilities.h>


map < string, std::tuple< LOGMASTER::eMSGSYSTEM, LOGMASTER::eMSGLEVEL > >  LOGMASTER::LHashMaps::fSubCmdHash;
map < string, LOGMASTER::eMSGTARGET>	LOGMASTER::LHashMaps::fTargetHash = map < string, LOGMASTER::eMSGTARGET>();
map < string, LOGMASTER::eMSGFORMAT>	LOGMASTER::LHashMaps::fFormatHash;
map < LOGMASTER::eMSGSYSTEM, string >	LOGMASTER::LHashMaps::fSystem2StringHash = map < LOGMASTER::eMSGSYSTEM, string >();
map < LOGMASTER::eMSGLEVEL, string  >	LOGMASTER::LHashMaps::fLevel2StringHash = map < LOGMASTER::eMSGLEVEL, string  >();



namespace LOGMASTER
{
    LHashMaps::LHashMaps( ) : fLogLevelHash(), fDefaultLevel(eMSGLEVEL::LOG_WARNING)
    {
        InitHash( eMSGLEVEL::LOG_WARNING );
    }


    LHashMaps::LHashMaps( const eMSGLEVEL  level) : fLogLevelHash(), fDefaultLevel( level )
    {
        InitHash( level );
    }

    LHashMaps::~LHashMaps()
    {
    }


    LHashMaps *
    LHashMaps::Instance()
    {
        static   LHashMaps *instance = new LHashMaps();
        return   instance;

    }

    void
    LHashMaps::InitHash()
    {
        static bool is_initialized = false;

        if ( is_initialized == false )
        {
            InitHashMsgFormat();
            InitHashLogTargets();
            InitHashLogTags();
            InitHashSystem2String();
            InitHashLevel2String();
            is_initialized = true;
        }

    }

    void
    LHashMaps::InitHash(const eMSGLEVEL level)
    {
        InitHash();
        InitHashLogLevel(level);
        fIsInitialized = true;
    }


    map < string, std::tuple<  eMSGSYSTEM, eMSGLEVEL > >      *
    LHashMaps::GetSubCmdHash()
    {
        InitHash();
        return  &fSubCmdHash;
    }


    map < string, eMSGTARGET>  *
    LHashMaps::GetTargetHash()
    {
        InitHash();
        return  &fTargetHash;
    }

    map < string, eMSGFORMAT>  *
        LHashMaps::GetFormatHash()
    {
        InitHash();
        return  &fFormatHash;
    }


    map<eMSGSYSTEM, string>
        * LHashMaps::GetSystem2StringHash()
    {
        InitHash();
        return &fSystem2StringHash;
    }


    map<eMSGLEVEL, string> *
    LHashMaps::GetLevel2StringHash()
    {
        InitHash();
        return &fLevel2StringHash;
    }


    eMSGTARGET
    LHashMaps::GetTarget( const string & hash )
    {
        InitHash();
        auto it = fTargetHash.find( hash );

        if ( it != fTargetHash.end() )
        {
            return it->second;
        }
        else
        {
            return (eMSGTARGET)0;
        }
    }


    eMSGFORMAT
    LHashMaps::GetFormat( const string & hash )
    {
        InitHash();
        auto it = fFormatHash.find(hash);

        if ( it != fFormatHash.end() )
        {
            return it->second;
        }
        else
        {
            return (eMSGFORMAT)0;
        }

    }


    vector<eMSGTARGET>
    LHashMaps::GetTargetEnums()
    {
        InitHash();
        static vector<eMSGTARGET> tmp;
        static bool is_first = true;

        if ( is_first == true )
        {
            for ( auto it = fTargetHash.begin(); it != fTargetHash.end(); it++ )
            {
                tmp.push_back( it->second );
            }

            is_first = false;
        }

        return tmp;
    }


    vector<eMSGFORMAT>
    LHashMaps::GetFormatEnums()
    {
        InitHash();
        static vector<eMSGFORMAT> tmp;
        static bool is_first = true;

        if ( is_first == true )
        {
            for ( auto it = fFormatHash.begin(); it != fFormatHash.end(); it++ )
            {
                tmp.push_back( it->second );

            }
            is_first = false;
        }
        return tmp;
    }


    vector<eMSGSYSTEM>
    LHashMaps::GetSystemEnums()
    {
        InitHash();
        static vector<eMSGSYSTEM> tmp;
        static bool is_first = true;

        if ( is_first == true )
        {
            for (auto it = fSystem2StringHash.begin(); it != fSystem2StringHash.end(); it++)
            {
                tmp.push_back(it->first );
            }
            is_first = false;
        }

        return tmp;
    }


    vector<eMSGLEVEL>
    LHashMaps::GetLevelEnums()
    {
            InitHash();
            static vector<eMSGLEVEL> tmp;
            static bool is_first = true;

            if ( is_first == true )
            {

        for (auto it = fLevel2StringHash.begin(); it != fLevel2StringHash.end(); it++)
        {
                    tmp.push_back(it->first);
        }

                is_first = false;
            }
            return tmp;
    }




    vector<string>
        LHashMaps::GetLogLevelTags()
    {
            InitHash();
            return g_utilities()->Hash2StringV(&fSubCmdHash);
    }


    vector<string>
    LHashMaps::GetLogTargetTags()
    {
        InitHash();
        return g_utilities()->Hash2StringV(&fTargetHash);
    }


    vector<string>
    LHashMaps::GetLogFormatTags()
    {
        InitHash();
        return g_utilities()->Hash2StringV(&fFormatHash);
    }


    bool
    LHashMaps::IsTargetHash( const string &target )
    {
        InitHash();
        return  fTargetHash.count( target ) > 0 ? true : false;
    }


    bool
    LHashMaps::IsFormatHash( const string &format )
    {
        InitHash();
        return fFormatHash.count( format ) > 0 ? true : false;
    }


    bool
    LHashMaps::IsSubCmdHash( const string &subcmd )
    {
        InitHash();
        return fSubCmdHash.count( subcmd ) > 0 ? true : false;
    }


    string
    LHashMaps::DoxygenDoc(const string filename)
    {
        InitHash();
        FILE *fp;

#ifdef _WIN32
        fopen_s(&fp, filename.c_str(), "w");
#else
        fp =  fopen(filename.c_str(), "w");
#endif

        fprintf(fp, "%s", "/**  \\page \"Logging System\"\n");
        fprintf(fp, "%s", "* \\section command_line_options Command line options for the logging system\n");
        fprintf(fp, "%s", "* Command | Parameters | Default | Explanation \n");
        fprintf(fp, "%s", "* --------- | ---------- | --------- | --------- \n");

        auto t = &fTargetHash;
        auto f = &fFormatHash;
        auto s = &fSubCmdHash;

        fprintf(fp, "%s", "* -target |");
        for (auto it = t->begin(); it != t->end(); it++)
        {
            fprintf(fp, "%s\\n", it->first.c_str());
        }

        fprintf(fp, "%s", " | --file | Where to write the log messages\n");
        fprintf(fp, "%s", "* -format |");

        for (auto it = f->begin(); it != f->end(); it++)
        {
            fprintf(fp, "%s\\n", it->first.c_str());
        }

        fprintf(fp, "%s", " |  1111111 | Options controlling the format of the log messages\n");

        fprintf(fp, "%s", "* -loglevel |");
        for (auto it = s->begin(); it != s->end(); it++)
        {
            fprintf(fp, " %s\\n", it->first.c_str());
        }

        fprintf(fp, "%s", " |  --all-error | Which subsystem / loglevel to log information from\n");
        fprintf(fp, "%s", "*/");
        fclose(fp);
        return string();
    }


    /** @brief initialization of the hash table for the logginglevel
    *
    *  This hash table holds the current logging level for a given sub-system. This table is checked every time the logging system is asked to log a message, and if logging is enabled for the given level
    *  and sub-system then the message is created. Where the message is actuall written (if at all) is decided by the target configuration, wether or not logging is enabled to to file, to console, etc..
    *  @param l  All system are initialized with logging for this level or higher.  */
    void
    LHashMaps::InitHashLogLevel(const eMSGLEVEL l)
    {
            fLogLevelHash.clear();
            eMSGLEVEL level = (eMSGLEVEL)(PAD((int)l));

            fLogLevelHash.emplace(eMSGSYSTEM::SYS_EX,      (eMSGLEVEL)PAD( (int)eMSGLEVEL::LOG_ERROR)  );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_USER,    level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_FSM,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_ALARM,   (eMSGLEVEL)PAD( (int)eMSGLEVEL::LOG_WARNING) );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_MESSAGE, level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_COM,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_HMI,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_SENSOR,  level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_ENGINE,  level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_SEM,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_API,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_XML,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_CLI,     level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_GENERAL, level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_SEQUENCE,level );
            fLogLevelHash.emplace(eMSGSYSTEM::SYS_NONE,    level );

    }


    /** @brief initialization of the hash table for the formatting of the messages,  used  on the command line or via the programming API */
    void
    LHashMaps::InitHashMsgFormat()
    {
        fFormatHash.emplace("--all-off",		eMSGFORMAT::ALL_FIELDS_OFF);
        fFormatHash.emplace("--msg-type",		eMSGFORMAT::MESSAGE_TYPE);
        fFormatHash.emplace("--time-stamp",		eMSGFORMAT::TIME_STAMP);
        fFormatHash.emplace("--time-short",		eMSGFORMAT::TIME_STAMP_SHORT);
        fFormatHash.emplace("--file-path",		eMSGFORMAT::FILE_PATH);
        fFormatHash.emplace("--file-name",		eMSGFORMAT::FILE_NAME);
        fFormatHash.emplace("--func-name",		eMSGFORMAT::FUNCTION_NAME);
        fFormatHash.emplace("--line-no",		eMSGFORMAT::LINE_NO);
        fFormatHash.emplace("--prefix-none",	eMSGFORMAT::PREFIX_OFF);
        fFormatHash.emplace("--msg-body",		eMSGFORMAT::MESSAGE_BODY);
        fFormatHash.emplace("--short",			eMSGFORMAT::SHORT_MSG);
        fFormatHash.emplace("--short-user",		eMSGFORMAT::USER_SHORT_MSG);
        fFormatHash.emplace("--prefix-all",		eMSGFORMAT::PREFIX_ALL);
    }


    /** @brief initialization of the hash table for the logging targets  used  on the command line or via the programming API */
    void
    LHashMaps::InitHashLogTargets()
    {
        fTargetHash.emplace("--target-off",         eMSGTARGET::TARGET_OFF);
        fTargetHash.emplace("--target-file",        eMSGTARGET::TARGET_FILE);
        fTargetHash.emplace("--target-stdout",      eMSGTARGET::TARGET_STDOUT);
        fTargetHash.emplace("--target-subscriber",  eMSGTARGET::TARGET_SUBSCRIBERS);
        fTargetHash.emplace("--target-gui",         eMSGTARGET::TARGET_GUI);
        fTargetHash.emplace("--target-all",         eMSGTARGET::TARGET_ALL);
    }


    void
    LHashMaps::InitHashSystem2String()
    {
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_EX,       "Exeption");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_GENERAL,  "General");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_USER,     "User");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_FSM,      "FSM");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_ALL,      "ALL systems");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_ALARM,    "Alarm");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_MESSAGE,  "Message");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_HMI,      "HMI");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_COM,      "COM");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_SENSOR,   "Sensor");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_ENGINE,   "ControlEngine");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_SEM,      "SEM");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_XML,      "XML");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_CLI,      "CLI");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_SEQUENCE,      "Sequence");
        fSystem2StringHash.emplace(eMSGSYSTEM::SYS_NONE,     "System Unknown");
    }


    void
    LHashMaps::InitHashLevel2String()
    {
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_OFF,         "OFF");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_FATAL,       "Fatal");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_ERROR,       "Error");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_WARNING,     "Warning");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_INFO,        "Info");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_DEBUG,       "Debug");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_FORCE_DEBUG, "Force_Debug");
        fLevel2StringHash.emplace(eMSGLEVEL::LOG_ALL,         "ALL loglevels");
    }


    /** @brief Initialization of hash tags for the logging system used  on the command line or via the programming API
         *
         * The hash table maps between a string tag (i.e --all, --info etc..) and the corresponding logging level and subsystem on binary format.
         * The second entry is a 32 bit integer where the most significant 8 bits represents the loglevel and the least significant 16 bits the the subsystem.
         * The hashmap is static and is initialzed only once. The actual loglevel is contained in the fLogLevelHash hashmap. The loglevel is padded with ones so that if a higher loglevel is
         * set, all lower leves are set. This is typically the behaviour the user expects. For example, if the loglevel is EXCEPTION_CLASS_CPP(GEngineException)set to WARNING, then one would expect
         * to also get messages with higher severity, that is ERROR and FATAL.
         * The padding is done at the end, after the hash map has been poulated.**/
    void
    LHashMaps::InitHashLogTags()
    {
        fSubCmdHash.emplace("--all-off",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--all-fatal",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--all-error",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--all-warning",		std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--all-info",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--all-debug",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--all-all",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_ALL));
        fSubCmdHash.emplace("--all",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_ALL));
        fSubCmdHash.emplace("--off",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--fatal",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--error",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--warning",			std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--info",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--debug",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--all",				std::make_pair(eMSGSYSTEM::SYS_ALL,			eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--ex-fatal",			std::make_pair(eMSGSYSTEM::SYS_EX,			eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--ex-error",			std::make_pair(eMSGSYSTEM::SYS_EX,			eMSGLEVEL::LOG_ERROR));

        fSubCmdHash.emplace("--gen-off",			std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--gen-fatal",			std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--gen-error",			std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--gen-warning",		std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--gen-info",			std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--gen-debug",			std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--gen-all",			std::make_pair(eMSGSYSTEM::SYS_GENERAL,		eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--user-off",			std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--user-fatal",			std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--user-error",			std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--user-warning",		std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--user-info",			std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--user-debug",			std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--user-all",			std::make_pair(eMSGSYSTEM::SYS_USER,		eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--fsm-off",			std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--fsm-fatal",			std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--fsm-error",			std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--fsm-warning",		std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--fsm-info",			std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--fsm-debug",			std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--fsm-all",			std::make_pair(eMSGSYSTEM::SYS_FSM,			eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--message-off",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--message-fatal",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--message-error",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--message-warning",	std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--message-info",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,     eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--message-debug",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--message-all",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--msg-off",			std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--msg-fatal",			std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--msg-error",			std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--msg-warning",		std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--msg-info",			std::make_pair(eMSGSYSTEM::SYS_MESSAGE,     eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--msg-debug",			std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--msg-all",			std::make_pair(eMSGSYSTEM::SYS_MESSAGE,		eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--engine-off",			std::make_pair(eMSGSYSTEM::SYS_ENGINE,		eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--engine-fatal",	    std::make_pair(eMSGSYSTEM::SYS_ENGINE,		eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--engine-error",		std::make_pair(eMSGSYSTEM::SYS_ENGINE,		eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--engine-warning",		std::make_pair(eMSGSYSTEM::SYS_ENGINE,		eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--engine-info",		std::make_pair(eMSGSYSTEM::SYS_ENGINE,      eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--engine-debug",		std::make_pair(eMSGSYSTEM::SYS_ENGINE,		eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--engine-all",			std::make_pair(eMSGSYSTEM::SYS_ENGINE,		eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--sensor-off",         std::make_pair(eMSGSYSTEM::SYS_SENSOR,		eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--sensor-fatal",	    std::make_pair(eMSGSYSTEM::SYS_SENSOR,		eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--sensor-error",		std::make_pair(eMSGSYSTEM::SYS_SENSOR,		eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--sensor-warning",		std::make_pair(eMSGSYSTEM::SYS_SENSOR,		eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--sensor-info",		std::make_pair(eMSGSYSTEM::SYS_SENSOR,      eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--sensor-debug",		std::make_pair(eMSGSYSTEM::SYS_SENSOR,		eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--sensor-all",			std::make_pair(eMSGSYSTEM::SYS_SENSOR,		eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--com-off",			std::make_pair(eMSGSYSTEM::SYS_COM,		    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--com-fatal",	        std::make_pair(eMSGSYSTEM::SYS_COM,		    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--com-error",		    std::make_pair(eMSGSYSTEM::SYS_COM,		    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--com-warning",		std::make_pair(eMSGSYSTEM::SYS_COM,		    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--com-info",		    std::make_pair(eMSGSYSTEM::SYS_COM,         eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--com-debug",		    std::make_pair(eMSGSYSTEM::SYS_COM,		    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--com-all",			std::make_pair(eMSGSYSTEM::SYS_COM,		    eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--hmi-off",			std::make_pair(eMSGSYSTEM::SYS_HMI,		    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--hmi-fatal",	        std::make_pair(eMSGSYSTEM::SYS_HMI,		    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--hmi-error",		    std::make_pair(eMSGSYSTEM::SYS_HMI,		    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--hmi-warning",		std::make_pair(eMSGSYSTEM::SYS_HMI,		    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--hmi-info",		    std::make_pair(eMSGSYSTEM::SYS_HMI,         eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--hmi-debug",		    std::make_pair(eMSGSYSTEM::SYS_HMI,		    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--hmi-all",			std::make_pair(eMSGSYSTEM::SYS_HMI,		    eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--api-off",			std::make_pair(eMSGSYSTEM::SYS_API,		    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--api-fatal",	        std::make_pair(eMSGSYSTEM::SYS_API,		    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--api-error",		    std::make_pair(eMSGSYSTEM::SYS_API,		    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--api-warning",		std::make_pair(eMSGSYSTEM::SYS_API,		    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--api-info",		    std::make_pair(eMSGSYSTEM::SYS_API,         eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--api-debug",		    std::make_pair(eMSGSYSTEM::SYS_API,		    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--api-all",			std::make_pair(eMSGSYSTEM::SYS_API,		    eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--sem-off",			std::make_pair(eMSGSYSTEM::SYS_SEM,		    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--sem-fatal",	        std::make_pair(eMSGSYSTEM::SYS_SEM,		    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--sem-error",		    std::make_pair(eMSGSYSTEM::SYS_SEM,		    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--sem-warning",		std::make_pair(eMSGSYSTEM::SYS_SEM,		    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--sem-info",		    std::make_pair(eMSGSYSTEM::SYS_SEM,         eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--sem-debug",		    std::make_pair(eMSGSYSTEM::SYS_SEM,		    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--sem-all",			std::make_pair(eMSGSYSTEM::SYS_SEM,		    eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--xml-off",			std::make_pair(eMSGSYSTEM::SYS_XML,		    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--xml-fatal",	        std::make_pair(eMSGSYSTEM::SYS_XML,		    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--xml-error",		    std::make_pair(eMSGSYSTEM::SYS_XML,		    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--xml-warning",		std::make_pair(eMSGSYSTEM::SYS_XML,		    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--xml-info",		    std::make_pair(eMSGSYSTEM::SYS_XML,         eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--xml-debug",		    std::make_pair(eMSGSYSTEM::SYS_XML,		    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--xml-all",			std::make_pair(eMSGSYSTEM::SYS_XML,		    eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--cli-off",			std::make_pair(eMSGSYSTEM::SYS_CLI,		    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--cli-fatal",	        std::make_pair(eMSGSYSTEM::SYS_CLI,		    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--cli-error",		    std::make_pair(eMSGSYSTEM::SYS_CLI,		    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--cli-warning",		std::make_pair(eMSGSYSTEM::SYS_CLI,		    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--cli-info",		    std::make_pair(eMSGSYSTEM::SYS_CLI,         eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--cli-debug",		    std::make_pair(eMSGSYSTEM::SYS_CLI,		    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--cli-all",			std::make_pair(eMSGSYSTEM::SYS_CLI,		    eMSGLEVEL::LOG_ALL));

        fSubCmdHash.emplace("--sequence-off",		std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_OFF));
        fSubCmdHash.emplace("--sequence-fatal",	    std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_FATAL));
        fSubCmdHash.emplace("--sequence-error",		std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_ERROR));
        fSubCmdHash.emplace("--sequence-warning",	std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_WARNING));
        fSubCmdHash.emplace("--sequence-info",		std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_INFO));
        fSubCmdHash.emplace("--sequence-debug",		std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_DEBUG));
        fSubCmdHash.emplace("--sequence-all",		std::make_pair(eMSGSYSTEM::SYS_SEQUENCE,    eMSGLEVEL::LOG_ALL));


        //// Padding of the loglevel with ones, so that all loglevesl with a higher severity is applied (if the loglevel is WARNING, then ERROR is also active etc..)
        for (auto it = fSubCmdHash.begin(); it != fSubCmdHash.end(); ++it)
        {
            eMSGLEVEL l = std::get<1>(it->second);
            eMSGLEVEL l_padded = (eMSGLEVEL)PAD(l);
            std::get<1>(it->second) = l_padded;
        }
    }
}


