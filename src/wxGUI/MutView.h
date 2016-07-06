/** \file                  -*- C++ -*-
 ********************************************************************
 * Document/View View class for Mutabor source files.
 *
 * Copyright:   (c) 2011 TU Dresden
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
 * \addtogroup docview
 * \{
 ********************************************************************/


#if (!defined(MUWX_MUTVIEW_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTVIEW_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTVIEW_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutFrame.h"

#ifndef MUWX_MUTVIEW_H_PRECOMPILED
#define MUWX_MUTVIEW_H_PRECOMPILED
// ---------------------------------------------------------------------------
// headers
// --------------------------------------------------------------------------


#include <wx/wx.h>
#include <wx/docview.h>


namespace mutaborGUI {
	class MutEditFile;
/** What are the important qualities of a view? A view is registered with 
 * its document, and when the view becomes active (ie the user clicks on it)
 * then it will set its document to be the active/current document.
 * What else? it will receive instructions from the document to update 
 * (ie redraw) when the
 * document changes, and close when the document closes, and do something when
 * the document changes its filename (eg the user does a save_as).
 *   Does the view need an event table? no I think its methods get called by direct
 * pointer access p->method etc.
 */
	class MutView : public wxView
	{

		friend class MutDocument;
	public:
		MutView();
		virtual ~MutView();

		// message handler methods go here
		// virtual override
		virtual bool OnCreate(wxDocument* doc, long flags);
		// virtual override
		virtual bool OnClose(bool deleteWindow = true);

#if wxUSE_PRINTING_ARCHITECTURE
		// virtual override
		virtual wxPrintout* OnCreatePrintout();
#endif
		// virtual override
		virtual void OnDraw(wxDC* dc);
		// virtual override
		virtual void OnUpdate(wxView* sender, wxObject* hint = NULL);
		
		virtual void OnActivateView(bool activate, wxView * activeView, wxView * deactiveView);


		MutEditFile * GetTextsw() { return textsw; }
		void SetTextsw(MutEditFile * t) { textsw = t; }
		MutFrame * GetMutFrame() { 
			wxWindow * f = GetFrame();
			if (f) {
				mutASSERT(dynamic_cast<MutFrame *>(f));
			}
			return static_cast<MutFrame *>(f); 
		}
		
		DECLARE_EVENT_TABLE()
	protected:
		/// Pass certain events to the Application.
		/** MutView::ProcessEvent is called indirectly from MutApp event 
		    handlers. This leads to endless loops. To prevent these loops, 
		    we must be very careful, which kind of events get passed back.
	    
		    Probably no events should be propagated.
		*/
		bool TryParent(wxEvent& event);	

		MutEditFile * textsw;
		
		DECLARE_DYNAMIC_CLASS(MutView)
	};

}
#endif //precompiled
#endif // header loaded

///\}
