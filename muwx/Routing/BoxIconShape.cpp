// -*-C++ -*-
/** \file
 ********************************************************************
 * Box icon shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxIconShape.cpp,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: BoxIconShape.cpp,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-03-30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.cpp,v
 * Revision 1.1.2.3  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
//#include "Defs.h"
//#include "wx/wx.h"
#include "BoxIconShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"



void MutBoxIconShape::GetBordersForSizer(int &borderTop, int &borderOther) const
{
	const int BORDER = 5; // FIXME: hardcoded value

	wxSize s = DoGetBestSize();
	DEBUGLOG (other, _T("Best Size: %dx%d"),s.x,s.y);
	/*	if (GetIcon().IsOk()) {
		s.x = std::max (GetIcon().GetWidth(), s.x);
		s.y += GetIcon().GetHeight();
		}
		return s;
	*/
	borderTop = s.y;
	borderOther = 0;
}

void MutBoxIconShape::OnDraw (wxDC & dc) 
{
	DEBUGLOG (other, _T("Checking icon"));

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG (other, _T("Checking icon again"));

	}
	DEBUGLOG (other, _T("Icon ok."));

	int x, y;
	x = 0;
	y = 0;
	wxRect size = GetRect();
	if (staticText) y += staticText->GetSize().y;
	if (GetIcon().IsOk()) {
		DEBUGLOG (other, _T("Size: %dx%d"),GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
		dc.DrawIcon(GetIcon(), x, y);
	}

	DEBUGLOG (other, _T("Focus %p and this %p"),FindFocus(),this);
	if (FindFocus() == this) {
		DEBUGLOG (other, _T("Painting Box"));
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(0,0,size.width,size.height);
	}
}

bool MutBoxIconShape::Layout() {
	if (!MutIconShape::Layout()) return false;
	DEBUGLOG (other, _T(""));
	if (staticText) {
		staticText->Move(0,0);
		staticText->CentreOnParent(wxHORIZONTAL);
	}
	return true;
}



/*
 * \}
 */
