/** \file               -*- C++ -*-
 ********************************************************************
 * Mutabor document manager
 *
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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

#include "src/kernel/Defs.h"

#ifndef MUWX_MUTDOCMANAGER_H_PRECOMPILED
#define MUWX_MUTDOCMANAGER_H_PRECOMPILED
#include "wx/docview.h"

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "wx/event.h"

namespace mutaborGUI {
	class MutEditFile;
	class MutDocManager:public wxDocManager {
	public:
		/// Extend event processing to search the view's event table
		bool ProcessEvent(wxEvent& event);

		/// calculate the frame title
		virtual wxString MakeFrameTitle(wxDocument* doc);
		void CmExecuteLogic(wxCommandEvent& event);

		/// Import a scala tuning and keybord map file
		/**
		 * This function handles the menu event in case there is no
		 * Document associated with it.
		 *
		 * \param event the event that triggers the command
		 */
		void CmImportScala(wxCommandEvent & event);

		/// Import a scala tuning and keybord map file
		/**
		 * This function handles the menu event in case there is no
		 * Document associated with it.
		 */
		void ImportScala(MutEditFile * editor);

		/**
		 * Connect the event handling functions to the events.
		 *
		 * \param handler Event handler that shall call the
		 * handling functions.
		 */
		void ConnectToApp(wxEvtHandler * handler);

		/**
		 * Disconnect the event handling functions from the events.
		 *
		 * \param handler Event handler that should have
		 * called the handling functions.
		 */
		void DisconnectFromApp(wxEvtHandler * handler);

#if 0
		/* We are using Connect for the event handling so the
		   following is not needed anymore. */

	protected:
		/// Pass certain events to the Application.
		/** MutDocManager::ProcessEvent is called directly from MutApp
		    event handlers. This leads to endless loops. To prevent these
		    loops, we must be very careful, which kind of events get
		    passed back. Probably no events should be propagated.
		*/
		virtual bool TryParent(wxEvent& event);
#endif
	private:
		template<class C>
		void doConnect(C & Connect);
		DECLARE_EVENT_TABLE()
	};
}

#endif
#endif

///\}
