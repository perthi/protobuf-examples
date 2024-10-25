// -*- mode: c++ -*-
#ifndef KFPROTOCOLUTILITIES_H
#define KFPROTOCOLUTILITIES_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include <utilities/GDefinitions.h>
#include "KFProtocolEnums.h"
#include <string>


using std::string;


class  KFProtocolUtilities
{
public:
    ///static  bool     API IsValidEnum( const  eSEM_COMMAND_ID cmd);
    static  string   API Enum2String( const  ePB_ONEOF_TYPE);
    static  string   API Enum2String( const  ePB_MESSAGE_ONEOF_TYPE);

    static  string   API Enum2String( const  eSEM_COMMAND_ID cmd );
    static  string   API Enum2String( const  eSEM_COMMAND_PAYLOAD_TYPE  type );
    
    static  string   API Enum2String( const  eSEM_SENSOR_STATE  type );
    static  string   API Enum2String( const  eSEM_SENSOR_ALARM_STATUS type );
    static  string   API Enum2String( const  eSEM_SENSOR_ERROR_CODE type );
    
    static  string   API Enum2String( const  eSEM_BOOL_SENSOR_STATE  type );
    static  string   API Enum2String( const  eSEM_BOOL_SENSOR_ERROR_CODE  type );
    
    static  string   API Enum2String( const  eSEM_MOTOR_STATE type );
    static  string   API Enum2String( const  eSEM_MOTOR_ERROR_CODE type );
    
    static  string   API Enum2String( const  eSEM_XY_MOTOR_STATE type );
    static  string   API Enum2String( const  eSEM_XY_MOTOR_ERROR_CODE type );
    
    static  string   API Enum2String( const  eSEM_SOLENOID_STATE type );
    static  string   API Enum2String( const  eSEM_SOLENOID_ERROR_CODE type );
    
    static  string   API Enum2String( const  eSEM_CONFIGURATION_ERROR_CODE  type );
    static  string   API Enum2String( const  eSEM_COMMAND_ERROR_CODE  type );
    
    static  string   API Enum2String( const  eSEM_SEM_STATE  type );
    static  string   API Enum2String( const  eSEM_ERROR_CODE  type );

};


#endif
