// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <utilities/GEnum.h>



G_ENUM( eMESSAGE_REQUEST,
{
	FACTORY_STATUS = 1,
	FSM_STATE = 2,
	FACTORY_CONFIGDATA = 3,
	CONFIG_STORE_DEVICE_SCAN = 4,
	USER_INPUT = 5
} )


G_ENUM( eBLOCKING_ERROR,
{
	DEFERRED = 1,
	TIMEOUT = 2,
	NO_MATCING_CHANNELS = 3,
	NO_SUBSCRIBERS = 4,
	MULTIPLE_SUBSCRIBERS = 5,
	NOT_IMPLEMENTED = 6,
	UNKNOWN = 7,
	INVALID_DATA_TYPE = 8
} )


G_ENUM ( eUSER_RESPONSE,
{
   OK = 1,
   APPLY = 2,
   CANCEL = 3,
   YES = 4,
   NO = 5,
   CONFIRM = 6, 
   ACCECPT = 7,
   CONTINUE = 8
} )



