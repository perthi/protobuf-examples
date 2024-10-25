

LIBNAME_SO:= libcommon.so
#LIBNAME_A:= libcommon.a


SRCCPP+= FSMNode.cpp \
	FSMAction.cpp \
	FSMState.cpp \
	FSM_StateInfo.cpp \
	FSM_Definitions.cpp \
	FSM_StateFactory.cpp \
	FSM_StateEvaluation.cpp \
	MBMessageInfo.cpp \
	MBMessageRequestUserInput.cpp \
	MBMessagePayloadT.cpp \
	MBMessage.cpp \
	MBMessageRequest.cpp \
	MBMessagePayload.cpp \
	MBMessageT.cpp \
	MBPostOffice.cpp \
	MBPostOfficeConfig.cpp \
	GComponent.cpp \
	GComponentTimer.cpp  \
	GComponentWireTap.cpp \
	GComponentDummyGuiResponse.cpp \
	GComponentDummyGuiRequest.cpp \
	GComponentDummyA.cpp \
	GComponentDummyB.cpp \
	GComponentDummyC.cpp \
	GIDGenerator.cpp \
	GlobalRegistry.cpp


CPPFLAGS=$(CPPFLAGS_RELAXED)


include ../../common.mk

