

PROGRAM=common-unit-tests

 SRCCPP:= common-dll-test.cpp \
	TestFSMNode.cpp \
	TestFSMNode_Main.cpp \
	TestFSMState.cpp \
	TestFSM_StateInfo.cpp \
	TestGEnum.cpp \
	TestMBPostOffice.cpp \
	TestFSMController.cpp \
	TestFSMNode_Debug.cpp \
	TestFSMNode_V.cpp \
	TestFSM_StateFactory_V.cpp \
	TestGComponentID.cpp \
	TestGComponent.cpp \
	TestMBMessage.cpp \
	GVersion.cpp



include ../../../../common.mk
include ../../../../unittest-common.mk

LIBS+= -lcommon -lxml-embc -lxml2 -llogmaster -lutilities  -lcmdline

INCLUDES+=$(GTEST_INCLUDES)
