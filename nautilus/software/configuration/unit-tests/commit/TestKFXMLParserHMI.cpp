

#include "TestKFXMLParserHMI.h"


#include <configuration/KFXMLParserHMI.h>
#include <configuration/KFConfigurationHandler.h>
#include <configuration/KFEntityHMICRing.h>
#include <configuration/KFEntityHMIOperation.h>
#include <configuration/KFConfigUtilities.h>


void
TestKFXMLParserHMI::SetUpTestCase()
{
	PUSH();

	SET_LOGTARGET("--target-off --target-file");
	KFConfigUtilities::Instance()->InitFileXML( "kf_hmi_unittest.xml",  fXMLFile );
	KFConfigUtilities::Instance()->InitFileXSD( "kf_hmi.xsd", fXSDFile );
	p = new KFXMLParserHMI();
	cfg = KFConfigurationHandler::Instance();


	POP();
}



void
TestKFXMLParserHMI::SetUp()
{
	Parse(fXMLFile, fXSDFile, p);
	EXPECT_EQ( cfg->GetEntitiesHMI().size(), 6 );
}


void
TestKFXMLParserHMI::TearDown()
{
	cfg->Purge();
	EXPECT_EQ( cfg->GetEntitiesHMI().size(), 0 );
}


TEST_F( TestKFXMLParserHMI, no_entities )
{
	EXPECT_EQ( cfg->GetEntitiesHMI().size(), 6 );
	cfg->Purge();
	EXPECT_EQ( cfg->GetEntitiesHMI().size(), 0 );
}



TEST_F( TestKFXMLParserHMI, exists )
{
	EXPECT_NE( nullptr, cfg->GetHMIByID("C180")  );
	EXPECT_NE( nullptr, cfg->GetHMIByID("C360")  );
	EXPECT_NE( nullptr, cfg->GetHMIByID("SP") );
	EXPECT_NE( nullptr, cfg->GetHMIByID("COATING") );
	EXPECT_NE( nullptr, cfg->GetHMIByID("WR")  );
	EXPECT_EQ( nullptr, cfg->GetHMIByID("") );
	EXPECT_EQ( nullptr, cfg->GetHMIByID("blahhhhh") );
}



TEST_F( TestKFXMLParserHMI, fields_cring180 )
{
	std::shared_ptr<KFEntityHMICRing> c = std::dynamic_pointer_cast<KFEntityHMICRing> (cfg->GetHMIByID("C180") );
	ASSERT_NE(c, nullptr);
	EXPECT_EQ((int)c->fType, (int)eHMI_TYPE::CRING180);
	EXPECT_EQ( c->fTitle, "C-Ring 180" );
	EXPECT_EQ( c->fHMIID, "C180");
	EXPECT_EQ( c->fDeviceID, "L1-VXY1");

	EXPECT_EQ( (int)c->fNavigatorTranslation.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ( c->fNavigatorTranslation.fCaption.fCaption, "Translation");
	EXPECT_EQ( c->fNavigatorTranslation.fCaption.fCaptionMin, "Left");
	EXPECT_EQ( c->fNavigatorTranslation.fCaption.fCaptionMax, "Right");

	vector<int> steps =   c->fNavigatorTranslation.fSteps;

	ASSERT_EQ( steps.size(), 3 );

	EXPECT_EQ(steps[0], 1 );
	EXPECT_EQ(steps[1], 2 );
	EXPECT_EQ(steps[2], 3 );


	EXPECT_EQ( c->fNavigatorTranslation.fDeviceID, "L1-VXY1" );
	EXPECT_EQ( (int)c->fIndicatorTranslation.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ( c->fIndicatorTranslation.fCanDecrement, true );
	EXPECT_EQ( c->fIndicatorTranslation.fCaption.fCaption, "Translation" );
	EXPECT_EQ( c->fIndicatorTranslation.fCaption.fCaptionMin, "FORE" );
	EXPECT_EQ( c->fIndicatorTranslation.fCaption.fCaptionMax, "STARBOARD" );
	EXPECT_EQ( c->fIndicatorTranslation.fMinValue, -3000 );
	EXPECT_EQ( c->fIndicatorTranslation.fMaxValue,  3000 );
	EXPECT_EQ( c->fIndicatorTranslation.fDeviceID, "L1-VXY1" );

	EXPECT_EQ( (int)c->fNavigatorRotation.fOrientation, (int)eORIENTATION::VERTICAL );
	EXPECT_EQ( c->fNavigatorRotation.fCaption.fCaption, "Rotation" );
	EXPECT_EQ( c->fNavigatorRotation.fCaption.fCaptionMin, "CW" );
	EXPECT_EQ( c->fNavigatorRotation.fCaption.fCaptionMax, "CCW" );

	steps =   c->fNavigatorRotation.fSteps;

	ASSERT_EQ( steps.size(), 4 );
	EXPECT_EQ(steps[0], 1 );
	EXPECT_EQ(steps[1], 30 );
	EXPECT_EQ(steps[2], 50 );
	EXPECT_EQ(steps[3], 70 );
	EXPECT_EQ( c->fNavigatorRotation.fDeviceID, "L1-VXY1" );
	EXPECT_EQ( (int)c->fIndicatorRotation.fOrientation, (int)eORIENTATION::VERTICAL );
	EXPECT_EQ( c->fIndicatorRotation.fCanDecrement, true );
	EXPECT_EQ( c->fIndicatorRotation.fCaption.fCaption, "Direction");
	EXPECT_EQ( c->fIndicatorRotation.fCaption.fCaptionMin, "CC");
	EXPECT_EQ( c->fIndicatorRotation.fCaption.fCaptionMax, "CCW");
	EXPECT_EQ( c->fIndicatorRotation.fMinValue, 3 );
	EXPECT_EQ( c->fIndicatorRotation.fMaxValue, 4 );
	EXPECT_EQ( c->fIndicatorRotation.fDeviceID, "L1-VXY1");

}



TEST_F( TestKFXMLParserHMI, fields_cring360 )
{
	std::shared_ptr<KFEntityHMICRing> c = std::dynamic_pointer_cast<KFEntityHMICRing> (cfg->GetHMIByID("C360") );
	ASSERT_NE(c, nullptr);
	EXPECT_EQ((int)c->fType, (int)eHMI_TYPE::CRING360);
	EXPECT_EQ( c->fTitle, "C-Ring 360" );
	EXPECT_EQ( c->fHMIID, "C360");
	EXPECT_EQ( c->fDeviceID, "L2-VXY2");
	EXPECT_EQ( (int)c->fNavigatorTranslation.fOrientation, (int)eORIENTATION::HORIZONTAL);


	EXPECT_EQ( c->fNavigatorTranslation.fCaption.fCaption, "TRanslation C-360");
	EXPECT_EQ( c->fNavigatorTranslation.fCaption.fCaptionMin, "Fore");
	EXPECT_EQ( c->fNavigatorTranslation.fCaption.fCaptionMax, "Aft");

	vector<int> steps =   c->fNavigatorTranslation.fSteps;

	ASSERT_EQ( steps.size(), 3 );

	EXPECT_EQ(steps[0], 1 );
	EXPECT_EQ(steps[1], 100 );
	EXPECT_EQ(steps[2], 200 );
	EXPECT_EQ(c->fNavigatorTranslation.fDeviceID, "L2-VXY2");

	EXPECT_EQ( (int)c->fIndicatorTranslation.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ( c->fIndicatorTranslation.fCanDecrement, true );
	EXPECT_EQ( c->fIndicatorTranslation.fCaption.fCaption, "" );
	EXPECT_EQ( c->fIndicatorTranslation.fCaption.fCaptionMin, "" );
	EXPECT_EQ( c->fIndicatorTranslation.fCaption.fCaptionMax, "" );
	EXPECT_EQ( c->fIndicatorTranslation.fMinValue, 0 );
	EXPECT_EQ( c->fIndicatorTranslation.fMaxValue,  0 );
	EXPECT_EQ( c->fIndicatorTranslation.fDeviceID, "L2-VXY2" );


	EXPECT_EQ( (int)c->fNavigatorRotation.fOrientation, (int)eORIENTATION::VERTICAL );
	EXPECT_EQ( c->fNavigatorRotation.fCaption.fCaption, "Rotation" );
	EXPECT_EQ( c->fNavigatorRotation.fCaption.fCaptionMin, "Port" );
	EXPECT_EQ( c->fNavigatorRotation.fCaption.fCaptionMax, "Starboard" );

	steps = c->fNavigatorRotation.fSteps;
	ASSERT_EQ( steps.size(), 7 );
	EXPECT_EQ(steps[0], 1 );
	EXPECT_EQ(steps[1], 20 );
	EXPECT_EQ(steps[2], 3 );
	EXPECT_EQ(steps[3], 4 );
	EXPECT_EQ(steps[4], 5 );
	EXPECT_EQ(steps[5], 6 );
	EXPECT_EQ(steps[6], 7 );

	EXPECT_EQ( c->fNavigatorRotation.fDeviceID, "L2-VXY2" );
	EXPECT_EQ( (int)c->fIndicatorRotation.fOrientation, (int)eORIENTATION::VERTICAL );
	EXPECT_EQ( c->fIndicatorRotation.fCanDecrement, true );
	EXPECT_EQ( c->fIndicatorRotation.fCaption.fCaption, "Rotation C-360");
	EXPECT_EQ( c->fIndicatorRotation.fCaption.fCaptionMin, "CCW");
	EXPECT_EQ( c->fIndicatorRotation.fCaption.fCaptionMax, "CC");
	EXPECT_EQ( c->fIndicatorRotation.fMinValue, -1000 );
	EXPECT_EQ( c->fIndicatorRotation.fMaxValue, 1500 );
	EXPECT_EQ( c->fIndicatorRotation.fDeviceID, "L2-VXY2");
}



TEST_F(TestKFXMLParserHMI, fields_surface_prep)
{
	std::shared_ptr< KFEntityHMIOperation > o = std::dynamic_pointer_cast< KFEntityHMIOperation > (cfg->GetHMIByID("SP"));
	ASSERT_NE(o, nullptr);
	EXPECT_EQ((int)o->fType, (int)eHMI_TYPE::SURFACE_PREP );
	EXPECT_EQ(o->fTitle, "Surface Preparation");
	EXPECT_EQ(o->fHMIID, "SP");

	EXPECT_EQ((int)o->fNavigatorMain.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ( o->fNavigatorMain.fCaption.fCaption, "Surface Prep");
	EXPECT_EQ( o->fNavigatorMain.fCaption.fCaptionMin, "Home");
	EXPECT_EQ( o->fNavigatorMain.fCaption.fCaptionMax, "Flow Line");
	vector<int> steps = o->fNavigatorMain.fSteps;
	ASSERT_EQ(steps.size(), 3 );
	EXPECT_EQ( steps[0], 1  );
	EXPECT_EQ( steps[1], 5  );
	EXPECT_EQ( steps[2], 20 );

	EXPECT_EQ( o->fNavigatorMain.fDeviceID, "L1-M42");

	EXPECT_EQ( (int)o->fIndicatorMain.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(o->fIndicatorMain.fCanDecrement, true);
	EXPECT_EQ( o->fIndicatorMain.fCaption.fCaption, "Position");
	EXPECT_EQ( o->fIndicatorMain.fCaption.fCaptionMin, "0");
	EXPECT_EQ( o->fIndicatorMain.fCaption.fCaptionMax, "100");

	EXPECT_EQ(o->fIndicatorMain.fMinValue, 0);
	EXPECT_EQ(o->fIndicatorMain.fMaxValue, 100);
	EXPECT_EQ(o->fIndicatorMain.fDeviceID, "L1-M44");
}



TEST_F(TestKFXMLParserHMI, fields_coating )
{
	std::shared_ptr< KFEntityHMIOperation > o = std::dynamic_pointer_cast<KFEntityHMIOperation> (cfg->GetHMIByID("COATING"));
	ASSERT_NE(o, nullptr);
	EXPECT_EQ((int)o->fType, (int)eHMI_TYPE::COATING);
	EXPECT_EQ(o->fTitle, "Coating");
	EXPECT_EQ(o->fHMIID, "COATING");

	EXPECT_EQ((int)o->fNavigatorMain.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(o->fNavigatorMain.fCaption.fCaption, "Coating");
	EXPECT_EQ(o->fNavigatorMain.fCaption.fCaptionMin, "Home");
	EXPECT_EQ(o->fNavigatorMain.fCaption.fCaptionMax, "Flow Line");
	vector<int> steps = o->fNavigatorMain.fSteps;
	ASSERT_EQ(steps.size(), 2);
	EXPECT_EQ(steps[0], 1);
	EXPECT_EQ(steps[1], 10);

	EXPECT_EQ(o->fNavigatorMain.fDeviceID, "L2-M46");

	EXPECT_EQ((int)o->fIndicatorMain.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(o->fIndicatorMain.fCanDecrement, false);
	EXPECT_EQ(o->fIndicatorMain.fCaption.fCaption, "Position");
	EXPECT_EQ(o->fIndicatorMain.fCaption.fCaptionMin, "0");
	EXPECT_EQ(o->fIndicatorMain.fCaption.fCaptionMax, "mL/min");

	EXPECT_EQ(o->fIndicatorMain.fMinValue, 0);
	EXPECT_EQ(o->fIndicatorMain.fMaxValue, 100);
	EXPECT_EQ(o->fIndicatorMain.fDeviceID, "L2-M47");

}


TEST_F(TestKFXMLParserHMI, wrapping  )
{

	std::shared_ptr< KFEntityHMIOperation > o = std::dynamic_pointer_cast<KFEntityHMIOperation> (cfg->GetHMIByID("WR"));
	ASSERT_NE(o, nullptr);
	EXPECT_EQ((int)o->fType, (int)eHMI_TYPE::WRAPPING );
	EXPECT_EQ(o->fTitle, "Wrapping");
	EXPECT_EQ(o->fHMIID, "WR");

	EXPECT_EQ((int)o->fNavigatorMain.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(o->fNavigatorMain.fCaption.fCaption, "Wrapping");
	EXPECT_EQ(o->fNavigatorMain.fCaption.fCaptionMin, "Home");
	EXPECT_EQ(o->fNavigatorMain.fCaption.fCaptionMax, "Flow Line");

	vector<int> steps = o->fNavigatorMain.fSteps;
	ASSERT_EQ(steps.size(), 4);
	EXPECT_EQ(steps[0], 1 );
	EXPECT_EQ(steps[1], 10 );
	EXPECT_EQ(steps[2], 25 );
	EXPECT_EQ(steps[3], 50 );

	EXPECT_EQ(o->fNavigatorMain.fDeviceID, "L2-M47");


	EXPECT_EQ((int)o->fIndicatorMain.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(o->fIndicatorMain.fCanDecrement, true);
	EXPECT_EQ(o->fIndicatorMain.fCaption.fCaption, "Position");
	EXPECT_EQ(o->fIndicatorMain.fCaption.fCaptionMin, "");
	EXPECT_EQ(o->fIndicatorMain.fCaption.fCaptionMax, "");

	EXPECT_EQ(o->fIndicatorMain.fMinValue, 9);
	EXPECT_EQ(o->fIndicatorMain.fMaxValue, 100);
	EXPECT_EQ(o->fIndicatorMain.fDeviceID, "L1-M44");

	auto controls = o->fControls;

	ASSERT_EQ(controls.size(), 2);
	auto c1 = controls.at(0);


	EXPECT_EQ(  (int)c1.fControl.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(  c1.fControl.fCaption.fCaption, "Test");
	EXPECT_EQ(  c1.fControl.fCaption.fCaptionMin, "Min");
	EXPECT_EQ(  c1.fControl.fCaption.fCaptionMax, "Max");
	steps =  c1.fControl.fSteps;
	ASSERT_EQ(steps.size(), 2);
	EXPECT_EQ(  steps.at(0), 10   );
	EXPECT_EQ(  steps.at(1), 100  );
	EXPECT_EQ(  c1.fControl.fMinValue, 1);
	EXPECT_EQ(  c1.fControl.fMaxValue, 2000);
	EXPECT_EQ(  c1.fControl.fDeviceID, "L1-M42");

	EXPECT_EQ(  (int)c1.fIndicator.fOrientation,  (int)eORIENTATION::HORIZONTAL );
	EXPECT_EQ(  c1.fIndicator.fCanDecrement, true);
	EXPECT_EQ(  c1.fIndicator.fCaption.fCaption, "Force");
	EXPECT_EQ(  c1.fIndicator.fCaption.fCaptionMin, "0N");
	EXPECT_EQ(  c1.fIndicator.fCaption.fCaptionMax, "2000N");
	EXPECT_EQ(c1.fIndicator.fDeviceID, "L2-M46");

	auto c2 = controls.at(1);
	EXPECT_EQ( (int)c2.fControl.fOrientation, (int)eORIENTATION::HORIZONTAL);


	EXPECT_EQ(c2.fControl.fCaption.fCaption, "");
	EXPECT_EQ(c2.fControl.fCaption.fCaptionMin, "");
	EXPECT_EQ(c2.fControl.fCaption.fCaptionMax, "");

	steps = c2.fControl.fSteps;
	ASSERT_EQ(steps.size(), 2);
	EXPECT_EQ(steps.at(0), 1);
	EXPECT_EQ(steps.at(1), 10);
	EXPECT_EQ(c2.fControl.fMinValue, 9);
	EXPECT_EQ(c2.fControl.fMaxValue, 100);
	EXPECT_EQ(c2.fControl.fDeviceID, "L2-M46");
	EXPECT_EQ( (int)c2.fIndicator.fOrientation, (int)eORIENTATION::HORIZONTAL);
	EXPECT_EQ(c2.fIndicator.fCanDecrement, false);
	EXPECT_EQ(c2.fIndicator.fCaption.fCaption, "Resin Used");
	EXPECT_EQ(c2.fIndicator.fCaption.fCaptionMin, "0mL");
	EXPECT_EQ(c2.fIndicator.fCaption.fCaptionMax, "100mL");
	EXPECT_EQ(c2.fIndicator.fDeviceID, "L33-PWM1");
}

