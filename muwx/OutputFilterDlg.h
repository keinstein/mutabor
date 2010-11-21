/////////////////////////////////////////////////////////////////////////////
// Name:        OutputFilterDlg.h
// Purpose:
// Author:      R. Krauße
// Modified by:
// Created:     10/22/05 16:09:37
// RCS-ID:
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUTFILTERDLG_H_
#define _OUTPUTFILTERDLG_H_

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
#define ID_MYDIALOG2 10030
#define SYMBOL_OUTPUTFILTERDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_OUTPUTFILTERDLG_TITLE _("Output Filter")
#define SYMBOL_OUTPUTFILTERDLG_IDNAME ID_MYDIALOG2
#define SYMBOL_OUTPUTFILTERDLG_SIZE wxSize(400, 300)
#define SYMBOL_OUTPUTFILTERDLG_POSITION wxDefaultPosition
#define ID_TEXTCTRL8 10031
#define ID_TEXTCTRL9 10032
#define ID_CHECKBOX 10033
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
 * OutputFilterDlg class declaration
 */

class OutputFilterDlg: public wxDialog
{
	DECLARE_DYNAMIC_CLASS( OutputFilterDlg )
	DECLARE_EVENT_TABLE()

public:
	/// Constructors
	OutputFilterDlg( );

	OutputFilterDlg( wxWindow* parent, wxWindowID id = SYMBOL_OUTPUTFILTERDLG_IDNAME, const wxString& caption = SYMBOL_OUTPUTFILTERDLG_TITLE, const wxPoint& pos = SYMBOL_OUTPUTFILTERDLG_POSITION, const wxSize& size = SYMBOL_OUTPUTFILTERDLG_SIZE, long style = SYMBOL_OUTPUTFILTERDLG_STYLE );

	/// Creation
	bool Create( wxWindow* parent, wxWindowID id = SYMBOL_OUTPUTFILTERDLG_IDNAME, const wxString& caption = SYMBOL_OUTPUTFILTERDLG_TITLE, const wxPoint& pos = SYMBOL_OUTPUTFILTERDLG_POSITION, const wxSize& size = SYMBOL_OUTPUTFILTERDLG_SIZE, long style = SYMBOL_OUTPUTFILTERDLG_STYLE );

	/// Creates the controls and sizers
	void CreateControls();

////@begin OutputFilterDlg event handler declarations

////@end OutputFilterDlg event handler declarations

////@begin OutputFilterDlg member function declarations

	long GetFrom() const
	{
		return From ;
	}

	void SetFrom(long value)

	{
		From = value ;
	}

	long GetTo() const
	{
		return To ;
	}

	void SetTo(long value)

	{
		To = value ;
	}

	bool GetAvoidDrumChannel() const
	{
		return AvoidDrumChannel ;
	}

	void SetAvoidDrumChannel(bool value)

	{
		AvoidDrumChannel = value ;
	}

	/// Retrieves bitmap resources

	wxBitmap GetBitmapResource( const wxString& name );

	/// Retrieves icon resources
	wxIcon GetIconResource( const wxString& name );

////@end OutputFilterDlg member function declarations

	/// Should we show tooltips?
	static bool ShowToolTips();

////@begin OutputFilterDlg member variables
	long From;

	long To;

	bool AvoidDrumChannel;

////@end OutputFilterDlg member variables
};

#endif
// _OUTPUTFILTERDLG_H_

