// -*- mode: c++ -*-

#pragma once

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <utilities/GDefinitions.h>
#include <common/MBDataTypes.h> 

/// GENERATE_DATATYPE(XMLFile_t, string);
/// GENERATE_DATATYPE(XSDFile_t, string);


class XMLFile_t  : public MBDataType<string> 
{ 
	public:
		XMLFile_t ( ) : MBDataType("") {};
		XMLFile_t ( string val) : MBDataType(val) {};
};

class XSDFile_t  : public MBDataType<string> 
{ 
	public:
		XSDFile_t ( ) : MBDataType("") {};
		XSDFile_t ( string val) : MBDataType(val) {};
};