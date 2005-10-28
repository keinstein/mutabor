#ifndef mhDEFS_H
#define mhDEFS_H

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

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


#if defined(_UNICODE)
#define SSCANF swscanf
#else		
#define SSCANF sscanf
#endif

#if defined(WX) && defined(_UNICODE)
  #include <wx/strconv.h>
  extern wxCSConv muCSConv;
  #define muT(x)  (wxString(x, muCSConv))
#else
  #define muT(x) x
#endif

#endif
