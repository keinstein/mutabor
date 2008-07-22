/////////////////////////////////////////////////////////////////////////////
// Name:        MutChild.cpp
// Purpose:     Mutabor MDI-Child
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include <iostream>
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/mdi.h"
#endif

#include "wx/toolbar.h"

#include "bitmaps/new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/print.xpm"
#include "bitmaps/help.xpm"


//#include "Mutabor.rh"
#include "MutChild.h"
#include "MutEditFile.h"
#include "MutFrame.h"


WX_DEFINE_OBJARRAY(ArrayOfWinAttr);

// ---------------------------------------------------------------------------
// global variables
// ---------------------------------------------------------------------------

int gs_nFrames = 0;

//WinKind ActiveWinKind = WK_NULL;

ArrayOfWinAttr WinAttrs[WK_NULL] = { 
  ArrayOfWinAttr(), ArrayOfWinAttr(), ArrayOfWinAttr(),
  ArrayOfWinAttr(), ArrayOfWinAttr(), ArrayOfWinAttr()
};

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

// Note that MDI_NEW_WINDOW and MDI_ABOUT commands get passed
// to the parent window for processing, so no need to
// duplicate event handlers here.
//#ifdef MDI_FORCE_EXTERN
BEGIN_EVENT_TABLE(MutChild, MutTextBox)
//#else
//BEGIN_EVENT_TABLE(MutChild, wxMDIChildFrame)
//#endif
//    EVT_MENU(MDI_CHILD_QUIT, MutChild::OnQuit)
//	EVT_MENU(CM_FILESAVE, MutChild::MenuPassOn)
//	EVT_MENU(CM_COMPILE, MutChild::MenuPassOn)
//	EVT_MENU(CM_ACTIVATE, MutChild::MenuPassOn)
//	EVT_MENU(CM_TOGGLEKEY, MutChild::MenuPassToParent)
//    EVT_MENU(MDI_REFRESH, MutChild::OnRefresh)
//    EVT_MENU(MDI_CHANGE_TITLE, MutChild::OnChangeTitle)
//    EVT_MENU(MDI_CHANGE_POSITION, MutChild::OnChangePosition)
//    EVT_MENU(MDI_CHANGE_SIZE, MutChild::OnChangeSize)

//    EVT_SIZE(MutChild::OnSize)
//    EVT_MOVE(MutChild::OnMove)
EVT_CLOSE(MutChild::OnClose)
EVT_AUI_PANE_CLOSE(MutChild::OnAuiClose)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================

MutChild::MutChild (WinKind winkind, 
		    WinAttr *winAttr, 
		    wxWindow * parent, 
		    wxWindowID id,
		    const wxPoint& pos,
		    const wxSize & size):
MutTextBox(winKind,winAttr,parent,id,pos,size)
//#ifdef MDI_FORCE_EXTERN
//       : wxAuiPaneInfo()

//#else
//       : wxMDIChildFrame(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
//                         wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE,title) 
//#endif
{
    winAttr->Win = this;
}

MutChild::~MutChild()
{
  DEBUGLOG(_T(""));
  deleteFromWinAttrs();
}

void MutChild::OnActivate(wxActivateEvent& event) {
  DEBUGLOG(_T(""));
  curBox = winAttr->Box;
}

void MutChild::deleteFromWinAttrs() {
  DEBUGLOG(_T(""));
  size_t i = WinAttrs[winKind].Index(*(this->winAttr));
  WinAttrs[winKind][i].Win = NULL;
  WinAttrs[winKind].RemoveAt(i,1);
  //    delete winAttr;
}


WinAttr *GetWinAttr(WinKind kind, int box)
{
  if ( kind != WK_EDIT )
    for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
      if ( WinAttrs[kind][i].Box == box )
        return &WinAttrs[kind][i];
  WinAttr *New = new WinAttr(true, box);
  WinAttrs[kind].Add(New);
  return New;
}

WinAttr *Get(WinKind kind, int box)
{
  for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
    if ( WinAttrs[kind][i].Box == box )
      return &WinAttrs[kind][i];
  return 0;
 }

bool IsOpen(WinKind kind, int box)
{
  WinAttr *Help;
  if ( (Help = Get(kind, box)) )
    if ( Help->Win )
      return true;
  return false;
}

bool IsWanted(WinKind kind, int box)
{
  WinAttr *Help;
  if ( (Help = Get(kind, box)) )
    if ( Help->Wanted )
      return true;
  return false;
}

void DontWant(WinKind kind, int box)
{
  WinAttr *Help;
  if ( (Help = Get(kind, box)) )
    Help->Wanted = 0;
}

int NumberOfOpen(WinKind kind)
{
  int n = 0;
  for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
    if ( WinAttrs[kind][i].Win )
      n++;
  return n;
}




