/////////////////////////////////////////////////////////////////////////////
// Name:        InputDevDlg.cpp
// Purpose:
// Author:      R. Krauße
// Modified by:
// Created:     10/12/05 14:22:47
// RCS-ID:
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "InputDevDlg.h"

/*!
 * InputDevDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( InputDevDlg, InputDevDlgBase )

BEGIN_EVENT_TABLE( InputDevDlg, InputDevDlgBase )
	EVT_CHOICE( XRCID("DeviceChoice"), InputDevDlg::OnChoiceSelected )
        EVT_BUTTON( ::wxID_REMOVE, InputDevDlg::OnRemoveClick )
        EVT_FILEPICKER_CHANGED(XRCID ("MidiFilePicker"), 
                               InputDevDlg::OnFileChanged)
        EVT_FILEPICKER_CHANGED(XRCID ("GuidoFilePicker"), 
                               InputDevDlg::OnFileChanged)
END_EVENT_TABLE()

/*!
 * InputDevDlg constructors
 */
/* \todo: find out, how we can reuse a file Picker for different file types */

InputDevDlg::InputDevDlg( wxWindow* parent):InputDevDlgBase(parent)
{
	DeviceChoice->Clear();
	DeviceChoice->Append(_("MIDI Device"),new TypeData(DTMidiPort));
	DeviceChoice->Append(_("MIDI file"),new TypeData(DTMidiFile));
	DeviceChoice->Append(_("GUIDO file"),new TypeData(DTGis));

	TypeBox = DeviceChoice->GetContainingSizer();
	PortBox = PortChoice->GetContainingSizer();
	MidiFileBox = MidiFilePicker->GetContainingSizer();
        DEBUGLOG (other,_T ("MidiFilePicker Growable: %d"), MidiFilePicker->IsPickerCtrlGrowable());
        if (MidiFilePicker->HasTextCtrl()) {
                DEBUGLOG (other,_T ("MidiFileTextCtrl Growable: %d"), 
                          MidiFilePicker->IsTextCtrlGrowable());
                MidiFilePicker->SetTextCtrlGrowable(true);
                DEBUGLOG (other,_T ("MidiFileTextCtrl Growable: %d"), 
                          MidiFilePicker->IsTextCtrlGrowable());
        }
	GuidoFileBox = GuidoFilePicker->GetContainingSizer();

//	GetSizer()->Fit(this);
//	GetSizer()->SetSizeHints(this);
//	Centre();
}

/*!
 * Should we show tooltips?
 */

bool InputDevDlg::ShowToolTips()
{
	return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap InputDevDlg::GetBitmapResource( const wxString& name )
{
	// Bitmap retrieval
	return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon InputDevDlg::GetIconResource( const wxString& name )
{
	// Icon retrieval
	return wxNullIcon;
}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void InputDevDlg::OnChoiceSelected( wxCommandEvent& event )
{
	UpdateLayout(GetType());
	event.Skip();
}

void InputDevDlg::UpdateLayout(DevType type)
{
        if (type == DTNotSet) {
                if (FindType (type) == wxNOT_FOUND)
                        DeviceChoice->Insert (_ ("Choose device type"),
                                              0,
                                              new TypeData (type));
        } else {
                int notset = FindType (DTNotSet);
                if (notset != wxNOT_FOUND) {
                        DeviceChoice->Delete (notset);
                }

                if (type == DTUnknown) {
                        if (FindType (type) == wxNOT_FOUND)
                                DeviceChoice->Insert (_ ("Unknown device type"),
                                                      0,
                                                      new TypeData (type));
                }
        }
        int Type = FindType (type);
        DeviceChoice -> SetSelection (Type);

	DEBUGLOG (other, _T("%d"),type);
	wxSizer * sizer = GetSizer();

	DEBUGLOG (other, _T("%d"),DTMidiPort);
	sizer->Show(PortBox, type == DTMidiPort, true);
	DEBUGLOG (other, _T("%d"),DTMidiFile);
	sizer->Show(MidiFileBox, (type == DTMidiFile), true);
	DEBUGLOG (other, _T("%d"),DTGis);
	sizer->Show(GuidoFileBox, (type == DTGis) , true);

        // We need Layout here, since otherwise the input boxex are not
        // shown in certain circumstances
	Layout();
//	GetSizer()->SetSizeHints(this);
	Fit();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void InputDevDlg::OnRemoveClick( wxCommandEvent& event )
{
	EndModal(::wxID_REMOVE);
}

void InputDevDlg::OnFileChanged ( wxFileDirPickerEvent & event ) 
{
        DEBUGLOG (other,_T ("Path changed: %s"),event.GetPath().c_str());
        Fit();
}


int InputDevDlg::FindType (DevType t)
{
        TypeData * Data;
	for (unsigned int i = 0; i < DeviceChoice->GetCount(); i++) {
                DEBUGLOG (other,_T ("Choice #%d of %d"),i, DeviceChoice->GetCount());
                Data = (TypeData *)DeviceChoice->GetClientObject(i);
                if (Data) {
                        if (*Data == t) return i;
                }
        }
	return wxNOT_FOUND;
}
