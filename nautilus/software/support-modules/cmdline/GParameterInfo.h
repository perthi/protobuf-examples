// -*- mode: c++ -*-
#ifndef PARAMETERINFO_H
#define PARAMETERINFO_H

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


#include <cstdio>

struct ParameterInfo
{
	ParameterInfo() :
		fDefaultValue(0), fMin(0), fMax(0)
	{
	}

	void Print()
	{
		printf("\t\tName:\t\t%s\n", fName);
		printf("\t\tUnits:\t\t%s\n", fUnit);
		printf("\t\tDescription:\t%s\n", fDescription);
		printf("\t\tDefault:\t%d %s\n", fDefaultValue, fUnit);
		printf("\t\tMin:\t\t%d %s\n", fMin, fUnit);
		printf("\t\tMax:\t\t%d %s\n", fMax, fUnit);
	}

	char fName[256];
	char fUnit[256];
	char fDescription[256];
	int fDefaultValue;
	int fMin;
	int fMax;
};

#endif
