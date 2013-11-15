// -*- C++ -*-
/** \file 
 ********************************************************************
 * Textbox for Lists
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  R. Krauﬂe
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
 *
 ********************************************************************
 * \addtogroup src/wxGUI
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

#include "src/kernel/Defs.h"
//#include "src/kernel/Global.h"
#include "src/kernel/routing/Box.h"
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

class MutTextBox : public wxListBox,
		   public mutabor::BoxClass::ChangedCallback
{

public:
	MutTextBox(  WinKind k,
	             mutabor::Box & b,
	             wxWindow* parent = NULL,
	             wxWindowID id=-1,

	             const wxPoint& pos = wxDefaultPosition,
	             const wxSize& size = wxDefaultSize);

	void UpdateUI(wxCommandEvent& event);

	/**
	 * Handle box updates from ChangedCallback
	 *
	 * \param flags flags what has changed.
	 */
	void BoxChangedAction(int flags);


	/**
	 * Handle action messages from ChangedCallback
	 *
	 * \param action action that shall be executed.
	 */
	void BoxChangedAction(const char * a);

	/**
	 * Get the string describing the current key configuration of our box.
	 *
	 * This function collects key data from the box of the object and updates the corresponding list.
	 *
	 * \param asTS bool if true frequencies will be shown as absolute cents otherwise relative to the previous key.
	 */
	void GetKeys(bool asTS);

	/**
	 * Update data to match the current tone system.
	 *
	 * \param asTS bool if true frequencies will be shown as absolute cents otherwise relative to the previous key.
	 */
	void GetToneSystem(bool asTS);

	/**
	 * Update date to match the list of all actions executed at sometime in any box.
	 *
	 */

	void GetAllActions();


	/**
	 * Update date to match the list of all actions executed at sometime in one fixed box.
	 *
	 */
	void GetBoxActions();

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
	WinKind winKind;
	mutabor::Box box;
	bool Ok;


	mutabor::Box Box()
	{
		return box;
	}

	DECLARE_EVENT_TABLE()
};

#endif // precompiled
#endif // header loaded

///\}
