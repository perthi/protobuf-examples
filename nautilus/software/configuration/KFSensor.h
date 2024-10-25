// -*- mode: c++ -*-


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#pragma once

#include <utility>
#include <string>
using std::string;
#include <vector>
using std::vector;

#include <utilities/GDefinitions.h>
#include <utilities/GPrintable.h>

//#include "KFEnums.h"

#include <protocol/KFProtocolEnums.h>


#include <stack>
#include <queue>


class KFSensor : public GPrintable
{
public:
	API         KFSensor(const string sensor_id, const string ip_adress, const eSENSOR_TYPE sensor_type);
	void    API SetSensorId(const string sensor_id);
	void    API SetIPAddress(const string ip_address);
	eSENSOR_TYPE API   GetSensorType() const { return fSensorType; };
	string API GetSensorId() const { return fSensorId; };
	string API GetIPAddress() const  { return fIPAddress; }
	virtual  string API str() const override;
	void API UpdateSensorValue();
	void API GetLastReading(double &time, double &value);
	std::queue<std::pair<double, double>>  API  GetXYData() const  { return fXYData;} ;

private:
	const  eSENSOR_TYPE fSensorType;
	string fSensorId = "";
	string fIPAddress = "";
//	vector<std::pair<double, double>> fXYData;
	std::queue<std::pair<double, double>> fXYData; 
};


