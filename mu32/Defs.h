// definitions

#define MUTWIN
//#define MUTMIDI

#ifdef WX
  #include "mhDefs.h"
#endif

#if defined(MUTWIN) && (!defined(WX) || defined(__WXMSW__))
  #include <windows.h>
#endif

#ifdef WX
#if !defined(__WXMSW__)
  #define UINT unsigned int
  #define WORD unsigned int
  #define DWORD unsigned long
  #define BYTE unsigned char
  #define BOOL bool
  #define pascal
  #define CALLBACK 
#endif
  #define min(a, b)	((a) < (b) ? (a) : (b))
  #define _export
#else // not WX
  #define REUSE(type) type
#endif 

#if defined(WX)
  #define STD_PRE std
#else
  #define STD_PRE
#endif

