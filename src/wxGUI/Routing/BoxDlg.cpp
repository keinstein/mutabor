/** \file 
 ********************************************************************
 * Box dialog
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/MutRouteWnd.h"
#include <wx/gdicmn.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutabor;

namespace mutaborGUI {

	void MutaborBoxSettings::SetBoxNumber (int nr) {
		mutASSERT(boxNumber);
		if (!boxNumber) return;
		int m;
		if (nr > (m = boxNumber->GetMax())) nr = m;
		if (nr < (m = boxNumber->GetMin())) nr = m;
		boxNumber -> SetValue(nr);
	}

	void InputFilterPanel::AddPage(wxPanel * panel, const wxString & label, 
				       bool selected, MutInputDeviceShape * shape)
	{
		TRACEC;
		inputDevice->InvalidateBestSize();
		TRACEC;
		int n = inputDevice->GetPageCount();
		TRACEC;
		if(inputDevice -> InsertPage(n,panel, label, selected)) {
			TRACEC;
			wxChoice * choice = inputDevice->GetChoiceCtrl();
			TRACEC;
			choice->SetClientObject(n,new InputShapeData(shape));
		} else UNREACHABLEC;
		TRACEC;
	}

	wxWindow * InputFilterPanel::GetCurrentDevicePage()
	{
		return inputDevice->GetCurrentPage();
	}

	MutInputDeviceShape * InputFilterPanel::GetCurrentSelection()
	{
		TRACEC;
		if (!inputDevice) {
			UNREACHABLEC;
			return NULL;
		}
		TRACEC;
		wxChoice * choice = inputDevice->GetChoiceCtrl();
		if (!choice) {
			UNREACHABLEC;
			return NULL;
		}
		TRACEC;
		InputShapeData * data = dynamic_cast<InputShapeData *> 
			(choice->GetClientObject(choice->GetSelection()));
		TRACEC;
		if (!data) {
			UNREACHABLEC;
			return NULL;
		}
		TRACEC;
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


# if 0
	// according to the documentation this should be done by wxWidgets
	RoutePanel::~RoutePanel() {
		for (boxdatalisttype::iterator i = boxdatalist.begin();
		     i != boxdatalist.end();
		     i = boxdatalist.begin()) {
			BoxShapeData * data = *i;
			delete data;
			boxdatalist.erase(i);
		}
	}
#endif

#if 0
	void RoutePanel::SetBox(mutabor Box & b) {
		
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
#endif

	mutabor::Box RoutePanel::GetBox() { 
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


	int RoutePanel::AddBox(mutabor::Box b, bool selected) {
		int number;
		BoxShapeData * shape = new BoxShapeData(b);
		// shall be deleted by wxWidgets
		// boxdatalist.push_back(shape);
		if (selected) {
			number = box->Append(_("this box"), 
					     shape);
			box->SetSelection(number);
		} else 	if (b) {
			number = box->Append(b->GetLabel(), 
					     shape);
		} else number = box->Append(_("new box"), 
					    shape);

#ifdef DEBUG
		if (b) {
			DEBUGLOG (dialog, "Entry box %p at Entry No. %d" ,
				 b.get(),number);
		} else {
			DEBUGLOG (dialog, "Entry 'new box' at Entry No. %d" ,
				 number);
		}
#endif
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
			DEBUGLOG (dialog, "disabledSize = (%d,%d)" ,disabledSize.x,disabledSize.y);
			EnableRoute(true);
			wxSize enabledSize = DoGetBestSize();
			DEBUGLOG (dialog, "enabledSize = (%d,%d)" ,enabledSize.x,enabledSize.y);
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
		mutUnused(event);
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
		mutASSERT(boxType);
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
		mutASSERT(boxType && boxTypeChoice);
		if (!boxType || !boxTypeChoice) return false;
		DEBUGLOG (dialog, "Setting box type number %d" , type);
		if (0<= type) type = Box0;
		wxWindow * page;
		switch (type) {
		case NoBox:
			page = noBoxPanel;
			break;
		case NewBox:
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
		mutUnused(event);
		MutRouteWnd * parentwin = dynamic_cast<MutRouteWnd *> (m_parent);
		if (!parentwin || !routeWindow) UNREACHABLEC;
		mutabor::Box box = mutabor::BoxClass::GetBox(GetBoxType()==Box0?GetBoxNumber():GetBoxType(),
							     mutabor::BoxClass::IDTypeFile);
		MutBoxChannelShape::CreateRoutePanel(NULL, 
						     parentwin, 
						     routeWindow, 
						     box);
		routeWindow->InvalidateBestSize();
		routeWindow->Fit();
		Fit();
	}

	void BoxDlg::OnRemoveClick( wxCommandEvent& event )
	{
		mutUnused(event);
		EndModal(::wxID_REMOVE);
	}
}
/// \}
