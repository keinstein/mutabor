#ifndef mhDEFS_H
#define mhDEFS_H

#ifdef __WXMSW__
  #define REUSE(type)
#else
  #define REUSE(type) type
#endif

#ifdef __WXMSW__			
	#define ICON(s)	wxIcon(_T(#s) _T("_icn"))
#else						
    #define ICON(s)	wxIcon( s##_xpm )		
#endif				


#endif
