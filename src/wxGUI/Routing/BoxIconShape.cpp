// -*-C++ -*-
/** \file
 ********************************************************************
 * Box icon shape for route window.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
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
 ********************************************************************
 *\addtogroup GUIroute
 *\{
 ********************************************************************/
#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/BoxIconShape.h"
#include "wx/dc.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"


namespace mutaborGUI {
	void MutBoxIconShape::GetBordersForSizer(int &borderTop, int &borderOther) const
	{
		wxSize s = DoGetBestSize();
		DEBUGLOG (other, _T("Best Size: %dx%d"),s.x,s.y);
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

#if __WXMSW__ 
		if (wxWindow::FindFocus() == this) {
			// MSW doesn't allow to change the border
			for (int i = 0 ; i < maxBorderSize.x - 1 ; i++) {
				dc.DrawLine(i,i,size.width-i,i);
				dc.DrawLine(i,size.height-i,size.width-i,size.height-i);
			}
			for (int i = 0 ; i < maxBorderSize.y - 1 ; i++) {
				dc.DrawLine(size.width-i,i,size.width-i,size.height-i);
				dc.DrawLine(i,i,i,size.height-i);
			}
		}
#endif 


		y += borderOffset.y;
		if (staticText) y += staticText->GetSize().y;
		if (GetIcon().IsOk()) {
			DEBUGLOG (other, _T("Size: %dx%d"),GetIcon().GetHeight(),
				  GetIcon().GetWidth());
			x = (size.width-GetIcon().GetWidth())/2;
#ifdef __WXMAC__ 
			x -= maxBorderSize.x - borderOffset.x;
#endif
			dc.DrawIcon(GetIcon(), x, y);
		}
		
		size.width -= 2* borderOffset.x;
		size.height -= 2* borderOffset.y;

#if 0 // done by changing border
		DEBUGLOG (other, _T("Focus %p and this %p"),FindFocus(),this);
		if (FindFocus() == this) {
			DEBUGLOG (other, _T("Painting Box"));
			dc.SetPen(*wxBLACK_PEN);
			dc.SetBrush(*wxTRANSPARENT_BRUSH);
			dc.DrawRectangle(borderOffset.x,
					 borderOffset.y,
					 size.width,
					 size.height);
		}
#endif
	}

	bool MutBoxIconShape::Layout() {
		if (!MutIconShapeClass<MutPanel>::Layout()) return false;
		TRACEC;
		if (staticText) {
			staticText->Move(borderOffset.x,borderOffset.y);
			staticText->CentreOnParent(wxHORIZONTAL);
		}
		return true;
	}

}

/*
 * \}
 */
