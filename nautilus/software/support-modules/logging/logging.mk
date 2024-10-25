

LIBNAME_SO=liblogmaster.so
#LIBNAME_A=liblogmaster.a


SRCCPP:= LColorMap.cpp \
	LConversion.cpp \
	LHashMaps.cpp \
	LLogging.cpp \
	LLogTest.cpp \
	LMessageFactory.cpp \
	LValidateArgs.cpp \
	LConfig.cpp \
	LDoc.cpp \
	LLogApi.cpp \
	LMessage.cpp \
	LMessageGenerator.cpp \
	LPublisher.cpp     

include ../../../common.mk

LIBS+= -lboost_filesystem -lm

ifneq (arm, $(TARGET))
LIBS+= -lX11
endif

