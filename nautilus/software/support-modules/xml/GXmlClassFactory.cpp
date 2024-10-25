// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlClassFactory.h"
#include "GXmlStreamWriterImpl.h"
#include "GXmlStreamReaderImpl.h"

#include <utilities/GException.h>

GXmlStreamWriter* GXmlClassFactory::CreateStreamWriter(std::string fileName)
{
	return(new GXmlStreamWriterImpl(fileName));
}

GXmlStreamReader* GXmlClassFactory::CreateStreamReader(const std::string& fileName)
{
	return(new GXmlStreamReaderImpl(fileName));
}

API std::shared_ptr<GXmlStreamWriter> GXmlClassFactory::CreateStreamWriterSmartPtr(std::string fileName)
{
	return(std::make_shared<GXmlStreamWriterImpl>(fileName));
}

API std::shared_ptr<GXmlStreamReader> GXmlClassFactory::CreateStreamReaderSmartPtr(const std::string & fileName)
{
	return(std::make_shared<GXmlStreamReaderImpl>(fileName));
}
