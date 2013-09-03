// -*- C++ -*-
/** \file
 ********************************************************************
 * Device shape base class for route window.
 *
 * Copyright:   (c) 2005,2006,2007-2011 TU Dresden
 * Changes: (c) 2012-2013 Tobias Schlemmer
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
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
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#if (!defined(MUWX_ROUTING_DEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_DEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_DEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/IconShape.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Device.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/RouteLists.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_DEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_DEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

#include <map>
#include "wx/sizer.h"
//#include "wx/defs.h"
//#include "wx/ogl/ogl.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"


namespace mutaborGUI {

	class InputDevDlg;
	class GUIInputDeviceBase;
	class InputFilterPanel;

	struct inputdevicetypes {
		typedef mutabor::InputDevice Device;
		typedef mutabor::InputDeviceClass DeviceClass;
		typedef GUIInputDeviceBase GUIDeviceBase;
		typedef InputDevDlg DeviceDialog;
		typedef InputFilterPanel FilterPanel;
#if 0
		MutIcon & GetMutIcon ()
		{
			return MidiInputDevBitmap;
		}
#endif

	};

	class OutputDevDlg;
	class GUIOutputDeviceBase;
	class OutputFilterPanel;

	struct outputdevicetypes {
		typedef mutabor::OutputDevice Device;
		typedef mutabor::OutputDeviceClass DeviceClass;
		typedef GUIOutputDeviceBase GUIDeviceBase;
		typedef OutputDevDlg DeviceDialog;
		typedef OutputFilterPanel FilterPanel;
#if 0
		MutIcon & GetMutIcon ()
		{
			return MidiOutputDevBitmap;
		}
#endif

	};

	template<class T>
	class MutDeviceShape:public MutIconShape
	{
	public:
		typedef typename T::Device devicetype;
		typedef typename T::DeviceClass DeviceClass;
		typedef typename T::GUIDeviceBase GUIDeviceBase;
		typedef typename T::DeviceDialog DeviceDialog;
		typedef typename T::FilterPanel FilterPanel;
		typedef MutDeviceShape<T> thistype;

		//	wxFileName filename;
		class strptrless {
		public:
			bool operator () (wxString * a, wxString * b) {
				if (a == b) return true;
				if (a == NULL) return true;
				if (b == NULL) return false;
				return (*a <= *b);
			}
		};

		typedef std::map<wxString *, MutDeviceShape *, strptrless> 
		stringmaptype;
		typedef typename stringmaptype::iterator stringmapiterator;
  
		virtual ~MutDeviceShape();
 
		bool Create (wxWindow * parent, wxWindowID id, 
			     const wxString & name = wxEmptyString)
			{
				DEBUGLOG(other, _T("Name %s"),name.c_str());
				bool state = MutIconShape::Create (parent,id);
				if (state) SetLabel(name);
				return state;
			}

		bool Create (wxWindow * parent, 
			     wxWindowID id, 
			     devicetype & d);


		const devicetype & GetDevice() const { return device; }
		devicetype & GetDevice() { return device; }

		const GUIDeviceBase * GetGUIDevice() const { 
			return ToGUIBase(device);
		}
		GUIDeviceBase * GetGUIDevice() { 
			return ToGUIBase(device);
		}
		mutabor::routeListType & getRoutes()
		{
#ifdef DEBUG
			if (!device) {
				UNREACHABLEC;
			}
#endif
			TRACEC;
			return device->GetRoutes();
		}

		
		const MutBoxChannelShapeList & GetChannels() const {
			return routes;
		}
	
		static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }
		static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

		/// add a device
		virtual void Add(DeviceClass * dev) {
			TRACEC;
			if (device)
				UNREACHABLEC;
			else 
				device = dev;
			TRACEC;
		};

		/// replace a device
		virtual bool Replace(devicetype olddev,
				     devicetype newdev) {
			/* we are using no references here, as we might get deleted
			   otherwise */
			TRACEC;
			if (device != olddev) {
				UNREACHABLEC;
				return false;
			} else 
				device = newdev;
			TRACEC;
			return true;
		}

		/// remove a device
		virtual bool Remove(devicetype dev) {
			TRACEC;
			if (device != dev) {
				UNREACHABLEC;
				return false;
			} else 
				device = NULL;
			TRACEC;
			return true;
		}

		/// add a route
		virtual void Add(MutBoxChannelShape *  route);
		/// replace a route
		virtual bool Replace(MutBoxChannelShape * oldroute,
				     MutBoxChannelShape * newroute);
		/// remove a route
		virtual bool Remove(MutBoxChannelShape * route);
		/// Move routes to another device 
		virtual bool MoveRoutes (MutDeviceShape * newclass);


		virtual bool Recompute();
//		virtual mutabor::Route getRoutes() = 0;
		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						 mutabor::Route & route) const = 0;
/*
		{ 
			ABSTRACT_FUNCTIONC;
			return NULL; 
		}
*/	
		virtual void ReadFilterPanel(wxWindow * panel, 
					     mutabor::Route & route) = 0;
/*
		{
			ABSTRACT_FUNCTIONC;
			return;
		}
*/
		virtual void ReadPanel(FilterPanel * panel, 
				       MutBoxChannelShape * channel);


		void OnKeyDown (wxKeyEvent & event);

		/** 
		 * Move the corresponding device in the device list and 
		 * update the GUI according to the new order.
		 * 
		 * \param event wxCommandEvent containing the request
		 */
		void CmMoveIcon (wxCommandEvent & event);



#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

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

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

	protected:
		MutBoxChannelShapeList routes;
		devicetype device;
		//	static stringmaptype stringmap;
		static wxSizerFlags sizerFlags;
		
		MutDeviceShape():MutIconShape(),
				 routes(),
				 device(NULL) {
		}

		MutDeviceShape (wxWindow * parent, wxWindowID id, 
				const wxString & name = wxEmptyString):
			MutIconShape(),
			routes(),
			device(NULL)
			{
				Create(parent, id, name);
			}

		MutDeviceShape (wxWindow * parent, 
				wxWindowID id, 
				devicetype & d):
			MutIconShape(),
			routes(),
			device(NULL) // device gets assigned by Create
		{
			Create (parent, id, d);
		}


		/** 
		 * Move the corresponding device in the device list and 
		 * update the GUI according to the new order.
		 * 
		 * \param count number of entries the device should be moved
		 *              up. Negative values indicate downwards direction.
		 */
		virtual void MoveDevice(int count) {
				device->MoveInList(count);
		}

		/** 
		 * Execute the double click. Despite its name this function must 
		 * not be called directly from a double click event handler.
		 * Click event handlers are not proof against control deletion.
		 */
		virtual void DoLeftDblClick();
		DeviceDialog * ShowDeviceDialog();

		virtual void InitializeDialog(DeviceDialog * in) const { }
		/// Initialize device data from a dialog
		/** Transfers the data from a dialog window into the corresponding 
		 *  device object. 
		 * \param dlg device dialog
		 * \retval true if the device has changed in a way that it must be reinitialized.
		 * \retval false otherwise
		 */
		virtual bool readDialog (DeviceDialog * dlg) { 
			mutASSERT (false);
			return false; 
		}
		/// detach device
		/** Detaches the device from any route and deletes the device. 
		 * \return true if the corresponding device has been removed and we can delete the Shape.
		 */
		virtual bool DetachDevice ();
		virtual bool replaceSelfBy (thistype  * newshape);
		virtual bool CanHandleType (mutabor::DevType  type) { return false; }

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 


#if 0
		void RemoveFromStringMap(stringmaptype & sm) {
			std::pair<stringmapiterator,stringmapiterator> 
				bounds = sm.equal_range(&m_label);
			for (stringmapiterator it = bounds.first; 
			     it != bounds.second; ++it) {
				if ((*it).second == this) {
					stringmapiterator it1 = it;
					it++;
					sm.erase(it1);
				}
			}
		}

		void InsertSelfToStringMap(stringmaptype & sm) {
			sm.insert(std::make_pair(&m_label,this)); 
		}
#endif	       
	private:
		DECLARE_ABSTRACT_CLASS(MutDeviceShape)
		DECLARE_EVENT_TABLE() 
	};

	template <class T>
	wxSizerFlags MutDeviceShape<T>::sizerFlags;




	typedef MutDeviceShape<inputdevicetypes> MutInputDeviceShape;
	typedef std::list<MutInputDeviceShape *> MutInputDeviceShapeList;

	typedef MutDeviceShape<outputdevicetypes> MutOutputDeviceShape;
	typedef std::list<MutOutputDeviceShape *> MutOutputDeviceShapeList;

}
#endif				/* DEVICESHAPE_H_PRECOMPILED */
#endif				/* DEVICESHAPE_H */
/*
 * \}
 */
