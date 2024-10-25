// -*- mode: c++ -*-

/* ****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
***************************************************************************** */

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

#define G_STANDALONE
#define EXT_DEBUG
#define MAX_STACK_DEPTH 20

#define THREAD_SAFE

#include <logging/LLogging.h>
#include "LMessage.h"
#include "LConfig.h"
#include "LPublisher.h"
#include "LConversion.h"

#include <cstdarg>

#ifdef THREAD_SAFE
#include <mutex>
std::mutex log_mutex;
std::mutex new_mutex;
#endif

namespace LOGMASTER
{
    //std::shared_ptr<std::stack< std::map<eMSGTARGET, LMessageFactory   >  > >   LLogging::fConfigurationStack;
    std::stack<   std::shared_ptr<  std::map<eMSGTARGET,  LMessageFactory   >  >     >  LLogging::fConfigurationStack;

    LLogging *
    LLogging::Instance()
    {
        static LLogging* instance = new LLogging();
        return instance;
    }


    LLogging::LLogging() : fSubscribers(),
                           fGuiSubscribers(),
                           fConfig(nullptr),
                           fDefaultConfig(nullptr),
                           fMessages(nullptr)
    {
        Init();
    }


    LLogging::~LLogging()
    {
        // delete fConfig;
        // delete fDefaultConfig;
        // fConfig = nullptr;
        // fDefaultConfig = nullptr;

        try
        {
            do
            {
                if ( fConfigurationStack.size() > 0 )
                {
                    delete &fConfigurationStack.top();
                    fConfigurationStack.pop();
                }
            } while ( fConfigurationStack.size() > 0 );
        }
        catch ( std::exception& e )
        {
            CERR << ":" << e.what() << endl;

        }
        catch ( ... )
        {
            CERR << ": Unknown exception !!" << endl;
        }
    }

	//  std::shared_ptr<std::map<eMSGTARGET,  LMessageFactory  > >  fConfig = nullptr;
    void
    LLogging::Init()
    {
        fConfig    =            std::make_shared<  std::map<eMSGTARGET,  LMessageFactory  > >();
        fDefaultConfig =        std::make_shared< std::map<eMSGTARGET, LMessageFactory > > ();

		fConfig->emplace(  eMSGTARGET::TARGET_FILE,        LMessageFactory()  ) ;
		fConfig->emplace(  eMSGTARGET::TARGET_STDOUT,      LMessageFactory());
		fConfig->emplace(  eMSGTARGET::TARGET_SUBSCRIBERS, LMessageFactory() );
        fConfig->emplace(  eMSGTARGET::TARGET_GUI,         LMessageFactory() );
        fConfig->emplace(  eMSGTARGET::TARGET_EXCEPTION,   LMessageFactory() );
        fConfig->emplace(  eMSGTARGET::TARGET_TESTING,     LMessageFactory() );

        fDefaultConfig = fConfig;

        SetLogTarget( "--target-off --target-file --target-subscriber --target-stdout --target-gui" );
        SetLogLevel("--all-warning");
        SetLogFormat("--target-gui --all-off --short-user");



       // fMessages = new std::map<eMSGTARGET,  LMessage *  >;
        fMessages =  std::make_shared< std::map<eMSGTARGET,  std::shared_ptr<LMessage>   > >();


        for ( auto it = fConfig->begin(); it != fConfig->end(); it ++ )
        {
            fMessages->emplace( it->first, new LMessage() );
        }
    }


    void
    LLogging::ClearMessages()
    {
        for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
        {
            it->second.GetMessage()->ClearContent();
        }

        for ( auto it = fMessages->begin(); it != fMessages->end(); it++ )
        {
            it->second->ClearContent();
        }
    }


    void
    LLogging::Reset()
    {
#ifdef THREAD_SAFE
        std::lock_guard<std::mutex> guard( log_mutex );
#endif
        fConfig = fDefaultConfig;
        do
        {
            auto c = fConfigurationStack.top();
            // if ( c == fConfig )
            // {
            //     delete c;
            // }

            fConfigurationStack.pop();

        } while ( fConfigurationStack.size() > 0 );
    }







    /** Main logging function that takes a log message, and adds to it the message
     *  type, and the location in the source file where the message was generated.
     *   @param  level  the loglevel/severity of the message
     *   @param  sys    the subsystem the message applies to
     *   @param  l The location of the log  message in the code (filenam, function name line number etc.. )
     *   @param  fmt The formatting for the message (same as the  C style printf formatting)
     *   @param  ...  Variable argument list
     *   @return  The generated log message */
    //std::map<eMSGTARGET,  LMessage *  >	*
    std::shared_ptr< std::map<eMSGTARGET,  std::shared_ptr<LMessage>   > >
    LLogging::Log( const eMSGLEVEL level, const eMSGSYSTEM sys, const GLocation l, const char* fmt... )
    {
        //		static LMessage *msg = new LMessage();
//#ifdef THREAD_SAFE
        std::lock_guard<std::mutex> guard( log_mutex );
///#endif
        va_list ap;
        va_start( ap, fmt );
        auto map = LogVarArgs( level, sys, l.fFileName.c_str(), l.fLineNo, l.fFunctName.c_str(), fmt, ap );
        va_end( ap );
        return map;
    }


    /** Helper function for the main logging (Log) function. The severity("level")
     *  and subsystem  ("system") of the message is checked against the configuration
     *  of the  logging system as given by the assoccicated hash maps. If logging
     *  is enabled for this level and system., then the message is generated and published.
     *   @param  level the loglevel/severity of the message
     *   @param  system the subsystem the message applies to
     *   @param  filename The name of the source code file where the message i created
     *   @param  lineno  The line number where the message is generated
     *   @param  function The name of the function that generated the message
     *   @param  fmt The formatting for the message (same as the  C style printf formatting)
     *   @param  ap  The list of arguments
     *   @param  force_generate Force the generation of message, regardless of the
     *			 loglevel and subystem. This feature is used by the exception handling system
     *			 where one wants the message to be genrated regardless (because you want to
     *			catch the exception with an exception handler). This falf is also usefull for debugging
     *   @param  addendum  optional string to attach to the messag */
    //std::map<eMSGTARGET,  LMessage *  >	*
    std::shared_ptr<std::map<eMSGTARGET,  std::shared_ptr <LMessage>   >	>
    LLogging::LogVarArgs( const eMSGLEVEL level, const eMSGSYSTEM system, const char* filename, const int lineno,
                          const char* function, const char* fmt, va_list ap, const bool force_generate, const string addendum )
    {
//       cerr <<  string(filename) << ":" << string(function) << "[" << lineno << "]" << endl;
 //      std::shared_ptr<std::map<eMSGTARGET,  std::shared_ptr <LMessage>   >	> m;

  //     return m;

       if( fConfig == nullptr )
       {
           CERR << "CONFIG IS A ZERO POINTER" << endl;
           exit(-1);
       }

     //   static  std::mutex l_mutex;
      //  std::lock_guard<std::mutex> guard( l_mutex );

       // static LMessage*           tmp_msg  =  new  LMessage();
     //   static  thread_local std::shared_ptr<LMessage>           tmp_msg  =   std::make_shared<LMessage>();
        static std::shared_ptr<LMessage>           tmp_msg  =   std::make_shared<LMessage>();

        ClearMessages();
        va_list ap_l;
        va_copy(ap_l, ap);

        for ( auto it = fConfig->begin(); it != fConfig->end(); ++it )
        {

            if ( it->second.IsEnabled() == true )
            {
                bool cl = CheckLevel( system, level, it->first );

                if ( (cl == true) || force_generate == true )
                {
                    tmp_msg = it->second.GenerateMessage( system, level, filename, lineno, function, fmt, ap_l, addendum );

                    if ( cl == true )
                    {
                        //	tmp_msg = it->second.GenerateMessage( system, level, filename, lineno, function, fmt, ap, addendum   );

                       /// auto     tmp_msg = it->second.GenerateMessage( system, level, filename, lineno, function, fmt, ap_l, addendum );
                        LPublisher::PublishMessage( tmp_msg, it->second.GetConfig(), it->first );
                        //LPublisher::PublishMessage( tmp_msg, it->second.GetConfig(), target );
                        auto it_msg = fMessages->find(it->first);
                        if ( it_msg != fMessages->end() )
                        {

                            it_msg->second = tmp_msg;
                        }

                    }
                }
            }
        }

        va_end(ap_l);
        return fMessages;
    }


    /** Checks the loglevel of a message issued by the user against the current loglevel configured for the logging system*
     *  @param system  The subsystem this message applies to
     *  @param level   The loglevel (severity) of the message
     *  @param target  Which target (file, stdout, etc..) to check level for
     *   @return true if the message should be generated for this level, false othervise */
    bool
    LLogging::CheckLevel( const eMSGSYSTEM system, const eMSGLEVEL level, const eMSGTARGET target )
    {

        static eMSGLEVEL zero_l = (eMSGLEVEL)0;
        static eMSGSYSTEM zero_s = (eMSGSYSTEM)0;

        if ( level == eMSGLEVEL::LOG_FORCE_DEBUG )
        {
            return true;
        }

        auto it_1 = fConfig->find( target );

        if ( it_1 == fConfig->end() )
        {
            return false;
        }
        else
        {
            auto hash = &it_1->second.GetConfig()->GetHash()->fLogLevelHash;
            auto it = hash->find( system );

            if ( it != hash->end() )
            {
                if ( (it->second & level) != zero_l )
                {
                    return true;
                }
            }
            for ( it = hash->begin(); it != hash->end(); it++ )
            {
                if ( (it->first & system) != zero_s )
                {
                    if ( (level & it->second) != zero_l )
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    }


    void
    LLogging::SetLogTarget( const string& target_s, bool eneable )
    {


#ifdef THREAD_SAFE
        std::lock_guard<std::mutex> guard( log_mutex );
#endif
        vector<eMSGTARGET> e_targets;
        vector<string> tokens  = g_tokenizer()->Tokenize( target_s, vector<string>{" ", "\n","\t" } );

        for ( size_t i = 0; i < tokens.size(); i++ )
        {
            eMSGTARGET e_tmp = LConversion::String2Target(  tokens[i]);

            if ( e_tmp == eMSGTARGET::TARGET_OFF )
            {
                TurnOffAllTargets();
                continue;
            }

            for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
            {
                if ( (e_tmp & it->first) != eMSGTARGET::TARGET_OFF )
                {
                    if(eneable)
                    {
                        it->second.Enable();
                    }
                    else
                    {
                        it->second.Disable();
                    }
                }
            }
        }
    }


    std::shared_ptr<LConfig>
    LLogging::GetConfig( const eMSGTARGET target )
    {
        auto it = fConfig->find( target );

        if ( it != fConfig->end() )
        {
            return it->second.GetConfig();
        }
        else
        {
            return nullptr;
        }
    }


    eMSGTARGET
    LLogging::GetLogTarget() const
    {

        eMSGTARGET tmp = eMSGTARGET::TARGET_OFF;

        for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
        {
            bool b = it->second.IsEnabled();

            if ( b == true )
            {
                tmp = tmp | it->first;
            }
        }

        return tmp;
    }


    eMSGFORMAT
    LLogging::GetLogFormat( const eMSGTARGET target ) const
    {
        auto it = fConfig->find( target );

        if ( it != fConfig->end() )
        {
            return it->second.GetConfig()->GetLogFormat();
        }
        else
        {
            return (eMSGFORMAT)0;
        }
    }


    void
    LLogging::SetLogFileName( const string& filename )
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> guard( mtx );

        auto m = LConversion::SplitByTarget( filename );
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            eMSGTARGET target = it->first;
            for ( auto it2 = fConfig->begin(); it2 != fConfig->end(); it2++ )
            {
                if ( (it2->first & target) != eMSGTARGET::TARGET_OFF )
                {
                    it2->second.GetConfig()->fLogFilename = filename;
                }
            }
        }
    }


    eMSGLEVEL
    LLogging::GetLogLevel( const eMSGSYSTEM system, const eMSGTARGET target ) const
    {
        auto it = fConfig->find( target );

        if ( it != fConfig->end() )
        {
            return it->second.GetConfig()->GetLogLevel( system );
        }

        return eMSGLEVEL::LOG_OFF;
    }


    string
    LLogging::GetLogFileName( const eMSGTARGET target ) const
    {
     //   std::lock_guard<std::mutex> guard( log_mutex );
        auto it = fConfig->find( target );

        if ( it != fConfig->end() )
        {
            return it->second.GetConfig()->fLogFilename;
        }
        else
        {
            return "no such subsystem-found";
        }
    }


    vector< void( *)(const  std::shared_ptr<LMessage>  ) >  &
    LLogging::GetSubscribers()
    {
        return fSubscribers;
    }


    void
    LLogging::SetLogLevel( const string& level_s )
    {
        std::lock_guard<std::mutex> guard( log_mutex );
        auto m = LConversion::SplitByTarget(level_s);

        for ( auto it_m = m.begin(); it_m != m.end(); it_m++ )
        {
            eMSGTARGET target = it_m->first;

            for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
            {
                if ( (it->first & target) != (eMSGTARGET)0 )
                {
                    it->second.GetConfig()->SetLogLevel( it_m->second );
                }
            }
        }
    }


    void
    LLogging::SetLogFormat( const string& f, bool enable)
    {

#ifdef THREAD_SAFE
        std::lock_guard<std::mutex> guard( log_mutex );
#endif

        auto m = LConversion::SplitByTarget(f );

        for ( auto it_m = m.begin(); it_m != m.end(); it_m++ )
        {
            eMSGTARGET target = it_m->first;

            for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
            {
                if ( (it->first & target) != (eMSGTARGET)0 )
                {
                    std::shared_ptr<LConfig> cfg = it->second.GetConfig();
                    cfg->SetLogFormat( it_m->second, enable);
                }
            }
        }
    }


	/** Register a subscriber callbakc function that will be called by the logging system *
	* NB! You must not call the logging itse�f system within a subscriber function s*/
    void
    LLogging::RegisterSubscriber( void( *funct )(const  std::shared_ptr<LMessage>  ) )
    {
      //  std::lock_guard<std::mutex> guard( log_mutex );
        fSubscribers.push_back( funct );
    }


    void
    LLogging::ClearSubscribers()
    {
      ///  std::lock_guard<std::mutex> guard( log_mutex );
        fSubscribers.clear();
    }

    vector<void( *)(const  std::shared_ptr<LMessage>  )> &
    LLogging::GetGuiSubscribers()
    {
        return fGuiSubscribers;
        // TODO: insert return statement here
    }

    void
    LLogging::RegisterGuiSubscriber( void( *funct )(const std::shared_ptr<LMessage>  ) )
    {
      //  std::lock_guard<std::mutex> guard( log_mutex );
        fGuiSubscribers.push_back(funct);
    }


    void
    LLogging::ClearGuiSubscribers()
    {
      //  std::lock_guard<std::mutex> guard( log_mutex );
        fGuiSubscribers.clear();
    }


    int
    LLogging::Push( )
    {
      ///  static std::mutex m;
        std::lock_guard<std::mutex> guard( log_mutex );
       // return 0;
        if ( fConfigurationStack.size() >= MAX_STACK_DEPTH )
        {
            CERR << "stack is full (size = " << fConfigurationStack.size() << ")" << endl;
            return -1;
        }
        else
        {
            fConfigurationStack.push( fConfig );
           // fConfig = new std::map<eMSGTARGET, LMessageFactory >( *fConfig );
            fConfig =  std::make_shared< std::map<eMSGTARGET, LMessageFactory > >( *fConfig );

            return 0;
        }
        return 0;
    }


    int
    LLogging::Pop(  )
    {
       std::lock_guard<std::mutex> guard( log_mutex );
     ///   return 0;
        if ( fConfigurationStack.size() > 0 )
        {
            fConfig = fConfigurationStack.top();
            fConfigurationStack.pop();

            return 0;

        }
        else
        {
            return -1;
        }
    }


    void
    LLogging::TurnOffAllTargets()
    {
    //    std::lock_guard<std::mutex> guard( log_mutex );
        for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
        {

            if ( it->first != eMSGTARGET::TARGET_EXCEPTION  && it->first != eMSGTARGET::TARGET_TESTING )
            {
                it->second.Disable();
            }
        }
    }


    void
    LLogging::TurnOnfAllTargets()
    {
  //     std::lock_guard<std::mutex> guard( log_mutex );
        for ( auto it = fConfig->begin(); it != fConfig->end(); it++ )
        {
            it->second.Enable();
        }
    }

} // namespace LOGMASTER

