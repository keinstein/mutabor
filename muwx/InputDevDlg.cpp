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

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "InputDevDlg.h"
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

#include "InputDevDlg.h"

////@begin XPM images
////@end XPM images

/*!
 * InputDevDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( InputDevDlg, wxDialog )

/*!
 * InputDevDlg event table definition
 */

BEGIN_EVENT_TABLE( InputDevDlg, wxDialog )

////@begin InputDevDlg event table entries
    EVT_CHOICE( ID_CHOICE, InputDevDlg::OnChoiceSelected )

    EVT_BUTTON( ID_BUTTON, InputDevDlg::OnButtonClick )

    EVT_BUTTON( ID_BUTTON1, InputDevDlg::OnButton1Click )

    EVT_BUTTON( wxID_REMOVE, InputDevDlg::OnRemoveClick )

////@end InputDevDlg event table entries

END_EVENT_TABLE()

/*!
 * InputDevDlg constructors
 */

InputDevDlg::InputDevDlg( )
{
}

InputDevDlg::InputDevDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * InputDevDlg creator
 */

bool InputDevDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin InputDevDlg member initialisation
    ctrlPanel = NULL;
    ctrlType = NULL;
    ctrlMidiDevicePanel = NULL;
    ctrlMidiDevice = NULL;
    ctrlMidiFilePanel = NULL;
    ctrlMidiFile = NULL;
    ctrlGUIDOFilePanel = NULL;
    ctrlGUIDOFile = NULL;
////@end InputDevDlg member initialisation

////@begin InputDevDlg creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end InputDevDlg creation
    return TRUE;
}

/*!
 * Control creation for InputDevDlg
 */

void InputDevDlg::CreateControls()
{    
////@begin InputDevDlg content construction
    InputDevDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 1, wxGROW|wxALL, 5);

    ctrlPanel = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(ctrlPanel, 1, wxALIGN_TOP|wxALL, 0);

    wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Device type"));
    wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static, wxHORIZONTAL);
    ctrlPanel->Add(itemStaticBoxSizer5, 0, wxGROW|wxALL, 5);

    wxString ctrlTypeStrings[] = {
        _("Midi Device"),
        _("Midi File"),
        _("GUIDO File")
    };
    ctrlType = new wxChoice( itemDialog1, ID_CHOICE, wxDefaultPosition, wxDefaultSize, 3, ctrlTypeStrings, 0 );
    ctrlType->SetStringSelection(_("Midi Device"));
    itemStaticBoxSizer5->Add(ctrlType, 1, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticBox* itemStaticBoxSizer7Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Device name"));
    ctrlMidiDevicePanel = new wxStaticBoxSizer(itemStaticBoxSizer7Static, wxVERTICAL);
    ctrlPanel->Add(ctrlMidiDevicePanel, 0, wxGROW|wxALL, 5);

    wxString* ctrlMidiDeviceStrings = NULL;
    ctrlMidiDevice = new wxChoice( itemDialog1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, ctrlMidiDeviceStrings, 0 );
    ctrlMidiDevicePanel->Add(ctrlMidiDevice, 1, wxGROW|wxALL, 0);

    wxStaticBox* itemStaticBoxSizer9Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Midi File name"));
    ctrlMidiFilePanel = new wxStaticBoxSizer(itemStaticBoxSizer9Static, wxVERTICAL);
    ctrlPanel->Add(ctrlMidiFilePanel, 0, wxGROW|wxALL, 5);

    ctrlMidiFile = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlMidiFilePanel->Add(ctrlMidiFile, 1, wxGROW|wxALL, 0);

    wxButton* itemButton11 = new wxButton( itemDialog1, ID_BUTTON, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlMidiFilePanel->Add(itemButton11, 0, wxALIGN_RIGHT|wxLEFT|wxTOP, 5);

    wxStaticBox* itemStaticBoxSizer12Static = new wxStaticBox(itemDialog1, wxID_ANY, _("GUIDO File name"));
    ctrlGUIDOFilePanel = new wxStaticBoxSizer(itemStaticBoxSizer12Static, wxVERTICAL);
    ctrlPanel->Add(ctrlGUIDOFilePanel, 0, wxGROW|wxALL, 5);

    ctrlGUIDOFile = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlGUIDOFilePanel->Add(ctrlGUIDOFile, 1, wxGROW|wxALL, 0);

    wxButton* itemButton14 = new wxButton( itemDialog1, ID_BUTTON1, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlGUIDOFilePanel->Add(itemButton14, 0, wxALIGN_RIGHT|wxLEFT|wxTOP, 5);

    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer15, 0, wxALIGN_TOP|wxALL, 5);

    wxButton* itemButton16 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton17 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton17, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton18 = new wxButton( itemDialog1, wxID_REMOVE, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton18, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton19 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton19, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Set validators
    ctrlType->SetValidator( wxGenericValidator(& Type) );
    ctrlMidiDevice->SetValidator( wxGenericValidator(& MidiDevice) );
    ctrlMidiFile->SetValidator( wxTextValidator(wxFILTER_NONE, & MidiFile) );
    ctrlGUIDOFile->SetValidator( wxTextValidator(wxFILTER_NONE, & GUIDOFile) );
////@end InputDevDlg content construction
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
////@begin InputDevDlg bitmap retrieval
    return wxNullBitmap;
////@end InputDevDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon InputDevDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin InputDevDlg icon retrieval
    return wxNullIcon;
////@end InputDevDlg icon retrieval
}
/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void InputDevDlg::OnChoiceSelected( wxCommandEvent& event )
{
    UpdateLayout(ctrlType->GetSelection());
////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE in InputDevDlg.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE in InputDevDlg. 
}

void InputDevDlg::UpdateLayout(int type)
{
    ctrlPanel->Show(ctrlMidiDevicePanel, type == 0, true);
    ctrlPanel->Show(ctrlMidiFilePanel, type == 1, true);
    ctrlPanel->Show(ctrlGUIDOFilePanel, type == 2, true);
    ctrlPanel->Layout();
	GetSizer()->SetSizeHints(this);
	Fit();
}
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void InputDevDlg::OnButtonClick( wxCommandEvent& event )
{
	wxString OldFileName;
	if ( !ctrlMidiFile->GetValue().empty() )
		OldFileName = ctrlMidiFile->GetValue();
    wxString NewFileName = wxFileSelector(_("Select Midi-File file"),
		_T(""), OldFileName, _T(""), _("Midi-file (*.mid*)|*.mid*|All files (*.*)|*.*"), wxOPEN | wxFILE_MUST_EXIST);
    if ( !NewFileName.empty() )
		ctrlMidiFile->SetValue(NewFileName);
    event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void InputDevDlg::OnRemoveClick( wxCommandEvent& event )
{
    EndModal(wxID_REMOVE);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void InputDevDlg::OnButton1Click( wxCommandEvent& event )
{
	wxString OldFileName;
	if ( !ctrlMidiFile->GetValue().empty() )
		OldFileName = ctrlMidiFile->GetValue();
    wxString NewFileName = wxFileSelector(_("Select Midi-File file"),
		_T(""), OldFileName, _T(""), _("GUIDO-file (*.gmn)|*.gmn|All files (*.*)|*.*"), wxOPEN | wxFILE_MUST_EXIST);
    if ( !NewFileName.empty() )
		ctrlMidiFile->SetValue(NewFileName);
    event.Skip();
}


