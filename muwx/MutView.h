/** \file                  -*- C++ -*-
 ********************************************************************
 * Document/View View class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutView.h,v 1.9 2011/09/27 20:13:23 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:23 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: MutView.h,v $
 * Revision 1.9  2011/09/27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.8  2011-09-05 11:30:08  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.7  2011-08-31 20:18:16  keinstein
 * some work on printing the editor file
 *
 * Revision 1.6  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.5  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.4  2011-08-06 09:19:45  keinstein
 * documentation fixes
 *
 * Revision 1.3  2011-07-31 21:32:21  keinstein
 * Slightly improved window positioning
 * Suppress route window, when a Window is opened from the command line
 *
 * Revision 1.2  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.1  2011-07-31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
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

#include "Defs.h"
#include "MutFrame.h"

#ifndef MUWX_MUTVIEW_H_PRECOMPILED
#define MUWX_MUTVIEW_H_PRECOMPILED
// ---------------------------------------------------------------------------
// headers
// --------------------------------------------------------------------------


#include <wx/wx.h>
#include <wx/docview.h>


namespace mutaborGUI {
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
				wxASSERT(dynamic_cast<MutFrame *>(f));
			}
			return (MutFrame *) f; 
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
