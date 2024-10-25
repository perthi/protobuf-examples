// -*- mode: c++ -*-

#pragma once


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <utilities/GDefinitions.h>
#include <utilities/GPrintable.h>

struct KFPositionCamera : public GPrintable
{
	virtual  string API str() const override;

	int fLeft = 0;
	int fTop = 0;
	int fWidth = 0;
	int fHeight = 0;

};
