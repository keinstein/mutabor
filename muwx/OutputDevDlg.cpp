/////////////////////////////////////////////////////////////////////////////
// Name:        OutputDevDlg.cpp
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     10/19/05 12:10:52
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "OutputDevDlg.h"
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

#include "OutputDevDlg.h"

////@begin XPM images
////@end XPM images

#include "valNum.h"

/*!
 * OutputDevDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( OutputDevDlg, wxDialog )

/*!
 * OutputDevDlg event table definition
 */

BEGIN_EVENT_TABLE( OutputDevDlg, wxDialog )

////@begin OutputDevDlg event table entries
    EVT_CHOICE( ID_CHOICE2, OutputDevDlg::OnChoice2Selected )

    EVT_BUTTON( ID_BUTTON2, OutputDevDlg::OnButton2Click )

    EVT_BUTTON( ID_BUTTON3, OutputDevDlg::OnButton3Click )

    EVT_BUTTON( wxID_REMOVE, OutputDevDlg::OnRemoveClick )

////@end OutputDevDlg event table entries

END_EVENT_TABLE()

/*!
 * OutputDevDlg constructors
 */

OutputDevDlg::OutputDevDlg( )
{
}

OutputDevDlg::OutputDevDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * OutputDevDlg creator
 */

bool OutputDevDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin OutputDevDlg member initialisation
    ctrlPanel = NULL;
    ctrlType = NULL;
    ctrlMidiDevicePanel = NULL;
    ctrlMidiDevice = NULL;
    ctrlMidiFilePanel = NULL;
    ctrlMidiFile = NULL;
    ctrlGUIDOFilePanel = NULL;
    ctrlGUIDOFile = NULL;
////@end OutputDevDlg member initialisation

////@begin OutputDevDlg creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end OutputDevDlg creation
    return TRUE;
}

/*!
 * Control creation for OutputDevDlg
 */

void OutputDevDlg::CreateControls()
{    
////@begin OutputDevDlg content construction
    OutputDevDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    ctrlPanel = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(ctrlPanel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Device Type"));
    wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static, wxHORIZONTAL);
    ctrlPanel->Add(itemStaticBoxSizer5, 0, wxGROW|wxALL, 5);

    wxString ctrlTypeStrings[] = {
        _("Midi Device"),
        _("Midi File"),
        _("GUIDO File")
    };
    ctrlType = new wxChoice( itemDialog1, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 3, ctrlTypeStrings, 0 );
    ctrlType->SetStringSelection(_("Midi Device"));
    itemStaticBoxSizer5->Add(ctrlType, 1, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticBox* itemStaticBoxSizer7Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Midi Device"));
    ctrlMidiDevicePanel = new wxStaticBoxSizer(itemStaticBoxSizer7Static, wxVERTICAL);
    ctrlPanel->Add(ctrlMidiDevicePanel, 0, wxGROW|wxALL, 5);

    wxString* ctrlMidiDeviceStrings = NULL;
    ctrlMidiDevice = new wxChoice( itemDialog1, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, ctrlMidiDeviceStrings, 0 );
    ctrlMidiDevicePanel->Add(ctrlMidiDevice, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    ctrlMidiDevicePanel->Add(itemBoxSizer9, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _("Bending Range"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemBoxSizer9->Add(itemStaticText10, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxTextCtrl* itemTextCtrl11 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL4, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemBoxSizer9->Add(itemTextCtrl11, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxStaticBox* itemStaticBoxSizer12Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Midi File"));
    ctrlMidiFilePanel = new wxStaticBoxSizer(itemStaticBoxSizer12Static, wxVERTICAL);
    ctrlPanel->Add(ctrlMidiFilePanel, 0, wxGROW|wxALL, 5);

    ctrlMidiFile = new wxTextCtrl( itemDialog1, ID_TEXTCTRL2, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlMidiFilePanel->Add(ctrlMidiFile, 0, wxGROW|wxALL, 0);

    wxButton* itemButton14 = new wxButton( itemDialog1, ID_BUTTON2, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlMidiFilePanel->Add(itemButton14, 0, wxALIGN_RIGHT|wxLEFT|wxTOP, 5);

    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    ctrlMidiFilePanel->Add(itemBoxSizer15, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText16 = new wxStaticText( itemDialog1, wxID_STATIC, _("Bending Range"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    itemBoxSizer15->Add(itemStaticText16, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxTextCtrl* itemTextCtrl17 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL5, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemBoxSizer15->Add(itemTextCtrl17, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

    wxStaticBox* itemStaticBoxSizer18Static = new wxStaticBox(itemDialog1, wxID_ANY, _("GUIDO File"));
    ctrlGUIDOFilePanel = new wxStaticBoxSizer(itemStaticBoxSizer18Static, wxVERTICAL);
    ctrlPanel->Add(ctrlGUIDOFilePanel, 0, wxGROW|wxALL, 5);

    ctrlGUIDOFile = new wxTextCtrl( itemDialog1, ID_TEXTCTRL3, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlGUIDOFilePanel->Add(ctrlGUIDOFile, 0, wxGROW|wxALL, 0);

    wxButton* itemButton20 = new wxButton( itemDialog1, ID_BUTTON3, _("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlGUIDOFilePanel->Add(itemButton20, 0, wxALIGN_RIGHT|wxLEFT|wxTOP, 5);

    wxBoxSizer* itemBoxSizer21 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer21, 0, wxALIGN_TOP|wxALL, 5);

    wxButton* itemButton22 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer21->Add(itemButton22, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton23 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer21->Add(itemButton23, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton24 = new wxButton( itemDialog1, wxID_REMOVE, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer21->Add(itemButton24, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton25 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer21->Add(itemButton25, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Set validators
    ctrlType->SetValidator( wxGenericValidator(& Type) );
    ctrlMidiDevice->SetValidator( wxGenericValidator(& MidiDevice) );
    itemTextCtrl11->SetValidator( wxNumValidator(& MidiDeviceBending, NV_BOTH, 0, 12) );
    ctrlMidiFile->SetValidator( wxTextValidator(wxFILTER_NONE, & MidiFile) );
    itemTextCtrl17->SetValidator( wxNumValidator(& MidiFileBending, NV_BOTH, 0, 12) );
    ctrlGUIDOFile->SetValidator( wxTextValidator(wxFILTER_NONE, & GUIDOFile) );
////@end OutputDevDlg content construction
}

/*!
 * Should we show tooltips?
 */

bool OutputDevDlg::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap OutputDevDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin OutputDevDlg bitmap retrieval
    return wxNullBitmap;
////@end OutputDevDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon OutputDevDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin OutputDevDlg icon retrieval
    return wxNullIcon;
////@end OutputDevDlg icon retrieval
}
/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2
 */

void OutputDevDlg::OnChoice2Selected( wxCommandEvent& event )
{
    int type = ctrlType->GetSelection();
    ctrlPanel->Show(ctrlMidiDevicePanel, type == 0, true);
    ctrlPanel->Show(ctrlMidiFilePanel, type == 1, true);
    ctrlPanel->Show(ctrlGUIDOFilePanel, type == 2, true);
    ctrlPanel->Layout();
	GetSizer()->SetSizeHints(this);
	Fit();
////@begin wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2 in OutputDevDlg.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2 in OutputDevDlg. 
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void OutputDevDlg::OnRemoveClick( wxCommandEvent& event )
{
    EndModal(wxID_REMOVE);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
 */

void OutputDevDlg::OnButton2Click( wxCommandEvent& event )
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
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
 */

void OutputDevDlg::OnButton3Click( wxCommandEvent& event )
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


