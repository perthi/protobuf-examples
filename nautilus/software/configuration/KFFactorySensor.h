// -*- mode: c++ -*-

#pragma once


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include <map>

#include "KFSensor.h"
#include <utilities/GDefinitions.h>
#include <memory>

class KFSensorFactory
{
public:
	static  KFSensorFactory API * Instance();
	void API AddSensor( std::shared_ptr< KFSensor> s );
	std::shared_ptr< KFSensor> API GetSensor(const string ip_address);
	void API GenerateMockSensorList();

	void API Update( const string key );
	void API UpdateAll();

	std::map<string, std::shared_ptr< KFSensor >  > API  &  GetSensorList() { return  fSensorList; };

private:
	API KFSensorFactory()  {};
	std::map<string,  std::shared_ptr< KFSensor > > fSensorList;



};

