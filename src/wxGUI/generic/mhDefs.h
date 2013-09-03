/** \file  -*- C++ -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/generic/mhDefs.h,v 1.24 2011/11/02 14:32:01 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  R. Krauße, Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:32:01 $
 * \version $Revision: 1.24 $
 * \license GPL
 *
 * $Log: mhDefs.h,v $
 * Revision 1.24  2011/11/02 14:32:01  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.23  2011-10-22 16:32:39  keinstein
 * commit to continue debugging on Linux/wine
 *
 * Revision 1.22  2011-10-04 05:38:44  keinstein
 * some configuration fixes
 *
 * Revision 1.21  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.20  2011-02-20 22:35:59  keinstein
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

#include "src/kernel/Defs.h"

#include "wx/window.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include <iostream>
#include <typeinfo>
#include <list>


#include "src/wxGUI/Mutabor.rh"

#ifndef HAVE_CONFIG_H
#  ifdef __WXMSW__
#    define REUSE(type)
#  else
#    define REUSE(type) type
#  endif
#endif

#include "wx/image.h"
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

inline wxString muT(const char * x) {
	if (!x || !(*x)) return wxEmptyString;
	wxString retval = wxString::FromUTF8(x);
	if (retval.IsEmpty()) {
		retval = wxString(x, wxConvISO8859_1);
	}
	return retval;
}
inline wxString muT(const wxChar * x) {
	if (!x || !(*x)) return wxEmptyString;
	return wxString(x);
}
inline wxString muT(const std::string & s) {
	return muT(s.c_str());
}

#if defined(WX) && (defined(UNICODE) || wxUSE_WCHAR_T)
#include "wx/strconv.h"
extern wxCSConv muCSConv;

#define mumT(x) _T(x)
#else
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


/** 
 * Call update on a Window hierarchy recursively.
 * \note this function is very expensive. It should be called very rarly (as well as Update().
 * 
 * \param win Parent window that shall be updated.
 */
inline void UpdateRecursive (wxWindow * win) {
	if (!win) return;
	wxWindowList & list = win->GetChildren();
	for (wxWindowList::iterator i = list.begin();
	     i != list.end();
	     i++)
		UpdateRecursive(*i);
	win->Update();
}

#ifdef DEBUG
void PRINTSIZER (wxSizer * sizer, const wxString & offset = _T (""));
#endif
//#ifdef __WXGTK__
#define MDI_FORCE_EXTERN
//#endif

typedef std::list<wxPoint> mutpointlist;

#endif


///\}
