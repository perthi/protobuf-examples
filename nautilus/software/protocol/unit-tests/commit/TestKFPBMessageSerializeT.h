// -*- mode: c++ -*-
#ifndef  TESTKFPBMESSAGESERIALIZET_H
#define  TESTKFPBMESSAGESERIALIZET_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include <testlib/TestBase.h>
#include <typeinfo>
#include <protocol/KFPBMessageSEMCommand.h>
#include <protocol/KFPBMessageSEMMessage.h>
#include <protocol/KFPBSubMessageSEMDeviceAddress.h>
#include <protocol/KFPBSubMessageSEMStepUnitConversion.h>
#include <protocol/KFPBSubMessageSEMLinearUnitConversion.h>
#include <protocol/KFPBSubMessageSEMThresholds.h>
#include <protocol/KFPBSubMessageSEMConfigStepperMotor.h>
#include <protocol/KFPBMessageSEMConfig.h>
#include <protocol/KFPBSubMessageSEMConfigSEM.h>
#include <protocol/KFPBSubMessageSEMConfigVirtualXYMotors.h>
#include <protocol/KFPBSubMessageSEMConfigSolenoid.h>
#include <protocol/KFPBSubMessageSEMConfigPWM.h>
#include <protocol/KFPBSubMessageSEMConfigSensorAnalog.h>
#include <protocol/KFPBSubMessageSEMCrc.h>
#include <protocol/KFPBSubMessageSEMConfigSensorBool.h>
#include <protocol/KFPBMessageSEMOneOfMessage.h>
#include <protocol/KFPBSubMessageSEMMessageMotor.h>
#include <protocol/KFPBMessageSEMMessage.h>
#include <protocol/KFPBSubMessageSEMMessageMotor.h> 
#include <protocol/KFPBSubMessageSEMMessageSensor.h> 
#include <protocol/KFPBSubMessageSEMMessageSensorBool.h> 
#include <protocol/KFPBSubMessageSEMMessageSolenoid.h>
#include <protocol/KFPBSubMessageSEMMessageStatus.h>
#include <protocol/KFPBSubMessageSEMMessageXYMotor.h>
#include <protocol/KFPBSubMessageSEMMessageCommandStatusReply.h>
#include <protocol/KFPBSubMessageSEMMessageConfigurationStatusReply.h>
#include <memory>



template <typename T>
class  TestKFPBMessageSerializeT : public TestBase
{
public:
    TestKFPBMessageSerializeT() {};
    virtual ~TestKFPBMessageSerializeT() {};

protected:
    std::shared_ptr<T> m1 = std::make_shared<T>();
    std::shared_ptr<T> m2 = std::make_shared<T>();
};


#if GTEST_HAS_TYPED_TEST
using testing::Types;
typedef Types<  KFPBMessageSEMCommand, 
                KFPBMessageSEMMessage, 
                KFPBSubMessageSEMDeviceAddress, 
                KFPBSubMessageSEMStepUnitConversion, 
                KFPBSubMessageSEMLinearUnitConversion, 
                KFPBSubMessageSEMThresholds,  
                KFPBSubMessageSEMConfigStepperMotor,
                KFPBMessageSEMConfig,
            //    KFPBSubMessageSEMConfigSEM,
                KFPBSubMessageSEMConfigVirtualXYMotors,
                KFPBSubMessageSEMConfigSolenoid,
                KFPBSubMessageSEMConfigPWM,
                KFPBSubMessageSEMConfigSensorAnalog,
                KFPBSubMessageSEMCrc,
                KFPBSubMessageSEMConfigSensorBool,
                KFPBMessageSEMOneOfMessage,
                KFPBMessageSEMMessage,
                KFPBSubMessageSEMMessageMotor, 
                KFPBSubMessageSEMMessageSensor, 
                KFPBSubMessageSEMMessageSensorBool, 
                KFPBSubMessageSEMMessageSolenoid,
                KFPBSubMessageSEMMessageStatus, 
                KFPBSubMessageSEMMessageXYMotor,
                KFPBSubMessageSEMMessageCommandStatusReply,
                 KFPBSubMessageSEMMessageConfigurationStatusReply
                > msg_classes;


//KFPBSubMessageSEMMessageMotor

TYPED_TEST_CASE_P ( TestKFPBMessageSerializeT  );




TYPED_TEST_P(TestKFPBMessageSerializeT, serialize  )
{
    string tmp = "";
    EXPECT_TRUE( this->m1->SerializeToString(tmp) );
    EXPECT_TRUE( this->m2->SerializeFromString( tmp) );


    uint8_t buffer[1024] = {0};
    int n = 0;
    
    EXPECT_TRUE( this->m1->SerializeToString(buffer, sizeof(buffer), &n )) ;
    EXPECT_TRUE( this->m2->SerializeFromString( buffer, sizeof(buffer)));

    string tmp2 = "";

    for(int i=0; i < n; i ++)
    {
        tmp2.push_back(buffer[i]);
    }

    EXPECT_EQ(tmp, tmp2);

}



REGISTER_TYPED_TEST_CASE_P( TestKFPBMessageSerializeT, serialize );
INSTANTIATE_TYPED_TEST_CASE_P(common_functions, TestKFPBMessageSerializeT , msg_classes );


#endif



#endif
