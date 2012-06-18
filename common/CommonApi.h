#if defined (WIN32) && defined (BUILD_SHARED_LIBS)
  #if defined(libcommon_EXPORTS)
    #define  DLL_SPEC __declspec(dllexport)
  #else
    #define  DLL_SPEC __declspec(dllimport)
  #endif
#else
 #define DLL_SPEC
#endif