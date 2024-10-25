// -*- mode: c++ -*-
#ifndef TESTKFPROTOBUFMESSAGE_H
#define TESTKFPROTOBUFMESSAGE_H

#include <testlib/TestBase.h>

class KFPBMessageSEMMessage;

class  TestKFPBMessageSEMMessage : public TestBase
{
public:
  TestKFPBMessageSEMMessage();
    virtual ~ TestKFPBMessageSEMMessage();

    virtual void SetUp()     override;
    virtual void TearDown()  override;

protected:
    KFPBMessageSEMMessage  *fMessage = nullptr;

};

#endif
