/** \file
 ***********************************************************************
 * Mutabor MDI-Child.
 *
 * $Id: MutEditFile.h,v 1.10 2010/11/21 13:15:47 keinstein Exp $
 * \author R. Krauﬂe <krausze@users.berlios.de>
 * \date $Date: 2010/11/21 13:15:47 $
 * \version $Revision: 1.10 $
 *
 * $Log: MutEditFile.h,v $
 * Revision 1.10  2010/11/21 13:15:47  keinstein
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
			: wxTextCtrl(parent, wxID_ANY, value, pos, size, wxTE_PROCESS_TAB | wxTE_MULTILINE | wxTE_RICH | wxTE_RICH2 | wxTE_NOHIDESEL | wxHSCROLL , wxDefaultValidator, name)
	{};

protected:
//	void SetupWindow();
	bool DoLoadFile(const wxString &filename, int WXUNUSED(fileType));

	bool DoSaveFile(const wxString& filename, int WXUNUSED(fileType));

	void CmFileSave(wxCommandEvent& WXUNUSED(event));

	void CmFileSaveAs(wxCommandEvent& event);

	void CmCompile(wxCommandEvent& WXUNUSED(event));

	void CmCompAct(wxCommandEvent& WXUNUSED(event));

	void CmGetLine(wxCommandEvent& WXUNUSED(event));

	void CmHelpContext(wxCommandEvent& WXUNUSED(event));

	void GoErrorLine();

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


	muConvAuto autoConverter;

	DECLARE_EVENT_TABLE()
};


#endif // __MUTEDITFILE_H_INCLUDED__
