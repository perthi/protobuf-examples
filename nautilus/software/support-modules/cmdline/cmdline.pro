#-------------------------------------------------
#
# Project created by QtCreator 2019-06-28T19:05:42
#
#-------------------------------------------------

QT       -= core gui

TARGET = cmdline
TEMPLATE = lib

DEFINES += SRC_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../../build/x86/lib


INCLUDEPATH+=${FERROTECH_HOME}/software/include


SOURCES += \
GArgument.cpp \
GArgumentParsed.cpp \
GCmdApi.cpp \
GCmdScan.cpp \
GCommandLineArgument.cpp \
GLogApplication.cpp



HEADERS += \
GArgument.h \
GArgumentParsed.h \
GCmdApi.h \
GCmdScan.h \
GCommandLineArgument.h \
GLogApplication.h \
GParameterInfo.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}
