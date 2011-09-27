/** \file 
 ********************************************************************
 * Box dialog
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxDlg.cpp,v 1.6 2011/09/27 20:13:24 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2008/08/05
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: BoxDlg.cpp,v $
 * Revision 1.6  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-01-24 08:40:54  keinstein
 * fix an issue with box dialog, preventing the scollbars to take effect in channel subwindow
 *
 * Revision 1.4  2011-01-13 21:44:47  keinstein
 * Some steps towards a fix for BoxDlg layout errors
 *
 * Revision 1.3  2011-01-13 21:13:03  keinstein
 * Fix some layout bugs.
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.11  2010-06-15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.10  2010/06/02 11:20:09  keinstein
 * Route.h:
 * 	new enum BoxType
 * 	new box type NewBox
 *
 * IconShape.cpp:
 * 	Hide shape in MutIconShape::DeleteSelf
 *
 * MutChild.h:
 * 	Changes on the increment value for Clientsize
 *
 * MutLogicWnd:
 * 	smaller whitespace fixes
 *
 * MutRouteWnd.cpp:
 * 	save sizerflags for MutBoxShape too
 *
 * BoxChannelShape.cpp:
 * 	rename CreateRouteShape to CreateRoutePanel
 * 	replace some wxDynamicCast by dynamic_cast
 * 	add Box “New Box“ if current box is not found
 * 	delete Route if route panel is disabled
 *
 * BoxChannelShape.h:
 * 	Update BoxShape layout  if necessary
 *
 * BoxDlg.cpp:
 * 	RoutePanel::AddBox: allow NULL boxShape
 * 	Fix Bug that didn't preselect GUIDO boxes and Through mode
 *
 * BoxShape.cpp:
 * 	fix color mapping for box numbers (shift right by 1 bit).
 * 	Add MutBoxShape::sizerFlags
 * 	SetBoxId: New function
 * 	Use SetBoxId for setting Box Id an Label in sync
 * 	AddChannel: call Layout()
 * 	implement replacement in DoLeftDblClick (enables New Box)
 * 	ShowBoxDialog: use dynamic_cast
 * 	ReadDialog: Add Channel only if new route is enabled (not deleted)
 * 	ReplaceSelfBy: new function (Unreachable as only needed for
 * 		class NewMutBoxShape)
 *
 * NewBoxShape.cpp/.h:
 * 	replaceSelfBy: new function
 * 	initialize Box id as NewBox
 *
 * *.po/mutabor.pot/ *.gmo
 *  	Sync with sources
 *
 * Revision 1.1.2.9  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.8  2010/04/27 09:16:32  keinstein
 * Remove old implementation
 *
 * Revision 1.1.2.7  2010/04/26 15:53:06  keinstein
 * BoxDlg reacts on “Remove Route”. Implementation of routing must be checked.;
 *
 * Revision 1.1.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.5  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.4  2010/03/30 08:38:27  keinstein
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

#include "Defs.h"
#include "BoxDlg.h"
#include "muwx/Routing/InputDeviceShape.h"
#include "muwx/Routing/OutputDeviceShape.h"
#include "muwx/Routing/BoxShape.h"
#include "muwx/Routing/GUIRoute-inlines.h"
#include "muwx/MutRouteWnd.h"
#include <wx/gdicmn.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutabor;

namespace mutaborGUI {

	void MutaborBoxSettings::SetBoxNumber (int nr) {
		wxASSERT(boxNumber);
		if (!boxNumber) return;
		int m;
		if (nr > (m = boxNumber->GetMax())) nr = m;
		if (nr < (m = boxNumber->GetMin())) nr = m;
		boxNumber -> SetValue(nr);
	}

	void InputFilterPanel::AddPage(wxPanel * panel, const wxString & label, 
				       bool selected, MutInputDeviceShape * shape)
	{
		inputDevice->InvalidateBestSize();
		int n = inputDevice->GetPageCount();
		if(inputDevice -> InsertPage(n,panel, label, selected)) {
			wxChoice * choice = inputDevice->GetChoiceCtrl();
			choice->SetClientObject(n,new InputShapeData(shape));
		} else UNREACHABLEC;
	}

	wxWindow * InputFilterPanel::GetCurrentDevicePage()
	{
		return inputDevice->GetCurrentPage();
	}

	MutInputDeviceShape * InputFilterPanel::GetCurrentSelection()
	{
		if (!inputDevice) {
			UNREACHABLEC;
			return NULL;
		}
		wxChoice * choice = inputDevice->GetChoiceCtrl();
		if (!choice) {
			UNREACHABLEC;
			return NULL;
		}
		InputShapeData * data = dynamic_cast<InputShapeData *> 
			(choice->GetClientObject(choice->GetSelection()));
		if (!data) {
			UNREACHABLEC;
			return NULL;
		}
		return data->GetDevice();
	}


	void OutputFilterPanel::AddPage(wxPanel * panel, const wxString & label, 
					bool selected, MutOutputDeviceShape * shape)
	{
		outputDevice->InvalidateBestSize();
		int n = outputDevice->GetPageCount();
		if(outputDevice -> InsertPage(n,panel, label, selected)) {
			wxChoice * choice = outputDevice->GetChoiceCtrl();
			choice->SetClientObject(n, new OutputShapeData(shape));
		} else UNREACHABLEC;
	}

	wxWindow * OutputFilterPanel::GetCurrentDevicePage()
	{
		return outputDevice->GetCurrentPage();
	}

	MutOutputDeviceShape * OutputFilterPanel::GetCurrentSelection()
	{
		if (!outputDevice) {
			UNREACHABLEC;
			return NULL;
		}
		wxChoice * choice = outputDevice->GetChoiceCtrl();
		if (!choice) {
			UNREACHABLEC;
			return NULL;
		}
		OutputShapeData * data = dynamic_cast<OutputShapeData *> 
			(choice->GetClientObject(choice->GetSelection()));
		if (!data) {
			UNREACHABLEC;
			return NULL;
		}
		return data->GetDevice();
	}

	IMPLEMENT_DYNAMIC_CLASS( RoutePanel, RoutePanelBase )

	/*!
	 * BoxDlg event table definition
	 */

	void RoutePanel::SetBox(MutBoxShape * shape) {
		if (!box) {
			UNREACHABLEC;
		}
		BoxShapeData  * data = new BoxShapeData(shape);
		if (!data) {
			UNREACHABLEC;
		}
		STUBC;
//		box->SetClientObject(data);
	}


	MutBoxShape * RoutePanel::GetBox() { 
		if (!box) {
			UNREACHABLEC;
			return NULL;
		}
		BoxShapeData * data = dynamic_cast<BoxShapeData *> 
			(box->GetClientObject(box->GetSelection()));
		if (!data) {
			UNREACHABLEC;
			return NULL;
		}
		return data->GetBox();
	}


	int RoutePanel::AddBox(MutBoxShape * boxShape, bool selected) {
		int number;
		if (boxShape)
			number = box->Append(boxShape->GetLabel(), 
					     new BoxShapeData(boxShape));
		else number = box->Append(_T("New Box"), 
					  new BoxShapeData(NULL));

#ifdef DEBUG
		if (boxShape) {
			DEBUGLOG(dialog,_T("Entry box Id %d at Entry No. %d"),
				 boxShape->GetBoxId(),number);
		} else {
			DEBUGLOG(dialog,_T("Entry 'new box' at Entry No. %d"),
				 number);
		}
#endif
		if (selected) box->SetSelection(number);
		return number;
	}

	void RoutePanel::EnableRoute(bool enable)
	{
	
		Enable(enable);
		if (inPanel)  inPanel  -> Enable(enable);
		if (outPanel) outPanel -> Enable(enable);
		Show(enable);
		if (inPanel) inPanel -> Show(enable);
		if (outPanel) outPanel -> Show(enable);
//	Layout();
//	GetSizer()->SetSizeHints(this);
//	Fit();
//	GetParent()->GetSizer()->SetSizeHints(GetParent());
//	GetParent()->FitInside();
	}

	BEGIN_EVENT_TABLE( RouteRemoveButton, wxButton )
	EVT_BUTTON(wxID_REMOVE, RouteRemoveButton::RemoveButtonPressed)
	END_EVENT_TABLE()
	IMPLEMENT_DYNAMIC_CLASS( RouteRemoveButton, wxButton )


	bool RouteRemoveButton::Create(RoutePanel * route, wxWindow* parent, wxWindowID id, const wxString&  label, 
				       const wxPoint&  pos, const wxSize&  size, 
				       long style, const wxValidator&  validator, const wxString&  name) {
		bool created = wxButton::Create(parent, id, label, pos, size, style, validator, name);
		panel = route;
		if (created) {
			// Avoid flipping of size.
			EnableRoute(false);
			wxSize disabledSize = DoGetBestSize();
			DEBUGLOG(dialog,_T("disabledSize = (%d,%d)"),disabledSize.x,disabledSize.y);
			EnableRoute(true);
			wxSize enabledSize = DoGetBestSize();
			DEBUGLOG(dialog,_T("enabledSize = (%d,%d)"),enabledSize.x,enabledSize.y);
			SetInitialSize(wxSize(std::max(disabledSize.x,enabledSize.x),std::max(disabledSize.y,enabledSize.y)));
		}
		return created;
	}

	void RouteRemoveButton::EnableRoute(bool enable)
	{
		SetLabel(enable?_("Remove Route"):_("Undelete Route"));
		if (panel) 
			panel->EnableRoute(enable);
	}

	void RouteRemoveButton::RemoveButtonPressed( wxCommandEvent& event )
	{
		if (panel) 
			EnableRoute(!panel->IsEnabled());
	}

	BEGIN_EVENT_TABLE( BoxDlg, BoxDlgBase)
	EVT_BUTTON(::wxID_ADD, BoxDlg::AddButtonPressed)
	EVT_BUTTON( ::wxID_REMOVE, BoxDlg::OnRemoveClick )
	END_EVENT_TABLE()
	IMPLEMENT_DYNAMIC_CLASS( BoxDlg, BoxDlgBase )


	BoxDlg::BoxDlg(wxWindow * parent):BoxDlgBase(parent) {
		if (boxType)
			boxTypeChoice = boxType -> GetChoiceCtrl();
		else
			boxTypeChoice = NULL;
		InitializeBoxTypes();
	}

	void BoxDlg::InitializeBoxTypes() {
//	int i = 0;
		wxASSERT(boxType);
		if (!boxType) {
			noBoxPanel = NULL;
			mutaborBoxPanel = NULL;
			guidoFileBoxPanel = NULL;
			return;
		}
		noBoxPanel = new NoBoxSettings(this);
		boxType -> AddPage(noBoxPanel,_("No box / thru mode"));
//	boxTypeChoice->SetClientObject(i++, new ClientData (NoBox));
	
		mutaborBoxPanel = new MutaborBoxSettings(this);
		boxType -> AddPage(mutaborBoxPanel,_("Mutabor box"));
//	boxTypeChoice->SetClientObject(i++, new ClientData (Box0));
	
		guidoFileBoxPanel = new GuidoFileBoxSettings(this);
		boxType -> AddPage(guidoFileBoxPanel,_("GUIDO file box"));
//	boxTypeChoice->SetClientObject(i++, new ClientData (GmnBox));
	}

	wxSize BoxDlg::DoGetBestSize() const 
	{
		wxRect screen = wxGetClientDisplayRect();
		wxSize size(0,0);
		wxSize routesSize = routeWindow->ClientToWindowSize(routeWindow->GetBestVirtualSize());
		wxSize enhancedRoutesSize = ClientToWindowSize(routesSize);
		size = BoxDlgBase::DoGetBestSize();
		size.y += routesSize.y;
		size.x = std::min(std::max(enhancedRoutesSize.x,size.x),screen.width);
		size.y = std::min(size.y, screen.height);
		return size;
	}


	int BoxDlg::GetBoxType() const {
		wxWindow * current = boxType->GetCurrentPage();
		if (current == noBoxPanel) return NoBox;
		else if (current == mutaborBoxPanel) return Box0;
		else if (current == guidoFileBoxPanel) return GmnBox;
		else {
			UNREACHABLEC;
			return -99;
		}
	}

	bool BoxDlg::SetBoxType(int type) {
		wxASSERT(boxType && boxTypeChoice);
		if (!boxType || !boxTypeChoice) return false;
		DEBUGLOG(dialog,_T("Setting box type number %d"), type);
		if (0<= type && type < MAX_BOX) type = Box0;
		wxWindow * page;
		switch (type) {
		case NewBox:
		case NoBox:
			page = noBoxPanel;
			break;
		case Box0:
			page = mutaborBoxPanel;
			break;
		case GmnBox:
			page = guidoFileBoxPanel;
			break;
		default:
			return false;
			break;
		}
		// This is ineffective, but the GUI does not need so much CPU.
		for (size_t i = 0; 
		     i < boxTypeChoice -> GetCount() && 
			     boxType->GetCurrentPage() != page; i++)
			boxType->SetSelection(i);
	
		return (boxType->GetCurrentPage() == page);
	}

	void BoxDlg::AddButtonPressed( wxCommandEvent& event )
	{
		MutRouteWnd * parentwin = dynamic_cast<MutRouteWnd *> (m_parent);
		if (!parentwin || !routeWindow) UNREACHABLEC;
		MutBoxChannelShape::CreateRoutePanel(NULL, 
						     parentwin, 
						     routeWindow, 
						     GetBoxType()==Box0?GetBoxNumber():GetBoxType());
		routeWindow->Layout();
		routeWindow->InvalidateBestSize();
		Layout();
		InvalidateBestSize();
		GetSizer()->SetSizeHints(this);
		Fit();
	}

	void BoxDlg::OnRemoveClick( wxCommandEvent& event )
	{
		EndModal(::wxID_REMOVE);
	}
}
/// \}
