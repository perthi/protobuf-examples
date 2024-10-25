// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlTextNode.h"


GXmlTextNode::GXmlTextNode(const std::string& text)
	: GXmlNodeImpl("", text)
{
}

eXML_NODETYPE GXmlTextNode::GetType() const
{
	return eXML_NODETYPE::ETextNode;
}
