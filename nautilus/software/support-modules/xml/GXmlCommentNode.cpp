// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlCommentNode.h"

GXmlCommentNode::GXmlCommentNode(const std::string& comment)
	: GXmlNodeImpl("", comment)
{
}

eXML_NODETYPE GXmlCommentNode::GetType() const
{
	return eXML_NODETYPE::ECommentNode;
}
