// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFXMLWriterCamera.h"
#include <configuration/KFXMLWriterCamera.h>
#include <configuration/KFInfoCamera.h>
#include <configuration/KFConfigurationHandlerCamera.h>
#include <configuration/KFConfigUtilities.h>
#include <kf-main/KFGlobals.h>


void
TestKFXMLWriterCamera::SetUpTestCase()
{
	KFConfigUtilities::Instance()->InitFileXML( "camera_config.xml", fXMLFile );
	KFConfigUtilities::Instance()->InitFileXSD(  KFGlobals::Instance()->GetXSDFilenameCamera().str() , fXSDFile );
}


TEST_F(TestKFXMLWriterCamera, set_modify_get)
{
	p.ParseXML( fCameras_v, fConfig_v, fXMLFile, fXSDFile);
	KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration( fCameras_v,  fConfig_v );
	KFInfoCamera* info = nullptr;
	KFConfigurationHandlerCamera::Instance()->GetCameraInfo( "2", &info);
	ASSERT_NE(info, nullptr);
	EXPECT_EQ( info->fCamera->fIPAddress, "192.168.1.2" );
	info->fCamera->fIPAddress = "192.168.1.123";
	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("2", &info);
	ASSERT_NE(info, nullptr);
	EXPECT_EQ(info->fCamera->fIPAddress, "192.168.1.123");
}


TEST_F(TestKFXMLWriterCamera, write_read_xml)
{
	p.ParseXML( fCameras_v, fConfig_v, fXMLFile, fXSDFile);
	KFConfigurationHandlerCamera::Instance()->SetCameraConfiguration( fCameras_v,  fConfig_v  );
	KFInfoCamera* info = nullptr;
	KFConfigurationHandlerCamera::Instance()->GetCameraInfo("2", &info);
	ASSERT_NE(info, nullptr);
	EXPECT_EQ(info->fCamera->fIPAddress, "192.168.1.2");
	XMLFile_t test_xml = XMLFile_t("write_read.xml");
	//GXmlValidator::IsValid();
	info->fCamera->fIPAddress = "192.168.1.233";
	KFConfigurationHandlerCamera::Instance()->GetCameraConfg(  fCameras_v,  fConfig_v );
	KFXMLWriterCamera().WriteXML(test_xml, fCameras_v,  fConfig_v  );
	p.ParseXML(  fCameras_v,  fConfig_v, test_xml, fXSDFile);
	ASSERT_NE(info, nullptr);
	EXPECT_EQ(info->fCamera->fIPAddress, "192.168.1.233");
}