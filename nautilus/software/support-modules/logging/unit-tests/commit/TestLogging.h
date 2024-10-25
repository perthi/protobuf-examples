// -*- mode: c++ -*-

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/


#pragma once


#include <testlib/TestBase.h>
#include <cmdline/GLogApplication.h>
#include <sstream>

namespace LOGMASTER
{
    struct LMessage;
}

class TestLogging :public TestBase
 //   public testing::Test
{
public:
    TestLogging();
    virtual ~TestLogging();
	static void SetUpTestCase();
    virtual void SetUp();
    virtual void TearDown();


protected:
    static void Subscriber(const std::shared_ptr<LOGMASTER::LMessage>   msg );
    static std::streambuf* fOldBuf;
    static std::ostringstream fStrCout;
    static string fMessage;
};

