/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocManager.h,v 1.8 2011/11/02 14:31:58 keinstein Exp $
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
 * $Log: MutDocManager.h,v $
 * Revision 1.8  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.7  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.6  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.5  2011-08-28 20:09:11  keinstein
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
 * \addtogroup docview
 * \{
 ********************************************************************/

#if (!defined(MUWX_MUTDOCMANAGER_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTDOCMANAGER_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTDOCMANAGER_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "mu32/Defs.h"

#ifndef MUWX_MUTDOCMANAGER_H_PRECOMPILED
#define MUWX_MUTDOCMANAGER_H_PRECOMPILED
#include "wx/docview.h"

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "wx/event.h"

namespace mutaborGUI {
	class MutDocManager:public wxDocManager {
	public:
		/// Extend event processing to search the view's event table
		bool ProcessEvent(wxEvent& event);

		/// calculate the frame title
		virtual wxString MakeFrameTitle(wxDocument* doc);
		void CmExecuteLogic(wxCommandEvent& event);
    

	protected:
		/// Pass certain events to the Application.
		/** MutDocManager::ProcessEvent is called directly from MutApp 
		    event handlers. This leads to endless loops. To prevent these
		    loops, we must be very careful, which kind of events get 
		    passed back. Probably no events should be propagated.
		*/
		virtual bool TryParent(wxEvent& event);	
		DECLARE_EVENT_TABLE()
	};
}

#endif
#endif

///\}
