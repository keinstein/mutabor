/////////////////////////////////////////////////////////////////////////////
// Name:        InputFilterDlg.cpp
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     10/21/05 18:28:56
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

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

BEGIN_EVENT_TABLE( InputFilterDlg, wxDialog )

////@begin InputFilterDlg event table entries
    EVT_RADIOBOX( ID_RADIOBOX, InputFilterDlg::OnRadioboxSelected )

    EVT_BUTTON( wxID_REMOVE, InputFilterDlg::OnRemoveClick )

////@end InputFilterDlg event table entries

END_EVENT_TABLE()

/*!
 * InputFilterDlg constructors
 */

InputFilterDlg::InputFilterDlg( )
{
}

InputFilterDlg::InputFilterDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * InputFilterDlg creator
 */

bool InputFilterDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin InputFilterDlg member initialisation
    ctrlType = NULL;
    ctrlFrom = NULL;
    ctrlTo = NULL;
////@end InputFilterDlg member initialisation

////@begin InputFilterDlg creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end InputFilterDlg creation
    return TRUE;
}

/*!
 * Control creation for InputFilterDlg
 */

void InputFilterDlg::CreateControls()
{    
////@begin InputFilterDlg content construction
    InputFilterDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxString ctrlTypeStrings[] = {
        _("&all"),
        _("&else"),
        _("&channel"),
        _("&stuff")
    };
    ctrlType = new wxRadioBox( itemDialog1, ID_RADIOBOX, _("Type"), wxDefaultPosition, wxDefaultSize, 4, ctrlTypeStrings, 1, 0 );
    itemBoxSizer4->Add(ctrlType, 0, wxGROW|wxALL, 0);

    wxStaticBox* itemStaticBoxSizer6Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Range"));
    wxStaticBoxSizer* itemStaticBoxSizer6 = new wxStaticBoxSizer(itemStaticBoxSizer6Static, wxHORIZONTAL);
    itemBoxSizer4->Add(itemStaticBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("from"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer6->Add(itemStaticText7, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxADJUST_MINSIZE, 5);

    ctrlFrom = new wxTextCtrl( itemDialog1, ID_TEXTCTRL6, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemStaticBoxSizer6->Add(ctrlFrom, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemDialog1, wxID_STATIC, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer6->Add(itemStaticText9, 0, wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 5);

    ctrlTo = new wxTextCtrl( itemDialog1, ID_TEXTCTRL7, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemStaticBoxSizer6->Add(ctrlTo, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5);

    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer11, 0, wxALIGN_TOP|wxALL, 5);

    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_REMOVE, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton15, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Set validators
    ctrlType->SetValidator( wxGenericValidator(& Type) );
    ctrlFrom->SetValidator( wxNumValidator(& From, NV_NNEG) );
    ctrlTo->SetValidator( wxNumValidator(& To, NV_NNEG) );
////@end InputFilterDlg content construction
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
    // Bitmap retrieval
////@begin InputFilterDlg bitmap retrieval
    return wxNullBitmap;
////@end InputFilterDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon InputFilterDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin InputFilterDlg icon retrieval
    return wxNullIcon;
////@end InputFilterDlg icon retrieval
}
/*!
 * wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX
 */

void InputFilterDlg::OnRadioboxSelected( wxCommandEvent& event )
{
    int type = ctrlType->GetSelection();
    ctrlFrom->Enable(type >=2);
    ctrlTo->Enable(type >= 2);
////@begin wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX in InputFilterDlg.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX in InputFilterDlg. 
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void InputFilterDlg::OnRemoveClick( wxCommandEvent& event )
{
    EndModal(wxID_REMOVE);
}


