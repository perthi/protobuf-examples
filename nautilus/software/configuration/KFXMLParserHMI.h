
#pragma once


#include "KFXMLParser.h"

class  GXmlStreamReader;
class  GXmlNode;

struct  KFEntityHMI;
struct  KFEntityHMICRing;
struct  KFEntityHMIOperation;
struct  KFEntityHMIHabitat;
struct  KFHMICaption;
struct  KFHMIControlGroup;
struct  KFHMIControl;
struct  KFHMIIndicator;
struct  KFHMIStepNavigator;


#include <protocol/KFProtocolEnums.h>

#include <xml/GXmlAttribute.h>

#include <utilities/GDefinitions.h>
#include <utilities/GLocation.h>

#include <memory>
#include <vector>
using std::vector;

class KFXMLParserHMI : public KFXMLParser
{
public:
	API KFXMLParserHMI();
	virtual vector< std::shared_ptr<KFEntity > >  ParseXML(const XMLFile_t  xml, const XSDFile_t xsd) override;
	API std::shared_ptr<KFEntityHMICRing>   ParseXMLCRing(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);
	API std::shared_ptr<KFEntityHMIOperation>   ParseXMLOperations(std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag);
	void InitHashMaps();

private:
	void               API   ParseXMLCaption      (  std::shared_ptr<GXmlStreamReader> xmlReader, KFHMICaption * caption );
	void               API   ParseXMLControl      (  std::shared_ptr<GXmlStreamReader> xmlReader, KFHMIControl  * control );
	void               API   ParseXMLIndicator    (  std::shared_ptr<GXmlStreamReader> xmlReader, KFHMIIndicator * indicator,   const string closing_tag  );
	void               API   ParseXMLStepNavigator(  std::shared_ptr<GXmlStreamReader> xmlReader, KFHMIStepNavigator  * navigator, const string closing_tag );
	KFHMIControlGroup  API   ParseXMLControlGroup (  std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag );
	vector<int>        API   ParseXMLSteps        (  std::shared_ptr<GXmlStreamReader> xmlReader );
	bool 		       API   ParseAtrributeIsDecrement( const GXmlNode * const node, GLocation l );
	eORIENTATION       API   ParseAtrributeOrientation( const GXmlNode * const node, GLocation l );

	std::map<string, eHMI_TYPE>  fHMITypes;
};
