
#pragma once


/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <testlib/TestBase.h>


class  MBPostOffice;


class TestMBPostOffice : public TestBase
{
public:
///	TestKMBPostOffice();
	virtual void SetUp();
	virtual void TearDown();
	static void SetUpTestCase();

protected:
	static MBPostOffice *po;
};



