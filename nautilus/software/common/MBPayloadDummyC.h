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



struct KMBPayloadDummyC
{
	void Hello()
	{
		cout << "Hello from C" << endl;
	}

	string  fDescription;
	char	fPayload[256];
};
