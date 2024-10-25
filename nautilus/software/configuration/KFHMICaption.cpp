
#include  "KFHMICaption.h"


#include <utilities/GException.h>

#include <sstream>
#include <utilities/GUtilities.h>
#include <iostream>

using std::endl;




string
KFHMICaption::str() const
{
    std::stringstream buffer;
    buffer << g_utilities()->TabAlign("CAPTION:") << fCaption << endl;
    buffer << g_utilities()->TabAlign("CAPTION_MIX:") << fCaptionMin << endl;
    buffer << g_utilities()->TabAlign("CAPTION_MAX:") << fCaptionMax << endl;
    return buffer.str();
}
