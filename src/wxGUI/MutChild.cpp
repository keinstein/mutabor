/** \file MutChild.h
 ********************************************************************
 * Mutabor Mutabor Child Frame management.
 *
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * \addtogroup src/wxGUI
 * \{
 ********************************************************************/

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include <iostream>

#include "wx/toolbar.h"
#include "wx/image.h"
#include "wx/log.h"

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
#include "src/wxGUI/MutChild.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/MutEditFile.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutLogicWnd.h"

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
	
	EVT_ACTIVATE(MutChild::OnActivate)
	EVT_SET_FOCUS(MutChild::OnGetFocus)
	EVT_CHAR(MutChild::OnChar)
	EVT_CLOSE(MutChild::OnClose)
	EVT_AUI_PANE_CLOSE(MutChild::OnAuiClose)
	END_EVENT_TABLE()

	// ===========================================================================
	// implementation
	// ===========================================================================

	MutChild::MutChild (WinKind k,
			    mutabor::Box box,
			    wxWindow * parent,
			    wxWindowID id,

			    const wxPoint& pos,
			    const wxSize & size):
	MutTextBox(k,box,parent,id,pos,size)
	{
		DEBUGLOG (other, _T("winKind=%d"),k);
		mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		BoxData * boxdata = ToGUIBase(box);
		switch (k) {
		case WK_KEY: 
			boxdata->SetKeyWindow(this);
			break;
		case WK_TS: 
			boxdata->SetTonesystemWindow(this);
			break;
		case WK_ACT: 
			boxdata->SetActionsWindow(this);
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
		mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		TRACEC;
		deleteFromWinAttrs();
	}

	void MutChild::OnActivate(wxActivateEvent& event)
	{
		if (event.GetActive()) {
			mutUnused(event);
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			TRACEC;
			SetCurrentBox(box);
		}
		event.Skip();
	}

	void MutChild::deleteFromWinAttrs()
	{
		DEBUGLOG (other, _T("winKind: %d"),winKind);
	
		BoxData * boxdata = ToGUIBase(box);
		mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		switch (winKind) {
		case WK_KEY: 
			boxdata->SetKeyWindow(NULL);
			break;
		case WK_TS: 
			boxdata->SetTonesystemWindow(NULL);
			break;
		case WK_ACT: 
			boxdata->SetActionsWindow(NULL);
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

	void MutChild::OnChar(wxKeyEvent& event)
	{
		if ( ('A' < event.GetKeyCode() && event.GetKeyCode() <= 'z') 
		     || event.GetKeyCode() == WXK_TAB 
		     || event.GetKeyCode() == WXK_RETURN 
		     || event.GetKeyCode() == WXK_SPACE ){
			if ((box) && ToGUIBase(box)) {
				MutLogicWnd * logic = ToGUIBase(box)->GetLogicWindow();
				if (logic)
					wxPostEvent(logic->GetEventHandler(),event);
				else {
					UNREACHABLEC;
				}
			}
		}
		else event.Skip();
		
		SetCurrentBox(box);
		mutASSERT(box);
		TRACEC;
	}

	bool IsOpen (WinKind kind, mutabor::Box & box)
	{
		mutASSERT(WK_KEY <= kind && kind < WK_NULL);
		//mutASSERT(0 <= box && box <= MAX_BOX);

		BoxData * boxdata = ToGUIBase(box);
		switch (kind) {
		case WK_KEY: 
			return boxdata->GetKeyWindow() != NULL;
			break;
		case WK_TS: 
			return boxdata->GetTonesystemWindow() != NULL;
			break;
		case WK_ACT: 
			return boxdata->GetActionsWindow() != NULL;
			break;
		case WK_LOGIC:
			return boxdata->GetLogicWindow() != NULL;
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

	bool IsWanted(WinKind kind, mutabor::Box & box)
	{
		mutASSERT(WK_KEY <= kind && kind < WK_NULL);
		BoxData * boxdata = ToGUIBase(box);
		switch (kind) {
		case WK_KEY: 
			return boxdata->WantKeyWindow();
			break;
		case WK_TS: 
			return boxdata->WantTonesystemWindow();
			break;
		case WK_ACT: 
			return boxdata->WantActionsWindow();
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

	void DontWant(WinKind kind, mutabor::Box & box)
	{
		mutASSERT(WK_KEY <= kind && kind < WK_NULL);

		BoxData * boxdata = ToGUIBase(box);
		switch (kind) {
		case WK_KEY: 
			boxdata->WantKeyWindow(false);
			break;
		case WK_TS: 
			boxdata->WantTonesystemWindow(false);
			break;
		case WK_ACT: 
			boxdata->WantActionsWindow(false);
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

#if 0
	int NumberOfOpen(WinKind kind)
	{
		mutASSERT(WK_KEY <= kind && kind < WK_NULL);

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
#endif

	void MutChild::OnGetFocus(wxFocusEvent& event)
	{
		SetCurrentBox(box);
		TRACEC;
		event.Skip();
	}



}
