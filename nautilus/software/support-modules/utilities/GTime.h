// -*- mode: c++ -*-

#pragma once

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


#include "GDefinitions.h"

#include <ctime>
#include <time.h>
#include <vector>
#include <string>
#include <map>

#include <stdint.h>


using std::vector;
using std::string;
using std::map;

class GTime;

inline GTime * g_time();


/** @brief Convert a time duration in micro seconds  to seconds, minutes, hours etc..*/
class GTimeSpan
{
public:
    inline GTimeSpan(const int64_t usTimeSpan) : fTimespan(usTimeSpan)  {  }
    inline int64_t GetMicroSeconds() { return(fTimespan); }
    inline int64_t GetMilliSeconds() { return(fTimespan / 1000); }
    inline int64_t GetSeconds() { return(fTimespan / 1000000); }
    inline int64_t GetMinutes() { return(fTimespan / 60000000); }
    inline int64_t GetHours() { return(fTimespan / 3600000000); }
    inline int64_t GetDays() { return(fTimespan / 86400000000); }
private:
    int64_t fTimespan;
};


/** @brief various utility for acess to system time which is can be availabel on a user specifed format
 *  @details Also contains function for leap-year checks and validtiy check for days, months etc.. */
class GTime 
{
public:
    inline GTime() :   fTimeVal(0) {};
	API GTime(int year, int month, int dayInMonth, int hour24 = 0, int minute = 0, int second = 0, int us = 0);
    ~GTime() {};
    inline bool operator!=(GTime& o) { return(fTimeVal != o.fTimeVal); }
    inline bool operator==(GTime& o) { return(fTimeVal == o.fTimeVal); }
    inline bool operator>(GTime& o) { return(fTimeVal > o.fTimeVal); }
    inline bool operator>=(GTime& o) { return(fTimeVal >= o.fTimeVal); }
    inline bool operator<(GTime& o) { return(fTimeVal < o.fTimeVal); }
    inline bool operator<=(GTime& o) { return(fTimeVal <= o.fTimeVal); }
    inline GTimeSpan operator-(GTime& o) { return(GTimeSpan(fTimeVal - o.fTimeVal)); }
    void API SetTime(int year, int month, int dayInMonth, int hour24 = 0, int minute = 0, int second = 0, int us = 0);
    
    static inline long double		API   AccessDate();
    static inline long double		API   AccessDate(const string date);
    static inline bool				API   IsGregorianLeapYear(int iYear);
    static inline bool				API   IsValidDateString(const string GTime);
    static inline bool				API   IsValidDay(    string  day );
    static inline bool				API   IsValidDay(   const int  day);
    static inline bool				API   IsValidDate(  const string  date );
    static inline bool				API   IsValidDate(  const int  date);
    static inline bool				API   IsValidMonth( const string  month);
    static inline bool				API   IsValidMonth( const int     month);
    static inline bool				API   IsValidYear(  const string  year);
    static inline bool				API   IsValidYear(  const int     year);
    static inline bool				API   IsValidHour(  const string  hour);
    static inline bool				API   IsValidHour(  const int     hour);
    static inline bool				API   IsValidMinute( const string  m);
    static inline bool				API   IsValidMinute( const int     h);
    static inline bool				API   IsValidSecond( const string  s);
    static inline bool				API   IsValidSecond( const int     s);
    static inline bool				API   IsValidFormat(const char  *c,  string & offender);
    vector<string> inline static	API   GetFormatSpecifiers();
    static  inline map<string, string> API & FormatChars();
    static inline string			API   str();
    static inline string			API   TimeStamp(struct std::tm *tout = 0, const char * format = 0, struct std::tm *tin = 0, int64_t *us = 0);
    static inline string			API   TimeStamp(const char * format, int64_t *us = 0 );
    static inline void				API   GetRawTime(time_t *seconds, int64_t  *us = nullptr);
    static inline double            API   GetEpochTime();
    //    static inline string			API   GetTime_ISO8601( bool use_microseconds = true );
    static inline time_t			API   DateString2Time(const string date, const string format, std::tm *t = 0, int64_t *us = 0);
    inline string		TimeStampShort(struct std::tm *tout = 0, struct std::tm *tin = 0, int64_t *us = 0);
    
#ifdef _WIN32
	static GTime API Now();
#endif

	inline int64_t GetBaseUsTime() { return(fTimeVal); }

private:
    static bool  inline Validate(bool( * funct)(const int), const string s, vector<string> arr = vector<string>() );
    int64_t fTimeVal;
    char fBuffer[512] = {0};
    char fFormat[512] = {0};
};



GTime * g_time()
{
    static GTime *instance = new GTime();
    return instance;
}


#include "GUtilities.h"
#include "GTokenizer.h"
#include "GNumbers.h"
#include "GRegexp.h"
#include <sstream>
#include <chrono>
using namespace std::chrono;

// #define YEAR_MIN 1999

/*
 * @class GTime class for 
 *  - manipulation of time/date stamps.
 *  - time estamp for the current time on user a defined format
 *  - Conversion between different forms of date representation
 *  
 *  The standard formattting used when converting to/from astring representation is shown below
 *     ***************************************************
 *     ***********    FORMAT SPECIFIERS      *************
 *     ***************************************************
 *     %a  =  abbrevated weekday
 *     %A  =  weekday
 *     %b  =  abbrevated month
 *     %B  =  month
 *     %C  =  Century (00-99)
 *     %d  =  Day of month (01-31), zero padded
 *     %e  =  Day of month ( 1-31), space padded
 *     %D  =  Equivalent to %m/%d/%y
 *     %F  =  Equivalent to %Y-%m-%d
 *     %g  =  last two digits of the week-based year
 *     %G  =  Week-based year
 *     %h  =  equivalent to %b (abbrevated month)
 *     %H  =  24-hour decimal (00-24)
 *     %I  =  12-hour decimal (00-12)
 *     %j  =  year day (001-366)
 *     %m  =  Month in decimal (01-12)
 *     %M  =  Minutes in decimal (00-59)
 *     %n  =  newline character
 *     %p  =  AM/PM designation
 *     %r  =  Equivalent to %I:%M : %S %p
 *     %R  =  Equivalent to %H:%M
 *     %S  =  Seconds in decimal (00-59)
 *     %t  =  newline character
 *     %T  =  Equivalent to  %H:%M:%S
 *     %u  =  week day in decimal (1-7)
 *     %w  =  week day in decimal (0-6)
 *     %U  =  sunday week number (00-53)
 *     %W  =  monday week number (00-53)
 *     %V  =  ISO 8601 week number (00-53)
 *     %X  =  Time display
 *     %y  =  year without century
 *     %Y  =  year with century"
 *     %z  =  Time zone
 *     %Z  =  Time zone name (if any)"
 *     %%  =  percent sign");
 */




vector<string> GTime::GetFormatSpecifiers()
{
    vector<string> tmp;
    std::map<string, string>  format = FormatChars();

    for (std::map<string, string>::iterator iter = format.begin(); iter != format.end(); ++iter)
    {
        tmp.push_back(iter->first);
    }

    return tmp;
}



/*
  NSR - 242
  * Checks if a Year is a leap year.
  * @param[in] iYear
  * @return true if Leap Year othervise false
  */
bool GTime::IsGregorianLeapYear(int iYear)
{

    if (iYear % 4 != 0)
    {
        return false;
    }
    else if (iYear % 100 != 0)
    {
        return true;
    }
    else if (iYear % 400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }

}



//CRAP PTH, refactor
bool
GTime::IsValidDateString(const string t)
{
    static vector<string> validMonths = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    static vector<string> validDays = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

    if (t.size() == 0)
    {
        return false;
    }

	static char day[64] = {0};
    int  date;
	static char month[64] = {0};
    int  year;
    int  hour;
    int  minute;
    int  second;


#ifdef _WIN32
    int  ret = sscanf_s(t.c_str(),  "[%s %d %s %d:%d:%d]", day, 64, &date, month, 64, &hour, &minute, &second );
    if (ret != 6)
    {
        std::stringstream buffer;
        buffer << "could not scan string " << t << " scanf returned " << ret << ", expected 6 paramters " << "\n";


#ifdef _WIN32
        throw(std::exception(buffer.str().c_str()));
#else
        throw(std::runtime_error(buffer.str().c_str()));
#endif

        //EXCEPTION("Could not scan string: \"%s\". sscanf returned: %i, expected 6 parameters", t.c_str(), ret);
    }
#else
    sscanf(t.c_str(),  "[%s %d %s %d:%d:%d]", day, &date, month, &hour, &minute, &second );
#endif


    vector<string> ytokens = g_tokenizer()->Tokenize(month, "-");

    if (ytokens.size() == 2)
    {
        year = g_numbers()->ToInteger<int>(ytokens[1]);
        snprintf(month, 64, "%s", ytokens[0].c_str());
    }
    else
    {
        CERR << "ERROR; invalid GTime  string;\t " << t << ", GTime.size() = " << t.size() << "\n";
        return false;
    }

  
    bool isValidDay = false;
    bool isValidDate = false;
    bool isValidMonth = false;
    bool isValidYear = false;
    bool isValidHour = false;
    bool isValidMinute = false;
    bool isValidSecond = false;

    string sday = string(day);
    for (uint16_t i = 0; i < validDays.size(); i++)
    {
        if (sday == validDays[i])
        {
            //      CERR << "DAY is valid (" << sday << ")" << endl;
            isValidDay = true;
            break;
        }
    }

    if (date > 0 && date <= 31)
    {
        isValidDate = true;
    }


    /// NB will fail in year 9999 !!!   
    if (year >= YEAR_MIN && year < 9999)
        //  if (year > 1999 && year < 9999)    
    {
        isValidYear = true;
    }
    else
    {
        CERR << "Invalid year " << year << ", year must be between " << YEAR_MIN << " and " << YEAR_MAX << "\n";
    }

    string smonth = string(month);
    for (uint16_t i = 0; i < validMonths.size(); i++)
    {
        if (smonth == validMonths[i])
        {
            
            isValidMonth = true;
            break;
        }
    }

    if (hour < 24 && hour >= 0) { isValidHour = true; }
    if (minute < 60 && minute >= 0) { isValidMinute = true; };
    if (second < 60 && second >= 0) { isValidSecond = true; };


    if (isValidDay && isValidDate && isValidMonth && isValidYear && isValidHour  && isValidMinute  && isValidSecond)
    {
        return true;
    }
    else
    {
      //  COUT << ":ERROR; invalid GTime  string;\t " << t << endl;
        return false;
    }

}


bool GTime::IsValidDay(string day)
{
    vector<string> valid_days = { "monday",  "tuesday",  "wednesday",  "thursday", "friday", "saturday", "sunday" };
    return Validate( IsValidDay, day, valid_days);
}


bool  GTime::IsValidDay(const int day)
{
    return g_utilities()->IsInRange(day, DAY_MIN, DAY_MAX);
}


bool GTime::IsValidDate(const string date)
{
    return Validate(IsValidDate, date);
}


bool GTime::IsValidDate(const int date)
{
    return g_utilities()->IsInRange(date, DATE_MIN, DATE_MAX);
}



bool GTime::IsValidMonth(const string month)
{
    vector<string> valid_months{ "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };
    return Validate(IsValidMonth, month, valid_months);
    return false;
}


bool  GTime::IsValidMonth(const int month)
{
    return g_utilities()->IsInRange(month, MONTH_MIN, MONTH_MAX);
}


bool GTime::IsValidYear(const string year)
{
    return Validate(IsValidYear, year);
}


bool  GTime::IsValidYear(const int year)
{
    return g_utilities()->IsInRange(year, YEAR_MIN, YEAR_MAX);
    
}


bool GTime::IsValidHour(const string hour)
{
    return Validate(IsValidHour, hour);
}


bool  GTime::IsValidHour(const int hour)
{
    return g_utilities()->IsInRange(hour, HOUR_MIN, HOUR_MAX);
}


bool  GTime::IsValidMinute(const string m)
{
    return Validate(IsValidMinute, m);
}


bool  GTime::IsValidMinute(const int m)
{
    return g_utilities()->IsInRange(m, MINUTE_MIN, MINUTE_MAX);
}


bool GTime::IsValidSecond(const string s)
{
    return Validate(IsValidSecond, s); 
}



bool  GTime::IsValidSecond(const int s)
{
    return g_utilities()->IsInRange(s, SECONDS_MIN,  SECONDS_MAX);
}



bool
GTime::Validate(bool(*funct)(const int), const string s, vector<string> arr)
{
    if ( g_numbers()->IsInteger(s) == true)
    {
        int tmp = g_numbers()->ToInteger<int>(s);
         bool ret = funct(tmp);
        return    ret;
    }
    else
    {
        bool ret =  g_string()->BeginsWith(arr, s);
        return  ret; 
    }
}


/** Todays GTime and date on a format understood by the Access databas. In Access the dat is represented as a
 *  single number (double) as the number of days since 1 Jan 1900 on decismnal form (tha is, for instance 0.5 days = 12 hours )
 *  The dat is taken from the operatinmg system 
 *  @return The number of days since 1.January 1900 00:00  on decimal form */
long double GTime::AccessDate()
{
    string date = TimeStamp("%Y:%m:%u:%H:%M:%S");
    return AccessDate(date);
}


/** Date and GTime converter form the input GArguments to a format understood by the Access databas. In Access the data is represented as a
 *  single number (double) as the number of days since 1 Jan 1900 on decimal form (that is, for instance 0.5 days = 12 hours )
 *  @param date on string format which assumes the format yyyy:mm:dd:hh:mm:ss  The separator is insignificant
 *  @return The date on Access format */
long double  GTime::AccessDate(const string date)
{
    int mdays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long double DAYS_1900_TO_2000 = 36526.0;
    long double nDays = DAYS_1900_TO_2000;

    vector<string> numbers = g_regexp()->ScanNumber(date, "1,12");
    
    if (numbers.size() != 6)
    {
        //	cerr << __FILE__ << __LINE__ << ": " << __FUNCTION__ << "Incorrect Date format" << date;
        //EXCEPTION("Incorrect Date format %s (the count of numbers fields is %d, expected 6)", date.c_str(), numbers.size());
        std::stringstream buffer;
        buffer << "Incorerect date format " << date << " the count of number fields is " << numbers.size() << " expected 6" << "\n";
#ifdef _WIN32
        throw(std::exception(buffer.str().c_str()));
#else
        throw(std::runtime_error(buffer.str().c_str()));
#endif

    }
    else
    {
        int year =  g_numbers()->ToInteger<int>(numbers[0]);
        int month = g_numbers()->ToInteger<int>(numbers[1]);
        int day =   g_numbers()->ToInteger<int>(numbers[2]);
        int hour =  g_numbers()->ToInteger<int>(numbers[3]);
        int min =   g_numbers()->ToInteger<int>(numbers[4]);
        int sec =   g_numbers()->ToInteger<int>(numbers[5]);

        for (int i = 2000; i < year; i++)
        {
            if (IsGregorianLeapYear(i))
            {
                nDays += 366;
            }
            else
            {
                nDays += 365;
            }
        }

        for (int i = 0; i < month - 1; i++)
        {
            nDays += mdays[i];
        }

        if (IsGregorianLeapYear(year) && month > 2)
        {
            nDays += 1;
        }

        nDays += (long double)day - (long double)1;
		int64_t minutes_per_day = 24 * 60;
		int64_t seconds_per_day = minutes_per_day*60;
		long double rem = (long double)hour / 24 + (long double)min / (minutes_per_day) + (long double)sec / (seconds_per_day );
        nDays += rem;
    }
    return nDays;
}



/*  Converts a date on string format to the number of seconds since January 1st 1970. Optionally gnerates std:tm struct an calculates the number of microseconds 
 *   by optional in/out parameters if the date string is on the ISO8601 format.    
 *  @param[in]  date  The date that should be converted
 *  @param[in]  format  The format of the date string. NB the format must match the date. Othervise aal fileds in the "tm" structy is set to ZERO.   
 For instance 
 date =  "1988-June-23 10:09:49";
 must be parsed with 
 format = "%Y-%b-%d %H:%M:%S",
  
 *  @return The number of sconds between Jauary 1st 00:00 1970  and the date represented by the "date" input parameter  
 */
time_t
GTime::DateString2Time(const string date, const string format, std::tm *t, int64_t *us )
{
    static std::tm t_l;
    std::istringstream ss(date);
    ss >> std::get_time(&t_l, format.c_str());
    vector<string> tokens = g_tokenizer()->Tokenize(date, ".");
    
    size_t n = tokens.size();

    //   COUT << "us = " <<  us << endl;
    
    if (us != 0)
    {
        if (n == 1)
        {
            *us = 0;
        }
        //else if (n >= 0)
        else
        {
            string snum = tokens.at(n - 1);
            //           COUT << "snum = " << snum << endl;
            if (g_numbers()->IsNumber(snum))
            {
                snum = "." + snum;
                double d = g_numbers()->ToFloat(snum);
                *us = (int64_t)(d * 1000000);
            }
            else
            {
                *us = 0;
            }
        }
    }
  


    if (t != 0)
    {
        *t = t_l;
    }

    return   mktime(&t_l);
}



/*
string
GTime::GetTime_ISO8601(bool use_microseconds)
{
    static int64_t us;

    string d = TimeStamp("%FT%T", &us);
    ///	CERR << "us = " << us << "\n";

    static char t[512];

    if (use_microseconds == true)
    {
#ifdef ARM
        SPRINTF(t, 512, "%s.%6lld", d.c_str(), us);
#else
#ifdef _WIN32
        SPRINTF(t, 512, "%s.%6lld", d.c_str(), us);
#else
		SPRINTF(t, 512, "%s.%6ld", d.c_str(), us);
#endif
#endif
    }
    else
    {
        SPRINTF(t, 512, "%s", d.c_str());
    }

    string utc = TimeStamp("%z");

    SPRINTF(t, 512, "%s%s", t, utc.c_str());

    return string(t);
}
*/


double   
GTime::GetEpochTime()
{
    system_clock::time_point tp = system_clock::now();
    system_clock::duration dtn = tp.time_since_epoch();
    //	return dtn.count() * system_clock::period::num / system_clock::period::den;
#ifdef _WIN32
    return ((double)dtn.count())/10000000;
#else
    return ((double)dtn.count())/1000000000;
#endif
}



/* @param[in|out] seconds Number of seconds since 1.january 1970
 *  @param[in|out] time since epoch in microseconds, the value is arbritrary and should be used for comparison only */
void  
GTime::GetRawTime(time_t * sec, int64_t * us)
{
    if (sec != 0)
    {
        *sec = std::time(0);
    }
    if (us != nullptr)
    {
        auto lus = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch());
        *us = lus.count() % 1000000;
        //*us = lus.count();

    }
}


/*
string
GTime::TimeStampShort(int64_t *us)
{
    //    TimeStamp(format, us);
    return TimeStampShort(0, 0, us);
}
*/



string
GTime::TimeStampShort(struct std::tm *  tout, struct std::tm * tin, int64_t * us )
{
    //return TimeStamp(tout, "[%H:%M:%S]" , tin, us);
   // return "short timestamp not implemented";
  //  static int64_t us = 0;
  //  static char fmt[] =   "%H:%M:%S"; 
  //  return TimeStamp(0, fmt, 0, 0);
   //   return TimeStamp(tout, fmt, tin, us);
   return TimeStamp(tout, "%H:%M:%S" , tin, us);
}



string
GTime::TimeStamp(const char * format, int64_t *us)
{
    return TimeStamp(0, format, 0, us);
}




#ifdef _WIN32
string
GTime::TimeStamp(struct std::tm *tout, const char * format, struct std::tm *tin, int64_t *us)
{
    string offender;

    if (IsValidFormat(format, offender) == false)
    {
        CERR << "Illegal format" << "\n";
        std::stringstream buffer;
        buffer << "Illegal format specifier " << string(format) << "\"\n"\
            + str() << \
            ", the offending specifier is \"" << offender << "\" which is unknown" << "\n" \
               << "error in function " << __FUNCTION__ << "at:" << __FILE__ << ":" << __LINE__ << "\n";

        ///@todo use GLOCATION
        throw(std::exception(buffer.str().c_str()));
    }
    else
    {
        char tmp[512] = { 0 };
        char f[512] = { 0 };

        struct std::tm timeinfo;
        std::time_t now;
        GetRawTime(&now, us);

        if (tin == 0)
        {
            localtime_s(&timeinfo, &now);
        }
        else
        {
            timeinfo = *tin;
        }
        if (tout != 0)
        {
            *tout = timeinfo;
        }
        if (format == 0)
        {
            snprintf(f, 512, "%s", "[%a %d %B-%Y %H:%M:%S]");
        }
        else
        {
            snprintf(f, 512, "%s", format);
        }

        std::strftime(tmp, 512 - 1, f, &timeinfo);
        return string(tmp);
    }
}


#else

string
GTime::TimeStamp(struct std::tm *tout, const char * format, struct std::tm *tin, int64_t *us)
{
    string offender;

    if (IsValidFormat(format, offender) == false)
    {
        std::stringstream buffer;
        buffer << "Illegal format specifier " << string(format) << "\"\n"\
            + str() << \
            ", the offending specifier is \"" << offender << "\" which is unknown" << "\n" \
               << "error in function " << __FUNCTION__ << "at:" << __FILE__ << ":" << __LINE__ << "\n";
        ///@todo use GLOCATION
        throw(std::runtime_error(buffer.str().c_str()));
    }
    else
    {
        char tmp[512] = { 0 };
        char f[512] = { 0 };
        //struct std::tm *timeinfo = 0;
        struct std::tm timeinfo;
        std::time_t now;
        GetRawTime(&now, us);
        
        if (tin == 0)
        {
            timeinfo = *localtime(&now);
        }
        else
        {
            timeinfo = *tin;
        }
    
        if (tout != 0)
        {
            *tout = timeinfo;
        }

        if (format == 0)
        {
            snprintf(f, 512, "%s", "[%a %d %B-%Y %H:%M:%S]");
        }
        else
        {
            snprintf(f, 512, "%s", format);
        }

        std::strftime(tmp, 512 - 1, f, &timeinfo);
        return string(tmp);
    }
}

#endif


map<string, string>  &
GTime::FormatChars()
{
    static map<string, string> format;
    static bool isInitialized = false;

    if (isInitialized == false)
    {
        format.emplace("%a", "abbrevated weekday");
        format.emplace("%A", "weekday");
        format.emplace("%b", "abbrevated month");
        format.emplace("%B", "month");
        format.emplace("%C", "Century (00-99)");
        format.emplace("%d", "Day of month (01-31), zero padded");
        format.emplace("%e", "Day of month ( 1-31), space padded");
        format.emplace("%D", "Equivalent to \"%m/%d/%y\"");
        format.emplace("%F", "Equivalent to \"%Y-%m-%d\"");
        format.emplace("%g", "last two digits of the week-based year");
        format.emplace("%G", "Week-based year");
        format.emplace("%h", "equivalent to %b (abbrevated month)");
        format.emplace("%H", "24-hour decimal (00-24)");

        format.emplace("%I", "12-hour decimal (00-12)");
        format.emplace("%j", "year day (001-366)");
        format.emplace("%m", "Month in decimal (01-12)");
        format.emplace("%M", "Minutes in decimal (00-59)");

        format.emplace("%n", "newline character");
        format.emplace("%p", "AM/PM designation");
        format.emplace("%r", "Equivalent to \"%I:%M : %S %p\"");
        format.emplace("%R", "Equivalent to \"%H:%M\"");
        format.emplace("%S", "Seconds in decimal (00-59)");
        format.emplace("%t", "newline character");
        format.emplace("%T", "Equivalent to \"%H:%M:%S\"");
        format.emplace("%u", "week day in decimal (1-7)");
        format.emplace("%w", "week day in decimal (0-6)");

        format.emplace("%U", "sunday week number (00-53)");
        format.emplace("%W", "monday week number (00-53)");
        format.emplace("%V", " ISO 8601 week number (00-53)");
        format.emplace("%X", "Time display");

        format.emplace("%y", "year without century");
        format.emplace("%Y", "year with century");
        format.emplace("%z", "Time zone");
        format.emplace("%z", "Time zone name (if any)");
       // format.emplace("[", "");
       // format.emplace("]", "");


        isInitialized = true;
    }
    return format;
}



bool
GTime::IsValidFormat(const char *c, string & offender)
{
    //  Initialize();
    bool has_valid_token = false;
    bool has_invalid_token = false;

    if (c == 0)
    {
        return true;
    }
    else
    {
        vector<string> tokens = g_tokenizer()->Tokenize(c, "%");
        static std::map<string, string>  &format = FormatChars();

        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            bool isvalid = false;
            string tmp = "";
            if (tokens[i].size() >= 1) { tmp = "%" + tokens[i].substr(0, 1); }
            for (std::map<string, string>::iterator iter = format.begin(); iter != format.end(); ++iter)
            {
                if (iter->first == tmp)
                {
                    has_valid_token = true;
                    isvalid = true;
                }
            }
            if (isvalid == false)
            {
                has_invalid_token = true;
                offender = tokens.at(i);
                break;
            }
        }
    }

    if (has_invalid_token == true)
    {
        return false;
    }
    if (has_valid_token == true)
    {
        return true;
    }
    return false;
}



string
GTime::str()
{
    static std::map<string, string>  &format = FormatChars();
    string infostring = "******  Valid Format Specifiers  BEGIN ******\n";
    for (std::map<string, string>::iterator iter = format.begin(); iter != format.end(); ++iter)
    {
        infostring += iter->first + ":\t" + string(iter->second) + "\n";

    }

    infostring += "\n ***** Valid format specifiers END ******\n";
    return infostring;
}







