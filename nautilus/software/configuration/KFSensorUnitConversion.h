// -*- mode: c++ -*-
#ifndef KFSENSORUNITCONVERSION_H
#define KFSENSORUNITCONVERSION_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/

//#include "KFEnums.h"

#include <protocol/KFProtocolEnums.h>

#include <utilities/GPrintable.h>

struct  KFSensorUnitConversion : public GPrintable
{
	KFSensorUnitConversion();
	virtual ~KFSensorUnitConversion();
	virtual  string  str() const override;
	void ValidateInputs();

	eSENSOR_INPUT_TYPE   fInputType = eSENSOR_INPUT_TYPE::UNKNOWN;
	string fInputTypeS = "";

	float fMinInput = 0;
	float fMaxInput = 0;
	float fMinOutput = 0;
	float fMaxOutput = 0;

	bool fHasMinInput = false;
	bool fHasMaxInput = false;
	bool fHasMinOutput = false;
	bool fHasMaxOutput = false;
	bool fHasInputType = false;

};

#endif
