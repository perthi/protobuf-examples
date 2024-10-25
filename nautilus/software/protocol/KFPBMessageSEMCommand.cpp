// -*- mode: c++ -*-
/***********************************************************************************
 * This file is property of and copyright by Kongsberg Ferrotech  2019             *
 *                                                                                 *
 * Author: Per Thomas Hille <pth@embc.no> for Semcon Devotek & Konsgberg Ferrotech *
 * Contributors are mentioned in the code where appropriate.                       *
 * Please report bugs to pth@embc.no                                               *
 ***********************************************************************************/

#include "KFPBMessageSEMCommand.h"
#include "KFProtocolUtilities.h"
#include <sstream>
//#include <utilities/GUtilities.h>




KFPBMessageSEMCommand::KFPBMessageSEMCommand() : KFPBMessageSEM( ( pb_field_t *  )SEMCommand_fields )
{
    Reset();
}





KFPBMessageSEMCommand::~KFPBMessageSEMCommand()
{

}


void
KFPBMessageSEMCommand::Reset(  )
{
    Reset( fCmd );
} 


void
KFPBMessageSEMCommand::Reset(  SEMCommand  *t )
{
    t->cmd_id = 0;
    
    for(size_t i=0; i <  sizeof( t->device_id ); i ++) 
    {
        t->device_id[i] = 0;
    }
    
  ///  t->has_sequence_id = false;
  ///  t->sequence_id = 0;
    t->which_payload = 0;
    t->payload.val.f_val = 0;
    t->payload.xy.x = 0;
    t->payload.xy.y = 0;
} 


float      
KFPBMessageSEMCommand::GetValue() 
{
    return fCmd->payload.val.f_val;
}


float       
KFPBMessageSEMCommand::GetValueX()
{
   return fCmd->payload.xy.x;     
}


float       
KFPBMessageSEMCommand::GetValueY()
{
    return fCmd->payload.xy.y;
}


void 
KFPBMessageSEMCommand::GetValueXY( float &x, float &y )
{
    x = fCmd->payload.xy.x;    
    y = fCmd->payload.xy.y;    
}


int
KFPBMessageSEMCommand::SetPayload( const float  val )
{
      fCmd->payload.val.f_val = val;
      fCmd->which_payload =  SEMCommand_val_tag;
      return 0; // CRAP PTH
}


int  
KFPBMessageSEMCommand::SetPayload( const float x, const float y )
{
    fCmd->payload.xy.x = x;    
    fCmd->payload.xy.y = y;    
    fCmd->which_payload =  SEMCommand_xy_tag;
    return 0; // CRAP PTH
}


eSEM_COMMAND_ID
KFPBMessageSEMCommand::GetCommandID() const
{ 
    return  (eSEM_COMMAND_ID)fCmd->cmd_id;

}



void
KFPBMessageSEMCommand::SetCommandID( const eSEM_COMMAND_ID   cmd  )
{
    fCmd->cmd_id = (int)cmd;

 //   return SetCommandID(cmd);
}




#if defined( __unix__ )  || defined (_WIN32 )
string  
KFPBMessageSEMCommand::GetDeviceID() const
{
    return string( fCmd->device_id );
}
#endif


int
KFPBMessageSEMCommand::GetDeviceID(char *id, const size_t max_size) const
{
    int n = max_size < sizeof( this->fCmd->device_id) ? max_size : sizeof( this->fCmd->device_id);
    // errno_t strcpy_s(char *restrict dest, rsize_t destsz, const char *restrict src);
    strncpy( id, (const char *)this->fCmd->device_id, n );
    return CMD_OK;
   /// return fCmd->device_id;
}




#if defined( __unix__ )  || defined (_WIN32 )
int
KFPBMessageSEMCommand::SetDeviceID(const string  id )
{
    KFPBMessageSEM::SetString( this->fCmd->device_id, sizeof( this->fCmd->device_id), id.c_str() );
    return CMD_OK;
}
#endif


int 
KFPBMessageSEMCommand::SetDeviceID(const char  *id, size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->device_id) ? max_size : sizeof( this->fCmd->device_id);
    strncpy( this->fCmd->device_id, id, n );
    ////return ret;

   // KFPBMessageSEM<T>::SetString( this->fCmd->device_id, sizeof( this->fCmd->device_id), id.c_str() );
    return CMD_OK;
}





#if defined( __unix__ )  || defined (_WIN32 ) 
void   
KFPBMessageSEMCommand::SetFieldsFloat( const string device_id, const eSEM_COMMAND_ID cmd, const float val )
{
    SetDeviceID( device_id );
    SetCommandID(cmd);
    SetPayload(val);
}



void   
KFPBMessageSEMCommand::SetFields( const string device_id, const eSEM_COMMAND_ID cmd )
{
    SetDeviceID( device_id );
    SetCommandID(cmd);
}



void   
KFPBMessageSEMCommand::SetFieldsXY( const string device_id, const eSEM_COMMAND_ID cmd, const float x, const float y )
{
    SetDeviceID( device_id );
    SetCommandID(cmd);
    SetPayload( x, y);
}
#endif




void   
KFPBMessageSEMCommand::SetFieldsFloat( const char *id, const size_t max_size, const eSEM_COMMAND_ID cmd, const float val )
{
    SetDeviceID( id, max_size );
    SetCommandID(cmd);
    SetPayload(val);
}



void   
KFPBMessageSEMCommand::SetFields( const char *id, const size_t max_size, const eSEM_COMMAND_ID cmd )
{
    SetDeviceID( id, max_size );
    SetCommandID(cmd);
}



void   
KFPBMessageSEMCommand::SetFieldsXY( const char *id, const size_t max_size, const eSEM_COMMAND_ID cmd, const float x, const float y )
{
    SetDeviceID( id, max_size );
    SetCommandID(cmd);
    SetPayload( x, y);
}



eSEM_COMMAND_PAYLOAD_TYPE
KFPBMessageSEMCommand::GetPayloadType() const
{
    return  (eSEM_COMMAND_PAYLOAD_TYPE)fCmd->which_payload;  
}

void             
KFPBMessageSEMCommand::SetPayloadType( const eSEM_COMMAND_PAYLOAD_TYPE type)
{
    fCmd->which_payload = (int)type;   
}



#if defined( __unix__ )  || defined (_WIN32 )
string       
KFPBMessageSEMCommand::str() const
{
    std::stringstream buffer;
    buffer <<  g_utilities()->TabAlign("DEVICE_ID:")  << fCmd->device_id << endl;
    buffer <<  g_utilities()->TabAlign("COMMAND_ID:") <<  KFProtocolUtilities::Enum2String(  (eSEM_COMMAND_ID)fCmd->cmd_id ) << endl;

    if( fCmd->which_payload == SEMCommand_val_tag )
    {
        buffer << g_utilities()->TabAlign("VALUE = ") << fCmd->payload.val.f_val << endl;
    }
    else if( fCmd->which_payload == SEMCommand_xy_tag  )
    {
        buffer <<  g_utilities()->TabAlign("X = ") << fCmd->payload.xy.x << endl;
        buffer <<  g_utilities()->TabAlign("Y = ") << fCmd->payload.xy.y << endl;
    }
    else
    {
        buffer << "ERROR, unknown payload tag" << fCmd->which_payload << endl;
    }
    
    return buffer.str();

}


#endif