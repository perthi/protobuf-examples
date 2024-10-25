TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = xml-example1 

SOURCES += \
xml-example1.cpp


HEADERS += \
xml-example1.cpp      


DESTDIR = ../../../../build/x86/bin


INCLUDEPATH+=${FERROTECH_HOME}/software/include
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -llogmaster  -lcmdline  -lcontrol-engine -lutilities -lxml -lxml2 -lboost_system -lboost_filesystem
