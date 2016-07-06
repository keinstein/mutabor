/** \file 
 ********************************************************************
 * Mutabor Panel. Panel based on wxControl and wxPanel
 * Most code comes from wxPanel and has been rewritten in order to 
 * be a subclass of wxControl.
 *
 * Note: License change towards (L)GPL is explicitly allowed for wxWindows license.
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author Julian Smart,  Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/

#if (!defined(MUWX_PANEL_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_PANEL_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_PANEL_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MUWX_PANEL_H_PRECOMPILED
#define MUWX_PANEL_H_PRECOMPILED

// system headers which do seldom change

#include "wx/panel.h"
#include "wx/control.h"
#include "wx/containr.h"

extern const wxChar MutPanelNameStr[];

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

	virtual bool Destroy();
	
	// implementation from now on
	// --------------------------
	
        // calls layout for layout constraints and sizers
	void OnSize(wxSizeEvent& event);
	
	virtual void InitDialog();
	
#ifdef __WXUNIVERSAL__
	virtual bool IsCanvasWindow() const { return true; }
#endif
	
	
//	WX_DECLARE_CONTROL_CONTAINER();
public: 
	void OnNavigationKey(wxNavigationKeyEvent& event); 
	void OnFocus(wxFocusEvent& event); 
	virtual void OnChildFocus(wxChildFocusEvent& event); 
	virtual void SetFocus(); 
	virtual void SetFocusIgnoringChildren(); 
	virtual void RemoveChild(wxWindowBase *child); 
	virtual bool AcceptsFocus() const; 
protected: 
	wxControlContainer m_container;

	
protected:
	// common part of all ctors
	void Init();
	
private:
	DECLARE_DYNAMIC_CLASS_NO_COPY(MutPanel)
	DECLARE_EVENT_TABLE()
};

#endif
// _MUTABOR_PANEL_H_PRECOMPILED
#endif
// _MUTABOR_PANEL_H_


///\}
