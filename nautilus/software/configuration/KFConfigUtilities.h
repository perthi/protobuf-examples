#pragma once

#include <xml/GXmlDataTypes.h>
#include <utilities/GDefinitions.h>

#include <string>
using std::string;

#include <memory>
#include <map>

#include <vector>
using std::vector;


#include <protocol/KFProtocolEnums.h>
#include <protocol/KFProtocolEnums.h>

class KFXMLParser;
class TestKFConfigUtilities_filenames_Test;

struct KFEntity;
struct KFEntityHMI;
struct KFEntityDevice;

class KFConfigUtilities
{
	friend TestKFConfigUtilities_filenames_Test;

public:
	static  KFConfigUtilities  API * Instance();
	
	void    API InitFileXML(const string base_name, XMLFile_t& xml );
	void    API InitFileXSD(const string base_name, XSDFile_t& xsd );
	vector< std::shared_ptr<KFEntity> > API  ParseConfigXML(const XMLFile_t xml, const XSDFile_t xsd, std::shared_ptr<KFXMLParser> p );
	bool    API CheckConsistency( std::map<string, std::shared_ptr<KFEntityDevice> > *m_hmi, std::map<string, std::shared_ptr<KFEntityDevice> > *md_dev );  
	std::shared_ptr<KFEntityHMI> API GetByHMIType( const eHMI_TYPE type, std::map<string, std::shared_ptr< KFEntityHMI > >  *m );
	string HMIType2String( const eHMI_TYPE type );
	string Direction2String( const eDIRECTION  );

private:
	string GenerateFilePath() const;
};

