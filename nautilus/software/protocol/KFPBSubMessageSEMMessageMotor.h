// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMMESSAGEMOTOR_H
#define KFPBSUBMESSAGESEMMESSAGEMOTOR_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include    "KFPBMessageSEMMessageCommon.h"
#include   "KFProtocolEnums.h"


class  KFPBSubMessageSEMMessageMotor : 
public KFPBMessageSEMMessageCommon <SEMMessageMotor, eSEM_MOTOR_ERROR_CODE, eSEM_MOTOR_STATE>
{
public:
    KFPBSubMessageSEMMessageMotor();
    virtual ~KFPBSubMessageSEMMessageMotor();
    void SetSpeed(const float speed);
    void SetPosition( const float position );
    void SetEndStopReached( const bool val);
    void SetHomePositionReached( const bool val);
    float GetSpeed() const;
    float GetPosition() const;
    bool  IsEndStopReached() const;
    bool  IsHomePositionReached() const;
    bool  HasEndStopReached() const;
    bool  HasHomePositionReached() const;
    bool  HasValueSpeed() const;

    virtual  void   API   Reset(  ) override;
    virtual  void   API   Reset( SEMMessageMotor *t) override;
#if defined( __unix__ )  || defined (_WIN32 )
    virtual string         str() const override;
    virtual string strOneLine() const override;

#endif

};

#endif
