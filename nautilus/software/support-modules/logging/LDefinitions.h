// -*- mode: c++ -*-
#pragma once

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#define BINARY_SYSTEM_WIDTH 16       ///  The number of bits used to specify the logging sub-system
#define BINARY_LEVEL_WIDT  8         ///  The number of bits used to specify the log level
#define BINARY_TOTAL_FIELD_WIDTH  (BINARY_SYSTEM_WIDTH + BINARY_LEVEL_WIDT)
#define SUBSYSTEM_MASK 0xffff       
#define HEX_WIDTH 8
#define LOG_FORMAT_WIDTH 8        ///  The number of bits used to specify the log format
#define LOG_TARGET_WIDTH 4            ///  The number of bits used to specify the log target  
#define NO_PADDING false
#define WITH_PADDING true


