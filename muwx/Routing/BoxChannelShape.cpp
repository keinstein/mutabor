// -*-C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxChannelShape.cpp,v 1.6 2011/09/30 09:10:25 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/09/30 09:10:25 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: BoxChannelShape.cpp,v $
 * Revision 1.6  2011/09/30 09:10:25  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.5  2011-09-29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.4  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.13  2010-08-10 15:54:29  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.1.2.12  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.1.2.11  2010/06/22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.1.2.10  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.9  2010/06/02 11:20:09  keinstein
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
 * Revision 1.1.2.8  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.7  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.6  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.5  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.4  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.3  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
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
#include "BoxChannelShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"
#include "OutputDeviceShape.h"
#include "BoxDlg.h"
#include "muwx/Routing/RouteIcons.h"
#include "muwx/MutRouteWnd.h"
#include "GUIRoute-inlines.h"
#include "GUIBoxData-inlines.h"
#include "muwx/Routing/DebugRoute.h"

#include "wx/dc.h"
using namespace mutabor;

namespace mutaborGUI {

	BEGIN_EVENT_TABLE(MutBoxChannelShape, MutIconShape)
	EVT_LEFT_DCLICK(MutBoxChannelShape::LeftDblClickEvent)
	//	EVT_MENU(CM_LEFT_DOUBLE_CLICK,MutBoxChannelShape::CmLeftDblClick)
	END_EVENT_TABLE()
	

	bool MutBoxChannelShape::Destroy() {
/*
		if (m_parent) {
			wxSizer * sizer = GetContainingSizer();
			if (sizer) 
				sizer -> Detach (this);
			wxWindow * parent = m_parent;
			parent->RemoveChild(this);
			SetParent(NULL);
			parent->InvalidateBestSize();
			parent->SetInitialSize(wxDefaultSize);
			parent->Layout();		
		}
*/
		return MutIconShape::Destroy();
	}

	MutIcon& MutBoxChannelShape::GetMutIcon()
	{

		DEBUGLOG (other, _T("Checking icons"));

		wxASSERT(ActiveChannelBitmap.IsOk () 
			 && PassiveChannelBitmap.IsOk ());

		if (route && (route -> GetActive())) {
			return ActiveChannelBitmap;
		} else {
			return PassiveChannelBitmap;
		}
	}
	void MutBoxChannelShape::Add(MutInputDeviceShape * device) 
	{
		if (input) UNREACHABLEC;
		input = device;
	}

	void MutBoxChannelShape::Add(MutOutputDeviceShape * device)
	{
		if (output) UNREACHABLEC;
		output = device;
	}

	void MutBoxChannelShape::Add(mutabor::Route r)
	{
		if (route) UNREACHABLEC;
		DEBUGLOG(smartptr,_T("Adding route %p"),r.get());
		route = r;
	}

	      
	/// replace an existing output device
	bool MutBoxChannelShape::Replace (MutOutputDeviceShape * olddev, 
					  MutOutputDeviceShape * newdev) {
		bool retval = olddev == output;
		if (retval)
			output = newdev;
		else
			wxASSERT(retval);
		return retval;
	}
	
	/// replace an existing input device
	bool MutBoxChannelShape::Replace (MutInputDeviceShape * olddev, 
			    MutInputDeviceShape * newdev) {
		bool retval = olddev == input;
		if (retval)
			input = newdev;
		else
			wxASSERT(retval);
		return retval;
	}

	/// replace an existing route
	bool MutBoxChannelShape::Replace (mutabor::Route oldroute,
					  mutabor::Route newroute) {
		bool retval = oldroute == route;
		if (retval) {
			DEBUGLOG(smartptr,_T("Replacing route %p by %p"),
				 oldroute.get(), newroute.get());

			route = newroute;
		} else
			wxASSERT(retval);
		return retval;
	}

	/// remove an existing output device
	bool MutBoxChannelShape::Remove (MutOutputDeviceShape * out) {
		bool retval = out == output;
		if (retval)
			output = NULL;
		else 
			UNREACHABLEC;
		return retval;
	}
	/// remove an existing input device
	bool MutBoxChannelShape::Remove (MutInputDeviceShape * in) {
		bool retval = in == input;
		if (retval)
			input = NULL;
		else 
			UNREACHABLEC;
		return retval;
	}
	/// remove an attatched route
	bool MutBoxChannelShape::Remove (mutabor::Route r) {
		bool retval = route == r
			&& input == NULL && output == NULL;
		if (!retval)
			UNREACHABLEC;
		if (retval) {
			DEBUGLOG(smartptr,_T("removing route %p"),r.get());
			route = NULL;
		}
		return retval;
	}

	void MutBoxChannelShape::Attatch(mutabor::Route r) {
		if (route) UNREACHABLEC;
		else {
			DEBUGLOG(smartptr,_T("Atta(t)ching route %p"),r.get());
			route = r;
		}

	}
	void MutBoxChannelShape::Detatch(mutabor::Route r) {
		wxASSERT (route == r);
		if (route) 
			ToGUIBase(route).Detatch(this);
		DEBUGLOG(smartptr,_T("Deta(t)ching route %p"),r.get());
		route = NULL;
	}

	void MutBoxChannelShape::CreateRoutePanel(MutBoxChannelShape * channel, 
						  MutRouteWnd * parentwin, 
						  wxWindow * routeWindow, 
						  int selectBox) {
		wxSizer * routeSizer = routeWindow->GetSizer();
		if (!routeSizer) UNREACHABLECT(MutBoxChannelShape);
	
		InputFilterPanel * inputfilter = new InputFilterPanel(routeWindow);
		MutBoxChannelShape::InitializeInputFilter(inputfilter,
							  parentwin,
							  channel);
	
		RoutePanel * routePanel = new RoutePanel(routeWindow);
		MutBoxChannelShape::InitializeRoute(routePanel,
						    parentwin,
						    channel,
						    selectBox);
	
		OutputFilterPanel * outputfilter = 
			new OutputFilterPanel(routeWindow);
		MutBoxChannelShape::InitializeOutputFilter(outputfilter,
							   parentwin,
							   channel);

	
		routePanel->SetInput(inputfilter);
		routePanel->SetOutput(outputfilter);
		routePanel->SetChannel(channel);
	
		RouteRemoveButton * removeButton = 
			new RouteRemoveButton(routePanel,routeWindow);
	
		routeSizer->Add(inputfilter,0,wxEXPAND);
		routeSizer->Add(routePanel,0,wxEXPAND);
		routeSizer->Add(outputfilter,0,wxEXPAND);
		routeSizer->Add(removeButton,0,
				wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL,5);
		removeButton->EnableRoute();	
	}



	void MutBoxChannelShape::InitializeInputFilter(InputFilterPanel * panel, 
						       MutRouteWnd * par,
						       MutBoxChannelShape * shape)
	{
		wxASSERT(par);
		wxChoicebook * choiceBook = panel->GetInputDeviceBook();
	
		MutInputDeviceShape * input;
		if (shape)
			input = shape->input;
		else
			input = NULL;
		Route  route;
		if (shape) {
			DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
				     _T("setting intermediete route %p"),
				 shape->route.get());
			route = shape->route;
		} else
			route = NULL;
	
		panel->AddPage(new wxPanel(choiceBook),
			       _("No input device"),
			       !input,
			       NULL);
		wxSizer *inputs = par->GetInputDevices();
		const wxSizerItemList &list = inputs->GetChildren();
		for (wxSizerItemList::const_iterator i = list.begin(); 
		     i != (list.end()); i++) {
			MutInputDeviceShape * device = 
				dynamic_cast<MutInputDeviceShape *> 
				((*i)->GetWindow());
		
			if (!device) continue;
			wxPanel * devicePanel = 
				device -> GetInputFilterPanel(choiceBook, route);
			panel -> AddPage(devicePanel, 
					 device->GetLabel(), 
					 input == device,
					 device);
		}
		DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
				     _T("End of function destruct pointer to  %p"),
			 route.get());
	}

	void MutBoxChannelShape::InitializeRoute(RoutePanel * panel, 
						 MutRouteWnd * par,
						 MutBoxChannelShape * shape,
						 int selectBox)
	{
		wxASSERT(par);
		wxASSERT(panel);
	
		if (!par || !panel) return;
		Route  route;
		if (shape) {
			DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
				     _T("setting intermediete route %p"),
				 shape->route.get());
			route = shape->route;
		} else
			route = NULL;
	
		if (route)
			panel->SetActive(route->GetActive());
		else
			panel->SetActive(true);
	
		wxSizer *boxes = par->GetBoxes();

	
		bool found = false;
	
		const wxSizerItemList &list = boxes->GetChildren();
		for (wxSizerItemList::const_iterator i = list.begin(); 
		     i != (list.end()); i++) {
			MutBoxShape * box = 
				dynamic_cast<MutBoxShape *> ((*i)->GetWindow());
			if (box) {
				bool select = box->GetBoxId() == selectBox;
				panel->AddBox(box, select);
				found |= select;
			}
		}

		if (!found)
			panel->AddBox(NULL, true);
		DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
				     _T("End of function destruct pointer to  %p"),
			 route.get());
	}

	void MutBoxChannelShape::InitializeOutputFilter(OutputFilterPanel * panel, 
							MutRouteWnd * par,
							MutBoxChannelShape * shape) {
		wxASSERT(par);
		wxASSERT(panel);
		if (!par || !panel) return;

		// parent for child elements
		wxChoicebook * choiceBook = panel->GetOutputDeviceBook();
	
		MutOutputDeviceShape * output;
		if (shape)
			output = shape->output;
		else
			output = NULL;
		Route  route;
		if (shape) {
			DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
				     _T("setting intermediete route %p"),
				 shape->route.get());
			route = shape->route;
		} else
			route = NULL;
	
		panel -> AddPage(new wxPanel(choiceBook),
				 _("No output device"), 
				 !output, 
				 NULL);
	
		wxSizer *outputs = par->GetOutputDevices();
		const wxSizerItemList &list = outputs->GetChildren();
		for (wxSizerItemList::const_iterator i = list.begin(); 
		     i != (list.end()); i++) {
			MutOutputDeviceShape * device = 
				wxDynamicCast((*i)->GetWindow(),
					      MutOutputDeviceShape);
			if (!device) continue;
			wxPanel * devicePanel = 
				device -> GetOutputFilterPanel (choiceBook, route);
	 		panel -> AddPage (devicePanel, 
					  device->GetLabel(), 
					  output == device, 
					  device);
		}
		DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
				     _T("End of function destruct pointer to  %p"),
			 route.get());
	}

	void MutBoxChannelShape::ReadPanel(RoutePanel * panel) 
	{
		wxASSERT(panel);
		wxASSERT(route);
		if (!panel) return;
		if (!route) return;
	
		if (!panel->IsEnabled()) {
			BoxData::CloseBox(route->GetBox());
			route->Destroy();
			/*
			DetachChannel();
			DeleteSelf();
			*/
			return;
		}

		DEBUGLOG (dialog, _T("Setting route channel: old: %d; new: %d"),
			  route->GetActive(),
			  panel->GetActive());
		route->SetActive(panel->GetActive());
	
		int oldbox = route -> GetBox();
		MutBoxShape * box = panel->GetBox();
		if (!box) {
			box = dynamic_cast<MutBoxShape *> (GetParent());
			if (!box) UNREACHABLEC;
		} else if (box != GetParent()) {
			MutBoxShape * oldbox = 
				dynamic_cast<MutBoxShape *>(GetParent());
			wxASSERT(oldbox);
			ToGUIBase(route).Reconnect(oldbox,box);
			BoxData::CloseBox(oldbox->GetBoxId());
			
		}
		int newbox = box->GetBoxId();
		if (oldbox != newbox) {
			route -> SetBox(newbox);
			BoxData::OpenBox(newbox);
			BoxData::CloseBox(oldbox);
		}
	
		OutputFilterPanel * outputPanel = panel->GetOutput();
		if (!outputPanel) UNREACHABLEC;
		else if (outputPanel) {
			MutOutputDeviceShape * newoutput = 
				outputPanel->GetCurrentSelection();
			if (newoutput) {
				if (newoutput != output) {
					if (output) 
						Reconnect(output,newoutput);
					else {
						Attatch(newoutput);
					}
				}
				output->ReadPanel(outputPanel,this);
				output->Refresh();
			} else if (output) {
				Detatch(output);
			}
		}

	
		InputFilterPanel * inputPanel = panel->GetInput();
		if (!inputPanel) UNREACHABLEC;
		else if (inputPanel) {
			MutInputDeviceShape * newinput = 
				inputPanel->GetCurrentSelection();
			if (newinput) {
				if (newinput != input) {
					if (input) 
						Reconnect(input,newinput);
					else {
						Attatch(newinput);
					}
				}
				input->ReadPanel(inputPanel,this);
				input->Refresh();
			} else if (input) {
				Detatch(input);
			}
		}

	


		DebugCheckRoutes();
		if (input)
			input->Refresh();
		if (output)
			output->Refresh();
		Refresh();
	}

#if 0


					   bool changeRoute) 
	{
		DEBUGLOG(routing,_T("Setting output of %p to %p (change route %p = %d)"),this,device,route.get(), changeRoute);
		if (changeRoute) {
			wxASSERT(route);
			OutputDevice dev = device ? device -> GetDevice() : NULL;
			route -> Attatch(dev);
		}
#ifdef DEBUG
		if (device && route) {
			wxASSERT(device->GetDevice() == route->GetOutputDevice());
		}
#endif
		output = device;
	}
#endif

	void MutBoxChannelShape::DrawLines(wxDC & dc, 
					   const wxPoint & parentPosition,
					   const wxRect & screenpos) const
	{
		wxRect m_rect = GetRect();
		m_rect.x += parentPosition.x;
		m_rect.y += parentPosition.y;
	
		wxPoint center(m_rect.x + m_rect.width/2, 
			       m_rect.y + m_rect.height/2);
		wxPoint origin (screenpos.x,screenpos.y);

		if (input) {
			wxRect rect = input->GetRect();
			// we do not know the position of the perimeter
			// point exactly thus we consider the whole box
			// for visibility
			if (!( (rect.x + rect.width < 0 && 
				m_rect.x + m_rect.width < 0) ||
			       (rect.y + rect.height < 0 && 
				m_rect.y + m_rect.height < 0) ||
			       (rect.x > screenpos.width 
				&& m_rect.x > screenpos.width) ||
			       (rect.y > screenpos.height 
				&& m_rect.y > screenpos.height) ) ) {
				wxPoint p2(center.x, 
					   m_rect.y + Icon.GetHeight()/2);
				wxPoint p1(rect.x+rect.width/2,
				       rect.y + rect.height/2);
				p1 = input->GetPerimeterPoint(p1, p2);
				p2 = GetPerimeterPoint(p2,p1,parentPosition);
				input -> LineTo(dc,p1,screenpos);
				dc.DrawLine(p1+origin,p2+origin);
				dc.DrawLine(p2+origin,center+origin);
			}
		}

		if (output) {
#ifdef DEBUG
			DEBUGLOG (other, _T("Drawing output line to device %x"),
				  output->GetDevice().get());
			wxASSERT(output->GetDevice());
			DEBUGLOG (other, 
				  _T("Lines for device:\n%s"), 
				  output->GetDevice()->TowxString().c_str());
#endif
			wxRect rect = output->GetRect();
			DEBUGLOG (other,
				  _T("Output rect: (%d,%d) -- (%d,%d)"),
				  rect.x,rect.y,rect.x+rect.width, 
				  rect.y+rect.height);
			// we do not know the position of the perimeter
			// point exactly thus we consider the whole box
			// for visibility
			if (!( (rect.x + rect.width < 0 && 
				m_rect.x + m_rect.width < 0) ||
			       (rect.y + rect.height < 0 && 
				m_rect.y + m_rect.height < 0) ||
			       (rect.x > screenpos.width 
				&& m_rect.x > screenpos.width) ||
			       (rect.y > screenpos.height 
				&& m_rect.y > screenpos.height) ) ) {

				wxPoint p2(center.x, m_rect.y + Icon.GetHeight()/2);
				wxPoint p1(rect.x+rect.width/2,
				   rect.y + rect.height/2);
				p1 = output->GetPerimeterPoint(p1, p2);
				p2 = GetPerimeterPoint(p2,p1,parentPosition);
				output -> LineTo(dc,p1,screenpos);
				dc.DrawLine(p1+origin, p2+origin);
				dc.DrawLine(p2+origin, center+origin);
			}
		}
	}

	wxPoint MutBoxChannelShape::GetPerimeterPoint(const wxPoint &i,
						      const wxPoint &o, 
						      const wxPoint & parentPosition)
		const {
		wxRect r = GetRect();
		DEBUGLOG (other, 
			  _T("Rect: (%d,%d) -- (%d,%d)"),
			  r.x,r.y,r.x+r.width,r.y+r.height);
		DEBUGLOG (other, 
			  _T("Points: i = (%d,%d), o = (%d, %d)"),i.x,i.y,o.x,o.y);
//	wxRect ir = GetIconRect();

		r.x += parentPosition.x;
		r.y += parentPosition.y;

#ifdef DEBUG
		wxASSERT(r.Contains(i));
#endif
		wxPoint p(r.x + r.width/2, r.y + r.height/2);
		
		if (p.x <= o.x) {
			p.x = r.x + r.width;
		} else if (p.x > o.x) {
			p.x = r.x;
		}
	
		return p;
	}

	void MutBoxChannelShape::Refresh(bool eraseBackground, const wxRect* rect) {
		if (!rect) {
			SetIcon(GetMutIcon());
		}
		MutIconShape::Refresh(eraseBackground,rect);
	}


	void MutBoxChannelShape::DetachChannel() {
		if (input) Detatch(input);
		if (output) Detatch(output);
	}
}

/*
 * \}
 */
