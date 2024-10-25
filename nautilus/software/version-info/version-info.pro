TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
version-info.cpp \
GGenerateRCFile.cpp \
GGenerateVersionInfo.cpp \
GMenu.cpp

HEADERS += \
version-info.h \
GGenerateRCFile.h \
GGenerateVersionInfo.h \
GMenu.h \
GVersion.h



DESTDIR=../build/x86/bin
INCLUDEPATH+=${FERROTECH_HOME}/software/include


#LIBS += -L${FERROTECH_HOME}/modules/build/x86/lib
LIBS+=  -lboost_system -lboost_filesystem


