/** \file 
********************************************************************
* Mutabor Edit window for Mutabor-files
*
* Copyright:   (c) 2008-2012 TU Dresden
* \author R. Krauße
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 2005/08/12
* $Date: 2011/11/02 14:31:59 $
* \version $Revision: 1.34 $
* \license GPL
*
* \addtogroup src/wxGUI
* \{
********************************************************************/

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/generic/mhDefs.h"

#include <iostream>

#include "wx/ffile.h"
#include "wx/numdlg.h"
#include "wx/filename.h"
#include "wx/textfile.h"
#include "wx/toolbar.h"


#ifdef __WXMSW__
#include "wx/msw/private.h"

#if (wxUSE_RICHEDIT) && 0

#if wxUSE_INKEDIT
#include "wx/dynlib.h"
#endif

// old mingw32 has richedit stuff directly in windows.h and doesn't have
// richedit.h at all
#if !defined(__GNUWIN32_OLD__) || defined(__CYGWIN10__)
#include <richedit.h>
#endif

#endif // wxUSE_RICHEDIT
#endif // __WXMSW__


//#include "Mutabor.rh"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutEditFile.h"
#include "src/wxGUI/CompDlg.h"
#include "src/kernel/Runtime.h"
#include "src/wxGUI/MutView.h"
#include "src/wxGUI/stclanguage.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/routing/Route-inlines.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif



mutaborGUI::CompDlg *CompDia = NULL;

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------
using mutaborGUI::MutEditFile;
BEGIN_EVENT_TABLE(MutEditFile, wxStyledTextCtrl)
//    EVT_MOUSE_EVENTS(MyCanvas::OnEvent)
//EVT_MENU(CM_FILESAVE,            MutEditFile::CmFileSave)
//EVT_MENU(CM_FILESAVEAS,          MutEditFile::CmFileSaveAs)
EVT_MENU(CM_COMPILE,             MutEditFile::CmCompile)
EVT_MENU(CM_COMPACT,             MutEditFile::CmCompAct)
EVT_MENU(CM_ACTIVATE,            MutEditFile::CmCompAct)
EVT_MENU(CM_GETLINE,             MutEditFile::CmGetLine)
EVT_MENU(CM_HELPCONTEXT,         MutEditFile::CmHelpContext)
EVT_MENU(CM_PROPERTIES,          MutEditFile::OnProperties)
// common
EVT_SIZE (                       MutEditFile::OnSize)
// edit
EVT_MENU (wxID_CLEAR,            MutEditFile::OnEditClear)
EVT_MENU (wxID_CUT,              MutEditFile::OnEditCut)
EVT_MENU (wxID_COPY,             MutEditFile::OnEditCopy)
EVT_MENU (wxID_PASTE,            MutEditFile::OnEditPaste)
EVT_MENU (CM_INDENTINC,          MutEditFile::OnEditIndentInc)
EVT_MENU (CM_INDENTRED,          MutEditFile::OnEditIndentRed)
EVT_MENU (wxID_SELECTALL,        MutEditFile::OnEditSelectAll)
EVT_MENU (CM_SELECTLINE,         MutEditFile::OnEditSelectLine)
EVT_MENU (wxID_REDO,             MutEditFile::OnEditRedo)
EVT_MENU (wxID_UNDO,             MutEditFile::OnEditUndo)
EVT_UPDATE_UI(wxID_REDO,         MutEditFile::OnEditRedoUI)
EVT_UPDATE_UI(wxID_UNDO,         MutEditFile::OnEditUndoUI)

// find
EVT_MENU (wxID_FIND,             MutEditFile::OnFind)
EVT_MENU (CM_FINDNEXT,           MutEditFile::OnFindNext)
EVT_MENU (wxID_REPLACE,          MutEditFile::OnReplace)
EVT_MENU (CM_REPLACENEXT,        MutEditFile::OnReplaceNext)
EVT_MENU (CM_BRACEMATCH,         MutEditFile::OnBraceMatch)
EVT_MENU (CM_GOTO,               MutEditFile::OnGoto)
EVT_FIND(wxID_ANY,               MutEditFile::OnFindDialog)
EVT_FIND_NEXT(wxID_ANY,          MutEditFile::OnFindDialog)
EVT_FIND_REPLACE(wxID_ANY,       MutEditFile::OnFindDialog)
EVT_FIND_REPLACE_ALL(wxID_ANY,   MutEditFile::OnFindDialog)
EVT_FIND_CLOSE(wxID_ANY,         MutEditFile::OnFindDialog)
// view
EVT_MENU_RANGE (CM_HILIGHTFIRST, CM_HILIGHTLAST,
		MutEditFile::OnHilightLang)
EVT_MENU (CM_DISPLAYEOL,         MutEditFile::OnDisplayEOL)
EVT_MENU (CM_INDENTGUIDE,        MutEditFile::OnIndentGuide)
EVT_MENU (CM_LINENUMBER,         MutEditFile::OnLineNumber)
EVT_MENU (CM_LONGLINEON,         MutEditFile::OnLongLineOn)
EVT_MENU (CM_WHITESPACE,         MutEditFile::OnWhiteSpace)
EVT_MENU (CM_FOLDTOGGLE,         MutEditFile::OnFoldToggle)
EVT_MENU (CM_OVERTYPE,           MutEditFile::OnSetOverType)
EVT_MENU (CM_READONLY,           MutEditFile::OnSetReadOnly)
EVT_MENU (CM_WRAPMODEON,         MutEditFile::OnWrapmodeOn)
EVT_MENU (CM_CHARSETANSI,        MutEditFile::OnUseCharset)
EVT_MENU (CM_CHARSETMAC,         MutEditFile::OnUseCharset)
// extra
EVT_MENU (CM_CHANGELOWER,        MutEditFile::OnChangeCase)
EVT_MENU (CM_CHANGEUPPER,        MutEditFile::OnChangeCase)
EVT_MENU (CM_CONVERTCR,          MutEditFile::OnConvertEOL)
EVT_MENU (CM_CONVERTCRLF,        MutEditFile::OnConvertEOL)
EVT_MENU (CM_CONVERTLF,          MutEditFile::OnConvertEOL)
// stc
EVT_STC_MARGINCLICK (wxID_ANY,   MutEditFile::OnMarginClick)
EVT_STC_CHARADDED (wxID_ANY,     MutEditFile::OnCharAdded)
END_EVENT_TABLE()

namespace mutaborGUI {
// ===========================================================================
// implementation
// ===========================================================================

// Editorfenster

	MutEditFile::MutEditFile(wxWindow* parent, 
				 const wxPoint& pos, 
				 const wxSize& size, 
				 const wxString& value, 
				 const wxString& name)
		: wxStyledTextCtrl(parent, 
				   wxID_ANY, 
				   pos, 
				   size, 
				   wxHSCROLL | wxVSCROLL | wxBORDER_SUNKEN 
				   | wxWANTS_CHARS, 
				   name)
	{
		Init();
#if wxUSE_FINDREPLDLG
		m_dlgFind = m_dlgReplace = NULL;
#endif
		
	}
	
	MutEditFile::MutEditFile(MutView * v,
				 wxWindow* parent, 
				 const wxPoint& pos, 
				 const wxSize& size, 
				 const wxString& value, 
				 const wxString& name)
		: wxStyledTextCtrl(parent, 
				   wxID_ANY, 
				   pos, 
				   size, 
				   wxHSCROLL | wxVSCROLL | wxBORDER_SUNKEN  
				   | wxWANTS_CHARS, 
				   name),
		  view(v)
	{
		Init();
#if wxUSE_FINDREPLDLG
		m_dlgFind = m_dlgReplace = NULL;
#endif
	}


	MutEditFile::~MutEditFile()
	{
		if (view) {
			view->SetTextsw(NULL);
		}
	}


	bool MutEditFile::Compile(bool activate)
	{
		wxString TmpFile = wxFileName::CreateTempFileName(wxT(PACKAGE));

		if ( SaveEditor )
			SaveFile(m_filename);

		bool result=true;

		if ( LogicOn ) {
			wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);
			GetParent()->GetEventHandler()->ProcessEvent(event);
		}

		wxFile file(TmpFile,wxFile::write);
		if (!file.IsOpened()) {
			wxMessageBox(_("Can't open temporary file."),
				     _("Error"), wxOK | wxICON_HAND);
			CompiledFile = wxEmptyString;
			return false;
		} 

		if (!file.Write(GetText(), wxConvUTF8) ) {
			wxMessageBox(_("Can't write temporary file."),
				     _("Error"), wxOK | wxICON_HAND);
			CompiledFile = wxEmptyString;
			if (file.IsOpened()) 
				file.Close();
			if (wxFile::Exists(TmpFile)) {
				wxRemoveFile(TmpFile);
			}
			return false;
		} 

		CompDia = new CompDlg(this);

		if (!CompDia->Show()) {
			wxLogError(_("The compile dialog could not be loaded."));
		};

		CompDia->SetFileName(GetName());

		if ( ::Compile(CompDia, TmpFile.c_str()) ) {
			CompiledFile = m_filename;

			if (activate) {
				wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, 
						      CM_DOACTIVATE);
				GetParent()->GetEventHandler()->ProcessEvent(event);
				CompDia->Destroy();
			} else
				CompDia->EnableButton(true);

		} else {
			CompiledFile = wxEmptyString;
			CompDia->EnableButton(true);
			GoErrorLine();
			result = false;
		}

		wxRemoveFile(TmpFile);
			
		return result;
		
	}

	bool MutEditFile::DoLoadFile(const wxString &filename, 
				     int WXUNUSED(fileType))
	{
		TRACEC;
		wxFFile file(filename);

		if ( file.IsOpened() ) {
			wxString text;

			if ( file.ReadAll(&text, autoConverter) ) {
				DEBUGLOG(mutparser,_T("%s"),text.c_str());

				SetText(text);
				EmptyUndoBuffer();
				SetSavePoint();
				m_filename = filename;
				file.Close();
				wxFileName fname (m_filename);
				InitializePrefs (DeterminePrefs (fname.GetFullName()));
				return true;
			}

#ifdef DEBUG
			else
				DEBUGLOG (mutparser,
					  _T("File opened, but couldn't be loaded."));

#endif
		}

		wxLogError(_("File couldn't be loaded."));
		return false;
	}

	bool MutEditFile::DoSaveFile(const wxString& filename, int WXUNUSED(fileType))

	{
#if wxUSE_FFILE
		DEBUGLOG(mutparser,_T("File contents:\n%s"),
			 (const wxChar *)GetValue());

		wxFFile file(filename, _T("w"));


		if ( file.IsOpened() && file.Write(GetValue(), autoConverter) ) {
			// if it worked, save for future calls
			m_filename = filename;
			// it's not modified any longer
			SetSavePoint();
			file.Close();

			return true;
		}

#endif // wxUSE_FFILE
		wxLogError(_("The text couldn't be saved."));

		return false;
	}


	void MutEditFile::CmFileSave(wxCommandEvent& WXUNUSED(event))

	{
		SaveFile(m_filename);
	}

	void MutEditFile::CmFileSaveAs(wxCommandEvent& event)
	{
		wxString newname = FileNameDialog(GetParent(), event.GetId(), m_filename);

		if (newname.IsEmpty()) return;

		m_filename = newname;
		CmFileSave(event);

		// Überschrift in MutWin setzen
		wxCommandEvent e(wxEVT_COMMAND_MENU_SELECTED,CM_SETTITLE);

		//  e.ResumePropagation(wxEVENT_PROPAGATE_MAX);
		wxFileName s(m_filename);

		e.SetString(s.GetFullName());

		AddPendingEvent(e);
	}


	void MutEditFile::CmCompile(wxCommandEvent& event)
	{

		DEBUGLOG (other, 
			  _T("MutEditFile::CmCompile(Event(%d)); filename = %s"),
			  event.GetId(),m_filename.c_str());
		Compile(false);
		event.Skip(false);
	}

	void MutEditFile::CmCompAct(wxCommandEvent& event)
	{
		Compile(true);
		event.Skip(false);
	}

	void MutEditFile::CmGetLine(wxCommandEvent& WXUNUSED(event))
	{
		STUBC;
		/*  int LineFirstPos = GetLineIndex(-1);
		    EditLine = GetLineFromPos(LineFirstPos) + 1;
		    uint Sel1, Sel2;
		    GetSelection(Sel1, Sel2);
		    EditRow = Sel2 - LineFirstPos + 1;*/
	}

	void MutEditFile::GoErrorLine()
	{
		int Line = GetErrorLine();
		if ( Line == -1 ) return;
		GotoLine(Line);
	}

	void MutEditFile::CmHelpContext(wxCommandEvent& WXUNUSED(event))
	{
		STUBC;
		/*  char s[1000], s1[1000];
		    uint a, e, i;
		    GetSelection(a, e);
		    if ( !GetLine(s, 999, GetLineFromPos(a)) ) return;
		    i = a - GetLineIndex(GetLineFromPos(a));
		    // nun Wortanfang und ende finden
		    if ( a == e )
		    {
		    while ( i > 0 && !strchr(" ,[]()", s[i-1]) )
		    i--;
		    a = i;
		    while ( s[i] != 0 && !strchr(" ,[]()", s[i]) )
		    i++;
		    e = i;
		    }
		    else
		    {
		    e = e - a + i;
		    a = i;
		    }
		    strncpy(s1, &(s[a]), e - a);
		    s1[e-a] = 0;
		    strupr(s1);
		    int HelpContext = 0;
		    for (i = 0; i < 2 * nKeyWords; i++)
		    if ( !strcmp(s1, KeyWords[i]) )
		    HelpContext = (i % nKeyWords) + SX_INTERVAL;
		    if ( HelpContext )
		    WinHelp(HlpFile, HELP_CONTEXT, HelpContext);
		    else
		    WinHelp(HlpFile, HELP_CONTEXT, SX_BASICS);*/
	}

#if defined(__WXMSW__) && !(wxUSE_UNICODE || wxUSE_WCHAR_T)

	wxString MutEditFile::GetValue() const
	{

		DEBUGLOG(other,_T(""));
		// range 0..-1 is special for GetRange() and means to retrieve all text
		return GetRange(0, -1);
	}

#endif


	void MutEditFile::Init() 
	{
		
		wxConfigBase *config = wxConfig::Get();
		if (config) {
			wxString old = config->GetPath();
			config->SetPath(_T("/Editor/Search"));
			wxUint32 flags = 0;
			if (config -> Read(_T("Downwards"),1l))
				flags |= wxFR_DOWN;
			if (config -> Read(_T("Whole words"),0l))
				flags |= wxFR_WHOLEWORD;
			if (config -> Read(_T("Case sensitive"),0l))
				flags |= wxFR_MATCHCASE;
			m_findData.SetFlags(flags);
			m_findData.SetFindString(config -> Read(_T("Find"),
								wxEmptyString));
			m_findData.SetReplaceString(config -> Read(_T("Replace to"),
								wxEmptyString));
			config -> SetPath(old);
		}
		m_filename = wxEmptyString;

		m_LineNrID = 0;
		m_DividerID = 1;
		m_FoldingID = 2;

		// initialize language
		m_language = NULL;

		// default font for all styles
		SetViewEOL (g_CommonPrefs.displayEOLEnable);
		SetIndentationGuides (g_CommonPrefs.indentGuideEnable);
		SetEdgeMode (g_CommonPrefs.longLineOnEnable?
			     wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
		SetViewWhiteSpace (g_CommonPrefs.whiteSpaceEnable?
				   wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
		SetOvertype (g_CommonPrefs.overTypeInitial);
		SetReadOnly (g_CommonPrefs.readOnlyInitial);
		SetWrapMode (g_CommonPrefs.wrapModeInitial?
			     wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);
		wxFont font (10, wxMODERN, wxNORMAL, wxNORMAL);
		StyleSetFont (wxSTC_STYLE_DEFAULT, font);
		StyleSetForeground (wxSTC_STYLE_DEFAULT, *wxBLACK);
		StyleSetBackground (wxSTC_STYLE_DEFAULT, *wxWHITE);
		StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (_T("DARK GREY")));
		StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
		StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour (_T("DARK GREY")));
		InitializePrefs (DEFAULT_LANGUAGE);

		// set visibility
		SetVisiblePolicy (wxSTC_VISIBLE_STRICT|wxSTC_VISIBLE_SLOP, 1);
		SetXCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
		SetYCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);

		// markers
		MarkerDefine (wxSTC_MARKNUM_FOLDER,        wxSTC_MARK_DOTDOTDOT, _T("BLACK"), _T("BLACK"));
		MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN, _T("BLACK"), _T("BLACK"));
		MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY,     _T("BLACK"), _T("BLACK"));
		MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_DOTDOTDOT, _T("BLACK"), _T("WHITE"));
		MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN, _T("BLACK"), _T("WHITE"));
		MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY,     _T("BLACK"), _T("BLACK"));
		MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY,     _T("BLACK"), _T("BLACK"));

		// miscelaneous
		m_LineNrMargin = TextWidth (wxSTC_STYLE_LINENUMBER, _T("_999999"));
		m_FoldingMargin = 16;
		CmdKeyClear (wxSTC_KEY_TAB, 0); // this is done by the menu accelerator key
		SetLayoutCache (wxSTC_CACHE_PAGE);
	}


	void MutEditFile::SaveSearchData () 
	{
		wxConfigBase *config = wxConfig::Get();
		if (config) {
			wxString old = config->GetPath();
			config->SetPath(_T("/Editor/Search"));
			wxUint32 flags = m_findData.GetFlags();

			config -> Write(_T("Downwards"),
					(bool) ((flags & wxFR_DOWN) != 0));
			config -> Write(_T("Whole words"),
					(bool)((flags & wxFR_WHOLEWORD) != 0));
			config -> Write(_T("Case sensitive"),
					(bool)((flags & wxFR_MATCHCASE)!= 0));
			config -> Write(_T("Find"),m_findData.GetFindString());
			config -> Write(_T("Replace to"),
					m_findData.GetReplaceString());
			config -> SetPath(old);
		}
	}


//----------------------------------------------------------------------------
// common event handlers
	void MutEditFile::OnSize( wxSizeEvent& event ) {
		int x = GetClientSize().x +
			(g_CommonPrefs.lineNumberEnable? m_LineNrMargin: 0) +
			(g_CommonPrefs.foldEnable? m_FoldingMargin: 0);
		if (x > 0) SetScrollWidth (x);
		event.Skip();
	}

// edit event handlers
	void MutEditFile::OnEditUndoUI (wxUpdateUIEvent &event) {
		event.Enable(CanUndo());
	}

	void MutEditFile::OnEditRedoUI (wxUpdateUIEvent &event) {
		event.Enable(CanRedo());
	}

	void MutEditFile::OnEditRedo (wxCommandEvent &WXUNUSED(event)) {
		if (!CanRedo()) return;
		Redo ();
	}

	void MutEditFile::OnEditUndo (wxCommandEvent &WXUNUSED(event)) {
		if (!CanUndo()) return;
		Undo ();
	}

	void MutEditFile::OnEditClear (wxCommandEvent &WXUNUSED(event)) {
		if (GetReadOnly()) return;
		Clear ();
	}

	void MutEditFile::OnEditCut (wxCommandEvent &WXUNUSED(event)) {
		if (GetReadOnly() || (GetSelectionEnd()-GetSelectionStart() <= 0))
			return;
		Cut ();
	}

	void MutEditFile::OnEditCopy (wxCommandEvent &WXUNUSED(event)) {
		if (GetSelectionEnd()-GetSelectionStart() <= 0) return;
		Copy ();
	}

	void MutEditFile::OnEditPaste (wxCommandEvent &WXUNUSED(event)) {
		if (!CanPaste()) return;
		Paste ();
	}

	void MutEditFile::OnFind (wxCommandEvent &event) {
		mutUnused(event);
		if ( m_dlgFind )
		{
			delete m_dlgFind;
			m_dlgFind = NULL;
		}
		m_dlgFind = new wxFindReplaceDialog (this,
						     &m_findData,
						     _T("Find dialog"),
						     // just for testing
						     //wxFR_NOWHOLEWORD
						     0);
		if (m_dlgFind)
			m_dlgFind->Show(true);
	}

	void MutEditFile::OnFindNext (wxCommandEvent &WXUNUSED(event)) {
		DoFind(m_findData.GetFindString(),
			 FindFlags().Down(m_findData.GetFlags() & wxFR_DOWN));
	}

	void MutEditFile::OnFindDialog (wxFindDialogEvent& event)
	{
		DEBUGLOG(editor,_T("Find (flags=%x,%s)"),
			 event.GetFlags(),
			 (const wxChar*)event.GetFindString());
		wxEventType type = event.GetEventType();

		if ( type == wxEVT_COMMAND_FIND_CLOSE )
		{
			wxFindReplaceDialog *dlg = event.GetDialog();

			if ( dlg == m_dlgFind )
			{
				m_dlgFind = NULL;
			}
			else if ( dlg == m_dlgReplace )
			{
				m_dlgReplace = NULL;
			}
			else
			{
				UNREACHABLEC;
			}


			dlg->Destroy();
			return;
		}

		SaveSearchData();

		int flags = 0;
		if (event.GetFlags() & wxFR_WHOLEWORD) 
			flags |= wxSTC_FIND_WHOLEWORD;
		if (event.GetFlags() & wxFR_MATCHCASE) 
			flags |=  wxSTC_FIND_WHOLEWORD;
		SetSearchFlags(flags);

		
		
		wxString findString = event.GetFindString();
		if ( type == wxEVT_COMMAND_FIND_REPLACE && 
		     GetSelectionStart() == GetTargetStart()) {
			int result = SearchInTarget(findString); // should not change anything
			if (result < 0) {
				return;
			}
			if (GetSelectionStart() != GetTargetStart() || 
			    GetSelectionEnd() != GetTargetEnd()) {
				SetCurrentPos(GetTargetStart());
				SetSelection(GetTargetStart(),
					     GetTargetEnd());
				return ; 
			}
			ReplaceTarget(event.GetReplaceString());
		}

		if ( type == wxEVT_COMMAND_FIND || type == wxEVT_COMMAND_FIND_NEXT ||
			type == wxEVT_COMMAND_FIND_REPLACE)
		{
			
#ifdef DEBUG
			int result =
#endif
				DoFind(findString,
				 FindFlags().Down(event.GetFlags() & wxFR_DOWN));
			DEBUGLOG(editor,_T("Find (flags=%x,%s) = %d"),
				 event.GetFlags(),
				 (const wxChar*)findString,result);
		} else if (type == wxEVT_COMMAND_FIND_REPLACE_ALL )
		{
			// first search is treated different 
			// (e.g. reuse current target)
			if (event.GetFlags() & wxFR_DOWN) {
				if (GetTargetEnd() < GetTargetStart())
					SetTargetStart(GetTargetEnd());
				SetTargetEnd(GetLength());
			} else {
				if (GetTargetEnd() > GetTargetStart()) 
					SetTargetStart(GetTargetEnd());
				SetTargetEnd(0);
			}
			
			int result = SearchInTarget(findString);
			
			if (result < 0) {
				wxMessageBox(
					_("The search string was not found."),
					_("Replace all"),
					wxOK | wxICON_INFORMATION);
				return;
			}

			FindFlags ff;
			ff.Down(event.GetFlags() & wxFR_DOWN).AskCircular(false)
				.ShowNotFound(false).UseCaret(false);
			int count = 0;
			BeginUndoAction();
			while (result >= 0) {
				count++;
				ReplaceTarget(event.GetReplaceString());
				result = DoFind(findString,ff);
			}
			EndUndoAction();
			wxMessageBox(
				wxString::Format(_("Replaced %d occurrences of `%s' by `%s'.\n\n"), count,(const wxChar*)findString,(const wxChar*)event.GetReplaceString())
				+ (ff.down?
				   _("Note: Occurences before the current cursor positions are not changed."):
				   _("Note: Occurences after the current cursor positions are not changed.")),
				_("Replace all"),
				wxOK | wxICON_INFORMATION);
		}
		else
		{
			wxLogError(wxT("Unknown find dialog event!"));
			UNREACHABLEC;
		}
	}

	int MutEditFile::DoFind(const wxString & pattern, FindFlags flags) 
	{
		if (flags.useCaret && GetCurrentPos() != GetTargetStart()) {
			SetTargetStart(GetCurrentPos());
			SetTargetEnd(flags.down?GetLength():0);
		} else {
			if (flags.down) {
				int i = GetTargetEnd();
				SetTargetEnd(GetLength());
				SetTargetStart(i);
			} else {
				int i = GetTargetStart();
				SetTargetEnd(0);
				SetTargetStart(i);
			}
		}
		int result = SearchInTarget(pattern);
		if (result < 0 && flags.askCircular) {
			int dlgresult;
			if (flags.down) {
				dlgresult = 
					wxMessageBox(
						_("Search reached the end of the file.\nProceed from the beginning?"),
						_("Search"),
						wxYES_NO | wxICON_QUESTION);
				SetTargetEnd(GetLength());
				SetTargetStart(0);
			} else {
				dlgresult = 
					wxMessageBox(
						_("Search reached the beginning of the file.\nProceed from the end?"),
						_("Search"),
						wxYES_NO | wxICON_QUESTION);
				SetTargetEnd(0);
				SetTargetStart(GetLength());
			}
			if (dlgresult == wxNO) return result;
			result = SearchInTarget(pattern);
		}
		if (result < 0 && flags.showNotFound) {
			wxMessageBox(
				_("The search string was not found."),
				_("Search"),
				wxOK | wxICON_INFORMATION);
		} else  {
			if (flags.useCaret) {
				SetCurrentPos(GetTargetStart());
				SetSelection(GetTargetStart(),GetTargetEnd());
			}
		}
			
		TRACEC;
		return result;
		
	}

	void MutEditFile::OnReplace (wxCommandEvent & event) {
		SearchAnchor();
		OnReplaceNext(event);
		if ( m_dlgReplace )
		{
			delete m_dlgReplace;
			m_dlgReplace = NULL;
		}
		else
		{
			m_dlgReplace = new wxFindReplaceDialog(this,
							       &m_findData,
							       _T("Find and replace dialog"),
							       wxFR_REPLACEDIALOG
				);

			m_dlgReplace->Show(true);
		}
	}

	void MutEditFile::OnReplaceNext (wxCommandEvent &WXUNUSED(event)) {
	}

	void MutEditFile::OnBraceMatch (wxCommandEvent &WXUNUSED(event)) {
		int min = GetCurrentPos ();
		int max = BraceMatch (min);
		if (max > (min+1)) {
			BraceHighlight (min, max);
			SetSelection (min+1, max);
		}else{
			BraceBadLight (min);
		}
	}

	void MutEditFile::OnGoto (wxCommandEvent &WXUNUSED(event)) {
		long linenr = wxGetNumberFromUser(_("Where shall we jump to?"),
						  _("Line No.:"),
						  _("Goto"),
						  -1,
						  1,
						  GetLineCount(),
						  this);
		if (linenr > 0)
			GotoLine(linenr-1);
	}

	void MutEditFile::OnEditIndentInc (wxCommandEvent &WXUNUSED(event)) {
		CmdKeyExecute (wxSTC_CMD_TAB);
	}

	void MutEditFile::OnEditIndentRed (wxCommandEvent &WXUNUSED(event)) {
		CmdKeyExecute (wxSTC_CMD_DELETEBACK);
	}

	void MutEditFile::OnEditSelectAll (wxCommandEvent &WXUNUSED(event)) {
		SetSelection (0, GetTextLength ());
	}

	void MutEditFile::OnEditSelectLine (wxCommandEvent &WXUNUSED(event)) {
		int lineStart = PositionFromLine (GetCurrentLine());
		int lineEnd = PositionFromLine (GetCurrentLine() + 1);
		SetSelection (lineStart, lineEnd);
	}

	void MutEditFile::OnHilightLang (wxCommandEvent &event) {
		InitializePrefs (g_LanguagePrefs [event.GetId() - CM_HILIGHTFIRST].name);
	}

	void MutEditFile::OnDisplayEOL (wxCommandEvent &WXUNUSED(event)) {
		SetViewEOL (!GetViewEOL());
	}

	void MutEditFile::OnIndentGuide (wxCommandEvent &WXUNUSED(event)) {
		SetIndentationGuides (!GetIndentationGuides());
	}

	void MutEditFile::OnLineNumber (wxCommandEvent &WXUNUSED(event)) {
		SetMarginWidth (m_LineNrID,
				GetMarginWidth (m_LineNrID) == 0? m_LineNrMargin: 0);
	}

	void MutEditFile::OnLongLineOn (wxCommandEvent &WXUNUSED(event)) {
		SetEdgeMode (GetEdgeMode() == 0? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
	}

	void MutEditFile::OnWhiteSpace (wxCommandEvent &WXUNUSED(event)) {
		SetViewWhiteSpace (GetViewWhiteSpace() == 0?
				   wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
	}

	void MutEditFile::OnFoldToggle (wxCommandEvent &WXUNUSED(event)) {
		ToggleFold (GetFoldParent(GetCurrentLine()));
	}

	void MutEditFile::OnSetOverType (wxCommandEvent &WXUNUSED(event)) {
		SetOvertype (!GetOvertype());
	}

	void MutEditFile::OnSetReadOnly (wxCommandEvent &WXUNUSED(event)) {
		SetReadOnly (!GetReadOnly());
	}

	void MutEditFile::OnWrapmodeOn (wxCommandEvent &WXUNUSED(event)) {
		SetWrapMode (GetWrapMode() == 0? wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);
	}

	void MutEditFile::OnUseCharset (wxCommandEvent &event) {
		int Nr;
		int charset = GetCodePage();
		switch (event.GetId()) {
		case CM_CHARSETANSI: {charset = wxSTC_CHARSET_ANSI; break;}
		case CM_CHARSETMAC: {charset = wxSTC_CHARSET_ANSI; break;}
		}
		for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
			StyleSetCharacterSet (Nr, charset);
		}
		SetCodePage (charset);
	}

	void MutEditFile::OnChangeCase (wxCommandEvent &event) {
		switch (event.GetId()) {
		case CM_CHANGELOWER: {
			CmdKeyExecute (wxSTC_CMD_LOWERCASE);
			break;
		}
		case CM_CHANGEUPPER: {
			CmdKeyExecute (wxSTC_CMD_UPPERCASE);
			break;
		}
		}
	}

	void MutEditFile::OnConvertEOL (wxCommandEvent &event) {
		int eolMode = GetEOLMode();
		switch (event.GetId()) {
		case CM_CONVERTCR: { eolMode = wxSTC_EOL_CR; break;}
		case CM_CONVERTCRLF: { eolMode = wxSTC_EOL_CRLF; break;}
		case CM_CONVERTLF: { eolMode = wxSTC_EOL_LF; break;}
		}
		ConvertEOLs (eolMode);
		SetEOLMode (eolMode);
	}

//! misc
	void MutEditFile::OnMarginClick (wxStyledTextEvent &event) {
		if (event.GetMargin() == 2) {
			int lineClick = LineFromPosition (event.GetPosition());
			int levelClick = GetFoldLevel (lineClick);
			if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0) {
				ToggleFold (lineClick);
			}
		}
	}

	void MutEditFile::OnCharAdded (wxStyledTextEvent &event) {
		char chr = (char)event.GetKey();
		int currentLine = GetCurrentLine();
		// Change this if support for mac files with \r is needed
		if (chr == '\n') {
			int lineInd = 0;
			if (currentLine > 0) {
				lineInd = GetLineIndentation(currentLine - 1);
			}
			if (lineInd == 0) return;
			SetLineIndentation (currentLine, lineInd);
			GotoPos(PositionFromLine (currentLine) + lineInd);
		}
	}


//----------------------------------------------------------------------------
// private functions
	wxString MutEditFile::DeterminePrefs (const wxString &filename) {

		LanguageInfo const* curInfo;

		// determine language from filepatterns
		int languageNr;
		for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++) {
			curInfo = &g_LanguagePrefs [languageNr];
			wxString filepattern = curInfo->filepattern;
			filepattern.Lower();
			while (!filepattern.empty()) {
				wxString cur = filepattern.BeforeFirst (';');
				if ((cur == filename) ||
				    (cur == (filename.BeforeLast ('.') + _T(".*"))) ||
				    (cur == (_T("*.") + filename.AfterLast ('.')))) {
					return curInfo->name;
				}
				filepattern = filepattern.AfterFirst (';');
			}
		}
		return wxEmptyString;

	}

	bool MutEditFile::InitializePrefs (const wxString &name) {

		// initialize styles
		StyleClearAll();
		LanguageInfo const* curInfo = NULL;

		// determine language
		bool found = false;
		int languageNr;
		for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++) {
			curInfo = &g_LanguagePrefs [languageNr];
			if (curInfo->name == name) {
				found = true;
				break;
			}
		}
		if (!found) return false;

		// set lexer and language
		SetLexer (curInfo->lexer);
		m_language = curInfo;

		// set margin for line numbers
		SetMarginType (m_LineNrID, wxSTC_MARGIN_NUMBER);
		StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (_T("DARK GREY")));
		StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
		SetMarginWidth (m_LineNrID, 0); // start out not visible

		// default fonts for all styles!
		int Nr;
		for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
			wxFont font (10, wxMODERN, wxNORMAL, wxNORMAL);
			StyleSetFont (Nr, font);
		}

		// set common styles
		StyleSetForeground (wxSTC_STYLE_DEFAULT, wxColour (_T("DARK GREY")));
		StyleSetForeground (wxSTC_STYLE_INDENTGUIDE, wxColour (_T("DARK GREY")));

		// initialize settings
		if (g_CommonPrefs.syntaxEnable) {
			int keywordnr = 0;
			for (Nr = 0; Nr < STYLE_TYPES_COUNT; Nr++) {
				if (curInfo->styles[Nr].type == -1) continue;
				const StyleInfo &curType = g_StylePrefs [curInfo->styles[Nr].type];
				wxFont font (curType.fontsize, wxMODERN, wxNORMAL, wxNORMAL, false,
					     curType.fontname);
				StyleSetFont (Nr, font);
				if (curType.foreground) {
					StyleSetForeground (Nr, wxColour (curType.foreground));
				}
				if (curType.background) {
					StyleSetBackground (Nr, wxColour (curType.background));
				}
				StyleSetBold (Nr, (curType.fontstyle & MutSTC_STYLE_BOLD) > 0);
				StyleSetItalic (Nr, (curType.fontstyle & MutSTC_STYLE_ITALIC) > 0);
				StyleSetUnderline (Nr, (curType.fontstyle & MutSTC_STYLE_UNDERL) > 0);
				StyleSetVisible (Nr, (curType.fontstyle & MutSTC_STYLE_HIDDEN) == 0);
				StyleSetCase (Nr, curType.lettercase);
				const wxChar *pwords = curInfo->styles[Nr].words;
				if (pwords) {
					SetKeyWords (keywordnr, pwords);
					keywordnr += 1;
				}
			}
		}

		// set margin as unused
		SetMarginType (m_DividerID, wxSTC_MARGIN_SYMBOL);
		SetMarginWidth (m_DividerID, 0);
		SetMarginSensitive (m_DividerID, false);

		// folding
		SetMarginType (m_FoldingID, wxSTC_MARGIN_SYMBOL);
		SetMarginMask (m_FoldingID, wxSTC_MASK_FOLDERS);
		StyleSetBackground (m_FoldingID, *wxWHITE);
		SetMarginWidth (m_FoldingID, 0);
		SetMarginSensitive (m_FoldingID, false);
		if (g_CommonPrefs.foldEnable) {
			SetMarginWidth (m_FoldingID, curInfo->folds != 0? m_FoldingMargin: 0);
			SetMarginSensitive (m_FoldingID, curInfo->folds != 0);
			SetProperty (_T("fold"), curInfo->folds != 0? _T("1"): _T("0"));
			SetProperty (_T("fold.comment"),
				     (curInfo->folds & MutSTC_FOLD_COMMENT) > 0? _T("1"): _T("0"));
			SetProperty (_T("fold.compact"),
				     (curInfo->folds & MutSTC_FOLD_COMPACT) > 0? _T("1"): _T("0"));
			SetProperty (_T("fold.preprocessor"),
				     (curInfo->folds & MutSTC_FOLD_PREPROC) > 0? _T("1"): _T("0"));
			SetProperty (_T("fold.html"),
				     (curInfo->folds & MutSTC_FOLD_HTML) > 0? _T("1"): _T("0"));
			SetProperty (_T("fold.html.preprocessor"),
				     (curInfo->folds & MutSTC_FOLD_HTMLPREP) > 0? _T("1"): _T("0"));
			SetProperty (_T("fold.comment.python"),
				     (curInfo->folds & MutSTC_FOLD_COMMENTPY) > 0? _T("1"): _T("0"));
			SetProperty (_T("fold.quotes.python"),
				     (curInfo->folds & MutSTC_FOLD_QUOTESPY) > 0? _T("1"): _T("0"));
		}
		SetFoldFlags (wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED |
			      wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

		// set spaces and indention
		SetTabWidth (4);
		SetUseTabs (false);
		SetTabIndents (true);
		SetBackSpaceUnIndents (true);
		SetIndent (g_CommonPrefs.indentEnable? 4: 0);

		// others
		SetViewEOL (g_CommonPrefs.displayEOLEnable);
		SetIndentationGuides (g_CommonPrefs.indentGuideEnable);
		SetEdgeColumn (80);
		SetEdgeMode (g_CommonPrefs.longLineOnEnable? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
		SetViewWhiteSpace (g_CommonPrefs.whiteSpaceEnable?
				   wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
		SetOvertype (g_CommonPrefs.overTypeInitial);
		SetReadOnly (g_CommonPrefs.readOnlyInitial);
		SetWrapMode (g_CommonPrefs.wrapModeInitial?
			     wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);

		return true;
	}

	bool MutEditFile::LoadFile ()
	{
#if wxUSE_FILEDLG
		// get filname
		if (!m_filename) {
			wxFileDialog dlg (this, _T("Open file"), wxEmptyString, wxEmptyString,
					  _T("Any file (*)|*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
			if (dlg.ShowModal() != wxID_OK) return false;
			m_filename = dlg.GetPath();
		}

		// load file
		return LoadFile (m_filename);
#else
		return false;
#endif // wxUSE_FILEDLG
	}

	bool MutEditFile::LoadFile (const wxString &filename) {
		return DoLoadFile(filename,0);
#if 0
		if (!filename.empty()) m_filename = filename;
		ClearAll ();

		wxStyledTextCtrl::LoadFile(m_filename);

		EmptyUndoBuffer();

		// determine lexer language
		wxFileName fname (m_filename);
		InitializePrefs (DeterminePrefs (fname.GetFullName()));

		return true;
#endif
	}

	bool MutEditFile::SaveFile ()
	{
#if wxUSE_FILEDLG
		// return if no change
		if (!IsModified()) return true;

		// get filname
		if (!m_filename) {
			wxFileDialog dlg (this, _T("Save file"), wxEmptyString, wxEmptyString, _T("Any file (*)|*"),
					  wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
			if (dlg.ShowModal() != wxID_OK) return false;
			m_filename = dlg.GetPath();
		}

		// save file
		return SaveFile (m_filename);
#else
		return false;
#endif // wxUSE_FILEDLG
	}

	bool MutEditFile::SaveFile (const wxString &filename) {
		// \todo check whether this works with wxWidgets >2.9.0

#if 0 && wxUSE_TEXTCTRL
		return wxStyledTextCtrl::SaveFile(filename);
#else 
		return DoSaveFile(filename,0);
#endif

	}

	bool MutEditFile::IsModified () {

		// return modified state
		return (GetModify() && !GetReadOnly());
	}

	void MutEditFile::OnProperties (wxCommandEvent &WXUNUSED(event)) {
		MutEditProperties dlg(this, 0);
	}

//----------------------------------------------------------------------------
// MutEditProperties
//----------------------------------------------------------------------------

	MutEditProperties::MutEditProperties (MutEditFile *edit,
					long style)
		: wxDialog (edit, wxID_ANY, wxEmptyString,
			    wxDefaultPosition, wxDefaultSize,
			    style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

		// sets the application title
		SetTitle (_("Properties"));
		wxString text;

		// fullname
		wxBoxSizer *fullname = new wxBoxSizer (wxHORIZONTAL);
		fullname->Add (10, 0);
		fullname->Add (new wxStaticText (this, wxID_ANY, _("Full filename"),
						 wxDefaultPosition, wxSize(80, wxDefaultCoord)),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);
		fullname->Add (new wxStaticText (this, wxID_ANY, edit->GetFilename()),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);

		// text info
		wxGridSizer *textinfo = new wxGridSizer (4, 0, 2);
		textinfo->Add (new wxStaticText (this, wxID_ANY, _("Language"),
						 wxDefaultPosition, wxSize(80, wxDefaultCoord)),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		textinfo->Add (new wxStaticText (this, wxID_ANY, edit->m_language->name),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
		textinfo->Add (new wxStaticText (this, wxID_ANY, _("Lexer-ID: "),
						 wxDefaultPosition, wxSize(80, wxDefaultCoord)),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		text = wxString::Format (_T("%d"), edit->GetLexer());
		textinfo->Add (new wxStaticText (this, wxID_ANY, text),
			       0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
		wxString EOLtype = wxEmptyString;
		switch (edit->GetEOLMode()) {
		case wxSTC_EOL_CR: {EOLtype = _T("CR (Unix)"); break; }
		case wxSTC_EOL_CRLF: {EOLtype = _T("CRLF (Windows)"); break; }
		case wxSTC_EOL_LF: {EOLtype = _T("CR (Macintosh)"); break; }
		}
		textinfo->Add (new wxStaticText (this, wxID_ANY, _("Line endings"),
						 wxDefaultPosition, wxSize(80, wxDefaultCoord)),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		textinfo->Add (new wxStaticText (this, wxID_ANY, EOLtype),
			       0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);

		// text info box
		wxStaticBoxSizer *textinfos = new wxStaticBoxSizer (
			new wxStaticBox (this, wxID_ANY, _("Informations")),
			wxVERTICAL);
		textinfos->Add (textinfo, 0, wxEXPAND);
		textinfos->Add (0, 6);

		// statistic
		wxGridSizer *statistic = new wxGridSizer (4, 0, 2);
		statistic->Add (new wxStaticText (this, wxID_ANY, _("Total lines"),
						  wxDefaultPosition, wxSize(80, wxDefaultCoord)),
				0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		text = wxString::Format (_T("%d"), edit->GetLineCount());
		statistic->Add (new wxStaticText (this, wxID_ANY, text),
				0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
		statistic->Add (new wxStaticText (this, wxID_ANY, _("Total chars"),
						  wxDefaultPosition, wxSize(80, wxDefaultCoord)),
				0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		text = wxString::Format (_T("%d"), edit->GetTextLength());
		statistic->Add (new wxStaticText (this, wxID_ANY, text),
				0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
		statistic->Add (new wxStaticText (this, wxID_ANY, _("Current line"),
						  wxDefaultPosition, wxSize(80, wxDefaultCoord)),
				0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		text = wxString::Format (_T("%d"), edit->GetCurrentLine());
		statistic->Add (new wxStaticText (this, wxID_ANY, text),
				0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
		statistic->Add (new wxStaticText (this, wxID_ANY, _("Current pos"),
						  wxDefaultPosition, wxSize(80, wxDefaultCoord)),
				0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
		text = wxString::Format (_T("%d"), edit->GetCurrentPos());
		statistic->Add (new wxStaticText (this, wxID_ANY, text),
				0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);

		// char/line statistics
		wxStaticBoxSizer *statistics = new wxStaticBoxSizer (
			new wxStaticBox (this, wxID_ANY, _("Statistics")),
			wxVERTICAL);
		statistics->Add (statistic, 0, wxEXPAND);
		statistics->Add (0, 6);

		// total pane
		wxBoxSizer *totalpane = new wxBoxSizer (wxVERTICAL);
		totalpane->Add (fullname, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		totalpane->Add (0, 6);
		totalpane->Add (textinfos, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		totalpane->Add (0, 10);
		totalpane->Add (statistics, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		totalpane->Add (0, 6);
		wxButton *okButton = new wxButton (this, wxID_OK, _("OK"));
		okButton->SetDefault();
		totalpane->Add (okButton, 0, wxALIGN_CENTER | wxALL, 10);

		SetSizerAndFit (totalpane);

		ShowModal();
	}

#if wxUSE_PRINTING_ARCHITECTURE

//----------------------------------------------------------------------------
// MutEditPrint
//----------------------------------------------------------------------------

	MutEditPrint::MutEditPrint (MutView * view, MutEditFile *edit, const wxString & title)
		: wxDocPrintout(view,title) {
		m_edit = edit;
	}

	bool MutEditPrint::OnPrintPage (int page) {

		wxDC *dc = GetDC();
		if (!dc) return false;

		// scale DC
		PrintScaling (dc);
		
		mutASSERT(0 < page);
		mutASSERT(page <= (int)m_ranges.size());
		std::pair <int,int> positions = m_ranges[page-1];

		m_edit->FormatRange (1, positions.first, positions.second,
				     dc, dc, m_printRect, m_pageRect);

		return true;
	}

	bool MutEditPrint::OnBeginDocument (int startPage, int endPage) {

		if (!wxDocPrintout::OnBeginDocument (startPage, endPage)) {
			return false;
		}

		return true;
	}

	void MutEditPrint::GetPageInfo (int *minPage,
					int *maxPage, 
					int *selPageFrom, 
					int *selPageTo) {

		// initialize values
		*minPage = 0;
		*maxPage = 0;
		*selPageFrom = 0;
		*selPageTo = 0;

		// scale DC if possible
		wxDC *dc = GetDC();
		if (!dc) return;
		PrintScaling (dc);

		// get print page informations and convert to printer pixels
		wxSize ppiScr;
		GetPPIScreen (&ppiScr.x, &ppiScr.y);
                DEBUGLOG(editor,_T("Screen resolution %dx%d ppi"),ppiScr.x,ppiScr.y);

		wxSize ppiPrint;
		GetPPIPrinter (&ppiPrint.x, &ppiPrint.y);
                DEBUGLOG(editor,_T("Printer resolution %dx%d ppi"),
                         ppiPrint.x,
                         ppiPrint.y);

                wxRect paper = GetPaperRectPixels();
		DEBUGLOG(editor,_T("Paper rect in pixels: x=%d, y=%d, w=%d, h=%d"),
			 paper.x,
			 paper.y,
			 paper.width,
			 paper.height);

                wxSize page;
		GetPageSizePixels(&page.x,&page.y);
		DEBUGLOG(editor,_T("Page size in pixels: %dx%d"),
			 page.x,
			 page.y);


 		page.x = static_cast<int> ((page.x * ppiScr.x) / ppiPrint.x);
		page.y = static_cast<int> ((page.y * ppiScr.y) / ppiPrint.y);
 		paper.x = static_cast<int> ((paper.x * ppiScr.x) / ppiPrint.x);
		paper.y = static_cast<int> ((paper.y * ppiScr.y)/ ppiPrint.y);
		paper.width = static_cast<int> (paper.width * ppiScr.x
		/ ppiPrint.x);
		paper.height = static_cast<int> (paper.height *
		ppiScr.y / ppiPrint.y);
		DEBUGLOG(editor,_T("Page size in pixels: %dx%d"),
			 page.x,
			 page.y);
		DEBUGLOG(editor,_T("Paper rect in pixels: x=%d, y=%d, w=%d, h=%d"),
			 paper.x,
			 paper.y,
			 paper.width,
			 paper.height);

		m_pageRect = page;

                int left = 15; // mm
                int top = 15; // mm
                int right = 15; // mm
                int bottom = 15; // mm



		top = static_cast<int> (top * ppiScr.y / 25.4);
		bottom = static_cast<int> (bottom * ppiScr.y / 25.4);
		left = static_cast<int> (left * ppiScr.x / 25.4);
		right = static_cast<int> (right * ppiScr.x / 25.4);
		DEBUGLOG(editor,
                         _T("Margins (pixels): top=%d, bottom=%d, left=%d, right=%d"),
			 top,
			 bottom,
			 left,
			 right);

                // adapat margin to correct results paper.x/paper.y is
                // negative if print area is provided
                left = std::max(paper.x + left,0);
                right = std::max(right - (paper.width + paper.x - page.x),0);
                top = std::max(paper.y + top,0);
                bottom = std::max(bottom - (paper.height + paper.y - page.y),0);
		DEBUGLOG(editor,
                         _T("Margins (pixels): top=%d, bottom=%d, left=%d, right=%d"),
			 top,
			 bottom,
			 left,
			 right);

		m_printRect = wxRect (left,
				      top,
				      page.x - (left + right),
				      page.y - (top + bottom));
		DEBUGLOG(editor,_T("Print rect (pixels): x=%d, y=%d, w=%d, h=%d"),
			 m_printRect.x,
			 m_printRect.y,
			 m_printRect.width,
			 m_printRect.height);

		// count pages
		int currpos = 0;
		int maxpos = m_edit->GetLength();
                *maxPage = 0;
		while (currpos < maxpos) {
			// print from oldpos to maxpos 
			// (returning the positon for next page)
			int oldpos = currpos;
			currpos = m_edit->FormatRange (0, oldpos, maxpos,
						       dc, dc, 
						       m_printRect, m_pageRect);
			m_ranges.push_back(std::pair<int,int>(oldpos, currpos));
			*maxPage += 1;
                        DEBUGLOG(editor,_T("Page %d: %d–%d"),*maxPage,oldpos,currpos);
		}
		if (*maxPage > 0) *minPage = 1;
		*selPageFrom = *minPage;
		*selPageTo = *maxPage;
                DEBUGLOG(editor,
                         _T("pages %d-%d, selected pages %d-%d"),
                         (*minPage),
                         (*maxPage),
                         (*selPageFrom),
                         (*selPageTo));
	}

	bool MutEditPrint::HasPage (int page) {
		return page <= (int)m_ranges.size();
	}

	bool MutEditPrint::PrintScaling (wxDC *dc){

		// check for dc, return if none
		if (!dc) return false;

		// get printer and screen sizing values
		wxSize ppiScr;
		GetPPIScreen (&ppiScr.x, &ppiScr.y);
		if (ppiScr.x == 0) { // most possible guess 96 dpi
			ppiScr.x = 96;
			ppiScr.y = 96;
		}
		wxSize ppiPrt;
		GetPPIPrinter (&ppiPrt.x, &ppiPrt.y);
		if (ppiPrt.x == 0) { // scaling factor to 1
			ppiPrt.x = ppiScr.x;
			ppiPrt.y = ppiScr.y;
		}
		wxSize dcSize = dc->GetSize();
                DEBUGLOG(editor,_T("DC size: %dx%d"),dcSize.x,dcSize.y);
		wxSize pageSize;
		GetPageSizePixels (&pageSize.x, &pageSize.y);

		// set user scale
		float scale_x = (float)(ppiPrt.x * dcSize.x) /
			(float)(ppiScr.x * pageSize.x);
		float scale_y = (float)(ppiPrt.y * dcSize.y) /
			(float)(ppiScr.y * pageSize.y);
		dc->SetUserScale (scale_x, scale_y);
                DEBUGLOG(editor,_T("Scaled page by %gx%g"),scale_x,scale_y);

		return true;
	}

#endif



#if 0
	wxString MutEditFile::GetRange(long from, long to) const

	{
		
		DEBUGLOG(other,_T("(from %ld, to %ld)"),from,to);
		wxString str;

		if ( from >= to && to != -1 ) {
			// nothing to retrieve
			return str;
		}

#if wxUSE_RICHEDIT
		if ( IsRich() ) {
			int len = GetWindowTextLength(GetHwnd());

			DEBUGLOG(other,_T("len = %d"),len);

			if ( len > from ) {
				if ( to == -1 )
					to = len;

				DEBUGLOG(other,_T("to = %d"), to);

#if !(wxUSE_UNICODE || wxUSE_WCHAR_T)
				// we must use EM_STREAMOUT if we don't want to lose all characters
				// not representable in the current character set (EM_GETTEXTRANGE
				// simply replaces them with question marks...)
				if ( GetRichVersion() > 1 ) {
					// we must have some encoding, otherwise any 8bit chars in the
					// control are simply *lost* (replaced by '?')
					wxFontEncoding encoding = wxFONTENCODING_SYSTEM;

					wxFont font = m_defaultStyle.GetFont();

					if ( !font.Ok() )
						font = GetFont();

					if ( font.Ok() ) {
						encoding = font.GetEncoding();
					}

					if ( encoding == wxFONTENCODING_SYSTEM ) {
						encoding = wxLocale::GetSystemEncoding();
					}

					if ( encoding == wxFONTENCODING_SYSTEM ) {
						encoding = wxFONTENCODING_ISO8859_1;
					}

					str = StreamOut(encoding);


					DEBUGLOG(other,_T("str.Len() = %d"),
						 str.Len());

					if ( !str.empty() ) {
						// we have to manually extract the required part, luckily
						// this is easy in this case as EOL characters in str are
						// just LFs because we remove CRs in mutRichEditStreamOut
						str = str.Mid(from, to - from);
						DEBUGLOG(other,_T("str.Len() = %d"),
							 str.Len());
					}
				}

				// StreamOut() wasn't used or failed, try to do it in normal way
				if ( str.empty() )
#endif // !wxUSE_UNICODE
				{
					// alloc one extra WORD as needed by the control
					wxStringBuffer tmp(str, ++len);
					wxChar *p = tmp;

					TEXTRANGE textRange;
					textRange.chrg.cpMin = from;
					textRange.chrg.cpMax = to;
					textRange.lpstrText = p;

					(void)::SendMessage(GetHwnd(), EM_GETTEXTRANGE,
							    0, (LPARAM)&textRange);

					if ( m_verRichEdit > 1 )
					{
						// RichEdit 2.0 uses just CR ('\r') for the
						// newlines which is neither Unix nor Windows
						// style - convert it to something reasonable

						for ( ; *p; p++ ) {
							if ( *p == _T('\r') )
								*p = _T('\n');
						}
					}
				}

				if ( m_verRichEdit == 1 ) {
					// convert to the canonical form - see comment below
					str = wxTextFile::Translate(str, wxTextFileType_Unix);
				}
			}

			//else: no text at all, leave the string empty
		} else
#endif // wxUSE_RICHEDIT {
			// retrieve all text
			str = wxGetWindowText(GetHWND());

		DEBUGLOG(other,_T("str.Len() = %d"), str.Len());

		// need only a range?
		if ( from < to ) {
			str = str.Mid(from, to - from);
			DEBUGLOG(other,_T("str.Len() = %d"), str.Len());
		}

		// WM_GETTEXT uses standard DOS CR+LF (\r\n) convention - convert to the
		// canonical one (same one as above) for consistency with the other kinds
		// of controls and, more importantly, with the other ports
		str = wxTextFile::Translate(str, wxTextFileType_Unix);

		DEBUGLOG(other,_T("str.Len() = %d"), str.Len());
	}

	return str;
}


#if wxUSE_RICHEDIT && (!(wxUSE_UNICODE || wxUSE_WCHAR_T) || wxUSE_UNICODE_MSLU)

// a small class used to set m_updatesCount to 0 (to filter duplicate events if
// necessary) and to reset it back to -1 afterwards

class UpdatesCountFilter
{

public:
	UpdatesCountFilter(int& count)
		: m_count(count)
		{
			mutASSERT_MSG( m_count == -1 || m_count == -2,
				      _T("wrong initial m_updatesCount value") );

			if (m_count != -2)
				m_count = 0;

			//else: we don't want to count how many update events we get as we're going
			//      to ignore all of them
		}

	~UpdatesCountFilter()
		{
			m_count = -1;
		}

	// return true if an event has been received

	bool GotUpdate() const
		{
			return m_count == 1;
		}

private:

	int& m_count;

	DECLARE_NO_COPY_CLASS(UpdatesCountFilter)
};



// TODO: using memcpy() would improve performance a lot for big amounts of text

DWORD CALLBACK
mutRichEditStreamIn(DWORD dwCookie, BYTE *buf, LONG cb, LONG *pcb)
{
	*pcb = 0;

	const wchar_t ** const ppws = (const wchar_t **)dwCookie;

	wchar_t *wbuf = (wchar_t *)buf;

	const wchar_t *wpc = *ppws;

	while ( cb && *wpc ) {
		*wbuf++ = *wpc++;

		cb -= sizeof(wchar_t);
		(*pcb) += sizeof(wchar_t);
	}

	*ppws = wpc;

	return 0;
}

// helper struct used to pass parameters from wxTextCtrl to mutRichEditStreamOut

struct wxStreamOutData
{
	wchar_t *wpc;
	size_t len;
};

DWORD CALLBACK
mutRichEditStreamOut(DWORD_PTR dwCookie, BYTE *buf, LONG cb, LONG *pcb)
{
	DEBUGLOG(other,_T("dwCookie = %p, buf = %p, cb = %ld, pcb = %p"),
		 dwCookie, buf, cb, pcb);
	*pcb = 0;

	wxStreamOutData *data = (wxStreamOutData *)dwCookie;

	const wchar_t *wbuf = (const wchar_t *)buf;

	wchar_t *wpc = data->wpc;

	DEBUGLOG(other,_T("wpc = %ld"), wpc);

	while ( cb ) {
		wchar_t wch = *wbuf++;
		char string[sizeof(wchar_t)+1];
		string[sizeof(wchar_t)] = 0;
		(wchar_t &)*string = wch;

		DEBUGLOG(other,_T("%s"),(const wxChar *)wxString(string));

		// turn "\r\n" into "\n" on the fly
//        if ( wch != L'\r' ) {
		*wpc++ = wch;
//        } else {
//            data->len--;
//		}
		cb -= sizeof(wchar_t);
		(*pcb) += sizeof(wchar_t);
	}

	data->wpc = wpc;

	DEBUGLOG(other,_T("wpc = %ld"), wpc);

	return 0;
}


#if wxUSE_UNICODE_MSLU
#define UNUSED_IF_MSLU(param)
#else
#define UNUSED_IF_MSLU(param) param
#endif

bool

MutEditFile::StreamIn(const wxString& value,
                      wxFontEncoding UNUSED_IF_MSLU(encoding),
                      bool selectionOnly)
{
#if wxUSE_UNICODE_MSLU

	const wchar_t *wpc = value.c_str();

#else // !wxUSE_UNICODE_MSLU
	wxCSConv conv(encoding);

	const size_t len = conv.MB2WC(NULL, value, value.length());

#if wxUSE_WCHAR_T
	wxWCharBuffer wchBuf(len);

	wchar_t *wpc = wchBuf.data();

#else
	wchar_t *wchBuf = (wchar_t *)malloc((len + 1)*sizeof(wchar_t));

	wchar_t *wpc = wchBuf;

#endif

	conv.MB2WC(wpc, value, value.length());

#endif // wxUSE_UNICODE_MSLU

	// finally, stream it in the control
	EDITSTREAM eds;

	wxZeroMemory(eds);

	eds.dwCookie = (DWORD)&wpc;

	// the cast below is needed for broken (very) old mingw32 headers
	eds.pfnCallback = (EDITSTREAMCALLBACK)mutRichEditStreamIn;

	// same problem as in DoWriteText(): we can get multiple events here
	UpdatesCountFilter ucf(m_updatesCount);

	::SendMessage(GetHwnd(), EM_STREAMIN,
	              SF_TEXT |
	              SF_UNICODE |
	              (selectionOnly ? SFF_SELECTION : 0),
	              (LPARAM)&eds);

	// It's okay for EN_UPDATE to not be sent if the selection is empty and
	// the text is empty, otherwise warn the programmer about it.
	mutASSERT_MSG( ucf.GotUpdate() || ( !HasSelection() && value.empty() ),
	              _T("EM_STREAMIN didn't send EN_UPDATE?") );

	if ( eds.dwError ) {
		wxLogLastError(_T("EM_STREAMIN"));
	}

#if !wxUSE_WCHAR_T
	free(wchBuf);

#endif // !wxUSE_WCHAR_T

	return true;
}

#if !wxUSE_UNICODE_MSLU

wxString
MutEditFile::StreamOut(wxFontEncoding encoding, bool selectionOnly) const
{
	wxString out;

	const int len = GetWindowTextLength(GetHwnd());

	DEBUGLOG(other,_T("len = %d"), len);

//#if wxUSE_WCHAR_T
//    wxWCharBuffer wchBuf(len+1);
//    wchar_t *wpc = wchBuf.data();
//#else
	wchar_t *wchBuf = (wchar_t *)malloc((len + 2)*sizeof(wchar_t));

	wchar_t *wpc = wchBuf;

//#endif

	wxStreamOutData data;

	data.wpc = wpc;

	data.len = len+1;

	EDITSTREAM eds;

	wxZeroMemory(eds);

	eds.dwCookie = (DWORD)&data;

	eds.pfnCallback = mutRichEditStreamOut;

	::SendMessage
		  (
			  GetHwnd(),
			  EM_STREAMOUT,
			  SF_TEXT | SF_UNICODE | (selectionOnly ? SFF_SELECTION : 0),
			  (LPARAM)&eds
			  );

	if ( eds.dwError ) {
		wxLogLastError(_T("EM_STREAMOUT"));
	} else // streamed out ok
	{
		// NUL-terminate the string because its length could have been
		// decreased by mutRichEditStreamOut
//#ifdef wxUSE_WCHAR_T
//        *(wchBuf.data() + data.len) = _T('\0');
//#else
		wchBuf[data.len] = 0;
//#endif

		DEBUGLOG(other,_T("len = %d"), len);
		wxString test("test");

		// now convert to the given encoding (this is a possibly lossful
		// conversion but what else can we do)
		wxCSConv conv(encoding);
		size_t lenNeeded = conv.WC2MB(NULL, wchBuf, 0);
//        size_t lenNeeded = conv.MB2WC( wchBuf, NULL,0);
		DEBUGLOG(other,_T("len = %d"), len);
		DEBUGLOG(other,_T("lenNeeded = %d"), lenNeeded);
		DEBUGLOG(other,_T("wchBuf[len] = %d"), wchBuf[len]);
		DEBUGLOG(other,_T("wchBuf[lenNeeded] = %d"), wchBuf[lenNeeded]);
		out.Alloc(lenNeeded+1);
		//wxStringBuffer buf(out, lenNeeded+1);

		if ( lenNeeded++ ) {
			char string[sizeof(wchar_t)+1];
			string[sizeof(wchar_t)] = 0;

			for (int i=0; i<= len; i++) {
				(wchar_t &)*string = wchBuf[i];

				DEBUGLOG(other,_T("%d: %s"),
					 i,(const wxChar *) wxString(string));
				out[i] = *string;
				DEBUGLOG(other,_T(" %s"),
					 (const wxChar *) wxString(out));
				std::cout<< out<<std::endl;
			}

//            conv.WC2MB(wxStringBuffer(out, lenNeeded+1), wchBuf, lenNeeded);
//			conv.MB2WC(wchBuf,wxStringBuffer(out,lenNeeded+1),lenNeeded/2);
		}

		DEBUGLOG(other,_T("lenNeeded = %d"), lenNeeded);
	}


//#if !wxUSE_WCHAR_T
	free(wchBuf);

//#endif // !wxUSE_WCHAR_T

	return out;
}

#endif // !wxUSE_UNICODE_MSLU

#endif // wxUSE_RICHEDIT
#endif

}
///\}
