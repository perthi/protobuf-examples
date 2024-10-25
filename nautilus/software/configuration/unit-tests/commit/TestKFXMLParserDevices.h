// -*- mode: c++ -*-
#ifndef TESTKFXMLPARSERDEVICES_H
#define TESTKFXMLPARSERDEVICES_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/


#include "TestKFXML.h"
#include <testlib/TestBase.h>


class  KFXMLParserDevices;
class  KFConfigurationHandler;


class  TestKFXMLParserDevices : public  TestKFXML
{
protected:
    static  void    SetUpTestCase();
	static  void    TearDownTestCase();
    virtual void    SetUp()     override;
    virtual void    TearDown()  override;
};


#endif
