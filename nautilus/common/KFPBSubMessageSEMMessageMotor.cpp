// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFPBSubMessageSEMMessageMotor.h"
//#include <utilities/GUtilities.h>
#include <sstream>
#include "KFProtocolUtilities.h"
#include <iomanip>


KFPBSubMessageSEMMessageMotor::KFPBSubMessageSEMMessageMotor() : KFPBMessageSEMMessageCommon( ( pb_field_t *  )SEMMessageMotor_fields )
{
    Reset();
}

KFPBSubMessageSEMMessageMotor::~KFPBSubMessageSEMMessageMotor()
{

}

void
KFPBSubMessageSEMMessageMotor::SetSpeed(const float speed)
{
    fCmd->value_speed = speed;
    fCmd->has_value_speed = true;
}


void
KFPBSubMessageSEMMessageMotor::SetEndStopReached( const bool val)
{
    fCmd->end_stop_reached = val;
    fCmd->has_end_stop_reached = true;

}


void
KFPBSubMessageSEMMessageMotor::SetHomePositionReached( const bool val)
{
    fCmd->home_position_reached = val;
    fCmd->has_home_position_reached = true;
}


float
KFPBSubMessageSEMMessageMotor::GetSpeed() const
{
    return fCmd->value_speed;
}

bool
KFPBSubMessageSEMMessageMotor::IsEndStopReached() const
{
    return fCmd->end_stop_reached;
}


bool
KFPBSubMessageSEMMessageMotor::IsHomePositionReached() const
{
    return fCmd->home_position_reached;
}


bool
KFPBSubMessageSEMMessageMotor::HasEndStopReached() const
{
    return fCmd->has_end_stop_reached;
}


bool
KFPBSubMessageSEMMessageMotor::HasHomePositionReached() const
{
    return fCmd->has_home_position_reached;
}


bool
KFPBSubMessageSEMMessageMotor::HasValueSpeed() const
{
    return fCmd->has_value_speed;
}

void
KFPBSubMessageSEMMessageMotor::SetPosition( const float position )
{
    fCmd->value_position = position;
}


float
KFPBSubMessageSEMMessageMotor::GetPosition() const
{
    return fCmd->value_position;
}



void
KFPBSubMessageSEMMessageMotor::Reset(  )
{
    Reset( fCmd );
}


void
KFPBSubMessageSEMMessageMotor::Reset( SEMMessageMotor *t)
{
    t->state = 0;
    t->value_position = 0;
    t->has_value_speed = false;
    t->value_speed = 0;
    t->has_end_stop_reached = false;
    t->end_stop_reached = false;
    t->has_home_position_reached = false;
    t->home_position_reached = false;
    t->has_error_code = false;
    t->error_code = 0;
    t->has_error_string = false;

    for(size_t i=0; i <  sizeof( t->error_string); i++ )
    {
        t->error_string[i] = 0;
    }
}


#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMMessageMotor::str() const
{
    std::stringstream buffer;

    buffer << g_utilities()->TabAlign("STATE:") << KFProtocolUtilities::Enum2String(GetState()) << endl;
    buffer << g_utilities()->TabAlign("POSITION") << GetPosition() << endl;
    buffer << g_utilities()->TabAlign("HAS_SPEED ?:") << ( HasValueSpeed() == true ? "TRUE" : "FALSE") << endl;

    if( HasValueSpeed() == true )
    {
        buffer << g_utilities()->TabAlign("SPEED:") << GetSpeed() <<  endl;
    }

    buffer << g_utilities()->TabAlign("HAS_ENDSTOP_REACHED ?:") << ( HasEndStopReached() == true ? "TRUE" : "FALSE") << endl;

    if( HasEndStopReached() == true )
    {
        buffer << g_utilities()->TabAlign("ENDSTOP_REACHED ?:") << ( IsEndStopReached() == true ? "TRUE" : "FALSE") << endl;
    }

    buffer << g_utilities()->TabAlign("HAS_HOME_POSITION_REACHED ?:") << ( HasHomePositionReached() == true ? "TRUE" : "FALSE") << endl;

    if( HasHomePositionReached() == true )
    {
        buffer << g_utilities()->TabAlign("HOME_POSITION_REACHED ?:") << ( IsHomePositionReached() == true ? "TRUE" : "FALSE") << endl;
    }

    buffer <<  KFPBMessageSEMMessageCommon::str();
    return buffer.str();
}



string
KFPBSubMessageSEMMessageMotor::strOneLine() const
{

    std::string endStop;
    if(HasEndStopReached())
    {
        endStop = (IsEndStopReached() ? "TRUE" : "FALSE");
    }
    else
    {
        endStop = "N/A";
    }

    std::string homePos;
    if(HasHomePositionReached())
    {
        homePos = (IsHomePositionReached() ? "TRUE" : "FALSE");
    }
    else
    {
        homePos = "N/A";
    }

	std::stringstream speed;
    if(HasValueSpeed())
    {
        speed << std::setprecision(2) << GetSpeed();
    }
    else
    {
        speed << "-";
    }


    GText buffer(
        "%-16s] POS[%-07.2f]\tSP[%-9s]\tHome[%5s] End[%5s]\tE[%s]%s",
        KFProtocolUtilities::Enum2String(GetState()).c_str(),
        GetPosition(),
        speed.str().c_str(),
        homePos.c_str(),
        endStop.c_str(),
        (HasErrorCode() ? KFProtocolUtilities::Enum2String(GetErrorCode()).c_str() : "-"),
        (HasErrorString() ? GetErrorString().c_str() : "")
        );

    return buffer.str();
}


#endif