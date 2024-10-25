// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "TestKFMain.h"
#include <kf-main/KFMain.h>


TestKNSTSMain::TestKNSTSMain()
{
}


TestKNSTSMain::~TestKNSTSMain()
{
}


TEST_F( TestKNSTSMain, init )
{
	auto m = KFMain::Instance();

	EXPECT_FALSE(m->DoAutoLogin());
	EXPECT_FALSE( m->DoSimulate());

	m->ScanArguments("-autologin");

	EXPECT_TRUE( m->DoAutoLogin());
	EXPECT_FALSE( m->DoSimulate());
	
	m->ScanArguments("-simulate");

	EXPECT_TRUE( m->DoAutoLogin());
	EXPECT_TRUE( m->DoSimulate());

	m->ScanArguments("-simulate --false  -autologin --false");

	EXPECT_FALSE(m->DoAutoLogin());
	EXPECT_FALSE( m->DoSimulate());

	m->ScanArguments("-simulate --true  -autologin --true");

	EXPECT_TRUE( m->DoAutoLogin());
	EXPECT_TRUE( m->DoSimulate());
}
