/** \file 
 ********************************************************************
 * Logic window
 *
 * Copyright:   (c) 2008-2012 TU Dresden
 *               Changes after 10/2011 Tobias Schlemmer
 * \author R. Krauße
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#include "src/kernel/Global.h"
//#include "src/kernel/Runtime.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/MutLogicWnd.h"
#include "src/wxGUI/MutChild.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "wx/dcclient.h"
#include "wx/image.h"


//#if !defined(__WXMSW__)
#include "Images/Icons/xpm/Logic.xpm"
#include "Images/Icons/xpm/LogicOpen.xpm"
#include "Images/Icons/xpm/Tonesyst.xpm"
#include "Images/Icons/xpm/TonesystOpen.xpm"
//#endif


#ifdef __BORLANDC__
#pragma hdrstop
#endif

namespace mutaborGUI {

	int pubTaste; // Taste aus anderen Fenstern für MutWin

	extern bool UseColorBars;

//void RightButtonMenu(TWindow *win, TPoint &point);

// TMutTag -----------------------------------------------------------
// repr‰sentiert Logik im Mut-Dialog


/*#define SETUPWINDOW_FONT(CLASS, BASECLASS, FONT)         \
  void CLASS::SetupWindow()										\
  {          															\
  BASECLASS::SetupWindow();									\
  SetWindowFont(HFONT(FONT), false);						\
  }

*/

	class MutTag : public MutIconShape
	{

	public:

		MutTag(wxWindow *parent, 
		       const wxPoint& pos,
		       int isLogic, 
		       int isOpen, 
		       int key);

		wxIcon & GetMutIcon() {
			return Icon;
		}

	private:
		bool IsLogic;
		int Key;
		wxIcon Icon;
		wxString Text;
		int TPos;

	public:
		int GetKey()
			{
				return Key;
			}

		bool GetIsLogic()

			{
				return IsLogic;
			}

#if 0
		void InitText(wxDC& dc);
		void OnPaint(wxPaintEvent& WXUNUSED(event));
#endif
		void OnDraw (wxDC & dc);
		void OnChar(wxKeyEvent& event);
		void OnLeftDown(wxMouseEvent& event);
		void OnGetFocus(wxFocusEvent& event);

	private:
		void PaintCenteredText(wxDC &dc, wxString s, int y)
		{
			wxCoord w, h;
			dc.GetMultiLineTextExtent(s, &w, &h);
			wxRect rect(wxPoint(0,0),GetSize());
			wxRect area = GetIconRect();
			rect.height = h;
			rect.y = y;
			dc.DrawLabel(s, area, wxALIGN_TOP | wxALIGN_CENTRE | wxST_NO_AUTORESIZE);
		}

	public:
		DECLARE_EVENT_TABLE()
	};

	BEGIN_EVENT_TABLE(MutTag, MutIconShape)
	//	EVT_PAINT(MutTag::OnPaint)
	EVT_CHAR(MutTag::OnChar)
	EVT_LEFT_DOWN(MutTag::OnLeftDown)
	//	EVT_SET_FOCUS(MutTag::OnGetFocus)
	//	EVT_KILL_FOCUS(MutTag::OnGetFocus)
	END_EVENT_TABLE()


	MutTag::MutTag(wxWindow *parent, const wxPoint& pos,
		       int isLogic, int isOpen, int key)
	: MutIconShape()
	{
		mutUnused(pos);
		/*  int Types[4] = { IDI_TONSYST, IDI_LOGIC, IDI_TONSYSTOPEN, IDI_LOGICOPEN};
		    Attr.Style |= BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS
		    | WS_GROUP | WS_TABSTOP;
		    Icon = new TIcon(GetModule()->GetInstance(), (TResId)Types[isLogic + 2*isOpen]);*/
		const char  ** TagIcon[4] = {
			tonesyst_xpm, logic_xpm, tonesystopen_xpm, logicopen_xpm
		};

		Icon = wxIcon(TagIcon[isLogic + 2*isOpen]);
		TPos = -1;
		IsLogic = isLogic != 0;
		Key = key;

		Create(parent, CM_MUTTAG);
		//TODO  Attr.AccelTable = IDA_MUTWIN;
	}


	void MutTag::OnDraw(wxDC & dc) {
		MutIconShape::OnDraw(dc);
		dc.SetTextBackground(GetBackgroundColour());
		dc.SetTextForeground(*wxBLACK);
		if (Key > 0)
			PaintCenteredText(dc, wxString::Format(_T("%c"), Key), 15);
	}

	void MutTag::OnChar(wxKeyEvent& event)
	{
		if ( ('A' < event.GetKeyCode() && event.GetKeyCode() <= 'z') 
		     //		     || event.GetKeyCode() == WXK_TAB 
		     || event.GetKeyCode() == WXK_RETURN 
		     || event.GetKeyCode() == WXK_SPACE )
			wxPostEvent(GetParent(),event);
		else 
			event.Skip();
	}

	void MutTag::OnLeftDown(wxMouseEvent& event)
	{
		mutUnused(event);
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_MUTTAG);
		event1.SetEventObject(this);
		wxPostEvent(GetParent(),event1);
	}

	void MutTag::OnGetFocus(wxFocusEvent& event)
	{
		Refresh();
		Update();
		event.Skip();
	}


	// MutLogicWnd ----------------------------------------------------------
	// Fenster, das die Logiken enthält


	BEGIN_EVENT_TABLE(MutLogicWnd, wxScrolledWindow)
	EVT_SET_FOCUS(MutLogicWnd::OnGetFocus)
	EVT_CHAR(MutLogicWnd::OnChar)
	EVT_SIZE(MutLogicWnd::OnSize)
	EVT_MENU(CM_MUTTAG, MutLogicWnd::CmMutTag)
	EVT_MENU(CM_UPDATEUI, MutLogicWnd::CmUpdateUI)
	EVT_CLOSE(MutLogicWnd::OnClose)
	EVT_ACTIVATE(MutLogicWnd::OnActivate)
	EVT_AUI_PANE_CLOSE(MutChild::OnAuiClose)
#if wxCHECK_VERSION(2,9,4)
	EVT_AUI_PANE_ACTIVATED(MutChild::OnAuiActivate)
#endif
	END_EVENT_TABLE()

	MutLogicWnd::MutLogicWnd(wxWindow *parent,
				 mutabor::Box b,

				 const wxPoint& pos,
				 const wxSize& size)
	: wxScrolledWindow(parent, -1, pos, size, wxHSCROLL |
				 wxVSCROLL | wxTAB_TRAVERSAL),
		ChangedCallback(b),
                Ok(false),
                nTags(-1),
                ColorBar1(NULL),
                ColorBar2(NULL),
                box(b),
		TagMinSize(80,40)
	{

		DEBUGLOG (other, "box %p" , box.get());


		SetScrollRate( 10, 10 );
		
		BoxData * guibox = ToGUIBase(box);
//	SetBackgroundColour(*wxWHITE);
		SetForegroundColour(guibox->GetTextColour());
		SetBackgroundColour(guibox->GetBackgroundColour());
		wxGridSizer * sizer = new wxGridSizer(1,10, 10);
		if (sizer) {
			//			sizer->SetFlexibleDirection(wxVERTICAL);
			//			sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);
			SetSizer(sizer);
		}

		BoxData * boxdata = ToGUIBase(box);
		mutASSERT(boxdata);
		if (!boxdata) return;
		mutASSERT(!boxdata->GetLogicWindow());
		boxdata->SetLogicWindow(this);

		CmBox();
	}


	wxString MutLogicWnd::MakeTitle() {
		return wxString::Format(_("Logic: %s - Box %d"),
					wxFileNameFromPath(CompiledFile).c_str(),
					box->get_routefile_id());
	}

	void MutLogicWnd::BoxChanged() {
		BoxData * guibox = ToGUIBase(box);
		SetForegroundColour(guibox->GetTextColour());
		SetBackgroundColour(guibox->GetBackgroundColour());
		wxAuiManager * manager = wxAuiManager::GetManager(this);
		mutASSERT(manager);
		if (!manager) return;
		wxAuiPaneInfo& pane = manager->GetPane(this);
		pane.Caption(MakeTitle());
		manager->Update();
	}

	void MutLogicWnd::OnSize(wxSizeEvent& event)
	{
		mutUnused(event);
		FixSizer();
	}

	void MutLogicWnd::FixSizer() {
		wxSize size = GetClientSize();
		wxGridSizer * sizer = dynamic_cast<wxGridSizer *>(GetSizer());
		if (!sizer) return;

		//		size_t columns = std::max(sizer->GetCols(),1);
		int rows = sizer->GetRows();
		// size_t clients = GetChildren().size();
		wxSize children_size;
		// size_t max_columns = size.x+TagMinSize.x-1/TagMinSize.x;
		
		if (rows != 0) sizer->SetRows(0);
		mutASSERT(sizer->GetRows() == 0);


#if 0
		if (!clients) {
			// this should not happen, but just in case
			// we need to avoid division by zero
			sizer->SetCols(1);
			FitInside();
			return;
		}
		
		while ((children_size = sizer->GetMinSize()).x <= size.GetWidth()) {
			if (columns > clients && 
			    (children_size.x*columns)/clients > (size_t) size.GetWidth())
				break;
			sizer->SetCols(++columns);
			// we need some overhead for calculation of the right size
			if (columns > max_columns) break; 
		}
		
		if (children_size.x / columns > TagMinSize.x) {
			TagMinSize.x = children_size.x/columns;
			max_columns = (size.x+TagMinSize.x-1)/TagMinSize.x;
		}

		if (columns > max_columns) columns = max_columns;

		while ((sizer->GetMinSize().x > size.GetWidth() && columns > 1)
		       || (columns > clients && children_size.x*columns/clients > (size_t) size.GetWidth()))
			sizer->SetCols(--columns);
#endif
		mutASSERT(TagMinSize.x >0);
		if (TagMinSize.x)
			sizer->SetCols(std::max(size.x/TagMinSize.x,1));
		
		FitInside();		
	}

	void MutLogicWnd::doClose(wxEvent& event)
	{
		TRACEC;
		wxWindow * parent = NULL;
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);

#if 0
		bool stop;
		if ( (stop = (NumberOfOpen(WK_LOGIC) <= 1) ) ) {
#endif
			parent = GetParent();

			while (parent && !(dynamic_cast<MutFrame *>(parent))) {
				DEBUGLOG (other, "Searching for MutFrame: %p..." ,(void*)parent);
				parent = parent->GetParent();
			}

			//GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND, CM_STOP);
#if 0
		}
#endif
		//    delete winAttr;
		event.Skip(false);

		Destroy();

		DEBUGLOGBASE(other,"MutLogicWnd",("Destroyed Window"));

		if (parent /* && stop*/) wxPostEvent(parent,event1);

		DEBUGLOGBASE(other,"MutLogicWnd",("Destroyed Window"));
	}


// Reaktion auf Computertastatur

	void MutLogicWnd::OnChar(wxKeyEvent& event)
	{
		pubTaste = event.GetKeyCode();
		CmTaste();

		SetCurrentBox(box);
		TRACEC;

		event.Skip();
	}

	void MutLogicWnd::CmTaste()

	{
		int key = pubTaste;

		if ( key == WXK_SPACE ) {
			wxWindow *w = wxWindow::FindFocus();

			if ( w && w->GetId() == CM_MUTTAG ) {
				mutASSERT(box);
				box->KeyboardAnalysis(((MutTag*)w)->GetKey(), 
						      ((MutTag*)w)->GetIsLogic()?
				      mutabor::BoxClass::KeyboardLogic:
				      mutabor::BoxClass::KeyboardNoLogic);
			}
		} else {
			mutASSERT(box);
			if (!box){
				UNREACHABLEC;
				return;
			}
			box->KeyboardAnalysis(key,mutabor::BoxClass::KeyboardAny);
		}
	}

	void MutLogicWnd::UpDate()
	{
		if (Ok) return;
		/* We might use a mutex here until rendering is done
		   to avoid rerendering, but this would at least slow
		   down music handling in BoxChangedAction. Currently
		   we waste time in the main thread when it is idle
		   anyway.
		*/
		Ok = true;
		// Analyse zuerst
#ifdef DEBUG
		BoxData * guibox = ToGUIBase(box);
		mutASSERT(guibox);
#endif

		wxSizer * sizer = GetSizer();
		wxSizerFlags flags;
		flags.Expand().Centre();

		
		//* \todo we must reuse old entries as rendering can be expensive
		DestroyChildren();
		MutTag * toFocus=NULL;
		bool isOpen;

		mutabor::BoxClass::logic_list logics = box->GetLogics();
		for (mutabor::BoxClass::logic_list::iterator i = logics.begin();
		     i != logics.end();
		     i++) {
			if ( (isOpen = i->flags == mutabor::BoxClass::logic_entry::CurrentLogic)) {
#if 0
				// guibox->SetLogic(sText);
				if ( !sEinst.IsEmpty() )
					guibox->SetTonesystem(sEinst);
				else if ( guibox->GetTonesystem().empty() )
					guibox->SetTonesystem(_("(INITIAL)"));
				else if ( guibox->GetTonesystem()[0] != '[' )
					guibox->SetTonesystem(
							      _T("[")
							      + guibox->GetTonesystem()
							      + _T("]")
							      );
#endif
			} else {
				//				guibox->SetTonesystem(sText);
			}
			bool isLogic = isOpen||i->flags == mutabor::BoxClass::logic_entry::Logic;
			MutTag * tag = new MutTag(this, 
						  wxDefaultPosition, 
						  isLogic,
						  isOpen || i->active,
						  i -> key);
			std::string taglabel = isLogic ? i-> name + (!i->startTuning.empty() ? 
								     "\n(" + i -> startTuning + ")":""): 
				i->startTuning;
#if wxCHECK_VERSION(2,9,0)
			tag -> SetLabel(taglabel);
#else
			tag -> SetLabel(wxString::FromUTF8(taglabel.c_str()));
#endif
			tag -> SetBackgroundColour(GetBackgroundColour());
			tag -> SetForegroundColour(GetForegroundColour());
			TagMinSize.IncTo(tag->GetBestSize());
			if (sizer)
				sizer->Add(tag,flags);
			if (isOpen || i->active) toFocus = tag;
		}

		Layout();
		FixSizer();

		if ( toFocus && FindFocus() != toFocus)
			toFocus->SetFocus();

	}

	// Reaktion auf geklickte TMutTag-s
	void MutLogicWnd::CmMutTag(wxCommandEvent& event)
	{
		mutASSERT(box);
		if (!box) {
			UNREACHABLEC;
			return;
		}
		MutTag *Tag = (MutTag*)event.GetEventObject();
		box->KeyboardAnalysis(Tag->GetKey(), 
				      Tag->GetIsLogic()?
				      mutabor::BoxClass::KeyboardLogic:
				      mutabor::BoxClass::KeyboardNoLogic);

		SetCurrentBox(box);
		TRACEC;
	}

	void MutLogicWnd::CmUpdateUI(wxCommandEvent & event) 
	{
		mutUnused(event);
		UpDate();
	}


	void MutLogicWnd::CmBox()
	{
		DEBUGLOG (other, "%s at box %p" ,CompiledFile.c_str(),box.get() );
		// Titel setzen
		GetParent()->SetName(MakeTitle());
		// Tags updaten
		UpDate();
	}

	void MutLogicWnd::OnActivate(wxActivateEvent& event)
	{
		if (event.GetActive()) {
			SetCurrentBox(box);
			mutUnused(event);
			TRACEC;
		}
	}

	void MutLogicWnd::OnGetFocus(wxFocusEvent& event)
	{
		SetCurrentBox(box);
		TRACEC;
		event.Skip();
	}

	void MutLogicWnd::BoxChangedAction(int flags) {
		if (flags & (ChangedCallback::LogicChanged | 
			     ChangedCallback::ActionChanged)) {
			Ok = false;
			wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,
					      CM_UPDATEUI);
			wxPostEvent(this,event);
		}
	}

	bool MutLogicWnd::SetBackgroundColour(const wxColour& colour) {
		bool retval = wxScrolledWindow::SetBackgroundColour(colour);
		wxWindowList & list = GetChildren();
		for (wxWindowList::iterator i = list.begin();
		     i != list.end();
		     ++i) {
			wxWindow * child = *i;
			retval &= child->SetBackgroundColour(colour);
		}
		return retval;
	}

	bool MutLogicWnd::SetForegroundColour(const wxColour& colour) {
		bool retval = wxScrolledWindow::SetForegroundColour(colour);
		wxWindowList & list = GetChildren();
		for (wxWindowList::iterator i = list.begin();
		     i != list.end();
		     ++i) {
			wxWindow * child = *i;
			retval &= child->SetForegroundColour(colour);
		}
		return retval;
	}


/*
  void MutLogicWnd::EvRButtonDown(uint, TPoint& point)
  {
  RightButtonMenu(this, point);
  }*/

}
///\}
