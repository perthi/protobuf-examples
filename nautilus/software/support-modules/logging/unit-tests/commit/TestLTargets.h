// -*- mode: c++ -*-

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/


#pragma once

#include <testlib/TestBase.h>


class TestLTargets : public TestBase
{
public:
	TestLTargets();
	~TestLTargets();
	virtual void SetUp() override;
	virtual void TearDown() override;
};

