// -*- mode: c++ -*-

#ifndef LLogTest_H
#define LLogTest_H

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#include <logging/LLogging.h>
#include <utilities/GDefinitions.h>

using namespace  LOGMASTER;

/**@brief Testing application for the logging system  */
class LLogTest
{
public:
	LLogTest()  {};
	~LLogTest() {};
	static API void WriteMessages();


    static API string file()
    {
        return __FILE__;
    }

    static API void test();

private:	
	static void Header();
	static void Footer();
};

#endif
