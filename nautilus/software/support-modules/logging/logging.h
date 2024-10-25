// -*- mode: c++ -*-
#pragma once


#ifdef __cplusplus
#include <logging/LLogApi.h>
#include <logging/LMessage.h>
using namespace  LOGMASTER;
#else
#include "LLogApi.h"
#include "LMessage.h"
#endif

#ifdef __cplusplus

extern "C" { //Her we specify C linkage in order to be able to call the enclosed functions from a DLL


#endif

#ifdef LOGGINGDLL_EXPORTS
#define K_API  __declspec(dllexport) 
#else
#define K_API __declspec(dllimport) 
#endif
    int    K_API   set_loglevel(    const char *loglevel );
    int    K_API   set_logtarget(   const char *target   );
    int    K_API   set_logformat(   const char *format,  eMSGTARGET target );
    int    K_API   set_logfilename( const char *filename   );
    void   K_API   log_test(void);
#ifdef __cplusplus
    void  K_API   register_subscriber(void(*funct)(const LMessage *const));
#else
    void  K_API   register_subscriber(void(*funct)(const struct LMessage *const));
#endif
    int  K_API    push(void);  // push current log configuration onto the stack
    int  K_API    pop(void);   // pop the previous log configuration


#ifdef __cplusplus

}
#endif



