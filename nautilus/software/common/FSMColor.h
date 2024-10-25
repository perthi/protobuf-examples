// -*- mode: c++ -*-

/********************************************
* Author: Per Thomas Hille <pth@embc.no> ****
*********************************************/

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once


#include <utilities/GColor.h>

#define C_FSM_UNKNOWN		C_GRAY
#define C_FSM_OK			C_GREEN
#define C_FSM_RUNNING		C_GREEN
#define C_FSM_READY			C_GREEN
#define C_FSM_TRANSIENT		C_LIGHT_BLUE

//#define C_FSM_WAITING		C_BLUE
#define C_FSM_WAITING		C_BLUE
#define C_FSM_PAUSED		C_YELLOW

#define C_FSM_WARNING		C_YELLOW
#define C_FSM_ERROR			C_RED
#define C_FSM_FATAL			C_PURPLE

