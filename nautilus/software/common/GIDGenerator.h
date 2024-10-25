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

#include <utilities/GSystem.h>
#include <utilities/GString.h>
#include <utilities/GTime.h>
#include <utilities/GNumbers.h>

#include <string>

using std::string;


/** @brief generate unique identification strings*/
class GIDGenerator
{
public:
	static GIDGenerator API * Instance();
	string API CreateUniqueID( const string prefix ) const;

private:
	API GIDGenerator();
	API ~GIDGenerator();
};


