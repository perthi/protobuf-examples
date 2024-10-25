// -*- mode: c++ -*-

#pragma once


/** @class LOGMASTER::LLogging
 *  @brief The main logging class providing interfaces for generation of logmessages. This class is tyically called via the interfaces defined in LLogApi.h/CPP */

#define G_STANDALONE


/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#include <utilities/GLocation.h>
#include <logging/LMessageFactory.h>

#include <string>
#include <stack>
#include <vector>
#include <map>

#include <memory>


using std::string;
using std::vector;
using std::map;


class TestLConfig_target_all_Test;
class TestLConfig_default_setting_Test;
class TestLogging_levels_Test;
class TestCheckLevel_check_level_Test;


namespace LOGMASTER
{
    struct LMessage;

    class LLogging
    {
        friend TestLConfig_target_all_Test;
        friend TestLConfig_default_setting_Test;
        friend TestLogging_levels_Test;
        friend TestCheckLevel_check_level_Test;

    public:
        ~LLogging();
        static LLogging			API *	Instance();
        std::shared_ptr< std::map<eMSGTARGET,  std::shared_ptr<LMessage>  >	>	API 	Log(const eMSGLEVEL level, const eMSGSYSTEM sys,  const GLocation l , const char * fmt, ...);

        std::shared_ptr< std::map<eMSGTARGET,  std::shared_ptr<LMessage>  >  >	API 	LogVarArgs(	const eMSGLEVEL level, const eMSGSYSTEM system, const char * filename, const int linenumber,
                                                                        const char * functionname, const char *fmt, va_list ap, 
                                                                        const bool force_generate = false, string addendum = "");
        

        void					API		SetLogFormat(   const  string  &format, bool enable = true);
        void					API		SetLogLevel( const  string  &level);
        void					API		SetLogTarget(   const  string  &target, bool eneable = true);
        void					API		SetLogFileName( const string &filename );
		
        eMSGTARGET				API		GetLogTarget()  const;
        eMSGFORMAT				API		GetLogFormat(   const eMSGTARGET target) const;
        std::shared_ptr<LConfig> API 	GetConfig(  const eMSGTARGET target);
        eMSGLEVEL				API		GetLogLevel(const eMSGSYSTEM system, const eMSGTARGET  target) const;
        string					API		GetLogFileName(const eMSGTARGET  target = eMSGTARGET::TARGET_FILE ) const;
		
        vector< void( *)(const std::shared_ptr<LMessage>  ) >  API & GetSubscribers();
        void					API		RegisterSubscriber(  void(  *funct)(const std::shared_ptr<LMessage>   ));
        void					API		ClearSubscribers();

        vector< void( *)(const  std::shared_ptr<LMessage> ) >  API & GetGuiSubscribers();
        void					API		RegisterGuiSubscriber(  void(  *funct)(const  std::shared_ptr<LMessage>  ));
        void					API		ClearGuiSubscribers();

        void					API		Reset();
        int						API		Push( );                                    
        int						API		Pop( );
        bool					API		CheckLevel(const eMSGSYSTEM system, const eMSGLEVEL level, const eMSGTARGET target);

    private:
        LLogging();
        LLogging( LLogging & );
		
        void	Init();
        void    ClearMessages();
        void    TurnOffAllTargets();
        void    TurnOnfAllTargets();
        void	operator=(LLogging &);
        
        vector< void(*)(const std::shared_ptr<LMessage>   ) > fSubscribers;
        vector< void(*)(const std::shared_ptr<LMessage>   ) > fGuiSubscribers;

        std::shared_ptr<std::map<eMSGTARGET,  LMessageFactory  > >  fConfig = nullptr;
        std::shared_ptr<std::map<eMSGTARGET, LMessageFactory > >   fDefaultConfig = nullptr;
        std::shared_ptr<std::map<eMSGTARGET, std::shared_ptr<LMessage> > > fMessages = nullptr;

        static std::stack<   std::shared_ptr<  std::map<eMSGTARGET,  LMessageFactory   >  >     >  fConfigurationStack;
    };

}

