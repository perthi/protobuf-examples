// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <string>

using std::string;

#include <iostream>

using  std::end;
using  std::cout;

struct 
KMBPayloadDummyA
{
	KMBPayloadDummyA() {};
	void Hello()
	{
		cout << "Hello from A" << endl;
	}

	string  fDescription;
	double  fPayload;
};
