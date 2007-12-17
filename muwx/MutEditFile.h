/** \file
 ***********************************************************************
 * Mutabor MDI-Child.
 *
 * $Id: MutEditFile.h,v 1.4 2007/12/17 13:00:46 keinstein Exp $
 * \author R. Krauﬂe <krausze@users.berlios.de>
 * \date $Date: 2007/12/17 13:00:46 $
 * \version $Revision: 1.4 $
 *
 * $Log: MutEditFile.h,v $
 * Revision 1.4  2007/12/17 13:00:46  keinstein
 * MutEditFile::DoLoadFile, MutEditFile::DoSaveFile: New functions.
 * Fix compilation in Unicode mode.
 * Copy Some Routines from wxRichEdit to try to circumvent wx/wine incompatibility
 * 	in non-Unicode build
 *
 * Revision 1.3  2006/01/18 15:37:02  keinstein
 * no MDI Windows in some environments
 *
 */

#ifndef __MUTEDITFILE_H_INCLUDED__
#define __MUTEDITFILE_H_INCLUDED__

/////////////////////////////////////////////////////////////////////////////
// Name:        MutChild.h
// Purpose:     Mutabor MDI-Child
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "wx/textctrl.h"
#include "muconvauto.h"

class MutEditFile : public wxTextCtrl
{
  public:
	MutEditFile(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const wxString& value = wxEmptyString, const wxString& name = wxTextCtrlNameStr)
	 : wxTextCtrl(parent, wxID_ANY, value, pos, size, wxTE_PROCESS_TAB | wxTE_MULTILINE | wxTE_RICH | wxTE_RICH2 | wxTE_NOHIDESEL | wxHSCROLL , wxDefaultValidator, name) {};
  protected:
//	void SetupWindow();
	bool DoLoadFile(const wxString &filename, int WXUNUSED(fileType));
	bool DoSaveFile(const wxString& filename, int WXUNUSED(fileType));
	void CmFileSave(wxCommandEvent& WXUNUSED(event));
	void CmCompile(wxCommandEvent& WXUNUSED(event));
	void CmCompAct(wxCommandEvent& WXUNUSED(event));
	void CmGetLine(wxCommandEvent& WXUNUSED(event));
	void CmHelpContext(wxCommandEvent& WXUNUSED(event));
	void GoErrorLine();
#if defined(__WXMSW__) && !(wxUSE_UNICODE)
	wxString GetValue() const;
	wxString GetRange(long from, long to) const;
#if wxUSE_RICHEDIT && (!wxUSE_UNICODE || wxUSE_UNICODE_MSLU)
    // replace the selection or the entire control contents with the given text
    // in the specified encoding
    bool StreamIn(const wxString& value, wxFontEncoding encoding, bool selOnly);

    // get the contents of the control out as text in the given encoding
    wxString StreamOut(wxFontEncoding encoding, bool selOnly = false) const;
#endif // wxUSE_RICHEDIT
#endif
	
	muConvAuto autoConverter;
	
	DECLARE_EVENT_TABLE()
};


#endif // __MUTEDITFILE_H_INCLUDED__
