
#include "KFConfigMotor.h"

#include <sstream>
#include <utilities/GUtilities.h>



#include <iostream>
using std::endl;


#include "KFConfigUtilities.h"

string  
KFConfigMotor::str() const
{
	std::stringstream buffer;
	buffer << g_utilities()->TabAlign("DIRECTION_POSITIVE") << KFConfigUtilities::Instance()->Direction2String( fDirectionPositive ); 
	buffer << g_utilities()->TabAlign("ENDSTOP_POSITIVE:") << fEndStopPositive << endl;
	buffer << g_utilities()->TabAlign("ENDSTOP_NEGATIVE:") << fEndStopNegative << endl;
	buffer << g_utilities()->TabAlign("ENDSTOP_POSITIVE_ID:") << fEndStopPositiveID << endl;
	buffer << g_utilities()->TabAlign("ENDSTOP_NEGATIVE_ID:") << fEndStopNegativeID << endl;
	buffer << g_utilities()->TabAlign("MAX_SPEED:") << fMaxSpeed << endl;
	buffer << g_utilities()->TabAlign("MAX_ACCELERATION:") << fMaxAccelleration << endl;
	buffer << g_utilities()->TabAlign("MAX_CURRENT:") << fMaxCurrent << endl;
	buffer << g_utilities()->TabAlign("CURRENT") << fCurrent << endl;
	buffer << g_utilities()->TabAlign("INACTIVE_TIMEOUT") << fInactiveTimeout << endl;
	buffer << g_utilities()->TabAlign("INACTIVE_CURRENT") << fInactiveCurrent << endl;
	buffer << g_utilities()->TabAlign("HOME_VALUE") << fHomeValue << endl;

	buffer << g_utilities()->TabAlign("HAS_HOME_DIRECTION ?:") << (fHasDirectionHome == true ? "TRUE" : "FALSE") << endl;

	if( fHasDirectionHome == true )
	{
		buffer << g_utilities()->TabAlign("HOME_DIRECTION:") <<  KFConfigUtilities::Instance()->Direction2String( fDirectionHome ); 
	}

	return buffer.str();
}
