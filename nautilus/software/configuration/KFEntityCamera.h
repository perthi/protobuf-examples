// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <string>

using std::string;

#include <utilities/GDefinitions.h>
#include "KFEntity.h"



struct KFEntityCamera : public KFEntity
{
	virtual  string API str() const override;
	string fID = "";      //!<  The camera ID
	string fConfigID = ""; //<   The ID of the cameraconfiguration to use for this camera
	string fName = "";  //!<  The name
	bool   fIsEnabled = true;
	string   fIPAddress = "";
	string	fProductID = "";
	string  fCring = "";
};


