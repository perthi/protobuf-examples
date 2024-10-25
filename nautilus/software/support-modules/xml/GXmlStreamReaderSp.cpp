// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlStreamReaderSp.h"

GXmlNodeSp::GXmlNodeSp(GXmlNode* data)
{
	fData.reset(data);
}

GXmlNodeSp::GXmlNodeSp(const GXmlNodeSp& rhs)
{
	fData = rhs.fData;
}

GXmlNodeSp& GXmlNodeSp::operator=(const GXmlNodeSp& rhs)
{
	fData = rhs.fData;
	return(*this);
}

eXML_NODETYPE GXmlNodeSp::GetType() const
{
	return(fData->GetType());
}

std::string GXmlNodeSp::GetName() const
{
	return(fData->GetName());
}

std::string GXmlNodeSp::GetValue() const
{
	return(fData->GetValue());
}

std::vector<GXmlAttribute> GXmlNodeSp::GetAttributes() const
{
	return(fData->GetAttributes());
}

GXmlStreamReaderSp::GXmlStreamReaderSp(const std::string& fileName) : fData(nullptr)
{
	fData = std::shared_ptr<GXmlStreamReader>(GXmlClassFactory::CreateStreamReader(fileName));
}

GXmlStreamReaderSp::~GXmlStreamReaderSp()
{
}

GXmlNodeSp GXmlStreamReaderSp::ReadNode()
{
	GXmlNodeSp node(fData->ReadNode());
	return(node);
}
