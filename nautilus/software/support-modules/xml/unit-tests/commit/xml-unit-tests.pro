TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = xml-unit-tests



SOURCES += \
xml-dll-test.cpp \
TestGXmlClassFactory.cpp \
TestGXmlValidatorImpl.cpp


HEADERS += \
xml-dll-test.h \
TestGXmlClassFactory.h \
TestGXmlValidatorImpl.h


DESTDIR = ../../../../build/x86/bin


INCLUDEPATH+=${FERROTECH_HOME}/software/include
INCLUDEPATH+= -isystem ${FERROTECH_HOME}/software
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -llogmaster -ltestlib  -lutilities -lcmdline -lxml -lxml2  -lgtest  -lpthread -lboost_system -lboost_filesystem

file = xml-unit-tests.pro
