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

wxList MutChildren;
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
  MutTextBox(parent,id,pos,size)
//#ifdef MDI_FORCE_EXTERN
//       : wxAuiPaneInfo()

//#else
//       : wxMDIChildFrame(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
//                         wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE,title) 
//#endif
{

    MutChildren.Append(this);
    this->winKind = winkind;
    this->winAttr = winAttr;
    winAttr->Win = this;
}

MutChild::~MutChild()
{
    MutChildren.DeleteObject(this);
    size_t i = WinAttrs[winKind].Index(*(this->winAttr));
    WinAttrs[winKind].RemoveAt(i,1);
    //    delete winAttr;
}

void MutChild::OnClose(wxCloseEvent& event)
{
#ifdef DEBUG
  std::cerr << "MutChild::OnClose" << std::endl;
#endif
    MutChildren.DeleteObject(this);
    size_t i = WinAttrs[winKind].Index(*(this->winAttr));
    WinAttrs[winKind][i].Win = NULL;
    WinAttrs[winKind].RemoveAt(i,1);
    //    delete winAttr;
    MutTextBox::OnClose(event);
}

void MutChild::OnAuiClose(wxAuiManagerEvent& event)
{
#ifdef DEBUG
  std::cerr << "MutChild::OnClose" << std::endl;
#endif
    MutChildren.DeleteObject(this);
    size_t i = WinAttrs[winKind].Index(*(this->winAttr));
    WinAttrs[winKind][i].Win = NULL;
    WinAttrs[winKind].RemoveAt(i,1);
    //    delete winAttr;
    //    MutTextBox::OnClose(event);
}

/*void MutChild::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}*/

/*
void MutChild::OnRefresh(wxCommandEvent& WXUNUSED(event))
{
	Refresh();
}


void MutChild::OnActivate(wxActivateEvent& event)
{
    if ( event.GetActive() )
        SetFocus();
}
*/

/*void MutChild::OnMove(wxMoveEvent& event)
{
    // VZ: here everything is totally wrong under MSW, the positions are
    //     different and both wrong (pos2 is off by 2 pixels for me which seems
    //     to be the width of the MDI canvas border)
    wxPoint pos1 = event.GetPosition(),
            pos2 = GetPosition();
    wxLogStatus(wxT("position from event: (%d, %d), from frame (%d, %d)"),
                pos1.x, pos1.y, pos2.x, pos2.y);

    event.Skip();
}

void MutChild::OnSize(wxSizeEvent& event)
{
    // VZ: under MSW the size event carries the client size (quite
    //     unexpectedly) *except* for the very first one which has the full
    //     size... what should it really be? TODO: check under wxGTK
    wxSize size1 = event.GetSize(),
           size2 = GetSize(),
           size3 = GetClientSize();
    wxLogStatus(wxT("size from event: %dx%d, from frame %dx%d, client %dx%d"),
                size1.x, size1.y, size2.x, size2.y, size3.x, size3.y);

    event.Skip();
}*/

/*

void MutChild::MenuPassToParent(wxCommandEvent& event)
{
//	if ( event.GetEventObject() == NULL ) // als Flag zur Sicherheit vor Endlosschleifen
//		return;
//	GetParent()->ProcessEvent(event);
	event.Skip();
}
*/
// TWinAttr ---------------------------------------------------------

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




