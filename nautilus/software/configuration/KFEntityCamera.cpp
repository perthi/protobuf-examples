// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "KFEntityCamera.h"
#include <iostream>

#include <sstream>

string 
KFEntityCamera::str() const
{
	std::stringstream  buffer;
	buffer << "ID =\t\t" << fID << endl;
	buffer << "CFG_ID=\t" << fConfigID << endl;
	buffer << "name=\t\t" << fName << endl;
	buffer << "Enabled =\t" << ( fIsEnabled == true ? "TRUE" : "FALSE") << endl ;
	buffer << "IP address=\t" << fIPAddress << endl;
	buffer << "Product ID=\t" << fProductID << endl;
	buffer << "C-RING=\t" << fCring << endl;
	return buffer.str();
}
