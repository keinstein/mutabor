/** \file -*- C++ -*-
***********************************************************************
* Mutabor MDI-Child.
*
* \author R. Krauﬂe,
* T. Schlemmer <keinstein@users.sourceforge.net>
* \license GPL
*
*    This program is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software
*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* \addtogroup GUI
* \{
********************************************************************/


#if (!defined(MUWX_MUTEDITFILE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTEDITFILE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTEDITFILE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/stclanguage.h"
#include "src/wxGUI/generic/muconvauto.h"

#ifndef MUWX_MUTEDITFILE_H_PRECOMPILED
#define MUWX_MUTEDITFILE_H_PRECOMPILED

#include <vector>
#include "wx/textctrl.h"
#include "wx/docview.h"
#include "wx/stc/stc.h"
#include "wx/fontdlg.h"
#include "wx/convauto.h"
#if wxUSE_FINDREPLDLG
    #include "wx/fdrepdlg.h"
#endif // wxUSE_FINDREPLDLG

namespace mutaborGUI {

	class MutView;

	class MutEditPrint;
	class MutEditProperties;


	class MutEditFile : public wxStyledTextCtrl
	{
		friend class MutEditProperties;
		friend class MutEditPrint;
	public:

		struct FindFlags 
		{
			bool down:1;
			bool askCircular:1;
			bool showNotFound:1;
			bool useCaret:1;

			FindFlags() 
			{
				down = askCircular = showNotFound = useCaret = true;
			}
			
			FindFlags & Down(bool d = true) 
		        { 
				down = d;  
				return *this;
			}
			FindFlags & Up (bool up = true) 
                        { 
				down = !up; 
				return *this;
			}
			FindFlags & AskCircular (bool a = true) 
			{ 
				askCircular = a; 
				return *this;
			}
			FindFlags & ShowNotFound (bool s = true) 
			{ 
				showNotFound = s;
				return *this;
			}
			FindFlags & UseCaret (bool s = true) 
			{ 
				useCaret = s;
				return *this;
			}
		};


		MutEditFile(wxWindow* parent, 
			    const wxPoint& pos = wxDefaultPosition, 
			    const wxSize& size = wxDefaultSize, 
			    const wxString& value = wxEmptyString, 
			    const wxString& name = wxTextCtrlNameStr);
	
		MutEditFile(MutView * v,
			    wxWindow* parent, 
			    const wxPoint& pos = wxDefaultPosition, 
			    const wxSize& size = wxDefaultSize, 
			    const wxString& value = wxEmptyString, 
			    const wxString& name = wxTextCtrlNameStr);


		virtual ~MutEditFile();

		void SetView(MutView * v) { view = v; }


		void OnSize( wxSizeEvent &event );
		// edit
		void OnEditRedo (wxCommandEvent &event);
		void OnEditUndo (wxCommandEvent &event);
		void OnEditClear (wxCommandEvent &event);
		void OnEditCut (wxCommandEvent &event);
		void OnEditCopy (wxCommandEvent &event);
		void OnEditPaste (wxCommandEvent &event);
		void OnEditRedoUI (wxUpdateUIEvent& event);
		void OnEditUndoUI (wxUpdateUIEvent& event);
		// find
		void OnFind (wxCommandEvent &event);
		void OnFindNext (wxCommandEvent &event);
		void OnFindDialog (wxFindDialogEvent& event);
		int DoFind(const wxString & pattern, FindFlags flags);
		void OnReplace (wxCommandEvent &event);
		void OnReplaceNext (wxCommandEvent &event);
		void OnBraceMatch (wxCommandEvent &event);
		void OnGoto (wxCommandEvent &event);
		void OnEditIndentInc (wxCommandEvent &event);
		void OnEditIndentRed (wxCommandEvent &event);
		void OnEditSelectAll (wxCommandEvent &event);
		void OnEditSelectLine (wxCommandEvent &event);
		//! view
		void OnHilightLang (wxCommandEvent &event);
		void OnDisplayEOL (wxCommandEvent &event);
		void OnIndentGuide (wxCommandEvent &event);
		void OnLineNumber (wxCommandEvent &event);
		void OnLongLineOn (wxCommandEvent &event);
		void OnWhiteSpace (wxCommandEvent &event);
		void OnFoldToggle (wxCommandEvent &event);
		void OnSetOverType (wxCommandEvent &event);
		void OnSetReadOnly (wxCommandEvent &event);
		void OnWrapmodeOn (wxCommandEvent &event);
		void OnUseCharset (wxCommandEvent &event);
		//! extra
		void OnChangeCase (wxCommandEvent &event);
		void OnConvertEOL (wxCommandEvent &event);
		// stc
		void OnMarginClick (wxStyledTextEvent &event);
		void OnCharAdded  (wxStyledTextEvent &event);
		void OnStyleNeeded  (wxStyledTextEvent &event);
		void OnUpdateStcUI(wxStyledTextEvent & event);
		void OnProperties (wxCommandEvent &WXUNUSED(event));

		//! language/lexer
		wxString DeterminePrefs (const wxString &filename);
		bool InitializePrefs (const wxString &filename);
		bool UserSettings (const wxString &filename);
		LanguageInfo const* GetLanguageInfo () {return m_language;};

		//! load/save file
		bool LoadFile ();
		bool LoadFile (const wxString &filename);
		bool SaveFile ();
		bool SaveFile (const wxString &filename);
		bool IsModified () const;
		wxString GetFilename () {return m_filename;};
		void SetFilename (const wxString &filename) {m_filename = filename;};

                //! compatibility with wx2.8
#if !wxCHECK_VERSION(2,9,0)
		virtual wxString GetValue() { return GetText(); }
#endif
		
	protected:
		void Init();
		void SaveSearchData();
//	void SetupWindow();

		bool Compile(bool activate);
		
		bool DoLoadFile(const wxString &filename, int WXUNUSED(fileType));

		bool DoSaveFile(const wxString& filename, int WXUNUSED(fileType));

		void CmFileSave(wxCommandEvent& WXUNUSED(event));

		void CmFileSaveAs(wxCommandEvent& event);

		void CmCompile(wxCommandEvent& WXUNUSED(event));

		void CmCompAct(wxCommandEvent& WXUNUSED(event));

		void CmGetLine(wxCommandEvent& WXUNUSED(event));

		void CmHelpContext(wxCommandEvent& WXUNUSED(event));

		void GoToErrorLine(int Line);


#if 0
#if defined(__WXMSW__) && !(wxUSE_UNICODE || wxUSE_WCHAR_T)
		wxString GetValue() const;

		wxString GetRange(long from, long to) const;

#if wxUSE_RICHEDIT && (!(wxUSE_UNICODE || wxUSE_WCHAR_T) || wxUSE_UNICODE_MSLU)
		// replace the selection or the entire control contents with the given text
		// in the specified encoding
		bool StreamIn(const wxString& value, wxFontEncoding encoding, bool selOnly);

		// get the contents of the control out as text in the given encoding
		wxString StreamOut(wxFontEncoding encoding, bool selOnly = false) const;

#endif // wxUSE_RICHEDIT
#endif
#endif

		
		// file
		wxString m_filename;

		// lanugage properties
		LanguageInfo const* m_language;

		// margin variables
		int m_LineNrID;
		int m_LineNrMargin;
		int m_FoldingID;
		int m_FoldingMargin;
		int m_DividerID;

#if wxUSE_FINDREPLDLG
		wxFindReplaceData m_findData;
		
		wxFindReplaceDialog *m_dlgFind,
                        *m_dlgReplace;
#endif // wxUSE_FINDREPLDLG

		MutView * view;
		//		muConvAuto autoConverter;
		wxConvAuto autoConverter;
		MutSTCLexer lexer;

		DECLARE_EVENT_TABLE()
	};

	
        //---------------------------------------------------------------------
        //! MutEditProperties
	class MutEditProperties: public wxDialog {

	public:

		//! constructor
		MutEditProperties (MutEditFile *edit, long style = 0);

	private:

	};

#if wxUSE_PRINTING_ARCHITECTURE

        //---------------------------------------------------------------------
        //! MutEditPrint
	class MutEditPrint: public wxDocPrintout {

	public:

		//! constructor
		MutEditPrint (MutView * view, MutEditFile *edit, const wxString & title = _T(""));

		//! event handlers
		bool OnPrintPage (int page);
		bool OnBeginDocument (int startPage, int endPage);

		//! print functions
		bool HasPage (int page);
		void GetPageInfo (int *minPage, 
				  int *maxPage, 
				  int *selPageFrom, 
				  int *selPageTo);

	private:
		MutEditFile *m_edit;
		wxRect m_pageRect;
		wxRect m_printRect;
		std::vector<std::pair < int, int > > m_ranges;

		bool PrintScaling (wxDC *dc);
	};



#endif // wxUSE_PRINTING_ARCHITECTURE#endif // wxUSE_PRINTING_ARCHITECTURE



}
#endif // __MUTEDITFILE_H precompiled
#endif // __MUTEDITFILE_H_INCLUDED__

///\}
