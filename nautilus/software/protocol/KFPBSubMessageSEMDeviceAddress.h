// -*- mode: c++ -*-
#ifndef KFPBSubMessageSEMDeviceAddress_H
#define KFPBSubMessageSEMDeviceAddress_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include    "KFPBMessageSEM.h"

struct KFDeviceAddress;


class  KFPBSubMessageSEMDeviceAddress : public    KFPBMessageSEM<  SEMDeviceAddress >  
{
	public:
		API KFPBSubMessageSEMDeviceAddress();
		virtual API  ~KFPBSubMessageSEMDeviceAddress();

#if defined( __unix__ )  || defined (_WIN32 )
	    int     API   SetDeviceID(const string id );
		void    API   SetDeviceName(const string name);
#endif
  		inline virtual int     SetDeviceID(const char *id, const size_t max_size );
		inline virtual int     SetDeviceName(const char *id, const size_t max_size );

		void    API   SetDeviceType(  eDEVICE_TYPE type);
		void    API   SetDevicePortNo(const int device_no);
		void    API   SetCardID(const int id);
		
#if defined( __unix__ )  || defined (_WIN32 )
		string  API   GetDeviceID() const;
		string  API   GetDeviceName();
#endif
 		inline virtual int     GetDeviceID(char *id, const size_t max_size ) const;
		inline virtual int     GetDeviceName(char *id, const size_t max_size ) const;

	 	eDEVICE_TYPE      API    GetDeviceType() const;
		int     API   GetDevicePortNo() const;
	    int     API   GetCardID() const;
		virtual void    API   Reset(SEMDeviceAddress *t)  override;
		virtual void    API   Reset(  )  override;

#if defined( __unix__ )  || defined (_WIN32 )
		void    API   SetConfiguration(const KFDeviceAddress* const address, eDEVICE_TYPE type);
		virtual string  API   str() const override;
#endif
};

#endif
