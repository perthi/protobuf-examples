
PROGRAM:=xml-unit-tests


SRCCPP += xml-dll-test.cpp \
	TestGXmlClassFactory.cpp \
	TestGXmlValidatorImpl.cpp \
	GVersion.cpp

include ../../../../../common.mk
include ../../../../../unittest-common.mk

LIBS+= -llogmaster -lutilities -lcmdline -lreadline -lxml-embc  -lxml2
INCLUDES+=$(GTEST_INCLUDES)
