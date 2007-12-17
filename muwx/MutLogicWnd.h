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

#include <wx/scrolwin.h>

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enth‰lt

class MutLogicWnd : public wxScrolledWindow
{
  public:
	MutLogicWnd(wxWindow *parent, 	int Kind, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	void OnSize(wxSizeEvent& event);
	void OnClose(wxCloseEvent& event);
	void UpDate(int thekey, bool isLogicKey);
	void CorrectScroller();
	void CmMutTag(wxCommandEvent& event);
	void CmBox();
	void OnChar(wxKeyEvent& event);
	void CmTaste();
  private:
	void DoLayout();
	bool Ok;
	int nTags;
	wxWindow *ColorBar1, *ColorBar2;
	int boxnumber;
  public:
   	DECLARE_EVENT_TABLE()
};

#endif
