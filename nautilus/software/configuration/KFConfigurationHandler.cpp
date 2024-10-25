// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/

#include "KFConfigurationHandler.h"

#include <utilities/GException.h>
#include <logging/LLogApi.h>
using namespace LOGMASTER;

#include <configuration/KFConfigUtilities.h>

#include "KFXMLParserDevices.h"
#include "KFXMLParserHMI.h"

#include  "KFEntityHMIOperation.h"
#include  "KFEntityHMICRing.h"
#include  <utilities/GFileIOHandler.h>
#include  <common/MBMessageInfo.h>
#include  <kf-common/KFXMLFiles.h>
#include  <kf-common/KFConfigXML.h>
#include <kf-main/KFGlobals.h>

#include <sstream>


KFConfigurationHandler::KFConfigurationHandler() : GComponent("CONFIGURATION_HANDLER")
{
	DoSubscribe("CONFIG_HANDLER");
//	ParseDefaultConfig();
	StartComponent();
}


KFConfigurationHandler::~KFConfigurationHandler()
{

}


KFConfigurationHandler *
KFConfigurationHandler::Instance()
{
    static  KFConfigurationHandler *instance = new KFConfigurationHandler();
    return instance;
}


void 
KFConfigurationHandler::ParseConfig( std::shared_ptr<MBMessageInfo>  message_info , KFConfigXML &config )
{
	ENGINE_DEBUG( "%s" , message_info->str().c_str()  );

	auto payload =  message_info->fMessage->ExtractRawPayload< KFXMLFiles>();
	
	if( payload == nullptr)
	{
		G_FATAL("Payload is ZERO POINTER");
		
		std::shared_ptr< MBMessageT<int > > reply = std::make_shared< MBMessageT< int > >( -1 );
		message_info->fPromise.set_value( reply );
	}
	else
	{
		ENGINE_INFO( "device file =\t%s",  payload->fDevices.c_str() );
		ENGINE_INFO( "hmi file = %s\t",    payload->fHmi.c_str() );
		
		XSDFile_t xsd_devices  =  KFGlobals::Instance()->GetXSDFilenameDevices();
		XSDFile_t xsd_hmi  =      KFGlobals::Instance()->GetXSDFilenameHmi();
		XMLFile_t xml_devices = XMLFile_t(payload->fDevices);
		XMLFile_t xml_hmi = XMLFile_t(payload->fHmi);

		ParseConfigDevices(  xml_devices, xsd_devices );
		ParseConfigHmi( xml_hmi, xsd_hmi );	

		config.fEntitiesDevices = fEntitiesDevices;
		config.fEntitiesHMI = fEntitiesHMI;
	}

}
 

void  
KFConfigurationHandler::ProcessMessageBlocking( std::shared_ptr<MBMessageInfo>  message_info )
{
	ENGINE_INFO("Handling blocking message %s: message source = %s",  fName.c_str(),  
									message_info->fMessage->fOriginator.c_str() );
	KFConfigXML config;
	ParseConfig( message_info, config );
	std::shared_ptr< MBMessageT< KFConfigXML > > reply = std::make_shared< MBMessageT< KFConfigXML > >(  config  );
	message_info->fPromise.set_value( reply );
}


void  
KFConfigurationHandler::ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  message_info)
{
	KFConfigXML config;
	ParseConfig( message_info, config );
	SendMessageRaw(config, "OUT::CONFIG_HANDLER");
}


void 
KFConfigurationHandler::InitFiles(  const XMLFile_t xml_fname_in,  XMLFile_t &xml_out,  
									const XSDFile_t xsd_fname_in,  XSDFile_t &xsd_out )
{
	KFConfigUtilities::Instance()->InitFileXML(  xml_fname_in.str() ,   xml_out );
	KFConfigUtilities::Instance()->InitFileXSD(  xsd_fname_in.str(),  xsd_out );

	XML_ASSERT_EXCEPTION( g_file()->DoExists(xml_out.str()) == true, "file: %s could not be opened for reading", xml_out.str().c_str()  );
	XML_ASSERT_EXCEPTION( g_file()->DoExists(xsd_out.str()) == true, "file: %s could not be opened for reading", xsd_out.str().c_str()  );
	XML_INFO("xml = %s, xsd = %s", xml_out.str().c_str(), xsd_out.str().c_str() );
}


void
KFConfigurationHandler::ParseConfigDevices(  const XMLFile_t xml_name, const XSDFile_t xsd_name  )
{
	XMLFile_t xml;
	XSDFile_t xsd;
	InitFiles( xml_name, xml, xsd_name, xsd );
	fEntitiesDevices.erase(fEntitiesDevices.begin(),   fEntitiesDevices.end()  ) ;
	std::shared_ptr<KFXMLParserDevices>  p_dev = std::make_shared<KFXMLParserDevices>();
	auto entities = p_dev->ParseXML(xml, xsd);
	ENGINE_INFO("parsing Devices");
	ENGINE_INFO("no devices = %d", entities.size() );
	AddEntities( entities );
}



void
KFConfigurationHandler::ParseConfigHmi(  const XMLFile_t xml_name, const XSDFile_t xsd_name  )
{
	XMLFile_t xml;
	XSDFile_t xsd;
	InitFiles( xml_name, xml, xsd_name, xsd );
	fEntitiesHMI.erase( fEntitiesHMI.begin(),  fEntitiesHMI.end() );
	std::shared_ptr<KFXMLParserHMI>  p_hmi = std::make_shared<KFXMLParserHMI>();
	ENGINE_INFO("parsing HMI");
	auto entities = p_hmi->ParseXML(xml, xsd);
	ENGINE_INFO("number of HMI entities = %d", entities.size() );	
	AddEntities( entities);
}



void
KFConfigurationHandler::ParseConfigDevices(  const XMLFile_t xml_name   )
{
	XSDFile_t xsd = KFGlobals::Instance()->GetXSDFilenameDevices();
	ParseConfigDevices( xml_name, xsd );
}


void
KFConfigurationHandler::ParseConfigHmi(  const XMLFile_t xml_name )
{
	XSDFile_t xsd = KFGlobals::Instance()->GetXSDFilenameHmi();
	ParseConfigHmi( xml_name, xsd );
}



std::map<string, std::shared_ptr< KFEntityDevice > >
KFConfigurationHandler::GetEntitiesDevices()
{
	return fEntitiesDevices;
}


std::map<string, std::shared_ptr< KFEntityHMI > >
KFConfigurationHandler::GetEntitiesHMI()
{
	return fEntitiesHMI;
}


std::shared_ptr<KFEntityHMI> 
KFConfigurationHandler::GetByHMIType( eHMI_TYPE type )
{
	return KFConfigUtilities::Instance()->GetByHMIType(type, &fEntitiesHMI);
}


void
KFConfigurationHandler::Purge()
{
  	fEntitiesDevices.erase( fEntitiesDevices.begin(), fEntitiesDevices.end() );
	fEntitiesHMI.erase( fEntitiesHMI.begin(), fEntitiesHMI.end() );
}



/** Check that there is consistency between the hmi and device configuration.
Each device ID specified in the HMI configuration must be present also in the
device configuration, othervise there is an error.
@param[in]  policy if set to STRICT (default) then an exception is thrown if an  error is encounter, if set to
RELAXED then an error message is written, and the function returns false
@exception if policy is STRICT and the configuration is inconsistent
@return true if the configuration is consistent, false if configuration is
inconsistent and the policy is set to RELAXED  */
bool
KFConfigurationHandler::CheckConsistency(const int policy )
{
	struct Device
	{
		Device(const string id, std::shared_ptr<KFEntityHMI> device) : fDeviceID(id), fDevice(device) {};
		string fDeviceID;
		std::shared_ptr<KFEntityHMI> fDevice;
	};

	bool is_consisten = true;
	vector<string> offending_ids;

	ENGINE_ASSERT_EXCEPTION( fEntitiesDevices.size() > 0, "No devices found (size = %d)", fEntitiesDevices.size());
	ENGINE_ASSERT_EXCEPTION( fEntitiesHMI.size() > 0, "No HMI entities found(size = %d)", fEntitiesHMI.size() );


	for (auto it = fEntitiesHMI.begin(); it != fEntitiesHMI.end(); it++)
	{
		std::shared_ptr<KFEntityHMIOperation> o = std::dynamic_pointer_cast<KFEntityHMIOperation>(it->second);
		std::shared_ptr<KFEntityHMICRing> c = std::dynamic_pointer_cast<KFEntityHMICRing>(it->second);

		ENGINE_ASSERT_EXCEPTION(o != nullptr || c != nullptr, "Illegal class type");

		vector<Device> devs;

		if (o != nullptr)
		{
			devs.push_back( Device( o->fIndicatorMain.fDeviceID, o) );
			devs.push_back( Device( o->fNavigatorMain.fDeviceID, o) );
			auto controls = o->fControls;

			for (size_t i = 0; i < controls.size(); i++)
			{
				devs.push_back( Device( o->fControls.at(i).fControl.fDeviceID, o ) );
				devs.push_back( Device( o->fControls.at(i).fIndicator.fDeviceID, o ) );
			}
		}

		if (c != nullptr)
		{
			devs.push_back( Device(c->fDeviceID, c ) );
			devs.push_back( Device(c->fIndicatorRotation.fDeviceID,c ) );
			devs.push_back( Device(c->fIndicatorTranslation.fDeviceID, c ) );
			devs.push_back( Device(c->fNavigatorRotation.fDeviceID, c )  );
			devs.push_back( Device(c->fNavigatorTranslation.fDeviceID, c ) );
		}

		for (size_t i = 0; i < devs.size(); i++)
		{
			auto device = GetDeviceByID( devs.at(i).fDeviceID );
			if (device == nullptr)
			{
				is_consisten = false;
				offending_ids.push_back( devs.at(i).fDeviceID );
				ENGINE_WARNING("Device with ID %s not found", devs.at(i).fDeviceID.c_str()  );
				ENGINE_DEBUG("Offending entry:\n%s", devs.at(i).fDevice->str().c_str() );
			}
		}
	}

	if (is_consisten == false)
	{
		if (policy == RELAXED)
		{
			ENGINE_ERROR("The followng IDs was not found\n\t%s", g_utilities()->Vec2String(offending_ids, ",").c_str());
			ENGINE_ERROR("Valid Device IDs are\n\t%s", g_utilities()->Vec2String(GetValidDeviceIDs(), ","  ).c_str() ) ;
			return false;
		}
		else if (policy == STRICT)
		{
			ENGINE_EXCEPTION("The followng IDs was not found \n\t%s", g_utilities()->Vec2String(offending_ids, ",").c_str());
			ENGINE_EXCEPTION("Valid Device IDs are\n\t%s", g_utilities()->Vec2String(GetValidDeviceIDs(), ",").c_str());
			return false;
		}
		else
		{
			ENGINE_EXCEPTION("unknown policy %d", policy );
			return false;
		}
	}
	return true;
}


vector<string>
KFConfigurationHandler::GetValidDeviceIDs()
{
	vector<string> tmp;
	for (auto it = fEntitiesDevices.begin(); it != fEntitiesDevices.end(); it++)
	{
		tmp.push_back( it->first );
	}
	return tmp;
}


/** @breif Finds a list of device entities by their IP address
 *  @param[in] The ip address to search forIP address */
vector< std::shared_ptr < KFEntityDevice > >
KFConfigurationHandler::KFConfigurationHandler::GetDevicesByIP( const string ip )
{
	vector<std::shared_ptr<KFEntityDevice> > tmp;

	for (auto it = fEntitiesDevices.begin(); it != fEntitiesDevices.end(); it++)
	{
		if (it->second->fAddress.fIPAddress == ip)
		{
			tmp.push_back(it->second);
		}
	}
	return tmp;
}



void
KFConfigurationHandler::AddEntity( std::shared_ptr<KFEntityDevice> entity )
{
	ENGINE_ASSERT_EXCEPTION(entity != nullptr, "entity is a ZERO POINTER !!!");

	auto it = fEntitiesDevices.find( entity->fAddress.fDeviceID );
	string hash = entity->fAddress.fDeviceID;

	if(it != fEntitiesDevices.end() )
	{
		ENGINE_ERROR("%s: device allready present in device list, ignoring request to add evice", hash.c_str() );
	}
	else
	{
		ENGINE_INFO("adding device with ID: %s", hash.c_str() );
		fEntitiesDevices.emplace(hash, entity );
	}
}


void
KFConfigurationHandler::AddEntity( std::shared_ptr<KFEntityHMI>  entity )
{
	ENGINE_ASSERT_EXCEPTION(entity != nullptr, "entity is a ZERO POINTER !!!");
	auto it = fEntitiesHMI.find( entity->fHMIID );
	string hash = entity->fHMIID;
	ENGINE_ASSERT_EXCEPTION( hash != "", "%s: hash tag cannot be empty", entity->fTitle.c_str() );

	if(it != fEntitiesHMI.end() )
	{
		//ENGINE_EXCEPTION("%s: device allready present in device list, ignoring request to add evice", hash.c_str() );
		ENGINE_ERROR("%s: device allready present in device list, ignoring request to add evice", hash.c_str() );
	}
	else
	{
		ENGINE_INFO("adding device with ID: %s", hash.c_str() );
		fEntitiesHMI.emplace(hash, entity );
	}
}


void
KFConfigurationHandler::AddEntities( vector< std::shared_ptr<KFEntity> > v)
{
	for(size_t i=0; i < v.size(); i++ )
	{
		if( std::dynamic_pointer_cast<KFEntityDevice >(v.at(i))  == nullptr &&  std::dynamic_pointer_cast<KFEntityHMI>(v.at(i)) == nullptr  )
		{
			ENGINE_EXCEPTION("Unreckognized class type " );
			return;
		}

		{
			std::shared_ptr<KFEntityDevice>  e  =   std::dynamic_pointer_cast<KFEntityDevice >(v.at(i )) ;
			if(e != nullptr)
			{
				AddEntity(e);
			}
		}

		{
			std::shared_ptr<KFEntityHMI>  e  =   std::dynamic_pointer_cast<KFEntityHMI >(v.at(i )) ;
			if(e != nullptr)
			{
				AddEntity(e);
			}
		}

	}
}


// string
// KFConfigurationHandler::GetXMLHmilFile() const
// {
// 	return fDefaultConfigHMI;
// }

// string
// KFConfigurationHandler::GetXMLDevices() const
// {
// 	return fDefaultConfigDevices;
// }



string 
KFConfigurationHandler::str() const
{
	std::stringstream buffer;

	buffer << "******* HMI IDs  ******* " << endl;
	for(auto it = fEntitiesHMI.begin(); it != fEntitiesHMI.end(); it ++ )
	{
		buffer << "\t" << it->first << endl;
	}
	buffer << "***** HMI IDs END ****** " << endl;
	buffer << endl;

	buffer << "******** Devices ********" << endl;
	for(auto it = fEntitiesDevices.begin(); it != fEntitiesDevices.end(); it ++ )
	{
		buffer << "\t" << it->first << endl;
	}

	buffer << "******* Devices END ******" 	 << endl;

	return buffer.str();

}