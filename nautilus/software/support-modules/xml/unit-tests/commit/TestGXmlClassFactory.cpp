// -*- mode: c++ -*-


/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#include "TestGXmlClassFactory.h"
#include <xml/GXmlClassFactory.h>
#include <xml/GXmlStreamWriter.h>
#include <xml/GXmlStreamReader.h>

#include <memory>
#include <algorithm>

#include <utilities/GSystem.h>
#include <utilities/GException.h>
#include <logging/LLogging.h>
#include <utilities/GException.h>




void 
TestGXmlClassFactory::SetUp()
{/*
	try {
	
	}
	catch()*/


}

TestGXmlClassFactory::TestGXmlClassFactory()
{
}

TestGXmlClassFactory::~TestGXmlClassFactory()
{
}

TEST_F(TestGXmlClassFactory, CreateStreamWriter)
{
	try
	{
	GXmlStreamWriter* xmlWriter = GXmlClassFactory::CreateStreamWriter("z.xml");
	xmlWriter->WriteStartTag("root");
	{
		xmlWriter->WriteSingleTag("single_tag");
		xmlWriter->WriteSingleTag("single_tag", { GXmlAttribute("name","value"), GXmlAttribute("name_two","2") });
		xmlWriter->WriteStartTag("value_tags", { GXmlAttribute("name","value"), GXmlAttribute("name_two","2") });
		{
			xmlWriter->WriteValueTag("value_tag", "tag text");
			xmlWriter->WriteValueTag("value_tag", { GXmlAttribute("name","value"), GXmlAttribute("name_two","2") }, "tag text");
		}
		xmlWriter->WriteEndTag();
		xmlWriter->WriteComment("Just a comment");
	}
	xmlWriter->WriteEndTag();
	delete xmlWriter;
	}
	catch(GException &e)
	{
		CERR << e.what() << endl;
	}
	catch(std::exception &e)
	{
		CERR << e.what() << endl;
	}
	catch(...)
	{
		CERR << "UNKNOWN exception caught" << endl;
	}

}

TEST_F(TestGXmlClassFactory, CreateStreamReader)
{
	try
	{
	struct KDBConnectionConfig {
		std::string engine;
		std::string server;
		std::string database;
		std::string user;
		std::string password;
		std::string passwordEncryption;
		std::string passwordEncoding;
	};

	struct KDBConnections
	{
		std::string mode;
		std::map<std::string, KDBConnectionConfig> config;
	};


	std::string exedir =  g_system()->GetExeDir();
	
	/// FORCE_DEBUG("EXEC DIR = %s", exedir.c_str() );
	
	#ifdef _WIN32
	std::string configFilePath = exedir + "..\\..\\config\\config.xml";
	#else
	std::string configFilePath = exedir + "/../../../../config/config.xml";
	#endif
	

	G_DEBUG("using config path: %s", configFilePath.c_str());


	std::shared_ptr<GXmlStreamReader> xmlReader = GXmlClassFactory::CreateStreamReaderSmartPtr(configFilePath);
	std::shared_ptr<GXmlNode> node(xmlReader->ReadNode());

	KDBConnections connections;
	std::stack<std::shared_ptr<GXmlNode>> xmlNodeStack;
	std::string activeConfigType;
	while (node != nullptr) 
	{
		const std::vector<GXmlAttribute> attributes = node->GetAttributes();

		switch (node->GetType())
		{
		case eXML_NODETYPE::EOpenTagNode:
			xmlNodeStack.push(node);

			if (xmlNodeStack.size() == 1)
			{
				G_ASSERT_EXCEPTION(node->GetName() == "database", "invalid root node");
				const auto mode = std::find_if(attributes.cbegin(), attributes.cend(),
					[](const GXmlAttribute& attr) {return attr.GetName() == "mode";  });
				G_ASSERT_EXCEPTION(mode != attributes.cend(), "mode attribute missing from database tag");

				connections.mode = mode->GetValue();
			}
			else if (xmlNodeStack.size() == 2)
			{
				G_ASSERT_EXCEPTION(node->GetName() == "connection", "invalid node, expected connection");
				const auto type = std::find_if(attributes.cbegin(), attributes.cend(),
					[](const GXmlAttribute& attr) {return attr.GetName() == "type";  });
				G_ASSERT_EXCEPTION(type != attributes.cend(), "type attribute missing from connection tag");

				activeConfigType = type->GetValue();
			}
			else if (xmlNodeStack.size() == 3 && node->GetName() == "password")
			{
				const auto encryption = std::find_if(attributes.cbegin(), attributes.cend(),
					[](const GXmlAttribute& attr) {return attr.GetName() == "encryption";  });
				G_ASSERT_EXCEPTION(encryption != attributes.cend(), "encryption attribute missing from password tag");

				const auto encoding = std::find_if(attributes.cbegin(), attributes.cend(),
					[](const GXmlAttribute& attr) {return attr.GetName() == "encoding";  });
				G_ASSERT_EXCEPTION(encoding != attributes.cend(), "encoding attribute missing from password tag");
				connections.config[activeConfigType].passwordEncryption = encryption->GetValue();
				connections.config[activeConfigType].passwordEncoding = encoding->GetValue();
			}
			break;
		case eXML_NODETYPE::ECloseTagNode:
			xmlNodeStack.pop();
			break;
		case eXML_NODETYPE::ETextNode:
		{
			const std::shared_ptr<GXmlNode> top = xmlNodeStack.top();

			if (top->GetName() == "engine")
			{
				connections.config[activeConfigType].engine = node->GetValue();
			}
			else if (top->GetName() == "server")
			{
				connections.config[activeConfigType].server = node->GetValue();
			}
			else if (top->GetName() == "database")
			{
				connections.config[activeConfigType].database = node->GetValue();
			}
			else if (top->GetName() == "user")
			{
				connections.config[activeConfigType].user = node->GetValue();
			}
			else if (top->GetName() == "password")
			{
				connections.config[activeConfigType].password = node->GetValue();
			}
			else
			{
				G_ASSERT_EXCEPTION(false, "Got unexpected text node \"%s\"", top->GetName().c_str());
			}
		} break;
		default:
				G_ASSERT_EXCEPTION(false, "Got unexpected node type");
		}

		node.reset(xmlReader->ReadNode());
	}



	G_DEBUG("--- config file read ---");

	G_DEBUG("mode: %s", connections.mode.c_str());
	
	for (const auto& connection : connections.config)
	{
		G_DEBUG("  type: %s", connection.first.c_str());
		const auto config = connection.second;

		G_DEBUG("    engine: %s", config.engine.c_str());
		G_DEBUG("    server: %s", config.server.c_str());
		G_DEBUG("    database: %s", config.database.c_str());
		G_DEBUG("    user: %s", config.user.c_str());
		G_DEBUG("    password: %s", config.password.c_str());
		G_DEBUG("    passwordEncryption: %s", config.passwordEncryption.c_str());
		G_DEBUG("    passwordEncoding: %s", config.passwordEncoding.c_str());
	}

	// Testing read results
	G_ASSERT_EXCEPTION(connections.mode == "Testsystem", "mode incorrect");
	G_ASSERT_EXCEPTION(connections.config.count("testrun") == 1, "connection incorrect");
	G_ASSERT_EXCEPTION(connections.config.at("testrun").engine == "PSQL", "engine incorrect");
	G_ASSERT_EXCEPTION(connections.config.at("testrun").server == "localhost", "server incorrect");
	G_ASSERT_EXCEPTION(connections.config.at("testrun").user == "dblab", "user incorrect");
	G_ASSERT_EXCEPTION(connections.config.at("testrun").password == "******Kryptert******", "password incorrect");
	G_ASSERT_EXCEPTION(connections.config.size() == 1, "connection map size incorrect");

		}
	 catch(GException &e)
	 {
	 	CERR << e.what() << endl;
	 }
	 catch(std::exception &e)
	 {
	 	CERR << e.what() << endl;
	 }
	 catch(...)
	 {
	 	CERR << "UNKNOWN exception caught" << endl;
	 }
}
