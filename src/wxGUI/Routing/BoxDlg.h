/** \file   -*- C++ -*-
********************************************************************
* Box dialog
*
* Copyright:   (c) 2008-2012 TU Dresden
*              (c) 2012 Tobias Schlemmer        
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
* \date 2008/08/05
* $Date: 2011/11/02 14:31:59 $
* \version $Version$
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
*
* \addtogroup GUIroute
* \{
********************************************************************/


// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#if (!defined(MUWX_ROUTING_BOXDLG_H) && !defined(PRECOMPILE))	      \
	|| (!defined(MUWX_ROUTING_BOXDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXDLG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/resourceload.h"
#include "src/wxGUI/Routing/DeviceShape.h"

#ifndef MUWX_ROUTING_BOXDLG_H_PRECOMPILED
#define MUWX_ROUTING_BOXDLG_H_PRECOMPILED

// system headers which do seldom change

MUTABOR_NAMESPACE(mutaborGUI)


typedef NoBoxSettingsBase NoBoxSettings;
typedef GuidoFileBoxSettingsBase GuidoFileBoxSettings;

class MutaborBoxSettings: public MutaborBoxSettingsBase {
public:
	MutaborBoxSettings(wxWindow * parent):MutaborBoxSettingsBase(parent) {}
	virtual ~MutaborBoxSettings() {}
	void SetBoxNumber(int nr);
	int GetBoxNumber() const 
	{ 
		mutASSERT(boxNumber);
		if (!boxNumber) return -99;
		return boxNumber -> GetValue(); 
	}
};

class InputFilterPanel : public InputFilterPanelBase {
	class InputShapeData: public wxClientData {
		MutInputDeviceShape * device;
	public:
		InputShapeData(MutInputDeviceShape * b):wxClientData() { device = b; }
		MutInputDeviceShape * GetDevice() { return device; }
		virtual ~InputShapeData() {}
	};
	
public:
	InputFilterPanel(wxWindow * parent):InputFilterPanelBase(parent) {}
	wxChoicebook * GetInputDeviceBook() { return inputDevice; }
	void AddPage(wxPanel * panel, const wxString &label, bool selected, MutInputDeviceShape * shape);
	wxWindow * GetCurrentDevicePage() ;
	MutInputDeviceShape * GetCurrentSelection();
};

class OutputFilterPanel : public OutputFilterPanelBase {
	class OutputShapeData: public wxClientData {
		MutOutputDeviceShape * device;
	public:
		OutputShapeData(MutOutputDeviceShape * b):wxClientData() { device = b; }
		MutOutputDeviceShape * GetDevice() { return device; }
		virtual ~OutputShapeData() {}
	};
public:
	OutputFilterPanel(wxWindow * parent):OutputFilterPanelBase(parent) {}
	wxChoicebook * GetOutputDeviceBook() { return outputDevice; }
	void AddPage(wxPanel * panel, const wxString &label, bool selected, MutOutputDeviceShape * shape);
	wxWindow * GetCurrentDevicePage() ;
	MutOutputDeviceShape * GetCurrentSelection();
};

class MutBoxShape;
class MutBoxChannelShape;

class RoutePanel:public RoutePanelBase {
	DECLARE_DYNAMIC_CLASS( RoutePanel )
		
	public:
	RoutePanel():RoutePanelBase()
	{
		inPanel = NULL;
		outPanel = NULL;
		channel = NULL;
	}
	
	RoutePanel(wxWindow * parent):RoutePanelBase(parent) 
	{
		inPanel = NULL;
		outPanel = NULL;
		channel = NULL;
	}
	~RoutePanel() {}
	
	bool GetActive() {
		return active->GetValue();
	}
	void SetActive(bool val) {
		active->SetValue(val);
		passive->SetValue(!val);
	}
	bool GetPassive() {
		return passive->GetValue();
	}
	void SetPassive(bool val) {
		passive->SetValue(val);
		active->SetValue(!val);
	}
	
	void SetBox(MutBoxShape * box);
	mutabor::Box GetBox();
	void SetInput(InputFilterPanel * in) { inPanel = in; }
	InputFilterPanel * GetInput() const { return inPanel; }
	void SetOutput(OutputFilterPanel * out) { outPanel = out; }
	OutputFilterPanel * GetOutput() const { return outPanel; }
	void SetChannel(MutBoxChannelShape * ch) { channel = ch; }
	MutBoxChannelShape * GetChannel() const { return channel; }
	wxChoice * GetBoxChoice() { return box; }
	int AddBox(mutabor::Box box, bool selected = false);
	
	void EnableRoute(bool enable = true);
protected:
	class BoxShapeData: public wxClientData {
		mutabor::Box box;
	public:
		BoxShapeData(mutabor::Box b):wxClientData(),
					     box(b) {}
		virtual ~BoxShapeData() {}
		mutabor::Box & GetBox() { return box; }
	};
	typedef std::list<BoxShapeData *> boxdatalisttype;
	InputFilterPanel * inPanel;
	OutputFilterPanel * outPanel;
	MutBoxChannelShape * channel;
	// this is not needed. The list should be
	// cleared by wxWidgets
	// boxdatalisttype boxdatalist;
	
};

class RouteRemoveButton: public wxButton {
public:
	RouteRemoveButton():wxButton() { panel = NULL; }
	RouteRemoveButton(RoutePanel * route, wxWindow* parent, wxWindowID id = wxID_REMOVE, const wxString&  label = wxEmptyString, 
			  const wxPoint&  pos = wxDefaultPosition, const wxSize&  size = wxDefaultSize, 
			  long style = 0, const wxValidator&  validator = wxDefaultValidator, const wxString&  name = wxButtonNameStr):wxButton() {
		Create(route, parent, id, label, pos, size, style, validator, name);
	}

	bool Create(RoutePanel * route, wxWindow* parent, wxWindowID id = wxID_REMOVE, const wxString&  label = wxEmptyString, 
		    const wxPoint&  pos = wxDefaultPosition, const wxSize&  size = wxDefaultSize, 
		    long style = 0, const wxValidator&  validator = wxDefaultValidator, const wxString&  name = wxButtonNameStr);
	
	void EnableRoute(bool enable = true);
		
protected:
	RoutePanel * panel;
	void RemoveButtonPressed( wxCommandEvent& event );
	DECLARE_DYNAMIC_CLASS( RouteRemoveButton )
	DECLARE_EVENT_TABLE()
};

class BoxDlg:public BoxDlgBase {
	wxChoice * boxTypeChoice;
public:
	BoxDlg():BoxDlgBase(),
		 noBoxPanel(NULL),
		 mutaborBoxPanel(NULL),
		 guidoFileBoxPanel(NULL) {
		if (boxType)
			boxTypeChoice = boxType -> GetChoiceCtrl();
		else
			boxTypeChoice = nullptr;
	}

	BoxDlg(wxWindow * parent);

	void InitializeBoxTypes();
	
	wxWindow * GetRouteWindow() 
	{
		return routeWindow;
	}

	virtual wxSize DoGetBestSize() const;
	
	int GetBoxType() const;
	bool SetBoxType(int type);
	
	void SetBoxNumber(int nr) 
	{ 
		mutASSERT(mutaborBoxPanel);
		if (!mutaborBoxPanel) return;
		mutaborBoxPanel->SetBoxNumber(nr); 
	}

	int GetBoxNumber() const 
	{ 
		mutASSERT(mutaborBoxPanel);
		if (!mutaborBoxPanel) return -99;
		return mutaborBoxPanel->GetBoxNumber(); 
	}
	
	void DisableRemove (bool disable=true) 
	{
		if (!wxID_REMOVE) UNREACHABLEC;
		wxID_REMOVE->Show(!disable);
		wxID_REMOVE->Enable(!disable);
	}
	
	/// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
	
protected:
	NoBoxSettings * noBoxPanel;
	MutaborBoxSettings * mutaborBoxPanel;
	GuidoFileBoxSettings * guidoFileBoxPanel;

	void OnRemoveClick( wxCommandEvent& event );	
	void AddButtonPressed(wxCommandEvent &event);

	DECLARE_DYNAMIC_CLASS( BoxDlg )
	DECLARE_EVENT_TABLE()
};


MUTABOR_NAMESPACE_END(mutaborGUI)

#endif
// _BOXDLG_H_PRECOMPILED
#endif
// _BOXDLG_H_

///\}
