

PROGRAM=kf-main-unit-tests

SRCCPP:=kf-main-dll-test.cpp \
		TesKFMain.cpp



include ../../../../common.mk
include ../../../../unittest-common.mk


LIBS+= -llogmaster -lcmdline

INCLUDES+=$(GTEST_INCLUDES)
