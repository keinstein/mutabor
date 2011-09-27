/** \file   -*- C++ -*-
 ********************************************************************
 * Box dialog
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxDlg.h,v 1.3 2011/09/27 20:13:24 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2008/08/05
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: BoxDlg.h,v $
 * Revision 1.3  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.10  2010-06-29 08:26:26  keinstein
 * hunting for errors
 *
 * Revision 1.1.2.9  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.8  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.7  2010/04/27 09:16:33  keinstein
 * Remove old implementation
 *
 * Revision 1.1.2.6  2010/04/26 15:53:06  keinstein
 * BoxDlg reacts on “Remove Route”. Implementation of routing must be checked.;
 *
 * Revision 1.1.2.5  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/22 10:14:02  keinstein
 * transfer files to other computer
 *
 * Revision 1.1.2.2  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.1  2010/01/11 10:12:59  keinstein
 * added some .cvsignore files
 *
 * \addtogroup route
 * \{
 ********************************************************************/


// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#if (!defined(MUWX_ROUTING_BOXDLG_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_BOXDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXDLG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "resourceload.h"
#include "InputDeviceShape.h"
#include "OutputDeviceShape.h"

#ifndef MUWX_ROUTING_BOXDLG_H_PRECOMPILED
#define MUWX_ROUTING_BOXDLG_H_PRECOMPILED

// system headers which do seldom change

namespace mutaborGUI {

	typedef NoBoxSettingsBase NoBoxSettings;
	typedef GuidoFileBoxSettingsBase GuidoFileBoxSettings;

	class MutaborBoxSettings: public MutaborBoxSettingsBase {
	public:
	MutaborBoxSettings(wxWindow * parent):MutaborBoxSettingsBase(parent) {}
		virtual ~MutaborBoxSettings() {}
		void SetBoxNumber(int nr);
		int GetBoxNumber() const 
		{ 
			wxASSERT(boxNumber);
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
		
			protected:
		class BoxShapeData: public wxClientData {
			MutBoxShape * box;
		public:
		BoxShapeData(MutBoxShape * b):wxClientData() { box = b; }
			MutBoxShape * GetBox() { return box; }
		};
		InputFilterPanel * inPanel;
		OutputFilterPanel * outPanel;
		MutBoxChannelShape * channel;
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
		MutBoxShape * GetBox();
		void SetInput(InputFilterPanel * in) { inPanel = in; }
		InputFilterPanel * GetInput() const { return inPanel; }
		void SetOutput(OutputFilterPanel * out) { outPanel = out; }
		OutputFilterPanel * GetOutput() const { return outPanel; }
		void SetChannel(MutBoxChannelShape * ch) { channel = ch; }
		MutBoxChannelShape * GetChannel() const { return channel; }
		wxChoice * GetBoxChoice() { return box; }
		int AddBox(MutBoxShape * boxShape, bool selected = false);
	
		void EnableRoute(bool enable = true);
	
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
	BoxDlg():BoxDlgBase(),noBoxPanel(NULL),mutaborBoxPanel(NULL),guidoFileBoxPanel(NULL) { }
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
			wxASSERT(mutaborBoxPanel);
			if (!mutaborBoxPanel) return;
			mutaborBoxPanel->SetBoxNumber(nr); 
		}

		int GetBoxNumber() const 
		{ 
			wxASSERT(mutaborBoxPanel);
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
		void OnRemoveClick( wxCommandEvent& event );	
		void AddButtonPressed(wxCommandEvent &event);
	
		NoBoxSettings * noBoxPanel;
		MutaborBoxSettings * mutaborBoxPanel;
		GuidoFileBoxSettings * guidoFileBoxPanel;
		DECLARE_DYNAMIC_CLASS( BoxDlg )
			DECLARE_EVENT_TABLE()
			};


}
#endif
// _BOXDLG_H_PRECOMPILED
#endif
// _BOXDLG_H_

///\}
