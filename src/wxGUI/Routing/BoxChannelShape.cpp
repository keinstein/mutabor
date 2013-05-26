// -*-C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/BoxChannelShape.cpp,v 1.13 2011/11/05 15:19:38 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/11/05 15:19:38 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "src/wxGUI/Routing/BoxChannelShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/OutputDeviceShape.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/GUIBoxData-inlines.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/Routing/BoxShape.h"

#include "wx/dc.h"
using namespace mutabor;

namespace mutaborGUI {

	BEGIN_EVENT_TABLE(MutBoxChannelShape, MutIconShape)
	EVT_LEFT_DCLICK(MutBoxChannelShape::LeftDblClickEvent)
	//	EVT_MENU(CM_LEFT_DOUBLE_CLICK,MutBoxChannelShape::CmLeftDblClick)
	END_EVENT_TABLE()
	

	void MutBoxChannelShape::GotFocus() {
//		m_parent->SetFocus();// we don't need the focus, currently
#if 0
		this->MutIconShape::GotFocus();
		DEBUGLOG (other, _T(""));
		UpdateBorder(wxBORDER_NONE);
#endif
	}



	void MutBoxChannelShape::LostFocus()
	{
	}

	MutBoxChannelShape::~MutBoxChannelShape()
	{
		if (route) {
			disconnect(route, const_cast<MutBoxChannelShape *>(this));
		}
		DetachChannel();
/*
  DEBUGLOG(routing,_T("Parent is %p"),m_parent);
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
					 mutabor::Route & r)
	{ 
		mutASSERT(!route || !r);
		if (route && r) {
			UNREACHABLEC;
			return false;
		}
		bool fine = MutIconShape::Create(p,id);
		if (p) {
			SetBackgroundColour(
				p->GetBackgroundColour()
				);
		}

		this->SetWindowStyle(
			(this->GetWindowStyle() & ~ wxBORDER_MASK)
			| wxBORDER_NONE);
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

		DEBUGLOG (other, _T("Checking icons"));

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
		DEBUGLOG(smartptr,_T("Adding route %p"),r.get());
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
		} else
			mutASSERT(retval);
		TRACEC;
		return retval;
	}

	/// replace an existing route
	bool MutBoxChannelShape::Replace (mutabor::Route & oldroute,
					  mutabor::Route & newroute) {
		bool retval = oldroute == route;
		if (retval) {
			DEBUGLOG(smartptr,_T("Replacing route %p by %p"),
				 oldroute.get(), newroute.get());

			route = newroute;
		} else
			mutASSERT(retval);
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
			DEBUGLOG(smartptr,_T("removing route %p"),r.get());
			route = NULL;
		}
		return retval;
	}

#if 0	
	void MutBoxChannelShape::Attatch(mutabor::Route & r) {
		if (route) UNREACHABLEC;
		else {
			DEBUGLOG(smartptr,_T("Atta(t)ching route %p"),r.get());
			route = r;
		}

	}

	void MutBoxChannelShape::Detatch(mutabor::Route & r) {
		mutASSERT (route == r);
		
		DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()));
		if (route) 
			disconnect(route).Detatch(this);
		DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()));
		route = NULL;
		DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()));
	}
#endif
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
				     _T("set intermediete route %p (%d)"),
				     route.get(),
				     intrusive_ptr_get_refcount(route.get()));
		} else
			route = NULL;
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
				device -> GetInputFilterPanel(choiceBook, route);
			TRACET(MutBoxChannelShape);
			panel -> AddPage(devicePanel, 
					 device->GetLabel(), 
					 input == device,
					 device);
			TRACET(MutBoxChannelShape);
		}
		DEBUGLOGTYPE(smartptr,MutBoxChannelShape,
			     _T("End of function. Destruct pointer to  %p (%d)"),
			     route.get(),
			     intrusive_ptr_get_refcount(route.get()));
	}
			
	void MutBoxChannelShape::InitializeRoute(RoutePanel * panel, 
						 MutRouteWnd * par,
						 MutBoxChannelShape * shape,
						 int selectBox)
	{
		mutASSERT(par);
		mutASSERT(panel);
	
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
			mutASSERT(oldbox);
			reconnect(route,oldbox,box);
			BoxData::CloseBox(oldbox->GetBoxId());
			
		}

		int newbox = box->GetBoxId();
		if (oldbox != newbox) {
			route -> SetBox(newbox);
		}
	
		OutputFilterPanel * outputPanel = panel->GetOutput();
		if (!outputPanel) UNREACHABLEC;
		else if (outputPanel) {
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
				output->ReadPanel(outputPanel,this);
				output->Refresh();
			} else if (output) {
				disconnect(this,output);
			}
		}

	
		InputFilterPanel * inputPanel = panel->GetInput();
		if (!inputPanel) UNREACHABLEC;
		else if (inputPanel) {
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
				TRACEC;
				input->ReadPanel(inputPanel,this);
				TRACEC;
				input->Refresh();
				TRACEC;
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

#if 0

	
					   bool changeRoute) 
	{
		DEBUGLOG(routinggui,_T("Setting output of %p to %p (change route %p = %d)"),this,device,route.get(), changeRoute);
		if (changeRoute) {
			mutASSERT(route);
			OutputDevice dev = device ? device -> GetDevice() : NULL;
			route -> Attatch(dev);
		}
#ifdef DEBUG
		if (device && route) {
			mutASSERT(device->GetDevice() == route->GetOutputDevice());
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
		mutASSERT(m_rect.width > 0);
		mutASSERT(m_rect.height > 0);
	
		wxPoint center(m_rect.x + m_rect.width/2, 
			       m_rect.y + m_rect.height/2);
		wxPoint origin (screenpos.x,screenpos.y);

		if (input) {
			wxRect rect = input->GetRect();
			mutASSERT(rect.width > 0);
			mutASSERT(rect.height > 0);
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
			DEBUGLOG (routinggui, _T("Drawing output line to device %x"),
				  output->GetDevice().get());
			mutASSERT(output->GetDevice());
			DEBUGLOG (routinggui, 
				  _T("Lines for device:\n%s"), 
				  output->GetDevice()->TowxString().c_str());
#endif
			wxRect rect = output->GetRect();
			mutASSERT (rect.width > 0);
			mutASSERT (rect.height > 0);
			DEBUGLOG (routinggui,
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
		mutASSERT(r.width > 0);
		mutASSERT(r.height > 0);
		DEBUGLOG (routinggui, 
			  _T("Rect: (%d,%d) -- (%d,%d)"),
			  r.x,r.y,r.x+r.width,r.y+r.height);
		DEBUGLOG (routinggui, 
			  _T("Points: i = (%d,%d), o = (%d, %d)"),i.x,i.y,o.x,o.y);
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
	}

void MutBoxChannelShape::DrawPerimeterPoint(wxDC & dc, 
					    const wxPoint & center, 
					    wxPoint p) const 
{
	mutUnused(center); // we are providing our own centre
	wxPoint mycenter = wxPoint()+GetSize()/2;
	mutASSERT(mycenter.x > 0);
	mutASSERT(mycenter.y > 0);
#if __WXGTK__
	mycenter.y -= maxBorderSize.y;
	p.y -= maxBorderSize.y;
#endif
	dc.DrawLine(mycenter, p);
}



void MutBoxChannelShape::Refresh(bool eraseBackground, const wxRect* rect) {
		if (!rect) {
			SetIcon(GetMutIcon());
		}
		MutIconShape::Refresh(eraseBackground,rect);
	}


	void MutBoxChannelShape::DetachChannel() {
		if (input) disconnect(this,input);
		if (output) disconnect(this,output);
	}
}

/*
 * \}
 */
