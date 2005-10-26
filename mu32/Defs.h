// definitions

#define MUTWIN
//#define MUTMIDI

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
  #define min(a, b)	((a) < (b) ? (a) : (b))
#endif
  #include "mhDefs.h"
  #define _export
#else
  #define REUSE(type) type
#endif 
