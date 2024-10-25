// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#include "KFMain.h"
#include <logging/LLogApi.h>
#include <cmdline/GCmdApi.h>
#include <cmdline/GCommandLineArgument.h>
#include <utilities/GConstants.h>
#include <api/api-fsm/APIFSMController.h>
#include <common/GComponentTimer.h>

using namespace LOGMASTER;
using namespace GCONSTANTS;

KFMain::KFMain( const string cmdline ) : GLogApplication(false)
{
	GComponentTimer::Instance();
	fFSMController =  APIFSMController::Instance();
	InitArgs();
	ScanArguments(cmdline );
}

KFMain::KFMain( int argc, const char **argv ) : GLogApplication(false)
{
	GComponentTimer::Instance();
	fFSMController =  APIFSMController::Instance();
	InitArgs();
	ScanArguments( argc, argv );
}

KFMain  *
KFMain::Instance( )
{
	static  KFMain * instance = new KFMain();
	return instance;
}

void
KFMain::InitFSM()
{
	fFSMController->InitFSM();
}

void
KFMain::InitComponents()
{
	GComponentTimer::Instance();
}

KFMain::~KFMain()
{

}

void
KFMain::InitArgs()
{
///	GCommandLineArgument<bool> *isim = new GCommandLineArgument <bool>("-simulate", "-simulate", "Force all instruments to simulation mode", &fDoSimulate, GCONSTANTS::fgkOPTIONAL, GCmdApi::bool2);
//	AddArgument(isim);
}
