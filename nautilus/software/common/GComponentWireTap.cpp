// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GComponentWireTap.h"
#include <common/MBPostOffice.h>
#include <common/MBMessageInfo.h>


GComponentWireTap::GComponentWireTap() : GComponent("WIRE_TAP")
{
	std::function< void( std::shared_ptr<MBMessageInfo> msg ) >   funct( std::bind( &GComponentWireTap::WireTap, this, std::placeholders::_1 ) );
	MBPostOffice::Instance()->SetWireTap( funct );
}


GComponentWireTap::~GComponentWireTap()
{

}


void 
GComponentWireTap::WireTap( std::shared_ptr<MBMessageInfo> msg )
{
	static int cnt = 0;
	

	if ( cnt % 100 == 0 )
	{
		FORCE_DEBUG( "recived %d messages in wire tap (component id = %s\tmsg id = %s)",  
			cnt, msg->fMessage->fComponentID.c_str(), msg->fMessage->fMessageID.c_str() );
	}

	cnt++;

}
