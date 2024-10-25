// -*- mode: c++ -*-
#ifndef KFPROTOCOLWRAPPER_H
#define KFPROTOCOLWRAPPER_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#define START_BYTE 0xaa

#define  N_START_BYTES 2
#define  N_SIZE_BYTES 2
#define  N_CRC_BYTES  2

#define  N_EXTRA_BYTES   N_START_BYTES  + N_SIZE_BYTES + N_CRC_BYTES


#include <stdint.h>
#include <cstddef>

#include <string>
using  std::string;


class  KFProtocolWrapper
{
	public:
		KFProtocolWrapper();
		virtual  ~KFProtocolWrapper();
		void     WrapMessage( const uint8_t *input_buffer, const  uint16_t size_ib,     uint8_t *output_buffer,  const uint16_t size_ob, uint16_t *size );		
		void     ExtractMessageBody( const uint8_t *input_buffer, const uint16_t size_ib,   uint8_t *output_buffer,  const  uint16_t size_ob,  uint16_t *size );	

	  #if defined( __unix__ )  || defined (_WIN32 )
		void     WrapMessage( const string in,  string &out  );		
		void     ExtractMessageBody( const string in,  string &out  );	
      #endif		

};

#endif
