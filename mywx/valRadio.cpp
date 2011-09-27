/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/valRadio.cpp,v 1.5 2011/09/27 20:13:26 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:26 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: valRadio.cpp,v $
 * Revision 1.5  2011/09/27 20:13:26  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
/////////////////////////////////////////////////////////////////////////////
// Name:        valradio.cpp
// Purpose:     wxRadioValidator
// Author:      Rüdiger Krauße
// Modified by:
// Created:     20/04/2004
/////////////////////////////////////////////////////////////////////////////


// For compilers that support precompilation, includes "wx.h".
#include "Defs.h"

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
