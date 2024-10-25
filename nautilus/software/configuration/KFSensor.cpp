// -*- mode: c++ -*-


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "KFSensor.h"
#include <utilities/GException.h>
#include <utilities/GUtilities.h>
#include <utilities/GTime.h>
#include <utilities/GRandom.h>

#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <sstream>


KFSensor::KFSensor(const string sensor_id, const string ip_address,  eSENSOR_TYPE sensor_type ) : fSensorType(sensor_type)
{
	SetSensorId( sensor_id );
	SetIPAddress( ip_address );
}


void
KFSensor::SetSensorId(const string sensor_id)
{
	G_ASSERT_EXCEPTION(sensor_id != "", "sensor ID cannot be empty" );
	fSensorId = sensor_id;
	
}


void 
KFSensor::SetIPAddress(const string ip_address)
{
	G_ASSERT_EXCEPTION ( g_utilities()->IsValidIPV4Address( ip_address ), "%s is not a vlaid IP address", ip_address.c_str()  );
	fIPAddress = ip_address;
}


string 
KFSensor::str() const
{
	std::stringstream buffer;
	buffer << fSensorId << endl;
	buffer << fIPAddress << endl;
	return buffer.str();
}


void 
KFSensor::UpdateSensorValue()
{
	G_INFO("Not implemented yet, generating simulated value ");
	double t = g_time()->GetEpochTime();
	double val = g_random()->Uniform(0, 200);
	auto pair = std::make_pair(t, val);
	fXYData.push(pair);
}


void 
KFSensor::GetLastReading(double& time, double& value)
{
	if (fXYData.size() == 0)
	{
		G_ERROR("No data");
		time = -1;
		value = -1;
	}
	else
	{
		auto element = fXYData.back();
		time = element.first;
		value = element.second;
	}


}


