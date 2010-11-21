// -*-C++ -*-

/** \file
********************************************************************
* Box shape for route window.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxChannelShape.cpp,v 1.2 2010/11/21 13:15:48 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 2009/11/23
* $Date: 2010/11/21 13:15:48 $
* \version $Revision: 1.2 $
*
* $Log: BoxChannelShape.cpp,v $
* Revision 1.2  2010/11/21 13:15:48  keinstein
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


MutIcon& MutBoxChannelShape::GetMutIcon()
{

	DEBUGLOG (other, _T("Checking icons"));

	wxASSERT(ActiveChannelBitmap.IsOk () && PassiveChannelBitmap.IsOk ());

	if (route && (route -> GetActive())) {
		return ActiveChannelBitmap;
	} else {
		return PassiveChannelBitmap;
	}
}

void MutBoxChannelShape::SetInput(MutInputDeviceShape * device) 
{
	input = device;
}

void MutBoxChannelShape::SetOutput(MutOutputDeviceShape * device, 
				   bool changeRoute) 
{
	DEBUGLOG(routing,_T("Setting output of %p to %p (change route %p = %d)"),this,device,route, changeRoute);
	if (changeRoute) {
		wxASSERT(route);
		OutDevice * dev = device ? device -> GetDevice() : NULL;
		route -> SetOutDevice(dev);
	}
#ifdef DEBUG
	if (device && route) {
		wxASSERT(device->GetDevice() == route->GetOutDevice());
	}
#endif
	output = device;
}


void MutBoxChannelShape::AddPossibleOutput(MutOutputDeviceShape * device) {
	OutDevice * out;
	if (route) out = route->GetOutDevice(); else out = NULL;
	if (!out) return;
	if (device->GetDevice() == out) {
		SetOutput(device);
		device->AddRoute(route);
	}
}


void MutBoxChannelShape::DrawLines(wxDC & dc, const wxPoint & parentPosition) const
{
	wxRect m_rect = GetRect();
	m_rect.x += parentPosition.x;
	m_rect.y += parentPosition.y;
	
	wxPoint center(m_rect.x + m_rect.width/2, m_rect.y + m_rect.height/2);

	if (input) {
		wxRect rect = input->GetRect();
		wxPoint p2(center.x, 
			   m_rect.y + Icon.GetHeight()/2);
		wxPoint p1(input->GetPerimeterPoint(wxPoint(rect.x+rect.width/2,rect.y + rect.height/2), p2));
		p2 = GetPerimeterPoint(p2,p1,parentPosition);
		input -> LineTo(dc,p1);
		dc.DrawLine(p1,p2);
		dc.DrawLine(p2,center);
	}

	if (output) {
#ifdef DEBUG
		DEBUGLOG (other, _T("Drawing output line to device %x"),output->GetDevice());
		wxASSERT(output->GetDevice());
		DEBUGLOG (other, _T("Lines for device:\n%s"), output->GetDevice()->TowxString().c_str());
#endif
		wxRect rect = output->GetRect();
		DEBUGLOG (other, _T("Output rect: (%d,%d) -- (%d,%d)"),rect.x,rect.y,rect.x+rect.width, rect.y+rect.height);
		wxPoint p2(center.x, m_rect.y + Icon.GetHeight()/2);
		wxPoint p1(output->GetPerimeterPoint(wxPoint(rect.x+rect.width/2,rect.y + rect.height/2), p2));
		p2 = GetPerimeterPoint(p2,p1,parentPosition);
		output -> LineTo(dc,p1);
		dc.DrawLine(p1,p2);
		dc.DrawLine(p2,center);
	}
}

wxPoint MutBoxChannelShape::GetPerimeterPoint(const wxPoint &i,const wxPoint &o, const wxPoint & parentPosition) const {
	wxRect r = GetRect();
	DEBUGLOG (other, _T("Rect: (%d,%d) -- (%d,%d)"),r.x,r.y,r.x+r.width,r.y+r.height);
	DEBUGLOG (other, _T("Points: i = (%d,%d), o = (%d, %d)"),i.x,i.y,o.x,o.y);
//	wxRect ir = GetIconRect();

	r.x += parentPosition.x;
	r.y += parentPosition.y;

#ifdef DEBUG
	wxASSERT(r.Contains(i));
#endif
	wxPoint p(r.x + r.width/2, r.y + r.height/2);
		
	if (r.x + r.width < o.x) {
		p.x = r.x + r.width;
	} else if (p.x > o.x) {
		p.x = r.x;
	} else p = o;
	
	return p;
}

void MutBoxChannelShape::CreateRoutePanel(MutBoxChannelShape * channel, MutRouteWnd * parentwin, wxWindow * routeWindow, int selectBox) {
	wxSizer * routeSizer = routeWindow->GetSizer();
	if (!routeSizer) UNREACHABLECT(MutBoxChannelShape);
	
	InputFilterPanel * inputfilter = new InputFilterPanel(routeWindow);
	MutBoxChannelShape::InitializeInputFilter(inputfilter,parentwin,channel);
	
	RoutePanel * routePanel = new RoutePanel(routeWindow);
	MutBoxChannelShape::InitializeRoute(routePanel,parentwin,channel,selectBox);
	
	OutputFilterPanel * outputfilter = new OutputFilterPanel(routeWindow);
	MutBoxChannelShape::InitializeOutputFilter(outputfilter,parentwin,channel);
	
	routePanel->SetInput(inputfilter);
	routePanel->SetOutput(outputfilter);
	routePanel->SetChannel(channel);
	
	RouteRemoveButton * removeButton = new RouteRemoveButton(routePanel,routeWindow);
	
	routeSizer->Add(inputfilter,0,wxEXPAND);
	routeSizer->Add(routePanel,0,wxEXPAND);
	routeSizer->Add(outputfilter,0,wxEXPAND);
	routeSizer->Add(removeButton,0,wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL,5);
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
	Route * route;
	if (shape)
		route = shape->route;
	else
		route = NULL;
	
	panel->AddPage(new wxPanel(choiceBook),_("No input device"),!input,NULL);
	wxSizer *inputs = par->GetInputDevices();
	const wxSizerItemList &list = inputs->GetChildren();
	for (wxSizerItemList::const_iterator i = list.begin(); 
	     i != (list.end()); i++) {
		MutInputDeviceShape * device = dynamic_cast<MutInputDeviceShape *> ((*i)->GetWindow());
		
		if (!device) continue;
		wxPanel * devicePanel = device -> GetInputFilterPanel(choiceBook, route);
		panel -> AddPage(devicePanel, device->GetLabel(), input == device, device);
	}
}

void MutBoxChannelShape::InitializeRoute(RoutePanel * panel, 
					 MutRouteWnd * par,
					 MutBoxChannelShape * shape,
					 int selectBox)
{
	wxASSERT(par);
	wxASSERT(panel);
	
	if (!par || !panel) return;
	Route * route;
	if (shape)
		route = shape->route;
	else
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
		MutBoxShape * box = dynamic_cast<MutBoxShape *> ((*i)->GetWindow());
		if (box) {
			bool select = box->GetBoxId() == selectBox;
			panel->AddBox(box, select);
			found |= select;
		}
	}

	if (!found)
		panel->AddBox(NULL, true);
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
	Route * route;
	if (shape)
		route = shape->route;
	else
		route = NULL;
	
	panel -> AddPage(new wxPanel(choiceBook), _("No output device"), !output, NULL);
	
	wxSizer *outputs = par->GetOutputDevices();
	const wxSizerItemList &list = outputs->GetChildren();
	for (wxSizerItemList::const_iterator i = list.begin(); 
	     i != (list.end()); i++) {
		MutOutputDeviceShape * device = wxDynamicCast((*i)->GetWindow(),
							     MutOutputDeviceShape);
		if (!device) continue;
		wxPanel * devicePanel = device -> GetOutputFilterPanel (choiceBook, route);
		panel -> AddPage (devicePanel, device->GetLabel(), output == device, device);
	}
}

void MutBoxChannelShape::ReadPanel(RoutePanel * panel) 
{
	wxASSERT(panel);
	wxASSERT(route);
	if (!panel) return;
	if (!route) return;
	
	if (!panel->IsEnabled()) {
		DetachChannel();
		DeleteSelf();
		return;
	}

	DEBUGLOG (dialog, _T("Setting route channel: old: %d; new: %d"),route->GetActive(),panel->GetActive());
	route->SetActive(panel->GetActive());
	
	MutBoxShape * box = panel->GetBox();
	if (!box) {
		box = dynamic_cast<MutBoxShape *> (GetParent());
		if (!box) UNREACHABLEC;
	} else if (box != GetParent()) {
		/**
		 * \todo reparent box channel
		 */
		MutBoxShape * parent = dynamic_cast<MutBoxShape *> (GetParent());
		parent->Detach(this);
		box->AddChannel(this);
		
		STUBC;
		return;
	}
	
	InputFilterPanel * inputPanel = panel->GetInput();
	if (!inputPanel) UNREACHABLEC;
	else if (inputPanel && !input) {
		input = inputPanel->GetCurrentSelection();
		if (input) input -> AddRoute(route);
 	}
	wxASSERT(inputPanel);
	if (input)
		input->ReadPanel(inputPanel,this);
	
	OutputFilterPanel * outputPanel = panel->GetOutput();
	if (!outputPanel) UNREACHABLEC;
	else if (outputPanel && !output) {
		SetOutput(outputPanel->GetCurrentSelection(),true);
		if (output) output->AddRoute(this);
	}
	if (output)
		output->ReadPanel(outputPanel,this);
	/// TODO: consistency check
	Refresh();
}

void MutBoxChannelShape::Refresh(bool eraseBackground, const wxRect* rect) {
	if (!rect) {
		SetIcon(GetMutIcon());
	}
	MutIconShape::Refresh(eraseBackground,rect);
}

void MutBoxChannelShape::DetachChannel() {
	if (input) input->RemoveRoute(route);
	if (output) output->RemoveRoute(route);
	delete route;
	route = NULL;
}


#include "wx/listimpl.cpp"

WX_DEFINE_LIST (MutBoxChannelShapeList);

/*
 * \}
 */
