#pragma once

#include <testlib/TestBase.h>


class TestGLogApplication : public TestBase
{
public:
    API TestGLogApplication();
    API virtual ~TestGLogApplication();
    API virtual void SetUp() override;
    API virtual void TearDown() override;

protected:
   // GLogApplication *fLogApplication = 0;
    string fValidCommands = "cmdline_valid.txt";
    string fNotValidCommands = "cmdline_not_valid.txt";
   

};

