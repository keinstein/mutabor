/** \file               -*- C++ -*-
********************************************************************
* Interface_dependent functions.
*
* Copyright:   (c) 2013 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
*
********************************************************************
* \addtogroup kernel
* \{
********************************************************************/
// availlable groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute

#include "src/kernel/Defs.h"
#include "src/wxGUI/generic/mhDefs.h"
#include "src/wxGUI/MutApp.h"
#include "src/kernel/interface_deps.h"
#include <stdio.h>
#include "wx/string.h"
#include "wx/log.h"
#include "wx/apptrait.h"

static bool DoShowAssertDialog(const wxString& msg)
{
	// under MSW we can show the dialog even in the console mode
#if defined(__WXMSW__) && !defined(__WXMICROWIN__)
	wxString msgDlg(msg);

	// this message is intentionally not translated -- it is for
	// developpers only
	msgDlg += wxT("\nDo you want to stop the program?\n")
		wxT("You can also choose [Cancel] to suppress ")
		wxT("further warnings.");

	switch ( ::MessageBox(NULL, msgDlg, _T("wxWidgets Debug Alert"),
			      MB_YESNOCANCEL | MB_ICONSTOP ) )
		{
		case IDYES:
			wxTrap();
			break;

		case IDCANCEL:
			// stop the asserts
			return true;

			//case IDNO: nothing to do
		}
#else // !__WXMSW__
	wxFprintf(stderr, wxT("%s\n"), msg.c_str());
	fflush(stderr);

	// TODO: ask the user to enter "Y" or "N" on the console?
	wxTrap();
#endif // __WXMSW__/!__WXMSW__

	// continue with the asserts
	return false;
}


extern "C" {
	void MutInitConsole(); /* in debug.cpp */

	// implement wxWidgets assertions:
	void mutabor_assert_fail(const char *file,
				 int line,
				 const char *func,
				 const char *cond,
				 const char *msg)
	{
		if (!std::clog.good()) MutInitConsole();
		wxString s = wxString::Format(_("%s:%d: An assert failed in %s().\nCondition: %s\nMessage:%s\nDo you want to call the default assert handler?"),
					      file,line,func,cond,msg);
		std::clog << (const char *) s.ToUTF8() << std::endl;


		// use wxWidgets ShowAssertDialog function (it's static so we repeat its code, here.

		{
			// this variable can be set to true to suppress "assert failure" messages
			static bool s_bNoAsserts = false;

			wxString message;
			message.reserve(2048);

			// here, we change format to the gcc form
			message.Printf(wxT("%s:%d: assert \"%s\" failed"), file, line, cond);

			// add the function name, if any
			if ( func && *func )
				message << _T(" in ") << func << _T("()");

			// and the message itself
			if ( msg )
				{
					message << _T(": ") << msg;
				}
			else // no message given
				{
					message << _T('.');
				}

#if wxUSE_THREADS
			// if we are not in the main thread, output the assert directly and trap
			// since dialogs cannot be displayed
			if ( !wxThread::IsMain() )
				{
					message += wxT(" [in child thread]");

#if defined(__WXMSW__) && !defined(__WXMICROWIN__)
					message << wxT("\r\n");
					OutputDebugString(message );
#else
					// send to stderr
					wxFprintf(stderr, wxT("%s\n"), message.c_str());
					fflush(stderr);
#endif
					// He-e-e-e-elp!! we're asserting in a child thread
					wxTrap();
				}
			else
#endif // wxUSE_THREADS

				if ( !s_bNoAsserts )
					{
						// send it to the normal log destination
						wxLogDebug(_T("%s"), message.c_str());

#ifdef __WXDEBUG__
						if ( wxGetApp().GetTraits() )
							{
								// delegate showing assert dialog (if possible) to that class
								s_bNoAsserts = wxGetApp().GetTraits()->ShowAssertDialog(message);
							}
						else // no traits object
#endif
							{
								// fall back to the function of last resort
								s_bNoAsserts = DoShowAssertDialog(message);
							}
					}
		}
	}
}

///\}
