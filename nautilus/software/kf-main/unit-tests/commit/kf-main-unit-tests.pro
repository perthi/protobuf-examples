
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


TARGET=kf-main-unit-tests
DESTDIR = ../../../build/x86/bin



INCLUDEPATH+=${FERROTECH_HOME}/software/include
INCLUDEPATH+= -isystem ${FERROTECH_HOME}/software
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -ltestlib  -lutilities -lcmdline -llogmaster -lgtest -lkf-main -lapi-fsm -lcommon-core -lxml -lxml2 -lpthread -lboost_system -lboost_filesystem


SOURCES += \
kf-main-dll-test.cpp \
TestKFMain.cpp



HEADERS += \
kf-main-dll-test.h
TestKFMain.cpp

