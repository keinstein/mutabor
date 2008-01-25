/////////////////////////////////////////////////////////////////////////////
// Name:        BoxDlg.h
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     10/22/05 16:16:24
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _BOXDLG_H_
#define _BOXDLG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "BoxDlg.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/valgen.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MYDIALOG3 10034
#define SYMBOL_BOXDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_BOXDLG_TITLE _("Mutabor-Box")
#define SYMBOL_BOXDLG_IDNAME ID_MYDIALOG3
#define SYMBOL_BOXDLG_SIZE wxSize(400, 300)
#define SYMBOL_BOXDLG_POSITION wxDefaultPosition
#define ID_RADIOBUTTON 10036
#define ID_TEXTCTRL10 10037
#define ID_RADIOBUTTON1 10038
#define ID_RADIOBUTTON2 10039
#define ID_RADIOBOX1 10035
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * BoxDlg class declaration
 */

class BoxDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( BoxDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    BoxDlg( );
    BoxDlg( wxWindow* parent, wxWindowID id = SYMBOL_BOXDLG_IDNAME, const wxString& caption = SYMBOL_BOXDLG_TITLE, const wxPoint& pos = SYMBOL_BOXDLG_POSITION, const wxSize& size = SYMBOL_BOXDLG_SIZE, long style = SYMBOL_BOXDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_BOXDLG_IDNAME, const wxString& caption = SYMBOL_BOXDLG_TITLE, const wxPoint& pos = SYMBOL_BOXDLG_POSITION, const wxSize& size = SYMBOL_BOXDLG_SIZE, long style = SYMBOL_BOXDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin BoxDlg event handler declarations

    /// wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON
    void UpdateEnable( wxCommandEvent& event );
	void UpdateLayout(int type);

////@end BoxDlg event handler declarations

////@begin BoxDlg member function declarations

    int GetBoxType() const { return Type ; }
    void SetBoxType(int value) { Type = value ; }

    long GetBoxNr() const { return BoxNr ; }
    void SetBoxNr(long value) { BoxNr = value ; }

    int GetMode() const { return Mode ; }
    void SetMode(int value) { Mode = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end BoxDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin BoxDlg member variables
    wxRadioButton* ctrlBox1;
    wxTextCtrl* ctrlBoxNr;
    wxRadioButton* ctrlBox2;
    wxRadioButton* ctrlBox3;
    wxRadioBox* ctrlMode;
    int Type;
    long BoxNr;
    int Mode;
////@end BoxDlg member variables
};

#endif
    // _BOXDLG_H_

