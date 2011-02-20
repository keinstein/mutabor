// -*- C++ -*-
/** \file
 ***********************************************************************
 *.
 *
 * $Id: CompDlg.h,v 1.8 2011/02/20 22:35:57 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date 05/08/14 21:41:59
 * $Date: 2011/02/20 22:35:57 $
 * \version $Revision: 1.8 $
 *
 * $Log: CompDlg.h,v $
 * Revision 1.8  2011/02/20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.7  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.5.2.2  2010-01-14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.5.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.6  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.5  2008/06/30 08:16:30  keinstein
 * Check if childs exist, when updating data.
 *
 * Revision 1.4  2008/06/02 16:39:17  keinstein
 * Use CompieleDlg from resource system now
 *
 * Revision 1.3  2006/01/18 15:33:42  keinstein
 * Doxygen header
 *
 * \addtogroup GUI
 * \{
 */

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
#include "resourceload.h"
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
	CompDlg(wxWindow * parent = NULL): CompileDlg(parent)
	{}

	~CompDlg()
	{}

	wxStaticText * GetLine()
	{
		return line;
	}

	void SetStatus(wxString l, wxString to, wxString tu,
	               wxString ts, wxString i, wxString ch)
	{
		if (logic)
			logic->SetLabel(l);

		if (tones)
			tones->SetLabel(to);

		if (tunes)
			tunes->SetLabel(tu);

		if (tone_system)
			tone_system->SetLabel(ts);

		if (intervals)
			intervals->SetLabel(i);

		if (chars)
			chars->SetLabel(ch);

		Layout();
	}

	void SetFileName(wxString s)
	{
		if (filename)
			filename->SetLabel(s);
	}

	void SetButtonText(wxString s)
	{
		if (wxID_OK)
			wxID_OK->SetLabel(s);
	}

	void SetMessage(wxString s)
	{
		if (message)
			message->SetLabel(s);
	}

	void EnableButton(bool enable = true)
	{
		if (wxID_OK)
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

///\}
