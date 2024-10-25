// -*- mode: c++ -*-
#ifndef KFGLOBALS_H
#define KFGLOBALS_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include <string>
using std::string;

#include  <xml/GXmlDataTypes.h>
#include  <utilities/GDefinitions.h>

class  KFGlobals
{
	public:
		inline static KFGlobals * Instance(); 
		inline XSDFile_t   GetXSDFilenameDevices() const;
		inline XSDFile_t   GetXSDFilenameHmi() const;
		inline XSDFile_t   GetXSDFilenameCamera() const;

		inline void        SetXSDFilenameDevices( const XSDFile_t fname );
		
		inline void        SetXSDFilenameHmi( const XSDFile_t fname );
		inline void        SetXSDFilenameCamera( const XSDFile_t fname );
	
	
	private:
		inline KFGlobals();
		inline virtual ~KFGlobals();
		XSDFile_t  fDefaultDevicesXSD = XSDFile_t("kf_config.xsd");
		XSDFile_t  fDefaultHMIXSD = XSDFile_t("kf_hmi.xsd");
		XSDFile_t  fDefaultCameraXSD = XSDFile_t("camera_config.xsd");

};


inline
KFGlobals::KFGlobals()
{

}

inline
KFGlobals::~KFGlobals()
{
	// must never be called
}


inline KFGlobals * 
KFGlobals::Instance()
{ 
    static  KFGlobals *instance = new KFGlobals();
    return instance;
}


inline XSDFile_t   
KFGlobals::GetXSDFilenameDevices() const
{
    return  fDefaultDevicesXSD;
}


inline XSDFile_t  
KFGlobals::GetXSDFilenameHmi() const
{
    return  fDefaultHMIXSD;
}


inline XSDFile_t  
KFGlobals::GetXSDFilenameCamera() const
{
    return  fDefaultCameraXSD;
}

inline void   
KFGlobals::SetXSDFilenameDevices( const XSDFile_t fname )
{
     fDefaultDevicesXSD = fname;
}


inline void   
KFGlobals::SetXSDFilenameHmi( const XSDFile_t fname )
{
   fDefaultHMIXSD = fname;  
}


inline void   
KFGlobals::SetXSDFilenameCamera( const XSDFile_t fname )
{
   fDefaultCameraXSD = fname;  
}


#endif
