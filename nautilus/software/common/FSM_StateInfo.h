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
#include <vector>
using std::vector;

/*  @struct FSM_StateInfo
 *  Container to store infomration about a state */

struct FSM_StateInfo
{
	string fName;             //!< The name of the state
	vector<string> fActions;  //!< List of valid actions for this state
	int fColor;               //!< Color code in  RGB format  e.g 0xRRGGBB
};

