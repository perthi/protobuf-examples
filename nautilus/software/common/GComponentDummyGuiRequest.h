// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "MBMessageInfo.h"
#include "GComponent.h"


class GComponentDummyGuiRequest : public GComponent
{
public:
	API GComponentDummyGuiRequest();
	API ~GComponentDummyGuiRequest();

private:
	virtual void API ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg) override;
//	virtual std::shared_ptr<MBMessage>		API	 	SendMessageBlocking(MBMessage  &msg, const string channel, const uint32_t timeout) override;

};

