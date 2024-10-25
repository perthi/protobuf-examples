// -*- mode: c++ -*-
#pragma once

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/

/* @class GCommon  Helper class for the other utilities classes */

#include <utilities/GCommon.h>
#include <utilities/GException.h>
#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include "GDefinitions.h"
#include "GLocation.h"
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

class GNumbers;
class GUtilities;
class GTokenizer;
class GRandom;
class GString;
class GRegexp;
class GFileIOHandler;


class GCommon;

inline GCommon * g_common();


/** @brief Some common global defines and functions */
class GCommon
{
	friend GNumbers;
	friend GUtilities;
	friend GTokenizer;
	friend GRandom;
	friend GString;
	friend GRegexp;
	friend GFileIOHandler;

public:
	GCommon() {};
	~GCommon() {};

private:
	inline void  HandleError(const string message, const GLocation &l, const bool disable_error);


};




void
#ifdef G_STANDALONE
GCommon::HandleError(const string message, const GLocation &, const bool disable_error)
#else
GCommon::HandleError(const string message, const GLocation & l, const bool disable_error)
#endif
{


    if (disable_error == false)
    {
#ifdef G_STANDALONE
		
	#ifdef _WIN32
		throw( std::exception(message.c_str() ) );
	#else
		throw(std::invalid_argument( message.c_str() ));
	#endif

	//	throw(message);
#else
        throw_exception(   GException(l.fFileName, l.fFunctName, l.fLineNo, SYS_EX, "%s", message.c_str( ))  )  ;
#endif
    }
    else
    {
#ifdef G_STANDALONE
        COUT << message << std::endl;
#else
        G_WARNING(message.c_str());
#endif
    }
}


inline GCommon * g_common()
{
	static GCommon *instance = new GCommon();
	return instance;
}


