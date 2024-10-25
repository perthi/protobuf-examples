TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
kf-main.cpp

HEADERS += \
kf-main.h

        
DESTDIR=../../build/x86/bin
INCLUDEPATH+=${FERROTECH_HOME}/modules/include


LIBS += -L${FERROTECH_HOME}/modules/build/x86/lib
LIBS+=  -lkf-main -lapi-fsm -lcmdline -llogmaster -lcommon-core -lutilities -lxml -lxml2 -lboost_system -lboost_filesystem


