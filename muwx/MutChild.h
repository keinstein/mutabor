/////////////////////////////////////////////////////////////////////////////
// Name:        MutChild.h
// Purpose:     Mutabor MDI-Child
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef MUTCHILD_H
#define MUTCHILD_H

#include <wx/toolbar.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!

//enum WinKind { WK_KEY, WK_TS, WK_ACT, WK_LOGIC, WK_ROUTE, WK_EDIT, WK_NULL };

typedef int WinKind;
#define WK_KEY 0
#define WK_TS  1
#define WK_ACT 2
#define WK_LOGIC 3
#define WK_ROUTE 4
#define WK_EDIT 5
#define WK_NULL 6

extern WinKind ActiveWinKind;

#define PARENT_KIND (PARENT->winKind)
#define PARENT_BOX (PARENT->winAttr->Box)
#define PARENT ((MutChild*)GetParent())


//class WinAttr;
//WX_DECLARE_OBJARRAY(WinAttr, ArrayOfWinAttr);

class WinAttr
{
  public:
    wxWindow *Win;  // 0 = nicht offen
    char Wanted;   // 0 = nicht wanted
    int X, Y, W, H;     // W = 0 ... noch nicht benutzt, d.h. undefiniert
    int Box;
    WinAttr(char wanted = 0, int box = -1)
    {
      Wanted = wanted;
      Box = box;
      W = 0;
      Win = 0;
    }
};

WX_DECLARE_OBJARRAY(WinAttr, ArrayOfWinAttr);
//WX_DEFINE_OBJARRAY(ArrayOfWinAttr);

extern ArrayOfWinAttr WinAttrs[6];

class MutChild: public wxMDIChildFrame
{
public:
    wxWindow *client;
	WinKind winKind;
    WinAttr *winAttr;
    MutChild(wxMDIParentFrame *parent, WinKind winKind, WinAttr *winAttr, const wxString& title);
    ~MutChild();

    void OnActivate(wxActivateEvent& event);

    void OnRefresh(wxCommandEvent& event);
    void OnUpdateRefresh(wxUpdateUIEvent& event);
    void OnChangeTitle(wxCommandEvent& event);
    void OnChangePosition(wxCommandEvent& event);
    void OnChangeSize(wxCommandEvent& event);
//    void OnQuit(wxCommandEvent& event);
//    void OnSize(wxSizeEvent& event);
//    void OnMove(wxMoveEvent& event);
    void OnClose(wxCloseEvent& event);
	void MenuPassOn(wxCommandEvent& event);
	void MenuPassToParent(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

extern wxList MutChildren;
extern int gs_nFrames;

WinAttr* GetWinAttr(WinKind kind, int box = 0);
WinAttr* Get(WinKind kind, int box = 0);
bool IsOpen(WinKind kind, int box = 0);
bool IsWanted(WinKind kind, int box = 0);
void DontWant(WinKind kind, int box = 0);
int NumberOfOpen(WinKind kind);
void CloseAll(WinKind kind);

#endif
