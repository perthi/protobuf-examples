// -*- mode: c++ -*-

#pragma once


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <utilities/GDefinitions.h>
#include <configuration/KFEntityCamera.h>
#include <configuration/KFConfigCamera.h>
#include <configuration/KFInfoCamera.h>

#include <map>
#include <vector>

#include <memory>

using  std::vector;




class KFConfigurationHandlerCamera
{	
//	friend  FGlobalConfig  g_cmdscan();

public:
	static   KFConfigurationHandlerCamera API * Instance();
	void API SetCameraConfiguration( const vector< std::shared_ptr<KFEntityCamera> > &c, const vector< std::shared_ptr<KFConfigCamera> > &cfg  );
	void API AddUniqueCamera( const std::shared_ptr<KFEntityCamera> c );
	void API AddUniqueCameraConfig( const std::shared_ptr<KFConfigCamera> c);
	void API CheckCameraConfigurations();
	std::shared_ptr<KFConfigCamera> API  FindConfiguration( std::shared_ptr<KFEntityCamera> c);
	vector<KFInfoCamera> API GetCameraInfo();
	void  API GetCameraInfo(const string key, KFInfoCamera **);
	void API EraseCameraList();
	void API EraseCameraConfigs();

	void API GetCameraConfg( vector< std::shared_ptr<KFEntityCamera>  > &c,  vector< std::shared_ptr<KFConfigCamera > > &c_cfg );

private:
	KFConfigurationHandlerCamera() {};
	std::map<string, std::shared_ptr<KFEntityCamera> > fCameraList; //! < Avilable cameras
	std::map<string, std::shared_ptr<KFConfigCamera> > fCameraConfigs; //! < Avilable camera configurations
};

