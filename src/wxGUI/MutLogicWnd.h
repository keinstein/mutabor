/** \file           -*- C++ -*-
 ********************************************************************
 * Logic window
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/MutLogicWnd.h,v 1.13 2011/11/02 14:31:59 keinstein Exp $
 * Copyright:   (c) 2005 TU Dresden
 * \author  R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 * $Log: MutLogicWnd.h,v $
 * Revision 1.13  2011/11/02 14:31:59  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.12  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.11  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.10  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
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


	class MutLogicWnd : public wxScrolledWindow
	{

	private:
		void DoLayout();
		bool Ok;
		int nTags;
		wxWindow *ColorBar1, *ColorBar2;
		int boxnumber;

	public:

		MutLogicWnd(wxWindow *parent, 	int box, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

		~MutLogicWnd()
		{
			mutaborGUI::BoxData & boxdata = mutaborGUI::BoxData::GetBox(boxnumber);
			boxdata.SetLogicWindow(NULL);
			DEBUGLOG(other, _T("Finished"));
		}

		void OnSize(wxSizeEvent& event);

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
		void CorrectScroller();
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
