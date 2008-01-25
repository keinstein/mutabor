/////////////////////////////////////////////////////////////////////////////
// Name:        MutLogicWnd.cpp
// Purpose:     Logic window
// Author:      R. Krauﬂe
// Modified by:
// Created:     01.09.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef MUTLOGICWND_H
#define MUTLOGICWND_H

#include "wx/scrolwin.h"
#include "wx/aui/aui.h"
#include "MutChild.h"

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enth‰lt

class MutLogicWnd : public wxScrolledWindow
{
  private:
	WinAttr * winAttr;
	void DoLayout();
	bool Ok;
	int nTags;
	wxWindow *ColorBar1, *ColorBar2;
	int boxnumber;
  public:
	MutLogicWnd(wxWindow *parent, 	int box, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	~MutLogicWnd() {
	  size_t i = WinAttrs[WK_LOGIC].Index(*(this->winAttr));
	  WinAttrs[WK_LOGIC].RemoveAt(i,1);
	}
	void OnSize(wxSizeEvent& event);
	void OnClose(wxCloseEvent& event) { doClose(event); }
	void OnAuiClose(wxAuiManagerEvent& event) { doClose(event); }
	void doClose(wxEvent& event);
	void UpDate(int thekey, bool isLogicKey);
	void CorrectScroller();
	void CmMutTag(wxCommandEvent& event);
	void CmBox();
	void OnChar(wxKeyEvent& event);
	void CmTaste();

   	DECLARE_EVENT_TABLE()
};

#endif
