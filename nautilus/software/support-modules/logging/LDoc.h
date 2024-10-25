// -*- mode: c++ -*-

#pragma once
/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


/** @class LOGMASTER::LDoc
*   @brief Class that provides brief documentation, written to the console, for the logging system  
*   
*Basic documentation for the loggings system that is written out to the console 
*   There are 3 main switches for the logging system (please refer to user documentation in Confluence for details ) 
*   -  - -loglevel
*   -  - -logtarget
*   -  - -logformat 
* <br>
*  If any of these command line switches are used incorrectly then this class provides a help menu that is written out to the console */



#include <logging/LLogApi.h>
#include <utilities/GDefinitions.h>
#include <string>
using std::string;
#include <map>
using std::map;


namespace LOGMASTER
{
    class LDoc
    {
    public:
        inline static LDoc *  Instance();
        string      API logLevelDoc();
        string      API logTargetDoc();
        string      API logFormatDoc();
        void        API  PrintLogLevels(bool toconsole = false);
        string      Help();
        string      UsageError(const string cmnd, const string sub, map <string, std::tuple<  eMSGSYSTEM, eMSGLEVEL > > m);
        
 //   private:
        LDoc() {};  // never used
        ~LDoc(); // never used
    };

    

    LDoc *
        LDoc::Instance()
    {
        static LDoc *instance = new LDoc();
        return instance;
    }

     
}
