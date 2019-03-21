/** \file 
********************************************************************
* Compile dialog
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/CompDlg.cpp,v 1.7 2011/11/02 14:31:58 keinstein Exp $
* Copyright:   (c) 2005, 2008 TU Dresden
* \author R. Krauße
* Tobias Schlemmer <keinstein@users.sourceforge.net>
* \date 2005/08/14
* $Date: 2011/11/02 14:31:58 $
* \version $Revision: 1.7 $
* \license GPL
*
* $Log: CompDlg.cpp,v $
* Revision 1.7  2011/11/02 14:31:58  keinstein
* fix some errors crashing Mutabor on Windows
*
* Revision 1.6  2011-09-27 20:13:22  keinstein
* * Reworked route editing backend
* * rewireing is done by RouteClass/GUIRoute now
* * other classes forward most requests to this pair
* * many bugfixes
* * Version change: We are reaching beta phase now
*
* Revision 1.5  2011-09-06 08:09:21  keinstein
* fix a compiler error showing a corruped error message
*
* Revision 1.4  2011-02-20 22:35:57  keinstein
* updated license information; some file headers have to be revised, though
*
* Revision 1.2  2010-11-21 13:15:51  keinstein
* merged experimental_tobias
*
* Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
* added some .cvsignore files
*
* \addtogroup GUI
* \{
********************************************************************/

#include "src/kernel/Defs.h"

#include "src/wxGUI/CompDlg.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef DEBUG
int CompDlgSilenceMudflapBuild=0;
#endif


#if 0
/*!
 * CompDlg type definition
 */

using mutaborGUI::CompDlg;
IMPLEMENT_DYNAMIC_CLASS( CompDlg, wxDialog )

/*!
 * CompDlg event table definition
 */

BEGIN_EVENT_TABLE( CompDlg, wxDialog )
END_EVENT_TABLE()
MUTABOR_NAMESPACE(mutaborGUI)

/*!
 * CompDlg constructors
 */

CompDlg::CompDlg( )
{}

CompDlg::CompDlg( wxWindow* parent, 
		  wxWindowID id, 
		  const wxString& caption, 
		  const wxPoint& pos, 
		  const wxSize& size, 
		  long style )
{
	Create(parent, id, caption, pos, size, style);
}

/*!
 * CompDlg creator
 */

bool CompDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
	wxDialog::Create( parent, id, caption, pos, size, style );

	CreateControls();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Centre();
	return TRUE;
}

/*!
 * Control creation for CompDlg
 */

void CompDlg::CreateControls()
{
	CompDlg* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Source"));
	wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
	itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
	itemStaticBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_CENTER_VERTICAL, 5);

	wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("File:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Line:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer4->Add(itemStaticText6, 0, wxALIGN_LEFT|wxRIGHT|wxTOP|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
	itemStaticBoxSizer3->Add(itemBoxSizer7, 1, wxALIGN_CENTER_VERTICAL, 5);

	wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, IDC_COMP_FILENAME, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer7->Add(itemStaticText8, 1, wxGROW|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText9 = new wxStaticText( itemDialog1, IDC_COMP_LINE, _("..."), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer7->Add(itemStaticText9, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

	wxStaticBox* itemStaticBoxSizer10Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Statistics"));
	wxStaticBoxSizer* itemStaticBoxSizer10 = new wxStaticBoxSizer(itemStaticBoxSizer10Static, wxHORIZONTAL);
	itemBoxSizer2->Add(itemStaticBoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

	wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
	itemStaticBoxSizer10->Add(itemBoxSizer11, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 5);

	wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Logics:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText13 = new wxStaticText( itemDialog1, wxID_STATIC, _("Tones:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer11->Add(itemStaticText13, 0, wxALIGN_LEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText14 = new wxStaticText( itemDialog1, wxID_STATIC, _("Tunes:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer11->Add(itemStaticText14, 0, wxALIGN_LEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

	wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
	itemStaticBoxSizer10->Add(itemBoxSizer15, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

	wxStaticText* itemStaticText16 = new wxStaticText( itemDialog1, IDC_COMP_LOGICS, _("000000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	itemBoxSizer15->Add(itemStaticText16, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText17 = new wxStaticText( itemDialog1, IDC_COMP_TONES, _("000000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	itemBoxSizer15->Add(itemStaticText17, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText18 = new wxStaticText( itemDialog1, IDC_COMP_TUNES, _("000000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	itemBoxSizer15->Add(itemStaticText18, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

	wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxVERTICAL);
	itemStaticBoxSizer10->Add(itemBoxSizer19, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxBOTTOM, 5);

	wxStaticText* itemStaticText20 = new wxStaticText( itemDialog1, wxID_STATIC, _("Tone syst.:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer19->Add(itemStaticText20, 0, wxALIGN_LEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText21 = new wxStaticText( itemDialog1, wxID_STATIC, _("Intervals:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer19->Add(itemStaticText21, 0, wxALIGN_LEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText22 = new wxStaticText( itemDialog1, wxID_STATIC, _("Read chars:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer19->Add(itemStaticText22, 0, wxALIGN_LEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

	wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxVERTICAL);
	itemStaticBoxSizer10->Add(itemBoxSizer23, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxBOTTOM, 5);

	wxStaticText* itemStaticText24 = new wxStaticText( itemDialog1, IDC_COMP_TONESYST, _("000000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	itemBoxSizer23->Add(itemStaticText24, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText25 = new wxStaticText( itemDialog1, IDC_COMP_INTERVALS, _("000000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	itemBoxSizer23->Add(itemStaticText25, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM|wxADJUST_MINSIZE, 5);

	wxStaticText* itemStaticText26 = new wxStaticText( itemDialog1, IDC_COMP_READCHARS, _("000000"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	itemBoxSizer23->Add(itemStaticText26, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 5);

	wxStaticBox* itemStaticBoxSizer27Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Message"));
	wxStaticBoxSizer* itemStaticBoxSizer27 = new wxStaticBoxSizer(itemStaticBoxSizer27Static, wxHORIZONTAL);
	itemBoxSizer2->Add(itemStaticBoxSizer27, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

	wxStaticText* itemStaticText28 = new wxStaticText( itemDialog1, IDC_COMP_MESSAGE, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
	itemStaticBoxSizer27->Add(itemStaticText28, 1, wxGROW|wxALL|wxADJUST_MINSIZE, 5);

	wxButton* itemButton29 = new wxButton( itemDialog1, wxID_OK, _("Reading Source ..."), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer2->Add(itemButton29, 1, wxGROW|wxALL, 5);

}

/*!
 * Should we show tooltips?
 */

bool CompDlg::ShowToolTips()
{
	return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CompDlg::GetBitmapResource( const wxString& name )
{
	// Bitmap retrieval
	return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon CompDlg::GetIconResource( const wxString& name )
{
	// Icon retrieval
	return wxNullIcon;
}

MUTABOR_NAMESPACE_END(mutaborGUI)


#endif

///\}
