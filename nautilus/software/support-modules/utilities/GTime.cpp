// -*- mode: c++ -*-

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no> http:///www.embc.no  ***
*** all rights reserved                                                    ***
***                                                                        ***
*** logmaster is free software: you can redistribute it and/or modify      ***
*** it under the terms of the Lesser GNU General Public License (LGPL)     ***
*** as published by the Free Software Foundation, either version 3 of the  ***
*** License, or (at your option) any later version.                        ***
***                                                                        ***
*** logmaster is distributed in the hope that it will be useful,           ***
*** but WITHOUT ANY WARRANTY; without even the implied warranty of         ***
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          ***
*** GNU General Public License for more details.                           ***
***                                                                        ***
*** You should have received a copy of the Lesser GNU General Public       ***
*** License along with logmaster in the README file in the source code     ***
*** directory. If not, see <http://www.gnu.org/licenses/>.                 ***
******************************************************************************
******************************************************************************/

#include "GTime.h"

#include <ctime>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


GTime::GTime(int year, int month, int dayInMonth, int hour24, int minute, int second, int us) : fTimeVal(0)
{
	SetTime(year, month, dayInMonth, hour24, minute, second, us);
}


#ifdef _WIN32
GTime GTime::Now()
{
	FILETIME fileTime;
	SYSTEMTIME systemTime;
	TIME_ZONE_INFORMATION timeZoneInformation;
	SYSTEMTIME localTime;

	GetTimeZoneInformation(&timeZoneInformation);
	GetSystemTimePreciseAsFileTime(&fileTime);
	FileTimeToSystemTime(&fileTime, &systemTime);
	SystemTimeToTzSpecificLocalTime(&timeZoneInformation,
		&systemTime,
		&localTime);

	ULARGE_INTEGER ul;
	ul.HighPart = fileTime.dwHighDateTime;
	ul.LowPart = fileTime.dwLowDateTime;
	int us = (int)((ul.QuadPart / 10) % 1000000);
	return ( GTime(localTime.wYear, localTime.wMonth, localTime.wDay, localTime.wHour, localTime.wMinute, localTime.wSecond, us));
}
#endif


void
GTime::SetTime(int year, int month, int dayInMonth, int hour24, int minute, int second, int us)
{
	std::tm tm;
	::memset(&tm, 0, sizeof(tm));
	tm.tm_year = year - 1900;
	tm.tm_mon = month;
	tm.tm_mday = dayInMonth;
	tm.tm_hour = hour24;
	tm.tm_min = minute;
	tm.tm_sec = second;

	int64_t timeSeconds = (int64_t)mktime(&tm);
	fTimeVal = timeSeconds * 1000000 + us;
}
