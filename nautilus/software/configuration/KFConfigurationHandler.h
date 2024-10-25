// -*- mode: c++ -*-
#ifndef KFCONFIGURATIONHANDLER_H
#define KFCONFIGURATIONHANDLER_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/

#include <utilities/GDefinitions.h>
#include "KFEntityDevice.h"
#include "KFEntityHMI.h"
#include <memory>

#include <vector>
using std::vector;
#include <utilities/GDefinitions.h>

#include <utilities/GException.h>
#include <logging/LLogApi.h>
#include <type_traits>
#include <typeinfo>
#include <xml/GXmlDataTypes.h>

#include <common/GComponent.h>


//#include  <kf-common/KFConfigXML.h>

#define STRICT 1
#define RELAXED 2


#include <utilities/GPrintable.h>


/** forward declarations ofr unit tester*/
class  TestKFXMLParserDevices;
class  TestKFXMLParserDevices_no_entities_Test;
class  TestKFXMLParserHMI_no_entities_Test;
class  TestKFConfigurationHandler_sizes_Test;
class  TestKFConfigurationHandler_get_by_ip_Test;
class  TestKFXMLParserHMI;

struct MBMessageInfo;
struct KFConfigXML;

///struct  KFXMLFiles;

/** @breif Configuation handler for all devices and HMI(gui widgets) entities read from XML configuration files
 *  @details this class reads the system configuation xml files and stores them two maps. One for HMI entities
 *  and one for Device entitites,  fEntitiesHMI, fEntitiesDevices respectively
 *  HMI entities contains a description of each HMI element (which can for instance be represented as a QT widget), The
 *  various HMI controls and interfaces maps to actual devives which must be present in the Device list (map). The device
 *  list containes entitites such as Motors, Sensors, Solenoids etc */
class  KFConfigurationHandler : public GComponent, public GPrintable
{
	friend  TestKFXMLParserDevices;
	friend  TestKFXMLParserDevices_no_entities_Test;
	friend  TestKFXMLParserHMI_no_entities_Test;
	friend  TestKFConfigurationHandler_sizes_Test;
	friend  TestKFConfigurationHandler_get_by_ip_Test;

	friend  TestKFXMLParserHMI;

	public:
		static  KFConfigurationHandler API * Instance();
		virtual void   API     ProcessMessageLocal( std::shared_ptr<MBMessageInfo>  msg)  override;
 		virtual void   API     ProcessMessageBlocking( std::shared_ptr<MBMessageInfo>  msg) override;

 		virtual   string str() const override;

		void  API AddEntities( vector< std::shared_ptr<KFEntity> > v);
		std::map<string, std::shared_ptr< KFEntityDevice > >   API   GetEntitiesDevices();
		std::map<string, std::shared_ptr< KFEntityHMI >    >   API   GetEntitiesHMI();

		bool API CheckConsistency(const int policy = STRICT );

		vector<string>  API  GetValidDeviceIDs();

		vector< std::shared_ptr< KFEntityDevice > >  API GetDevicesByIP( const string ip );
		inline std::shared_ptr<KFEntityDevice >  API  GetDeviceByID( const string id  );
		inline std::shared_ptr<KFEntityHMI >     API  GetHMIByID(    const string id  );

		template<typename T>
		vector< std::shared_ptr<T> >  GetByClassType();
		std::shared_ptr<KFEntityHMI> API GetByHMIType( eHMI_TYPE type );
		
		void  API ParseConfig(  std::shared_ptr<MBMessageInfo>  message_info, KFConfigXML &config );
		void  API ParseConfigDevices( const XMLFile_t xml, const XSDFile_t xsd  );
		void  API ParseConfigHmi( const XMLFile_t xml, const XSDFile_t xsd );
		void  API ParseConfigDevices( const XMLFile_t xml   );
		void  API ParseConfigHmi( const XMLFile_t xml );


		void API InitFiles(  const XMLFile_t xml_fname_in,  XMLFile_t &xml_out,  const XSDFile_t xsd_fname_in,  XSDFile_t &xsd_out );

	private:
		API  KFConfigurationHandler();
		virtual API ~KFConfigurationHandler();

		void API Purge();
		void   AddEntity( std::shared_ptr<KFEntityDevice> entity );
		void   AddEntity( std::shared_ptr<KFEntityHMI> entity );

		template<typename T  >
		std::shared_ptr<T>  GetByID( std::map<string,  std::shared_ptr<T> > *m, const string id );

		template<typename T1, typename T2>
		void GetByType( std::map<string,  std::shared_ptr<T1> > *m, vector< std::shared_ptr<T2> > *v  );

		std::map<string, std::shared_ptr< KFEntityDevice > >  fEntitiesDevices;
		std::map<string, std::shared_ptr< KFEntityHMI > >  fEntitiesHMI;

};



std::shared_ptr< KFEntityDevice>
KFConfigurationHandler::GetDeviceByID( const string  id )
{
	return GetByID( &fEntitiesDevices, id);
}



std::shared_ptr< KFEntityHMI>
KFConfigurationHandler::GetHMIByID( const string  id )
{
	return GetByID( &fEntitiesHMI, id);
}


template<typename T>
std::shared_ptr<T>
KFConfigurationHandler::GetByID( std::map<string,  std::shared_ptr<T> > *m, const string id  )
{
	auto it = m->find(id);

	if( it ==  m->end()  )
	{
		ENGINE_WARNING("could not find device with id = %s", id.c_str() );
		return nullptr;
	}
	else
	{
		return it->second;
	}
}


template<typename T>
vector< std::shared_ptr<T> >
KFConfigurationHandler::GetByClassType()
{
	vector < std::shared_ptr<T>  > tmp;

	if( std::is_base_of<KFEntityDevice, T >::value == true)
	{
		GetByType<KFEntityDevice>(  &fEntitiesDevices, &tmp );
	}
	else if( std::is_base_of<KFEntityHMI, T >::value == true  )
	{
		GetByType<KFEntityHMI>( &fEntitiesHMI, &tmp );
	}
	else
	{
		ENGINE_EXCEPTION("Illegal class type %s",  typeid(T).name()  );
	}

	return tmp;
}



template<typename T1, typename T2>
void
KFConfigurationHandler::GetByType( std::map<string,  std::shared_ptr<T1> > *m, vector < std::shared_ptr<T2> > *v )
{
	for(auto it = m->begin(); it !=  m->end(); it ++ )
	{	
		auto ptr = std::dynamic_pointer_cast<T2>(it->second );
		if( ptr != nullptr )
		{
			v->push_back(ptr);
		}
	}
}




#endif
