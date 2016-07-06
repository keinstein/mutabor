/** \file 
 ********************************************************************
 * wxRadioValidator
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
// Name:        valradio.cpp
// Purpose:     
// Author:      Rüdiger Krauße
// Modified by:
// Created:     20/04/2004
/////////////////////////////////////////////////////////////////////////////


// For compilers that support precompilation, includes "wx.h".
#include "src/kernel/Defs.h"

#if wxUSE_VALIDATORS

#ifndef WX_PRECOMP
#include <stdio.h>
#include "wx/radiobut.h"
#include "wx/utils.h"
#include "wx/msgdlg.h"
#include "wx/intl.h"
#endif

#include "valRadio.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

//#ifdef __GNUG__
//#pragma implementation "valRadio.h"
//#endif

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

{}

// Called when the value in the window must be validated.
bool wxRadioValidator::Validate(wxWindow* WXUNUSED(parent))
{
	return TRUE;
}

// Called to transfer data to the window
bool wxRadioValidator::TransferToWindow(void)
{
	if ( !CheckValidator() )
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
	if ( !CheckValidator() )
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

///\}
