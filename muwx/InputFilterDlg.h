/////////////////////////////////////////////////////////////////////////////
// Name:        InputFilterDlg.h
// Purpose:     
// Author:      R. Krauﬂe
// Modified by: 
// Created:     10/21/05 18:28:56
// RCS-ID:      
// Copyright:   (c) R. Krauﬂe, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _INPUTFILTERDLG_H_
#define _INPUTFILTERDLG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "InputFilterDlg.cpp"
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
#define ID_MYDIALOG1 10026
#define SYMBOL_INPUTFILTERDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_INPUTFILTERDLG_TITLE _("Input Filter")
#define SYMBOL_INPUTFILTERDLG_IDNAME ID_MYDIALOG1
#define SYMBOL_INPUTFILTERDLG_SIZE wxSize(400, 300)
#define SYMBOL_INPUTFILTERDLG_POSITION wxDefaultPosition
#define ID_RADIOBOX 10029
#define ID_TEXTCTRL6 10027
#define ID_TEXTCTRL7 10028
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
 * InputFilterDlg class declaration
 */

class InputFilterDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( InputFilterDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    InputFilterDlg( );
    InputFilterDlg( wxWindow* parent, wxWindowID id = SYMBOL_INPUTFILTERDLG_IDNAME, const wxString& caption = SYMBOL_INPUTFILTERDLG_TITLE, const wxPoint& pos = SYMBOL_INPUTFILTERDLG_POSITION, const wxSize& size = SYMBOL_INPUTFILTERDLG_SIZE, long style = SYMBOL_INPUTFILTERDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_INPUTFILTERDLG_IDNAME, const wxString& caption = SYMBOL_INPUTFILTERDLG_TITLE, const wxPoint& pos = SYMBOL_INPUTFILTERDLG_POSITION, const wxSize& size = SYMBOL_INPUTFILTERDLG_SIZE, long style = SYMBOL_INPUTFILTERDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin InputFilterDlg event handler declarations

    /// wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX
    void OnRadioboxSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
    void OnRemoveClick( wxCommandEvent& event );

////@end InputFilterDlg event handler declarations

////@begin InputFilterDlg member function declarations

    int GetType() const { return Type ; }
    void SetType(int value) { Type = value ; }

    long GetFrom() const { return From ; }
    void SetFrom(long value) { From = value ; }

    long GetTo() const { return To ; }
    void SetTo(long value) { To = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end InputFilterDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin InputFilterDlg member variables
    wxRadioBox* ctrlType;
    wxTextCtrl* ctrlFrom;
    wxTextCtrl* ctrlTo;
    int Type;
    long From;
    long To;
////@end InputFilterDlg member variables
};

#endif
    // _INPUTFILTERDLG_H_
