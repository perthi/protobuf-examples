// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GlobalRegistry.h"
#include <logging/LLogApi.h>
#include <common/GComponent.h>
#include <common/MBPostOffice.h>

using namespace LOGMASTER;


GlobalRegistry * GlobalRegistry::Instance()
{
	static  GlobalRegistry * instance = new GlobalRegistry();
	return instance;
}


void 
GlobalRegistry::CleanUp()
{
	FORCE_DEBUG("Cleaning up, number of registered components = %d", fComponentRegister.size() );
	for ( size_t i = 0; i < fComponentRegister.size();  i++ )
	{
		FORCE_DEBUG( "component[%d]: name = %s, id = %s ", i, fComponentRegister[i]->GetName().c_str(), fComponentRegister[i]->GetComponentID().c_str() );
		fComponentRegister[i]->StopComponent();
	}
}


GlobalRegistry::GlobalRegistry()
{

}


GlobalRegistry::~GlobalRegistry()
{

}


void 
GlobalRegistry::RegisterComponent( std::shared_ptr<GComponent> component )
{
	fComponentRegister.push_back( component );
}
