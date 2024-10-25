// -*- mode: c++ -*-
#ifndef KFPBMessageSEM_H
#define KFPBMessageSEM_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "KFProtocolEnums.h"
#include "kf.pb.h"

#define CMD_OK       1
#define CMD_INVALID  2

#include<vector>
using std::vector;

#include <string>
using std::string;


#if defined( __unix__ )  || defined (_WIN32 )
    #include <sstream>
    using std::endl;
    #include   <utilities/GDefinitions.h>
    #include   <utilities/GUtilities.h>
    #include   <utilities/GPrintable.h>
    #include   <utilities/GException.h>
    #include   <logging/LLogApi.h>
using namespace LOGMASTER;
#endif


#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <kf.pb.h>

#include "KFProtocolEnums.h"
#include "KFProtocolUtilities.h"
#include <type_traits>
#include <memory>


#include "KFPBCommon.h"


#if defined( __unix__ )  || defined (_WIN32 )
#include <utilities/GText.h>
#endif


/** C++ Wrapper for serializing an deserializing a SCM protobuf message
  * @author Per Thomas Hille
  * @template T the type of protobuf message as defined in kf.pb.h*/
template<class T>
#if defined( __unix__ )  || defined (_WIN32 )
class  KFPBMessageSEM : public GPrintable
#else
class  KFPBMessageSEM
#endif
{
	public:
        /** @brief Convert a protobuf struct fCmd to a serialized string
        *   @param[in, out] dta The string where the serialzied protobuf message will be stored
        *   @return true if the msg message was successfully serialized false othervise*/

    #if defined( __unix__ )  || defined (_WIN32 )
        inline virtual bool   SerializeToString( string &  dta  ) final;
    #endif

        /** @brief Convert a protobuf struct fCmd to a serialized character array
        *   @param  output_buffer[in, out] The charcter array where the serialzied protobuf message will be stored
        *   @param  buffer_size The size of the output buffer
        *   @param  size   The number of byrtes written to the output buffer
        *   @return true if the msg message was successfully serialized false othervise*/
        inline virtual bool   SerializeToString( uint8_t *output_buffer, const int buffer_size, int *size ) final;

        /** @brief   Convert a serialized message to applicable parameters and store it in the Protobuf struct fCmd
         *  @details The function extracts the parameters
         *   from dta and sets various parameters which are the available via thoer respective Getter functions.
         *  @param  msg[in]  The serialzed data which must be a valid serialized protobuf message
         *  @return true if the dta message was successfully serialized false othervise*/
#if defined( __unix__ )  || defined (_WIN32 )
        inline virtual bool   SerializeFromString(const string  dta );
#endif
        /** @copydoc SerializeFromString( string &dta )
         *  @param size[in] The size of the charcter array dta */
        inline virtual bool   SerializeFromString( const  uint8_t * const dta, const int size);
        inline virtual void Set(T *ptr);
        virtual void Reset(T *t)  = 0;
        virtual inline void Reset() = 0;
        void SetString( char * output_buffer, size_t size, const char * const input_buffer );

#if defined( __unix__ )  || defined (_WIN32 )
        inline virtual string strOneLine() const { return "UNDEFINED"; };
#endif

    protected:
        inline   KFPBMessageSEM(   pb_field_t  *  f );
        inline   KFPBMessageSEM(   pb_field_t  *  f, T *cmd );
        inline   virtual ~KFPBMessageSEM();

    ///    public:
        T  * fCmd  = nullptr;  //!< The actual protobuf command as defined in kf.pb.h */
        T   fCmdObj;          //! < to avoid dynamic memory allocation on embedded*/
        pb_field_t  *fFields = nullptr;

	private:
        inline   KFPBMessageSEM(const KFPBMessageSEM &) {};
        inline   const KFPBMessageSEM & operator = ( const KFPBMessageSEM & /*rhs*/ )  { return *this; };
};



template<class T>
inline
KFPBMessageSEM<T>::KFPBMessageSEM(  pb_field_t *   fields ) : fCmd(nullptr), fCmdObj()
{

    fCmd =  &fCmdObj;
    fFields =  fields;
}


template<class T >
inline
KFPBMessageSEM<T>::KFPBMessageSEM(  pb_field_t *  fields,  T *cmd ) : fCmd(cmd), fCmdObj(), fFields(nullptr)
{
    fFields =  fields;
}


template<class T >
inline
KFPBMessageSEM<T>::~KFPBMessageSEM()
{

}


template<class T>
inline void
KFPBMessageSEM<T>::Set(T *  ptr )
{
    this->fCmd = ptr;
}


template<class T>
inline void
KFPBMessageSEM<T>::SetString(char * output_buffer, size_t size, const char * const input_buffer )
{
#ifdef _WIN32
    sprintf_s( output_buffer, size -1, "%s", input_buffer );
#else
    snprintf( output_buffer, size -1, "%s",  input_buffer );
#endif

}


template<class T>
inline  void
KFPBMessageSEM<T>::Reset( )
{
    Reset(fCmd);
}


#if defined( __unix__ )  || defined (_WIN32 )
template<class T >
inline  bool
KFPBMessageSEM<T>::SerializeToString( string &  dta  )
{
    uint8_t buffer[1024] = {0}; /// CRAP PTH
    int bytes_written = 0;
    bool status = SerializeToString(  buffer, sizeof( buffer),  &bytes_written );

    dta.erase(dta.begin(), dta.end() );
    string tmp;

    for( int i=0; i <  bytes_written; i ++ )
    {
        tmp.push_back(buffer[i]); /// CRAP PTH
    }

    dta = tmp;
    return  status;
}
#endif


template<class T >
inline bool
KFPBMessageSEM<T>::SerializeToString( uint8_t *output_buffer, const int buffer_size, int *size  )
{
    pb_ostream_t stream = pb_ostream_from_buffer( output_buffer, buffer_size );

#if defined( __unix__ )  || defined (_WIN32 )
    MESSAGE_ASSERT_EXCEPTION(fCmd != nullptr, "fCmd is a ZERO POINTER !!");
#endif

    bool status = pb_encode(&stream, fFields, fCmd );
    size_t message_length = stream.bytes_written;

   if(status == false)
    {
#if defined( __unix__ )  || defined (_WIN32 )
        MESSAGE_ERROR("Error: failed to encode message; %s ",   PB_GET_ERROR( &stream)  );
#endif
        return false;
    }
    *size =  message_length;
    return  true;

}



template<class T>
inline bool
KFPBMessageSEM<T>::SerializeFromString( const uint8_t * const msg, const int size  )
{
  pb_istream_t stream = pb_istream_from_buffer( msg,  size );

#if defined( __unix__ )  || defined (_WIN32 )
    MESSAGE_ASSERT_EXCEPTION(fCmd != nullptr, "fCmd is a ZERO POINTER !!");
#endif

    bool status = pb_decode(&stream, fFields, fCmd );

    if ( status == false )
    {
#if defined( __unix__ )  || defined (_WIN32 )
        G_ERROR("Decoding failed: %s", PB_GET_ERROR(&stream) );
#endif
        return false;
    }

    return true;

}


#if defined( __unix__ )  || defined (_WIN32 )
template<class T>
inline bool
KFPBMessageSEM<T>::SerializeFromString(const string dta )
{
    return SerializeFromString( (const uint8_t * const)dta.c_str(), dta.size() );
}
#endif


#endif
