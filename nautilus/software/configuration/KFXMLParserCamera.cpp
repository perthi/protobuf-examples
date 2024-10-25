// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFXMLParserCamera.h"


#include <configuration/KFEntityCamera.h>
#include <configuration/KFConfigCamera.h>
#include <configuration/KFPositionCamera.h>

#include <utilities/GException.h>
#include <utilities/GNumbers.h>

#include <xml/GXmlClassFactory.h>
#include <xml/GXmlStreamWriter.h>
#include <xml/GXmlStreamReader.h>
#include <xml/GXmlValidator.h>


KFXMLParserCamera::KFXMLParserCamera()
{

}

KFXMLParserCamera::~KFXMLParserCamera()
{

}


void
KFXMLParserCamera::ParseXML(vector< std::shared_ptr< KFEntityCamera > >& cameras, vector< std::shared_ptr<KFConfigCamera> >& camera_configs,  const XMLFile_t file_xml, const  XSDFile_t file_xsd)
{
    cameras.erase( cameras.begin(), cameras.end() );
    camera_configs.erase(camera_configs.begin(), camera_configs.end());

    try
    {
        G_ASSERT_EXCEPTION(GXmlValidator::IsValid(file_xml.str(), file_xsd.str() ), "Faild to validate XML file %s against %s", \
                 file_xml.str().c_str(), file_xsd.str().c_str());
        std::shared_ptr<GXmlStreamReader> xmlReader = GXmlClassFactory::CreateStreamReaderSmartPtr(file_xml.str() );
        GXmlNode *node =  xmlReader->ReadNode();
        //std::stack<std::shared_ptr<GXmlNode>> xmlNodeStack;
       // std::string activeConfigType;

		// SET_LOGFORMAT("11000111");
        // SET_LOGLEVEL("--all-debug");
        bool isvalid = GXmlValidator::IsValid(file_xml.str(), file_xsd.str() );
        G_FATAL("valid = %s", isvalid == true ? "TRUE" : "FALSE");

        while (node != nullptr)
        {
            if (node->GetName() == "CAMERA" && node->GetType() == eXML_NODETYPE::EOpenTagNode)
            {
                std::shared_ptr<KFEntityCamera> c = std::make_shared<KFEntityCamera>();
                c->fID =         GetTagValue( xmlReader, "ID");
                c->fConfigID =   GetTagValue( xmlReader, "CONFIG_ID");
                c->fName =       GetTagValue( xmlReader, "NAME");
                string enabled = GetTagValue( xmlReader, "ENABLED");
                G_ASSERT_EXCEPTION(enabled == "TRUE" || enabled == "FALSE", "Illegal value %s, nuts be either TRUE OR FALSE", enabled.c_str());

                if (enabled == "TRUE")
                {
                    c->fIsEnabled = true;
                }
                else if (enabled == "FALSE")
                {
                    c->fIsEnabled = false;
                }

                c->fIPAddress = GetTagValue( xmlReader, "IP_ADDRESS");
                c->fProductID = GetTagValue( xmlReader, "PRODUCT_ID");
                c->fCring =     GetTagValue( xmlReader, "C_RING");
                node = xmlReader->ReadNode();
                G_ASSERT_EXCEPTION(node->GetType() == eXML_NODETYPE::ECloseTagNode, "Unexcpeted node typ %d", node->GetType());
                G_ASSERT_EXCEPTION(node->GetName() == "CAMERA", "Unexpeced name %s, expected CAMERA", node->GetName().c_str());
                cameras.push_back(c);
            }

            if (node->GetName() == "CAMERA_CONFIG" && node->GetType() == eXML_NODETYPE::EOpenTagNode)
            {
                std::shared_ptr<KFConfigCamera> cfg = std::make_shared<KFConfigCamera>();
                cfg->fID =       GetTagValue( xmlReader, "ID");
                cfg->fName =     GetTagValue( xmlReader, "NAME");
                string enabled = GetTagValue( xmlReader, "ENABLED");
                G_ASSERT_EXCEPTION(enabled == "TRUE" || enabled == "FALSE", "Illegal value %s, nuts be either TRUE OR FALSE", enabled.c_str());

                if (enabled == "TRUE")
                {
                    cfg->fIsEnabled = true;
                }
                else if (enabled == "FALSE")
                {
                    cfg->fIsEnabled = false;
                }

                string exposure_type  = GetTagValue( xmlReader, "EXPOSURE_TYPE");

                if (exposure_type == "AUTO")
                {
                    cfg->fExposutreType = eEXPOSURE_TYPE::AUTO;
                }
                else if (exposure_type == "MANUAL")
                {
                    cfg->fExposutreType = eEXPOSURE_TYPE::MANUAL;
                }
                else
                {
                    EXCEPTION("Illegela valeue %s for tag EXPOSURE_TYPE", exposure_type.c_str() );
                }

                node =  xmlReader->ReadNode();
                G_ASSERT_EXCEPTION(node->GetType() == eXML_NODETYPE::EOpenTagNode, "Epsxpced opening tag");
                G_ASSERT_EXCEPTION(node->GetName() == "SCREEN_POSITION", "expceted tag  SCREEN_POSITION, got %s",  node->GetName().c_str()  );

                KFPositionCamera p;

                p.fLeft =    GetTagValue<int>(xmlReader, "LEFT") ;
                p.fTop  =    GetTagValue<int>(xmlReader, "TOP") ;
                p.fWidth =   GetTagValue<int>(xmlReader, "WIDTH") ;
                p.fHeight =  GetTagValue<int>(xmlReader, "HEIGHT") ;

                node = xmlReader->ReadNode();
                G_ASSERT_EXCEPTION(node->GetType() == eXML_NODETYPE::ECloseTagNode, "Expected closing tag");
                G_ASSERT_EXCEPTION(node->GetName() == "SCREEN_POSITION", "expceted tag  SCREEN_POSITION, got %s", node->GetName().c_str());
                cfg->fPosition = p;
                node =  xmlReader->ReadNode();
                G_ASSERT_EXCEPTION(node->GetType() == eXML_NODETYPE::ECloseTagNode, "Excepected closing tag");
                G_ASSERT_EXCEPTION(node->GetName() == "CAMERA_CONFIG", "expceted tag  CAMERA_CONFIG, got %s", node->GetName().c_str());
                camera_configs.push_back( cfg );
                //	FORCE_DEBUG("TP3, CAMERA CONFIG size = %d",  camera_configs.size() );
            }
            node = xmlReader->ReadNode();
        }
    }
    catch (GException& e)
    {
        CERR << e.what() << endl;
        throw(e);
    }

}



vector < std::shared_ptr<KFEntity>  >
KFXMLParserCamera::ParseXML(const XMLFile_t  /*xml*/, const XSDFile_t /*xsd*/ )
{
    ENGINE_FATAL("NOT IMPLEMENTED");
    vector < std::shared_ptr<KFEntity>  >tmp;
    return tmp;
}