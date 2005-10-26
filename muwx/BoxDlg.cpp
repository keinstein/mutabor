/////////////////////////////////////////////////////////////////////////////
// Name:        BoxDlg.cpp
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     10/22/05 16:16:24
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "BoxDlg.h"
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

#include "BoxDlg.h"
#include "valNum.h"
#include "valRadio.h"

////@begin XPM images
////@end XPM images

/*!
 * BoxDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( BoxDlg, wxDialog )

/*!
 * BoxDlg event table definition
 */

BEGIN_EVENT_TABLE( BoxDlg, wxDialog )

////@begin BoxDlg event table entries
    EVT_RADIOBUTTON( ID_RADIOBUTTON, BoxDlg::UpdateEnable )

    EVT_RADIOBUTTON( ID_RADIOBUTTON1, BoxDlg::UpdateEnable )

    EVT_RADIOBUTTON( ID_RADIOBUTTON2, BoxDlg::UpdateEnable )

////@end BoxDlg event table entries

END_EVENT_TABLE()

/*!
 * BoxDlg constructors
 */

BoxDlg::BoxDlg( )
{
}

BoxDlg::BoxDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * BoxDlg creator
 */

bool BoxDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin BoxDlg member initialisation
    ctrlBox1 = NULL;
    ctrlBoxNr = NULL;
    ctrlBox2 = NULL;
    ctrlBox3 = NULL;
    ctrlMode = NULL;
////@end BoxDlg member initialisation

////@begin BoxDlg creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end BoxDlg creation
    return TRUE;
}

/*!
 * Control creation for BoxDlg
 */

void BoxDlg::CreateControls()
{    
////@begin BoxDlg content construction
    BoxDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Box"));
    wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static, wxVERTICAL);
    itemBoxSizer4->Add(itemStaticBoxSizer5, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer5->Add(itemBoxSizer6, 0, wxGROW|wxALL, 0);

    ctrlBox1 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON, _("Box number"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlBox1->SetValue(FALSE);
    itemBoxSizer6->Add(ctrlBox1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    ctrlBoxNr = new wxTextCtrl( itemDialog1, ID_TEXTCTRL10, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemBoxSizer6->Add(ctrlBoxNr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    ctrlBox2 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON1, _("GUIDO-file"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlBox2->SetValue(FALSE);
    itemStaticBoxSizer5->Add(ctrlBox2, 0, wxGROW|wxALL, 5);

    ctrlBox3 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON2, _("no box / thru mode"), wxDefaultPosition, wxDefaultSize, 0 );
    ctrlBox3->SetValue(FALSE);
    itemStaticBoxSizer5->Add(ctrlBox3, 0, wxGROW|wxALL, 5);

    wxString ctrlModeStrings[] = {
        _("&active"),
        _("&passive")
    };
    ctrlMode = new wxRadioBox( itemDialog1, ID_RADIOBOX1, _("Mode"), wxDefaultPosition, wxDefaultSize, 2, ctrlModeStrings, 1, wxRA_SPECIFY_ROWS );
    itemBoxSizer4->Add(ctrlMode, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer12, 0, wxALIGN_TOP|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton15, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Set validators
    ctrlBox1->SetValidator( wxRadioValidator(& Type, 0) );
    ctrlBoxNr->SetValidator( wxNumValidator(& BoxNr, NV_NNEG) );
    ctrlBox2->SetValidator( wxRadioValidator(& Type, 1) );
    ctrlBox3->SetValidator( wxRadioValidator(& Type, 2) );
    ctrlMode->SetValidator( wxGenericValidator(& Mode) );
////@end BoxDlg content construction
}

/*!
 * Should we show tooltips?
 */

bool BoxDlg::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap BoxDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin BoxDlg bitmap retrieval
    return wxNullBitmap;
////@end BoxDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon BoxDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin BoxDlg icon retrieval
    return wxNullIcon;
////@end BoxDlg icon retrieval
}
/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON
 */

void BoxDlg::UpdateEnable( wxCommandEvent& event )
{
    ctrlBoxNr->Enable(ctrlBox1->GetValue());
    ctrlMode->Enable(!ctrlBox3->GetValue());
////@begin wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON in BoxDlg.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON in BoxDlg. 
}


