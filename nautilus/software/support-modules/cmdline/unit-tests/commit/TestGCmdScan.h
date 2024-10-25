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

#include <testlib/TestBase.h>
#include <cmdline/GCommandLineArgument.h>
#include <utilities/GConstants.h>

using namespace GCONSTANTS;

/** @brief unit tests for GCmdScan */
class TestGCmdScan : public TestBase
{
public:
    TestGCmdScan();
    virtual ~ TestGCmdScan();
    virtual void SetUp();
    virtual void TearDown();
    static bool ValidateFunct(const string cmnd, const vector<string> subs, const vector<string> args);


 private:
    TestGCmdScan& operator = ( const TestGCmdScan & );
    TestGCmdScan( const TestGCmdScan & );
    
};

  
