// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNode.h"
#include "GXmlAttribute.h"

/** @brief A base implementation for GXmlNode 
 *  @details Provides a suitable constructor and basic implemetation for GetName, GetValue, GetAttributes
*/
class GXmlNodeImpl : public GXmlNode
{
public:
	GXmlNodeImpl(const std::string& name, const std::string& value);
	
	virtual ~GXmlNodeImpl();
	virtual std::string GetName() const override;
	virtual std::string GetValue() const override;
	virtual std::vector<GXmlAttribute> GetAttributes() const;
private:
	const std::string fkName;
	const std::string fkValue;
};