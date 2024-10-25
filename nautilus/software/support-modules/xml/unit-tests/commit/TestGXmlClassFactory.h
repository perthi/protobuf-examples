// -*- mode: c++ -*-

#ifndef TESTGXMLCLASSFACTORY_H
#define TESTGXMLCLASSFACTORY_H


/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/



#include <testlib/TestBase.h>

class TestGXmlClassFactory : public TestBase
{
public:
	virtual void SetUp() override;
	TestGXmlClassFactory();
	~TestGXmlClassFactory();
};

#endif // !TESTGXMLCLASSFACTORY_H