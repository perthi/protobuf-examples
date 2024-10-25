// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#ifndef GXMLSTREAMREADERSP_H
#define GXMLSTREAMREADERSP_H

#include "GXmlNode.h"
#include <memory>
#include "xml/GXmlStreamReader.h"
#include "xml/GXmlClassFactory.h"
#include "GXmlEnums.h"


class GXmlNodeSpData;
class GXmlStreamReaderSp;

class GXmlNodeSp : public GXmlNode
{
public:
	API GXmlNodeSp(GXmlNode* data);
	API GXmlNodeSp(const GXmlNodeSp& rhs);
	API GXmlNodeSp() { fData = nullptr; }
	API GXmlNodeSp& operator=(const GXmlNodeSp& rhs);
	inline bool IsValid()
	{
		return(fData != nullptr);
	}

	// Inherited via GXmlNode
	virtual API eXML_NODETYPE GetType() const override;
	virtual API std::string GetName() const override;
	virtual API std::string GetValue() const override;
	virtual API std::vector<GXmlAttribute> GetAttributes() const override;
private:
	std::shared_ptr<GXmlNode> fData = nullptr;
	friend class  GXmlStreamReaderSp;
};

class GXmlStreamReaderSpData;
class GXmlStreamReader;

class GXmlStreamReaderSp
{
public:
	API GXmlStreamReaderSp(const std::string& fileName);
	API ~GXmlStreamReaderSp();
	API GXmlNodeSp ReadNode();
private:
    GXmlStreamReaderSp( const GXmlStreamReaderSp & );
	GXmlStreamReaderSp operator = ( const GXmlStreamReaderSp & );
	std::shared_ptr<GXmlStreamReader> fData;
};

#endif // !GXMLSTREAMREADERSP_H
