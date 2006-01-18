/////////////////////////////////////////////////////////////////////////////
// Name:        MutEditFile.cpp
// Purpose:     Mutabor Edit window for Mutabor-files
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/mdi.h"
    #include "wx/filename.h"
#endif

#include "wx/toolbar.h"

#include "Mutabor.rh"
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

wxString TmpFile = wxFileName::CreateTempFileName(wxT(PACKAGE));

void MutEditFile::CmFileSave(wxCommandEvent& WXUNUSED(event))
{
	SaveFile(GetName());
	std::cout << "File saved: " << GetName().fn_str() << std::endl;
}

void MutEditFile::CmCompile(wxCommandEvent& WXUNUSED(event))
{
	if ( SaveEditor )
		SaveFile(GetName());
	bool modified = IsModified();
	if ( LogicOn )
	{
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);
		GetParent()->ProcessEvent(event1);
	}
	if ( !SaveFile(TmpFile) )
	{
		wxMessageBox(_("Can't write temporary file."), _("Error"), wxOK | wxICON_HAND);
		CompiledFile = wxEmptyString;
	}
	else
	{
		if ( modified )
			MarkDirty();
		CompDia = new CompDlg(this);
		CompDia->Show();
		CompDia->SetText(IDC_COMP_FILENAME, GetName());
		if ( Compile(CompDia, TmpFile.fn_str()) )
			CompiledFile = GetName();
		else
		{
			CompiledFile = wxEmptyString;
			GoErrorLine();
		}
		CompDia->FindWindow(wxID_OK)->Enable(TRUE);
		wxRemoveFile(TmpFile);
	}
}

void MutEditFile::CmCompAct(wxCommandEvent& WXUNUSED(event))
{
	if ( SaveEditor )
		SaveFile(GetName());
	bool modified = IsModified();
	if ( LogicOn )
	{
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_STOP);
		GetParent()->ProcessEvent(event1);
	}
	if ( !SaveFile(TmpFile) )
	{
		wxMessageBox(_("Can't write temporary file."), _("Error"), wxOK | wxICON_HAND);
		CompiledFile = wxEmptyString;
	}
	else
	{
		if ( modified )
			MarkDirty();
		CompDia = new CompDlg(this);
		CompDia->Show();
		CompDia->SetText(IDC_COMP_FILENAME, GetName());
		if ( Compile(CompDia, TmpFile.fn_str()) )
		{
			CompiledFile = GetName();
			//CompDia->SendMessage(WM_CLOSE);
			CompDia->Destroy();
			wxCommandEvent event2(wxEVT_COMMAND_MENU_SELECTED, CM_DOACTIVATE);
			GetParent()->AddPendingEvent(event2);
		}
		else
		{
			CompiledFile = wxEmptyString;
			GoErrorLine();
		}
		CompDia->FindWindow(wxID_OK)->Enable(TRUE);
		wxRemoveFile(TmpFile);
	}
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

