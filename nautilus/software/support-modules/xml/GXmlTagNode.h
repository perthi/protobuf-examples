// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNodeImpl.h"
#include "GXmlAttribute.h"
#include <string>
#include <vector>

class GXmlTagNode : public GXmlNodeImpl
{
public:
	GXmlTagNode(const std::string& name);
	virtual ~GXmlTagNode();
	virtual std::vector<GXmlAttribute> GetAttributes() const override;

	void AddAttribute(const GXmlAttribute& attribute);
private:
	std::vector<GXmlAttribute> fAttributes;
};
