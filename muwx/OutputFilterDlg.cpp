/////////////////////////////////////////////////////////////////////////////
// Name:        OutputFilterDlg.cpp
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     10/22/05 16:09:37
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "OutputFilterDlg.h"
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

#include "OutputFilterDlg.h"
#include "valNum.h"

////@begin XPM images
////@end XPM images

/*!
 * OutputFilterDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( OutputFilterDlg, wxDialog )

/*!
 * OutputFilterDlg event table definition
 */

BEGIN_EVENT_TABLE( OutputFilterDlg, wxDialog )

////@begin OutputFilterDlg event table entries
////@end OutputFilterDlg event table entries

END_EVENT_TABLE()

/*!
 * OutputFilterDlg constructors
 */

OutputFilterDlg::OutputFilterDlg( )
{
}

OutputFilterDlg::OutputFilterDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * OutputFilterDlg creator
 */

bool OutputFilterDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin OutputFilterDlg member initialisation
////@end OutputFilterDlg member initialisation

////@begin OutputFilterDlg creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end OutputFilterDlg creation
    return TRUE;
}

/*!
 * Control creation for OutputFilterDlg
 */

void OutputFilterDlg::CreateControls()
{    
////@begin OutputFilterDlg content construction
    OutputFilterDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Channel"));
    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer3->Add(itemStaticBoxSizer4, 0, wxALIGN_TOP|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer4->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("from"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText6, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxTextCtrl* itemTextCtrl7 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL8, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemBoxSizer5->Add(itemTextCtrl7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText8, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

    wxTextCtrl* itemTextCtrl9 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL9, _T(""), wxDefaultPosition, wxSize(40, -1), 0 );
    itemBoxSizer5->Add(itemTextCtrl9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox10 = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("avoid drum channel"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    itemCheckBox10->SetValue(FALSE);
    itemStaticBoxSizer4->Add(itemCheckBox10, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer11->Add(itemButton14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Set validators
    itemTextCtrl7->SetValidator( wxNumValidator(& From, NV_NNEG) );
    itemTextCtrl9->SetValidator( wxNumValidator(& To, NV_NNEG) );
    itemCheckBox10->SetValidator( wxGenericValidator(& AvoidDrumChannel) );
////@end OutputFilterDlg content construction
}

/*!
 * Should we show tooltips?
 */

bool OutputFilterDlg::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap OutputFilterDlg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin OutputFilterDlg bitmap retrieval
    return wxNullBitmap;
////@end OutputFilterDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon OutputFilterDlg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin OutputFilterDlg icon retrieval
    return wxNullIcon;
////@end OutputFilterDlg icon retrieval
}
