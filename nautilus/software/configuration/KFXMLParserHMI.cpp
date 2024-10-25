
#include "KFXMLParserHMI.h"
#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <xml/GXmlClassFactory.h>
#include <xml/GXmlStreamWriter.h>
#include <xml/GXmlStreamReader.h>
#include <xml/GXmlValidator.h>
#include <utilities/GException.h>

#include "KFConfigurationHandler.h"
#include "KFHMICaption.h"
#include "KFHMIControl.h"
#include "KFHMIControlGroup.h"
#include "KFHMIStepNavigator.h"
#include "KFEntityHMICRing.h"
#include "KFEntityHMIOperation.h"

#include  <memory>
#include  <exception>
#include  <utilities/GTokenizer.h>
#include  <utilities/GNumbers.h>


KFXMLParserHMI::KFXMLParserHMI()
{
	InitHashMaps();
}


vector< std::shared_ptr<KFEntity> >
KFXMLParserHMI::ParseXML(const XMLFile_t xml, const XSDFile_t xsd)
{
	ENGINE_ASSERT_EXCEPTION(GXmlValidator::IsValid(xml.str(), xsd.str()), "Faild to validate XML file %s against %s", 
	xml.str().c_str(), xsd.str().c_str());
	std::shared_ptr<GXmlStreamReader> xmlReader = GXmlClassFactory::CreateStreamReaderSmartPtr(xml.str());
	GXmlNode* node = xmlReader->ReadNode();
	vector< std::shared_ptr<KFEntity> > tmp;

	while (node != nullptr)
	{
		string tag = node->GetName();

		if (tag == "FERROTECH_HMI" && node->GetType() == eXML_NODETYPE::EOpenTagNode)
		{
			ENGINE_INFO("node name is FERROTECH_HMI");
		}
		else
		{
			if (tag == "C_RING-180")
			{
				tmp.push_back ( ParseXMLCRing(xmlReader, tag) );
			}
			else if( tag == "C_RING-360" )
			{
				tmp.push_back ( ParseXMLCRing(xmlReader, tag) );
			}
			else if( tag == "OPERATION" )
			{
				tmp.push_back ( ParseXMLOperations( xmlReader, tag ) );
			}
		}
		node = xmlReader->ReadNode();
	}

//	FORCE_DEBUG("tmp.size() = %d", tmp.size() );

	return tmp;
}


std::shared_ptr<KFEntityHMICRing>
KFXMLParserHMI::ParseXMLCRing(std::shared_ptr<GXmlStreamReader>  xmlReader, const string  closing_tag )
{
	std::shared_ptr<KFEntityHMICRing>  c = std::make_shared<KFEntityHMICRing>();
	c->fType = String2Enum(GetTagValue<string>(xmlReader, "HMI_TYPE", GLOCATION), &fHMITypes);
	c->fTitle = GetTagValue<string>( xmlReader,  "TITLE",     GLOCATION  );
	c->fHMIID = GetTagValue<string>( xmlReader,  "HMI_ID",    GLOCATION  );
	c->fDeviceID =GetTagValue<string>(xmlReader, "DEVICE_ID", GLOCATION  );

	xmlReader->ReadNode();
	ParseXMLStepNavigator(  xmlReader,  &c->fNavigatorTranslation, "TRANSLATION_NAVIGATOR" );
	xmlReader->ReadNode();
	ParseXMLIndicator(      xmlReader,  &c->fIndicatorTranslation, "TRANSLATION_INDICATOR");
	xmlReader->ReadNode();
	ParseXMLStepNavigator(  xmlReader,  &c->fNavigatorRotation , "ROTATION_NAVIGATOR" );
	xmlReader->ReadNode();
	ParseXMLIndicator(      xmlReader,  &c->fIndicatorRotation, "ROTATION_INDICATOR");
	AssertTagCloseGroup(    xmlReader, closing_tag, GLOCATION );
	return c;
}


void
KFXMLParserHMI::ParseXMLCaption(  std::shared_ptr<GXmlStreamReader> xmlReader, KFHMICaption *  caption )
{
	AssertTagOpenGroup(xmlReader, "CAPTION", GLOCATION);
	{
		caption->fCaption = GetTagValue<string>(xmlReader, "CAPTION", GLOCATION);
		caption->fCaptionMin = GetTagValue<string>(xmlReader, "CAPTION_MIN", GLOCATION);
		caption->fCaptionMax = GetTagValue<string>(xmlReader, "CAPTION_MAX", GLOCATION);
	}
	AssertTagCloseGroup(xmlReader, "CAPTION", GLOCATION);
}


void
KFXMLParserHMI::ParseXMLStepNavigator(  std::shared_ptr<GXmlStreamReader> xmlReader, KFHMIStepNavigator  * navigator, const string closing_tag  )
{
	GXmlNode *node = xmlReader->GetCurrentNode();
	vector<GXmlAttribute> attributes = node->GetAttributes();
	navigator->fOrientation =  ParseAtrributeOrientation( node, GLOCATION );

	ENGINE_ASSERT_EXCEPTION(navigator != nullptr, "navigator is ZERO pointer");
	ENGINE_ASSERT_EXCEPTION( xmlReader != nullptr, "xmlreader is a ZERO pointer");

	ParseXMLCaption(xmlReader, &navigator->fCaption);
	navigator->fSteps =  ParseXMLSteps(xmlReader);
	navigator->fDeviceID = GetTagValue<string>(xmlReader, "DEVICE_ID", GLOCATION);
	AssertTagCloseGroup(xmlReader, closing_tag, GLOCATION );
}


void
KFXMLParserHMI::ParseXMLIndicator(  std::shared_ptr<GXmlStreamReader>  xmlReader ,KFHMIIndicator * indicator, const string closing_tag  )
{
	ENGINE_ASSERT_EXCEPTION( indicator != nullptr, "indicator is ZERO pointer");
	ENGINE_ASSERT_EXCEPTION( xmlReader != nullptr, "xmlreader is a ZERO pointer");
	GXmlNode *node = xmlReader->GetCurrentNode();

	indicator->fCanDecrement  =  ParseAtrributeIsDecrement( node, GLOCATION );
	indicator->fOrientation   =  ParseAtrributeOrientation( node, GLOCATION );

	if( HasAttributes( node) )
	{
		PrinttAttributes( node, GLOCATION );
	}

	ParseXMLCaption(xmlReader, &indicator->fCaption);
	//G_FATAL( "lineno = %d", xmlReader->GetLineNumber() );
	indicator->fMinValue = GetTagValue<int>(xmlReader,    "MIN_VALUE", GLOCATION );
	indicator->fMaxValue = GetTagValue<int>(xmlReader,    "MAX_VALUE", GLOCATION );
	indicator->fDeviceID = GetTagValue<string>(xmlReader, "DEVICE_ID", GLOCATION );
	AssertTagCloseGroup(xmlReader, closing_tag, GLOCATION );
}


vector<int>
KFXMLParserHMI::ParseXMLSteps (  std::shared_ptr<GXmlStreamReader> xmlReader  )
{
	string tmp = GetTagValue<string>(xmlReader, "STEPS", GLOCATION);
	vector<string> tokens = g_tokenizer()->Tokenize(tmp, "," );
	vector<int> ret;

	for(size_t i=0; i < tokens.size(); i++ )
	{
		int num = g_numbers()->ToInteger<int>(tokens.at(i));
		ENGINE_DEBUG("tokens[%d] = %s,  num = %d", i, tokens.at(i).c_str(), i );
		ret.push_back(num);
	}

	ENGINE_DEBUG("The numer of steps read is %d", ret.size() );
	return ret;
 }


std::shared_ptr<KFEntityHMIOperation>
KFXMLParserHMI::ParseXMLOperations(std::shared_ptr<GXmlStreamReader>  xmlReader, const string  closing_tag )
{
	auto operation = std::make_shared< KFEntityHMIOperation>();
	operation->fType  = String2Enum ( GetTagValue<string>(xmlReader, "HMI_TYPE"), &fHMITypes );
	operation->fTitle = GetTagValue<string>( xmlReader, "TITLE", GLOCATION );
	operation->fHMIID = GetTagValue<string>( xmlReader, "HMI_ID", GLOCATION );
	xmlReader->ReadNode();
	ParseXMLStepNavigator(xmlReader,  &operation->fNavigatorMain, "MAIN_NAVIGATOR");
	xmlReader->ReadNode();
	ParseXMLIndicator( xmlReader, &operation->fIndicatorMain, "MAIN_INDICATOR" );
	string tag = xmlReader->ReadNode()->GetName();

	while(tag != closing_tag )
	{
		ENGINE_INFO("tag = %s", tag.c_str() );
		if(tag == "CONTROL_GROUP")
		{
			auto ctrl = ParseXMLControlGroup(xmlReader,  tag );
		 	tag = xmlReader->ReadNode()->GetName();
			operation->fControls.push_back(ctrl);
		}
	}

	if(tag ==  closing_tag )
	{
		ENGINE_DEBUG("closing tag %s reached", tag.c_str() );
		return operation;
	}

	AssertTagCloseGroup(xmlReader, closing_tag, GLOCATION );
	return operation;
}


KFHMIControlGroup
KFXMLParserHMI::ParseXMLControlGroup (  std::shared_ptr<GXmlStreamReader> xmlReader, const string closing_tag )
{
	KFHMIControlGroup g;
	ParseXMLControl(xmlReader,  &g.fControl );
	xmlReader->ReadNode();
	ParseXMLIndicator(xmlReader, &g.fIndicator, "INDICATOR" );
	AssertTagCloseGroup(xmlReader, closing_tag, GLOCATION );
	return g;
}


void
KFXMLParserHMI::ParseXMLControl(  std::shared_ptr<GXmlStreamReader>  xmlReader, KFHMIControl  * control )
{
	GXmlNode *node = xmlReader->GetCurrentNode();
	node = xmlReader->ReadNode();
	control->fOrientation = ParseAtrributeOrientation(node, GLOCATION);
	ParseXMLCaption( xmlReader, &control->fCaption );
	control->fSteps     =  ParseXMLSteps( xmlReader );
	control->fMinValue  =  GetTagValue<int>(xmlReader, "MIN_VALUE", GLOCATION );
	control->fMaxValue  =  GetTagValue<int>(xmlReader, "MAX_VALUE", GLOCATION );
	control->fDeviceID =  GetTagValue<string>( xmlReader, "DEVICE_ID", GLOCATION);
	AssertTagCloseGroup( xmlReader, "CONTROL", GLOCATION );
}


bool
KFXMLParserHMI::ParseAtrributeIsDecrement( const GXmlNode * const node, GLocation l )
{
	bool is_decrement = false;
	bool is_found = false;
	vector<GXmlAttribute> attributes = node->GetAttributes();

	for( size_t i=0; i < attributes.size(); i ++  )
	{
		const string name =   attributes.at(i).GetName();

		if( name  == "decrement"  )
		{
			is_found = true;
			const string value = attributes.at(i).GetValue();

			if( attributes.at(i).GetValue() == "true" )
			{
				is_decrement = true;
			}
			else if( attributes.at(i).GetValue() == "false" )
			{
				is_decrement = false;
			}
			else
			{
				throw( GEngineException( l.fFileName,l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_ENGINE,  "%s: Illegal argument %s",  name.c_str(),  value.c_str() ));

			}
		}
	}

	if(is_found == false )
	{
		throw( GEngineException( l.fFileName,l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_ENGINE, "could not find attribute \"decrement\""  ));
	}
	return   is_decrement;
}


eORIENTATION
KFXMLParserHMI::ParseAtrributeOrientation( const GXmlNode * const node, GLocation l )
{
	bool is_found = false;
	vector<GXmlAttribute> attributes = node->GetAttributes();
	eORIENTATION ret = eORIENTATION::UNKNOWN;

	const string tagname = node->GetName();

	for( size_t i=0; i < attributes.size(); i ++  )
	{
		const string name =   attributes.at(i).GetName();

		if(  name == "orientation")
		{
			is_found = true;
			const string value = attributes.at(i).GetValue();

			if(value ==  "horizontal")
			{
				ret = eORIENTATION::HORIZONTAL;
			}
			else if( value == "vertical")
			{
				ret = eORIENTATION::VERTICAL;
			}
			else
			{
				ret = eORIENTATION::UNKNOWN;
				throw( GEngineException( l.fFileName,l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_ENGINE,  "%s: unreckognized value %s", name.c_str(), value.c_str()   )  );
			}

		}
	}

	if(is_found == false)
	{
		throw( GEngineException( l.fFileName,l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_ENGINE,    "tag: %s, expcted to find attribute \"orientation\", but it was not found", tagname.c_str() )  );
	}

	return ret;
}


void
KFXMLParserHMI::InitHashMaps()
{
	fHMITypes.emplace("CRing180", eHMI_TYPE::CRING180);
	fHMITypes.emplace("CRing360", eHMI_TYPE::CRING360);
	fHMITypes.emplace("SurfacePrep", eHMI_TYPE::SURFACE_PREP );
	fHMITypes.emplace("Coating", eHMI_TYPE::COATING);
	fHMITypes.emplace("Wrapping", eHMI_TYPE::WRAPPING);
	fHMITypes.emplace("Patching", eHMI_TYPE::PATCHING);
}

