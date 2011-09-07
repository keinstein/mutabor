/** \file
 ********************************************************************
 * Mutabor Mutabor Child Frame management.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutChild.h,v 1.13 2011/09/07 13:06:50 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/09/07 13:06:50 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 * $Log: MutChild.h,v $
 * Revision 1.13  2011/09/07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.12  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.11  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.9.2.3  2010-06-15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.9.2.2  2010/06/02 11:20:08  keinstein
 * Route.h:
 * 	new enum BoxType
 * 	new box type NewBox
 *
 * IconShape.cpp:
 * 	Hide shape in MutIconShape::DeleteSelf
 *
 * MutChild.h:
 * 	Changes on the increment value for Clientsize
 *
 * MutLogicWnd:
 * 	smaller whitespace fixes
 *
 * MutRouteWnd.cpp:
 * 	save sizerflags for MutBoxShape too
 *
 * BoxChannelShape.cpp:
 * 	rename CreateRouteShape to CreateRoutePanel
 * 	replace some wxDynamicCast by dynamic_cast
 * 	add Box “New Box“ if current box is not found
 * 	delete Route if route panel is disabled
 *
 * BoxChannelShape.h:
 * 	Update BoxShape layout  if necessary
 *
 * BoxDlg.cpp:
 * 	RoutePanel::AddBox: allow NULL boxShape
 * 	Fix Bug that didn't preselect GUIDO boxes and Through mode
 *
 * BoxShape.cpp:
 * 	fix color mapping for box numbers (shift right by 1 bit).
 * 	Add MutBoxShape::sizerFlags
 * 	SetBoxId: New function
 * 	Use SetBoxId for setting Box Id an Label in sync
 * 	AddChannel: call Layout()
 * 	implement replacement in DoLeftDblClick (enables New Box)
 * 	ShowBoxDialog: use dynamic_cast
 * 	ReadDialog: Add Channel only if new route is enabled (not deleted)
 * 	ReplaceSelfBy: new function (Unreachable as only needed for
 * 		class NewMutBoxShape)
 *
 * NewBoxShape.cpp/.h:
 * 	replaceSelfBy: new function
 * 	initialize Box id as NewBox
 *
 * *.po/mutabor.pot/ *.gmo
 *  	Sync with sources
 *
 * Revision 1.9.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.10  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.9  2008/10/01 09:32:49  keinstein
 * fixed inclution for XCode build
 *
 * Revision 1.8  2008/08/01 16:24:30  keinstein
 * Fix some segfaults on stopping Mutabor
 *
 * Revision 1.7  2008/07/21 09:10:54  keinstein
 * changed parent signalling according to current window loayout
 * moved WinAttr
 *
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

#include "wx/toolbar.h"
#include "wx/dynarray.h"
#include "wx/arrimpl.cpp" // this is a magic incantation which must be done!
#include "mhDefs.h"
#include "wx/aui/aui.h"
#include "MutTextBox.h"


class MutFrame;

class MutChild: public MutTextBox
{

public:
	MutChild (WinKind winkind,
	          int boxId,
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

	void OnClose(wxCloseEvent& event)
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		DEBUGLOG(other,_T(""));
		MutTextBox::OnClose(event);
	}


	void OnAuiClose(wxAuiManagerEvent& event)

	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		DEBUGLOG(other,_T(""));
		deleteFromWinAttrs();
	}

	// Override sizing for drawing the color

	void GetClientSize(int * width, int * height)
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		MutTextBox::GetClientSize(width,height);

		if ((width += 2) < 0) width = 0;

		if ((height +=2) < 0) height =0;
	}

	void SetClientSize(int width, int height)
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		MutTextBox::SetClientSize(width-2, height-3);
	}

	void SetClientSize(const wxSize& size)
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		wxSize s = size;
		s.IncBy(-2);
		MutTextBox::SetClientSize(s);
	}

	void ClientToScreen(int * x, int * y )

	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		MutTextBox::ClientToScreen(x,y);
		x+=1;
		y+=1;
	}

	wxPoint ClientToScreen(const wxPoint& pt) const
	{
		wxASSERT(WK_KEY <= winKind && winKind < WK_NULL);
		return MutTextBox::ClientToScreen(pt)+wxPoint(1,1);
	}


//	void MenuPassOn(wxCommandEvent& event);
//	void MenuPassToParent(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

bool IsOpen(WinKind kind, int box = 0);

bool IsWanted(WinKind kind, int box = 0);

void DontWant(WinKind kind, int box = 0);

int NumberOfOpen(WinKind kind);

#endif

///\}
