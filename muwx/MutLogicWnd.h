/** \file 
 ********************************************************************
 * Logic window
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutLogicWnd.h,v 1.11 2011/09/07 13:06:50 keinstein Exp $
 * Copyright:   (c) 2005 TU Dresden
 * \author  R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/09/07 13:06:50 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 * $Log: MutLogicWnd.h,v $
 * Revision 1.11  2011/09/07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.10  2011-02-20 22:35:57  keinstein
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

	DECLARE_EVENT_TABLE()
};

#endif


///\}
