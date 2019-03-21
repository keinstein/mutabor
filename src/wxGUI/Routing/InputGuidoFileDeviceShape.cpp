// -*-C++ -*-
/** \file
********************************************************************
* Input device shape for reading GUIDO files in the route window.
*
* \author Rüdiger Krauße,
* Tobias Schlemmer <keinstein@users.sourceforge.net>
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
*\addtogroup GUIroute
*\{
********************************************************************/
#include "src/kernel/Defs.h"
#include <limits>
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/InputGuidoFileDeviceShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"


using namespace mutabor;
MUTABOR_NAMESPACE(mutaborGUI)
class GisInputFilterPanel : public GisInputFilterPanelBase {
public:
	GisInputFilterPanel(wxWindow * parent):GisInputFilterPanelBase(parent) {}
	
	/**
	 * TODO: set limits according to changes: min.max = max.value and max.min = min.value
	 */
	void SetFromBox(int current, int min, int max) {
		from_box->SetRange(min,max);
		from_box->SetValue(current);
	}
	int GetFromBox() const
	{
		return from_box->GetValue();
	}
	
	void SetToBox(int current, int min, int max) {
		to_box->SetRange(min,max);
		to_box->SetValue(current);
	}
	int GetToBox() const
	{
		return to_box->GetValue();
	}
	
	void SetFromStaff(int current, int min, int max) {
		from_staff->SetRange(min,max);
		from_staff->SetValue(current);
	}
	int GetFromStaff() const
	{
		return from_staff->GetValue();
	}
	
	void SetToStaff(int current, int min, int max) {
		to_staff->SetRange(min,max);
		to_staff->SetValue(current);
	}
	int GetToStaff() const
	{
		return to_staff->GetValue();
	}
	
	void SetRouteType(RouteType routetype) {
		wxPanel * panel =  NULL;
		switch (routetype) {
		case RTall: panel = all_panel; break;
		case RTchannel: panel = box_tag_panel; break;
		case RTstaff: panel = staves_panel; break;
		case RTelse: panel = else_panel; break;
		default:
			UNREACHABLEC;
			std::cerr << "GisInputFilterPanel::SetRouteType: invaid route type " 
				  << routetype << std::endl;
			abort();
		}
		for (size_t i = 0 ; i < type->GetPageCount(); i++) {
			if (type -> GetPage(i) != panel) continue;
			type->SetSelection(i);
		}
	}
	
	RouteType GetRouteType() {
		wxWindow * window = type->GetCurrentPage();
		if (window == all_panel)
			return RTall;
		else if (window == box_tag_panel)
			return RTchannel;
		else if (window == staves_panel)
			return RTstaff;
		else if (window == else_panel)
			return RTelse;
		else {
			UNREACHABLEC;
			return RTall;
		}
	}
	
};

void MutInputGuidoFileDeviceShape::InitializeDialog(InputDevDlg * in) const
{
	mutASSERT(device);
	mutASSERT(device->GetType() == DTGis);
	mutASSERT(in);
	in -> SetType(DTGis);
	in -> SetGUIDOFile(device->GetName());
}

bool MutInputGuidoFileDeviceShape::readDialog (InputDevDlg * in)
{
	mutASSERT(device);
	mutASSERT(device->GetType() == DTGis);
	mutASSERT(in);
	mutASSERT (in -> GetType() == DTGis);
	DEBUGLOG (other, ("File %s"),  (in -> GetGUIDOFile()).c_str());
	device->SetName (std::string(in -> GetGUIDOFile().ToUTF8()));
	SetLabel (device->GetName());
	return true;
}
#ifdef max
#undef max
#endif
wxPanel * MutInputGuidoFileDeviceShape::GetFilterPanel(wxWindow * parent, 
						       Route & route) const
{
	const int maxint = std::numeric_limits<int>().max();
	GisInputFilterPanel * panel = new GisInputFilterPanel(parent);
	if (!panel) return NULL;
	if (!route) {
		panel->SetFromBox(0, 0, maxint);
		panel->SetToBox(maxint, 0, maxint);
		panel->SetFromStaff(0, 0, maxint);
		panel->SetToStaff(maxint, 0, maxint);
		panel->SetRouteType(RTall);		
		return panel;
	}
	panel->SetFromBox(route->GetInputFrom(), 0, maxint);
	panel->SetToBox(route->GetInputTo(), 0, maxint);
	panel->SetFromStaff(route->GetInputFrom(), 0, maxint);
	panel->SetToStaff(route->GetInputTo(), 0, maxint);
	panel->SetRouteType(route->GetType());
	return panel;
}

void MutInputGuidoFileDeviceShape::ReadFilterPanel(wxWindow * panel, Route & route)
{
	GisInputFilterPanel * pan = dynamic_cast<GisInputFilterPanel *> (panel);
	if (!pan) {
		UNREACHABLEC;
		return;
	}
	route->SetType(pan->GetRouteType());
	switch (route->GetType()) {
	case RTall:
	case RTelse:
		// those have no data
		break;
	case RTchannel:
		route->SetInputFrom(pan->GetFromBox());
		route->SetInputTo(pan->GetToBox());
		break;
	case RTstaff:
		route->SetInputFrom(pan->GetFromStaff());
		route->SetInputTo(pan->GetToStaff());
		break;
	default:
		UNREACHABLEC;
		break;
	}
	return;
	
}


void MutInputGuidoFileDeviceShape::DoDeviceNotification(wxCommandEvent & event)
{
	if (device && device->IsOpen() && !playbuttons) {
		createPlayButtons();
	}
	MutInputDeviceShape::DoDeviceNotification(event);
}

IMPLEMENT_DYNAMIC_CLASS(MutInputGuidoFileDeviceShape, MutInputDeviceShape)
MUTABOR_NAMESPACE_END(mutaborGUI)

/*
 * \}
 */
