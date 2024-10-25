// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlDocTypeNode.h"

GXmlDocTypeNode::GXmlDocTypeNode(const std::string& name)
	: GXmlNodeImpl(name, "")
{
}

eXML_NODETYPE 
GXmlDocTypeNode::GetType() const
{
	return eXML_NODETYPE::EDocTypeNode;
}
