// definitions
#ifdef HAVE_CONFIG_H
#  include "config.h"
#else
#define MUTWIN
//#define MUTMIDI
#endif

#ifdef WX
  #include "mhDefs.h"
#endif

#if defined(MUTWIN) && (!defined(WX) || defined(__WXMSW__))
  #include <windows.h>
#endif

#ifdef WX
#include "wx/setup.h"
#if !defined(__WXMSW__)
  #define UINT unsigned int
  #define WORD unsigned int
  #define DWORD unsigned long
  #define BYTE unsigned char
  #define BOOL bool
  #define pascal
  #define CALLBACK 
#endif
  #define _export
#if defined(__VISUALC__)
  #define min(a, b) wxMin(a, b)
#endif
#else // not WX
  #define REUSE(type) type
#endif 

#if defined(WX)
  #define STD_PRE std
#else
  #define STD_PRE
#endif


