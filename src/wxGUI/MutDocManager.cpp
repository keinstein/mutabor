/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/MutDocManager.cpp,v 1.8 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.8 $
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
 * Revision 1.8  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.7  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.6  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-08-28 20:09:10  keinstein
 * several impovements for opening and saving files
 *
 * Revision 1.4  2011-08-24 21:19:36  keinstein
 * first run with 2.9.2+
 *
 * Revision 1.3  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.2  2011-08-11 19:00:48  keinstein
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
// availlable groups: GUI, route, kernel, src/wxGUI, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutDocManager.h"
#include "src/wxGUI/MutView.h"
#include "src/wxGUI/MutDocument.h"
#include "src/kernel/routing/Route-inlines.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


using mutaborGUI::MutDocManager;

BEGIN_EVENT_TABLE(MutDocManager, wxDocManager)
EVT_MENU(CM_EXECUTE, MutDocManager::CmExecuteLogic)
END_EVENT_TABLE()

namespace mutaborGUI {

	bool MutDocManager::TryParent(wxEvent& event)
	{
		mutUnused(event);
		TRACEC;
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

		return true;
	}

        // Extend event processing to search the view's event table
	bool MutDocManager::ProcessEvent(wxEvent& event)
	{
		if (!wxEvtHandler::ProcessEvent(event))
		{
			wxView* view = GetCurrentView();
			DEBUGLOG(eventqueue,_T("View: %p"),
				 (void*)(dynamic_cast<MutView *>(view)));
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

	void MutDocManager::CmExecuteLogic(wxCommandEvent& event) 
	{
		mutUnused(event);
		wxDocument * doc = CreateDocument( wxEmptyString, 0);
		if ( !doc )
		{
			OnOpenFileFailure();
			return;
		}

		/** \todo correct command processing */

		mutASSERT(dynamic_cast<MutDocument *>(doc));
		wxView * view = doc->GetFirstView();
		if (!view) {
			UNREACHABLEC;
			return;
		}
		wxWindow * f = view->GetFrame();
		if (!f) {
			UNREACHABLEC;
		}
		mutASSERT(dynamic_cast<MutFrame *>(f));
		wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED,
				  CM_ACTIVATE);
		f->GetEventHandler()->ProcessEvent(ev);
	}


}
///\}
