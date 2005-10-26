/////////////////////////////////////////////////////////////////////////////
// Name:        Action.cpp
// Purpose:     Actions at UI
// Author:      R. Krauﬂe
// Modified by:
// Created:     01.09.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef MUTROUTEWND_H
#define MUTROUTEWND_H

#include <wx/scrolwin.h>
#include "EDevice.h"

#define xz 5 // Zwischenr‰ume
#define yz 5

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enth‰lt

class MutRouteWnd : public wxScrolledWindow
{
  public:
	MutRouteWnd(wxWindow *parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
/*    void RePaint();
    int FocusPos[2];
  private:
	wxString FileName;
    int nTags;*/
    int x1, x2, x3, x4, x5;
    wxIcon *DevIcon[4];
    wxBitmap *ConIcon[4];
    wxIcon *PlopIcon[4];
  public:
	virtual void OnDraw(wxDC& dc);
	void OnSize(wxSizeEvent& event);
	/*  protected:
    virtual void SetupWindow();
    virtual bool CanClose();
	virtual void EvChar(uint key, uint repeatCount, uint flags);
	void CorrectScroller();
    void SetFocusPos();*/
    int CalcXl() { return x1+x2+x3+x4+x5+10*xz; }
    int CalcYl();
    bool CheckPoint(wxPoint point, EDevice **in, ERoute **r, int &token, bool &needNew);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftDClick(wxMouseEvent &event);
/*    void EvLButtonDblClk(UINT modKeys, TPoint& point);
    void EvRButtonDown(uint modKeys, TPoint& point);*/
  public:
   	DECLARE_EVENT_TABLE()
};

extern bool LogicOn;

wxColor BoxColor(int nr);

#endif