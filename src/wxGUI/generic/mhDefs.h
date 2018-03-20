/** \file  -*- C++ -*-
 ********************************************************************
 * Uncategorized definitions.
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 *              changes after 2011/11 (c) by the authors
 * \author  R. Krauße, Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ********************************************************************
 * \addtogroup GUI
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

// currently only used for Mac port translation of “FILE”
inline wxString getContextLocal(const wxString & s)
{
	wxString ret = s.AfterFirst('|');

	if (ret == wxEmptyString) return s;
	else return ret;
}


#if defined(WX) && (defined(UNICODE) || wxUSE_WCHAR_T)
#if 0
#include "wx/strconv.h"
extern wxCSConv muCSConv;
#endif

#define mumT(x) _T(x)
#else
#define mumT(x) _T(x)
#endif
#else
#endif

struct MutFileDataType {
	wxFileName name;
	enum { 
		Canceled,
		Unknown,
		TextRoute,
		UTF8TextRoute,
		XMLRoute1,
		LogicSource
	} type;
	operator wxString() {
		return name.GetPath();
	}
	MutFileDataType():name(),type(Unknown) {}
};

MutFileDataType FileNameDialog(wxWindow * parent,
                        int Command = CM_FILEOPEN,
                        wxString Filename = wxEmptyString);

#include "mutDebug.h"

#if 0
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
#endif

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
	     ++i)
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
