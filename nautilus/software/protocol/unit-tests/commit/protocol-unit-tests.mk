

PROGRAM=protocol-unit-tests



SRCCPP:=protocol-unit-tests.cpp \
	TestKFPBMessageSEMCommand.cpp \
	TestKFPBMessageSEMMessage.cpp \
	TestKFPBMessageSEMMsgCommonT.cpp \
	TestKFPBMessageSerializeT.cpp \
	TestKFPBSubMessageSEMDeviceAddress.cpp \
	TestKFPBSubMessageSEMStepUnitConversion.cpp \
	TestKFPBSubMessageSEMLinearUnitConversion.cpp \
	TestKFPBSubMessageSEMThresholds.cpp \
	TestKFPBSubMessageSEMConfigStepperMotor.cpp \
	TestKFPBSubMessageSEMConfigSEM.cpp \
	TestKFPBMessageSEMConfig.cpp \
	TestKFPBSubMessageSEMConfigVirtualXYMotors.cpp \
	TestKFPBSubMessageSEMConfigSolenoid.cpp \
	TestKFPBSubMessageSEMConfigPWM.cpp \
	TestKFPBSubMessageSEMConfigSensorAnalog.cpp \
	TestKFPBSubMessageSEMCrc.cpp \
	TestKFPBSubMessageSEMConfigSensorBool.cpp \
	TestKFPBSubMessageSEMMessageMotor.cpp \
	TestKFPBSubMessageSEMMessageSensor.cpp \
	TestKFPBSubMessageSEMMessageSensorBool.cpp \
	TestKFPBSubMessageSEMMessageSolenoid.cpp \
	TestKFPBSubMessageSEMMessageStatus.cpp \
	TestKFPBSubMessageSEMMessageXYMotor.cpp \
	TestKFPBSubMessageSEMMessageCommandStatusReply.cpp \
	TestKFPBSubMessageSEMMessageConfigurationStatusReply.cpp \
	TestKFProtocolWrapper.cpp


include ../../../../common.mk
include ../../../../unittest-common.mk


LIBS+=  -ltestlib -llogmaster  -lcmdline -lprotocol   -lconfiguration -lxml-embc -lxml2 -lcommon
#LIBS+=  -ltestlib -llogmaster  -lcmdline -lprotocol  -lxml-embc -lxml2 


LIBS+= $(PROTOBUF_LIBS)
INCLUDES+=$(PROTOBUF_INCLUDES)

INCLUDES+=$(GTEST_INCLUDES)

