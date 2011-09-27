// -*- C++ -*-
/** \file 
 ********************************************************************
 * Textbox for Lists
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutTextBox.h,v 1.14 2011/09/27 20:13:23 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/09/27 20:13:23 $
 * \version $Revision: 1.14 $
 * \license GPL
 *
 * $Log: MutTextBox.h,v $
 * Revision 1.14  2011/09/27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.13  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.12  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.11  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup muwx
 * \{
 ********************************************************************/

#if (!defined(MUWX_MUTTEXTBOX_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTTEXTBOX_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTTEXTBOX_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Global.h"
// #include "MutChild.h"

#ifndef MUWX_MUTTEXTBOX_H_PRECOMPILED
#define MUWX_MUTTEXTBOX_H_PRECOMPILED

#include "wx/listbox.h"

enum WinKind { WK_KEY = 0, WK_TS, WK_ACT, WK_LOGIC, WK_ROUTE, WK_EDIT, WK_NULL };

inline WinKind operator++(WinKind & k)
{
	return k = WinKind(int(k) + 1);
}

inline WinKind operator++(WinKind & k,int)
{
	WinKind l=k;
	++k;
	return l;
}


/*
class WinAttr
{

public:
	wxWindow * Win;  // 0 = nicht offen
	char Wanted;   // 0 = nicht wanted
	//  int X, Y, W, H;     // W = 0 ... noch nicht benutzt, d.h. undefiniert
	int Box;
	WinAttr(char wanted = 0, int box = -1)
	{
		Wanted = wanted;
		Box = box;
		//      X = Y = H = W = 0;
		Win = NULL;
	}
};
*/

class MutTextBox : public wxListBox
{

protected:
	WinKind winKind;
	int box;

public:
	MutTextBox(  WinKind k,
	             int boxId,
	             wxWindow* parent = NULL,
	             wxWindowID id=-1,

	             const wxPoint& pos = wxDefaultPosition,
	             const wxSize& size = wxDefaultSize);

	void UpdateUI(wxCommandEvent& event);

	void NewText(char *s, bool newTitle = false);

	void NewText(const wxString &s, bool newTitle = false);

	wxString MakeTitle() const;

	int ColorBox;

	void OnClose(wxCloseEvent& event);


	WinKind GetKind()
	{
		return winKind;
	}

protected:

	int Box()
	{
		return box;
	}

	DECLARE_EVENT_TABLE()
};

#endif // precompiled
#endif // header loaded

///\}
