/** \file MutChild.h
 ********************************************************************
 * Mutabor Mutabor Child Frame management.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutChild.h,v 1.6 2008/06/30 08:31:21 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/06/30 08:31:21 $
 * \version $Revision: 1.6 $
 * \license wxWindows license
 * 
 * $Log: MutChild.h,v $
 * Revision 1.6  2008/06/30 08:31:21  keinstein
 * removed MutChildren.
 * ~MutChild: outcourcing WinAttrs logic
 * OnClose: removed WinAttrs code
 *
 * Revision 1.5  2008/01/25 09:21:40  keinstein
 * MutChild: Inherit MutTextBox
 * Add EVT_AUI_PANE_CLOSE(MutChild::OnAuiClose) event handler
 * Reduce functionality to management of the window lists.
 * Implement WinKind as enum with (pre- and postfix) operator ++.
 * Removed unused Coordinates from WinAttr.
 * Move CloseAll to MutFrame
 *
 ********************************************************************/

#ifndef MUTCHILD_H
#define MUTCHILD_H

#include <wx/toolbar.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
#include "mhDefs.h"
#include "wx/aui/aui.h"
#include "MutTextBox.h"

enum WinKind { WK_KEY = 0, WK_TS, WK_ACT, WK_LOGIC, WK_ROUTE, WK_EDIT, WK_NULL };

inline WinKind operator++(WinKind & k)
{ return k = WinKind(int(k) + 1); }

inline WinKind operator++(WinKind & k,int)
{ WinKind l=k; ++k; return l; }

/*
typedef int WinKind;
#define WK_KEY 0
#define WK_TS  1
#define WK_ACT 2
#define WK_LOGIC 3
#define WK_ROUTE 4
#define WK_EDIT 5
#define WK_NULL 6
*/

//extern WinKind ActiveWinKind;

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
  //  int X, Y, W, H;     // W = 0 ... noch nicht benutzt, d.h. undefiniert
  int Box;
  WinAttr(char wanted = 0, int box = -1)
    {
      Wanted = wanted;
      Box = box;
      //      X = Y = H = W = 0;
      Win = NULL;
    }
};

WX_DECLARE_OBJARRAY(WinAttr, ArrayOfWinAttr);
//WX_DEFINE_OBJARRAY(ArrayOfWinAttr);

extern ArrayOfWinAttr WinAttrs[WK_NULL];

class MutFrame;

//#ifdef MDI_FORCE_EXTERN
//class MutChild: public wxAuiPaneInfo, private wxObject
//#else
//class MutChild: public wxMDIChildFrame
//#endif

class MutChild: public MutTextBox
{
public:
  WinKind winKind;
  WinAttr *winAttr;
  MutChild (WinKind winkind, 
	    WinAttr *winAttr, 
	    wxWindow * parent= NULL, 
	    wxWindowID id = -1,
	    const wxPoint& pos = wxDefaultPosition,
	    const wxSize & size = wxDefaultSize);
  ~MutChild();

  void OnActivate(wxActivateEvent& event);

//    void OnRefresh(wxCommandEvent& event);
//    void OnUpdateRefresh(wxUpdateUIEvent& event);
//    void OnQuit(wxCommandEvent& event);
//    void OnSize(wxSizeEvent& event);
//    void OnMove(wxMoveEvent& event);

  void deleteFromWinAttrs();

  void OnClose(wxCloseEvent& event) {
#ifdef DEBUG
    std::cerr << "MutChild::OnClose" << std::endl;
#endif
    MutTextBox::OnClose(event);
  }


  void OnAuiClose(wxAuiManagerEvent& event) {
#ifdef DEBUG
    std::cerr << "MutChild::OnAuiClose" << std::endl;
#endif
    deleteFromWinAttrs();
  }

  // Override sizing for drawing the color

  void GetClientSize(int * width, int * height) {
    MutTextBox::GetClientSize(width,height);
    if ((width -= 2) < 0) width = 0;
    if ((height -=2) < 0) height =0; 
  }

  void SetClientSize(int width, int height) {
    MutTextBox::SetClientSize(width+2, height+3);
  }

  void SetClientSize(const wxSize& size) {
    wxSize s = size;
    s.IncBy(2);
    MutTextBox::SetClientSize(s);
  }

  void ClientToScreen(int * x, int * y ) {
    MutTextBox::ClientToScreen(x,y);
    x+=1; y+=1;
  }
  
  wxPoint ClientToScreen(const wxPoint& pt) const{
    return MutTextBox::ClientToScreen(pt)+wxPoint(1,1);
  }

    
//	void MenuPassOn(wxCommandEvent& event);
//	void MenuPassToParent(wxCommandEvent& event);

  DECLARE_EVENT_TABLE()
};

extern int gs_nFrames;

WinAttr* GetWinAttr(WinKind kind, int box = 0);
WinAttr* Get(WinKind kind, int box = 0);
bool IsOpen(WinKind kind, int box = 0);
bool IsWanted(WinKind kind, int box = 0);
void DontWant(WinKind kind, int box = 0);
int NumberOfOpen(WinKind kind);

#endif
