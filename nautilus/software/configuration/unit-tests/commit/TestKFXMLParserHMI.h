#pragma once
#include "TestKFXML.h"

class TestKFXMLParserHMI : public TestKFXML
{
	protected:
	static  void    SetUpTestCase();
	virtual void    SetUp()     override;
	virtual void    TearDown()  override;
};
