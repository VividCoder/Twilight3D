// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the VIVIDBIND_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// VIVIDBIND_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VIVIDBIND_EXPORTS
#define VIVIDBIND_API __declspec(dllexport)
#else
#define VIVIDBIND_API __declspec(dllimport)
#endif

// This class is exported from the dll
class VIVIDBIND_API CVividBind {
public:
	CVividBind(void);
	// TODO: add your methods here.
};

extern VIVIDBIND_API int nVividBind;

VIVIDBIND_API int fnVividBind(void);
