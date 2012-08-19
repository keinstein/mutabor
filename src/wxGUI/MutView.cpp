/** \file 
 ********************************************************************
 * Document/View View class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/MutView.cpp,v 1.11 2011/11/02 14:31:59 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 * $Log: MutView.cpp,v $
 * Revision 1.11  2011/11/02 14:31:59  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.10  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.9  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.8  2011-09-04 15:35:08  keinstein
 * disable print preview on OS X and when using libgnomeprint as they proviede their own means
 *
 * Revision 1.7  2011-08-31 20:18:16  keinstein
 * some work on printing the editor file
 *
 * Revision 1.6  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.5  2011-08-12 09:49:11  keinstein
 * act on some additional errors
 * delete Frame in OnClose if requested
 *
 * Revision 1.4  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.3  2011-08-06 09:19:45  keinstein
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
// availlable groups: GUI, route, kernel, src/wxGUI, debug


// ---------------------------------------------------------------------------
// headers
// --------------------------------------------------------------------------


#include "src/kernel/Defs.h"

#include "src/wxGUI/MutView.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutApp.h"
#include "src/wxGUI/MutDocument.h"
#include "src/kernel/routing/Route-inlines.h"

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
		textsw = (MutEditFile *) NULL;
		SetFrame(NULL);
	}

	MutView::~MutView()
	{
		DEBUGLOG(docview,_T(""));
		if (textsw) textsw->SetView(NULL);
		MutFrame * f = GetMutFrame();
		if (f) {
			f->SetView(NULL);
			f->Destroy();
		}
	}

/** this function will create a frame window, child of the mainframe,
 *   and will tell that frame about the view. 
 *  The MutViewFrame is smart enough
 *   to know what to  do with the view (ie use it for painting).
 */
	bool MutView::OnCreate(wxDocument* doc, long flags)
	{
		mutUnused(flags);
		DEBUGLOG(docview,_T(""));
		if (doc) {
			mutASSERT(dynamic_cast<MutDocument *>(doc));
		}

		// create a new MutViewFrame for this view to draw into. The ChildFrame is
		// told about the view, and the mainframe. It does not need to know about
		// the document. The constructor of the Frame will call View::SetFrame(this)
		MutFrame * frame  = new MutFrame((MutDocument *)doc, this, NULL, wxID_ANY, wxT(""));
		if (!frame) return false;
		wxGetApp().InitMainFrame(MutApp::EditorMenu,frame);

		textsw = new MutEditFile(this,
					 frame, 
					 wxDefaultPosition, 
					 wxDefaultSize);
	

		if (!textsw) {
			delete frame;
			return false;
		}
		frame->SetClient(textsw,doc->GetTitle());
#ifdef __X__
		// X seems to require a forced resize
		int x, y;
		frame->GetSize(&x, &y);
		frame->SetSize(wxDefaultCoord, wxDefaultCoord, x, y);
#endif

		frame->SetView(this);
		SetFrame(frame);
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
			MutFrame * f = GetMutFrame();
			SetFrame(NULL);
			f->SetView(NULL);
			f->Destroy();
		}
		return true;
	}


#if wxUSE_PRINTING_ARCHITECTURE
	wxPrintout* MutView::OnCreatePrintout() {
		if (textsw) {
			mutASSERT(GetDocument());
			wxString name;
			GetDocument()->GetPrintableName(name);
			return new MutEditPrint(this,textsw,name);
		} else {
			return wxView::OnCreatePrintout();
		}
	}
#endif

	void MutView::OnDraw(wxDC* dc)
	{
		mutUnused(dc);
                // handled by MutEditWindow
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

	void MutView::OnActivateView(bool activate, 
				     wxView *activeView, 
				     wxView *deactiveView)
	{
			mutUnused(deactiveView);
		// don't implement this function before looking at the debug output
		DEBUGLOG(docview,_T("Activate: %d && %x == %x"),
			 activate, activeView, this);
	}


	bool MutView::TryParent(wxEvent& event)
	{
		mutUnused(event);
		DEBUGLOG(eventqueue,_T(""));
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

}
///\}
