/** \file 
 ********************************************************************
 * Logic window
 *
 * Copyright:   (c) 2008-2012 TU Dresden
 *               Changes after 10/2011 Tobias Schlemmer
 * \author R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
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
#if 0
	void MutTag::InitText(wxDC& dc)

	{
		int i = Text.Length();
		wxCoord w, h;
		dc.GetMultiLineTextExtent(Text, &w, &h);

		if ( w <= MUTTAGX-4 ) TPos = 0;

		while ( i >= 0 ) {
			if ( Text[i] == '_' ) {
				Text[i] = '-';
				if ( TPos == -1 ) {
					dc.GetMultiLineTextExtent(Text.Left(i+1), &w, &h);
					if ( w <= MUTTAGX-4 ) TPos = i+1;
				}
			}

			i--;
		}

		if ( TPos == -1 ) TPos = 0;

		dc.GetMultiLineTextExtent(Text.Mid(TPos), &w, &h);

		if ( w > MUTTAGX-4 )
			Text.Last() = '.';

		dc.GetMultiLineTextExtent(Text.Mid(TPos), &w, &h);

		int l = Text.Length();

		while ( w > MUTTAGX-4 ) {
			l--;
			Text.Truncate(l);
			Text.Last() = '.';
			dc.GetMultiLineTextExtent(Text.Mid(TPos), &w, &h);
		}
	}

	

	void MutTag::OnPaint(wxPaintEvent& WXUNUSED(event))
	{
		wxPaintDC dc(this);
		//dc.SetBackgroundMode(wxTRANSPARENT);
		dc.SetBackground(GetBackgroundColour());

		dc.SetMapMode(wxMM_TEXT);
		// evtl. erst noch Abteilung des Textes berechnen

		if ( TPos == -1 ) InitText(dc);

		// Selected-Rahmen
		wxPen SelPen(GetForegroundColour(), 1, wxDOT);
		wxBrush SelBrush(GetBackgroundColour(),wxTRANSPARENT);

		if ( wxWindow::FindFocus() == this ) {
			dc.SetPen(SelPen);
			dc.SetBrush(SelBrush);
			if ( TPos )
				dc.DrawRectangle(1, 3, MUTTAGX-6, MUTTAGY-3);
			else
				dc.DrawRectangle(1, 3, MUTTAGX-6, MUTTAGY-6);
		}

		// dc.SetPen(wxNullPen);

		// Icon zeichnen
		dc.DrawIcon(Icon, MUTTAGX/2-16, 10);

		// Taste auf Icon
		dc.SetTextBackground(GetBackgroundColour());
		dc.SetTextForeground(*wxBLACK);
		if (Key > 0)
			PaintCenteredText(dc, wxString::Format(_T("%c"), Key), 20);

		dc.SetTextForeground(GetForegroundColour());
		if ( TPos ) {
			PaintCenteredText(dc, Text.Mid(0, TPos), 44);
			PaintCenteredText(dc, Text.Mid(TPos), 56);
		} else
			PaintCenteredText(dc, Text, 50);

	}
#endif

	void MutTag::OnChar(wxKeyEvent& event)
	{
//  TButton::EvChar(key, repeatCount, flags);

		if ( ('A' < event.GetKeyCode() && event.GetKeyCode() <= 'z') 
		     || event.GetKeyCode() == WXK_TAB 
		     || event.GetKeyCode() == WXK_RETURN 
		     || event.GetKeyCode() == WXK_SPACE )
			wxPostEvent(GetParent(),event);
	}

	void MutTag::OnLeftDown(wxMouseEvent& event)
	{
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_MUTTAG);
		event1.SetEventObject(this);
		//((MutLogicWnd*)GetParent())->UpDate(GetKey(), GetIsLogic());
		wxPostEvent(GetParent(),event1);
	}

	void MutTag::OnGetFocus(wxFocusEvent& event)
	{
//		SetFocus();
		Refresh();
		Update();
//		((MutLogicWnd*)GetParent())->CorrectScroller();
		event.Skip();
	}

/*LRESULT TMutTag::EvCommand(UINT id, HWND hWndCtl, UINT notifyCode)
  {
  if (hWndCtl == 0 && notifyCode == 1)
  // from an accelerator
  if ( id == VK_LEFT || id == VK_RIGHT || id == VK_UP || id == VK_DOWN || id == VK_F12 )
  Parent->HandleMessage(WM_CHAR, id, 1);
  return TButton::EvCommand(id, hWndCtl, notifyCode);
  }*/

// Funktion f¸r FirstThat

/*bool HasPosition(TWindow *win, void *param)
  {
  return win->Attr.X == ((int*)param)[0] && win->Attr.Y == ((int*)param)[1];
  }*/

// MutLogicWnd ----------------------------------------------------------
// Fenster, das die Logiken enth‰lt

/*DEFINE_RESPONSE_TABLE1(MutLogicWnd, TWindow)
  EV_WM_CHAR,
  EV_WM_SIZE,
  EV_COMMAND(CM_MUTTAG, CmMutTag),
  EV_COMMAND(CM_TASTE, CmTaste),
  EV_COMMAND(CM_BOX, CmBox),
  EV_WM_RBUTTONDOWN,
  END_RESPONSE_TABLE;*/

	BEGIN_EVENT_TABLE(MutLogicWnd, wxScrolledWindow)
	EVT_SET_FOCUS(MutLogicWnd::OnGetFocus)
	EVT_CHAR(MutLogicWnd::OnChar)
	EVT_SIZE(MutLogicWnd::OnSize)
	EVT_MENU(CM_MUTTAG, MutLogicWnd::CmMutTag)
	EVT_MENU(CM_UPDATEUI, MutLogicWnd::CmUpdateUI)
	EVT_CLOSE(MutLogicWnd::OnClose)
	EVT_ACTIVATE(MutLogicWnd::OnActivate)
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

		DEBUGLOG(other,_T("box %p"), box.get());


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

	void MutLogicWnd::OnSize(wxSizeEvent& event)
	{
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
				DEBUGLOG (other, _T("Searching for MutFrame: %p..."),(void*)parent);
				parent = parent->GetParent();
			}

			//GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND, CM_STOP);
#if 0
		}
#endif
		//    delete winAttr;
		event.Skip(false);

		Destroy();

		DEBUGLOGBASE(other,"MutLogicWnd",_T("Destroyed Window"));

		if (parent /* && stop*/) wxPostEvent(parent,event1);

		DEBUGLOGBASE(other,"MutLogicWnd",_T("Destroyed Window"));
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
		/*	if ( key == WXK_TAB )
			{
			HWND Handle = GetWindowPtr(GetFocus())->GetNextWindow(GW_HWNDNEXT);
			if ( Handle )
			GetWindowPtr(Handle)->SetFocus();
			else
			GetFirstChild()->SetFocus();
			SetFocusPos();
			CorrectScroller();
			}
			else if ( key == VK_UP )
			MoveFocus(0, -1);
			else if ( key == VK_DOWN )
			MoveFocus(0, +1);
			else if ( key == VK_LEFT )
			MoveFocus(-1, 0);
			else if ( key == VK_RIGHT )
			MoveFocus(+1, 0);
			else if ( key == VK_F12 )
			MessageBox("This code was nearly completely written by R.K.", "Besides...", MB_OK | MB_ICONASTERISK);
			else*/

		if ( key == WXK_SPACE ) {
			/*		TWindow *Win = FirstThat(HasPosition, FocusPos);
					if ( Win ) Win->SetFocus();
					CorrectScroller();
					SetFocusPos();*/
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

#if 0
#ifndef max
#define max(a, b) ((a) < (b) ? (b) : (a))
#endif


	void MutLogicWnd::DoLayout()
	{
/*
		wxSize R = GetClientSize();
		int nx = (R.GetWidth()-4) / MUTTAGX, 
			ny = (R.GetHeight()-4)/ MUTTAGY;
		bool quer = R.GetWidth() > R.GetHeight();

		if ( nx * ny < nTags ) // Scroller notwendig
		{

			if  ( ny < 1) ny = 1;

			if ( quer ) nx = (nTags + ny -1) / ny;
		}
		DEBUGLOG(other, _T("nTags = %d, nx = %d"),nTags,nx);

		if  ( nx < 1 ) nx = 1;

		ny = (nTags + nx -1) / nx;

		int x = 4, y = 4, xi = 0;

		DEBUGLOG(other, 
			 _T("nx = %d,  MUTTAGX = %d,  ny == %d,  MUTTAGY = %d"),
			 nx, MUTTAGX, ny, MUTTAGY);

		SetVirtualSize(nx*MUTTAGX+8, ny*MUTTAGY+8);

		int xv, yv;

		GetViewStart(&xv, &yv);

		for (wxWindowList::iterator i = GetChildren().begin(); 
		     i!=GetChildren().end(); i++) {
			wxWindow * Win= *i;
			if ( Win->GetId() == CM_MUTTAG ) {
				//			Win->Move(x - Scroller->XPos*Scroller->XUnit, y - Scroller->YPos*Scroller->YUnit, MUTTAGX, MUTTAGY, true);
				Win->Move(x-xv*10, y-yv*10);
				x += MUTTAGX;
				xi++;

				if ( xi == nx ) {
					x = 4;
					xi = 0;
					y += MUTTAGY;
				}
			}
		}

		if ( xi )
			y += MUTTAGY;

		// Farbbalken
		if ( ColorBar1 )
			ColorBar1->SetSize(-xv*10, -yv*10, max(nx*MUTTAGX+8, R.GetWidth()), 2);

		if ( ColorBar2 )
			ColorBar2->SetSize(-xv*10, -yv*10, 2, max(ny*MUTTAGY+8, R.GetHeight()));

		CorrectScroller();
*/
	}

#endif
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
		BoxData * guibox = ToGUIBase(box);
		mutASSERT(guibox);
#warning reimplement this using BoxClass::GetLogics();
#if 0
		guibox->KeyboardAnalysis(thekey,flags);
		if (flags == mutabor::BoxClass::KeyboardLogic) {
			guibox->SetKeyTonesystem(0);
			guibox->SetKeyLogic(thekey);
		}
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
			} else
				//				guibox->SetTonesystem(sText);
				;
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

#if 0
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED,
				      CM_UPDATEUI);

		BoxData * boxdata = ToGUIBase(box);
		wxWindow * win = boxdata->GetActionsWindow();
		if (win) 
			wxPostEvent(win,event1);
		win = boxdata->GetTonesystemWindow();
		if (win) 
			wxPostEvent(win,event1);
		/* keys may be retuned, now */
		win = boxdata->GetKeyWindow();
		if (win) 
			wxPostEvent(win,event1);
#endif
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
		UpDate();
	}

#if 0
	void MutLogicWnd::CorrectScroller()
	{
		wxWindow *Win = wxWindow::FindFocus();

		if ( !Win || Win->GetId() != CM_MUTTAG )
			return;

		int xView, yView;

		GetViewStart(&xView, &yView);

		xView *=10;

		yView *=10;

		int xw, yw;

		Win->GetPosition(&xw, &yw);

		xw += xView;

		yw += yView;

		int w, h;

		GetClientSize(&w, &h);

		int dx = xView, dy = yView;

		// rechte untere Ecke im Bild ???
		if ( xw + MUTTAGX > xView+w ) dx = xw + MUTTAGX - w;

		if ( yw + MUTTAGY > yView+h ) dy = yw + MUTTAGY - h;

		// linke obere Ecke im Bild ??? (dominierend)
		if ( xw < xView ) dx = xw;

		if ( yw < yView ) dy = yw;

		Scroll(dx / 10, dy / 10);
	}
#endif

// keyboardanalyse, Fenster aufräumen, Logiken lesen und anzeigen

// Reaktion auf neues aktuelles Instrument
	void MutLogicWnd::CmBox()
	{
		DEBUGLOG (other, _T("%s at box %p"),CompiledFile.c_str(),box.get() );
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


/*
  void MutLogicWnd::EvRButtonDown(uint, TPoint& point)
  {
  RightButtonMenu(this, point);
  }*/

}
///\}
