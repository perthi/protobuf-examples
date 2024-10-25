// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGGINGDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGGINGDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOGGINGDLL_EXPORTS
#define LOGGINGDLL_API __declspec(dllexport)
#else
#define LOGGINGDLL_API __declspec(dllimport)
#endif

// This class is exported from the logging-dll.dll
class LOGGINGDLL_API Cloggingdll {
public:
	Cloggingdll(void);
	// TODO: add your methods here.
};

extern LOGGINGDLL_API int nloggingdll;

LOGGINGDLL_API int fnloggingdll(void);
