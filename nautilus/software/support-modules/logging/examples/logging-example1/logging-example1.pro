TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
logging-example1.cpp

HEADERS += \
logging-example1.h

        
DESTDIR=../../../../build/x86/bin

INCLUDEPATH+=${FERROTECH_HOME}/software/include
LIBS += -L${FERROTECH_HOME}/software/build/x86/lib

LIBS+=  -llogmaster  -lcmdline -lutilities -lboost_system -lboost_filesystem


