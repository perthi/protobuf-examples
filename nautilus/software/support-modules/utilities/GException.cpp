// -*- mode: c++ -*-


/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no>  http:///www.embc.no ***
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


#include "GException.h"
#include  <utilities/GStackTrace.h>
/// #include <utilities/GTokenizer.h>
#include <utilities/GRegexp.h>
#include <utilities/GRegexp.cpp>
#include <utilities/GString.h>
//#include <utilities/GString.cpp>

#include <logging/LLogging.h>
#include <logging/LMessage.h>
#include <logging/LMessageGenerator.h>
#include <logging/LConfig.h>
#include <typeinfo>
#include <string>

using std::string;

#include <cstdarg>

using namespace LOGMASTER;

std::shared_ptr< std::map<eMSGTARGET, std::shared_ptr <LMessage> >  > GException::fgMessageMap = nullptr;
std::shared_ptr<LMessage>   GException::fgMessage = nullptr;


bool  GException::fIsEnabledStackTrace = false;
bool  GException::fIsEnabledException = true;

#include <mutex>
std::mutex exception_mutex;



#define EXCEPTION_CLASS_CPP(classname) classname::classname (const string file, \
					      const string function,	\
					      const int line,\
					      const eMSGSYSTEM system, \
					      const char * fmt, ...) \
    {\
    static va_list ap;\
    va_start(ap, fmt); \
    string msg = string(" (") + ExtractClassname(typeid(*this).name()) + string(")") + (fIsEnabledStackTrace == true ?  + "\n" + string("******* Stack Trace START *******") + "\n" + GStackTrace::str() + "\n" + string("******* Stack Trace END *******") + "\n" : "");  \
    fgMessageMap = LLogging::Instance()->LogVarArgs(eMSGLEVEL::LOG_ERROR, system, file.c_str(), line, function.c_str(), fmt, ap, true, msg ); \
    va_end(ap); 							\
}

///fgMessage = LMessageGenerator::GetMsg();

/**Generating class implementation using a macro for convenience. NB!! These classes must be befriended by the LLogging class since it
calls the private method LLogging::LogVaArgs*/
EXCEPTION_CLASS_CPP(GException)
EXCEPTION_CLASS_CPP(GFileNotFoundException)
EXCEPTION_CLASS_CPP(GRangeException)
EXCEPTION_CLASS_CPP(GInvalidArgumentException)
EXCEPTION_CLASS_CPP(GMissingArgumentException)
EXCEPTION_CLASS_CPP(GFSMException)
EXCEPTION_CLASS_CPP(GComException)
EXCEPTION_CLASS_CPP(GAlarmException)
EXCEPTION_CLASS_CPP(GHMIException)
EXCEPTION_CLASS_CPP(GMessageException)
EXCEPTION_CLASS_CPP(GSensorException)
EXCEPTION_CLASS_CPP(GEngineException)
EXCEPTION_CLASS_CPP(GSEMException)
EXCEPTION_CLASS_CPP(GApiException)
EXCEPTION_CLASS_CPP(GXMLException)
EXCEPTION_CLASS_CPP(GCLIException)
EXCEPTION_CLASS_CPP(GSequenceException)



std::shared_ptr<LMessage>
GException::GetMessageL()
{
    auto test = std::make_shared<LMessage>(); // CRAP PTH
    //LMessage *test = new LMessage();
    return test;
    // return fgMessage;
}


bool
GException::IsEnabledException()
{
	return fIsEnabledException;
}


/**@{
* @brief wether or not to enable exception
*
* If disabled, then the exeption handling system will write
* a fatal log message instead of actually throwing an exception
* which can be usefull for debugging* */
void
GException::EnableException()
{
	fIsEnabledException = true;
}


void GException::DisableException()
{
	fIsEnabledException = false;
}
/**@}*/


bool
GException::IsEnabledStackTrace()
{
	return fIsEnabledStackTrace;
}



/**@{
  * @brief wether or not to enable stack trace
  *
  * If enabled, then a stack trace is added to the exception befor its logged/published vi the
  * logging system. This can be usefull for debugging. By default the stack trace is turned off */
void
GException::EnableStackTrace()
{
    fIsEnabledStackTrace = true;
}


void
GException::DisableStackTrace()
{
	fIsEnabledStackTrace = false;
}
/**@}*/



const char *
GException::what() const
{
    static char  tmp[MAX_MSG_TOTAL_SIZE];

    if ( fgMessageMap != nullptr )
    {
        auto it =fgMessageMap->find(eMSGTARGET::TARGET_EXCEPTION);

        if ( it != fgMessageMap->end() )
        {
            fgMessage = it->second;
            snprintf( tmp, MAX_MSG_TOTAL_SIZE, "%s", fgMessage->fMsg );
        }
    }

    return tmp;
}


/* On Linux using GCC the class name is prefixed with a number
 * on Windows it is prefixed with the name "Class". We need to be
 * consistent between platforms, so we scan the string for a
 * number an replace it with the word "Class" */
inline string
GException::ExtractClassname(const char *in)
{
    string tmp = string(in);
    vector<string> numbers = g_regexp()->ScanNumber(in);
    if(numbers.size() == 0 )
    {
        tmp = string(in);
    }
    else if(numbers.size() >  0 )
    {
        string tmp_r = g_string()->Replace(tmp, numbers[0], "");
        tmp = "class " + tmp_r;
    }

    return tmp;
}
