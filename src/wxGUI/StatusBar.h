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

#if (!defined(WXGUI_STATUSBAR) && !defined(PRECOMPILE)) \
	|| (!defined(WXGUI_STATUSBAR_PRECOMPILED))
#ifndef PRECOMPILE
#define WXGUI_STATUSBAR
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutBitmaps.h"

#ifndef WXGUI_STATUSBAR_PRECOMPILED
#define WXGUI_STATUSBAR_PRECOMPILED

// system headers which do seldom change
#include "wx/statusbr.h"
#include "wx/stattext.h"
#include "wx/statbmp.h"
#include "wx/frame.h"
#include "wx/window.h"

namespace mutaborGUI {
	class StatusBar: public wxStatusBar {
	public:
		enum playstate {
			Hide,
			Stop,
			Pause,
			Play
		};


		StatusBar(wxWindow* parent, 
			  wxWindowID id = wxID_ANY, 
			  long style = wxST_SIZEGRIP, 
			  const wxString& name = _T("statusBar")):wxStatusBar(),
							      insertStatus(NULL),
							      active(NULL),
							      play(NULL),
							      line(-1),
							      column(-1) {
			Create (parent,id,style,name);
		}

		bool Create(wxWindow* parent, 
			    wxWindowID id = wxID_ANY, 
			    long style = wxST_SIZEGRIP, 
			    const wxString& name = _T("statusBar")) {
			StatusBarBitmaps::Init();
			bool retval = wxStatusBar::Create (parent,id,style,name);
			if (!retval) return false;
			SetFieldsCount(countStatusbarRegions);
			return true;
		}

		static void SetInsert(wxWindow * win,bool status) {
			StatusBar * bar = GetStatusBar(win);
			if (!bar) return;
			if (!bar->insertStatus) {
				bar->insertStatus = 
					new wxStaticText(bar,wxID_ANY,_("INS"));
				bar->PositionElements();
			}
			if (!bar->insertStatus) return;
			bar -> insertStatus->Enable(status);
		}

		static void SetPosition (wxWindow * win, int line, int column) {
			StatusBar * bar = GetStatusBar(win);
			if (!bar) return;
			if (bar->line == line && bar->column == column)
				// don't waste time for rendering the position
				return; 
			
			bar -> line = line;
			bar -> column = column;
			wxString tmp = _T("");
			if (line >= 0) tmp << line;
			if (column >= 0) tmp << _T(":") << column;
			bar->SetStatusText(tmp,StatusbarLineNo);
		}

		static void AllSetActive(bool active) {
			for (wxWindowList::iterator i = wxTopLevelWindows.begin();
			     i != wxTopLevelWindows.end(); i++) {
				wxFrame * win = dynamic_cast<wxFrame *>(*i);
				if (!win) continue;
				StatusBar * bar = dynamic_cast<StatusBar*>(win->GetStatusBar());
				if (!bar) continue;
				bar->SetActive(active);
			}
		}

		void SetActive(bool act) {
			if (!active && StatusBarBitmaps::Active.IsOk()) {
				active = new wxStaticBitmap(this,wxID_ANY, StatusBarBitmaps::Active);
				//DEBUGLOG(gui,_("Created active: %p"),bar->active);
				PositionElements();
			}
			if (!active) return;
			active->Show(act);
		}


		static void AllSetPlaystate(playstate pst = Stop, bool force = false) {
			static playstate oldpst = Hide;
			if (force) {
				AllDoSetPlaystate(pst);
				return;
			}
			if (pst == oldpst) return;
			switch (pst) {
			case Play:
			case Hide:
				oldpst = pst;
				AllDoSetPlaystate(pst);
				return;
				break;
			case Pause:
				if (oldpst == Stop) {
					oldpst = pst;
					AllDoSetPlaystate(pst);
					return;
				}
				break;
			case Stop:
				break;
			default:
				UNREACHABLECT(StatusBar);
				return;
			}
			playstate newpst = GetCurrentPlayState();
			if (newpst == oldpst) return;
			oldpst = newpst;
			AllDoSetPlaystate(newpst);
		}

		void SetPlaystate(playstate pst) {
			wxBitmap * bmp = NULL;
			switch (pst) {
			case Hide:
			case Stop: 
				bmp = &StatusBarBitmaps::Stop;
				break;
			case Pause: 
				bmp = &StatusBarBitmaps::Pause;
				break;
			case Play: 
				bmp = &StatusBarBitmaps::Play;
				break;
			default:
				UNREACHABLEC;
				return;
			}
			if (playbmp != bmp && bmp->IsOk()) {
				if (!play)
					play = new wxStaticBitmap(this,wxID_ANY, *bmp);
				else 
					play->SetBitmap(*bmp);
				//DEBUGLOG(gui,_("Created active: %p"),bar->active);
				PositionElements();
			}
			if (play)
				play->Show(pst != Hide);
		}

		

	protected:
		wxStaticText * insertStatus;
		wxStaticBitmap * active, *play;
		wxBitmap * playbmp;
		
		enum StatusBarSections {
			StatusbarInfoArea = 0,
			StatusbarLineNo,
			StatusbarInsert,
			StatusbarPlayback,
			StatusbarLogicActive,
			StatusbarSizeGrip,
			countStatusbarRegions
		};

		int line, column;

		static StatusBar * GetStatusBar(wxWindow * win) {
			if (!win) return NULL;
			wxFrame * frame;
			while (win && !(frame = dynamic_cast<wxFrame *>(win)))
				win = win -> GetParent();
			if (!win) return NULL;
			return dynamic_cast<StatusBar *>(frame->GetStatusBar());
		}


		void OnSize(wxSizeEvent& event);
		void PositionElements();
		
		static void AllDoSetPlaystate(playstate pst) {
			for (wxWindowList::iterator i = wxTopLevelWindows.begin();
			     i != wxTopLevelWindows.end(); i++) {
				wxFrame * win = dynamic_cast<wxFrame *>(*i);
				if (!win) continue;
				StatusBar * bar = dynamic_cast<StatusBar*>(win->GetStatusBar());
				if (!bar) continue;
				bar->SetPlaystate(pst);
			}
		}

		static playstate GetCurrentPlayState();

		DECLARE_EVENT_TABLE()
	};
}


#endif // precompiled
#endif // header loaded


///\}
