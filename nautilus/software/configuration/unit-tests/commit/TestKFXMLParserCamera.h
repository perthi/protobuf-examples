// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFXML.h"

#include <testlib/TestBase.h>
struct KFEntityDeviceCamera;
struct KFConfigCamera;

#include <memory>
#include <vector>

#include <configuration/KFXMLParserCamera.h>


class TestKFXMLParserCamera : public  TestKFXML
{
protected:
	static void SetUpTestCase();
    vector< std::shared_ptr<KFEntityCamera> > fCameras_v;
    vector< std::shared_ptr<KFConfigCamera> > fConfig_v;

	KFXMLParserCamera p;
};
