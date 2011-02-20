/** \file 
 ********************************************************************
 * Mutabor Panel. Panel based on wxControl and wxPanel
 * Most code comes from wxPanel and has been rewritten in order to 
 * be a subclass of wxControl.
 *
 * Note: License change towards (L)GPL is explicitly allowed for wxWindows license.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Panel.h,v 1.5 2011/02/20 22:35:58 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Julian Smart, Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Panel.h,v $
 * Revision 1.5  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.4  2011-01-29 20:09:31  keinstein
 * compiles on mac 
 *
 * Revision 1.3  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-02-15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 *
 ********************************************************************
 * \addtogroup muwx
 * \{
 ********************************************************************/

#ifndef _MUTABOR_PANEL_H_
#define _MUTABOR_PANEL_H_

#include "Defs.h"

// ----------------------------------------------------------------------------
// headers and forward declarations
// ----------------------------------------------------------------------------

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


///\}
