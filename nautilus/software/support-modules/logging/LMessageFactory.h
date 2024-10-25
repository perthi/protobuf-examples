// -*- mode: c++ -*-
#pragma once


/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

///#include <fec-core/common/include/KGDefinitions.h>
#include "LEnums.h"
#include <utilities/GDefinitions.h>


#include <string>

using std::string;

#include <memory>


namespace LOGMASTER
{
	struct  LMessage;
	class  LMessageGenerator;
	class  LConfig;
	class  LLogging;

	/** @class LMessageFactory
	* Helper class used by LLogging  */
	class LMessageFactory
	{

            friend LLogging;
	public:
            LMessageFactory();
            LMessageFactory( const LMessageFactory &gen );
            ~LMessageFactory();
            void      API    SetConfig( const LConfig  c );
           std::shared_ptr< LConfig>   API   GetConfig();
           std::shared_ptr< LMessage>  API  GetMessage();
            bool      API    IsEnabled() const;
            void      API    Enable();
            void      API    Disable();
            std::shared_ptr< LMessage>  API GenerateMessage( const eMSGSYSTEM s, const eMSGLEVEL l, const char *file, const int line, const char *func, const char *fmt, va_list ap, const string addedndum );
            
	private:
            LMessageFactory operator = ( const LMessageFactory &);
            bool fIsEnabled = true;
            std::shared_ptr<LMessage> fMessage = nullptr;
            std::shared_ptr<LMessageGenerator> fGenerator = nullptr;
            std::shared_ptr<LConfig> fConfig = nullptr;
	};

}

