/** \file                 -*- C++ -*-
 *
 * Copyright:   (c) 2005,2006,2007-2011 TU Dresden
 *                  changes since 11/2011 Tobias Schlemmer
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 ********************************************************************/

#if (!defined(MUWX_MUT_CHILD_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUT_CHILD_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUT_CHILD_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/generic/mhDefs.h"
#include "src/wxGUI/MutTextBox.h"

#ifndef MUWX_MUT_CHILD_H_PRECOMPILED
#define MUWX_MUT_CHILD_H_PRECOMPILED

#include "wx/toolbar.h"
#include "wx/dynarray.h"
#include "wx/arrimpl.cpp" // this is a magic incantation which must be done!
#include "wx/aui/aui.h"

namespace mutaborGUI {

	struct MutChildApi {
		virtual ~MutChildApi() {}
		virtual wxString MakeTitle() = 0;
		virtual void BoxChanged() = 0;
	};

	class MutChild: public MutTextBox,
			public MutChildApi
	{

	public:
		MutChild (WinKind winkind,
			  mutabor::Box b,
			  wxWindow * parent= NULL,
			  wxWindowID id = -1,

			  const wxPoint& pos = wxDefaultPosition,
			  const wxSize & size = wxDefaultSize);

		~MutChild();

		virtual wxString MakeTitle() {
			return MutTextBox::MakeTitle();
		}

		virtual void BoxChanged();

		void OnActivate(wxActivateEvent& event);

//    void OnRefresh(wxCommandEvent& event);
//    void OnUpdateRefresh(wxUpdateUIEvent& event);
//    void OnQuit(wxCommandEvent& event);
//    void OnSize(wxSizeEvent& event);
//    void OnMove(wxMoveEvent& event);

		void deleteFromWinAttrs(bool setWant = true);

		void OnClose(wxCloseEvent& event)
		{
			DEBUGLOG(aui, "OnClose Event Type %d  Id %d",
				 event.GetEventType(),
				 event.GetId());
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			TRACEC;
			deleteFromWinAttrs();
			MutTextBox::OnClose(event);
		}

#if wxCHECK_VERSION(2,9,4)
		void OnAuiActivate(wxAuiManagerEvent& event)
		{
			mutUnused(event);
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			TRACEC;
			wxActivateEvent e;
			OnActivate(e);
		}
#endif

		void OnAuiClose(wxAuiManagerEvent& event)

		{
			DEBUGLOG(aui, "OnClose Event Type %d  Id %d",
				 event.GetEventType(),
				 event.GetId());
			mutUnused(event);
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			TRACEC;
			deleteFromWinAttrs();
		}

		// Override sizing for drawing the color
#if colour_only_frameborder
		void GetClientSize(int * width, int * height)
		{
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			MutTextBox::GetClientSize(width,height);

			if ((*width += 2) < 0) *width = 0;

			if ((*height += 2) < 0) *height =0;
		}

		void SetClientSize(int width, int height)
		{
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			MutTextBox::SetClientSize(width-2, height-2);
		}

		void SetClientSize(const wxSize& size)
		{
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			wxSize s = size;
			s.IncBy(-2);
			MutTextBox::SetClientSize(s);
		}

		void ClientToScreen(int * x, int * y )

		{
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			MutTextBox::ClientToScreen(x,y);
			x+=1;
			y+=1;
		}

		wxPoint ClientToScreen(const wxPoint& pt) const
		{
			mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
			return MutTextBox::ClientToScreen(pt)+wxPoint(1,1);
		}

#endif
		void OnChar(wxKeyEvent& event);

 		void OnGetFocus(wxFocusEvent& event);

//	void MenuPassOn(wxCommandEvent& event);
//	void MenuPassToParent(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
	};

	bool IsOpen(WinKind kind, mutabor::Box & b);

	bool IsWanted(WinKind kind, mutabor::Box & b);

	void DontWant(WinKind kind, mutabor::Box & b);

	int NumberOfOpen(WinKind kind);
}
#endif
#endif

///\}
