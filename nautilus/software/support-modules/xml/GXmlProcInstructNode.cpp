// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#include "GXmlProcInstructNode.h"

GXmlProcInstructNode::GXmlProcInstructNode(const std::string& target, const std::string& content)
	: GXmlNodeImpl(target, content)
{
}

eXML_NODETYPE GXmlProcInstructNode::GetType() const
{
	return eXML_NODETYPE::EProcInstrNode;
}