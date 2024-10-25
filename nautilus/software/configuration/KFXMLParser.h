// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#pragma once


//#define LIBXML_TREE_ENABLED   1
//#define LIBXML_DEBUG_ENABLED  1


#include  <utilities/GDefinitions.h>
#include  <utilities/GException.h>
#include  <utilities/GNumbers.h>
#include <utilities/GLocation.h>

#include  <xml/GXmlDataTypes.h>
#include  <xml/GXmlNode.h>
#include  <xml/GXmlStreamReader.h>
#include  <xml/GXmlAttribute.h>


///#include <xml/3rd-party/tree.h>

#include  <logging/LLogApi.h>
using namespace LOGMASTER;

#include <string>
using std::string;
#include <memory>

struct KFEntity;

class KFXMLParser
{
public:
    API KFXMLParser();
    API virtual ~KFXMLParser();
	virtual  vector< std::shared_ptr<KFEntity> > API ParseXML(const XMLFile_t  /*xml*/, const XSDFile_t /*xsd*/ )  = 0;

	template<typename T>
	inline T String2Enum(const string hash, std::map<string, T>*);

	inline string  Enum2String( eXML_NODETYPE );

protected:
	template<typename T = string>
    inline T  GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader,  const string tagname, const bool read_node  = true);

	template<typename T>
	inline T  GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader,  const string tagname, GLocation l ,const bool read_node  = true );

	template<typename T >
	inline T     GetTagValueOrNothing( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, GLocation l, bool *has_value ,const bool read_node = true );

	void   AssertTagOpenGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l, const bool read_node = true );
	void   AssertTagCloseGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l,  const bool read_node = true  );
	// bool   AssertOptionalTagGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l, eXML_NODETYPE node_type );
	void   AssertTag(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l, eXML_NODETYPE node_type, const bool read_node = true  );
	void   PrinttAttributes( const GXmlNode * const node , GLocation l );
	bool   HasAttributes(  const GXmlNode * const node ) const;



};


inline string
KFXMLParser::Enum2String(  const eXML_NODETYPE type )
{
	switch (type )
	{
	  case eXML_NODETYPE::EOpenTagNode:
				return "EOpenTagNode";
			  break; 
      case eXML_NODETYPE::ECloseTagNode:
			return "ECloseTagNode";
			  break; 
      case eXML_NODETYPE::ESingleTagNode:
			return "ESingleTagNode";
			  break; 
      case eXML_NODETYPE::ETextNode:
			return "ETextNode";
			  break; 
      case eXML_NODETYPE::ECommentNode:
			return "ECommentNode";
			  break; 
      case eXML_NODETYPE::EProcInstrNode:
			return "EProcInstrNode";
			  break; 
      case eXML_NODETYPE::EDocTypeNode:
			return "EDocTypeNode";
			  break; 
      case eXML_NODETYPE::ECDataNode:
			return "ECDataNode";
			break;
	default:
		std::stringstream buffer;
		buffer << 	"Type not" << (int)type << "reckognized";
		return  buffer.str();	
		break;
	}

}


template<typename T>
inline T
KFXMLParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname,const bool read_node  )
{
//	GXmlNode	*node_test = xmlReader->GetCurrentNode();
///	vector<GXmlAttribute> attributes = node_test->GetAttributes();
	GXmlNode	*node = nullptr;
	if( read_node == true)
	{
		node	= xmlReader->ReadNode();
	}
	else
	{
		node	= xmlReader->GetCurrentNode();	
	}

///	attributes = node->GetAttributes();
	XML_ASSERT_EXCEPTION( node != nullptr,  "  xmlReader->ReadNode() returned a ZERO POINTER !!!" );

	if( node->GetType()  == eXML_NODETYPE::ESingleTagNode)
	{
		XML_WARNING("%s is a single tag node (with no value) !!", tagname.c_str() );
		vector<GXmlAttribute> tmp =  node->GetAttributes();

		for (size_t i = 0; i < tmp.size(); i++)
		{
			FORCE_DEBUG("Attribute name= %s, value = %s",tmp.at(i).GetName(), tmp.at(i).GetValue() );
		}
		 return "";
	}

	XML_ASSERT_EXCEPTION( node->GetType() == eXML_NODETYPE::EOpenTagNode, "Unexpcted node type %d (name = %s, type = %s, value = %s)", node->GetType(), node->GetName().c_str(), *node->GetType(),  node->GetValue().c_str() );
	string name = node->GetName();
	XML_ASSERT_EXCEPTION(node->GetName() == tagname, "expected %s, got %s (type = %s)", tagname.c_str(), node->GetName().c_str(),  *node->GetType()  );
	node =  xmlReader->ReadNode();

	if (node->GetType() == eXML_NODETYPE::ECloseTagNode)
	{
		return "";
	}

	string value = node->GetValue();
	node = xmlReader->ReadNode();
	return value;
}


template < >
inline int
KFXMLParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, const bool read_node   )
{
    string tmp =  GetTagValue( xmlReader, tagname, read_node);
    return g_numbers()->ToInteger(tmp);
}


template < >
inline float
KFXMLParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, const bool read_node  )
{
    string tmp =  GetTagValue( xmlReader, tagname, read_node);
	return g_numbers()->ToFloat<float>(tmp);
}


template < >
inline bool
KFXMLParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, const bool read_node  )
{
    string tmp =  GetTagValue( xmlReader, tagname, read_node);

    if(tmp == "true")
	{
		return true;
	}
	else if(tmp == "false")
	{
		return false;
	}
	else
	{
		ENGINE_EXCEPTION("unexpected value for boolena %s, expected either \"true\" or \"false\"");
	}

	return false;
}


template<typename T>
inline T
KFXMLParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader,  const string tagname, GLocation l, const bool read_node )
{
	LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l,  "tag = %s", tagname.c_str() );
	return 	GetTagValue<T>( xmlReader,  tagname , read_node );
}




template<typename T>
inline T
KFXMLParser::String2Enum(const string hash, std::map<string, T>* m)
{
	auto it = m->find(hash);
	XML_ASSERT_EXCEPTION(it != m->end(), "could not find enum for hash tag %s, \n legal values are: %s", hash.c_str(), g_utilities()->Hash2String(m).c_str());
	return (T)it->second;
}


template<typename T>
inline T
KFXMLParser::GetTagValueOrNothing( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, GLocation l, bool *has_value,  const bool read_node )
{
	string tmp = GetTagValue<string>( xmlReader, tagname, l, read_node  );
	if(tmp == "")
	{
		XML_INFO("value for %s is empty", tagname.c_str()  );
		LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l,  "value for tag %s is empty", tagname.c_str()  );
		*has_value = false;
		// return NAN;
		return (T)-1;
	}
	else
	{
		T ret = g_numbers()->ToNumber<T>(tmp);
		LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l,  "value for tag %s is %d", tagname.c_str(), ret );
		*has_value = true;
		return ret;
		//return -1;
	}
}

