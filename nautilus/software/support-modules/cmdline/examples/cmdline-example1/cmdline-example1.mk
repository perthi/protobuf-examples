
PROGRAM:=cmdline-example1



SRCCPP+=../cmdline-example1.cpp \
		../GVersion.cpp


LIBS+= -llogmaster  -lutilities  -lcmdline  -lutilities -lreadline -llogmaster -lboost_system -lboost_filesystem  -lpthread  

include ../../../../../common.mk
