// -*- mode: c++ -*-
#ifndef TESTKFPROTOBUCOMMAND_H
#define TESTKFPROTOBUCOMMAND_H

#include <testlib/TestBase.h>

class KFPBMessageSEMCommand;

class  TestKFPBMessageSEMCommand : public TestBase
{
public:
  TestKFPBMessageSEMCommand();
    virtual ~ TestKFPBMessageSEMCommand();

    virtual void SetUp()     override;
    virtual void TearDown()  override;

protected:
    KFPBMessageSEMCommand  *fMessage = nullptr;

};

#endif
