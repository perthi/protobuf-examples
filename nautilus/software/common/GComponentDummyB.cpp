// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "MBMessageInfo.h"
#include "GComponentDummyB.h"

#include <logging/LLogApi.h>
using namespace LOGMASTER;


GComponentDummyB::GComponentDummyB( ) : GComponent( "I am GComponentDummyB" )
{

}


GComponentDummyB::~GComponentDummyB()
{

}

void 
GComponentDummyB::ProcessMessageLocal(std::shared_ptr<MBMessageInfo> /*msg*/ )
{
	//FORCE_DEBUG("recvied message, queue size = %d", fMessageQueue.size() );
	///FORCE_DEBUG("ID = %s",  msg->fMessage->GetMessageID().c_str() );
}


