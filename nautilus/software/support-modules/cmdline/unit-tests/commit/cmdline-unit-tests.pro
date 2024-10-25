TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET=cmdline-unit-tests

SOURCES += \
cmdline-dll-test.cpp \
TestGCmdScan.cpp \
TestGCommandLineArgument.cpp \
TestGLogApplication.cpp

HEADERS += \
TestGCmdScan.h \
TestGCommandLineArgument.h \
TestGLogApplication.h


DESTDIR = ../../../../build/x86/bin




INCLUDEPATH+=${FERROTECH_HOME}/software/include
INCLUDEPATH+= -isystem ${FERROTECH_HOME}/software
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -llogmaster -ltestlib  -lutilities -lcmdline -lgtest  -lpthread -lboost_system -lboost_filesystem
