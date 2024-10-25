// -*- mode: c++ -*-

#ifndef LLOGAPI_H
#define LLOGAPI_H

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/


#ifdef _WIN32
#define __func__ __FUNCTION__
#endif

#include <utilities//GDefinitions.h>
#include  <logging/LEnums.h>
#include <logging/LLogging.h>

// #define G_STANDALONE


#ifdef ERROR
#undef ERROR
#endif

#ifdef __cplusplus

#include <utilities/GLocation.h>


#define SET_LOGLEVEL(level)          LLogging::Instance()->SetLogLevel(level )
#define SET_LOGFORMAT(format )       LLogging::Instance()->SetLogFormat(format )
#define SET_LOGTARGET(target )       LLogging::Instance()->SetLogTarget(target )
#define SET_LOGFILENAME(filename)    LLogging::Instance()->SetLogFileName(filename )
#define PUSH()                       LLogging::Instance()->Push(  )
#define POP()                        LLogging::Instance()->Pop(  )

#define LOG_DATA(data, ...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,  eMSGSYSTEM::SYS_DATA,  GLocation( __FILE__, __LINE__, __func__ ), data,  __VA_ARGS__)
#define G_LOG(level, system, ...)    LLogging::Instance()->Log( level, system,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FORCE_DEBUG(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FORCE_DEBUG, eMSGSYSTEM::SYS_GENERAL,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)

#define G_DEBUG(...)                 LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_GENERAL,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_INFO(...)                  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_GENERAL,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_WARNING(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_GENERAL,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_ERROR(...)                 LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_GENERAL,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_FATAL(...)                 LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_GENERAL,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_DEBUG_U(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_GENERAL | eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_INFO_U(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_GENERAL | eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_WARNING_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_GENERAL | eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_ERROR_U(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_GENERAL | eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_FATAL_U(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,	   eMSGSYSTEM::SYS_GENERAL | eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define G_ASSERT_DEBUG(expr, ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_GENERAL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define G_ASSERT_INFO(expr,  ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,       eMSGSYSTEM::SYS_GENERAL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define G_ASSERT_WARNING(expr, ...)  if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_GENERAL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define G_ASSERT_ERROR(expr,  ...)   if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_GENERAL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define G_ASSERT_FATAL(expr,  ...)   if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_GENERAL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)


#define USER_DEBUG(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define USER_INFO(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define USER_WARNING(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define USER_ERROR(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define USER_FATAL(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_USER,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define USER_ASSERT_DEBUG(expr, ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::DEBUG,     eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define USER_ASSERT_INFO(expr,  ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,       eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define USER_ASSERT_WARNING(expr, ...)  if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define USER_ASSERT_ERROR(expr,  ...)   if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define USER_ASSERT_FATAL(expr,  ...)   if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define FSM_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_FSM,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_FSM,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_FSM,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_FSM,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_FSM,   GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_DEBUG_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_FSM  | eMSGSYSTEM::SYS_USER,    GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_INFO_U(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_FSM  | eMSGSYSTEM::SYS_USER,    GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_WARNING_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_FSM  | eMSGSYSTEM::SYS_USER,    GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_ERROR_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_FSM  | eMSGSYSTEM::SYS_USER,    GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_FATAL_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_FSM  | eMSGSYSTEM::SYS_USER,    GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define FSM_ASSERT_DEBUG(expr, ...)    if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_FSM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define FSM_ASSERT_INFO(expr,  ...)     if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,       eMSGSYSTEM::SYS_FSM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define FSM_ASSERT_WARNING(expr, ...)    if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_FSM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define FSM_ASSERT_ERROR(expr,  ...)     if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_FSM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define FSM_ASSERT_FATAL(expr,  ...)     if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_FSM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define ALARM_WARNING(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ALARM,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALARM_ERROR(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ALARM,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALARM_FATAL(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ALARM,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALARM_WARNING_U(...)         LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ALARM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALARM_ERROR_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ALARM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALARM_FATAL_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ALARM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALARM_ASSERT_WARNING(expr, ...)    if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ALARM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ALARM_ASSERT_ERROR(expr,  ...)     if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ALARM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ALARM_ASSERT_FATAL(expr,  ...)     if(!expr) LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ALARM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define EX_ERROR(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_EX,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define EX_FATAL(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_EX,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)

#define MESSAGE_DEBUG(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_INFO(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_WARNING(...)         LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_ERROR(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_FATAL(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_DEBUG_U(...)         LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MESSAGE_INFO_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MESSAGE_WARNING_U(...)       LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER, GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MESSAGE_ERROR_U(...)         LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MESSAGE_FATAL_U(...)         LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MESSAGE_ASSERT_DEBUG(expr, ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_ASSERT_INFO(expr,  ...)     if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_ASSERT_WARNING(expr, ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_ASSERT_ERROR(expr,  ...)     if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MESSAGE_ASSERT_FATAL(expr,  ...)     if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define MSG_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_DEBUG_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MSG_INFO_U(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MSG_WARNING_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER, GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MSG_ERROR_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define MSG_FATAL_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_MESSAGE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS_
#define MSG_ASSERT_DEBUG(expr, ...)     if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_ASSERT_INFO(expr,  ...)     if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_ASSERT_WARNING(expr, ...)   if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_ASSERT_ERROR(expr,  ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define MSG_ASSERT_FATAL(expr,  ...)    if(! (expr) ) LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_MESSAGE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define SEM_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_DEBUG_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SEM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEM_INFO_U(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SEM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEM_WARNING_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SEM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEM_ERROR_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SEM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEM_FATAL_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SEM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEM_ASSERT_DEBUG(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_ASSERT_INFO(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,       eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_ASSERT_WARNING(expr, ...)   if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_ASSERT_ERROR(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEM_ASSERT_FATAL(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SEM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define COM_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_DEBUG_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_COM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define COM_INFO_U(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_COM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define COM_WARNING_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_COM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define COM_ERROR_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_COM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define COM_FATAL_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_COM | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define COM_ASSERT_DEBUG(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,   eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_ASSERT_INFO(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,    eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_ASSERT_WARNING(expr, ...)   if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING, eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_ASSERT_ERROR(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,   eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define COM_ASSERT_FATAL(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,   eMSGSYSTEM::SYS_COM,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define SENSOR_DEBUG(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_INFO(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_WARNING(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_ERROR(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_FATAL(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_DEBUG_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SENSOR | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SENSOR_INFO_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SENSOR | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SENSOR_WARNING_U(...)        LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SENSOR | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SENSOR_ERROR_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SENSOR | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SENSOR_FATAL_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SENSOR | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SENSOR_ASSERT_DEBUG(expr, ...)        if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_ASSERT_INFO(expr, ...)         if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_ASSERT_WARNING(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_ASSERT_ERROR(expr, ...)        if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SENSOR_ASSERT_FATAL(expr, ...)        if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SENSOR,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define HMI_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_DEBUG_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_HMI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define HMI_INFO_U(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_HMI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define HMI_WARNING_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_HMI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define HMI_ERROR_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_HMI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define HMI_FATAL_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_HMI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define HMI_ASSERT_DEBUG(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_ASSERT_INFO(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_ASSERT_WARNING(expr, ...)   if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_ASSERT_ERROR(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define HMI_ASSERT_FATAL(expr, ...)     if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_HMI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define API_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_DEBUG_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_API | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define API_INFO_U(...)              LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_API | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define API_WARNING_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_API | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define API_ERROR_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_API | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define API_FATAL_U(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_API | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define API_ASSERT_DEBUG(expr, ...)           if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_ASSERT_INFO(expr, ...)            if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,      eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_ASSERT_WARNING(expr, ...)         if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,   eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_ASSERT_ERROR(expr, ...)           if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,     eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define API_ASSERT_FATAL(expr, ...)           if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,     eMSGSYSTEM::SYS_API,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define ENGINE_DEBUG(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_INFO(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_WARNING(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_ERROR(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_FATAL(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_DEBUG_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_ENGINE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ENGINE_INFO_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_ENGINE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ENGINE_WARNING_U(...)        LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ENGINE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ENGINE_ERROR_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ENGINE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ENGINE_FATAL_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ENGINE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ENGINE_ASSERT_DEBUG(expr, ...)           if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,     eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_ASSERT_INFO(expr, ...)            if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,      eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_ASSERT_WARNING(expr, ...)         if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,   eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_ASSERT_ERROR(expr, ...)           if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,     eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ENGINE_ASSERT_FATAL(expr, ...)           if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,     eMSGSYSTEM::SYS_ENGINE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define XML_DEBUG(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_INFO(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_WARNING(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_ERROR(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_FATAL(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_DEBUG_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_XML | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define XML_INFO_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_XML | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define XML_WARNING_U(...)        LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_XML | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define XML_ERROR_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_XML | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define XML_FATAL_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_XML | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define XML_ASSERT_DEBUG(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_ASSERT_INFO(expr, ...)       if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_ASSERT_WARNING(expr, ...)    if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_ASSERT_ERROR(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define XML_ASSERT_FATAL(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_XML,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define CLI_DEBUG(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_INFO(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_WARNING(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_ERROR(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_FATAL(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_DEBUG_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_CLI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define CLI_INFO_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_CLI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define CLI_WARNING_U(...)        LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_CLI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define CLI_ERROR_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_CLI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define CLI_FATAL_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_CLI | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define CLI_ASSERT_DEBUG(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_ASSERT_INFO(expr, ...)       if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_ASSERT_WARNING(expr, ...)    if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_ASSERT_ERROR(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define CLI_ASSERT_FATAL(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_CLI,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define SEQUENCE_DEBUG(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_INFO(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_WARNING(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_ERROR(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_FATAL(...)            LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_DEBUG_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SEQUENCE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEQUENCE_INFO_U(...)           LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SEQUENCE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEQUENCE_WARNING_U(...)        LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SEQUENCE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEQUENCE_ERROR_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SEQUENCE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEQUENCE_FATAL_U(...)          LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SEQUENCE | eMSGSYSTEM::SYS_USER,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define SEQUENCE_ASSERT_DEBUG(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_ASSERT_INFO(expr, ...)       if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_ASSERT_WARNING(expr, ...)    if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_ASSERT_ERROR(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define SEQUENCE_ASSERT_FATAL(expr, ...)      if(! (expr) )  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_SEQUENCE,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)

#define ALL_DEBUG(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALL_INFO(...)                LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALL_WARNING(...)             LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALL_ERROR(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALL_FATAL(...)               LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),  __VA_ARGS__)
#define ALL_ASSERT_DEBUG(expr, ...)      if( ! ( expr ))  LLogging::Instance()->Log(eMSGLEVEL::LOG_DEBUG,       eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ALL_ASSERT_INFO(expr, ...)       if( ! ( expr ))  LLogging::Instance()->Log(eMSGLEVEL::LOG_INFO,        eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ALL_ASSERT_WARNING(expr, ...)    if( ! ( expr ))  LLogging::Instance()->Log(eMSGLEVEL::LOG_WARNING,     eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ALL_ASSERT_ERROR(expr, ...)      if( ! ( expr ))  LLogging::Instance()->Log(eMSGLEVEL::LOG_ERROR,       eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)
#define ALL_ASSERT_FATAL(expr, ...)      if( ! ( expr ))  LLogging::Instance()->Log(eMSGLEVEL::LOG_FATAL,       eMSGSYSTEM::SYS_ALL,  GLocation( __FILE__, __LINE__, __func__ ),   __VA_ARGS__)


#endif

#endif
