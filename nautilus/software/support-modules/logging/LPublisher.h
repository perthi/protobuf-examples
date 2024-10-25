// -*- mode: c++ -*-
#pragma once

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#include "LLogApi.h"
#include <utilities/GDefinitions.h>

#include <memory>


namespace LOGMASTER
{
    struct LMessage;
    class LLogging;
    class LConfig;

    /** @class LPublisher
	* class that is responsible for writing ( publishing) messages to various targets. Available targets
	* for the moment is  File, subscribere functions, or standra output (i.e the console). Targets soon to
	* be added is GUI, and TCP/IP port */
    class LPublisher
    {
        friend LLogging;
    public:		
        static  void API  EnableColor();
        static  void API  DisableColor();
        static bool  API *GetEnableColor();
    
    private:
        static void     PublishMessage(const std::shared_ptr<LMessage>, const std::shared_ptr<LConfig>,  const eMSGTARGET target );
        static void     PublishToSubscribers(const std::shared_ptr<LMessage>   msg);
        static void     PublishToGuiSubscribers(const std::shared_ptr<LMessage> msg);
        static void     PublishToConsole(const std::shared_ptr<LMessage>  msg);
        static void     PublishToFile(const char * filename, const std::shared_ptr<LMessage>   );
        static bool     fgEnableColor; 	/* !< Wether or not colors will be used for distinguishing messages when they are written to the console */
    };

}
