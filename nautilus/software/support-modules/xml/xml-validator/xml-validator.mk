

PROGRAM:=xml-validator

SRCCPP+=../xml-validator.cpp \
	GVersion.cpp \
	GVersionMenu.cpp


LIBS+= -lxml-embc  -lxml2 -llogmaster -lutilities -lcmdline  -lboost_system  -lboost_filesystem  -lreadline


