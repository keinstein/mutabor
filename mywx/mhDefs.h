/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mhDefs.h,v 1.20 2011/02/20 22:35:59 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  R. Krauße, Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.20 $
 * \license GPL
 *
 * $Log: mhDefs.h,v $
 * Revision 1.20  2011/02/20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
#ifndef mhDEFS_H
#define mhDEFS_H

#include "Defs.h"
#include "wx/wx.h"


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

#ifdef VC8
  #include <wx/html/helpctrl.h>
#else
  class wxHtmlHelpController;
#endif

extern wxHtmlHelpController * HelpController;

#ifdef WX
#if defined(WX) && (defined(UNICODE) || wxUSE_WCHAR_T)
#include "wx/strconv.h"
extern wxCSConv muCSConv;

#define muT(x)  (wxString(x, wxConvISO8859_1))
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

#include "mutDebug.h"

// STUBs should generate error messages even in non-debug mode
#define STUBBASE(stubtype,typestr) \
do { \
	std::cerr << stubtype << " in " ; \
        std::cerr << __FILE__ << ":" << __LINE__ << ": " ;\
	std::cerr << typestr << "::" ;\
	std::cerr << __WXFUNCTION__ << std::endl;\
	wxFAIL_MSG(wxString::Format(_T("\n\n%s\n\nin %s:%d:\n\n%s::%s\n\n"), \
				    muT(stubtype).c_str(), \
				    _T(__FILE__), \
				    __LINE__, \
				    muT(typestr).c_str(), \
				    muT(__WXFUNCTION__).c_str())); \
} while (0)

/// functions or code that has to be written -- simple function
#define STUB STUBBASE("stub function","")
/// functions or code that has to be written -- use for static class members
#define STUBCT(type) STUBBASE("stub function",((const char *) (typeid(type).name())))
/// functions or code that has to be written -- use for normal class members
#define STUBC STUBCT(*this)

#define UNREACHABLE STUBBASE("unreachable code","")
#define UNREACHABLECT(type) STUBBASE("unreachable code",((const char *) (typeid(type).name())))
#define UNREACHABLEC UNREACHABLECT(*this)

#define ABSTRACT_FUNCTION STUBBASE("unreachable function","")
#define ABSTRACT_FUNCTIONCT(type) STUBBASE("unreachable function",((const char *) (typeid(type).name())))
#define ABSTRACT_FUNCTIONC ABSTRACT_FUNCTIONCT(*this)



#ifdef DEBUG
void PRINTSIZER (wxSizer * sizer, const wxString & offset = _T (""));
#endif
//#ifdef __WXGTK__
#define MDI_FORCE_EXTERN
//#endif

#endif


///\}
