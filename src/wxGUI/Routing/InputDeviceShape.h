// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/InputDeviceShape.h,v 1.7 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.7 $
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
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_INPUTDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_INPUTDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_INPUTDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"

#ifndef MUWX_ROUTING_INPUTDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_INPUTDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"


namespace mutaborGUI {
	class MutBoxChannelShape;
	class InputFilterPanel;


	class MutInputDeviceShape:public MutDeviceShape{
		friend class GUIInputDeviceFactory;
	protected: 
		mutabor::InputDevice device;
		//	static stringmaptype stringmap;
		static wxSizerFlags sizerFlags;


		MutInputDeviceShape():MutDeviceShape(),device(NULL) {
		}

		MutInputDeviceShape (wxWindow * parent, wxWindowID id, 
				     const wxString &
				     name):MutDeviceShape (),
					   device(NULL)
		{
			Create (parent, id, name);
		}


		MutInputDeviceShape (wxWindow * parent, wxWindowID id, 
				     mutabor::InputDevice & d):
			MutDeviceShape(),
			device(NULL)
		{
			Create (parent, id, d);
		}
	public:
		typedef mutabor::InputDevice devicetype;

		virtual ~MutInputDeviceShape();

		bool Create (wxWindow * parent, wxWindowID id, const wxString &
	                     name)
		{
			TRACEC;
			device = NULL;
			TRACEC;
			return MutDeviceShape::Create (parent, id, name);
		}

		bool Create (wxWindow * parent, wxWindowID id, 
			     mutabor::InputDevice & d);

		/*
		  static MutInputDeviceShape * CreateShape(wxWindow * parent,
		  wxWindowID id,
		  mutabor::InputDevice d);

		  MutInputDeviceShape * CreateShape (mutabor::InputDevice d) 
		  {
		  DEBUGLOG (other,_T (""));
		  return CreateShape (m_parent, wxID_ANY,d);
		  }
		*/
		static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }
		static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

		void SetLabel(const wxString & st );

		MutIcon & GetMutIcon ()
		{
			return MidiInputDevBitmap;
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
		
		// pull some functions from MutDeviceShape

		// alias some overloaded virtual functions
		using MutDeviceShape::Add;
		using MutDeviceShape::Replace;
		using MutDeviceShape::Remove;
		using MutDeviceShape::MoveRoutes;

		virtual void Add(mutabor::InputDeviceClass * dev);
		/// replace a dev
		virtual bool Replace(mutabor::InputDevice & olddev,
				     mutabor::InputDevice & newdev);
		/// remove a dev
		virtual bool Remove(mutabor::InputDeviceClass * dev);

#if 0 
		/// attach a device to the shape
		void Attatch(mutabor::InputDevice & dev) {
			mutASSERT(device.get() == NULL);
			TRACEC;
			device = dev;
			TRACEC;
		}
		/// Attatch to a given route
		void Attatch(mutabor::Route & route) {
			TRACEC;
			connect(device,route);
			TRACEC;
		}
		/// Attatch to a given route
		void Attatch(MutBoxChannelShape * route) {
			TRACEC;
			Attatch(route->GetRoute());
			TRACEC;
		}

		/// Replace a given route 
		void Reconnect(mutabor::Route & oldroute, 
			       mutabor::Route & newroute) {
			TRACEC;
			reconnect(device,oldroute,newroute);
			TRACEC;
		}
		/// Replace a given route 
		void Reconnect(MutBoxChannelShape * oldroute, 
			       MutBoxChannelShape * newroute) {
			TRACEC;
			Reconnect(oldroute->GetRoute(),newroute->GetRoute());
			TRACEC;
		}

		/// Detach a device from the shape
		/** this function is usually called short before the
		    deletion of the window
		*/
		void Detatch(mutabor::InputDevice & dev) {
			TRACEC;
			mutASSERT(device == dev);
			TRACEC;
			if (device)
				ToGUIBase(device).Detatch(this);
			TRACEC;
			device = NULL;
			TRACEC;
		}
		/// Detatch a given route
		void Detatch(mutabor::Route & route) {
			TRACEC;
			disconnect(device,route);
			TRACEC;
		}
		/// Detatch a given route
		void Detatch(MutBoxChannelShape * route) {
			TRACEC;
			Detatch(route->GetRoute());
			TRACEC;
		}

#endif
	
		const mutabor::InputDevice & GetDevice() const { return device; }
		mutabor::InputDevice & GetDevice() { return device; }

		const GUIInputDeviceBase * GetGUIDevice() const { 
			return ToGUIBase(device);
		}
		GUIInputDeviceBase * GetGUIDevice() { 
			return ToGUIBase(device);
		}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void DoLeftDblClick();
		InputDevDlg * ShowDeviceDialog();
		virtual wxPanel * GetInputFilterPanel(wxWindow * parent, 
						      mutabor::Route & route) const
		{ 
			ABSTRACT_FUNCTIONC;
			return NULL; 
		}
	
		virtual void ReadInputFilterPanel(wxWindow * panel, 
						  mutabor::Route & route) 
		{
			ABSTRACT_FUNCTIONC;
			return;
		}
		virtual void ReadPanel(InputFilterPanel * panel, MutBoxChannelShape * channel);

	protected: 
		virtual void InitializeDialog(InputDevDlg * in) const { }
		/// Initialize device data from a dialog
		/** Transfers the data from a dialog window into the corresponding 
		 *  device object. 
		 * \param in input device dialog
		 * \retval true if the device has changed in a way that it must be reinitialized.
		 * \retval false otherwise
		 */
		virtual bool readDialog (InputDevDlg * in) { 
			mutASSERT (false);
			return false; 
		}
		/// detach device
		/** Detaches the device from any route and deletes the device. 
		 * \return true if the corresponding device has been removed and we can delete the Shape.
		 */
		virtual bool DetachDevice ();
		virtual bool replaceSelfBy (MutInputDeviceShape  * newshape);
		virtual bool CanHandleType (mutabor::DevType  type) { return false; }

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 
	private:
		DECLARE_DYNAMIC_CLASS(MutDeviceShape)
	};


}
#endif				/* INPUTDEVICESHAPE_H_PRECOMPILED */
#endif				/* INPUTDEVICESHAPE_H */
/*
 * \}
 */
