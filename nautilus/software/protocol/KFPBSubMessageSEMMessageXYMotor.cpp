// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "KFPBSubMessageSEMMessageXYMotor.h"
#include <iomanip>

KFPBSubMessageSEMMessageXYMotor::KFPBSubMessageSEMMessageXYMotor(): KFPBMessageSEMMessageCommon(  (pb_field_t *  )SEMMessageXYMotor_fields)
{
    Reset();
}




KFPBSubMessageSEMMessageXYMotor::~KFPBSubMessageSEMMessageXYMotor()
{

}

void
KFPBSubMessageSEMMessageXYMotor::SetXYPosition( const float x, const float y)
{
    fCmd->value_x_position = x;
    fCmd->value_y_position = y;
}


void
KFPBSubMessageSEMMessageXYMotor::GetXYPosition( float &x, float &y)
{
    x = fCmd->value_x_position;
    y = fCmd->value_y_position;
}


void
KFPBSubMessageSEMMessageXYMotor::Reset(  )
{
    Reset(fCmd);
}


void
KFPBSubMessageSEMMessageXYMotor::Reset( SEMMessageXYMotor *t)
{
    t->error_code = 0;
    t->has_error_code= false;
    t->has_error_string = false;
    t->state = 0;

    for(size_t i=0; i < sizeof( t->error_string ); i ++ )
    {
        t->error_string[i] = 0;
    }

    t->value_x_position = 0;

    t->value_y_position = 0;

}



#if defined( __unix__ )  || defined (_WIN32 )
string
KFPBSubMessageSEMMessageXYMotor::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("STATE:") << KFProtocolUtilities::Enum2String(GetState()) << endl;
    buffer << g_utilities()->TabAlign("X:") << GetValueXPosition() << endl;
    buffer << g_utilities()->TabAlign("Y:") << GetValueYPosition() << endl;
    buffer << KFPBMessageSEMMessageCommon::str();
    return buffer.str();
}


string
KFPBSubMessageSEMMessageXYMotor::strOneLine() const
{
	std::stringstream xPos;
    xPos << std::setprecision(2) << GetValueXPosition();

	std::stringstream yPos;
    yPos << std::setprecision(2) << GetValueYPosition();

    GText buffer(
        "%-16s] POS[%-8s: %-12s]\t\t\t\tE[%s]%s",
        KFProtocolUtilities::Enum2String(GetState()).c_str(),
        xPos.str().c_str(),
        yPos.str().c_str(),
        (HasErrorCode() ? KFProtocolUtilities::Enum2String(GetErrorCode()).c_str() : "FALSE"),
        (HasErrorString() ? GetErrorString().c_str() : "")
        );

    return buffer.str();
}

#endif
