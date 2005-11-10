/////////////////////////////////////////////////////////////////////////////
// Name:        InputDevDlg.h
// Purpose:     
// Author:      R. Krauﬂe
// Modified by: 
// Created:     10/12/05 14:22:47
// RCS-ID:      
// Copyright:   (c) R. Krauﬂe, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _INPUTDEVDLG_H_
#define _INPUTDEVDLG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "InputDevDlg.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/valgen.h"
#include "wx/valtext.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxBoxSizer;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10010
#define SYMBOL_INPUTDEVDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_INPUTDEVDLG_TITLE _("Inut Device")
#define SYMBOL_INPUTDEVDLG_IDNAME ID_DIALOG
#define SYMBOL_INPUTDEVDLG_SIZE wxSize(400, 300)
#define SYMBOL_INPUTDEVDLG_POSITION wxDefaultPosition
#define ID_CHOICE 10011
#define ID_CHOICE1 10012
#define ID_TEXTCTRL 10013
#define ID_BUTTON 10014
#define ID_TEXTCTRL1 10015
#define ID_BUTTON1 10016
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
 * InputDevDlg class declaration
 */

class InputDevDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( InputDevDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    InputDevDlg( );
    InputDevDlg( wxWindow* parent, wxWindowID id = SYMBOL_INPUTDEVDLG_IDNAME, const wxString& caption = SYMBOL_INPUTDEVDLG_TITLE, const wxPoint& pos = SYMBOL_INPUTDEVDLG_POSITION, const wxSize& size = SYMBOL_INPUTDEVDLG_SIZE, long style = SYMBOL_INPUTDEVDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_INPUTDEVDLG_IDNAME, const wxString& caption = SYMBOL_INPUTDEVDLG_TITLE, const wxPoint& pos = SYMBOL_INPUTDEVDLG_POSITION, const wxSize& size = SYMBOL_INPUTDEVDLG_SIZE, long style = SYMBOL_INPUTDEVDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin InputDevDlg event handler declarations

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
    void OnChoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnButtonClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
    void OnButton1Click( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
    void OnRemoveClick( wxCommandEvent& event );

	void UpdateLayout(int type);
////@end InputDevDlg event handler declarations

////@begin InputDevDlg member function declarations

    int GetMidiDevice() const { return MidiDevice ; }
    void SetMidiDevice(int value) { MidiDevice = value ; }

    wxString GetMidiFile() const { return MidiFile ; }
    void SetMidiFile(wxString value) { MidiFile = value ; }

    wxString GetGUIDOFile() const { return GUIDOFile ; }
    void SetGUIDOFile(wxString value) { GUIDOFile = value ; }

    int GetType() const { return Type ; }
    void SetType(int value) { Type = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end InputDevDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin InputDevDlg member variables
    wxBoxSizer* ctrlPanel;
    wxChoice* ctrlType;
    wxStaticBoxSizer* ctrlMidiDevicePanel;
    wxChoice* ctrlMidiDevice;
    wxStaticBoxSizer* ctrlMidiFilePanel;
    wxTextCtrl* ctrlMidiFile;
    wxStaticBoxSizer* ctrlGUIDOFilePanel;
    wxTextCtrl* ctrlGUIDOFile;
    int MidiDevice;
    wxString MidiFile;
    wxString GUIDOFile;
    int Type;
////@end InputDevDlg member variables
};

#endif
    // _INPUTDEVDLG_H_

