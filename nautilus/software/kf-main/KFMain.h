// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include  <common/FDefinitions.h>
#include  <cmdline/GLogApplication.h>

class APIFSMController;

class KFMain : public GLogApplication
{
public:
	API ~KFMain( );
	static 	KFMain API * Instance( );
	void Start();
	void Stop();

	APIFSMController * GetFSMController() { return fFSMController; };
	void API InitFSM();
	void API InitComponents();


private:
	API KFMain(const string commandline = "");
	API KFMain(int argc,  const char **argv );
	void InitArgs( );

	APIFSMController *fFSMController = nullptr;
};

