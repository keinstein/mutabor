/** \file 
 ********************************************************************
 * Document/View View class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutView.cpp,v 1.3 2011/08/06 09:19:45 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/08/06 09:19:45 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: MutView.cpp,v $
 * Revision 1.3  2011/08/06 09:19:45  keinstein
 * documentation fixes
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
		DEBUGLOG(docview,_T(""));
		frame = (MutFrame *) NULL;
		textsw = (MutEditFile *) NULL;
	}

	MutView::~MutView()
	{
		DEBUGLOG(docview,_T(""));
		
		
	}

/** this function will create a frame window, child of the mainframe,
 *   and will tell that frame about the view. 
 *  The MutViewFrame is smart enough
 *   to know what to  do with the view (ie use it for painting).
 */
	bool MutView::OnCreate(wxDocument* doc, long flags)
	{
		DEBUGLOG(docview,_T(""));
		// create a new MutViewFrame for this view to draw into. The ChildFrame is
		// told about the view, and the mainframe. It does not need to know about
		// the document. The constructor of the Frame will call View::SetFrame(this)
		frame = new MutFrame(doc, this, NULL, wxID_ANY, wxT(""));
		wxGetApp().InitMainFrame(MutApp::EditorMenu,frame);

		textsw = new MutEditFile(this,
					 frame, 
					 wxDefaultPosition, 
					 wxDefaultSize);
	

		frame->SetClient(textsw,wxT(""));
#ifdef __X__
		// X seems to require a forced resize
		int x, y;
		frame->GetSize(&x, &y);
		frame->SetSize(wxDefaultCoord, wxDefaultCoord, x, y);
#endif

		frame->Show(true);	
		// The doc manager maintains an active view, which is used to
		// discern the active document which could be meaningful in MDI apps.
		Activate(true);

		//  return false to have this view deleted, supposedly.
		return true;
	}

	bool MutView::OnClose(bool deleteWindow)
	{
		if (!GetDocument()->Close())
			return false;
    
		Activate(false);
    
		if (deleteWindow)
		{
			delete frame;
			return true;
		}
		return true;
	}

	void MutView::OnDraw(wxDC* WXUNUSED(dc))
	{
#if 0
// handled by MutEditWindow
		MutDocument* pDoc = dynamic_cast<MutDocument*>(GetDocument());
		// just a bit of doc-independent test code
		wxSize s = GetFrame()->GetClientSize();
		pdc->DrawCircle(0,0,s.GetWidth());
#endif
	}

	void MutView::OnUpdate(wxView* WXUNUSED(sender), wxObject* WXUNUSED(hint))
	{
#if 0
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
#endif
	}

}
///\}
