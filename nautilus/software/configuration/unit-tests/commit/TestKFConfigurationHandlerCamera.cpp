// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFConfigurationHandlerCamera.h"
#include <configuration/KFEntityCamera.h>
#include <configuration/KFConfigCamera.h>
#include <configuration/KFConfigurationHandlerCamera.h>

#include <memory>
//
//TEST_F(TestKFConfigurationHandlerCamera, dummy)
//{
//	EXPECT_TRUE(false);
//}



TEST_F(TestKFConfigurationHandlerCamera, add_cameras )
{
	std::shared_ptr<KFEntityCamera> c1 = std::make_shared<KFEntityCamera>();
	std::shared_ptr<KFEntityCamera> c2 = std::make_shared<KFEntityCamera>();
	std::shared_ptr<KFEntityCamera> c3 = std::make_shared<KFEntityCamera>();
	std::shared_ptr<KFEntityCamera> c4 = std::make_shared<KFEntityCamera>();
	std::shared_ptr<KFEntityCamera> c5_invalid_config = std::make_shared<KFEntityCamera>(); 
	std::shared_ptr<KFConfigCamera> cfg1 = std::make_shared<KFConfigCamera>();
	std::shared_ptr<KFConfigCamera> cfg2 = std::make_shared<KFConfigCamera>();

	c1->fID = "1";
	c1->fConfigID = "1";
	c1->fName = "C - ring 180";
	c1->fIsEnabled = true;
	c1->fIPAddress = "192.168.1.1";
	c1->fIPAddress = "blahhh";
	c1->fCring = "C - ring 180 along pipe";
	c2->fID = "2";
	c2->fConfigID = "1";
	c2->fName = "C-ring 180 inspect";
	c2->fIsEnabled = true;
	c2->fIPAddress = "192.168.1.2";
	c2->fProductID  = "blahhh";
	c2->fCring = "C - ring 180 towards pipe";
	c3->fID = "3";
	c3->fConfigID = "2";
	c3->fName = "C-ring 180 inspect";
	c3->fIsEnabled = true;
	c3->fIPAddress = "10.0.0.2";
	c3->fIPAddress = "blahhh";
	c3->fCring = "C - ring 180 towards pipe";

	c4 = c2;
	c5_invalid_config = c2;
	c5_invalid_config->fConfigID = "42";


	cfg1->fID = "1";
	cfg1->fName = "Surface preparation";
	cfg1->fIsEnabled = true;
	cfg1->fExposutreType = eEXPOSURE_TYPE::AUTO;
	cfg1->fPosition.fLeft = 830;
	cfg1->fPosition.fTop = 50;
	cfg1->fPosition.fWidth = 800;
	cfg1->fPosition.fHeight = 600;
	cfg2->fID = "2";
	cfg2->fName = "Structure";
	cfg2->fIsEnabled = true;
	cfg2->fExposutreType = eEXPOSURE_TYPE::AUTO;
	cfg2->fPosition.fLeft = 350;
	cfg2->fPosition.fTop = 560;
	cfg2->fPosition.fWidth = 1200;
	cfg2->fPosition.fHeight = 1800;

	vector<std::shared_ptr<KFEntityCamera> > cameras_v = { c1,c2,c3 };
	vector<std::shared_ptr<KFEntityCamera> > cameras_v_invalid1 = { c1,c2, c4, c3 };
	vector<std::shared_ptr<KFEntityCamera> > cameras_v_invalid2 = { c1,c2, c5_invalid_config , c3 };
	vector<std::shared_ptr<KFConfigCamera> > configs_v = { cfg1, cfg2 };

	EXPECT_NO_THROW(  KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(cameras_v, configs_v));
	EXPECT_ANY_THROW( KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(cameras_v_invalid1, configs_v));
	EXPECT_ANY_THROW( KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(cameras_v_invalid2, configs_v));

	EXPECT_NO_THROW(KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(cameras_v, configs_v));

	cameras_v = { c1,c2 };

	EXPECT_NO_THROW(   KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(cameras_v, configs_v));
	EXPECT_NO_THROW(   KFConfigurationHandlerCamera::Instance()->AddUniqueCamera(c3) );
	EXPECT_ANY_THROW(  KFConfigurationHandlerCamera::Instance()->AddUniqueCamera(c3));
	EXPECT_ANY_THROW(  KFConfigurationHandlerCamera::Instance()->AddUniqueCamera(c4));
	EXPECT_ANY_THROW(  KFConfigurationHandlerCamera::Instance()->AddUniqueCamera(c5_invalid_config ));
	EXPECT_ANY_THROW ( KFConfigurationHandlerCamera::Instance()->AddUniqueCameraConfig(cfg1) );
	EXPECT_ANY_THROW ( KFConfigurationHandlerCamera::Instance()->AddUniqueCameraConfig(cfg1) );
	
}


