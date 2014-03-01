/** \file               -*- C++ -*-
 ********************************************************************
 * Status bar.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:26 $
 * \version $Version$
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
 *
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#include "src/wxGUI/StatusBar.h"
#include "src/kernel/routing/Box.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/event.h"
// system headers which do seldom change

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutaborGUI {
	BEGIN_EVENT_TABLE(StatusBar, wxStatusBar)
	EVT_MENU(CM_PLAYSTATE_CHANGED,StatusBar::HandlePlaystateChanged)
	EVT_SIZE(StatusBar::OnSize)
	END_EVENT_TABLE()

	StatusBar::playstate StatusBar::lastprocessed=StatusBar::Stop;

	void StatusBar::OnSize(wxSizeEvent& event)
	{
		PositionElements();
		event.Skip();
	}

	void StatusBar::PositionElements()
	{
		wxRect rect;
		wxSize size = GetSize(), border = GetWindowBorderSize();
		DEBUGLOG(gui, _T("Size: %dx%d, Border: %d,%d"),size.x,size.y,border.x,border.y);
		if (!border.x) border.x = 2;
		int widths[countStatusbarRegions] = { -1, 0, 0, 0, 0, 0 };
		widths[StatusbarSizeGrip] = size.GetHeight();
		widths[StatusbarLineNo] = 4*size.GetHeight();
		if (insertStatus) {
			widths[StatusbarInsert] = insertStatus->GetBestSize().GetWidth()+
				2*border.x+2;
			DEBUGLOG(gui,_T("INS width = %d"),widths[StatusbarInsert]);
			
		}
		if (active) {
			widths[StatusbarLogicActive] = active->GetBestSize().GetWidth() +
			       2*border.x+2;
			DEBUGLOG(gui,_T("Logic width = %d"),widths[StatusbarLogicActive]);
			
		}
		if (play) {
			widths[StatusbarPlayback] = play->GetBestSize().GetWidth() +
			       2*border.x+2;
			DEBUGLOG(gui,_T("Play width = %d"),widths[StatusbarPlayback]);
			
		}
		SetFieldsCount(countStatusbarRegions, widths);
		if (insertStatus) {
			if (GetFieldRect(StatusbarInsert,rect)) {
				rect.Deflate(border.x);
				insertStatus->SetSize(rect);
			}
		}
		if (active) {
			if (GetFieldRect(StatusbarLogicActive,rect)) {
				rect.Deflate(border.x);
				active->SetSize(rect);
			}
		}
		if (play) {
			if (GetFieldRect(StatusbarPlayback,rect)) {
				rect.Deflate(border.x);
				play->SetSize(rect);
			}
		}

	}

	StatusBar::playstate StatusBar::GetCurrentPlayState() {
		typedef mutabor::InputDeviceClass::listtype listtype;
		playstate retval = Stop;
		const listtype & list = mutabor::InputDeviceClass::GetDeviceList();
		for (listtype::const_iterator i = list.begin();
		     i != list.end();
		     i++) {
			mutabor::MutaborModeType mode = (*i)->GetMode();
			switch (mode) {
			case mutabor::DevicePlay:
				return Play;
			case mutabor::DevicePause:
				retval = Pause;
				break;
			case mutabor::DeviceUnregistered:
			case mutabor::DeviceStop:
			case mutabor::DeviceCompileError:
			case mutabor::DeviceTimingError:
			default:
				break;
			}
		}
		return retval;
	}
}



///\}
