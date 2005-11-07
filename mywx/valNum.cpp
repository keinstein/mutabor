/////////////////////////////////////////////////////////////////////////////
// Name:        valtext.cpp
// Purpose:     wxTextValidator
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: valNum.cpp,v 1.4 2005/11/07 14:51:08 keinstein Exp $
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "valNum.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif

#if wxUSE_VALIDATORS

#ifndef WX_PRECOMP
  #include <stdio.h>
  #include "wx/textctrl.h"
  #include "wx/utils.h"
  #include "wx/msgdlg.h"
  #include "wx/intl.h"
#endif

#include "valNum.h"
/*
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#ifdef __SALFORDC__
    #include <clib.h>
#endif
*/
IMPLEMENT_DYNAMIC_CLASS(wxNumValidator, wxTextValidator)

/*BEGIN_EVENT_TABLE(wxTextValidator, wxValidator)
    EVT_CHAR(wxTextValidator::OnChar)
END_EVENT_TABLE()
*/
//static bool wxIsNumeric(const wxString& val);

wxNumValidator::wxNumValidator(long *val, int style, int min, int max, wxCheckBox* enabler)
: wxTextValidator(wxFILTER_NUMERIC, 0) 
{
    Style = style ;
	Min = min;
	Max = max;
	Enabler = enabler;
    m_intValue = val ;
	bufferString = _T("");
	m_stringValue = &bufferString;
/*
    m_refData = new wxVTextRefData;

    M_VTEXTDATA->m_validatorStyle = style ;
    M_VTEXTDATA->m_stringValue = val ;
*/
}

wxNumValidator::wxNumValidator(const wxNumValidator& val)
    : wxTextValidator()
{
    Copy(val);
}

bool wxNumValidator::Copy(const wxNumValidator& val)
{
    wxTextValidator::Copy(val);

    Style = val.Style ;
    m_intValue = val.m_intValue ;
    Min = val.Min ;
    Max = val.Max ;
    Enabler = val.Enabler ;

    return TRUE;
}

wxNumValidator::~wxNumValidator()
{
}

// Called when the value in the window must be validated.
// This function can pop up an error message.
bool wxNumValidator::Validate(wxWindow *parent)
{
    if ( !wxTextValidator::Validate(parent) )
		return FALSE;

    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;
    wxString val(control->GetValue());

    bool ok = TRUE;

    wxString errormsg;

    long i;
	if ( Enabler && !Enabler->GetValue() )
	{
      // nix testen
	}
	else if ( !val.ToLong(&i) ) 
    {
		if ( !Enabler || Enabler->GetValue() )
		{
			ok = FALSE;
			errormsg = _("'%s' ist keine Zahl.");
		}
    }
    else if ( (Style & NV_MIN) && i < Min )
    {
        ok = FALSE;

        errormsg = _("'%s' ist zu klein.");
    }
    else if ( (Style & NV_MAX) && i > Max )
    {
        ok = FALSE;

        errormsg = _("'%s' is too big.");
    }

    if ( !ok )
    {
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
    if( !CheckValidator() )
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
    if( !CheckValidator() )
        return FALSE;

    if (!m_intValue)
        return TRUE;

    if ( !wxTextValidator::TransferFromWindow() )
		return FALSE;

    bool res = m_stringValue->ToLong(m_intValue);
	
	if ( !Enabler || Enabler->GetValue() )
		return res;

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
