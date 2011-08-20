/** \file -*- C++ -*-
***********************************************************************
* Mutabor MDI-Child.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutEditFile.h,v 1.14 2011/08/20 17:50:39 keinstein Exp $
* \author R. Krauﬂe <krausze@users.berlios.de>
* T. Schlemmer <keinstein@users.berlios.de>
* \date 2005/08/12
* $Date: 2011/08/20 17:50:39 $
* \version $Revision: 1.14 $
* \license GPL
*
* $Log: MutEditFile.h,v $
* Revision 1.14  2011/08/20 17:50:39  keinstein
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


#ifndef __MUTEDITFILE_H_INCLUDED__
#define __MUTEDITFILE_H_INCLUDED__

#include "Defs.h"
#include "wx/textctrl.h"
#include "wx/docview.h"
#include "wx/stc/stc.h"
#include "muwx/stclanguage.h"
#include "muconvauto.h"

namespace mutaborGUI {

	class MutView;

	class MutEditPrint;
	class MutEditProperties;

	class MutEditFile : public wxStyledTextCtrl
	{
		friend class MutEditProperties;
		friend class MutEditPrint;
	public:

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
		// find
		void OnFind (wxCommandEvent &event);
		void OnFindNext (wxCommandEvent &event);
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

		
	protected:
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


		MutView * view;
		muConvAuto autoConverter;

		DECLARE_EVENT_TABLE()
	private:
		void Init();
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
	class MutEditPrint: public wxPrintout {

	public:

		//! constructor
		MutEditPrint (MutEditFile *edit, wxChar *title = _T(""));

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
		int m_printed;
		wxRect m_pageRect;
		wxRect m_printRect;

		bool PrintScaling (wxDC *dc);
	};



#endif // wxUSE_PRINTING_ARCHITECTURE#endif // wxUSE_PRINTING_ARCHITECTURE



}
#endif // __MUTEDITFILE_H_INCLUDED__

///\}
