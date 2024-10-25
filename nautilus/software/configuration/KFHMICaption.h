#pragma once

#include <string>
using std::string;

#include <utilities/GPrintable.h>

#include <utilities/GDefinitions.h>

struct KFHMICaption : public GPrintable 
{
	virtual  string  API str() const override;	
	string fCaption = "";
	string fCaptionMin = "";
	string fCaptionMax = "";
};