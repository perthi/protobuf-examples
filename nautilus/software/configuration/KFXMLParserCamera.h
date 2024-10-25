// -*- mode: c++ -*-
#ifndef KFXMLPARSERCAMERA_H
#define KFXMLPARSERCAMERA_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFXMLParser.h"
#include "KFEntityCamera.h"
#include "KFConfigCamera.h"
#include <xml/GXmlDataTypes.h>

#include <vector>

using std::vector;


class  KFXMLParserCamera : public KFXMLParser
{
	public: 
	API KFXMLParserCamera();
	virtual API ~KFXMLParserCamera();
	//virtual void API ParseXML(const XMLFile_t  /*xml*/, const XSDFile_t /*xsd*/) override {};
	virtual vector< std::shared_ptr<KFEntity> > API ParseXML(const XMLFile_t  /*xml*/, const XSDFile_t /*xsd*/ )  override;
	
	void API ParseXML(  vector< std::shared_ptr<KFEntityCamera> > &c, vector< std::shared_ptr<KFConfigCamera> > &cfg,  const XMLFile_t  xml,  const XSDFile_t xsd );
};


#endif
