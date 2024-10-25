// -*- mode: c++ -*-


/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#ifndef GXMLCLASSFACTORY_H
#define GXMLCLASSFACTORY_H

#include <utilities/GDefinitions.h>
#include <string>
#include <memory>

class GXmlStreamWriter;
class GXmlStreamReader;

class GXmlClassFactory
{
public:
	static API GXmlStreamWriter* CreateStreamWriter(std::string fileName);
	static API GXmlStreamReader* CreateStreamReader(const std::string& fileName);
	static API std::shared_ptr<GXmlStreamWriter> CreateStreamWriterSmartPtr(std::string fileName);
	static API std::shared_ptr<GXmlStreamReader> CreateStreamReaderSmartPtr(const std::string& fileName);
};

#endif // !GXMLCLASSFACTORY_H
