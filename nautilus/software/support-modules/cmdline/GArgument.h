// -*- mode: c++ -*-

#ifndef GArgumentBASE_H
#define GArgumentBASE_H

/***************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                     ****
****************************************************************************/

/****************************************************************************
*** Copyright(C) 2018  Per Thomas Hille, pth@embc.no                      ***
*** This file is part of logmaster.logmaster is free software : you can   ***
*** redistribute it and / or modify it under the terms of the Lesser GNU  ***
*** General Public License(LGPL) V3 or later.See.cpp file for details     ***
*****************************************************************************/


/** @class GArgument 
*   @brief Base class for all command line arguments
*
*   The main purpose of this class is to proved an interface that makes it possible to create a vector of  pointers to command line arguments. This vector is then used by the command line
*   handling system when scanning arguments (see GCmdScan). The main implementation is in the template class GCommandLinArgument.  It would not bes possibel in general to use this class when 
*   creating a vector *of pointers because different template initializations would yield different pointer types. */



#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>
#include <utilities/GConstants.h>
#include <vector>
using std::vector;

using namespace  GCONSTANTS;

#include <functional>

//class  GArgument : public GPrintable
class  GArgument
{
    friend class GCmdScan;

public: 
	API GArgument(	const string name, const string usage, const string helptxt,  const bool ismandatory,  
					std::function< bool ( const string cmnd, const string args_s, const vector<string> sub, const vector<string> par ) > funct ); 
	API GArgument();
    virtual API ~GArgument() { }
    
    static void API SetNTabs( const int n);
    inline bool		IsMandatory() const {  return  fIsMandatory; }
	inline bool		IsOptional() const { return  !IsMandatory(); }
	void    API		SetMandatory() { fIsMandatory = fgkMANDATORY; };
	void    API		SetOptional() { fIsMandatory = fgkOPTIONAL; };
	void    API		SetUsage(const string usage) { fUsage = usage; }

    string API      GetUsage() const { return fUsage; };
	  string API      GetHelpText() const { return fHelpText; }; 
    string		API GetHelpText(const bool subcommands ) const;
    

    virtual		API  string str(const bool subcommands = false) const;
    bool		Verify();
    void		API		AddSubCommand(const string cmd);
    void		API		SetCommand(const string cmd ){ fCmd = cmd; };
    void		API		SetSubCommands(const vector<string> sub){ fSubCmds = sub; };
    string		API		GetCommand() const {return fCmd ;};
    
    vector<string> &  GetSubCommands()  { return fSubCmds; };
    string          API    GetSubCommandsS();
    string            GetTypeId() const { return fTypeId;}
    string            GetTypeIdBase() const { return fTypeIdBase; }
    void              SetExcecName(const char *name);
  //  void  API  SetValidationFunction( bool(*funct) (const string cmd, const vector<string> sub, const 
   //                                                vector<string> par )   );
 	void		API		SetValidationFunction(  std::function< bool(const string cmd, const string args_s, const vector<string> sub, const vector<string> par )> funct );

protected:
    static int fNTabs;   /*!< The number of tabs to use when aligning the help menu output */  
    string  fCmd = "";
    vector<string> fSubCmds; 
    bool    fIsMandatory;
    string  fTypeId = "";
    string  fTypeIdBase = "";
    string  fUsage = "";
    string  fHelpText = "";
    string  fExecName = "";
  //  bool (*ValidateCommands)( const string cmd,  const vector<string> sub, const vector<string> par  );
	std::function< bool( const string cmd, const string args_s, const vector<string> sub, const vector<string> par ) >  ValidateCommands;

private : 
    
};



#endif

