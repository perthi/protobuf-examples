// -*- mode: c++ -*-
#ifndef KFPBMESSAGESEMMESSAGE_H
#define KFPBMESSAGESEMMESSAGE_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "KFPBMessageSEM.h"


#include "KFPBSubMessageSEMMessageStatus.h"
#include "KFPBSubMessageSEMMessageSensor.h"
#include "KFPBSubMessageSEMMessageSensorBool.h"
#include "KFPBSubMessageSEMMessageMotor.h"
#include "KFPBSubMessageSEMMessageSolenoid.h"
#include "KFPBSubMessageSEMMessageXYMotor.h"
#include "KFPBSubMessageSEMMessageConfigurationStatusReply.h"
#include "KFPBSubMessageSEMMessageCommandStatusReply.h"



class  KFPBMessageSEMMessage : public KFPBMessageSEM< SEMMessage  >
{
    public:
        API KFPBMessageSEMMessage();
        virtual API ~KFPBMessageSEMMessage();
        void SetMessageType(  const  ePB_MESSAGE_ONEOF_TYPE  cmd  );
      ///  void SetSequenceID( int32_t id);
        ePB_MESSAGE_ONEOF_TYPE   GetMessageType() const;
     ///   int32_t  GetSequenceID() const;

        KFPBSubMessageSEMMessageStatus *       GetMessageStatus();
        KFPBSubMessageSEMMessageSensor *       GetMessageSensor();
        KFPBSubMessageSEMMessageSensorBool *   GetMessageSensorBool();
        KFPBSubMessageSEMMessageMotor *        GetMessageMotor();
        KFPBSubMessageSEMMessageSolenoid *     GetMessageSolenoid();
        KFPBSubMessageSEMMessageXYMotor *      GetMMessageXYMotor();
        KFPBSubMessageSEMMessageConfigurationStatusReply * GetMessageConfigurationStatusReply();
        KFPBSubMessageSEMMessageCommandStatusReply * GetMessageCommandStatusReply();

         #if defined( __unix__ )  || defined (_WIN32 )
        virtual string  GetDeviceID() const;
        virtual int     SetDeviceID(const string id );
       #endif
        virtual int     GetDeviceID(char *id, const size_t max_size ) const;
        virtual int     SetDeviceID(const char *id, const size_t max_size );
        virtual void  API    Reset(SEMMessage *t) override;
        virtual void  API    Reset () override;
        #if defined( __unix__ )  || defined (_WIN32 )
        virtual string      str() const override;
        virtual string strOneLine() const override;

        #endif

    private:
        KFPBSubMessageSEMMessageStatus                   fSEMMessageStatus;
        KFPBSubMessageSEMMessageSensor                   fSEMMessageSensor;
        KFPBSubMessageSEMMessageSensorBool               fSEMMessageSensorBool;
        KFPBSubMessageSEMMessageMotor                    fSEMMessageMotor;
        KFPBSubMessageSEMMessageSolenoid                 fSEMMessageSolenoid;
        KFPBSubMessageSEMMessageXYMotor                  fSEMMessageXYMotor;
        KFPBSubMessageSEMMessageConfigurationStatusReply fSEMMessageConfigurationStatusReply;
        KFPBSubMessageSEMMessageCommandStatusReply       fSEMMessageCommandStatusReply;
};

#endif

