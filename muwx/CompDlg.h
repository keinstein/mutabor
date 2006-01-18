/** \file
 ***********************************************************************
 *.
 *
 * $Id: CompDlg.h,v 1.3 2006/01/18 15:33:42 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2006/01/18 15:33:42 $
 * \version $Revision: 1.3 $
 *
 * $Log: CompDlg.h,v $
 * Revision 1.3  2006/01/18 15:33:42  keinstein
 * Doxygen header
 *
 */
/////////////////////////////////////////////////////////////////////////////
// Name:        CompDlg.h
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     08/14/05 21:41:59
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _COMPDLG_H_
#define _COMPDLG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "CompDlg.cpp"
#endif

/*!
 * Includes
 */

#include "wx/wx.h"
#include "wx/dialog.h"
////@begin includes
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
#define ID_DIALOG 10000
#define SYMBOL_COMPDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_COMPDLG_TITLE _("Compiling")
#define SYMBOL_COMPDLG_IDNAME ID_DIALOG
#define SYMBOL_COMPDLG_SIZE wxSize(400, 300)
#define SYMBOL_COMPDLG_POSITION wxDefaultPosition
#define IDC_COMP_FILENAME 10002
#define IDC_COMP_LINE 10003
#define IDC_COMP_LOGICS 10001
#define IDC_COMP_TONES 10005
#define IDC_COMP_TUNES 10006
#define IDC_COMP_TONESYST 10007
#define IDC_COMP_INTERVALS 10008
#define IDC_COMP_READCHARS 10009
#define IDC_COMP_MESSAGE 10004
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
 * CompDlg class declaration
 */

class CompDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CompDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CompDlg( );
    CompDlg( wxWindow* parent, wxWindowID id = SYMBOL_COMPDLG_IDNAME, const wxString& caption = SYMBOL_COMPDLG_TITLE, const wxPoint& pos = SYMBOL_COMPDLG_POSITION, const wxSize& size = SYMBOL_COMPDLG_SIZE, long style = SYMBOL_COMPDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_COMPDLG_IDNAME, const wxString& caption = SYMBOL_COMPDLG_TITLE, const wxPoint& pos = SYMBOL_COMPDLG_POSITION, const wxSize& size = SYMBOL_COMPDLG_SIZE, long style = SYMBOL_COMPDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin CompDlg event handler declarations

////@end CompDlg event handler declarations

////@begin CompDlg member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CompDlg member function declarations
	void SetText(wxWindowID id1, const wxString& s) {  
		this->FindWindow(id1)->SetLabel(s);
		wxSafeYield(this);
	}

	void SetNumber(wxWindowID id1, int n) {
		SetText(id1, wxString::Format(_T("%d"), n));
	}

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CompDlg member variables
////@end CompDlg member variables
};

#endif
    // _COMPDLG_H_

