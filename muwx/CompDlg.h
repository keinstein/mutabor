// -*- C++ -*-
/** \file
 ***********************************************************************
 *.
 *
 * $Id: CompDlg.h,v 1.4 2008/06/02 16:39:17 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2008/06/02 16:39:17 $
 * \version $Revision: 1.4 $
 *
 * $Log: CompDlg.h,v $
 * Revision 1.4  2008/06/02 16:39:17  keinstein
 * Use CompieleDlg from resource system now
 *
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

/*
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "CompDlg.cpp"
#endif
*/
/*!
 * Includes
 */

#include "wx/wx.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wxresource.h"
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
////@end control identifiers


/*!
 * CompDlg class declaration
 */

class CompDlg: public CompileDlg
{    
  //DECLARE_DYNAMIC_CLASS( CompDlg )
  //DECLARE_EVENT_TABLE()

  public:
  /// Constructors
  //  CompDlg():CompileDlg() {}
  CompDlg(wxWindow * parent = NULL): CompileDlg(parent) {}
  ~CompDlg() {}

  wxStaticText * GetLine() { return line; }
  void SetStatus(wxString l, wxString to, wxString tu, 
		 wxString ts, wxString i, wxString ch) {
    logic->SetLabel(l);
    tones->SetLabel(to);
    tunes->SetLabel(tu);
    tone_system->SetLabel(ts);
    intervals->SetLabel(i);
    chars->SetLabel(ch);
    Layout();
  }

  void SetFileName(wxString s) {
    filename->SetLabel(s);
  }

  void SetButtonText(wxString s) {
    wxID_OK->SetLabel(s);
  }

  void SetMessage(wxString s) {
    message->SetLabel(s);
  }

  void EnableButton(bool enable = true) {
    wxID_OK->Enable(enable);
  }
  /*
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
*/
};

#endif
    // _COMPDLG_H_

