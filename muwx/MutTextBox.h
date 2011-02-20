// -*- C++ -*-
/** \file 
 ********************************************************************
 * Textbox for Lists
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutTextBox.h,v 1.11 2011/02/20 22:35:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/02/20 22:35:57 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 * $Log: MutTextBox.h,v $
 * Revision 1.11  2011/02/20 22:35:57  keinstein
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

#ifndef MUTTEXTBOX_H
#define MUTTEXTBOX_H

#include "wx/listbox.h"
#include "Global.h"
// #include "MutChild.h"

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

WX_DECLARE_OBJARRAY(WinAttr, ArrayOfWinAttr);


class MutTextBox : public wxListBox
{

protected:
	WinKind winKind;
	WinAttr *winAttr;

public:
	MutTextBox(  WinKind k,
	             WinAttr *a,
	             wxWindow* parent = NULL,
	             wxWindowID id=-1,

	             const wxPoint& pos = wxDefaultPosition,
	             const wxSize& size = wxDefaultSize);

	void NewText(char *s, bool newTitle = false);

	void NewText(wxString s, bool newTitle = false);

	int ColorBox;

	void OnClose(wxCloseEvent& event);

	WinKind GetKind()
	{
		return winKind;
	}

protected:

	int Box()
	{
		return winAttr->Box;
	}

	DECLARE_EVENT_TABLE()
};

#endif

///\}
