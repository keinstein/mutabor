// -*-C++ -*-
/** \file
********************************************************************
* Box shape for route window.
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
#include "src/wxGUI/Routing/BoxChannelShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/error.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/GUIBoxData-inlines.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/Routing/BoxShape.h"

//#include "wx/dc.h"
#include "wx/graphics.h"
using namespace mutabor;

MUTABOR_NAMESPACE(mutaborGUI)
BEGIN_EVENT_TABLE(MutBoxChannelShape, MutIconShape)
EVT_LEFT_DCLICK(MutBoxChannelShape::LeftDblClickEvent)
END_EVENT_TABLE()


void MutBoxChannelShape::GotFocus() {
	//		m_parent->SetFocus();// we don't need the focus, currently
#if 0
	this->MutIconShape::GotFocus();
	DEBUGLOG (other, "" );
	UpdateBorder(wxBORDER_NONE);
#endif
}



void MutBoxChannelShape::LostFocus()
{
}

MutBoxChannelShape::~MutBoxChannelShape()
{
	try {
		DetachChannel();
	} catch (const mutabor::error::unreachable_exception & e) {
		mutabor::unhandled_exception_handler();
	}
}


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

bool MutBoxChannelShape::Create (wxWindow * p,
				 wxWindowID id,
				 mutabor::Route r)
{
	mutASSERT(!route || !r);
	if (route && r) {
		UNREACHABLEC;
		return false;
	}
	bool fine = MutIconShape::Create(p,id,wxBORDER_NONE);
	if (p) {
		SetBackgroundColour(
				    p->GetBackgroundColour()
				    );
	}
#if 0
	this->SetWindowStyle(
			     (this->GetWindowStyle() & ~ wxBORDER_MASK)
			     | wxBORDER_NONE);
#endif
#if __WXGTK__
	borderOffset = wxSize(0,0);
#else
	borderOffset =
		maxBorderSize = GetWindowBorderSize();
#endif
	if (fine)
		connect(r,this);
	return fine;
}


MutIcon& MutBoxChannelShape::GetMutIcon()
{

	DEBUGLOG (other, "Checking icons" );

	mutASSERT(ActiveChannelBitmap.IsOk ()
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
	TRACEC;
	input = device;
	TRACEC;
}

void MutBoxChannelShape::Add(MutOutputDeviceShape * device)
{
	if (output) UNREACHABLEC;
	output = device;
}

void MutBoxChannelShape::Add(mutabor::Route & r)
{
	if (route) UNREACHABLEC;
	DEBUGLOG (smartptr, "Adding route %p" ,(void *)r.get());
	route = r;
	Icon = GetMutIcon();
}


/// replace an existing output device
bool MutBoxChannelShape::Replace (MutOutputDeviceShape * olddev,
				  MutOutputDeviceShape * newdev) {
	bool retval = olddev == output;
	if (!retval)
		UNREACHABLEC;
	output = newdev;
	return retval;
}

/// replace an existing input device
bool MutBoxChannelShape::Replace (MutInputDeviceShape * olddev,
				  MutInputDeviceShape * newdev) {
	TRACEC;
	bool retval = olddev == input;
	TRACEC;
	if (retval) {
		input = newdev;
		TRACEC;
	} else {
		mutASSERT(retval);
	}
	TRACEC;
	return retval;
}

/// replace an existing route
bool MutBoxChannelShape::Replace (mutabor::Route & oldroute,
				  mutabor::Route & newroute) {
	bool retval = oldroute == route;
	if (retval) {
		DEBUGLOG (smartptr, "Replacing route %p by %p" ,
			  (void *)oldroute.get(), (void *)newroute.get());

		route = newroute;
	} else {
		mutASSERT(retval);
	}
	return retval;
}

/// remove an existing output device
bool MutBoxChannelShape::Remove (MutOutputDeviceShape * out) {
	bool retval = (out == output);
	if (retval)
		output = NULL;
	else
		UNREACHABLEC;
	return retval;
}
/// remove an existing input device
bool MutBoxChannelShape::Remove (MutInputDeviceShape * in) {
	TRACEC;
	bool retval = in == input;
	TRACEC;
	if (retval) {
		input = NULL;
		TRACEC;
	} else
		UNREACHABLEC;
	TRACEC;
	return retval;
}
/// remove an attatched route
bool MutBoxChannelShape::Remove (mutabor::Route & r) {
	bool retval = route == r
		&& input == NULL && output == NULL;
	if (!retval)
		UNREACHABLEC;
	if (retval) {
		DEBUGLOG (smartptr, "removing route %p" ,(void *)r.get());
		route.reset();
	}
	return retval;
}

void MutBoxChannelShape::CreateRoutePanel(MutBoxChannelShape * channel,
					  MutRouteWnd * parentwin,
					  wxWindow * routeWindow,
					  const mutabor::Box & box) {
	wxSizer * routeSizer = routeWindow->GetSizer();
	if (!routeSizer) {
		UNREACHABLECT(MutBoxChannelShape);
		return;
	}

	InputFilterPanel * inputfilter = new InputFilterPanel(routeWindow);
	MutBoxChannelShape::InitializeInputFilter(inputfilter,
						  parentwin,
						  channel);

	RoutePanel * routePanel = new RoutePanel(routeWindow);
	MutBoxChannelShape::InitializeRoute(routePanel,
					    parentwin,
					    channel,
					    box);

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
	mutASSERT(par);
	wxChoicebook * choiceBook = panel->GetInputDeviceBook();

	TRACET(MutBoxChannelShape);
	MutInputDeviceShape * input;
	TRACET(MutBoxChannelShape);
	if (shape)
		input = shape->input;
	else
		input = NULL;
	TRACET(MutBoxChannelShape);
	Route route;
	TRACET(MutBoxChannelShape);
	if (shape) {
		TRACET(MutBoxChannelShape);
		route = shape->route;
		DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
			     ("set intermediete route %p (%d)"),
			     (void *)route.get(),
			     (int)intrusive_ptr_get_refcount(route.get()));
	} else
		route.reset();
	TRACET(MutBoxChannelShape);

	panel->AddPage(new wxPanel(choiceBook),
		       _("No input device"),
		       !input,
		       NULL);
	TRACET(MutBoxChannelShape);
	wxSizer *inputs = par->GetInputDevices();
	const wxSizerItemList &list = inputs->GetChildren();
	for (wxSizerItemList::const_iterator i = list.begin();
	     i != (list.end()); i++) {
		TRACET(MutBoxChannelShape);
		MutInputDeviceShape * device =
			dynamic_cast<MutInputDeviceShape *>
			((*i)->GetWindow());
		TRACET(MutBoxChannelShape);

		if (!device) continue;
		wxPanel * devicePanel =
			device -> GetFilterPanel(choiceBook, route);
		TRACET(MutBoxChannelShape);
		panel -> AddPage(devicePanel,
				 device->GetLabel(),
				 input == device,
				 device);
		TRACET(MutBoxChannelShape);
	}
	DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
		     ("End of function. Destruct pointer to  %p (%d)"),
		     (void*)route.get(),
		     (int)intrusive_ptr_get_refcount(route.get()));
}

void MutBoxChannelShape::InitializeRoute(RoutePanel * panel,
					 MutRouteWnd * par,
					 MutBoxChannelShape * shape,
					 mutabor::Box box)
{
	mutASSERT(par);
	mutASSERT(panel);

	if (!par || !panel) return;
	Route  route;
	if (shape) {
		DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
			     ("setting intermediete route %p"),
			     (void *)shape->route.get());
		route = shape->route;
	} else
		route.reset();

	if (route)
		panel->SetActive(route->GetActive());
	else
		panel->SetActive(true);

	//wxSizer *boxes = par->GetBoxes();


	bool found = false;


	const mutabor::BoxListType &list = mutabor::BoxClass::GetBoxList();
	for (mutabor::BoxListType::const_iterator i = list.begin();
	     i != (list.end()); i++) {
		bool select = ((*i) == box);
		found |= select;
		panel->AddBox(*i, select);
	}

	if (!found)
		panel->AddBox(NULL, true);
	DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
		     ("End of function: destruct pointer to  %p"),
		     (void *)route.get());
}

void MutBoxChannelShape::InitializeOutputFilter(OutputFilterPanel * panel,
						MutRouteWnd * par,
						MutBoxChannelShape * shape) {
	mutASSERT(par);
	mutASSERT(panel);
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
			     ("setting intermediete route %p"),
			     (void*)shape->route.get());
		route = shape->route;
	} else
		route.reset();

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
			device -> GetFilterPanel (choiceBook, route);
		panel -> AddPage (devicePanel,
				  device->GetLabel(),
				  output == device,
				  device);
	}
	DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
		     ("End of function destruct pointer to  %p"),
		     (void*)route.get());
}

void MutBoxChannelShape::ReadPanel(RoutePanel * panel)
{
	mutASSERT(panel);
	mutASSERT(route);
	if (!panel) return;
	if (!route) return;

	if (!panel->IsEnabled()) {
		//		BoxData::CloseRoute(route->GetBox());
		route->Destroy();
		/*
		  DetachChannel();
		  DeleteSelf();
		*/
		return;
	}

	DEBUGLOG (dialog, "Setting route channel: old: %d; new: %d" ,
		  route->GetActive(),
		  panel->GetActive());
	route->SetActive(panel->GetActive());

#if 0
	mutabor::Box box = panel->GetBox();
	BoxData * guibox = ToGUIBase(box);
	mutASSERT(guibox);
	if (!guibox) {
		UNREACHABLEC;
		return;
	}
	MutBoxShape * shape = guibox->GetShape(GetGrandParent());

	if (!shape) {
		shape = dynamic_cast<MutBoxShape *> (GetParent());
		if (!box) UNREACHABLEC;
	}
	// this should be done by reconnect below
	else if (shape != GetParent()) {
		MutBoxShape * oldshape =
			dynamic_cast<MutBoxShape *>(GetParent());
		mutASSERT(oldshape);
		reconnect(this,oldshape,shape);
	}
#endif

	Box oldbox = route -> GetBox();
	Box newbox = panel -> GetBox();
	if (oldbox != newbox) {
		if (newbox) {
			if (oldbox) {
				reconnect(route,oldbox,newbox);
			} else {
				connect(route,newbox);
			}
		}
		/* else we must use the newly created box which is already connected to the route */
	}

	OutputFilterPanel * outputPanel = panel->GetOutput();
	if (!outputPanel) {
		UNREACHABLEC;
	} else {
		MutOutputDeviceShape * newoutput =
			outputPanel->GetCurrentSelection();
		if (newoutput) {
			if (newoutput != output) {
				if (output)
					reconnect(this,output,newoutput);
				else {
					connect(this,newoutput);
				}
			}
			mutASSERT(output == newoutput);
			if (output) {
				output->ReadPanel(outputPanel,this);
				output->Refresh();
			}
		} else if (output) {
			disconnect(this,output);
		}
	}


	InputFilterPanel * inputPanel = panel->GetInput();
	if (!inputPanel) {
		UNREACHABLEC;
	} else {
		TRACEC;
		MutInputDeviceShape * newinput =
			inputPanel->GetCurrentSelection();
		TRACEC;
		if (newinput) {
			if (newinput != input) {
				TRACEC;
				if (input)
					reconnect(this,input,newinput);
				else {
					connect(this,newinput);
				}
			}
			mutASSERT(input == newinput);
			if (input) {
				TRACEC;
				input->ReadPanel(inputPanel,this);
				TRACEC;
				input->Refresh();
				TRACEC;
			}
		} else if (input) {
			TRACEC;
			disconnect(this,input);
			TRACEC;
		}
	}


	Icon = GetMutIcon();

	DebugCheckRoutes();
	if (input)
		input->Refresh();
	if (output)
		output->Refresh();
	Refresh();
}


void MutBoxChannelShape::DrawLines(wxGraphicsContext & gc,
				   wxWindow * paintingWindow
				   /* ,const wxPoint & origin */) const
{
	mutASSERT(paintingWindow);
	if (!paintingWindow)
		return;

	wxPoint myoffset = GetPositionInWindow(paintingWindow);
	wxSize size      = GetClientSize();
	wxPoint center(wxPoint(0,0) + size/2);

	center += myoffset;

	// without origin as this has been incorporated in the screen coordinates

	if (input) {
		wxSize inputSize = input->GetClientSize();
		wxPoint inputOffset = input->GetPositionInWindow(paintingWindow);
		wxPoint inputPosition(inputOffset+inputSize/2);

		inputPosition = inputOffset + input->GetPerimeterPoint(center-inputPosition);
		wxPoint position = myoffset + GetPerimeterPoint(inputPosition-center);

		wxGraphicsPath path = gc.CreatePath();
		path.MoveToPoint(inputPosition);
		path.AddLineToPoint(position);
		path.AddLineToPoint(center);
		gc.StrokePath(path);
		input -> Refresh();
	}

	if (output) {
		wxSize outputSize = output->GetClientSize();
		wxPoint outputOffset = output->GetPositionInWindow(paintingWindow);
		wxPoint outputPosition(outputOffset + outputSize/2);

		outputPosition = outputOffset + output->GetPerimeterPoint(center - outputPosition);
		wxPoint position = myoffset + GetPerimeterPoint(outputPosition - center);

		wxGraphicsPath path = gc.CreatePath();
		path.MoveToPoint(outputPosition);
		path.AddLineToPoint(position);
		path.AddLineToPoint(center);
		gc.StrokePath(path);
		output -> Refresh();
	}
	const_cast<MutBoxChannelShape *> (this) -> Refresh();
}

wxPoint MutBoxChannelShape::GetPerimeterPoint(const wxPoint &direction) const
{
	wxRect iconRect = this->GetIconRect();
	DEBUGLOG (routinggui, "Icon rect: x=%d, y=%d, w=%d, h=%d" ,iconRect.x,iconRect.y,iconRect.width,iconRect.height);
	wxPoint iconCenter(iconRect.x+iconRect.width/2,
			   iconRect.y+iconRect.height/2);
	DEBUGLOG (routinggui, "center = (%d,%d)" , iconCenter.x, iconCenter.y);
	wxSize bordersize = (this->GetSize()-this->GetClientSize()).Scale(0.5,0.5);

	wxPoint upperLeft = - this->GetClientAreaOrigin() - bordersize;
	wxPoint lowerRight = upperLeft + GetSize();

	wxPoint perimeterpoint(direction.x <= 0 ? upperLeft.x: lowerRight.x,
			       iconCenter.y);

	mutpointlist::iterator pos = std::find(usedperimeterpoints.begin(),
					       usedperimeterpoints.end(),
					       perimeterpoint);
	if (pos == usedperimeterpoints.end())
		usedperimeterpoints.push_back(perimeterpoint);

	DEBUGLOG(window_positions,"new point (%d,%d)",perimeterpoint.x, perimeterpoint.y);

	return perimeterpoint;
#if 0
	wxRect r = GetRect();
	mutASSERT(r.width > 0);
	mutASSERT(r.height > 0);
	DEBUGLOG (routinggui,
		  ("Rect: (%d,%d) -- (%d,%d)"),
		  r.x,r.y,r.x+r.width,r.y+r.height);
	DEBUGLOG (routinggui,
		  ("Points: i = (%d,%d), o = (%d, %d)"),i.x,i.y,o.x,o.y);
	//	wxRect ir = GetIconRect();

	wxPoint savepoint(0, r.height/2);

	r.x += parentPosition.x;
	r.y += parentPosition.y;

#ifdef DEBUG
	mutASSERT(r.Contains(i));
#endif
	wxPoint p(r.x + r.width/2, r.y + r.height/2);
	if (p.x <= o.x) {
		p.x = r.x + r.width;
		savepoint.x = r.width;
	} else if (p.x > o.x) {
		p.x = r.x;
	}

	mutpointlist::iterator pos = std::find(usedperimeterpoints.begin(),
					       usedperimeterpoints.end(),
					       savepoint);
	if (pos == usedperimeterpoints.end())
		usedperimeterpoints.push_back(savepoint);

	return p;
#endif
}

void MutBoxChannelShape::DrawPerimeterPoint(wxGraphicsContext & dc,
					    const wxPoint & center,
					    wxPoint p) const
{
	mutUnused(center); // we are providing our own centre
	DEBUGLOG(window_positions,"DrawPerimeterPoint (%d,%d)",p.x,p.y);
	wxPoint mycenter = wxPoint()+GetClientSize()/2;
	mutASSERT(mycenter.x > 0);
	mutASSERT(mycenter.y > 0);
#if __WXGTK__ && 0
	mycenter.y -= maxBorderSize.y;
	p.y -= maxBorderSize.y;
#endif
	wxGraphicsPath path = dc.CreatePath();
	path.MoveToPoint(mycenter);
	path.AddLineToPoint(p);
	dc.StrokePath(path);
#if 0
	dc.DrawLine(mycenter, p);
#endif
}



void MutBoxChannelShape::Refresh(bool eraseBackground, const wxRect* rect) {
	if (!rect) {
		SetIcon(GetMutIcon());
	}
	MutIconShape::Refresh(eraseBackground,rect);
}


void MutBoxChannelShape::DetachChannel() {
	if (route)
		disconnect(route,this);
}

void MutBoxChannelShape::DeleteRoute() {
	if (route)
		route->Destroy();
	route.reset();
}
MUTABOR_NAMESPACE_END(mutaborGUI)


/*
 * \}
 */
