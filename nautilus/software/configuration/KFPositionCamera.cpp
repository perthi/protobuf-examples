// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "KFPositionCamera.h"

#include <sstream>
#include <iostream>
using std::endl;


string KFPositionCamera::str() const
{
	std::stringstream buffer;
	buffer << "\tleft=\t" << fLeft << endl;
	buffer << "\ttop =\t" << fTop << endl;
	buffer << "\twidth=\t" << fWidth << endl;
	buffer << "\theight=\t" << fHeight << endl;
	return buffer.str();
}
