// -*- C++ -*-
/** \file
***********************************************************************
* Compilation dialog box.
*
* \author R. Krauße,
*         Tobias Schlemmer <keinstein@users.sourceforge.net>
* \version $Revision: 1.11 $
*
*
* \addtogroup GUI
* \{
*/

#if (!defined(MUWX_COMPDLG_H) && !defined(PRECOMPILE))		      \
	|| (!defined(MUWX_COMPDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_COMPDLG_H
#endif

/*!
 * Includes
 */

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Box.h"
#include "src/wxGUI/resourceload.h"

#ifndef MUWX_COMPDLG_H_PRECOMPILED
#define MUWX_COMPDLG_H_PRECOMPILED

#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"


MUTABOR_NAMESPACE(mutaborGUI)

/*!
 * CompDlg class declaration
 */

class CompDlg: public CompileDlg,
	       public mutabor::BoxClass::CompileCallback
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

	void SetLine(int l) {
		line->SetLabel(wxString::Format(_T("%d"),l));
		wxSafeYield(this,true);
	}

	void SetStatus(int logics, 
		       int tones, 
		       int tunings,
		       int tone_systems,
		       int intervals,
		       int characters)
	{
		if (logic) {
			logic->SetLabel(wxString::Format(_T("%i"),logics));
			logic->InvalidateBestSize();
		}

		if (this->tones) {
			this->tones->SetLabel(wxString::Format(_T("%i"),tones));
			this->tones->InvalidateBestSize();
		}

		if (tunes) {
			tunes->SetLabel(wxString::Format(_T("%i"),tunings));
			tunes->InvalidateBestSize();
		}

		if (tone_system) {
			tone_system->SetLabel(wxString::Format(_T("%i"),tone_systems));
			tone_system->InvalidateBestSize();
		}

		if (this->intervals) {
			this->intervals->SetLabel(wxString::Format(_T("%i"),intervals));
			this->intervals->InvalidateBestSize();
		}

		if (chars) {
			chars->SetLabel(wxString::Format(_T("%i"),characters));
			chars->InvalidateBestSize();
		}

		Fit();
		wxSafeYield(this,true);
	}

	void SetFileName(wxString s)
	{
		if (filename) {
			filename->SetLabel(s);
			filename->InvalidateBestSize();
		}
		Layout();
		InvalidateBestSize();
		GetSizer()->SetSizeHints(this);
		Fit();
		wxSafeYield(this,true);
	}

	void SetStatus(std::string s) {
		if (wxID_OK) {
			wxID_OK->SetLabel(s);
			wxID_OK->InvalidateBestSize();
		}
		Fit();
		wxSafeYield(this,true);
	}

	void SetMessage(std::string s)
	{
		if (message) {
			message->SetLabel(s);
			message->InvalidateBestSize();
		}
		Layout();
		InvalidateBestSize();
		GetSizer()->SetSizeHints(this);
		Fit();
		wxSafeYield(this,true);
	}

	void EnableButton(bool enable = true)
	{
		if (wxID_OK)
			wxID_OK->Enable(enable);
		wxSafeYield(this,true);
	}

	/** Refresh the dialog.
	 *
	 * This function must be implemented since
	 * CompileCallback depends on it beeing defined.
	 *
	 */
	void RefreshDlg() {
		CompileDlg::Refresh();
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
MUTABOR_NAMESPACE_END(mutaborGUI)


#endif // precompile
#endif // header loaded

///\}
