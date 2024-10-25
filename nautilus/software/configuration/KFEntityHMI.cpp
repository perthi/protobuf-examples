// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFEntityHMI.h"
#include <iostream>

#include <utilities/GUtilities.h>


KFEntityHMI::KFEntityHMI()
{

}

KFEntityHMI::~KFEntityHMI()
{

}

string 
KFEntityHMI::str() const
{
	std::stringstream buffer;
	buffer << g_utilities()->TabAlign("TYPE:") << (int)fType << endl;
	buffer << g_utilities()->TabAlign("TITLE:") << fTitle << endl;
	buffer <<  g_utilities()->TabAlign("HMI_ID:") << fHMIID << endl;
	return buffer.str();
}
