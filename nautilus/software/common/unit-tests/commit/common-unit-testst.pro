
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


TARGET=common-unit-tests
DESTDIR = ../../../build/x86/bin


INCLUDEPATH+=${FERROTECH_HOME}/software/include
INCLUDEPATH+= -isystem ${FERROTECH_HOME}/software
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -llogmaster -ltestlib  -lutilities -lcmdline -lcommon-core -lxml -lxml2 -lgtest  -lpthread -lboost_system -lboost_filesystem

SOURCES += \
common-dll-test.cpp \
TestFSMNode.cpp \
TestFSMNode_Main.cpp \
TestFSMState.cpp \
TestFSM_StateInfo.cpp \
TestGEnum.cpp \
TestMBMessage.cpp \
TestFSMController.cpp \
TestFSMNode_Debug.cpp \
TestFSMNode_V.cpp \
TestFSM_StateFactory_V.cpp \
TestGComponentID.cpp \
TestGComponent.cpp \
TestMBPostOffice.cpp



HEADERS += \
common-dll-test.h \
TestFSMController.h \
TestFSMNode.h \
TestFSMNode_V.h \
TestFSMState.h \
TestGComponentID.h \
TestGComponent.h \
TestMBPostOffice.h \
TestFSMNode_Debug.h \
TestFSMNode_Main.h \
TestFSM_StateFactory_V.h \
TestFSM_StateInfo.h \
TestGEnum.h \
TestMBMessage.h

