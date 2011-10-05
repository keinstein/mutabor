// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxChannelShape.h,v 1.11 2011/10/05 16:28:39 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/10/05 16:28:39 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 * $Log: BoxChannelShape.h,v $
 * Revision 1.11  2011/10/05 16:28:39  keinstein
 * correct layout on mac
 *
 * Revision 1.10  2011-10-04 20:09:16  keinstein
 * Clean up focus handling a little bit.
 * Change perimeter point handling a little bit. Need at least one night to
 * get overthought.
 *
 * Revision 1.9  2011-10-04 05:38:44  keinstein
 * some configuration fixes
 *
 * Revision 1.8  2011-10-03 15:50:21  keinstein
 * Fix focus issues in the route window. This includes:
 *  * Using templates to describe the base class of MutIconShape.
 *  * Rename MutIconShape->MutIconShapeClass.
 *  * typedef MutIconShapeClass<wxControl> MutIconShape
 *  * Expand the control container macros in MutPanel.
 *  * Disable most of the control container behaviour as we don't need it, currently
 *  * Focus NewInputDevice on window creation.
 *  * MutBoxChannelShape focuses its parent on focus (which can be done only by mouse so far).
 *  * Display focused Window with sunken border
 *
 * Revision 1.7  2011-10-02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.6  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.5  2011-09-30 09:10:25  keinstein
 * Further improvements in the routing system.
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
 * Revision 1.1.2.8  2010-06-15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.7  2010/06/02 11:20:09  keinstein
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
 * Revision 1.1.2.6  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.5  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v
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

#if (!defined(MUWX_ROUTING_BOXCHANNELSHAPE_H) && !defined(PRECOMPILE))	\
	|| (!defined(MUWX_ROUTING_BOXCHANNELSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXCHANNELSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "GUIRoute.h"
#include "IconShape.h"
//#include "Device.h"
#include "box.h"

#ifndef MUWX_ROUTING_BOXCHANNELSHAPE_H_PRECOMPILED
#define MUWX_ROUTING_BOXCHANNELSHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"
#include "wx/sizer.h"


namespace mutaborGUI {
	using mutabor::NullRoute;
	class MutRouteWnd;
	class InputFilterPanel;
	class RoutePanel;
	class OutputFilterPanel;
	class MutOutputDeviceShape;

	class MutBoxChannelShape:public MutIconShape
	{
		friend class GUIRouteFactory;
		mutabor::Route route;
		MutInputDeviceShape * input;
		MutOutputDeviceShape * output;
		virtual MutIcon & GetMutIcon ();

	protected:

		/// Constructor
		/** Constructor for MutBoxChannelShape. This function 
		    constructs a window via Create(), which calles the 
		    corresponding attatch function.
		*/
		MutBoxChannelShape (wxWindow * p = NULL, wxWindowID id = wxID_ANY, 
				    mutabor::Route & r=NullRoute):MutIconShape(),
							   route(NULL), 
							   input(NULL),
							   output(NULL)
			{
				// to satisfy attatch route mus be NULL for now
				Create (p, id, r);
//				borderOffset = maxBorderSize;
			}

	public:
		virtual ~MutBoxChannelShape()
			{
				if (route) {
					ToGUIBase(route).Detatch (this);
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

		// can this window have focus?
		virtual bool AcceptsFocus() const { 
			//return false;
			return IsShown() && IsEnabled();
		}
		

		virtual bool Destroy();

		/// Create the window
		/** This function does the work of window creation and 
		    connects to the underlying route if necessary. It will 
		    complain if a route is already attached to the channel shape.
		    \param wxWindow * p parent window
		    \param wxWindowId id id of the shape
		    \param Route r Route of the undelying Mutabor engine.
		    \retval true if everything is ok
		    \retval false if an error has occured
		*/
		bool Create (wxWindow * p = NULL, wxWindowID id = wxID_ANY, 
			     mutabor::Route & r=NullRoute)
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
				borderOffset = 
					maxBorderSize = GetWindowBorderSize();
				if (fine)
					ToGUIBase(r).Attatch(this);
				return fine;
			}

		/*****************************************/
		// Event handlers
		/*****************************************/

		virtual void GotFocus() ;
		virtual void LostFocus() ;
		

		void LeftDblClickEvent (wxMouseEvent & event) { 
			GetParent()->GetEventHandler()->ProcessEvent(event);
		}

#if 0 // for own event handling
		/// Get a double click and prepare for execution of the command
		/** Since programs might produce segmentation faults
		    when the object is deleted during processing of mouse
		    events, we send us a new event using the event queue.
		*/
		void LeftDblClickEvent (wxMouseEvent & event) { 
			wxCommandEvent command(wxEVT_COMMAND_MENU_SELECTED,
					       CM_LEFT_DOUBLE_CLICK); 
			wxPostEvent(this,command); 
		}
		/// Process a double click
		/** Since programs might produce segmentation faults
		    when the object is deleted during processing of mouse
		    events, we send us a new event using the event queue.
		*/
		void CmLeftDblClick (wxCommandEvent& event) {
			DoLeftDblClick(); 
		}
#endif
		

		/*****************************************/
		// Connection management
		/*****************************************/
	
		/// add a new output device
		virtual void Add (MutOutputDeviceShape * out);
		/// add a new input device
		virtual void Add (MutInputDeviceShape * in);
		/// add a new route 
		virtual void Add (mutabor::Route & r);
		/// add a new box shape
		virtual void Add (MutBoxShape * box) { /* handled by box */ }
	      
		/// replace an existing output device
		virtual bool Replace (MutOutputDeviceShape * olddev, 
				      MutOutputDeviceShape * newdev);
		/// replace an existing input device
		virtual bool Replace (MutInputDeviceShape * olddev, 
				      MutInputDeviceShape * newdev);
		/// replace an existing route 
		virtual bool Replace (mutabor::Route & oldroute,
				      mutabor::Route & newroute);
		/// replace a box shape 
		virtual bool Replace (MutBoxShape * oldbox,
				      MutBoxShape * newbox) {
			/* handled by box */
			return true;
		}

		/// replace an existing output device
		virtual bool Remove (MutOutputDeviceShape * out);
		/// replace an existing input device
		virtual bool Remove (MutInputDeviceShape * in);
		/// remove a Route
		virtual bool Remove (mutabor::Route & r);
		/// remove a box from the route shape
		virtual bool Remove (MutBoxShape * box) {
			/* handled by box */
			return true;
		}

		
		// fortunately we can distinguish devices 
		// and shapes by their pointer types

		/// add a new device shape
		template <class deviceshape>
		void Attatch (deviceshape * dev) {
			if (dev) 
				Attatch(dev->GetDevice());
			else 
				UNREACHABLEC;
		}

		/// Attatch a new input or output device
		template <class device>
		void Attatch (boost::intrusive_ptr<device> dev) {
			if (route)
				route->Attatch(dev);
			else 
				UNREACHABLEC;
		}

		/// replace an existing device shape
		template <class deviceshape>
		bool Reconnect (deviceshape * olddev, 
				deviceshape * newdev) {
			if (olddev && newdev) 
				return Reconnect(olddev->GetDevice(),
						 newdev->GetDevice());
			else {
				UNREACHABLEC;
				return false;
			}
		}
		/// Replace current input or output device with a new one
		template <class device>
		bool Reconnect(boost::intrusive_ptr<device> & olddev, 
			       boost::intrusive_ptr<device> & newdev) {
			if (route) 
				return route->Reconnect(olddev,newdev);
			else {
				UNREACHABLEC;
				return false;
			}
			return false;
		}

		/// Detatch current device shape
		template <class deviceshape>
		bool Detatch (deviceshape * dev) {
			if (dev) {
				typename deviceshape::devicetype d(dev->GetDevice());
				return Detatch(d);
			}else {
				UNREACHABLEC;
				return false;
			}
			return false;
		}
		/// Detatch current device
		template <class device>
		bool Detatch(boost::intrusive_ptr<device> & dev) {
			if (route)
				return route->Detatch(dev);
			else {
				UNREACHABLEC;
				return false;
			}
		}
		void Attatch(mutabor::Route & r);
		void Detatch(mutabor::Route & r);
		
		
		mutabor::Route & GetRoute() const { 
			return const_cast<mutabor::Route &>(route); 
		}
		const MutInputDeviceShape * GetInput() const { 
			return input; 
		}
		MutInputDeviceShape * GetInput() { 
			return input; 
		}
		const MutOutputDeviceShape * GetOutput() const { 
			return output; 
		}
		MutOutputDeviceShape * GetOutput() { 
			return output; 
		}

		GUIfiedRoute * GetGUIfiedRoute() const { 
			return static_cast<GUIfiedRoute *>(route.get()); 
		}

		static void CreateRoutePanel(MutBoxChannelShape * channel, 
					     MutRouteWnd * parentwin, 
					     wxWindow * routeWindow, 
					     int selectBox);
		static void InitializeInputFilter(InputFilterPanel * panel, 
						  MutRouteWnd * par,
						  MutBoxChannelShape * shape = NULL);
		static void InitializeRoute(RoutePanel * panel, 
					    MutRouteWnd * par,
					    MutBoxChannelShape * shape = NULL,
					    int selectBox = NoBox);
		
		static void InitializeOutputFilter(OutputFilterPanel * panel, 
						   MutRouteWnd * par,
						   MutBoxChannelShape * shape = NULL);
		virtual void ReadPanel(RoutePanel * panel);

		virtual void DrawLines(wxDC & dc, 
				       const wxPoint & parentPosition,
				       const wxRect & screenpos) const;
		virtual wxPoint GetPerimeterPoint(const wxPoint &i,
						  const wxPoint &o,
						  const wxPoint & parentPosition) const;
		virtual void DrawPerimeterPoint(wxDC & dc, 
						const wxPoint & center, 
						wxPoint p) const;
		virtual void Refresh(bool eraseBackground = true, const wxRect* rect = NULL);
		/// Detaches the channel from a box shape.
		/**
		 * This function detaches a channel from its containing Box. The shape is not deteted.
		 */
		void DetachChannel();
	private:
		DECLARE_EVENT_TABLE()
	};
}

#endif				/* BOXCHANNELSHAPE_H_PRECOMPILED */
#endif				/* BOXCHANNELSHAPE_H */
/*
 * \}
 */
