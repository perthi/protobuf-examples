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
class GComponentWireTap : public GComponent
{
public:
	API GComponentWireTap();
	virtual API ~GComponentWireTap();

	virtual void   API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  /*msg*/ ) {};

	virtual void   API WireTap( std::shared_ptr<MBMessageInfo>  msg );

};

