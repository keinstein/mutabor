/** \file MutChild.h
 ********************************************************************
 * Mutabor Mutabor Child Frame management.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutChild.cpp,v 1.14 2011/08/21 16:52:05 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/08/21 16:52:05 $
 * \version $Revision: 1.14 $
 * \license GPL
 *
 * $Log: MutChild.cpp,v $
 * Revision 1.14  2011/08/21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.13  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

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

#if 0
#include "bitmaps/new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/print.xpm"
#include "bitmaps/help.xpm"
#endif


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

MutChild::MutChild (WinKind k,
                    WinAttr * attr,
                    wxWindow * parent,
                    wxWindowID id,

                    const wxPoint& pos,
                    const wxSize & size):
		MutTextBox(k,attr,parent,id,pos,size)
//#ifdef MDI_FORCE_EXTERN
//       : wxAuiPaneInfo()

//#else
//       : wxMDIChildFrame(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
//                         wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE,title)
//#endif
{
	DEBUGLOG (other, _T("winKind=%d"),winKind);
	wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
	winAttr->Win = this;
	DEBUGLOG (other, _T("winKind=%d"),winKind);
}

MutChild::~MutChild()

{
	wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
	DEBUGLOG (other, _T(""));
	deleteFromWinAttrs();
}

void MutChild::OnActivate(wxActivateEvent& event)
{
	wxASSERT(WK_KEY <= winKind &&winKind < WK_NULL);
	DEBUGLOG (other, _T(""));
	curBox = winAttr->Box;
}

void MutChild::deleteFromWinAttrs()
{
	DEBUGLOG (other, _T("winKind: %d"),winKind);
	wxASSERT(WK_KEY <= winKind &&winKind < WK_NULL);
	int i = WinAttrs[winKind].Index(*winAttr);
	wxASSERT(WK_KEY <= winKind &&i != wxNOT_FOUND);

	if (i == wxNOT_FOUND) {
		wxLogWarning(_("Subwindow is not in the list anymore. Please report this bug! %s in %s : %d"),__WXFUNCTION__,_T(__FILE__),__LINE__);
		return;
	}

	WinAttrs[winKind][i].Win = NULL;

	WinAttrs[winKind].RemoveAt(i,1);
	//    delete winAttr;
}


WinAttr* GetWinAttr (WinKind kind, int box)
{
	wxASSERT(WK_KEY <= kind &&kind < WK_NULL);
	WinAttr * attr;

	if ( kind != WK_EDIT ) {
		attr = Get (kind, box);

		if (attr) return attr;
	}

	attr = new WinAttr(true, box);

	WinAttrs[kind].Add(attr);
	return attr;
}

WinAttr* Get (WinKind kind, int box)
{
	wxASSERT(WK_KEY <= kind && kind < WK_NULL);

	for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
		if ( WinAttrs[kind][i].Box == box )
			return &WinAttrs[kind][i];

	return 0;
}

bool IsOpen (WinKind kind, int box)
{
	wxASSERT(WK_KEY <= kind && kind < WK_NULL);

	WinAttr *Help;

	if ( (Help = Get(kind, box)) )
		if ( Help->Win )
			return true;

	return false;
}

bool IsWanted(WinKind kind, int box)
{
	wxASSERT(WK_KEY <= kind && kind < WK_NULL);

	WinAttr *Help;

	if ( (Help = Get(kind, box)) )
		if ( Help->Wanted )
			return true;

	return false;
}

void DontWant(WinKind kind, int box)
{
	wxASSERT(WK_KEY <= kind && kind < WK_NULL);

	WinAttr *Help;

	if ( (Help = Get(kind, box)) )
		Help->Wanted = 0;
}

int NumberOfOpen(WinKind kind)
{
	wxASSERT(WK_KEY <= kind && kind < WK_NULL);

	int n = 0;

	for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
		if ( WinAttrs[kind][i].Win )
			n++;

	return n;
}




