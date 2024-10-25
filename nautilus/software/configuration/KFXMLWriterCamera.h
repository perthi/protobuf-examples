// -*- mode: c++ -*-

#pragma once


/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/


#include <utilities/GDefinitions.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include   <configuration/KFEntityCamera.h>
#include   <configuration/KFConfigCamera.h>
#include   <xml/GXmlDataTypes.h>

#include <memory>

#include "KFXMLWriter.h"


class KFXMLWriterCamera : public KFXMLWriter
{
public:
	void API WriteXML(const  XMLFile_t xml_file,  vector<   std::shared_ptr<KFEntityCamera> > &,  vector<  std::shared_ptr<KFConfigCamera> >  &  ) const ;
};

