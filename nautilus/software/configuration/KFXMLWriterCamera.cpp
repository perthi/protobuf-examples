// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include    "KFXMLWriterCamera.h"
#include    <xml/GXmlStreamWriter.h>
#include    <xml/GXmlClassFactory.h>
#include    <utilities/GException.h> 
#include    <utilities/GNumbers.h>
#include    <utilities/GString.h>

#include   "KFEntityCamera.h"
#include   "KFConfigCamera.h"
#include   <memory>


void
KFXMLWriterCamera::WriteXML(const XMLFile_t xml_file, vector< std::shared_ptr<KFEntityCamera> >& c,  vector< std::shared_ptr<KFConfigCamera> >&  cfg ) const
{
    try
    {
        GXmlStreamWriter* xmlWriter = GXmlClassFactory::CreateStreamWriter(xml_file.str() );
        xmlWriter->WriteStartTag("FERROTECH");
        {
            for (size_t i = 0; i < c.size(); i++)
            {
                xmlWriter->WriteStartTag("CAMERA");
                {
                    auto camera = c.at(i);
                 //   auto camera = std::dynamic_pointer_cast<KFEntityDeviceCamera>(c.at(i));
                    ENGINE_ASSERT_EXCEPTION(camera != nullptr, "cast failed, ZERO pointer" );
                  //  auto camera =  dynamic_cast<  KFCamera >(c.at(i));
                    xmlWriter->WriteValueTag("ID", camera->fID);
                    xmlWriter->WriteValueTag("CONFIG_ID", camera->fConfigID );
                    xmlWriter->WriteValueTag("NAME", camera->fName );
                    string enabled = camera->fIsEnabled == true ? "TRUE" : "FALSE";
                    xmlWriter->WriteValueTag("ENABLED", enabled );
                    xmlWriter->WriteValueTag("IP_ADDRESS", camera->fIPAddress );
                    xmlWriter->WriteValueTag("PRODUCT_ID", camera->fProductID  );
                    xmlWriter->WriteValueTag("C_RING", camera->fCring );
                }
                xmlWriter->WriteEndTag( );
            }
            
            for (size_t i = 0; i < cfg.size(); i++)
            {
             //   auto camera_cfg = dynamic_pointer_cast<KFConfigCamera> (cfg.at(i)) ;
                auto camera_cfg = cfg.at(i);
                ENGINE_ASSERT_EXCEPTION(camera_cfg != nullptr, "cast failed, ZERO pointer" );

                xmlWriter->WriteStartTag("CAMERA_CONFIG");
                {
                    xmlWriter->WriteValueTag("ID", camera_cfg->fID);
                    xmlWriter->WriteValueTag("NAME", camera_cfg->fName);
                    string enabled = camera_cfg->fIsEnabled == true ? "TRUE" : "FALSE";
                    xmlWriter->WriteValueTag("ENABLED", enabled);
                    xmlWriter->WriteValueTag("EXPOSURE_TYPE", camera_cfg->GetExposureTypeS());
                    xmlWriter->WriteStartTag("SCREEN_POSITION");
                    
                    {
                        xmlWriter->WriteValueTag("LEFT", g_string()->ToString(camera_cfg->fPosition.fLeft));
                        xmlWriter->WriteValueTag("TOP", g_string()->ToString(camera_cfg->fPosition.fTop));
                        xmlWriter->WriteValueTag("WIDTH", g_string()->ToString(camera_cfg->fPosition.fWidth));
                        xmlWriter->WriteValueTag("HEIGHT", g_string()->ToString(camera_cfg->fPosition.fHeight));
                    }
                    xmlWriter->WriteEndTag();
                }
                xmlWriter->WriteEndTag();
            }
            xmlWriter->WriteEndTag();
        }
        delete xmlWriter;
    }
    catch (GException& e)
    {
        CERR << e.what() << endl;
    }
    catch (std::exception& e)
    {
        CERR << e.what() << endl;
    }
    catch (string& e)
    {
        CERR << e << endl;
    }
    catch (...)
    {
        CERR << "UNKNOWN exception caught" << endl;
    }
    
}
