
#include "TestKFConfigurationHandler.h"


#include <configuration/KFConfigurationHandler.h>
#include <configuration/KFXMLParserDevices.h>
#include <configuration/KFConfigUtilities.h>

#include <kf-main/KFGlobals.h>

void
TestKFConfigurationHandler::SetUpTestCase()
{
	cfg = KFConfigurationHandler::Instance();
	cfg->ParseConfigDevices( XMLFile_t("kf_config_unittest.xml"), KFGlobals::Instance()->GetXSDFilenameDevices() );
	cfg->ParseConfigHmi( XMLFile_t("kf_hmi_unittest.xml"), KFGlobals::Instance()->GetXSDFilenameHmi() );
}


void
TestKFConfigurationHandler::TearDownTestCase()
{
	//cfg->Purge();
}



TEST_F(TestKFConfigurationHandler, get_by_ip )
{


	try
	{
	///	cfg->ParseDefaultConfig();

		auto cfg = KFConfigurationHandler::Instance();
		auto devices = cfg->GetDevicesByIP("192.168.0.1");
		EXPECT_EQ(devices.size(), 3);
		devices = cfg->GetDevicesByIP("192.168.1.17");
		ASSERT_EQ(devices.size(), 1);

		devices.at(0)->fDeviceTypeS = "MotorStepper";
		devices.at(0)->fAddress.fDeviceID = "L1-M42";

		devices = cfg->GetDevicesByIP("192.168.1.18");
		EXPECT_EQ(devices.size(), 3);

		devices = cfg->GetDevicesByIP("192.168.1.2");
		EXPECT_EQ(devices.size(), 2);
	}
	catch (GException& e)
	{
		cout << e.what() << endl;
		throw(e);
	}
}



TEST_F(TestKFConfigurationHandler, get_by_hmi_type)
{
	PUSH();
	SET_LOGTARGET("--target-stdout");
	SET_LOGLEVEL("--all-info");

	try
	{
		EXPECT_NO_THROW(cfg->GetByHMIType(eHMI_TYPE::CRING180));
		EXPECT_NO_THROW(cfg->GetByHMIType(eHMI_TYPE::CRING360));
		EXPECT_NO_THROW(cfg->GetByHMIType(eHMI_TYPE::COATING));
		EXPECT_NO_THROW(cfg->GetByHMIType(eHMI_TYPE::SURFACE_PREP));
		EXPECT_NO_THROW(cfg->GetByHMIType(eHMI_TYPE::WRAPPING));
	}
	catch ( GException e)
	{
		cout << e.what() << endl;
		POP();
		throw(e);
	}
	catch (std::exception& e)
	{
		CERR << e.what() << endl;
		POP();
		throw(e);
	}
	catch (string& e)
	{
		CERR << e << endl;
		POP();
		throw(e);
	}

	catch (...)
	{
		CERR << "Uniknown exeption caught" << endl;
		POP();
		throw("unknown exception");
	}
	POP();
}




TEST_F( TestKFConfigurationHandler, sizes )
{
	ASSERT_NE(cfg, nullptr);

	try
	{

		cfg->ParseConfigDevices( XMLFile_t("kf_config_unittest.xml"), KFGlobals::Instance()->GetXSDFilenameDevices() );
		cfg->ParseConfigHmi( XMLFile_t("kf_hmi_unittest.xml"), KFGlobals::Instance()->GetXSDFilenameHmi() );
		EXPECT_EQ( cfg->GetEntitiesDevices().size(), 14  );
		EXPECT_EQ(cfg->GetEntitiesHMI().size(), 6 );
	}
	catch( GException &e )
	{
		CERR << e.what();

		throw(e);
	}

//	POP();
}

