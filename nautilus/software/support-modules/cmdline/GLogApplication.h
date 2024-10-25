// -*- mode: c++ -*-
#pragma once

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


/** @class GLogApplication
*   @brief Main application that all applications should inherit from. The
*   constructors of this class initializes arguments for the logging system so that the logging system can be configured
*   from the command line by all applications that inherits from this class.
*
*   It also adds a command line tag "--version"
*   that when issued on the commanline prints out SVN revision and tag information for this application. That is, which source code
*   revision, branch (trung, tag, or release) an release tag (v-x-y-z) the application was compiled from.
*   The SVN information is contained in the object pointet to by SvnData fSvnData. The SvnData class is autogenerted based on the current SVN
*   Information. The autogeneration tool is svninfo.exe.
*/

#include <utilities/GDefinitions.h>
#include <utilities/GFileName_t.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

template <typename T> class GCommandLineArgument;
#include <cmdline/GArgument.h>
#define DO_INIT true
#define DONT_INIT false
#include <functional>


class GLogApplication
{
public:
    API GLogApplication( const bool init = false ) : fArgs(0), fHelp(0), fLog(0), fTarget(0), fFormat(0), fColor(0)
    {
        if(init == true )
        {
            InitLogArgs();
        }
    };

    API  GLogApplication(	const int argc, const char** argv,  vector  <GArgument *> *additional_arguments = 0, bool do_init = DO_INIT);
    API  GLogApplication(	const GFileName_t &t,  vector  <GArgument *> *additional_arguments = 0);
    API  virtual ~GLogApplication();

    void		API             Purge();
    void		API		SetCallBackFunction(	const string cmd,
                                                std::function< bool( const string cmd,  const string args_s,
                                                                     const vector<string> sub, const	vector<string> par ) > funct ) ;

    void		API		AddArgument(GArgument *  arg);
    void		API		AddArguments(vector<GArgument *>  *args);
    GArgument	API *	GetArgument(const string cmd);
    void		API		RemoveArgument(const string cmd);
#ifdef _WIN32
    void		API		ScanArguments();
#endif

public:
    virtual void        API		ScanArguments(const string cmdline);
    virtual void        API		ScanArguments(const string cmdline, GArgument * arg);
    virtual void        API		ScanArguments(const string cmdline, vector  <GArgument *> *args);
    virtual void        API		ScanArguments(const int argc, const char** argv, vector  <GArgument *> *arg);
    virtual void        API		ScanArguments(const int argc, const char** argv);
    static bool			API		HasCommand( vector<GArgument *>  *args, const string cmd);
    bool				API		HasCommand( const string cmd);
    vector<GArgument *>	API	 *	GetArguments();
    string				API		Help(const string cmd = "" ) const;
    static string		API		Help(const vector  <GArgument *> args, const string cmd = "" );
    string				API		Help(const char *exename, const string heading,  const string cmd = "" ) const;
    virtual void		API		InitLogArgs();
	int					API		SetMandatory(const string cmd);
	int					API		SetOptional(const string cmd);
	bool				API		IsMandatory(const string cmd) const;
	bool				API		IsOptional(const string cmd) const;


protected:
    vector  <GArgument *>    fArgs;  //!< vector containing all arguments that is valid for this application
    GCommandLineArgument < void >  *fHelp; //!< Command line argument for printing out version information
  ///  GCommandLineArgument < void >  *fVersion; //!< Command line argument for printing out version information
    GCommandLineArgument < vector< string > >  *fLog;     //!< Command line argument for the configuration of the log  level
    GCommandLineArgument < vector< string > >  *fTarget;  //!< Command line argument for the configuration of the log  target
    GCommandLineArgument < vector< string > >  *fFormat;  //!< Command line argument for the configuration of the log  format
    GCommandLineArgument < bool >  *fColor;   //!< Command line argument for controling wether or not to use color coding of log messages

 private:
    GLogApplication (GLogApplication &);
    void operator=(GLogApplication &);
    //  SvnData *fSvnData;   //!< Pointer to object that holds Svn information autogenerated by the build system
};


#define CATCH_EXCEPTION \
 catch (GText &e) \
{ \
	G_ERROR("%s",e.what()); \
    throw(e); \
} \
catch (GException &e) \
{ \
    static char tmp[8096]; \
    SPRINTF(tmp, 8096, "%s", e.GetMessageL()->fMsgBody );       \
    G_ERROR("%s", tmp);\
    throw(e); \
} \
catch (std::exception &e) \
{ \
	G_ERROR("%s",e.what()); \
        throw(e);               \
} \
catch (...) \
{ \
	G_ERROR("%s","Unknown exception caught"); \
        throw("Unknown exception caught");        \
}
