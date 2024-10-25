// -*- mode: c++ -*-

#ifndef TESTGXMLVALIDATORIMPL_H
#define TESTGXMLVALIDATORIMPL_H

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/



#include <testlib/TestBase.h>
#include <string>

using std::string;

class TestGXmlValidatorImpl : public TestBase
{
    protected:
        static void SetUpTestCase();

        static string fDataDir;

};

#endif // !TESTGXMLVALIDATORIMPL_H
