// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <common/MBMessageT.h>
#include <common/MBEnums.h>

class MBMessageRequest : public MBMessageT<eMESSAGE_REQUEST>
{
public:
	inline MBMessageRequest( const eMESSAGE_REQUEST request,  const string G_s = "Request Message");
	inline ~MBMessageRequest();
};


inline 
MBMessageRequest::MBMessageRequest( const eMESSAGE_REQUEST request, const string G_s ) : MBMessageT<eMESSAGE_REQUEST>(request, G_s)
{

}


inline 
MBMessageRequest::~MBMessageRequest()
{

}
