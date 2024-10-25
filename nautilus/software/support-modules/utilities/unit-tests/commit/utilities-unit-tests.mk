

PROGRAM:=utilities-unit-tests


SRCCPP += utilities-dll-test.cpp \
	TestGMath.cpp \
	TestGRandom.cpp \
	TestGString.cpp \
	TestGText.cpp \
	TestGTokenizer.cpp \
	TestGFileIOHandler.cpp \
	TestGRegexp.cpp \
	TestGSystem.cpp \
	TestGTime.cpp \
	TestGUtilities.cpp \
	TestGNumbers.cpp \
	TestException.cpp \
	TestDataTypesT.cpp \
	TestGEnum.cpp \
	TestGCrc.cpp \
	GVersion.cpp


#TestGEnum.cpp 

include ../../../../../common.mk
include ../../../../../unittest-common.mk

LIBS+= -llogmaster -lcmdline -lreadline
INCLUDES+=$(GTEST_INCLUDES)
