/** \file 
 ********************************************************************
 * Logic window
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutLogicWnd.cpp,v 1.23 2011/09/07 13:06:50 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/09/07 13:06:50 $
 * \version $Revision: 1.23 $
 * \license GPL
 *
 * $Log: MutLogicWnd.cpp,v $
 * Revision 1.23  2011/09/07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.22  2011-09-05 11:30:08  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.21  2011-07-30 12:58:49  keinstein
 * Fix bug introduced before last commit.
 * Change MutTag::OnLefUp into MutTag::OnLeftDown
 *
 * Revision 1.20  2011-07-30 12:06:20  keinstein
 * Change tone system status window when changing the tuning logic by hand
 *
 * Revision 1.19  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup muwx
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
//    #include "wx/mdi.h"
#endif

#include "Global.h"
//#include <stdio.h>
#include "Runtime.h"
#include "MidiKern.h"
//#include "Help.rh"
//#include "Mutabor.rh"
#include "MutLogicWnd.h"
#include "MutChild.h"
#include "MutFrame.h"
#include "MutRouteWnd.h"


//#if !defined(__WXMSW__)
#include "Icon/Logic.xpm"
#include "Icon/LogicOpen.xpm"
#include "Icon/Tonesyst.xpm"
#include "Icon/TonesystOpen.xpm"
//#endif

using mutaborGUI::BoxData;

int pubTaste; // Taste aus anderen Fenstern f¸r MutWin

extern bool UseColorBars;

//void RightButtonMenu(TWindow *win, TPoint &point);

// TMutTag -----------------------------------------------------------
// repr‰sentiert Logik im Mut-Dialog

#define MUTTAGX 90
#define MUTTAGY 70


wxSize MutTagSize(MUTTAGX, MUTTAGY);

/*#define SETUPWINDOW_FONT(CLASS, BASECLASS, FONT)         \
  void CLASS::SetupWindow()										\
  {          															\
	   BASECLASS::SetupWindow();									\
	   SetWindowFont(HFONT(FONT), false);						\
  }

*/

class MutTag : public wxWindow
{

public:

	MutTag(wxWindow *parent, const wxPoint& pos,
	       int isLogic, int isOpen, int key, const wxString& text);

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

	void InitText(wxDC& dc);
	/*    void ODADrawEntire(DRAWITEMSTRUCT far& drawInfo);
	void ODAFocus(DRAWITEMSTRUCT far& drawInfo);
	void ODASelect(DRAWITEMSTRUCT far& drawInfo);*/
	void OnPaint(wxPaintEvent& WXUNUSED(event));
	void OnChar(wxKeyEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnFocus(wxFocusEvent& event);

private:
	void PaintCenteredText(wxDC &dc, wxString s, int y)
	{
		wxCoord w, h;
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (MUTTAGX-w)/2, y);
	}

public:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MutTag, wxWindow)
	EVT_PAINT(MutTag::OnPaint)
	EVT_CHAR(MutTag::OnChar)
	EVT_LEFT_DOWN(MutTag::OnLeftDown)
	EVT_SET_FOCUS(MutTag::OnFocus)
	EVT_KILL_FOCUS(MutTag::OnFocus)
END_EVENT_TABLE()

/*TFont MutFont(8, 0, 0, 0, FW_NORMAL,
  false, false, false, 1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
  DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "MS Sans Serif");

SETUPWINDOW_FONT(TMutTag, TButton, MutFont)*/

MutTag::MutTag(wxWindow *parent, const wxPoint& pos,
               int isLogic, int isOpen, int key, const wxString& text)
		: wxWindow(parent, CM_MUTTAG, pos, MutTagSize)
{
	/*  int Types[4] = { IDI_TONSYST, IDI_LOGIC, IDI_TONSYSTOPEN, IDI_LOGICOPEN};
	  Attr.Style |= BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS
				 | WS_GROUP | WS_TABSTOP;
	  Icon = new TIcon(GetModule()->GetInstance(), (TResId)Types[isLogic + 2*isOpen]);*/
	SetBackgroundColour(*wxWHITE);

	const char  ** TagIcon[4] = {
	                                    tonesyst_xpm, logic_xpm, tonesystopen_xpm, logicopen_xpm
	                            };

	Icon = wxIcon(TagIcon[isLogic + 2*isOpen]);
	Text = text;
	TPos = -1;
	IsLogic = isLogic;
	Key = key;

//TODO  Attr.AccelTable = IDA_MUTWIN;
}

void MutTag::InitText(wxDC& dc)

{
	int i = Text.Length();
	wxCoord w, h;
	dc.GetTextExtent(Text, &w, &h);

	if ( w <= MUTTAGX-4 ) TPos = 0;

	while ( i >= 0 ) {
		if ( Text[i] == '_' ) {
			Text[i] = '-';
			if ( TPos == -1 ) {
				dc.GetTextExtent(Text.Left(i+1), &w, &h);
				if ( w <= MUTTAGX-4 ) TPos = i+1;
			}
		}

		i--;
	}

	if ( TPos == -1 ) TPos = 0;

	dc.GetTextExtent(Text.Mid(TPos), &w, &h);

	if ( w > MUTTAGX-4 )
		Text.Last() = '.';

	dc.GetTextExtent(Text.Mid(TPos), &w, &h);

	int l = Text.Length();

	while ( w > MUTTAGX-4 ) {
		l--;
		Text.Truncate(l);
		Text.Last() = '.';
		dc.GetTextExtent(Text.Mid(TPos), &w, &h);
	}
}

void MutTag::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	dc.SetMapMode(wxMM_TEXT);
	// evtl. erst noch Abteilung des Textes berechnen

	if ( TPos == -1 ) InitText(dc);

	// Selected-Rahmen
	wxPen SelPen(*wxBLACK, 1, wxDOT);

	if ( wxWindow::FindFocus() == this )
		dc.SetPen(SelPen);
	else
		dc.SetPen(*wxWHITE_PEN);

	if ( TPos )
		dc.DrawRectangle(1, 3, MUTTAGX-6, MUTTAGY-3);
	else
		dc.DrawRectangle(1, 3, MUTTAGX-6, MUTTAGY-6);

	dc.SetPen(wxNullPen);

	// Icon zeichnen
	dc.DrawIcon(Icon, MUTTAGX/2-16, 10);

	// Taste auf Icon
	dc.SetBackgroundMode(wxTRANSPARENT);

	PaintCenteredText(dc, wxString::Format(_T("%c"), Key), 20);

	dc.SetBackgroundMode(wxSOLID);

	// Beschriftung
	if ( TPos ) {
		PaintCenteredText(dc, Text.Mid(0, TPos), 44);
		PaintCenteredText(dc, Text.Mid(TPos), 56);
	} else
		PaintCenteredText(dc, Text, 50);

	/*  // Focus
	  if (drawInfo.itemState & ODS_FOCUS)
	  	 dc.DrawFocusRect(TRect(MUTTAGX/2-19, 7, MUTTAGX/2+19, 7+38));*/
}

/*void TMutTag::ODADrawEntire(DRAWITEMSTRUCT far& drawInfo)
{
  TDC dc(drawInfo.hDC);
  // evtl. erst noch Abteilung des Textes berechnen
  if ( TPos == -1 ) InitText(dc);
  // Selected-Rahmen
  if (drawInfo.itemState & ODS_SELECTED)
	   SelectObject(drawInfo.hDC, GetStockObject(BLACK_PEN));
  else
	   SelectObject(drawInfo.hDC, GetStockObject(WHITE_PEN));
  if ( TPos )
	   dc.Rectangle(TRect(1, 3, MUTTAGX-3, MUTTAGY));
  else
	   dc.Rectangle(TRect(1, 3, MUTTAGX-3, MUTTAGY-3));
  dc.RestorePen();
  // Icon zeichnen
  dc.DrawIcon(MUTTAGX/2-16, 10, *Icon);
  // Taste auf Icon
  dc.SetBkMode(TRANSPARENT);
  char s[20];
  sprintf(s, "%c", Key);
  dc.DrawText(s, -1, TRect(MUTTAGX/2-10, 20, MUTTAGX/2+10, 20+14), DT_CENTER | DT_VCENTER);
  dc.SetBkMode(OPAQUE);
  // Beschriftung
  if ( TPos )
  {
  	 dc.DrawText(Text, TPos, TRect(2, 44, MUTTAGX-2, 44+14), DT_CENTER | DT_VCENTER);
	   dc.DrawText(&(Text[TPos]), -1, TRect(2, 56, MUTTAGX-2, 56+14), DT_CENTER | DT_VCENTER);
  }
  else
	   dc.DrawText(Text, -1, TRect(2, 50, MUTTAGX-2, 50+14), DT_CENTER | DT_VCENTER);
  // Focus
  if (drawInfo.itemState & ODS_FOCUS)
  	 dc.DrawFocusRect(TRect(MUTTAGX/2-19, 7, MUTTAGX/2+19, 7+38));
}

void TMutTag::ODAFocus(DRAWITEMSTRUCT far& drawInfo)
{
  TDC dc(drawInfo.hDC);
  dc.DrawFocusRect(TRect(MUTTAGX/2-19, 7, MUTTAGX/2+19, 7+38));
}

void TMutTag::ODASelect(DRAWITEMSTRUCT far& drawInfo)
{
  ODADrawEntire(drawInfo);
}*/

void MutTag::OnChar(wxKeyEvent& event)
{
//  TButton::EvChar(key, repeatCount, flags);

	if ( ('A' < event.GetKeyCode() && event.GetKeyCode() <= 'z') || event.GetKeyCode() == WXK_TAB || event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_SPACE )
		wxPostEvent(GetParent(),event);
}

void MutTag::OnLeftDown(wxMouseEvent& event)
{
	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_MUTTAG);
	event1.SetEventObject(this);
	//((MutLogicWnd*)GetParent())->UpDate(GetKey(), GetIsLogic());
	wxPostEvent(GetParent(),event1);
	event.Skip();
}

void MutTag::OnFocus(wxFocusEvent& event)
{
	Refresh();
	((MutLogicWnd*)GetParent())->CorrectScroller();
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
	EVT_CHAR(MutLogicWnd::OnChar)
	EVT_SIZE(MutLogicWnd::OnSize)
	EVT_MENU(CM_MUTTAG, MutLogicWnd::CmMutTag)
	EVT_CLOSE(MutLogicWnd::OnClose)
END_EVENT_TABLE()

MutLogicWnd::MutLogicWnd(wxWindow *parent,
                         int box,

                         const wxPoint& pos,
                         const wxSize& size)
		: wxScrolledWindow(parent, -1, pos, size, wxHSCROLL | wxVSCROLL | wxTAB_TRAVERSAL)
{

	DEBUGLOG(other,_T("box %d"), box);
	boxnumber = box;
	ColorBar1 = 0;
	ColorBar2 = 0;

	BoxData & boxdata = BoxData::GetBox(box);
	wxASSERT(!boxdata.GetLogicWindow());
	boxdata.SetLogicWindow(this);

	SetScrollRate( 10, 10 );
//	SetBackgroundColour(*wxWHITE);
	SetBackgroundColour(BoxColor(box));
	Ok = false;
	CmBox();
}


void MutLogicWnd::doClose(wxEvent& event)
{
	DEBUGLOG (other, _T(""));
	wxWindow * parent;
	bool stop;
	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);

	if ( (stop = (NumberOfOpen(WK_LOGIC) <= 1) ) ) {
		parent = GetParent();

		while (!(dynamic_cast<MutFrame *>(parent))) {
			DEBUGLOG (other, _T("Searching for MutFrame: %p..."),parent);
			parent = parent->GetParent();
		}

		//GetApplication()->GetMainWindow()->PostMessage(WM_COMMAND, CM_STOP);
	}

	//    delete winAttr;
	event.Skip(false);

	Destroy();

	DEBUGLOGBASE(other,"MutLogicWnd",_T("Destroyed Window"));

	if (stop) wxPostEvent(parent,event1);

	DEBUGLOGBASE(other,"MutLogicWnd",_T("Destroyed Window"));
}


// Reaktion auf Computertastatur

void MutLogicWnd::OnChar(wxKeyEvent& event)
{
	pubTaste = event.GetKeyCode();
	CmTaste();
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

		if ( w && w->GetId() == CM_MUTTAG )
			UpDate(((MutTag*)w)->GetKey(), ((MutTag*)w)->GetIsLogic());
	} else {
		// Buchstabentaste
		// Umwandeln in Groﬂbuchstaben

		if ( 'a' <= key && key <= 'z' ) key += 'A' - 'a';

		// ermiteln, ob Logik
		char isLogic = IsLogicKey((char)key);

		if ( isLogic == 2 ) return;

		// Update aufrufen
		UpDate(key, isLogic);
	}
}

void MutLogicWnd::OnSize(wxSizeEvent& event)
{
	//  wxScrolledWindow::EvSize(sizeType, size);
	event.Skip();
	DoLayout();
}

#define max(a, b) ((a) < (b) ? (b) : (a))

void MutLogicWnd::DoLayout()
{
	wxSize R = GetClientSize();
	int nx = (R.GetWidth()-4) / MUTTAGX, ny = (R.GetHeight()-4)/ MUTTAGY;
	bool quer = R.GetWidth() > R.GetHeight();

	if ( nx * ny < nTags ) // Scroller notwendig
	{

		if  ( ny < 1) ny = 1;

		if ( quer ) nx = (nTags + ny -1) / ny;
	}
	std::cout << nTags << nx << std::endl;

	if  ( nx < 1 ) nx = 1;

	ny = (nTags + nx -1) / nx;

	int x = 4, y = 4, xi = 0;

	std::cout << nx << MUTTAGX << ny << MUTTAGY << std::endl;

	SetVirtualSize(nx*MUTTAGX+8, ny*MUTTAGY+8);

	int xv, yv;

	GetViewStart(&xv, &yv);

	for (wxWindowList::iterator i = GetChildren().begin(); i!=GetChildren().end(); i++) {
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
};

// Reaktion auf geklickte TMutTag-s

void MutLogicWnd::CmMutTag(wxCommandEvent& event)
{
	MutTag *Tag = (MutTag*)event.GetEventObject();
	UpDate(Tag->GetKey(), Tag->GetIsLogic());
}

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

// keyboardanalyse, Fenster aufr‰umen, Logiken lesen und anzeigen
void MutLogicWnd::UpDate(int thekey, bool isLogicKey)
{
	// Analyse zuerst
	KeyboardAnalyse(boxnumber, thekey, isLogicKey);
        BoxData & box = BoxData::GetBox(boxnumber);
        if (isLogicKey) {
                box.SetKeyTonesystem(0);
                box.SetKeyLogic(thekey);
        }
	wxWindow *ToFocus = NULL;

	// alte TMutTag-s lˆschen
        //* \todo we must reuse old entries rendering can be expensive
	DestroyChildren();

	// neue erstellen
	char isLogic, s[200], s1[200], key, isOpen;

	wxString sText, sEinst;
	wxWindow *aWin;
	nTags = 0;

	if ( GetMutTag(isLogic, s, s1, key, boxnumber) )
		do {
			nTags++;
			sText = muT(s);
			sEinst = muT(s1);

			if ( (isOpen = (key == thekey)) != 0 ) {
				if ( isLogic ) {
					box.SetLogic(sText);

					if ( !sEinst.IsEmpty() )
						box.SetTonesystem(sEinst);
					else if ( box.GetTonesystem().empty() )
						box.SetTonesystem(_("(INITIAL)"));
					else if ( box.GetTonesystem()[0] != '[' )
						box.SetTonesystem(
                                                        _T("[")
                                                        + box.GetTonesystem()
                                                        + _T("]")
                                                        );
				} else
					box.SetTonesystem(sText);
                        }

			aWin = new MutTag(this, wxDefaultPosition, isLogic, isOpen, key, sText);

			if ( isOpen ) ToFocus = aWin;
		} while ( GetMutTag(isLogic, s, s1, key) );

	// Color Bars
	if ( UseColorBars ) {
		wxColour BarColor = BoxColor(boxnumber);
		ColorBar1 = new wxWindow(this, -1, wxPoint(0, 0), wxSize(2,2));
		ColorBar1->SetBackgroundColour(BarColor);
		ColorBar1->Disable();
		ColorBar2 = new wxWindow(this, -1, wxPoint(0, 0), wxSize(2,2));
		ColorBar2->SetBackgroundColour(BarColor);
		ColorBar2->Disable();
	} else {
		ColorBar1 = 0;
		ColorBar2 = 0;
	}

	// neue TMutTag-s aktivieren
	//CreateChildren();
	// Fokus setzen
#if 0
	if ( !ToFocus )
		ToFocus = GetChildren().GetFirst()->GetData();
#endif

	if ( ToFocus && FindFocus() != ToFocus)
		ToFocus->SetFocus();

	// Tags anordnen
	DoLayout();

	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED,
			      CM_UPDATEUI);
	GetParent()->GetEventHandler()->ProcessEvent(event1);
	Ok = true;
}

// Reaktion auf neues aktuelles Instrument
void MutLogicWnd::CmBox()
{
	DEBUGLOG (other, _T("%s at box %d"),CompiledFile.c_str(),boxnumber );
	// Titel setzen
	GetParent()->SetName(wxString::Format(_("Logic: %s - Box %d"),
	                                      CompiledFile.c_str(), boxnumber));
	// Tags updaten
	UpDate(0, true);
}

/*
void MutLogicWnd::EvRButtonDown(uint, TPoint& point)
{
  RightButtonMenu(this, point);
}*/


///\}
