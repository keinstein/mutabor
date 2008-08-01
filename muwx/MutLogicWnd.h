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
	  DEBUGLOG(_T(""));
	  int i = WinAttrs[WK_LOGIC].Index(*winAttr);
	  if (i == wxNOT_FOUND) {
	    wxLogWarning(_("Subwindow is not in the list anymore. Please report this bug! %s in %s : %d"),__WXFUNCTION__,_T(__FILE__),__LINE__);
	    return;
	  }
	  WinAttrs[WK_LOGIC][i].Win=NULL;
	  WinAttrs[WK_LOGIC].RemoveAt(i,1);
	  DEBUGLOG(_T("Finished"));
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
	void OnActivate(wxActivateEvent& event);

   	DECLARE_EVENT_TABLE()
};

#endif
