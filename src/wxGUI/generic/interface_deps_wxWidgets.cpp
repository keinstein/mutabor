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

#include "interface_deps.h"
#include "stdio.h"

void mutabor_assert_fail(const char *file,
			 int line,
			 const char *func,
			 const char *cond,
			 const char *msg) {
	if (!std::clog.good()) MutInitConsole();
	std::string message = boost::str(boost::format("%s:%d:%s An assert failed.\nFunction: %s; Expression: %s")
				   % file
				   % line
				   % (msg?msg:""),
				   % func,
				   cond);

	std::clog << message << std::endl;
	// use wxWidgets ShowAssertDialog function (it's static so we repeat its code, here.
	{
		// this variable can be set to true to suppress "assert failure" messages
		static bool s_bNoAsserts = false;
		
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
					wxLogDebug(_T("%s"), wxString(message).c_str());

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
#endif
}


///\}
