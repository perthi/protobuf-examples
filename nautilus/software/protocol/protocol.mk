

LIBNAME_SO=libprotocol.so
#LIBNAME_A=libprotocol.a


SRCCPP:=  kf.pb.cpp \
	pb_common.cpp \
	pb_decode.cpp \
	pb_encode.cpp \
	KFPBMessageSEM.cpp \
	KFPBMessageSEMMessageCommon.cpp \
	KFPBMessageSEMCommand.cpp \
	KFPBMessageSEMConfig.cpp \
	KFPBMessageSEMMessage.cpp \
	KFPBSubMessageSEMDeviceAddress.cpp \
	KFPBSubMessageSEMStepUnitConversion.cpp \
	KFPBSubMessageSEMLinearUnitConversion.cpp \
	KFPBSubMessageSEMThresholds.cpp \
	KFPBSubMessageSEMConfigStepperMotor.cpp \
	KFPBSubMessageSEMConfigSEM.cpp \
	KFPBSubMessageSEMConfigVirtualXYMotors.cpp \
	KFPBSubMessageSEMConfigSolenoid.cpp \
	KFPBSubMessageSEMConfigPWM.cpp \
	KFPBSubMessageSEMConfigSensorAnalog.cpp \
	KFPBSubMessageSEMCrc.cpp \
	KFPBSubMessageSEMConfigSensorBool.cpp \
	KFPBMessageSEMOneOfMessage.cpp \
	KFPBSubMessageSEMMessageCommandStatusReply.cpp \
	KFPBSubMessageSEMMessageMotor.cpp \
	KFPBSubMessageSEMMessageSensor.cpp \
	KFPBSubMessageSEMMessageStatus.cpp \
	KFPBSubMessageSEMMessageConfigurationStatusReply.cpp \
	KFPBSubMessageSEMMessageSensorBool.cpp \
	KFPBSubMessageSEMMessageSolenoid.cpp \
	KFPBSubMessageSEMMessageXYMotor.cpp \
	KFMessageHandler.cpp \
	KFProtocolUtilities.cpp \
	KFProtocolWrapper.cpp


## KFPBMessageSEMConfig.cpp \


include ../../common.mk

LIBS+=  -lcom -llogmaster  -lboost_filesystem -lm
LIBS+=$(PROTOBUF_LIBS)
INCLUDES+=  $(PROTOBUF_INCLUDES)


CPPFLAGS+= -Wswitch-enum 
CPPFLAGS:=$(CPPFLAGS_RELAXED) 
