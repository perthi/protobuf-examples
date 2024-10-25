// -*- mode: c++ -*-

#pragma once

#undef ERROR
#undef NO_ERROR

///#include <utilities/GEnum.h>

#if defined( __unix__ )  || defined (_WIN32 )
#include <protocol/kf.pb.h>
#else
#include "kf.pb.h"
#endif

#if defined( __unix__ )  || defined (_WIN32 )
#include <kf-common/KFCommonEnums.h>
#else
#include "KFCommonEnums.h"
#endif


enum class eSEM_COMMAND_PAYLOAD_TYPE
{
    FLOAT = SEMCommand_val_tag,  
    XY = SEMCommand_xy_tag, 
    NONE = 0, 
    INVALID = 98,
    UNKNOWN = 99
};



enum class ePB_MESSAGE_ONEOF_TYPE
{
    SEM_STATUS = SEMMessage_sem_status_tag,
    SENSOR_STATUS = SEMMessage_sensor_status_tag,
    BOOL_SENSOR_STATUS =  SEMMessage_bool_sensor_status_tag,
    MOTOR_STEPPER_STATUS =  SEMMessage_motor_status_tag,
    SOLENOID_STATUS =  SEMMessage_solenoid_status_tag,
    MOTOR_XY_STATUS =  SEMMessage_xy_motor_status_tag,
    CONFIGURATION_REPLY = SEMMessage_configuration_reply_tag,
    COMMAND_REPLY = SEMMessage_command_reply_tag,
    INVALID = 98,
    UNKNOWN = 99
};



/** Top level oneof message */
enum class ePB_ONEOF_TYPE : pb_size_t
{
    MESSAGE =  SEMOneOfMessage_sem_message_tag,
    COMMAND =  SEMOneOfMessage_sem_command_tag,
    CONFIG =   SEMOneOfMessage_sem_config_tag,
    INVALID = 98,
    UNKNOWN = 99
};





enum class eSEM_CONFIGTYPE : pb_size_t
{
    SEM =  SEMConfig_sem_tag,
    MOTOR_STEPPER = SEMConfig_motor_stepper_tag,
    MOTOR_XY = SEMConfig_motor_xy_tag,
    SOLENOID = SEMConfig_solenoid_tag,
    PWM = SEMConfig_pwm_tag,
    SENSOR_ANALOG = SEMConfig_sensor_analog_tag,
    SENSOR_BOOL =  SEMConfig_sensor_bool_tag,
    INVALID = 98,
    UNKNOWN = 99
};



enum class eSENSOR_INPUT_TYPE :  pb_size_t
{
	PNP = 1,
	MA_0_20,  // 0-20mA
	MA_4_20,  // 0-40mA
	V0_10,    //  0-10V
	PWM_RC,
	PWM_DUTY, // PWM duty cycle
	SPI,
	I2C,
    INVALID,
	UNKNOWN
};




enum class eDEVICE_TYPE
{
    SEM = 1,
    MOTOR_STEPPER,
    MOTOR_VIRTUAL_XY,
    SOLENOID,
    PWM_SIGNAL,
    PWM_POWER,
    SENSOR_ANALOG_DIRECT,
    SENSOR_LOCAL,
    SENSOR_BOOL_DIRECT,
 //   SENSOR_TEMPERATURE,
 //   SENSOR_VOLUME,
    INVALID,
    UNKNOWN
};






enum class eSTEP_UNIT
{
    ANGLE_DEGREES =1,
    MM,
    UNKNOWN
};



/*******************************************************************/
/******* Enums for SEM Message states, error codes, statuses *******/
/*******************************************************************/
/** States of the SEM itself */
enum class eSEM_SEM_STATE
 // 1-NOT_CONFIGURED, 2-RUNNING, 3-ERROR, 4-READY
{ // 1-NOT_CONFIGURED, 2-RUNNING, 3-ERROR, 4-READY
    ERROR = 0x01,   /// Execution OK.
    NOT_CONFIGURED = 0x02,
    READY = 0x04,
    RUNNING = 0x08,
    UNKNOWN = 0x10
};


enum class eSEM_ERROR_CODE
{
     // 0x01 - Communication Error, 0x02 - Sensor Not Connected
    ERROR = 0x1,
    NO_ERROR = 0x2,
    UNKNOWN = 0x4
};



/*** SENSOR MESSAGES ****/
/** Sensor state (SEMSensorMessage.state ) */
enum class eSEM_SENSOR_STATE
{
    // 1-NOT_CONFIGURED, 2-RUNNING, 3-ERROR
    NOT_CONFIGURED = 1,
    RUNNING,
    ERROR,
    UNKNOWN
};

/** Alaram status (SEMSensorMessage.alarm_status ) */
enum class eSEM_SENSOR_ALARM_STATUS
{
    NOT_CONFIGURED = 1,
    NO_ALARMS,
    ALARM_LOW,
    WARNING_LOW,
    WARNING_HIGH,
    ALARM_HIGH
};

/** Sensor states (SEMSensorMessage.error_code ) */
enum class eSEM_SENSOR_ERROR_CODE
{
     // 0x01 - Communication Error, 0x02 - Sensor Not Connected
    COMMUNICATION_ERROR = 0x1,
    ERROR = 0x2,
    UNKNOWN = 0x4
};
/*** END SENSOR MESSAGES ****/




/*** BOOL SENSOR MESSAGES ****/
/** Motor state SEMMessageSensorBool.state */
enum class eSEM_BOOL_SENSOR_STATE
{
    NOT_CONFIGURED = 1,
    RUNNING,
    ERROR,
    UNKNOWN
};

enum class eSEM_BOOL_SENSOR_ERROR_CODE
{
     // 0x01 - Communication Error, 0x02 - Sensor Not Connected
    COMMUNICATION_ERROR = 0x1,
    ERROR = 0x2,
    UNKNOWN = 0x4
};

/*** END BOOL SENSOR MESSAGES ****/



/*** MOTOR MESSAGES ****/
/** Motor state SEMMessageMotor.state */
enum class eSEM_MOTOR_STATE
{
    NOT_CONFIGURED = 1,
    RUNNING,
    ERROR,
    READY,
    FINISHED,
    ABORTING,
    ABORTED,
    STOPPING,
    STOPPED,
    UNKNOWN
};


/** Motor error state states (SEMMessageMotor.error_code ) */
enum class eSEM_MOTOR_ERROR_CODE
{
    NO_ERROR = 0x00,
    EXECUTION_ERROR = 0x01,
    OVER_TEMPERATURE = 0x02,
    OVER_CURRENT = 0x04,
    SHORT_CIRCUIT  = 0x8,
    INVALID_COMMAND = 0x10,
    INVALID_PARAMETER = 0x20,
    UNSPECIFIED_ERROR = 0x40
};

  enum class eMOTOR_DIRECTION
    {
        BACKWARD = 0,
        FORWARD = 1
    };

/*** END SENSOR MESSAGES ****/



/*** SOLENOID MESSAGES ****/
/** Motor state SEMMessageSolenoide.state */
enum class eSEM_SOLENOID_STATE
{
    // 1-NOT_CONFIGURED, 2-ERROR, 3-ACTIVATED, 4-DEACTIVATED
    ERROR = 1,   /// Execution OK.
    NOT_CONFIGURED,
    READY,
    RUNNING,
    UNKNOWN
};


/** Motor error state states (SEMMessageSolenoid.error_code ) */
enum class eSEM_SOLENOID_ERROR_CODE
{
     // 0x00 -
    NO_ERROR = 0x00,
    EXECUTIOM_ERROR = 0x01,
    OVER_TEMPERATURE = 0x02,
    OVER_CURRENT = 0x04,
    SHORT_CIRCUIT = 0x08,
    INVALID_COMMAND = 0x10,
    UNSPECIFIED_ERROR = 0x20
};
/*** END SENSOR MESSAGES ****/


/**** XY MOTOR MESSAGES ****/
/** Motor error state states (SEMMessageXYMotor.state ) */
enum class eSEM_XY_MOTOR_STATE
{
    ERROR =1,   /// Execution OK.
    NOT_CONFIGURED,
    READY,
    RUNNING,
    FINISHED,
    ABORTING,
    ABORTED,
    STOPPING,
    STOPPED,
    UNKNOWN
};


/** Motor error state states (SEMMessageXYMotor.error_code ) */
enum class eSEM_XY_MOTOR_ERROR_CODE
{
    NO_ERROR = 0x00,
    EXCUTION_ERROR = 0x01,
    FOLLOW_ERROR = 0x02,
    INVALID_COMMAND =  0x04,
    UNSPECIFIED_ERROR = 0x08
};
/*** END XY MESSAGES ****/



enum class eSEM_CONFIGURATION_ERROR_CODE
{
    ERROR = 1,
    NO_ERROR = 2
};


enum class eSEM_COMMAND_ERROR_CODE
{
    ERROR = 1,
    NO_ERROR = 2
};



/*******************************************************************/
/******* END Enums for SEM Message states, error codes, statuses *******/
/*******************************************************************/

