// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlCDataNode.h"

GXmlCDataNode::GXmlCDataNode(const std::string& value)
	: GXmlNodeImpl("", value)
{
}

eXML_NODETYPE  GXmlCDataNode::GetType() const
{
	return eXML_NODETYPE::ECDataNode;
}
