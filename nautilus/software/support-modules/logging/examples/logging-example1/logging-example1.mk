
PROGRAM:=logging-example1

SRCCPP+=../logging-example1.cpp \
	../GVersion.cpp


LIBS+= -llogmaster  -lutilities  -lcmdline  -lutilities -llogmaster -lreadline -lboost_system -lboost_filesystem  -lpthread  


include ../../../../../common.mk

