

PROGRAM:=configuration-unit-tests


SRCCPP += configuration-unittests.cpp \
	  TestKFConfigurationHandlerCamera.cpp \
	  TestKFXML.cpp \
	  TestKFXMLParserCamera.cpp \
	  TestKFXMLWriterCamera.cpp \
	  TestKFSensor.cpp \
	  TestKFFactorySensor.cpp \
	  TestKFXMLParserDevices.cpp \
	  TestKFConfigurationHandler.cpp \
	  TestKFConfigUtilities.cpp \
 	  TestKFXMLParserHMI.cpp 


include ../../../../common.mk
include ../../../../unittest-common.mk

LIBS+= -llogmaster  -lcontrol-engine -lcontrol-engine -lconfiguration  -lxml-embc  -lxml2 -lcommon -lutilities   -lcmdline
INCLUDES+=$(GTEST_INCLUDES)
INCLUDES+=$(PROTOBUF_INCLUDES)

