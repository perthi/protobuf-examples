
PROGRAM:=xml-example1


SRCCPP:=xml-example1.cpp \
	GVersion.cpp


LIBS+= -lcmdline   -llogmaster  -lcontrol-engine -lconfiguration -lxml-embc   -lxml2 -lutilities -lreadline -lcommon -lboost_system -lboost_filesystem 
CPPFLAGS:=$(CPPFLAGS_RELAXED)
INCLUDES+=$(XML_INCLUDES)
INCLUDES+=$(PROTOBUF_INCLUDES)

include ../../../../../common.mk

