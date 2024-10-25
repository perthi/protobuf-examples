#pragma once

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <testlib/TestBase.h>
#include <utilities/GEnum.h>

class TestGEnum : public TestBase
{
public:
	G_ENUM(eTESTINT, { EN,TO,UNKNOWN = -1 });
};

class TestKEnum2
{
public:
	G_ENUM(eTESTINT2, { EN, TO=2 });
	eTESTINT2 fEnumInt2;
};
