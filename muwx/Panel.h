/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/panelg.h
// Purpose:     wxPanel: a container for child controls based on wxControl
// Author:      Julian Smart, Tobias Schlemmer
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id: Panel.h,v 1.3 2010/12/13 00:27:53 keinstein Exp $
// Copyright:   (c) Julian Smart, Tobias sclhemmer
// Licence:     wxWindows licence
// $Log: Panel.h,v $
// Revision 1.3  2010/12/13 00:27:53  keinstein
// compiles in linux as well as in mingw
//
// Revision 1.2  2010-11-21 13:15:47  keinstein
// merged experimental_tobias
//
// Revision 1.1.2.1  2010-02-15 12:08:21  keinstein
// intermediate update for backup progress
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MUTABOR_PANEL_H_
#define _MUTABOR_PANEL_H_

#include "Defs.h"

// ----------------------------------------------------------------------------
// headers and forward declarations
// ----------------------------------------------------------------------------

#include "wx/panel.h"
#include "wx/control.h"
#include "wx/containr.h"

class WXDLLIMPEXP_FWD_CORE wxControlContainer;

extern WXDLLEXPORT_DATA(const wxChar) MutPanelNameStr[];

// ----------------------------------------------------------------------------
// wxPanel contains other controls and implements TAB traversal between them
// ----------------------------------------------------------------------------

class MutPanel : public wxControl
{
public:
	MutPanel() { Init(); }
	
	// Old-style constructor (no default values for coordinates to avoid
	// ambiguity with the new one)
	MutPanel (wxWindow *parent,
		  int x, int y, int width, int height,
		  long style = 0 /* wxTAB_TRAVERSAL | wxNO_BORDER */,
		  const wxValidator& validator = wxDefaultValidator,
		  const wxString& name = wxPanelNameStr)
	{
		Init();		
		Create(parent, wxID_ANY, wxPoint(x, y), wxSize(width, height), style, validator, name);
	}
	
	// Constructor
	MutPanel(wxWindow *parent,
		 wxWindowID winid = wxID_ANY,
		 const wxPoint& pos = wxDefaultPosition,
		 const wxSize& size = wxDefaultSize,
		 long style = 0 /* wxTAB_TRAVERSAL | wxNO_BORDER */,
		 const wxValidator& validator = wxDefaultValidator,
		 const wxString& name = wxPanelNameStr)
	{
		Init();		
		Create(parent, winid, pos, size, style, validator, name);
	}
	
	// Pseudo ctor
	bool Create(wxWindow *parent,
		    wxWindowID winid = wxID_ANY,
		    const wxPoint& pos = wxDefaultPosition,
		    const wxSize& size = wxDefaultSize,
		    long style = 0 /* wxTAB_TRAVERSAL | wxNO_BORDER */,
		    const wxValidator& validator = wxDefaultValidator,
		    const wxString& name = wxPanelNameStr);
	
	virtual ~MutPanel();
	
	// implementation from now on
	// --------------------------
	
        // calls layout for layout constraints and sizers
	void OnSize(wxSizeEvent& event);
	
	virtual void InitDialog();
	
#ifdef __WXUNIVERSAL__
	virtual bool IsCanvasWindow() const { return true; }
#endif
	
	
	WX_DECLARE_CONTROL_CONTAINER();
	
protected:
	// common part of all ctors
	void Init();
	
private:
	DECLARE_DYNAMIC_CLASS_NO_COPY(MutPanel)
	DECLARE_EVENT_TABLE()
};

#endif
// _MUTABOR_PANEL_H_
