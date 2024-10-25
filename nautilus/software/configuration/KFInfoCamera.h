// -*- mode: c++ -*-
#pragma once


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <configuration/KFEntityCamera.h>
#include <configuration/KFConfigCamera.h>


#include <memory>

struct KFInfoCamera
{
	std::shared_ptr<KFEntityCamera>        fCamera = nullptr;
	std::shared_ptr<KFConfigCamera>        fCameraConfig = nullptr;
};

