// -*- mode: c++ -*-
#ifndef KFXMLWRITER_H
#define KFXMLWRITER_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFEntityDevice.h"
#include "KFConfig.h"

#include <utilities/GDefinitions.h>
#include <xml/GXmlDataTypes.h>

#include <memory>
#include <vector>

using std::vector;

class  KFXMLWriter
{
	public:
	API KFXMLWriter();
	virtual API  ~KFXMLWriter();
	//virtual void API WriteXML(const  XMLFile_t xml_file,  vector<   std::shared_ptr<KFEntityDevice> > &,  vector<  std::shared_ptr<KFConfig> >  &  ) = 0;
};

#endif
