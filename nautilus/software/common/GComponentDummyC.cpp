// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "MBMessageInfo.h"
#include "GComponentDummyC.h"
#include <logging/LLogApi.h>
using namespace LOGMASTER;



GComponentDummyC::GComponentDummyC() : GComponent("I am GComponentDummyC") 
{

}


GComponentDummyC::~GComponentDummyC()
{

}


void
GComponentDummyC::ProcessMessageLocal(std::shared_ptr<MBMessageInfo> /*msg*/ )
{
	//	FORCE_DEBUG("recvied message, queue size = %d", fMessageQueue.size() );
	//FORCE_DEBUG("ID = %s",  msg->fMessage->GetMessageID().c_str() );	
}

