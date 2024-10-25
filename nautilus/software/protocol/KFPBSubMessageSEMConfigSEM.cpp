// -*- mode: c++ -*-


#include "KFPBSubMessageSEMConfigSEM.h"


KFPBSubMessageSEMConfigSEM::KFPBSubMessageSEMConfigSEM() : KFPBMessageSEM(  ( pb_field_t * )SEMConfigSEM_fields )
{
    Reset();
}



KFPBSubMessageSEMConfigSEM::~KFPBSubMessageSEMConfigSEM()
{

}



void 
KFPBSubMessageSEMConfigSEM::Reset(SEMConfigSEM  * /*t*/ ) 
{
  //  t->dummy_field = 0;
}


void
KFPBSubMessageSEMConfigSEM::Reset(  ) 
{
   // fCmd->dummy_field = 0;

}


// void  
// KFPBSubMessageSEMConfigSEM::SetDummy(const char c )
// {
//     fCmd->dummy_field = c;
// }


// char
// KFPBSubMessageSEMConfigSEM::GetDummy( ) const
// {
//     return  fCmd->dummy_field;
// }


#if defined( __unix__ )  || defined (_WIN32 )
string     
KFPBSubMessageSEMConfigSEM::str() const
{
    std::stringstream buffer;
    ///buffer << g_utilities()->TabAlign("DUMMY:") << fCmd->dummy_field << endl; 
    //return buffer.str();

    return "not implemented";
}
#endif