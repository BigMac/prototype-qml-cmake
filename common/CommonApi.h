#if defined (WIN32) && defined (_WINDLL)
	#if defined(libcommon_EXPORTS)
		#define  DLL_SPEC __declspec(dllexport)
	#else
		#define  DLL_SPEC __declspec(dllimport)
	#endif
#else
    #define DLL_SPEC
#endif