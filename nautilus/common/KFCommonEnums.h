
#pragma once
/*** DONE ***/
/** FOR HMI/GUI */
enum class eCRING : int
{
    C_RING_1_180 = 1,
    C_RING_2_360 = 2
};


enum class eDIRECTION : int
{
    NEGATIVE       = -1,
    READ_FROM_FRAM = 0, // This one might need to be confirmed,
    POSITIVE       = 1,
    CW,             // Clokcwise
    CCW,             //  Counter clockwise
    INVALID,
    UNKNOWN
};



/** Use by HMI/GUI */
enum class eORIENTATION
{
	VERTICAL = 1,
	HORIZONTAL,
	UNKNOWN
};


/** Use by HMI/GUI */
enum class eHMI_TYPE
{
    CRING180 = 1,
    CRING360,
    COATING,
    WRAPPING,
    SURFACE_PREP,
    PATCHING,
    HABITAT,
    UNKNOWN
};


enum class eSEM_COMMAND_ID : int
//G_ENUM(eSEM_COMMAND_ID, int,
{
    DEBUG1 = 1,     ///  for ebugging only
    DEBUG2,     ///  for ebugging only
    DEBUG3,     ///  for ebugging only
    BLINK_LED_ON,     ///  for ebugging only
    BLINK_LED_OFF,    ///  for ebugging only
    MOTOR_DEBUG_ON,   ///  for ebugging only
    MOTOR_DEBUG_OFF,   ///  for ebugging only
    REQUEST_SENSOR_VALUE,
    REQUEST_MOTOR_POSITION,
    REQUEST_STATE,   // Request current state of the SEM
    REQUEST_FW_VERSION,          ///  request FW revision info form SEM
    REQUEST_CONFIG,
    SET_SINGLE_VALUE,
    SET_XY_VALUE,
    GO_HOME,
    CALIBRATE_HOME,
    SOLENOID_ACTIVATE,
    SOLENOID_DE_ACTIVATE,
    PWM_SET,
    MOTOR_XY_START_CONTINUOUS_TRANSLATION,
    MOTOR_XY_STOP_CONTINUOUS_TRANSLATION,
    MOTOR_XY_START_CONTINUOUS_ROTATION,
    MOTOR_XY_STOP_CONTINUOUS_ROTATION,
    MOTOR_XY_SET_SPEED,
    MOTOR_XY_SET_SPEED_TRANSLATION,
    MOTOR_XY_SET_SPEED_ROTATION,
    MOTOR_XY_SET_POSITION,
    MOTOR_XY_INCREMENT_POSITION,

    MOTOR_STEPPER_START_CONTINIOUS_MOVE, // 0 or one parameter, -1/1 = negative direction, 1 = positive direction
    MOTOR_STEPPER_START_INCREMENT_POSITION,  // one parameter, float = SI unit
    MOTOR_STEPPER_START_GOTO_POSITION,   // one parameter, float = SI unit
    MOTOR_STEPPER_STOP_HARD,
    MOTOR_STEPPER_STOP_SOFT,
    MOTOR_STEPPER_SET_SPEED,
    MOTOR_STEPPER_SET_ACCELERATION,
    MOTOR_STEPPER_SET_CURRENT,
    MOTOR_STEPPER_SET_INACTIVE_CURRENT,
    MOTOR_STEPPER_CONFIGURE_POSITION,
    PAUSE,
    RESUME,
    INVALID = 98,
    UNKNOWN = 99
};



enum class eSENSOR_TYPE /// CRAP PTH, do we need this ENUM ?
{
	TEMPERATURE = 1,
	HUMIDITY ,
	CURRENT ,
	VOLTAGE ,
	PRESSURE,
	UNKNOWN
};


enum class eEXPOSURE_TYPE /// CRAP PTH, do we need this ENUM ?
{
	AUTO = 1,
	MANUAL,
	UNKNOWN
};
