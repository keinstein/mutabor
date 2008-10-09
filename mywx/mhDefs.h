#ifndef mhDEFS_H
#define mhDEFS_H

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include <iostream>
#include <typeinfo>

#include "Mutabor.rh"

#ifndef HAVE_CONFIG_H
#  ifdef __WXMSW__
#    define REUSE(type)
#  else
#    define REUSE(type) type
#  endif
#endif

#ifdef __WXMSW__			
	#define ICON(s)	wxIcon(_T(#s) _T("_icn"))
#else						
    #define ICON(s)	wxIcon( s##_xpm )		
#endif				


#if defined(_UNICODE) || defined(UNICODE)
#define SSCANF swscanf
#else		
#define SSCANF sscanf
#endif

class wxHtmlHelpController;
extern wxHtmlHelpController * HelpController;

#ifdef WX
#if defined(WX) && defined(UNICODE)
  #include "wx/strconv.h"
  extern wxCSConv muCSConv;
  #define muT(x)  (wxString(x, muCSConv))
  #define mumT(x) _T(x)
#else
  #define muT(x) wxString(x)
  #define mumT(x) _T(x)
#endif
#else
#endif

wxString FileNameDialog(wxWindow * parent, 
			int Command = CM_FILEOPEN, 
			wxString Filename = wxEmptyString);

#ifdef DEBUG
# define DEBUGLOGBASE(type, ...)		   \
  std::cout << __FILE__ << ":" << __LINE__ << ": " \
  << ((const char *) type) << "::" << __WXFUNCTION__ << ": "	\
  << (const char *)((wxString::Format(__VA_ARGS__)).ToUTF8()) << std::endl

#else
# define DEBUGLOGBASE(...)
#endif

#define DEBUGLOG(...) DEBUGLOGBASE(typeid(*this).name(),__VA_ARGS__)
#define DEBUGLOG2(...) DEBUGLOGBASE(_T(""),__VA_ARGS__)
#define DEBUGLOGTYPE(type, ...) DEBUGLOGBASE(typeid(type).name(), __VA_ARGS__)

//#ifdef __WXGTK__
#define MDI_FORCE_EXTERN
//#endif

#endif

