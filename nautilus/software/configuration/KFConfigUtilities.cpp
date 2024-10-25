

#include "KFConfigUtilities.h"
#include "KFEntityHMI.h"

#include <utilities/GSystem.h>
#include <configuration/KFXMLParserDevices.h>
#include <configuration/KFXMLParser.h>

#include <logging/LLogApi.h>
using namespace LOGMASTER;


KFConfigUtilities * KFConfigUtilities::Instance()
{
	static KFConfigUtilities* instance = new KFConfigUtilities();
	return instance;
}


string
KFConfigUtilities::GenerateFilePath() const
{
	string path = "";
	std::string exedir = g_system()->GetExeDir();
#ifdef _WIN32
	path = exedir + "..\\..\\config";
#else
	string ferrotech_home = "FERROTECH_HOME";
	char* tmp = getenv(ferrotech_home.c_str());
	G_ASSERT_EXCEPTION(tmp != nullptr, "could not find environmen variable %s", ferrotech_home.c_str());
	path = string(tmp) + "/config/";
#endif
	return path;

}


void
KFConfigUtilities::InitFileXML(const string base_name, XMLFile_t& xml  )
{
	string path =  GenerateFilePath();
	xml =   XMLFile_t(path + base_name);
}


void
KFConfigUtilities::InitFileXSD(const string base_name, XSDFile_t& xsd)
{
	string path =  GenerateFilePath();
	xsd =   XSDFile_t(path  + base_name );
}


vector< std::shared_ptr<KFEntity> >
KFConfigUtilities::ParseConfigXML(const XMLFile_t xml, const XSDFile_t xsd, std::shared_ptr<KFXMLParser> p)
{
	return p->ParseXML(xml, xsd);
}



bool
KFConfigUtilities::CheckConsistency( std::map<string, std::shared_ptr<KFEntityDevice> > * /*m_hmi*/, std::map<string, std::shared_ptr<KFEntityDevice> >  * /*md_dev*/ )
{
	return false;
}


std::shared_ptr<KFEntityHMI>
KFConfigUtilities::GetByHMIType( const eHMI_TYPE type, std::map<string, std::shared_ptr< KFEntityHMI > >  *m )
{
	vector< std::shared_ptr< KFEntityHMI> > tmp;

	for (auto it = m->begin(); it != m->end(); it++)
	{
		if (it->second->fType == type)
		{
			tmp.push_back(it->second );
		}
	}

	ENGINE_ASSERT_EXCEPTION(tmp.size() < 2, "Expected at most one entity of type %s (%d)",  HMIType2String(type).c_str(), (int)type );

	if (tmp.size() == 0)
	{
		ENGINE_WARNING("Could not find any elements of type %s (%d), returning a ZERO pointer", HMIType2String(type).c_str(), (int)type );
		return nullptr;
	}
	else
	{
		return tmp.at(0);
	}
}


string
KFConfigUtilities::HMIType2String( const eHMI_TYPE type )
{
	switch(type)
	{
		case eHMI_TYPE::CRING180:
			return  "CRING180";
		case eHMI_TYPE::CRING360:
			return  "CRING360";
		case eHMI_TYPE::COATING:
			return "COATING";
		case eHMI_TYPE::WRAPPING:
			return "WRAPPING";
		case eHMI_TYPE::SURFACE_PREP:
			return "SURFACE_PREP";
		case eHMI_TYPE::PATCHING:
			return "PATCHING";
		case eHMI_TYPE::HABITAT:
			return "HABITAT";
		case eHMI_TYPE::UNKNOWN:
			return "UNKNOWN";
		default:
			return "ERROR, type not reckognized";
	}
}


string
KFConfigUtilities::Direction2String( const eDIRECTION d )
{
	switch(d)
	{
		case eDIRECTION::NEGATIVE:
			return "NEGATIVE";
    	case eDIRECTION::READ_FROM_FRAM:
			return "READ_FROM_FRAM";
		case eDIRECTION::POSITIVE:
			return  "POSITIVE";
    	case eDIRECTION::CW:
			return "CW";
    	case eDIRECTION::CCW:
			return "CCW";
    	case eDIRECTION::INVALID:
			return "INVALID";
    	case eDIRECTION::UNKNOWN:
			return  "UNKNOWN";
		default:
			return "ERROR, type not reckognized";
	}
}