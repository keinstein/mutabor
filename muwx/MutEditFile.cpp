/** \file 
 ********************************************************************
 * Mutabor Edit window for Mutabor-files
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutEditFile.cpp,v 1.14 2011/02/20 22:35:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/02/20 22:35:57 $
 * \version $Revision: 1.14 $
 * \license GPL
 *
 * $Log: MutEditFile.cpp,v $
 * Revision 1.14  2011/02/20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include "mhDefs.h"

#include <iostream>

#include "wx/wxprec.h"
#include "wx/ffile.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/mdi.h"
#include "wx/filename.h"
#include "wx/textfile.h"
#endif

#include "wx/toolbar.h"


#ifdef __WXMSW__
#include "wx/msw/private.h"

#if wxUSE_RICHEDIT

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
#include "MutFrame.h"
#include "MutEditFile.h"
#include "CompDlg.h"
#include "Runtime.h"

CompDlg *CompDia = NULL;

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MutEditFile, wxTextCtrl)
	//    EVT_MOUSE_EVENTS(MyCanvas::OnEvent)
	EVT_MENU(CM_FILESAVE, MutEditFile::CmFileSave)
	EVT_MENU(CM_FILESAVEAS, MutEditFile::CmFileSaveAs)
	EVT_MENU(CM_COMPILE, MutEditFile::CmCompile)
	EVT_MENU(CM_COMPACT, MutEditFile::CmCompAct)
	EVT_MENU(CM_ACTIVATE, MutEditFile::CmCompAct)
	EVT_MENU(CM_GETLINE, MutEditFile::CmGetLine)
	EVT_MENU(CM_HELPCONTEXT, MutEditFile::CmHelpContext)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================

// Editorfenster

//SETUPWINDOW_FONT(TEditFileMut, TEditFile, EditFont)


bool MutEditFile::DoLoadFile(const wxString &filename, int WXUNUSED(fileType))
{
	DEBUGLOG(mutparser,_T(""));
	wxFFile file(filename);

	if ( file.IsOpened() ) {
		wxString text;

		if ( file.ReadAll(&text, autoConverter) ) {
			DEBUGLOG(mutparser,_T("%s"),text.c_str());

			SetValue(text);
			DiscardEdits();
			m_filename = filename;
			file.Close();
			return true;
		}

#ifdef DEBUG
		else
			DEBUGLOG (mutparser,_T("File opened, but couldn't be loaded."));

#endif
	}

	wxLogError(_("File couldn't be loaded."));
	return false;
}

bool MutEditFile::DoSaveFile(const wxString& filename, int WXUNUSED(fileType))

{
#if wxUSE_FFILE
#ifdef DEBUG
	std::cerr << "MutEditFile::DoSaveFile" << std::endl
	<< (GetValue().fn_str()) << std::endl;
#endif
	wxFFile file(filename, _T("w"));

	if ( file.IsOpened() && file.Write(GetValue(), autoConverter) ) {
		// if it worked, save for future calls
		m_filename = filename;

		// it's not modified any longer
		DiscardEdits();

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
#ifdef DEBUG
	std::cerr << "File saved: " << m_filename.fn_str() << std::endl;
#endif
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

	DEBUGLOG (other, _T("MutEditFile::CmCompile(Event(%d)); filename = %s"),event.GetId(),m_filename.c_str());
	wxString origfilename = m_filename;
	wxString TmpFile = wxFileName::CreateTempFileName(wxT(PACKAGE));

	if ( SaveEditor )
		SaveFile(m_filename);

	bool modified = IsModified();

	if ( LogicOn ) {
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);
		wxPostEvent(GetParent(),event1);
	}

	if ( !SaveFile(TmpFile) ) {
		wxMessageBox(_("Can't write temporary file."), _("Error"), wxOK | wxICON_HAND);
		CompiledFile = wxEmptyString;
	} else {
		if ( modified )
			MarkDirty();

		CompDia = new CompDlg(this);

		CompDia->SetFileName(origfilename);

#ifdef DEBUG
		std::cout << "MutEditile::CmCompile: Parent"
		<< CompDia->GetParent() << std::endl;

#endif
		if (CompDia->GetParent())
			CompDia->Centre();

		CompDia->Show();

		CompDia->MakeModal(true);

		if ( Compile(CompDia, TmpFile.c_str()) )
			CompiledFile = origfilename;
		else {
			CompiledFile = wxEmptyString;
			GoErrorLine();
		}

		CompDia->MakeModal(false);

		CompDia->EnableButton(true);
		CompDia->Hide();
		int r = CompDia->ShowModal();
#ifdef DEBUG
		std::cerr << "MutEditFile::CmCompile return code: "
		<< r << std::endl;
#endif
		wxRemoveFile(TmpFile);
	}

	m_filename = origfilename;

	DEBUGLOG (other, _T("filename (at end) = '%s'"),m_filename.c_str());
	event.Skip(false);
}

void MutEditFile::CmCompAct(wxCommandEvent& event)
{
	wxString TmpFile = wxFileName::CreateTempFileName(wxT(PACKAGE));

	if ( SaveEditor )
		SaveFile(m_filename);

	bool modified = IsModified();

	if ( LogicOn ) {
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);
		wxPostEvent(GetParent(),event1);
	}

	if ( !SaveFile(TmpFile) ) {
		wxMessageBox(_("Can't write temporary file."),
		             _("Error"), wxOK | wxICON_HAND);
		CompiledFile = wxEmptyString;
	} else {
		if ( modified )
			MarkDirty();

		CompDia = new CompDlg(this);

		if (!CompDia->Show()) {
			wxLogError(_("The compile dialog could not be loaded."));
		};

		CompDia->SetFileName(GetName());

		if ( Compile(CompDia, TmpFile.c_str()) ) {
			CompiledFile = m_filename;
			//CompDia->SendMessage(WM_CLOSE);
			CompDia->Destroy();
			wxCommandEvent event2(wxEVT_COMMAND_MENU_SELECTED, CM_DOACTIVATE);
			wxPostEvent(GetParent(),event2);
		} else {
			CompiledFile = wxEmptyString;
			GoErrorLine();
		}

		CompDia->EnableButton(true);

		wxRemoveFile(TmpFile);
	}

	event.Skip(false);
}

void MutEditFile::CmGetLine(wxCommandEvent& WXUNUSED(event))
{
	/*  int LineFirstPos = GetLineIndex(-1);
	  EditLine = GetLineFromPos(LineFirstPos) + 1;
	  uint Sel1, Sel2;
	  GetSelection(Sel1, Sel2);
	  EditRow = Sel2 - LineFirstPos + 1;*/
}

void MutEditFile::GoErrorLine()
{
	/*  int Line = GetErrorLine();
	  if ( Line == -1 ) return;
	  uint pos = GetLineIndex(Line-1);
	  SetSelection(pos, pos);*/
}

void MutEditFile::CmHelpContext(wxCommandEvent& WXUNUSED(event))
{
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
	std::cout << "MutEditFile::GetValue()" << std::endl;
	// range 0..-1 is special for GetRange() and means to retrieve all text
	return GetRange(0, -1);
}

wxString MutEditFile::GetRange(long from, long to) const

{
	std::cout << "MutEditFile::GetRange ("<< from << ", " << to << ")" << std::endl;
	wxString str;

	if ( from >= to && to != -1 ) {
		// nothing to retrieve
		return str;
	}

#if wxUSE_RICHEDIT
	if ( IsRich() ) {
		int len = GetWindowTextLength(GetHwnd());
		std::cout << "MutEditFile::GetRange: len = "<< len << std::endl;

		if ( len > from ) {
			if ( to == -1 )
				to = len;

			std::cout << "MutEditFile::GetRange: to  = "<< to << std::endl;

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

				std::cout << "str = StreamOut(encoding);" << std::endl;

				std::cout << "MutEditFile::GetRange: str.Len  = "<< (str.Len()) << std::endl;

				if ( !str.empty() ) {
					// we have to manually extract the required part, luckily
					// this is easy in this case as EOL characters in str are
					// just LFs because we remove CRs in mutRichEditStreamOut
					str = str.Mid(from, to - from);
					std::cout << "MutEditFile::GetRange: str.Len  = "<< (str.Len()) << std::endl;
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

	std::cout << "str = wxGetWindowText(GetHWND());" << std::endl;

	std::cout << "MutEditFile::GetRange: str.Len  = "<< (str.Len()) << std::endl;

	// need only a range?
	if ( from < to ) {
		str = str.Mid(from, to - from);
		std::cout << "MutEditFile::GetRange: str.Len  = "<< (str.Len()) << std::endl;
	}

	// WM_GETTEXT uses standard DOS CR+LF (\r\n) convention - convert to the
	// canonical one (same one as above) for consistency with the other kinds
	// of controls and, more importantly, with the other ports
	str = wxTextFile::Translate(str, wxTextFileType_Unix);

	std::cout << "MutEditFile::GetRange: str.Len  = "<< (str.Len()) << std::endl;
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
		wxASSERT_MSG( m_count == -1 || m_count == -2,
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
	std::cout << "::mutRichEditStreamOut: dwCookie = " << dwCookie <<
	" buf = " << buf <<
	" cb = " << cb << " pcb = " << pcb << std::endl;
	*pcb = 0;

	wxStreamOutData *data = (wxStreamOutData *)dwCookie;

	const wchar_t *wbuf = (const wchar_t *)buf;

	wchar_t *wpc = data->wpc;

	std::cout << "::mutRichEditStreamOut: wpc = " << wpc << std::endl;

	while ( cb ) {
		wchar_t wch = *wbuf++;
		char string[sizeof(wchar_t)+1];
		string[sizeof(wchar_t)] = 0;
		(wchar_t &)*string = wch;

		std::cout << string;

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

	std::cout << "::mutRichEditStreamOut: wpc = " << wpc << std::endl;

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
	wxASSERT_MSG( ucf.GotUpdate() || ( !HasSelection() && value.empty() ),
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

	std::cout << "MutEditFile::StreamOut: len = " << len << std::endl;

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
		std::cout << "MutEditFile::StreamOut: data.len = " << (data.len) << std::endl;
		wxString test("test");

		// now convert to the given encoding (this is a possibly lossful
		// conversion but what else can we do)
		wxCSConv conv(encoding);
		size_t lenNeeded = conv.WC2MB(NULL, wchBuf, 0);
//        size_t lenNeeded = conv.MB2WC( wchBuf, NULL,0);
		std::cout << "MutEditFile::StreamOut: lenNeeded = " << lenNeeded << std::endl;
		std::cout << wchBuf[len] << " " << std:: endl;
		std::cout << wchBuf[lenNeeded] << " " << std::endl;
//		std::cout << (wxStringBuffer(out,lenNeeded+1)[lenNeeded]) << std::endl;
		std::cout << "MutEditFile::StreamOut: len = " << len << std::endl;
		out.Alloc(lenNeeded+1);
		//wxStringBuffer buf(out, lenNeeded+1);

		if ( lenNeeded++ ) {
			char string[sizeof(wchar_t)+1];
			string[sizeof(wchar_t)] = 0;

			for (int i=0; i<= len; i++) {
				(wchar_t &)*string = wchBuf[i];

				std::cout << i << ": " << string << std::endl;
				out[i] = *string;
				std::cout<< out<<std::endl;
			}

//            conv.WC2MB(wxStringBuffer(out, lenNeeded+1), wchBuf, lenNeeded);
//			conv.MB2WC(wchBuf,wxStringBuffer(out,lenNeeded+1),lenNeeded/2);
		}

		std::cout << "MutEditFile::StreamOut: lenNeeded = " << lenNeeded << std::endl;


//		std::cout << "MutEditFile::StreamOut: test.Len() = " << (test.Len()) << std::endl;
//		out = test;
	}


//#if !wxUSE_WCHAR_T
	free(wchBuf);

//#endif // !wxUSE_WCHAR_T

	return out;
}

#endif // !wxUSE_UNICODE_MSLU

#endif // wxUSE_RICHEDIT

#endif // __WXMSW__ && !wxUSE_UNICODE

///\}
