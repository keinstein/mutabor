/** \file
 ********************************************************************
 * MIDI Input filter configuration dialog
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/InputFilterDlg.cpp,v 1.5 2009/08/10 11:15:46 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007,2008 TU Dresden
 * \author R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/10/21 18:28:56
 * $Date: 2009/08/10 11:15:46 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: InputFilterDlg.cpp,v $
 * Revision 1.5  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.4  2008/08/18 15:07:41  keinstein
 * Changed Input filter dialog to wxResources
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "InputFilterDlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "InputFilterDlg.h"
#include "wx/valgen.h"
#include "valNum.h"

////@begin XPM images
////@end XPM images

/*!
 * InputFilterDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( InputFilterDlg, wxDialog )

/*!
 * InputFilterDlg event table definition
 */

BEGIN_EVENT_TABLE( InputFilterDlg, InputFilterDlgBase )
	EVT_BUTTON( ::wxID_REMOVE, InputFilterDlg::OnRemoveClick )
END_EVENT_TABLE()

/*!
 * InputFilterDlg constructors
 */

InputFilterDlg::InputFilterDlg( wxWindow* parent, DevType t)
		:InputFilterDlgBase(parent)
{
	from = to = 0;
	Type->SetValidator( wxGenericValidator((int*) (& type) ) );
	From->SetValidator( wxNumValidator(& from, NV_NNEG) );
	To->SetValidator( wxNumValidator(& to, NV_NNEG) );

	DEBUGLOG(_T("Type.id:%d"),Type->GetId());
	Type->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED,
	               wxCommandEventHandler( InputFilterDlg::OnRadioboxSelected ),
	               NULL,
	               this );

	SetDeviceType(t);
}

void InputFilterDlg::SetDeviceType(DevType type)
{
	switch (type) {

	case DTGis:
		Type->SetString(RTchannel,_("&box tag"));

		break;

	case DTMidiPort:
		Type->SetString(RTstaff,_("&key range"));

		break;

	case DTMidiFile:
		Type->SetString(RTstaff,_("&track"));

		break;

	case DTNotSet:
		wxLogWarning(_("Unexpected value: DTNotSet"));

		break;

	case DTUnknown:
		break;

	default:
		wxLogError(_("Unexpected device type: %d"), type);
	}

	UpdateLayout(type);
}


/*!
 * Should we show tooltips?
 */

bool InputFilterDlg::ShowToolTips()
{
	return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap InputFilterDlg::GetBitmapResource( const wxString& name )
{
	return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon InputFilterDlg::GetIconResource( const wxString& name )
{
	return wxNullIcon;
}

/*!
 * wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX
 */

void InputFilterDlg::OnRadioboxSelected( wxCommandEvent& event )
{
	UpdateLayout(Type->GetSelection());
	event.Skip();
}

void InputFilterDlg::UpdateLayout(int type)

{
	DEBUGLOG(_T("%d"),type);
	From->Enable(type >=2);
	To->Enable(type >= 2);
	fromlabel->Enable(type >=2);
	tolabel->Enable(type >=2);
	//  TransferDataToWindow();
}

void InputFilterDlg::OnRemoveClick( wxCommandEvent& event )
{
	EndModal(::wxID_REMOVE);
}

///\}

