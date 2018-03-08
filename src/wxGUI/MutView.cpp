/** \file 
 ********************************************************************
 * Document/View View class for Mutabor source files.
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
		TRACEC;
		textsw = (MutEditFile *) NULL;
		SetFrame(NULL);
	}

	MutView::~MutView()
	{
		TRACEC;
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
		TRACEC;
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
#if wxCHECK_VERSION(2,9,0)
			name = GetDocument()->GetUserReadableName();
#else
			GetDocument()->GetPrintableName(name);
#endif
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
		mutUnused(activate);
		mutUnused(activeView);
		mutUnused(deactiveView);
		// don't implement this function before looking at the debug output
		DEBUGLOG (docview, "Activate: %d && %p == %p" ,
			 activate, (void*)activeView, (void*)this);
	}


	bool MutView::TryParent(wxEvent& event)
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

		return false;
	}

}
///\}
