// -*- mode: c++ -*-
#ifndef KFSENSORTHRESHOLDS_H
#define KFSENSORTHRESHOLDS_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/


#include <utilities/GDefinitions.h>
#include <utilities/GPrintable.h>

struct  KFSensorThresholds : public GPrintable
{
	API KFSensorThresholds();
	API virtual ~KFSensorThresholds();
	virtual  string API str() const override;

	void ValidateThresholds();

	float  fAlarmLow = 0;
	bool fHasAlarmLow = true; 

	float  fWarningLow = 0;
	bool fHasWarningLow = true;

	float  fWarningHigh = 0;
	bool fHasWarningHigh = true;
	float  fAlarmHigh = 0;
	bool fHasAlarmHigh = true;


};

#endif
