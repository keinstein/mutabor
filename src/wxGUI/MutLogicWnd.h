/** \file           -*- C++ -*-
 ********************************************************************
 * Logic window
 *
 * Copyright:   (c) 2005 TU Dresden
 *               Changes after 10/2011 Tobias Schlemmer
 * \author  R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.13 $
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
 * \addtogroup src/wxGUI
 * \{
 ********************************************************************/

#if (!defined(MUWX_MUTLOGICWND_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTLOGICWND_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTLOGICWND_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutChild.h"
#include "src/wxGUI/GUIBoxData.h"

#ifndef MUWX_MUTLOGICWND_H_PRECOMPILED
#define MUWX_MUTLOGICWND_H_PRECOMPILED


#include "wx/scrolwin.h"
#include "wx/aui/aui.h"

namespace mutaborGUI {

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enth‰lt


	class MutLogicWnd : public wxScrolledWindow, public MutChildApi
	{

	private:
//		void DoLayout();
		bool Ok;
		int nTags;
		wxWindow *ColorBar1, *ColorBar2;
		int boxnumber;

	public:

		MutLogicWnd(wxWindow *parent, 
			    int box, 
			    const wxPoint& pos = wxDefaultPosition, 
			    const wxSize& size = wxDefaultSize);

		~MutLogicWnd()
		{
			mutaborGUI::BoxData & boxdata = mutaborGUI::BoxData::GetBox(boxnumber);
			boxdata.SetLogicWindow(NULL);
			DEBUGLOG(other, _T("Finished"));
		}

		virtual wxString MakeTitle();

		void OnSize(wxSizeEvent& event);
		void FixSizer();

		void OnClose(wxCloseEvent& event)
		{
			doClose(event);
		}

		void OnAuiClose(wxAuiManagerEvent& event)
		{
			doClose(event);
		}

		void doClose(wxEvent& event);
		void UpDate(int thekey, bool isLogicKey);
//		void CorrectScroller();
		void CmMutTag(wxCommandEvent& event);
		void CmBox();
		void OnChar(wxKeyEvent& event);
		void CmTaste();
		void OnActivate(wxActivateEvent& event);
		void OnGetFocus(wxFocusEvent& event);


		DECLARE_EVENT_TABLE()
	};
}
#endif
#endif


///\}
