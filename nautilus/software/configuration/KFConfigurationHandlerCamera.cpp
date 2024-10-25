// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "KFConfigurationHandlerCamera.h"
#include <utilities/GException.h>
#include <utilities/GUtilities.h>


KFConfigurationHandlerCamera * KFConfigurationHandlerCamera::Instance()
{
	static KFConfigurationHandlerCamera* instance = new KFConfigurationHandlerCamera();
	return instance;
}


void
KFConfigurationHandlerCamera::SetCameraConfiguration(const vector< std::shared_ptr< KFEntityCamera> >& c, const vector<  std::shared_ptr< KFConfigCamera> >& cfg)
{
	EraseCameraList();
	EraseCameraConfigs();
	
	for (size_t i = 0; i < c.size(); i++)
	{
		AddUniqueCamera(c.at(i));
	}

	for (size_t i = 0; i < cfg.size(); i++)
	{
		AddUniqueCameraConfig(cfg.at(i));
	}
}


void 
KFConfigurationHandlerCamera::AddUniqueCamera( const std::shared_ptr<KFEntityCamera> c)
{
	if (fCameraList.count(c->fID) != 0)
	{
		EXCEPTION("Camera config with ID %s allready exists, please check tyour XML config file", c->fID.c_str() );
	}
	else
	{
		fCameraList.emplace(c->fID, c );
	}
}



void 
KFConfigurationHandlerCamera::AddUniqueCameraConfig( const std::shared_ptr<KFConfigCamera> c)
{
	if (fCameraConfigs.count(c->fID) != 0)
	{
		EXCEPTION("Camera config with ID %s allready exists, please check tyour XML config file", c->fID.c_str());
	}
	else
	{
		fCameraConfigs.emplace(c->fID, c );
	}
}


/** @brief checks that the camrea configuration ID refered to by a camera actually exists
 *  in the list of camera configurations */
void 
KFConfigurationHandlerCamera::CheckCameraConfigurations()
{
	for (auto it = fCameraList.begin(); it != fCameraList.end() ; it++)
	{
		auto  cfg_ptr = FindConfiguration( it->second);

		if (cfg_ptr == nullptr)
		{		
			EXCEPTION("Could not find configuration with ID, you must add the camera configuration before adding the camera %s",
				it->second->fConfigID.c_str() );
		}
	}
}


std::shared_ptr<KFConfigCamera> 
KFConfigurationHandlerCamera::FindConfiguration( std::shared_ptr<KFEntityCamera> c)
{

	string key = c->fConfigID;
	auto cfg = fCameraConfigs.find( key );
	
	if ( cfg == fCameraConfigs.end() )
	{
		return nullptr;
	}
	else
	{
		return cfg->second;
	}
	
	
}


vector<KFInfoCamera>
KFConfigurationHandlerCamera::GetCameraInfo()
{	
	vector<KFInfoCamera> vec;

	for (auto it = fCameraList.begin(); it != fCameraList.end(); it++)
	{
		KFInfoCamera f;
		auto cfg = FindConfiguration(it->second);
		G_ASSERT_EXCEPTION(cfg != nullptr, "configuration is ZERO pointer");
		f.fCamera = it->second;
		f.fCameraConfig = cfg;
		vec.push_back(f);
	}

	return vec;
}


void 
KFConfigurationHandlerCamera::GetCameraInfo(const string key, KFInfoCamera **info)
{

	auto it = fCameraList.find(key);
	
	if (it == fCameraList.end())
	{
		G_ERROR("Could not find camera with key %s", key.c_str() );
	}
	else
	{	
		*info = new KFInfoCamera();
		std::shared_ptr< KFEntityCamera > c = it->second;
		std::shared_ptr< KFConfigCamera >  cfg = FindConfiguration(c);		
		G_ASSERT_EXCEPTION(cfg !=nullptr, "Configuration is ZERO pointer" );

		(*info)->fCamera = c;

		(*info)->fCameraConfig = cfg;
	}

}


void 
KFConfigurationHandlerCamera::EraseCameraList()
{
	fCameraList.erase(fCameraList.begin(), fCameraList.end());
}


void
KFConfigurationHandlerCamera::EraseCameraConfigs()
{
	fCameraConfigs.erase(fCameraConfigs.begin(), fCameraConfigs.end());
}


void 
KFConfigurationHandlerCamera::GetCameraConfg(vector<std::shared_ptr<KFEntityCamera> >& c, vector< std::shared_ptr<KFConfigCamera> >& c_cfg)
{
	c.erase(c.begin(), c.end());
	c_cfg.erase ( c_cfg.begin(), c_cfg.end() );
	c = g_utilities()->Hash2SContentV( &fCameraList);
	c_cfg = g_utilities()->Hash2SContentV( &fCameraConfigs );
}
