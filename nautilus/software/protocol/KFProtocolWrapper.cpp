// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFProtocolWrapper.h"
#include <utilities/GCrc.h>

#if defined( __unix__ )  || defined (_WIN32 )
#include <utilities/GException.h>
#include <logging/LLogApi.h>
using namespace LOGMASTER;
#endif


KFProtocolWrapper::KFProtocolWrapper()
{

}


KFProtocolWrapper::~KFProtocolWrapper()
{

}


void     
KFProtocolWrapper::WrapMessage( const uint8_t *input_buffer, const uint16_t size_ib,  uint8_t *output_buffer,  const uint16_t size_ob, uint16_t *total_size )
{
    uint16_t tot_size = size_ib + N_EXTRA_BYTES; 
    *total_size = tot_size;
    output_buffer[0] = START_BYTE;
    output_buffer[1] = START_BYTE;
    
    GCrc c;

    uint8_t size_lb = c.LoByte( tot_size ); 
    uint8_t size_hb = c.HiByte( tot_size ); 

    output_buffer[2] =  size_lb;
    output_buffer[3] =  size_hb;

    //output_buffer[2] = *total_size; 

    for( size_t i = 0; i <  size_ib; i++ )
    {
      output_buffer[i +4] = input_buffer[i]; 
    }

  

    uint16_t o_size = 0;
   // void         AddCrc16(  uint8_t * in, const size_t input_size, size_t *output_size );
    c.AddCrc16(output_buffer, size_ib,  &o_size );

    #if defined( __unix__ )  || defined (_WIN32 )
    G_ASSERT_EXCEPTION( tot_size == o_size, "size must be equals( got %d and %d)", tot_size, o_size );
    #endif

}


#if defined( __unix__ )  || defined (_WIN32 )
void    
KFProtocolWrapper::WrapMessage( const string in,  string &out  )
{
    uint16_t size =  in.size() + N_EXTRA_BYTES; 
    uint8_t* buf_out = new  uint8_t[ size ];
    uint16_t tot_size = 0; 
    WrapMessage( (uint8_t *) in.c_str(), in.size(), buf_out, size,  &tot_size ); 
    out.erase( out.begin(), out.end() );

    for (  uint16_t i = 0; i < tot_size; i++ )
    {
        out.push_back( buf_out[i] );
    }

    delete[] buf_out;
}

void  
KFProtocolWrapper::ExtractMessageBody( const string in,  string &out  )
{
    out.erase( out.begin(), out.end() );
    uint16_t size =  in.size() + N_EXTRA_BYTES; 
    uint8_t* buf_out = new  uint8_t[ size ];

    uint16_t size_out = 0; 

    for( size_t i = 0; i < in.size(); i++   )
    {
       ExtractMessageBody( (const uint8_t *)in.c_str(), in.size(), buf_out, size, &size_out  ); 
    }

    for(uint16_t i =0; i <  size_out; i ++ )
    {
        out.push_back( buf_out[i] );
    }


    delete[] buf_out;     
}

#endif


void     
KFProtocolWrapper::ExtractMessageBody( const uint8_t *input_buffer, const uint16_t size_ib,   uint8_t *output_buffer,  const  uint16_t size_ob,  uint16_t *size )
{
    uint16_t  idx_start =  N_START_BYTES + N_SIZE_BYTES;

    for(  uint16_t i = idx_start; i <  size_ib - N_CRC_BYTES; i ++ )
    {
        output_buffer[i] =  input_buffer[i];  
    }

    *size = size_ib - N_EXTRA_BYTES;
}