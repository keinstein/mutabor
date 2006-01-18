/** \file
 ***********************************************************************
 * Mutabor MDI-Child.
 *
 * $Id: MutEditFile.h,v 1.3 2006/01/18 15:37:02 keinstein Exp $
 * \author R. Krauﬂe <krausze@users.berlios.de>
 * \date $Date: 2006/01/18 15:37:02 $
 * \version $Revision: 1.3 $
 *
 * $Log: MutEditFile.h,v $
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

class MutEditFile : public wxTextCtrl
{
  public:
	MutEditFile(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const wxString& value = wxEmptyString, const wxString& name = wxTextCtrlNameStr)
	 : wxTextCtrl(parent, wxID_ANY, value, pos, size, wxTE_PROCESS_TAB | wxTE_MULTILINE | wxTE_RICH | wxTE_RICH2 | wxTE_NOHIDESEL | wxHSCROLL , wxDefaultValidator, name) {};
  protected:
//	void SetupWindow();
	void CmFileSave(wxCommandEvent& WXUNUSED(event));
	void CmCompile(wxCommandEvent& WXUNUSED(event));
	void CmCompAct(wxCommandEvent& WXUNUSED(event));
	void CmGetLine(wxCommandEvent& WXUNUSED(event));
	void CmHelpContext(wxCommandEvent& WXUNUSED(event));
	void GoErrorLine();
	DECLARE_EVENT_TABLE()
};


#endif // __MUTEDITFILE_H_INCLUDED__
