

##ifneq (ARM, $(TARGET))
## LIBNAME_SO:=libtestlib.so
##endif

#LIBNAME_A:=libtestlib.a
LIBNAME_SO:=libtestlib.so

SRCCPP+=TestBase.cpp
LIBS+= -lcmdline -lboost_system -llogmaster

INCLUDES+=$(GTEST_INCLUDES)

export CPPFLAGS:=$(CPPFLAGS_RELAXED)

include ../../../common.mk
