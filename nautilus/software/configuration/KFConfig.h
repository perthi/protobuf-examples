// -*- mode: c++ -*-
#ifndef KFCONFIG_H
#define KFCONFIG_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include <string>
using std::string;

#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>

struct  KFConfig : public GPrintable
{
	API KFConfig();
	virtual API ~KFConfig();
};

#endif
