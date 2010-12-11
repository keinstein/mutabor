/////////////////////////////////////////////////////////////////////////////
// Name:        valtext.h
// Purpose:     wxTextValidator class
// Author:      Julian Smart
// Modified by:
// Created:     29/01/98
// RCS-ID:      $Id: valNum.h,v 1.7 2010/12/11 02:10:09 keinstein Exp $
// Copyright:   (c) 1998 Julian Smart
// Licence:   	wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_VALNUMH__
#define _WX_VALNUMH__

/*
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "valNum.h"
#endif
*/

#include "wx/defs.h"

#if wxUSE_VALIDATORS

#include "wx/valtext.h"
#include "wx/checkbox.h"
#include "wx/string.h"

#define NV_MIN 1
#define NV_MAX 2
#define NV_BOTH 3
#define NV_NNEG 1, 0

class wxNumValidator: public wxTextValidator
{
	DECLARE_DYNAMIC_CLASS(wxNumValidator)

protected:
	int Style;
	long *m_intValue;
	wxString bufferString;
	int Min, Max;
	wxCheckBox* Enabler;

public:

	wxNumValidator(long *val = 0, int style = 0, int min = 0, int max = 12, wxCheckBox* enabler = 0);

	wxNumValidator(const wxNumValidator& val);

	~wxNumValidator();

	// Make a clone of this validator (or return NULL) - currently necessary
	// if you're passing a reference to a validator.
	// Another possibility is to always pass a pointer to a new validator
	// (so the calling code can use a copy constructor of the relevant class).
	virtual wxObject *Clone() const
	{
		return new wxNumValidator(*this);
	}

	bool Copy(const wxNumValidator& val);

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

	    bool CheckValidator() const
	    {
	        wxCHECK_MSG( m_validatorWindow, FALSE,
	                     _T("No window associated with validator") );
	        wxCHECK_MSG( m_validatorWindow->IsKindOf(CLASSINFO(wxTextCtrl)), FALSE,
	                     _T("wxTextValidator is only for wxTextCtrl's") );
	        wxCHECK_MSG( m_stringValue, FALSE,
	                     _T("No variable storage for validator") );

	        return TRUE;
	    }
};

#endif
// wxUSE_VALIDATORS

#endif
// _WX_VALTEXTH__

