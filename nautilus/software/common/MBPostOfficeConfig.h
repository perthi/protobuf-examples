// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifndef MBMessageSYSTEMINFO_H
#define MBMessageSYSTEMINFO_H


#include "FDefinitions.h"
#include <vector>

class MBPostOfficeConfig
{
public:
	MBPostOfficeConfig();
	~MBPostOfficeConfig();
	static API MBPostOfficeConfig* Instance();
	std::vector<std::string> GetChannels();

private:
	std::vector<std::string> fChannels;

};


#endif // !MBMessageSYSTEMINFO_H
