// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include <utilities/GDefinitions.h>
#include <vector>
#include <memory>

using std::vector;

class GComponent;


class GlobalRegistry
{
public:
	static GlobalRegistry  API * Instance();
	void   API    CleanUp();
	void   API    RegisterComponent(std::shared_ptr<GComponent>  component);

private:
	GlobalRegistry();
	virtual ~GlobalRegistry();
	vector< std::shared_ptr<GComponent> > fComponentRegister;
};

