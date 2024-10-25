// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFFactorySensor.h"
#include <configuration/KFSensor.h>
#include <configuration/KFFactorySensor.h>

#include <memory>


TEST_F(TestKFFactorySensor, add_sensors)
{
	KFSensorFactory* f = KFSensorFactory::Instance();

	std::shared_ptr<KFSensor>  s1 = std::make_shared<KFSensor>("some id", "192.168.1.7", eSENSOR_TYPE::HUMIDITY);
	std::shared_ptr<KFSensor>  s2 = std::make_shared<KFSensor>("some id", "192.168.1.8", eSENSOR_TYPE::HUMIDITY );
	std::shared_ptr<KFSensor>  s3 = std::make_shared<KFSensor>("some id", "192.168.1.9", eSENSOR_TYPE::HUMIDITY);
	std::shared_ptr<KFSensor>  s4 = std::make_shared<KFSensor>("some id", "192.168.1.10", eSENSOR_TYPE::HUMIDITY);

	EXPECT_NO_THROW(f->AddSensor(s1));
	EXPECT_NO_THROW(f->AddSensor(s2));
	EXPECT_NO_THROW(f->AddSensor(s3));
	EXPECT_NO_THROW(f->AddSensor(s4));

	auto sensorlist = f->GetSensorList();
	EXPECT_EQ(sensorlist.size(), 4);

	// We expect an exception if we try to add the same snors a second time
	EXPECT_ANY_THROW(f->AddSensor(s1));
	EXPECT_ANY_THROW(f->AddSensor(s2));
	EXPECT_ANY_THROW(f->AddSensor(s3));
	EXPECT_ANY_THROW(f->AddSensor(s4));

	sensorlist = f->GetSensorList();
	EXPECT_EQ(sensorlist.size(), 4);

}


