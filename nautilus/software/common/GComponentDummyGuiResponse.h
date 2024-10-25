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
class GComponentDummyGuiResponse :
	public GComponent
{
public:

	API GComponentDummyGuiResponse();
	API virtual ~GComponentDummyGuiResponse();
	virtual void   API     ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg)        override;
	virtual void   API     ProcessMessageBlocking( std::shared_ptr<MBMessageInfo>  msg)      override;

};

