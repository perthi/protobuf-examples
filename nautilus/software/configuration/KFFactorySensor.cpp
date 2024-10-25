

/******************************************
* @copyright Kongsberg Ferrotech          *
* @author Per Thomas Hille <pth@embc.no>  *
*******************************************/
// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "KFFactorySensor.h"
#include <utilities/GException.h>
#include <logging/LLogApi.h>

using namespace LOGMASTER;


KFSensorFactory *
KFSensorFactory::Instance()
{
	static KFSensorFactory* instance = new KFSensorFactory();
	return instance;
}


void
KFSensorFactory::AddSensor(std::shared_ptr<KFSensor> s)
{
	string hash = s->GetIPAddress();
	if (fSensorList.count(hash) > 0)
	{
		auto it = fSensorList.find(hash);
		std::shared_ptr<KFSensor> tmp = it->second;
		EXCEPTION("Duplicate IP address %s,\n new sensor %s conflicts with exisiting sensor %s",
			hash.c_str(), s->str().c_str(), tmp->str().c_str()  );
	}
	else
	{
		fSensorList.emplace( s->GetIPAddress(), s);
	}
}


std::shared_ptr<KFSensor>
KFSensorFactory::GetSensor(const string ip_address)
{
	auto it = fSensorList.find(ip_address);
	if (it == fSensorList.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}


void
KFSensorFactory::GenerateMockSensorList()
{
	std::shared_ptr<KFSensor>  s1 = std::make_shared< KFSensor>("ID1", "192.168.1.7", eSENSOR_TYPE::HUMIDITY);
	std::shared_ptr<KFSensor>  s2 = std::make_shared< KFSensor>("ID2", "192.168.1.11", eSENSOR_TYPE::HUMIDITY);
	std::shared_ptr<KFSensor>  s3 = std::make_shared< KFSensor>("ID3", "192.168.1.12", eSENSOR_TYPE::PRESSURE);
	std::shared_ptr<KFSensor>  s4 = std::make_shared< KFSensor>("ID4", "192.168.1.13", eSENSOR_TYPE::VOLTAGE);
	std::shared_ptr<KFSensor>  s5 = std::make_shared< KFSensor>("ID5", "192.168.1.17", eSENSOR_TYPE::VOLTAGE);
    std::shared_ptr<KFSensor>  s6 = std::make_shared< KFSensor>("ID5", "192.168.1.18", eSENSOR_TYPE::VOLTAGE);
	AddSensor(s1);
	AddSensor(s2);
	AddSensor(s3);
	AddSensor(s4);
    AddSensor(s5);
    AddSensor(s6);

}

void
KFSensorFactory::Update(const string key)
{
	if (fSensorList.count(key) == 0)
	{
		G_ERROR("Could not find sensor with key %s", key.c_str() );
	}
	else
	{
		std::shared_ptr<KFSensor> s = fSensorList.find(key)->second;
		s->UpdateSensorValue();
	}

}

void
KFSensorFactory::UpdateAll()
{
	for (auto it = fSensorList.begin(); it != fSensorList.end(); it++)
	{
		it->second->UpdateSensorValue();
	}

}
