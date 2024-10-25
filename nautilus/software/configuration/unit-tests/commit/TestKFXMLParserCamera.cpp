// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFXMLParserCamera.h"

#include <xml/GXmlValidator.h>
#include <xml/GXmlStreamReader.h>
#include <configuration/KFConfigurationHandlerCamera.h>
#include <configuration/KFConfigUtilities.h>
#include <kf-main/KFGlobals.h>


void
TestKFXMLParserCamera::SetUpTestCase()
{
	KFConfigUtilities::Instance()->InitFileXML( "camera_config.xml", fXMLFile );
	KFConfigUtilities::Instance()->InitFileXSD(  KFGlobals::Instance()->GetXSDFilenameCamera().str() , fXSDFile );
}



TEST_F(TestKFXMLParserCamera, is_valid)
{
	EXPECT_TRUE(GXmlValidator::IsValid(fXMLFile.str(), fXSDFile.str()));
}


TEST_F(TestKFXMLParserCamera, sizes)
{

	p.ParseXML(  fCameras_v,  fConfig_v, fXMLFile, fXSDFile);

	EXPECT_EQ( fCameras_v.size(), 3);
	EXPECT_EQ( fConfig_v.size(), 2);
}



TEST_F(TestKFXMLParserCamera, exists_camera_config)
{
	p.ParseXML( fCameras_v, fConfig_v, fXMLFile, fXSDFile);

	KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(  fCameras_v, fConfig_v );
	
	
	KFInfoCamera* info = nullptr;
	
	/// We expecet cameras with ID 1 -3 to exist in the XML files
	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("1", &info);
	ASSERT_NE(info, nullptr);
	delete info;
	
	info = nullptr;
	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("2", &info);
	ASSERT_NE(info, nullptr);
	delete info;
	info = nullptr;

	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("3", &info);
	ASSERT_NE(info, nullptr);
	delete info;
	info = nullptr;

	/// Camreas with ID 4 and 42 does not exist in the XML file
	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("4", &info);
	EXPECT_EQ(info, nullptr);

	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("42", &info);
	EXPECT_EQ(info, nullptr);
}


/// @brief Verify that values given by SW coreespnds to waht we expecet from the
/// XML file
TEST_F(TestKFXMLParserCamera, check_camera_config)
{
	p.ParseXML( fCameras_v,  fConfig_v, fXMLFile, fXSDFile);
	KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration(  fCameras_v,  fConfig_v );
	KFInfoCamera* info = nullptr;

	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("1", &info);
	ASSERT_NE(info, nullptr);
	
	std::shared_ptr<KFEntityCamera> c1 = info->fCamera;
	std::shared_ptr<KFConfigCamera> cfg1 = info->fCameraConfig;
	
	EXPECT_EQ(c1->fID, "1");
	EXPECT_EQ(c1->fConfigID, "1");
	EXPECT_EQ(c1->fName, "C-ring 180");
	EXPECT_EQ(c1->fIsEnabled, true);
	EXPECT_EQ(c1->fIPAddress, "192.168.1.1");
	EXPECT_EQ(c1->fProductID, "someID_1");
	EXPECT_EQ(c1->fCring, "C-ring 180 along pipe");

	EXPECT_EQ( cfg1->fID, "1");
	EXPECT_EQ( cfg1->fName, "Surface preparation");
	EXPECT_EQ( (int)cfg1->fExposutreType, (int)eEXPOSURE_TYPE::AUTO );
	EXPECT_EQ( cfg1->fPosition.fLeft, 830 );
	EXPECT_EQ( cfg1->fPosition.fTop, 50 );
	EXPECT_EQ( cfg1->fPosition.fWidth, 800 );
	EXPECT_EQ( cfg1->fPosition.fHeight, 600 );


	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("2", &info);
	std::shared_ptr<KFEntityCamera> c2 = info->fCamera;
	std::shared_ptr<KFConfigCamera> cfg2 = info->fCameraConfig;


	EXPECT_EQ(c2->fID, "2");
	EXPECT_EQ(c2->fConfigID, "1");
	EXPECT_EQ(c2->fName, "C-ring 180 inspect");
	EXPECT_EQ(c2->fIsEnabled, true);
	EXPECT_EQ(c2->fIPAddress, "192.168.1.2");
	EXPECT_EQ(c2->fProductID, "someID_1");
	EXPECT_EQ(c2->fCring, "C-ring 180 towards pipe");

	EXPECT_EQ(cfg2->fID, "1");
	EXPECT_EQ(cfg2->fName, "Surface preparation");
	EXPECT_EQ((int)cfg2->fExposutreType, (int)eEXPOSURE_TYPE::AUTO);
	EXPECT_EQ(cfg2->fPosition.fLeft, 830);
	EXPECT_EQ(cfg2->fPosition.fTop, 50);
	EXPECT_EQ(cfg2->fPosition.fWidth, 800);
	EXPECT_EQ(cfg2->fPosition.fHeight, 600);



	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("3", &info);

	std::shared_ptr<KFEntityCamera> c3 = info->fCamera;
	std::shared_ptr<KFConfigCamera> cfg3 = info->fCameraConfig;

	EXPECT_EQ(c3->fID, "3");
	EXPECT_EQ(c3->fConfigID, "2");
	EXPECT_EQ(c3->fName, "C-ring 180 inspect");
	EXPECT_EQ(c3->fIsEnabled, true);
	EXPECT_EQ(c3->fIPAddress, "10.0.0.12");
	EXPECT_EQ(c3->fProductID, "someID_1");
	EXPECT_EQ(c3->fCring, "C-ring 180 towards pipe");

	EXPECT_EQ(cfg3->fID, "2");
	EXPECT_EQ(cfg3->fName, "Structure");
	EXPECT_EQ((int)cfg3->fExposutreType, (int)eEXPOSURE_TYPE::AUTO);
	EXPECT_EQ(cfg3->fPosition.fLeft, 350);
	EXPECT_EQ(cfg3->fPosition.fTop, 560);
	EXPECT_EQ(cfg3->fPosition.fWidth, 1200 );
	EXPECT_EQ(cfg3->fPosition.fHeight, 1800 );

	//delete info;
		
}
