// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlTagNode.h"
#include "GXmlAttribute.h"

#include <algorithm>
#include <vector>

GXmlTagNode::GXmlTagNode(const std::string& name) 
	: GXmlNodeImpl(name, "")
{
}

std::vector<GXmlAttribute> GXmlTagNode::GetAttributes() const
{
	return fAttributes;
}

void GXmlTagNode::AddAttribute(const GXmlAttribute& attribute)
{
	fAttributes.push_back(attribute);
}

GXmlTagNode::~GXmlTagNode()
{
}
