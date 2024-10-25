
#pragma once

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#include <testlib/TestBase.h>

class GIDGenerator;

class TestGComponentID : public TestBase
{
public:
	TestGComponentID();
	~TestGComponentID();

protected:
	GIDGenerator *fIdGenerator;

};

