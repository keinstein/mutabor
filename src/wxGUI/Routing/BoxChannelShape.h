// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/BoxChannelShape.h,v 1.13 2011/11/05 15:19:38 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
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

#if (!defined(MUWX_ROUTING_BOXCHANNELSHAPE_H) && !defined(PRECOMPILE))	\
	|| (!defined(MUWX_ROUTING_BOXCHANNELSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXCHANNELSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/IconShape.h"
//#include "Device.h"
#include "src/kernel/box.h"

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
//	class MutOutputDeviceShape;

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
		virtual ~MutBoxChannelShape();

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
			     mutabor::Route & r=NullRoute);

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
		

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
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

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

#if 0
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
				connect(route,dev);
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
				return reconnect(route,olddev,newdev);
			UNREACHABLEC;
			return false;
		}

		void Attatch(mutabor::Route & r);
		void Detatch(mutabor::Route & r);
#endif		
		
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

		GUIRoute * GetGUIRoute() const { 
			return static_cast<GUIRoute *>(route.get()); 
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
