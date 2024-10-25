
#pragma once

#include <testlib/TestBase.h>

class APIFSMController;

class TestAPIFSMController : public TestBase
{
public:
	virtual void SetUp() override;
	virtual void TearDown() override;

protected:
	APIFSMController *fController;

};

