/** \file 
 ********************************************************************
 * Logic window
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutLogicWnd.h,v 1.10 2011/02/20 22:35:57 keinstein Exp $
 * Copyright:   (c) 2005 TU Dresden
 * \author  R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/02/20 22:35:57 $
 * \version $Revision: 1.10 $
 * \license GPL
 *
 * $Log: MutLogicWnd.h,v $
 * Revision 1.10  2011/02/20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup muwx
 * \{
 ********************************************************************/


#ifndef MUTLOGICWND_H
#define MUTLOGICWND_H

#include "wx/scrolwin.h"
#include "wx/aui/aui.h"
#include "MutChild.h"

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enth‰lt


class MutLogicWnd : public wxScrolledWindow
{

private:
	WinAttr * winAttr;
	void DoLayout();
	bool Ok;
	int nTags;
	wxWindow *ColorBar1, *ColorBar2;
	int boxnumber;

public:

	MutLogicWnd(wxWindow *parent, 	int box, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	~MutLogicWnd()
	{
		DEBUGLOG(other, _T(""));
		int i = WinAttrs[WK_LOGIC].Index(*winAttr);

		if (i == wxNOT_FOUND) {
			wxLogWarning(_("Subwindow is not in the list anymore. Please report this bug! %s in %s : %d"),__WXFUNCTION__,_T(__FILE__),__LINE__);
			return;
		}

		WinAttrs[WK_LOGIC][i].Win=NULL;

		WinAttrs[WK_LOGIC].RemoveAt(i,1);
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

	DECLARE_EVENT_TABLE()
};

#endif


///\}
