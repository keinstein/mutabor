// -*- C++ -*-
/** \file
 ***********************************************************************
 *.
 *
 * $Id: CompDlg.h,v 1.11 2011/11/02 14:31:58 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date 05/08/14 21:41:59
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.11 $
 *
 * $Log: CompDlg.h,v $
 * Revision 1.11  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.10  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.9  2011-09-06 08:09:21  keinstein
 * fix a compiler error showing a corruped error message
 *
 * Revision 1.8  2011-02-20 22:35:57  keinstein
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

#if (!defined(MUWX_COMPDLG_H) && !defined(PRECOMPILE)) \
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


namespace mutaborGUI {

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

		void SetStatus(wxString s) {
			if (wxID_OK) {
				wxID_OK->SetLabel(s);
				wxID_OK->InvalidateBestSize();
			}
			Fit();
			wxSafeYield(this,true);
		}

		void SetMessage(wxString s)
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

		void Refresh() {
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
}

#endif // precompile
#endif // header loaded

///\}
