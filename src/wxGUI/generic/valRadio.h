/** \file 
 ********************************************************************
 * wxRadio Validator class
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
/////////////////////////////////////////////////////////////////////////////
// Name:        valradio.h
// Purpose:     wxRadio Validator class
// Author:      Rüdiger Krauße
// Modified by:
// Created:     29/01/98
// RCS-ID:      $Id: valRadio.h,v 1.6 2011/02/20 22:35:59 keinstein Exp $
// Copyright:   (c) 1998 Julian Smart
// Licence:   	wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_VALRADIOH__
#define _WX_VALRADIOH__

//#if defined(__GNUG__) && !defined(__APPLE__)
//#pragma interface "valRadio.h"
//#endif

#include "wx/defs.h"

#if wxUSE_VALIDATORS

#include "wx/validate.h"
#include "wx/radiobut.h"

#define NV_MIN 1
#define NV_MAX 2
#define NV_BOTH 3
#define NV_NNEG 1, 0

class  wxRadioValidator: public wxValidator
{
	DECLARE_DYNAMIC_CLASS(wxRadioValidator)

public:

	wxRadioValidator(int *val = 0, int id = 0);

	wxRadioValidator(const wxRadioValidator& val);

	~wxRadioValidator();

	// Make a clone of this validator (or return NULL) - currently necessary
	// if you're passing a reference to a validator.
	// Another possibility is to always pass a pointer to a new validator
	// (so the calling code can use a copy constructor of the relevant class).
	virtual wxObject *Clone() const
	{
		return new wxRadioValidator(*this);
	}

	bool Copy(const wxRadioValidator& val);

	// Called when the value in the window must be validated.
	// This function can pop up an error message.
	virtual bool Validate(wxWindow *parent);

	// Called to transfer data to the window
	virtual bool TransferToWindow();

	// Called to transfer data to the window
	virtual bool TransferFromWindow();

	/*    // ACCESSORS
	    inline long GetStyle() const { return m_validatorStyle; }
	    inline void SetStyle(long style) { m_validatorStyle = style; }

	    void SetIncludeList(const wxStringList& list);
	    inline wxStringList& GetIncludeList() { return m_includeList; }

	    void SetExcludeList(const wxStringList& list);
	    inline wxStringList& GetExcludeList() { return m_excludeList; }

	    // Filter keystrokes
	    void OnChar(wxKeyEvent& event);

	    bool IsInCharIncludeList(const wxString& val);
	    bool IsNotInCharExcludeList(const wxString& val);

	DECLARE_EVENT_TABLE()
	*/

protected:
	int Id;

	int *m_intValue;

	bool CheckValidator() const
	{
		wxCHECK_MSG( m_validatorWindow, FALSE,
		             _T("No window associated with validator") );
		wxCHECK_MSG( m_validatorWindow->IsKindOf(CLASSINFO(wxRadioButton)), FALSE,
		             _T("wxTextValidator is only for wxRadioButton's") );
		wxCHECK_MSG( m_intValue, FALSE,
		             _T("No variable storage for validator") );

		return TRUE;
	}
};

#endif
// wxUSE_VALIDATORS

#endif
// _WX_VALTEXTH__


///\}
