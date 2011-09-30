// -*-C++ -*-
/** \file
 ********************************************************************
 * Input device shape for reading GUIDO files in the route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputGuidoFileDeviceShape.cpp,v 1.5 2011/09/30 18:07:05 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/09/30 18:07:05 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: InputGuidoFileDeviceShape.cpp,v $
 * Revision 1.5  2011/09/30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.4  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-03-30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.4  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.cpp,v
 * Revision 1.1.2.3  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "Defs.h"
#include <limits>
#include "InputGuidoFileDeviceShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"


using namespace mutabor;
namespace mutaborGUI {
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
			wxPanel * panel;
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
		DEBUGLOG (other,_T ("File %s"),  (in -> GetGUIDOFile()).c_str());
		device->SetName (in -> GetGUIDOFile());
		SetLabel (device->GetName());
		return true;
	}

	wxPanel * MutInputGuidoFileDeviceShape::GetInputFilterPanel(wxWindow * parent, 
								    Route  route) const
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
		panel->SetFromBox(route->IFrom, 0, maxint);
		panel->SetToBox(route->ITo, 0, maxint);
		panel->SetFromStaff(route->IFrom, 0, maxint);
		panel->SetToStaff(route->ITo, 0, maxint);
		panel->SetRouteType(route->GetType());
		return panel;
	}

	void MutInputGuidoFileDeviceShape::ReadInputFilterPanel(wxWindow * panel, Route  route)
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


	IMPLEMENT_DYNAMIC_CLASS(MutInputGuidoFileDeviceShape, MutInputDeviceShape)
}
/*
 * \}
 */
