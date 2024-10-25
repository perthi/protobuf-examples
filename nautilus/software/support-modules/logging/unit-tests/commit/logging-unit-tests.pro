
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


TARGET=logging-unit-tests

DESTDIR = ../../../build/x86/bin


INCLUDEPATH+=${FERROTECH_HOME}/software/include
INCLUDEPATH+= -isystem ${FERROTECH_HOME}/software
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -llogmaster -ltestlib  -lutilities -lcmdline -lgtest  -lpthread -lboost_system -lboost_filesystem

SOURCES += \
logging-unit-tests.cpp \
TestCheckLevel.cpp \
TestLConfig.cpp \
TestLConversion.cpp \
TestLFormat.cpp \
TestLHashMaps.cpp \
TestLogging.cpp \
TestLTargets.cpp \
TestSubscriber.cpp


HEADERS += \
logging-unit-tests.h \
TestCheckLevel.h \
TestLConfig.h \
TestLConversion.h \
TestLFormat.h \
TestLHashMaps.h \
TestLogging.h \
TestLTargets.h \
TestSubscriber.h
