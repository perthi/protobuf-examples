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

class GComponentDummyA : public GComponent
{
public:
	API GComponentDummyA( );
	API ~GComponentDummyA();
	virtual void API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg) override;
};

