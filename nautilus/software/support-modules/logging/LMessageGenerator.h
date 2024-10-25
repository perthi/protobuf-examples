// -*- mode: c++ -*-

#pragma once

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/


#include "LEnums.h"
#include <utilities/GDefinitions.h>
#include <string>
#include <iostream>
using std::string;
using std::ostringstream;

#include <memory>


class TestLogging_level_to_string_Test;
class TestLogging_system_to_string_Test;
class TestLogging_to_string_Test;

namespace LOGMASTER
{
    struct LMessage;
    class LLogging;
    

/** @class  LMessageGenerator
 *  Helper class for the logging system that is responisble for the generation of log messages*/
class LMessageGenerator
{
    friend LLogging;
    friend TestLogging_level_to_string_Test;
    friend TestLogging_system_to_string_Test;
    friend TestLogging_to_string_Test;

public:
    static  LMessageGenerator API * Instance(); // CRAP PTH
    LMessageGenerator();
    ~LMessageGenerator();
      LMessageGenerator( const LMessageGenerator&  rhs );

    //static  LMessage   API *  GetLastMsg();
    std::shared_ptr<LMessage>   API   GetLastMsg();
    std::shared_ptr<LMessage>   API   GenerateMsg( std::shared_ptr<LMessage> msg,  const eMSGFORMAT format, const eMSGLEVEL l,  const eMSGSYSTEM s, const char *fname, int line, const char * func, const char * fmt, va_list ap, string addendum = "" );

private:
   /// LMessageGenerator( const LMessageGenerator&  rhs );
    LMessageGenerator operator = (LMessageGenerator &rhs );
    // static string  API  ToString(const eMSGLEVEL    level);
    // static string  API  ToString(const eMSGSYSTEM   sys);
    // static string  API  ToString(const eMSGSYSTEM sys, const eMSGLEVEL  level );
    // static LMessage *fgMsgLast;
    // static LMessage *fgMsg;

    string  API  ToString(const eMSGLEVEL    level);
    string  API  ToString(const eMSGSYSTEM   sys);
    string  API  ToString(const eMSGSYSTEM sys, const eMSGLEVEL  level );
  //  LMessage *fgMsgLast = nullptr;
  //  LMessage *fgMsg = nullptr;
 
  std::shared_ptr< LMessage>  fgMsgLast = nullptr;
  std::shared_ptr< LMessage>  fgMsg  = nullptr;


};


}
