/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocManager.cpp,v 1.2 2011/08/11 19:00:48 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/08/11 19:00:48 $
 * \version $Revision: 1.2 $
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
 * $Log: MutDocManager.cpp,v $
 * Revision 1.2  2011/08/11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.1  2011-08-06 09:22:27  keinstein
 * added mutabor document manager class
 *
 *
 *
 ********************************************************************
 * \deftogroup docview Document/View framework
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>
#include "MutDocManager.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutabor {

	bool MutDocManager::TryParent(wxEvent& event)
	{
		// if we must pass some events to the Application, 
		// they must be handled here somehow replacing false
#if 0
		// Implementation in Event.cpp:
		if ( wxTheApp && false )
		{
			// Special case: don't pass wxEVT_IDLE to wxApp, since it'll always
			// swallow it. wxEVT_IDLE is sent explicitly to wxApp so it will be
			// processed appropriately via SearchEventTable.
			if ( event.GetEventType() != wxEVT_IDLE )
			{
				if ( wxTheApp->ProcessEvent(event) )
					return true;
			}
		}
#endif

		return false;
	}

        // Extend event processing to search the view's event table
	bool MutDocManager::ProcessEvent(wxEvent& event)
	{
		if (!wxEvtHandler::ProcessEvent(event))
		{
			wxView* view = GetCurrentView();
			if (view && view->ProcessEvent(event))
				return true;
			else return false;
		}
		return true;
	}


	// Make a frame title (override this to do something different)
        // If docName is empty, a document is not currently active.
	wxString MutDocManager::MakeFrameTitle(wxDocument* doc)
	{
		wxString appName = wxTheApp->GetAppName();
		wxString title;
		if (!doc)
			title = appName;
		else
		{
			wxString docName;
			doc->GetPrintableName(docName);
			title = docName + wxString(_(" - ")) + _T(PACKAGE_NAME);
		}
		return title;
	}


}
///\}
