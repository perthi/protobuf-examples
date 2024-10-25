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




class GComponentDummyB : public GComponent
{
public:
	API GComponentDummyB( );
	API ~GComponentDummyB();

private:
	virtual void API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg) override;
};

