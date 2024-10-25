// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GComponentDummyGuiRequest.h"



GComponentDummyGuiRequest::GComponentDummyGuiRequest() : GComponent("Dummy GUI Request")
{

}


GComponentDummyGuiRequest::~GComponentDummyGuiRequest()
{

}


void 
GComponentDummyGuiRequest::ProcessMessageLocal(std::shared_ptr<MBMessageInfo>  /*msg*/ )
{

}



/*
std::shared_ptr<MBMessage>	
GComponentDummyGuiRequest::SendMessageBlocking(MBMessage  &msg, const string channel, const uint32_t timeout)
{
	uint32_t lTimeout = timeout;
	string ch = channel;

	MBMessage  lmsg = msg;
}
*/
