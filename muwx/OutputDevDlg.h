/////////////////////////////////////////////////////////////////////////////
// Name:        OutputDevDlg.h
// Purpose:     
// Author:      R. Krauﬂe
// Modified by: 
// Created:     10/19/05 12:10:52
// RCS-ID:      
// Copyright:   (c) R. Krauﬂe, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUTDEVDLG_H_
#define _OUTPUTDEVDLG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "OutputDevDlg.cpp"
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
#define ID_MYDIALOG 10017
#define SYMBOL_OUTPUTDEVDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_OUTPUTDEVDLG_TITLE _("Output Device")
#define SYMBOL_OUTPUTDEVDLG_IDNAME ID_MYDIALOG
#define SYMBOL_OUTPUTDEVDLG_SIZE wxSize(400, 300)
#define SYMBOL_OUTPUTDEVDLG_POSITION wxDefaultPosition
#define ID_CHOICE2 10018
#define ID_CHOICE3 10019
#define ID_TEXTCTRL4 10024
#define ID_TEXTCTRL2 10020
#define ID_BUTTON2 10022
#define ID_TEXTCTRL5 10025
#define ID_TEXTCTRL3 10021
#define ID_BUTTON3 10023
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
 * OutputDevDlg class declaration
 */

class OutputDevDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( OutputDevDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    OutputDevDlg( );
    OutputDevDlg( wxWindow* parent, wxWindowID id = SYMBOL_OUTPUTDEVDLG_IDNAME, const wxString& caption = SYMBOL_OUTPUTDEVDLG_TITLE, const wxPoint& pos = SYMBOL_OUTPUTDEVDLG_POSITION, const wxSize& size = SYMBOL_OUTPUTDEVDLG_SIZE, long style = SYMBOL_OUTPUTDEVDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_OUTPUTDEVDLG_IDNAME, const wxString& caption = SYMBOL_OUTPUTDEVDLG_TITLE, const wxPoint& pos = SYMBOL_OUTPUTDEVDLG_POSITION, const wxSize& size = SYMBOL_OUTPUTDEVDLG_SIZE, long style = SYMBOL_OUTPUTDEVDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin OutputDevDlg event handler declarations

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE2
    void OnChoice2Selected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON2
    void OnButton2Click( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON3
    void OnButton3Click( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
    void OnRemoveClick( wxCommandEvent& event );

////@end OutputDevDlg event handler declarations

////@begin OutputDevDlg member function declarations

    int GetType() const { return Type ; }
    void SetType(int value) { Type = value ; }

    int GetMidiDevice() const { return MidiDevice ; }
    void SetMidiDevice(int value) { MidiDevice = value ; }

    wxString GetMidiFile() const { return MidiFile ; }
    void SetMidiFile(wxString value) { MidiFile = value ; }

    wxString GetGUIDOFile() const { return GUIDOFile ; }
    void SetGUIDOFile(wxString value) { GUIDOFile = value ; }

    long GetMidiDeviceBending() const { return MidiDeviceBending ; }
    void SetMidiDeviceBending(long value) { MidiDeviceBending = value ; }

    long GetMidiFileBending() const { return MidiFileBending ; }
    void SetMidiFileBending(long value) { MidiFileBending = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end OutputDevDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin OutputDevDlg member variables
    wxBoxSizer* ctrlPanel;
    wxChoice* ctrlType;
    wxStaticBoxSizer* ctrlMidiDevicePanel;
    wxChoice* ctrlMidiDevice;
    wxStaticBoxSizer* ctrlMidiFilePanel;
    wxTextCtrl* ctrlMidiFile;
    wxStaticBoxSizer* ctrlGUIDOFilePanel;
    wxTextCtrl* ctrlGUIDOFile;
    int Type;
    int MidiDevice;
    wxString MidiFile;
    wxString GUIDOFile;
    long MidiDeviceBending;
    long MidiFileBending;
////@end OutputDevDlg member variables
};

#endif
    // _OUTPUTDEVDLG_H_
