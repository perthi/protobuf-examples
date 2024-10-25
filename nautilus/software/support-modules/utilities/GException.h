// -*- mode: c++ -*-


#ifndef EXCEPTION_H
#define EXCEPTION_H

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

///#include <utilities/GDefinitions.h>
#include <logging/LMessage.h>
#include <logging/LLogApi.h>
#include <logging/LLogging.h>

using namespace LOGMASTER;

#include <string>
using std::string;

#include <memory>


/** @brief custom execeptions that uses the logging system
 *
 *  @details Throws exceptions using printf formatting. The exeption handling system uses the logging system so that
 * any execptions thrown are also written to logfiles or standard output if the loglevel is ERROR or higher.
 * From the point of view of the logging system an execption message is just like any other logging message with the
 * following specifications
 *  - loglevel is ERROR
 *  - sub system is either
 *    -# SYS_EXCEPTION
 *    -# SYS_EXCEPTION  | "<any other sub-system>""
 *
 * The execptions can be disabled for debugging purposes. If disabled then a EX_FATAL exception message is written
 * insted of throwing an exception when calling an exception macro. */
class  GException
{
public:
    API GException() {};
    API GException(const string file, const string function, const int line, const eMSGSYSTEM system, const char * fmt, ...);

    virtual API ~GException()
    {

    }

    static std::shared_ptr<LOGMASTER::LMessage> API  GetMessageL();
    static bool API IsEnabledException();
    static void API EnableException();
    static void API DisableException();
    static bool API IsEnabledStackTrace();
    static void API EnableStackTrace();
    static void API DisableStackTrace();
    const char  API * what() const;
    static string API ExtractClassname(const char *in);

protected:
    static std::shared_ptr< std::map<eMSGTARGET, std::shared_ptr<LMessage > > > fgMessageMap;
    static std::shared_ptr<LOGMASTER::LMessage>  fgMessage;
    static bool fIsEnabledStackTrace; /* !< If set to true then a stack trace is included in the log message for the exception. This can be usefull for debugging. Default is FALSE*/
    static bool fIsEnabledException;  /* !< If set to FALSE then a fatal error message is written instead of throwing an exception */

};


#define EXCEPTION_CLASS_H(classname)  class classname : public GException \
 {                                                                     \
 public:                                                               \
     classname() { };                                                \
     API classname(const string file, const string function, const int line, const eMSGSYSTEM system, const char * fmt, ... ); \
   virtual ~classname() { };                                      \
};



/** Macro defintions of Exception classes */
EXCEPTION_CLASS_H(GFileNotFoundException)
EXCEPTION_CLASS_H(GInvalidArgumentException)
EXCEPTION_CLASS_H(GMissingArgumentException)
EXCEPTION_CLASS_H(GRangeException)
EXCEPTION_CLASS_H(GFSMException)

EXCEPTION_CLASS_H(GAlarmException)
EXCEPTION_CLASS_H(GComException)
EXCEPTION_CLASS_H(GHMIException)
EXCEPTION_CLASS_H(GMessageException)
EXCEPTION_CLASS_H(GSensorException)
EXCEPTION_CLASS_H(GEngineException)
EXCEPTION_CLASS_H(GSEMException)
EXCEPTION_CLASS_H(GApiException)
EXCEPTION_CLASS_H(GXMLException)
EXCEPTION_CLASS_H(GCLIException)
EXCEPTION_CLASS_H(GSequenceException)

template<typename T>
void throw_exception(const T &e)
{
    if (GException::IsEnabledException() == true)
    {
        throw(e);
    }
    else
    {
        //    COUT << "writing message" << endl;
        EX_FATAL("Fatal condition that would have resultetd in an exception, but exceptions was switched off !!");
        EX_FATAL("%s", e.what());
    }
}


#define EXCEPTION(...)                     throw_exception( GException(                 __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_EX,       __VA_ARGS__ ) )
#define RANGE_EXCEPTION(...)               throw_exception( GRangeException(            __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_EX,       __VA_ARGS__ ) )
#define FILE_NOT_FOUND_EXCEPTION(...)      throw_exception( GFileNotFoundException(     __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_EX,       __VA_ARGS__ ) )
#define INVALID_ARGUMENT_EXCEPTION(...)    throw_exception( GInvalidArgumentException(  __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_EX,       __VA_ARGS__ ) )
#define MISSING_ARGUMENT_EXCEPTION(...)    throw_exception( GMissingArgumentException(  __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_EX,       __VA_ARGS__ ) )
#define COM_EXCEPTION(...)                 throw_exception( GComException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_COM,      __VA_ARGS__ ) )
#define FSM_EXCEPTION(...)                 throw_exception( GFSMException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_FSM,      __VA_ARGS__ ) )
#define ALARM_EXCEPTION(...)               throw_exception( GAlarmException(            __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_ALARM,    __VA_ARGS__ ) )
#define HMI_EXCEPTION(...)                 throw_exception( GHMIException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_HMI,      __VA_ARGS__ ) )
#define MESSAGE_EXCEPTION(...)             throw_exception( GMessageException(          __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_MESSAGE,  __VA_ARGS__ ) )
#define SENSOR_EXCEPTION(...)              throw_exception( GSensorException(           __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_SENSOR,   __VA_ARGS__ ) )
#define ENGINE_EXCEPTION(...)              throw_exception( GEngineException(           __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_ENGINE,   __VA_ARGS__ ) )
#define SEM_EXCEPTION(...)                 throw_exception( GSEMException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_SEM,      __VA_ARGS__ ) )
#define API_EXCEPTION(...)                 throw_exception( GApiException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_API,      __VA_ARGS__ ) )
#define XML_EXCEPTION(...)                 throw_exception( GXMLException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_XML,      __VA_ARGS__ ) )
#define CLI_EXCEPTION(...)                 throw_exception( GCLIException(              __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_CLI,      __VA_ARGS__ ) )
#define SEQUENCE_EXCEPTION(...)            throw_exception( GSequenceException(         __FILE__,  __func__, __LINE__ , eMSGSYSTEM::SYS_SEQUENCE, __VA_ARGS__ ) )


#define G_ASSERT_EXCEPTION(expr, ...)          if(!(expr)) throw_exception( GException(          __FILE__,  __func__, __LINE__ ,    eMSGSYSTEM::SYS_EX , __VA_ARGS__ ) )
#define FSM_ASSERT_EXCEPTION(expr, ...)        if(!(expr)) throw_exception( GFSMException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_FSM ),      __VA_ARGS__  ) )
#define ALARM_ASSERT_EXCEPTION(expr, ...)      if(!(expr)) throw_exception( GAlarmException(     __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_ALARM ),    __VA_ARGS__  ) )
#define MESSAGE_ASSERT_EXCEPTION(expr, ...)    if(!(expr)) throw_exception( GMessageException(   __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_MESSAGE ),  __VA_ARGS__  ) )
#define MSG_ASSERT_EXCEPTION(expr, ...)        if(!(expr)) throw_exception( GMessageException(   __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_MESSAGE ),  __VA_ARGS__  ) )
#define COM_ASSERT_EXCEPTION(expr, ...)        if(!(expr)) throw_exception( GComException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_COM),       __VA_ARGS__  ) )
#define HMI_ASSERT_EXCEPTION(expr, ...)        if(!(expr)) throw_exception( GHMIException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_HMI),       __VA_ARGS__  ) )
#define SENSOR_ASSERT_EXCEPTION(expr, ...)     if(!(expr)) throw_exception( GSensorException(    __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_SENSOR),    __VA_ARGS__  ) )
#define ENGINE_ASSERT_EXCEPTION(expr, ...)     if(!(expr)) throw_exception( GEngineException(    __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_ENGINE),    __VA_ARGS__  ) )
#define SEM_ASSERT_EXCEPTION(expr, ...)        if(!(expr)) throw_exception( GSEMException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_SEM),       __VA_ARGS__  ) )
#define API_ASSERT_EXCEPTION(expr, ...)         if(!(expr)) throw_exception( GApiException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_API),       __VA_ARGS__  ) )
#define XML_ASSERT_EXCEPTION(expr, ...)         if(!(expr)) throw_exception( GXMLException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_XML),       __VA_ARGS__  ) )
#define CLI_ASSERT_EXCEPTION(expr, ...)         if(!(expr)) throw_exception( GCLIException(       __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_CLI),       __VA_ARGS__  ) )
#define SEQUENCE_ASSERT_EXCEPTION(expr, ...)    if(!(expr)) throw_exception( GSequenceException(  __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_SEQUENCE),  __VA_ARGS__  ) )

//#define MESSAGE_ASSERT_EXCEPTION(expr, ...)        if(!(expr)) throw_exception( GEngineException(    __FILE__,  __func__, __LINE__ ,	( eMSGSYSTEM)(  eMSGSYSTEM::SYS_EX |  eMSGSYSTEM::SYS_MESSAGE),    __VA_ARGS__  ) )


#endif
