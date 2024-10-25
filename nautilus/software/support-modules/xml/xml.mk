


## ifneq (ARM, $(TARGET))
LIBNAME_SO:=libxml-embc.so	
## endif	

#LIBNAME_A:=libxml-embc.a


SRCCPP+= GXmlAttribute.cpp \
	GXmlClassFactory.cpp \
	GXmlDocTypeNode.cpp \
	GXmlProcInstructNode.cpp \
	GXmlStreamReaderSp.cpp \
	GXmlTagNode.cpp \
	GXmlValidator.cpp \
	GXmlCDataNode.cpp \
	GXmlCommentNode.cpp \
	GXmlNodeImpl.cpp \
	GXmlStreamReaderImpl.cpp \
	GXmlStreamWriterImpl.cpp \
	GXmlTextNode.cpp \
	GXmlValidatorImpl.cpp 


CPPFLAGS:=$(CPPFLAGS_RELAXED)

INCLUDES+=$(XML_INCLUDES)
