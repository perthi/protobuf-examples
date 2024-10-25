
PROGRAM:= version-info
#LIBNAME_SO:= libversion-info.so

SRCCPP+=	version-info.cpp \
		GGenerateVersionInfo.cpp

#GMenu.cpp 




# LIBS+= -lexception  -llogmaster -lutilities  -llogmaster  -lboost_system  -lexception -lutilities -lcmdline -lboost_filesystem  -lpthread

LIBS+= -lboost_system  -lboost_filesystem  -lpthread  

include ../../common.mk
