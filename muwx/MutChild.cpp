/** \file MutChild.h
 ********************************************************************
 * Mutabor Mutabor Child Frame management.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutChild.cpp,v 1.17 2011/09/27 20:13:23 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/09/27 20:13:23 $
 * \version $Revision: 1.17 $
 * \license GPL
 *
 * $Log: MutChild.cpp,v $
 * Revision 1.17  2011/09/27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.16  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.15  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.14  2011-08-21 16:52:05  keinstein
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

#include "Defs.h"
#include <iostream>

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

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutaborGUI;
namespace mutaborGUI {

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
			    int boxId,
			    wxWindow * parent,
			    wxWindowID id,

			    const wxPoint& pos,
			    const wxSize & size):
	MutTextBox(k,boxId,parent,id,pos,size)
	{
		DEBUGLOG (other, _T("winKind=%d"),k);
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		BoxData & boxdata = BoxData::GetBox(boxId);
		switch (k) {
		case WK_KEY: 
			boxdata.SetKeyWindow(this);
			break;
		case WK_TS: 
			boxdata.SetTonesystemWindow(this);
			break;
		case WK_ACT: 
			boxdata.SetActionsWindow(this);
			break;
		case WK_LOGIC:
			wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLEC;
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLEC;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLEC;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLEC;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), k);
			UNREACHABLEC;
		}
		DEBUGLOG (other, _T("winKind=%d"),k);
	}

	MutChild::~MutChild()
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		DEBUGLOG (other, _T(""));
		deleteFromWinAttrs();
	}

	void MutChild::OnActivate(wxActivateEvent& event)
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		DEBUGLOG (other, _T(""));
		mutaborGUI::curBox = box;
	}

	void MutChild::deleteFromWinAttrs()
	{
		DEBUGLOG (other, _T("winKind: %d"),winKind);
	
		BoxData & boxdata = BoxData::GetBox(box);
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		switch (winKind) {
		case WK_KEY: 
			boxdata.SetKeyWindow(NULL);
			break;
		case WK_TS: 
			boxdata.SetTonesystemWindow(NULL);
			break;
		case WK_ACT: 
			boxdata.SetActionsWindow(NULL);
			break;
		case WK_LOGIC:
			wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLEC;
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLEC;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLEC;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLEC;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), winKind);
			UNREACHABLEC;
		}	
	}

	bool IsOpen (WinKind kind, int box)
	{
		wxASSERT(WK_KEY <= kind && kind < WK_NULL);
		wxASSERT(0 <= box && box <= MAX_BOX);

		BoxData & boxdata = BoxData::GetBox(box);
		switch (kind) {
		case WK_KEY: 
			return boxdata.GetKeyWindow();
			break;
		case WK_TS: 
			return boxdata.GetTonesystemWindow();
			break;
		case WK_ACT: 
			return boxdata.GetActionsWindow();
			break;
		case WK_LOGIC:
			return boxdata.GetLogicWindow();
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLE;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLE;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLE;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), kind);
			UNREACHABLE;
		}
		return false;
	}

	bool IsWanted(WinKind kind, int box)
	{
		wxASSERT(WK_KEY <= kind && kind < WK_NULL);
		wxASSERT(0 <= box && box <= MAX_BOX);

		BoxData & boxdata = BoxData::GetBox(box);
		switch (kind) {
		case WK_KEY: 
			return boxdata.WantKeyWindow();
			break;
		case WK_TS: 
			return boxdata.WantTonesystemWindow();
			break;
		case WK_ACT: 
			return boxdata.WantActionsWindow();
			break;
		case WK_LOGIC:
			wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLE;
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLE;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLE;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLE;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), kind);
			UNREACHABLE;
		}	
		return false;
	}

	void DontWant(WinKind kind, int box)
	{
		wxASSERT(WK_KEY <= kind && kind < WK_NULL);
		wxASSERT(0 <= box && box <= MAX_BOX);

		BoxData & boxdata = BoxData::GetBox(box);
		switch (kind) {
		case WK_KEY: 
			boxdata.WantKeyWindow(false);
			break;
		case WK_TS: 
			boxdata.WantTonesystemWindow(false);
			break;
		case WK_ACT: 
			boxdata.WantActionsWindow(false);
			break;
		case WK_LOGIC:
			wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLE;
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLE;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLE;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLE;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), kind);
			UNREACHABLE;
		}	
	}

	int NumberOfOpen(WinKind kind)
	{
		wxASSERT(WK_KEY <= kind && kind < WK_NULL);

		int n = wxNOT_FOUND;
		switch (kind) {
		case WK_KEY:
			n = 0;
			for(size_t i = 0 ; i < MAX_BOX; i++) {
				if (BoxData::GetBox(i).GetKeyWindow()) 
					n++;
			}
			break;
		case WK_TS: 
			n = 0 ;
			for(size_t i = 0 ; i < MAX_BOX; i++) {
				if (BoxData::GetBox(i).GetTonesystemWindow()) 
					n++;
			}
			break;
		case WK_ACT: 
			n = 0 ;
			for(size_t i = 0 ; i < MAX_BOX; i++) {
				if (BoxData::GetBox(i).GetActionsWindow()) 
					n++;
			}
			break;
		case WK_LOGIC:
			n = 0 ;
			for(size_t i = 0 ; i < MAX_BOX; i++) {
				if (BoxData::GetBox(i).GetLogicWindow()) 
					n++;
			}
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLE;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLE;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLE;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), kind);
			UNREACHABLE;
		}	
		return n;
	}



}
