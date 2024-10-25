// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#pragma once
#include "GXmlNode.h"

/*! @brief A simple interface for reading xml files node for node
	@details There are in principle two ways of looking at XML files. They can be viewed as trees or as a stream of nodes.
		This class provides a stream-of-nodes-interface to read XML files which means memory usage is minimal and constant
		no matter how large the XML file is.
*/
class GXmlStreamReader
{
public:
	virtual ~GXmlStreamReader() {};

	/*! @brief Read node from xml file and set up for next read
		@return pointer to node if success. nullptr on end of file or failure.
	*/
	virtual GXmlNode API * ReadNode() = 0;
	virtual GXmlNode API * GetCurrentNode() = 0;
	virtual int  API GetLineNumber()    const = 0;
	virtual int  API GetColumnNumber()  const = 0;

protected:
	GXmlNode *fCurrentNode  = nullptr;
};
