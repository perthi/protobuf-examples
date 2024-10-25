// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include  "MBMessage.h"
#include  "MBMessagePayload.h"
#include  "MBMessagePayloadT.h"
#include  <memory>

template<class T>
class MBMessageT : public MBMessage
{
public:
	MBMessageT(T message, const string G_s = "");
};


template<class T>
inline MBMessageT<T>::MBMessageT(T  message, const string G_s ) : MBMessage(G_s)
{
	fPayload = std::dynamic_pointer_cast<MBMessagePayload>(std::make_shared<MBMessagePayloadT<T> >( message) );
	G_ASSERT_EXCEPTION( fPayload != nullptr, "dynamic cast failes, fPayload is  ZERO pointer" );
}

