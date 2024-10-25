// -*- mode: c++ -*-
#ifndef KFXMLFILE_H
#define KFXMLFILE_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include <string>
using std::string;



class  KFXMLFiles
{
public:
    inline  KFXMLFiles( const string devices, const string hmi  = "" ) : fDevices(devices), fHmi(hmi)   { };
    inline  virtual ~KFXMLFiles() {};

    string fDevices = "";
    string fHmi = "";
};

#endif
