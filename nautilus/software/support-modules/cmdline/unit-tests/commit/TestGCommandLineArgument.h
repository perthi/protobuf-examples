// -*- mode: c++ -*-

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/

#pragma once


#include <testlib/TestBase.h>
#include <cmdline/GCommandLineArgument.h>
#include <utilities/GConstants.h>

#include <functional>
using std::function;


bool test(const string cmnd, const vector<string> sub, const vector<string> par)
{
    cerr << "hello world" << endl;
    return true;
}


using namespace GCONSTANTS;

class TestGCommandLineArgument : public TestBase
{
public:
    TestGCommandLineArgument();
    virtual ~TestGCommandLineArgument();
    virtual void SetUp();
    virtual void TearDown();
    
//	static bool ValidateFunct(const string cmnd, const string args_s, const vector<string> subs, const vector<string> args);
    virtual bool ValidateFunct(const string cmnd, const string args_s, const vector<string> subs, const vector<string> args);
	bool ValidateFunct2( const string /*cmnd*/, const string /*args_s*/ )
	{
		return false;
	}


	float f;
    double d = 0;
    long double ld = 0;
    short si = 0;
    int i = 0;
    long int li = 0;
    long long int lli = 0;

    unsigned short us;
    unsigned int ui = 0;
    unsigned long int uli = 0;
    unsigned long long int ulli = 0;
    bool b = false;
    string s = "";
    vector<string> vs;
    vector<int>  vi;
    vector<unsigned int>  vui;
    vector<double> vd;
    vector<long double> vld;
    vector<float> vf;

    GCommandLineArgument <float> *farg = new  GCommandLineArgument<float>("-myfloat", "-myfloat [value]", "This is the documentation", &f, fgkOPTIONAL, 0);
    GCommandLineArgument <double> *darg = new  GCommandLineArgument <double>("-mydouble", "-mydouble [value]", "This is the documentation", &d, fgkOPTIONAL, 0);
    GCommandLineArgument <long double> *ldarg = new  GCommandLineArgument <long double>("-myldouble", "-myldouble [value]", "This is the documentation", &ld, fgkOPTIONAL, 0);
    GCommandLineArgument <short> *siarg = new  GCommandLineArgument <short>("-mysint", "-mysint [value]", "This is the documentation", &si, fgkOPTIONAL, 0);
    GCommandLineArgument <int> *iarg = new  GCommandLineArgument <int>("-myint", "-myint [value]", "This is the documentation", &i, fgkOPTIONAL, 0 );
 
	GCommandLineArgument <long int> *liarg = new  GCommandLineArgument <long int>("-mylint", "-mylint [value]", "This is the documentation", &li, fgkOPTIONAL, 0);
    GCommandLineArgument <long long int> *lliarg = new  GCommandLineArgument <long long int>("-myllint", "-myllint [value]", "This is the documentation", &lli, fgkOPTIONAL, 0);
    GCommandLineArgument <unsigned short> *usarg = new  GCommandLineArgument <unsigned short>("-myusint", "-myusint [value]", "This is the documentation", &us, fgkOPTIONAL, 0);
    GCommandLineArgument <unsigned int> *uiarg = new  GCommandLineArgument <unsigned int>("-myuint", "-myuint [value]", "This is the documentation", &ui, fgkOPTIONAL, 0);
    GCommandLineArgument <unsigned long int> *uliarg = new  GCommandLineArgument <unsigned long int>("-myulint", "-myulint [value]", "This is the documentation", &uli, fgkOPTIONAL, 0);
    GCommandLineArgument <unsigned long long int> *ulliarg = new  GCommandLineArgument <unsigned long long int>("-myullint", "-myullint [value]", "This is the documentation", &ulli, fgkOPTIONAL, 0);
   
    GCommandLineArgument <bool> *barg = new  GCommandLineArgument <bool>("-mybool", "-mybool [value]", "This is the documentation", &b, fgkOPTIONAL, 0);
    GCommandLineArgument <void> *varg = new  GCommandLineArgument <void>("-myvoid", "-myvoid [value]", "This is the documentation", 0, fgkOPTIONAL, 0);
    GCommandLineArgument <string> *sarg = new  GCommandLineArgument <string>("-mystring", "-mystring [value]", "This is the documentation", &s, fgkOPTIONAL, 0);
    GCommandLineArgument <vector<string>> *vsarg = new  GCommandLineArgument <vector<string>>("-myvector", "-myvector [value1] [value2].... [valueN]", "This is the documentation", &vs, fgkOPTIONAL, 0);
    GCommandLineArgument <vector<int> >    *viarg  = new  GCommandLineArgument <vector<int>>("-myivector", "-myivector [value1] [value2].... [valueN]", "This is the documentation", &vi, fgkOPTIONAL, 0);
    GCommandLineArgument <vector<unsigned int> >    *vuiarg = new  GCommandLineArgument <vector<unsigned int>>("-myuivector", "-myuivector [value1] [value2].... [valueN]", "This is the documentation", &vui, fgkOPTIONAL, 0);
    GCommandLineArgument <vector<double> > *vdarg  = new  GCommandLineArgument <vector<double>>("-mydvector", "-mydvector [value1] [value2].... [valueN]", "This is the documentation", &vd, fgkOPTIONAL, 0);
    GCommandLineArgument <vector<long double> > *vldarg = new  GCommandLineArgument <vector<long double>>("-myldvector", "-myldvector [value1] [value2].... [valueN]", "This is the documentation", &vld, fgkOPTIONAL, 0);
    GCommandLineArgument <vector<float> > *vfarg = new  GCommandLineArgument <vector<float>>("-myfvector", "-myfvector [value1] [value2].... [valueN]", "This is the documentation", &vf, fgkOPTIONAL, 0);
  
    };

  
