// -*- mode: c++ -*-
#pragma once

/* *************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#define G_STANDALONE

#include <utilities/GLocation.h>
#include <utilities/GFileName_t.h>
#include <string>

using std::string;



namespace LOGMASTER
{
    class LLoggingInternal
    {
    public:
        static void     API Log(GLocation local, GLocation caller, GFileName_t fname, const string message);
    };

}
