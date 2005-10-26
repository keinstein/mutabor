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
	void CmCompile(wxCommandEvent& WXUNUSED(event));
	void CmCompAct(wxCommandEvent& WXUNUSED(event));
	void CmGetLine(wxCommandEvent& WXUNUSED(event));
	void CmHelpContext(wxCommandEvent& WXUNUSED(event));
	void GoErrorLine();
	DECLARE_EVENT_TABLE()
};

