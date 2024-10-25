#include "KFCard.h"


#include <sstream>
#include <utilities/GUtilities.h>

#include <iostream>

using std::endl;

string  
KFCard::str() const
{
	std::stringstream buffer;
	buffer << g_utilities()->TabAlign("MANUFACTURER_ID:") << fManufacturerID <<endl;
	buffer << g_utilities()->TabAlign("CARD_NAME:") << fCardName << endl;
	buffer << g_utilities()->TabAlign("CARD_ID:") << fCardID << endl;;
	buffer << g_utilities()->TabAlign("PORT:") << fPort << endl;
	return buffer.str();
}
