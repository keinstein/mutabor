/** \file                  -*- C++ -*-
 ********************************************************************
 * Document/View View class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutView.h,v 1.4 2011/08/06 09:19:45 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/08/06 09:19:45 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: MutView.h,v $
 * Revision 1.4  2011/08/06 09:19:45  keinstein
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


#ifndef MUTABOR_MUT_VIEW_H
#define MUTABOR_MUT_VIEW_H
// ---------------------------------------------------------------------------
// headers
// --------------------------------------------------------------------------


// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include <wx/wx.h>
#include <wx/docview.h>
#include "MutFrame.h"


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
		DECLARE_DYNAMIC_CLASS(MutView)
		DECLARE_EVENT_TABLE()
		public:
		MutView();
		~MutView();

		// message handler methods go here
		// virtual override
		virtual bool OnCreate(wxDocument* doc, long flags);
		// virtual override
		virtual bool OnClose(bool deleteWindow = true);
		// virtual override
		virtual void OnDraw(wxDC* dc);
		// virtual override
		virtual void OnUpdate(wxView* sender, wxObject* hint = NULL);
		
		MutEditFile * GetTextsw() { return textsw; }
		MutFrame * GetFrame() { return frame; }
	protected:
		MutFrame * frame;
		MutEditFile * textsw;

	};

}
#endif

///\}
