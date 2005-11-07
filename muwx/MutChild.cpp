/////////////////////////////////////////////////////////////////////////////
// Name:        MutChild.cpp
// Purpose:     Mutabor MDI-Child
// Author:      R. Krauße
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauße
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

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


#include "Mutabor.rh"
#include "MutChild.h"
#include "MutEditFile.h"

WX_DEFINE_OBJARRAY(ArrayOfWinAttr);

// ---------------------------------------------------------------------------
// global variables
// ---------------------------------------------------------------------------

wxList MutChildren;
int gs_nFrames = 0;

WinKind ActiveWinKind = WK_NULL;

ArrayOfWinAttr WinAttrs[6] = { ArrayOfWinAttr(), ArrayOfWinAttr(), ArrayOfWinAttr(),
                               ArrayOfWinAttr(), ArrayOfWinAttr(), ArrayOfWinAttr() };

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

// Note that MDI_NEW_WINDOW and MDI_ABOUT commands get passed
// to the parent window for processing, so no need to
// duplicate event handlers here.
BEGIN_EVENT_TABLE(MutChild, wxMDIChildFrame)
//    EVT_MENU(MDI_CHILD_QUIT, MutChild::OnQuit)
	EVT_MENU(CM_COMPILE, MutChild::MenuPassOn)
	EVT_MENU(CM_ACTIVATE, MutChild::MenuPassOn)
//	EVT_MENU(CM_TOGGLEKEY, MutChild::MenuPassToParent)
//    EVT_MENU(MDI_REFRESH, MutChild::OnRefresh)
//    EVT_MENU(MDI_CHANGE_TITLE, MutChild::OnChangeTitle)
//    EVT_MENU(MDI_CHANGE_POSITION, MutChild::OnChangePosition)
//    EVT_MENU(MDI_CHANGE_SIZE, MutChild::OnChangeSize)

//    EVT_SIZE(MutChild::OnSize)
//    EVT_MOVE(MutChild::OnMove)

    EVT_CLOSE(MutChild::OnClose)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================

MutChild::MutChild(wxMDIParentFrame *parent, WinKind winkind, WinAttr *winAttr, const wxString& title)
       : wxMDIChildFrame(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
                         wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE) 
{
    client = (wxWindow *) NULL;
    MutChildren.Append(this);
	this->winKind = winkind;
	this->winAttr = winAttr;
	winAttr->Win = this;
    // this should work for MDI frames as well as for normal ones
    SetSizeHints(100, 100);
}

MutChild::~MutChild()
{
    MutChildren.DeleteObject(this);
}

/*void MutChild::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}*/

void MutChild::OnRefresh(wxCommandEvent& WXUNUSED(event))
{
    if ( client )
        client->Refresh();
}

void MutChild::OnChangePosition(wxCommandEvent& WXUNUSED(event))
{
    Move(10, 10);
}

void MutChild::OnChangeSize(wxCommandEvent& WXUNUSED(event))
{
    SetClientSize(100, 100);
}

void MutChild::OnChangeTitle(wxCommandEvent& WXUNUSED(event))
{
//#if wxUSE_TEXTDLG
    static wxString s_title = _T("Canvas Frame");

    wxString title = wxGetTextFromUser(_T("Enter the new title for MDI child"),
                                       _T("MDI sample question"),
                                       s_title,
                                       GetParent()->GetParent());
    if ( !title )
        return;

    s_title = title;
    SetTitle(s_title);
//#endif
}

void MutChild::OnActivate(wxActivateEvent& event)
{
    if ( event.GetActive() && client )
        client->SetFocus();
}

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

void MutChild::OnClose(wxCloseEvent& event)
{
    if ( client && winKind == WK_EDIT && ((MutEditFile*)client)->IsModified() )
    {
        if ( wxMessageBox(_T("Really close?"), _T("Please confirm"),
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();

            return;
        }
    }

    gs_nFrames--;
	winAttr->Win = NULL;
    event.Skip();
}


void MutChild::MenuPassOn(wxCommandEvent& event)
{
	if ( event.GetEventObject() == NULL ) // als Flag zur Sicherheit vor Endlosschleifen
		return;
	event.SetEventObject(NULL);
	client->ProcessEvent(event);
	event.Skip();
}

void MutChild::MenuPassToParent(wxCommandEvent& event)
{
/*	if ( event.GetEventObject() == NULL ) // als Flag zur Sicherheit vor Endlosschleifen
		return;
	GetParent()->ProcessEvent(event);*/
	event.Skip();
}

// TWinAttr ---------------------------------------------------------

WinAttr* GetWinAttr(WinKind kind, int box)
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

void CloseAll(WinKind kind)
{
  for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
    if ( WinAttrs[kind][i].Win )
    {
      WinAttrs[kind][i].Wanted = 2;
      WinAttrs[kind][i].Win->GetParent()->Close();
	  WinAttrs[kind][i].Win = 0;
    }
}



