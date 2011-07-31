/** \file 
 ********************************************************************
 * Document/View View class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutView.cpp,v 1.1 2011/07/31 12:40:42 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/07/31 12:40:42 $
 * \version $Revision: 1.1 $
 * \license GPL
 *
 * $Log: MutView.cpp,v $
 * Revision 1.1  2011/07/31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug


// ---------------------------------------------------------------------------
// headers
// --------------------------------------------------------------------------


// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#include "MutView.h"
#include "MutFrame.h"
#include "MutApp.h"
#include "MutDocument.h"
#include <wx/wx.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

using mutaborGUI::MutView;
IMPLEMENT_DYNAMIC_CLASS(MutView, wxView)

BEGIN_EVENT_TABLE(MutView, wxView)
END_EVENT_TABLE()

namespace mutaborGUI {

 	MutView::MutView()
	{
		
	}

	MutView::~MutView()
	{
		
		
	}

/** this function will create a frame window, child of the mainframe,
 *   and will tell that frame about the view. 
 *  The MutViewFrame is smart enough
 *   to know what to  do with the view (ie use it for painting).
 */
	bool MutView::OnCreate(wxDocument* doc, long flags)
	{
		printf("MutView::OnCreate\n");
		// create a new MutViewFrame for this view to draw into. The ChildFrame is
		// told about the view, and the mainframe. It does not need to know about
		// the document. The constructor of the Frame will call View::SetFrame(this)
		MutFrame * pFrame = new MutFrame(doc, this, NULL, wxID_ANY, wxT(""), wxPoint(260,60), wxSize(150,160) );

		pFrame->Show(true);
	
		// The doc manager maintains an active view, which is used to
		// discern the active document which could be meaningful in MDI apps.
		Activate(true);

		//  return false to have this view deleted, supposedly.
		return true;
	}

	bool MutView::OnClose(bool bDelWindow)
	{
		// this tells the framework that this view is invalid
		Activate(false);
		// I suspect that this instance of the object is going to be deleted,
		// so we must destroy anything that maintains a pointer to it: its window

		if(bDelWindow)
		{
			// if the request to close comes from the menu => doc manager => doc => view, we'll be here.

			// The argument to Close says whether to delete the window or not.
			GetFrame()->Close(true);
		}
		else
		{
			// if the request to close comes from the window itself, we'd be here.

			// don't need this (?) 
			//wxDocChildFrame* p = dynamic_cast<wxDocChildFrame*>(GetFrame());
			//p->SetView(NULL);
		}
		// wxMessageBox(wxT("onclose"), _T(""), wxOK | wxICON_INFORMATION);
		return true;
	}

	void MutView::OnDraw(wxDC* pdc)
	{
		MutDocument* pDoc = dynamic_cast<MutDocument*>(GetDocument());
		// just a bit of doc-independent test code
		wxSize s = GetFrame()->GetClientSize();
		pdc->DrawCircle(0,0,s.GetWidth());
	}

	void MutView::OnUpdate(wxView* sender, wxObject* hint)
	{
		if(GetFrame())
		{
			GetFrame()->Refresh();
		}
		else
		{
			assert(false);
		}
		assert(dynamic_cast<MutFrame*>(GetFrame())->GetView()==this);

		wxMessageBox(wxT("onupdate"), _T("onupdate"), wxOK | wxICON_INFORMATION);
	}

}
///\}
