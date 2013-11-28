/** \file 
 ********************************************************************
 * Validator for numeric text
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
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/
/////////////////////////////////////////////////////////////////////////////
// Name:        valtext.cpp
// Purpose:     wxTextValidator
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: valNum.cpp,v 1.10 2011/11/02 14:32:01 keinstein Exp $
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


// For compilers that support precompilation, includes "wx.h".
#include "src/kernel/Defs.h"

#if wxUSE_VALIDATORS

#ifndef WX_PRECOMP
#include <stdio.h>
#include "wx/textctrl.h"
#include "wx/utils.h"
#include "wx/msgdlg.h"
#include "wx/intl.h"
#endif

#include "valNum.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

IMPLEMENT_DYNAMIC_CLASS(wxNumValidator, wxTextValidator)

/*BEGIN_EVENT_TABLE(wxTextValidator, wxValidator)
    EVT_CHAR(wxTextValidator::OnChar)
END_EVENT_TABLE()
*/
//static bool wxIsNumeric(const wxString& val);

wxNumValidator::wxNumValidator(long *val, int style, int min, int max, wxCheckBox* enabler)
		: wxTextValidator(wxFILTER_NUMERIC, &bufferString)
{
	DEBUGLOG(other,_T("val: %p, style: %d, min: %d, max: %d, enabler: %p"),
	         (void*)val,style,min,max,(void*)enabler);
	Style = style ;
	Min = min;
	Max = max;
	Enabler = enabler;
	m_intValue = val ;
	bufferString = _T("");
	/*
	    m_refData = new wxVTextRefData;

	    M_VTEXTDATA->m_validatorStyle = style ;
	    M_VTEXTDATA->m_stringValue = val ;
	*/
}

wxNumValidator::wxNumValidator(const wxNumValidator& val)
		: wxTextValidator(wxFILTER_NUMERIC, &bufferString)
{
	TRACEC;
	Copy(val);
}

bool wxNumValidator::Copy(const wxNumValidator& val)

{
	DEBUGLOG(other,_T("%p"),(void*)m_stringValue);
	wxTextValidator::Copy(val);
	DEBUGLOG(other,_T("%p"),(void*)m_stringValue);
	m_stringValue = &bufferString;

	Style = val.Style ;
	m_intValue = val.m_intValue ;
	Min = val.Min ;
	Max = val.Max ;
	Enabler = val.Enabler ;

	return TRUE;
}

wxNumValidator::~wxNumValidator()

{
	DEBUGLOG(other,_T("value: %s"),bufferString.c_str());
}

// Called when the value in the window must be validated.
// This function can pop up an error message.
bool wxNumValidator::Validate(wxWindow *parent)
{
	TRACEC;

	if ( !wxTextValidator::Validate(parent) )
		return FALSE;

	wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;

	wxString val(control->GetValue());

	bool ok = TRUE;

	wxString errormsg;

	long i;

	if ( Enabler && !Enabler->GetValue() ) {
		// nix testen
	} else if ( !val.ToLong(&i) ) {
		if ( !Enabler || Enabler->GetValue() ) {
			ok = FALSE;
			errormsg = _("'%s' is not a number.");
		}
	} else if ( (Style & NV_MIN) && i < Min ) {
		ok = FALSE;

		errormsg = _("'%s' is too small.");
	} else if ( (Style & NV_MAX) && i > Max ) {
		ok = FALSE;

		errormsg = _("'%s' is too big.");
	}

	if ( !ok ) {
		wxASSERT_MSG( !errormsg.empty(), _T("you forgot to set errormsg") );

		m_validatorWindow->SetFocus();

		wxString buf;
		buf.Printf(errormsg, val.c_str());

		wxMessageBox(buf, _("Validation conflict"),
		             wxOK | wxICON_EXCLAMATION, parent);
	}

	return ok;
}

// Called to transfer data to the window
bool wxNumValidator::TransferToWindow(void)
{
	TRACEC;

	if ( !CheckValidator() )
		return FALSE;

	if (!m_intValue)
		return TRUE;

	bufferString = wxString::Format(_T("%ld"), *m_intValue);

	m_stringValue = &bufferString;

	return wxTextValidator::TransferToWindow();
}

// Called to transfer data to the window
bool wxNumValidator::TransferFromWindow(void)
{
	TRACEC;

	if ( !CheckValidator() )
		return FALSE;

	if (!m_intValue)
		return TRUE;

	if ( !wxTextValidator::TransferFromWindow() )
		return FALSE;

	bool res = m_stringValue->ToLong(m_intValue);

	DEBUGLOG(other,_T("before enabler"));

	if ( !Enabler || Enabler->GetValue() )
		return res;

	DEBUGLOG(other,_T("after enabler"));

	if ( !res )
		(*m_intValue) = 0;

	if ( (Style & NV_MIN) && (*m_intValue) < Min )
		(*m_intValue) = Min;

	if ( (Style & NV_MAX) && (*m_intValue) > Max )
		(*m_intValue) = Max;

	return true;
}


#endif
// wxUSE_VALIDATORS

///\}

// Local Variables:
// mode: c++
// End:
