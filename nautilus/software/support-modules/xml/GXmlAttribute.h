// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifndef GXMLATTRIBUTE_H
#define GXMLATTRIBUTE_H

#include <utilities/GDefinitions.h>
#include <string>



/** @brief xml attribute
	@details implements a simple Node-like class for attributes
*/
class GXmlAttribute
{
public:
	API GXmlAttribute(const std::string& name, const std::string& value);
	API std::string GetName() const;
	API std::string GetValue() const;
private:
	const std::string fName;
	const std::string fValue;
};

#endif // !GXMLATTRIBUTE_H