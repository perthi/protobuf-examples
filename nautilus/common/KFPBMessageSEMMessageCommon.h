// -*- mode: c++ -*-
#ifndef KFPBMESSAGESEMMESSAGECOMMON_H
#define KFPBMESSAGESEMMESSAGECOMMON_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBMessageSEM.h"

template<class T1, class T2, class T3 = void >
class  KFPBMessageSEMMessageCommon : public KFPBMessageSEM<T1>
{
	public:
		inline KFPBMessageSEMMessageCommon(  pb_field_t  *  f  );
		inline virtual ~KFPBMessageSEMMessageCommon();
        inline bool  HasErrorString() const;


        template< typename U = T3>
        typename std::enable_if<  std::is_enum<U>::value, void>::type  SetState( U state )
        {
            this->fCmd->state = (int)state;
        }

        template<typename U = T3>
        typename std::enable_if< std::is_enum<U>::value, U>::type  GetState(   ) const
        {
           return  (T3)this->fCmd->state; 
        } 



        void SetErrorCode( const T2 code );
		T2 GetErrorCode() const;
		bool  HasErrorCode() const;
	
    #if defined( __unix__ )  || defined (_WIN32 )
		inline virtual string  GetErrorString() const;
    	inline virtual void    SetErrorString(const string id );
  	#endif
    	inline virtual void    GetErrorString(char *id, const size_t max_size ) const;
    	inline virtual void    SetErrorString(const char *id, const size_t max_size );

	#if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override  = 0;
    #endif
};





template<class T1, class T2, class T3>
inline 
KFPBMessageSEMMessageCommon<T1, T2, T3>::KFPBMessageSEMMessageCommon( pb_field_t  *  f ) : KFPBMessageSEM<T1>(f)
{

}


template<class T1, class T2, class T3>
inline 
KFPBMessageSEMMessageCommon<T1, T2, T3>::~KFPBMessageSEMMessageCommon()
{

}





template<class T1, class T2, class T3>
void
KFPBMessageSEMMessageCommon<T1, T2, T3>::SetErrorCode( T2 code )
{
    this->fCmd->error_code = (int)code;
    this->fCmd->has_error_code = true;
}


template<class T1, class T2, class T3>
T2
KFPBMessageSEMMessageCommon<T1, T2, T3>::GetErrorCode() const
{
    return  (T2)this->fCmd->error_code;
}


template<class T1, class T2, class T3>
bool
KFPBMessageSEMMessageCommon<T1, T2, T3>::HasErrorCode() const
{
    return this->fCmd->has_error_code;
}



template<class T1, class T2, class T3>
inline bool
KFPBMessageSEMMessageCommon<T1, T2, T3>::HasErrorString() const
{
    return this->fCmd->has_error_string;
}



#if defined( __unix__ )  || defined (_WIN32 )

template<class T1, class T2, class T3> 
inline string
KFPBMessageSEMMessageCommon<T1, T2, T3>::GetErrorString() const
{
    return string( this->fCmd->error_string);
}



template<class T1, class T2, class T3>
inline  void
KFPBMessageSEMMessageCommon<T1, T2, T3>::SetErrorString(const string id )
{
     KFPBMessageSEM<T1>::SetString(  this->fCmd->error_string, sizeof( this->fCmd->error_string), id.c_str() ); 
	 this->fCmd->has_error_string = true;
 }

#endif



template<class T1, class T2, class T3>
inline void
KFPBMessageSEMMessageCommon<T1, T2, T3>::GetErrorString(char *id, const size_t max_size ) const
{
 int n = max_size < sizeof( this->fCmd->error_string ) ? max_size : sizeof( this->fCmd->error_string);
    // errno_t strcpy_s(char *restrict dest, rsize_t destsz, const char *restrict src);
    strncpy( id, (const char *)this->fCmd->error_string, n );
}



template<class T1, class T2, class T3>
inline void
KFPBMessageSEMMessageCommon<T1, T2, T3>::SetErrorString(const char *id, const size_t max_size )
{
    auto n = max_size < sizeof( this->fCmd->error_string) ? max_size : sizeof(  this->fCmd->error_string);
    strncpy( this->fCmd->error_string, id, n );
    this->fCmd->has_error_string = true;
}



#if defined( __unix__ )  || defined (_WIN32 )
template<class T1, class T2, class T3>
string
KFPBMessageSEMMessageCommon<T1, T2, T3>::str() const
{
    std::stringstream buffer;

    buffer << g_utilities()->TabAlign("HAS_ERROR_CODE ?:") << ( HasErrorCode() == true ? "TRUE" : "FALSE") << endl;
    if( HasErrorCode() == true )
    {
         buffer << g_utilities()->TabAlign("ERROR_CODE:") << KFProtocolUtilities::Enum2String(GetErrorCode()) << endl;
    }

    buffer << g_utilities()->TabAlign("HAS_ERROR_STRING ?:") << ( HasErrorString() == true ? "TRUE" : "FALSE") << endl;
    if( HasErrorString() == true )
    {
        buffer << g_utilities()->TabAlign("ERROR_STRING:") <<  GetErrorString() << endl;
    }

    return buffer.str();
}

#endif


#endif