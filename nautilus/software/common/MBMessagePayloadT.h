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
#include "MBMessagePayload.h"
#include <memory>


template <class T>
class MBMessagePayloadT : public MBMessagePayload

{
public:
	API MBMessagePayloadT(T  );
	API virtual ~MBMessagePayloadT();
	API virtual void Test() {};
	std::shared_ptr<T>   fPayload;

};


template<class T>
inline MBMessagePayloadT<T>::MBMessagePayloadT(T in)
{
	fPayload =   std::make_shared<T>(in);
	fPayloadType = string( typeid(T).name() ) ;
}


template<class T>
inline MBMessagePayloadT<T>::~MBMessagePayloadT()
{

}



