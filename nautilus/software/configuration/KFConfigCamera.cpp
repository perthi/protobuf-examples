// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "KFConfigCamera.h"

#include <string>
#include <sstream>
using std::string;


#include <utilities/GUtilities.h>

string 
KFConfigCamera::GetExposureTypeS()
{
	if (fExposutreType == eEXPOSURE_TYPE::AUTO)
	{
		return "AUTO";
	}
	else if (fExposutreType == eEXPOSURE_TYPE::MANUAL)
	{
		return "MANUAL";
	}
	else
	{
		return "UNKNOWN";
	}

}

string 
KFConfigCamera::str() const
{
	std::stringstream buffer;
	buffer <<   g_utilities()->TabAlign("ID:") << fID << endl;
	buffer <<   g_utilities()->TabAlign("fName:") << fName << endl;
	buffer <<   g_utilities()->TabAlign("Exposure type:") << (int)fExposutreType << endl;
	buffer <<   g_utilities()->TabAlign("Screen position:") << endl << fPosition << endl;
	return buffer.str();
}
