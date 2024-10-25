// -*- mode: c++ -*-
#pragma once

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#include <logging/LEnums.h>
#include <utilities/GDefinitions.h>

#include <map>
#include <tuple>
#include <string>
#include <vector>

using std::string;
using std::map;
using std::vector;


namespace LOGMASTER
{
	class LConfig;
	class LLogging;

	class LHashMaps
	{
		friend LConfig;
		friend LLogging;

	public:
            API    LHashMaps(  );
            API    LHashMaps(const eMSGLEVEL level  );
            API    ~LHashMaps();
            static  LHashMaps API* Instance();
            
            static void		API		InitHash();
            void			API		InitHash( const eMSGLEVEL level );
            static void		API		InitHashMsgFormat();
            static void		API		InitHashLogTags();
            static void		API		InitHashLogTargets();
            static void		API		InitHashSystem2String();
            static void		API		InitHashLevel2String();
            void			API		InitHashLogLevel(const eMSGLEVEL level);
            
            static	string							API DoxygenDoc(const string filename);
            static	map < string, std::tuple<  eMSGSYSTEM, eMSGLEVEL > >  API * GetSubCmdHash();
            static  map < string, eMSGTARGET>		API *	GetTargetHash();
            static  map < string, eMSGFORMAT>		API	*	GetFormatHash();
            static	map <eMSGSYSTEM, string >		API *	GetSystem2StringHash();
            static	map <eMSGLEVEL, string  >		API	*	GetLevel2StringHash();

            static  eMSGTARGET              API		GetTarget( const string  &hash);
            static  eMSGFORMAT              API		GetFormat( const string  &hash );
            static	vector<eMSGTARGET>		API  	GetTargetEnums();
            static	vector<eMSGFORMAT>		API  	GetFormatEnums();
            static  vector<eMSGSYSTEM>		API  	GetSystemEnums();
            static  vector<eMSGLEVEL>		API  	GetLevelEnums();
            static	vector<string>			API		GetLogLevelTags();
            static	vector<string>			API		GetLogTargetTags();
            static	vector<string>			API		GetLogFormatTags();
            static bool                     API     IsTargetHash( const string &target );
            static bool                     API     IsFormatHash( const string &format );
            static bool                     API     IsSubCmdHash( const string &subcmd );
            
        private:
            
            static map < string, std::tuple<  eMSGSYSTEM, eMSGLEVEL > >  fSubCmdHash;
            static map < string, eMSGTARGET>	fTargetHash;
            static map < string, eMSGFORMAT>	fFormatHash;
            static map <eMSGSYSTEM, string >	fSystem2StringHash;
            static map <eMSGLEVEL, string  >	fLevel2StringHash;
            map < eMSGSYSTEM, eMSGLEVEL>		fLogLevelHash;
            eMSGLEVEL							fDefaultLevel;
            bool								fIsInitialized = false;
	};

}
