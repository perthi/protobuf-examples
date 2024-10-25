


## ifneq (ARM, $(TARGET))
LIBNAME_SO:=libutilities.so
## endif

#LIBNAME_A:=libutilities.a


SRCCPP+=GCommon.cpp \
	GFileIOHandler.cpp \
	GDataTypes.cpp \
	GFileName_t.cpp \
	GLocation.cpp \
	GMath.cpp \
	GNumbers.cpp \
	GPrintable.cpp \
	GRandom.cpp \
	GRegexp.cpp \
	GString.cpp \
	GText.cpp \
	GSystem.cpp \
	GTime.cpp \
	GTokenizer.cpp \
	GUtilities.cpp \
	GStackTrace.cpp \
	GException.cpp \
	GEnumHelper.cpp \
	GEnumHelperImpl.cpp \
	GCrc.cpp


#LIBS+= -llogmaster  -lreadline -lboost_system  -lboost_filesystem
#LIBFLAGS= -shared -lm -L/home/ferrotech/nautilus/software/build/x86/lib  -llogmaster -lboost_system  -lboost_filesystem  -lreadline
#LIBFLAGS= $(LIBS) -static  -llogmaster -lreadline -lboost_system  -lboost_filesystem

#ifneq (arm, $(TARGET))
#LIBS+=  -lX11 -lboost_regex  -lboost_system  -lboost_filesystem -libutilities
#else
#LIBS+=  -lboost_system  -lboost_filesystem
#endif

# LIBS+= -lcmdline -ltestlib -lcmdline  -lboost_system  -lboost_filesystem
# LIBS+=  -lboost_system  -lboost_filesystem

