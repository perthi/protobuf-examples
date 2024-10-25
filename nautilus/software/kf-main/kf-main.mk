

LIBNAME_SO=libkf-main.so
#LIBNAME_A=libkf-main.a


SRCCPP:= KFMain.cpp \
	KFGlobals.cpp


CPPFLAGS:=$(CPPFLAGS_RELAXED)

include ../../common.mk


