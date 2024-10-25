// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "MBPostOfficeConfig.h"
#include <utilities/GException.h>
#include <utilities/GEnum.h>
#include <xml/GXmlStreamReaderSp.h>
#include <utilities/GFileIOHandler.h>
#include <string>
#include <cstdlib>

#include <utilities/GDefinitions.h>


G_ENUM(eXMLTAGS, { POSTOFFICE, CHANNELS, CHANNEL, ERROR });

//#include <utilities/GString.h>
#include <utilities/GSystem.h>

#undef ERROR

#include <string>

MBPostOfficeConfig::MBPostOfficeConfig()
{
#ifdef _WIN32
	std::string xmlFilePath = string(g_system()->GetExeDir()) + "\\..\\..\\config\\post_office.xml";
#else
	string xmlFilePath = string(getenv("FERROTECH_HOME")) + "/config/post_office.xml";
#endif

//	FORCE_DEBUG("Path = %s", xmlFilePath.c_str() );
	G_ASSERT_EXCEPTION( g_file()->DoExists( xmlFilePath ),  "The file \"%s\" does not exists", xmlFilePath.c_str());
//	G_ASSERT_EXCEPTION(kg_path()->Exists(xmlFilePath), "The file \"%s\" does not exists", xmlFilePath.c_str());



	GXmlStreamReaderSp reader(xmlFilePath);
	GXmlNodeSp node;

	std::string tempString;
	do
	{
		node = reader.ReadNode();
		if (!node.IsValid())
		{
			break;
		}
		eXMLTAGS tag = eXMLTAGS::ERROR;
		eXML_NODETYPE tagType = node.GetType();
		if (tagType != eXML_NODETYPE::ETextNode)
		{
			std::string tagName = node.GetName();
			tag = EnumLookup(tagName, eXMLTAGS::ERROR);
			G_ASSERT_EXCEPTION(tag != eXMLTAGS::ERROR, "Tag %s is not expected", tagName.c_str());
		}
		switch (tagType)
		{
			case eXML_NODETYPE::EOpenTagNode:
				break;
			case eXML_NODETYPE::ECloseTagNode:
				switch (tag)
				{
					case eXMLTAGS::CHANNEL:
						fChannels.push_back(tempString);
						break;
				}
				break;
			case eXML_NODETYPE::ESingleTagNode:
				break;
			case eXML_NODETYPE::ETextNode:
				tempString = node.GetValue();
				break;
			case eXML_NODETYPE::ECommentNode:
				break;
			case eXML_NODETYPE::EProcInstrNode:
				break;
			case eXML_NODETYPE::EDocTypeNode:
				break;
			case eXML_NODETYPE::ECDataNode:
				break;
			default:
				break;
		}
	} while (true);
}


MBPostOfficeConfig::~MBPostOfficeConfig()
{

}


MBPostOfficeConfig*
MBPostOfficeConfig::Instance()
{
	static MBPostOfficeConfig* instance = new MBPostOfficeConfig();

	return instance;
}

std::vector<std::string> MBPostOfficeConfig::GetChannels()
{
	return fChannels;
}
