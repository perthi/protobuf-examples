// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "MBMessageInfo.h"
#include "GComponentDummyA.h"


#include <logging/LLogApi.h>
using namespace LOGMASTER;

GComponentDummyA::GComponentDummyA() : GComponent("I am GComponentDummyA" )
{

}


GComponentDummyA::~GComponentDummyA()
{

}


void 
GComponentDummyA::ProcessMessageLocal(std::shared_ptr<MBMessageInfo> /*msg*/ ) 
{
	//	FORCE_DEBUG("recvied message, queue size = %d", fMessageQueue.size() );
	//FORCE_DEBUG("ID = %s",  msg->fMessage->GetMessageID().c_str() );
}

