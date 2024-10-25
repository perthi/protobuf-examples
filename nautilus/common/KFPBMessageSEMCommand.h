// -*- mode: c++ -*-
/***********************************************************************************
 * This file is property of and copyright by Kongsberg Ferrotech  2019             *
 *                                                                                 *
 * Author: Per Thomas Hille <pth@embc.no> for Semcon Devotek & Konsgberg Ferrotech *
 * Contributors are mentioned in the code where appropriate.                       *
 * Please report bugs to pth@embc.no                                               *
 ***********************************************************************************/
#pragma once


/** forward declarations for unit testing */
class TestKFPBMessageSEMCommand_set_get_id_Test;
class TestKFPBMessageSEMCommand_set_get_id_invalid_Test;

#include "kf.pb.h"

#include "KFPBMessageSEM.h"


/** Protobuf message to be sent from PC to SEM*/
class  KFPBMessageSEMCommand : public KFPBMessageSEM< SEMCommand  >
{
    friend  TestKFPBMessageSEMCommand_set_get_id_Test;
    friend  TestKFPBMessageSEMCommand_set_get_id_invalid_Test;
    friend  int main(int argc, const char **argv);

public:
    API                 KFPBMessageSEMCommand();
    virtual API        ~KFPBMessageSEMCommand();
    virtual  float  API   GetValue();
    virtual  float  API   GetValueX();
    virtual  float  API   GetValueY();
    virtual  void   API   GetValueXY( float &x, float &y );
    eSEM_COMMAND_ID  API   GetCommandID() const;
    eSEM_COMMAND_PAYLOAD_TYPE          GetPayloadType() const;  
    void            SetPayloadType(const eSEM_COMMAND_PAYLOAD_TYPE type);

    virtual  void   API   Reset(  ) override;
    virtual  void   API   Reset( SEMCommand *t) override;
    virtual  int    API   SetPayload( const float val );
    virtual  int    API   SetPayload( const float x, const float y ); 
    void            API   SetCommandID(  const eSEM_COMMAND_ID cmd  );
 
#if defined( __unix__ )  || defined (_WIN32 )
    virtual string  GetDeviceID() const;
    virtual int     SetDeviceID(const string id );
#endif
    virtual int     GetDeviceID(char *id, const size_t max_size ) const;
    virtual int     SetDeviceID(const char *id, const size_t max_size );

#if defined( __unix__ )  || defined (_WIN32 )
    void            SetFields( const string device_id, const eSEM_COMMAND_ID cmd_type );
    void            SetFieldsFloat( const string device_id, const eSEM_COMMAND_ID cmd_type, const float val );
    void            SetFieldsXY( const string device_id, const eSEM_COMMAND_ID cmd_type, const float x, const float y );
#endif
    void            SetFields( const char *id, const size_t max_size,  const eSEM_COMMAND_ID cmd_type );
    void            SetFieldsFloat( const char *id,  const size_t max_size, const eSEM_COMMAND_ID cmd_type, const float val );
    void            SetFieldsXY( const char *id,  const size_t max_size, const eSEM_COMMAND_ID cmd_type, const float x, const float y );

    #if defined( __unix__ )  || defined (_WIN32 )
        virtual string         str() const override;
#endif

};

