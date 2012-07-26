/** \file -*- C++ -*-
***********************************************************************
* Mutabor MDI-Child.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutEditFile.h,v 1.22 2011/11/02 14:31:59 keinstein Exp $
* \author R. Krauﬂe <krausze@users.berlios.de>
* T. Schlemmer <keinstein@users.berlios.de>
* \date 2005/08/12
* $Date: 2011/11/02 14:31:59 $
* \version $Revision: 1.22 $
* \license GPL
*
* $Log: MutEditFile.h,v $
* Revision 1.22  2011/11/02 14:31:59  keinstein
* fix some errors crashing Mutabor on Windows
*
* Revision 1.21  2011-09-27 20:13:23  keinstein
* * Reworked route editing backend
* * rewireing is done by RouteClass/GUIRoute now
* * other classes forward most requests to this pair
* * many bugfixes
* * Version change: We are reaching beta phase now
*
* Revision 1.20  2011-09-04 15:35:08  keinstein
* disable print preview on OS X and when using libgnomeprint as they proviede their own means
*
* Revision 1.19  2011-09-04 12:02:08  keinstein
* require wxWidgets 2.8.5 configure.in
*
* Revision 1.18  2011-08-31 20:18:16  keinstein
* some work on printing the editor file
*
* Revision 1.17  2011-08-28 21:24:56  keinstein
* added file properties dialog
*
* Revision 1.16  2011-08-27 17:44:44  keinstein
* Implemented Search and Search/Replace
*
* Revision 1.15  2011-08-21 16:52:05  keinstein
* Integrate a more sophisticated editor menu based on the stc sample
*
* Revision 1.14  2011-08-20 17:50:39  keinstein
* use  wxSTC for the editor windows
*
* Revision 1.13  2011-08-11 19:00:48  keinstein
* get Document/View running.
* Needs further testing (possible segfaults).
*
* Revision 1.12  2011-07-31 20:16:04  keinstein
* Implemented opening files from command line using Document/View framework
*
* Revision 1.11  2011-02-20 22:35:57  keinstein
* updated license information; some file headers have to be revised, though
*
* Revision 1.10  2010-11-21 13:15:47  keinstein
* merged experimental_tobias
*
* Revision 1.8.2.1  2009-08-10 11:23:12  keinstein
* merged from wrong tree
*
* Revision 1.9  2009/08/10 11:15:46  keinstein
* some steps towards new route window
*
* Revision 1.8  2008/10/27 15:51:26  keinstein
* fixes for non-Unicode
*
* Revision 1.7  2008/10/01 09:33:22  keinstein
* Better multibyte wxString support
*
* Revision 1.6  2008/08/18 15:09:39  keinstein
* Moved temp file handling a little bit around
*
* Revision 1.5  2008/06/02 16:17:31  keinstein
* CmFileSaveAs: new function
*
* Revision 1.4  2007/12/17 13:00:46  keinstein
* MutEditFile::DoLoadFile, MutEditFile::DoSaveFile: New functions.
* Fix compilation in Unicode mode.
* Copy Some Routines from wxRichEdit to try to circumvent wx/wine incompatibility
* 	in non-Unicode build
*
* Revision 1.3  2006/01/18 15:37:02  keinstein
* no MDI Windows in some environments
*
* \addtogroup muwx
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

#include "mu32/Defs.h"
#include "muwx/stclanguage.h"
#include "mywx/muconvauto.h"

#ifndef MUWX_MUTEDITFILE_H_PRECOMPILED
#define MUWX_MUTEDITFILE_H_PRECOMPILED

#include <vector>
#include "wx/textctrl.h"
#include "wx/docview.h"
#include "wx/stc/stc.h"
#include "wx/fontdlg.h"
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
		bool IsModified ();
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

		void GoErrorLine();


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
		muConvAuto autoConverter;

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
