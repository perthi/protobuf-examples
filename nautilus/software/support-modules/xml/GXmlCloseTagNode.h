// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlTagNode.h"
#include "GXmlEnums.h"

class GXmlCloseTagNode : public GXmlTagNode
{
public:
	using GXmlTagNode::GXmlTagNode;
	virtual eXML_NODETYPE GetType() const override { return eXML_NODETYPE::ECloseTagNode; }
};
