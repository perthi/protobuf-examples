// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlAttribute.h"

#include <utilities/GDefinitions.h>
#include <string>
#include <vector>
#include "GXmlEnums.h"


/** @brief A Generic node interface
 *  @details An XML document looks something like this 
		@verbatim
		<root>
			<tag1>text for tag1</tag1>
			<tag2 x="42"></tag2>
			<tag3 y="-1"/>
		</root>

		Nodes have four properties: name, value, attributes, and type. Attributes is often empty
		but also name and value can be empty. 

		Examples of nodes:
		- <tag1>: OpenTagNode, name="tag1", value="", attributes={}
		- </tag2>: OpenTagNode, name="tag2", value="", attributes={}
		- <tag3>: SingleTagNode, name="tag3", value="", attributes={ y="-1" }
		- text for tag1: TextNode, name="", value="text for tag1", attributes={}
		@endverbatim
 */

class GXmlNode
{
public:
	virtual ~GXmlNode() {};

	API virtual eXML_NODETYPE GetType() const = 0; /*!< Get type of node */
	API virtual std::string GetName() const = 0; /*!< Get name of node, includes namespace */
	API virtual std::string GetValue() const = 0; /*!< Get value of node */
	API virtual std::vector<GXmlAttribute> GetAttributes() const = 0; /*!< Get attributes, empty if there are no attributes */
};


