

PROGRAM:= cmdline-unit-tests



SRCCPP+= cmdline-dll-test.cpp \
	TestGCommandLineArgument.cpp \
	TestGLogApplication.cpp \
	TestGCmdScan.cpp \
	GVersion.cpp 

include ../../../../../common.mk
include ../../../../../unittest-common.mk

LIBS+= -llogmaster -lcmdline
INCLUDES+=$(GTEST_INCLUDES)
