// -*- mode: c++ -*-


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include "KFXMLParser.h"
#include <logging/LLogApi.h>
#include <exception>

using namespace LOGMASTER;
#include <cmath>
#include <ctgmath>


KFXMLParser::KFXMLParser()
{

}


KFXMLParser::~KFXMLParser()
{

}

// bool
// KFXMLParser::AssertOptionalTagGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string tag, GLocation l, eXML_NODETYPE node_type )
// {
// 	try
// 	{
// 		AssertTag(xmlReader, tag, l, node_type );
// 	}
// 	catch(const GEngineException& exception)
// 	{
// 		exception.DisableException();
// 		// xmlReader.get()->RewindNode();
// 		return false;
// 	}
// 	return true;
// }

void
KFXMLParser::AssertTagOpenGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string tag, GLocation l, const bool read_node )
{
	AssertTag(xmlReader, tag, l, eXML_NODETYPE::EOpenTagNode, read_node );
}


void
KFXMLParser::AssertTagCloseGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string tag, GLocation l, const bool read_node  )
{
	AssertTag(xmlReader, tag, l, eXML_NODETYPE::ECloseTagNode, read_node );
}


void
KFXMLParser::AssertTag(std::shared_ptr<GXmlStreamReader> xmlReader, const string tag, GLocation l, eXML_NODETYPE node_type,  const bool read_node  )
{
	LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l,   "tag = %s, node type = %s", tag.c_str(),   *node_type  );
	
	GXmlNode *node  = xmlReader->GetCurrentNode();

	if(read_node == true)
	{
		node = xmlReader->ReadNode();
	}

	ENGINE_ASSERT_EXCEPTION(node != nullptr, "node is a ZERO pointer");
	eXML_NODETYPE node_type_l = node->GetType();
	string tag_l =  node->GetName();

	if( tag_l != tag )
	{
		throw( GEngineException( l.fFileName,l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_XML, "Unexpected node type(%s), expected %s, got %s",  Enum2String(node_type).c_str(),  tag.c_str(),  tag_l.c_str() ) );
	}
	else if( node_type != node_type_l )
	{
		throw( GEngineException( l.fFileName,l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_XML, "Unexpected tag, expected %s, got %s", *node_type, *node_type_l ) );
	}

}


void
KFXMLParser::PrinttAttributes( const GXmlNode * const node,  GLocation l)
{
	vector<GXmlAttribute> a =  node->GetAttributes();
	string name = node->GetName();
	auto type = node->GetType();
	LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l,  "tag = %s, type = %s, attributes.size() = %d", name.c_str(), *type, a.size() );

	for(size_t i =0; i < a.size(); i++ )
	{
		LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l, "Attribute[%d]: name = %s, value = %s", i, a.at(i).GetName().c_str(), a.at(i).GetValue().c_str()  );
	}
}


bool
KFXMLParser::HasAttributes(  const GXmlNode * const node ) const
{
	return node->GetAttributes().size() > 0 ? true : false;
}

