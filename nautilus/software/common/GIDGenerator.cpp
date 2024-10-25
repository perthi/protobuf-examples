// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GIDGenerator.h"

 

GIDGenerator * 
GIDGenerator::Instance()
{
	static GIDGenerator *instance = new GIDGenerator();
	return instance;
}


string
GIDGenerator::CreateUniqueID(const string prefix) const
{
	static int64_t cnt = 0;
	cnt++;
	//auto date = g_time()->AccessDate();
	time_t s = 0;
	g_time()->GetRawTime( &s );
//	GTime::GetRawTime(time_t * sec, long long int * us)
	string date_s = g_string()->ToString(s);
	string tmp = prefix + ":" +  g_system()->GetHostName() + ":" +  g_system()->GetProcessID() + ":" + date_s + ":" +  g_string()->ToString(cnt, 9);
	return tmp;
}


GIDGenerator::GIDGenerator()
{

}


GIDGenerator::~GIDGenerator()
{

}
