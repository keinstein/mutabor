/////////////////////////////////////////////////////////////////////////////
// Name:        valradio.cpp
// Purpose:     wxRadioValidator
// Author:      Rüdiger Krauße
// Modified by:
// Created:     20/04/2004
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "valRadio.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif

#if wxUSE_VALIDATORS

#ifndef WX_PRECOMP
  #include <stdio.h>
  #include "wx/radiobut.h"
  #include "wx/utils.h"
  #include "wx/msgdlg.h"
  #include "wx/intl.h"
#endif

#include "valRadio.h"

IMPLEMENT_DYNAMIC_CLASS(wxRadioValidator, wxValidator)

wxRadioValidator::wxRadioValidator(int *val, int id)
: wxValidator() 
{
    Id = id ;
    m_intValue = val ;
}

wxRadioValidator::wxRadioValidator(const wxRadioValidator& val)
    : wxValidator()
{
    Copy(val);
}

bool wxRadioValidator::Copy(const wxRadioValidator& val)
{
    wxValidator::Copy(val);

    Id = val.Id ;
    m_intValue = val.m_intValue ;

    return TRUE;
}

wxRadioValidator::~wxRadioValidator()
{
}

// Called when the value in the window must be validated.
bool wxRadioValidator::Validate(wxWindow* WXUNUSED(parent))
{
	return TRUE;
}

// Called to transfer data to the window
bool wxRadioValidator::TransferToWindow(void)
{
    if( !CheckValidator() )
        return FALSE;

    if (!m_intValue)
        return TRUE;

    wxRadioButton *control = (wxRadioButton *) m_validatorWindow;
    control->SetValue(*m_intValue == Id) ;

    return TRUE;
}

// Called to transfer data to the window
bool wxRadioValidator::TransferFromWindow(void)
{
    if( !CheckValidator() )
        return FALSE;

    if (!m_intValue)
        return TRUE;

    wxRadioButton *control = (wxRadioButton *) m_validatorWindow;
	if ( control->GetValue() )
		*m_intValue = Id;

    return TRUE;
}


#endif
  // wxUSE_VALIDATORS
