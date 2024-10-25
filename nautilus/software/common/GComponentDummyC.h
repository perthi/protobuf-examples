// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GComponent.h"


class GComponentDummyC : public GComponent
{
public:
	API GComponentDummyC();
	API ~GComponentDummyC();
	virtual void API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg);
};

