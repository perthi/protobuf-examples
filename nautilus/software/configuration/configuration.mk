

LIBNAME_SO=libconfiguration.so



SRCCPP:= KFCard.cpp \
	KFConfig.cpp \
	KFConfigMotor.cpp \
	KFConfigCamera.cpp \
	KFConfigurationHandlerCamera.cpp \
	KFHMICaption.cpp \
	KFHMIControl.cpp \
	KFHMIControlGroup.cpp \
	KFHMIIndicator.cpp \
	KFHMIStepNavigator.cpp \
	KFEntity.cpp \
	KFEntityCamera.cpp \
	KFEntityDevice.cpp \
	KFEntityDeviceMotorStepper.cpp \
	KFEntityDeviceMotorXY.cpp \
	KFEntityDeviceSensor.cpp \
	KFEntityDeviceSensorAnalogDirect.cpp \
	KFEntityDeviceSensorBoolDirect.cpp \
	KFEntityDeviceSolenoid.cpp \
	KFEntityDevicePWM.cpp \
	KFEntityDevicePWMSignal.cpp \
	KFEntityDevicePWMPower.cpp \
	KFEntityHMI.cpp \
	KFEntityHMICRing.cpp \
	KFEntityHMIOperation.cpp \
	KFEntityHMIHabitat.cpp \
	KFInfoCamera.cpp \
	KFDeviceAddress.cpp \
	KFFactorySensor.cpp \
	KFPositionCamera.cpp \
	KFXMLParserCamera.cpp \
	KFXMLParserHMI.cpp \
	KFXMLParserDevices.cpp \
	KFXMLWriter.cpp \
	KFXMLParser.cpp \
	KFXMLWriterCamera.cpp \
	KFSensorUnitConversion.cpp \
	KFSensorThresholds.cpp \
	KFSensor.cpp \
	KFConfigurationHandler.cpp \
	KFConfigUtilities.cpp

include ../../common.mk


ifneq (arm, $(TARGET))
LIBS+= -lX11
endif

INCLUDES+=$(PROTOBUF_INCLUDES)


CPPFLAGS_TMP:=$(CPPFLAGS)
CPPFLAGS= $(filter-out -Weffc++, $(CPPFLAGS_TMP) )
