// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <common/FDefinitions.h>

class MBMessagePayload
{
public:
	inline API MBMessagePayload();
	inline virtual API ~MBMessagePayload();
	string fPayloadType = "";
};


inline
MBMessagePayload::MBMessagePayload()
{
}


inline 
MBMessagePayload::~MBMessagePayload()
{
}
