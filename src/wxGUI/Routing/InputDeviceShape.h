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
 * $Log: InputDeviceShape.h,v $
 * Revision 1.7  2011/11/02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.6  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.5  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
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
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.9  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.8  2010-06-15 14:30:15  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
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
 * Revision 1.1.2.4  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
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
				DEBUGLOG (other,_T (""));
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
