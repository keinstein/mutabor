/** \file */// -*- C++ -*-
/********************************************************************
 * Output device shape for route window.
 *
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_OUTPUTDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_OUTPUTDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_OUTPUTDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/wxGUI/Routing/DeviceShape.h"

#if 0
#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"

#ifndef MUWX_ROUTING_OUTPUTDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_OUTPUTDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"


namespace mutaborGUI {
	class MutOutputDeviceShape:public MutDeviceShape
	{
		friend class GUIDeviceFactory;
	public:
		typedef mutabor::OutputDevice devicetype;

		virtual ~MutOutputDeviceShape();


		bool Create (wxWindow * parent, wxWindowID id, 
			     const wxString & name)
			{
				device = NULL;
				return MutDeviceShape::Create (parent,id, name);
			}

		bool Create (wxWindow * parent, wxWindowID id, mutabor::OutputDevice & d);

		static void SetSizerFlags (wxSizerFlags flags) 
			{
				sizerFlags = flags; 
			}

		static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

		void SetLabel(const wxString & st );        

		MutIcon & GetMutIcon ()
			{
				return MidiOutputDevBitmap;
			}
	
		// alias some overloaded virtual functions
		using MutDeviceShape::Add;
		using MutDeviceShape::Replace;
		using MutDeviceShape::Remove;
		using MutDeviceShape::MoveRoutes;

		virtual void Add(mutabor::OutputDevice  dev);
		/// replace a dev
		virtual bool Replace(mutabor::OutputDevice olddev,
				     mutabor::OutputDevice newdev);
		/// remove a dev
		virtual bool Remove(mutabor::OutputDevice dev);

		mutabor::Route getRoutes()
			{
				UNREACHABLEC;
				abort();
			}
		const MutBoxChannelShapeList & getRoutesList()
			{
				return routes;
			}
	
		const mutabor::OutputDevice & GetDevice() const 
			{
				return device;
			}
		mutabor::OutputDevice & GetDevice() 
			{
				return device;
			}

		virtual void DoLeftDblClick();

		OutputDevDlg * ShowDeviceDialog();

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		virtual wxPanel * GetOutputFilterPanel(wxWindow * parent, 
						       mutabor::Route& route) const
			{ 
				ABSTRACT_FUNCTIONC;
				return NULL; 
			}
	
		virtual void ReadOutputFilterPanel(wxWindow * panel, mutabor::Route & route)
			{
				ABSTRACT_FUNCTIONC;
			}	
		virtual void ReadPanel(OutputFilterPanel * panel, MutBoxChannelShape * channel);
	
	protected:
		static wxSizerFlags sizerFlags;
		mutabor::OutputDevice device;

		MutOutputDeviceShape():MutDeviceShape(),device(NULL) { }


		MutOutputDeviceShape (wxWindow * parent, wxWindowID id, 
				      const wxString & name) {
			Create (parent, id, name);
		}
	
		MutOutputDeviceShape (wxWindow * parent, wxWindowID id, 
				      mutabor::OutputDevice d):
			MutDeviceShape() {
			Create (parent, id,  d);
		}

		/** 
		 * Move the corresponding device in the device list and 
		 * update the GUI according to the new order.
		 * 
		 * \param count number of entries the device should be moved
		 *              up. Negative values indicate downwards direction.
		 */
		virtual void MoveDevice(int count);

		virtual void InitializeDialog(OutputDevDlg * out) const
			{
				DEBUGLOG(other, _T("Initializing only generic OutputDeviceShape"));
			}

		virtual bool readDialog (OutputDevDlg * out) { 
			mutASSERT (false);
			return false; 
		}

		/// detach device
		/** Detaches the device from any route and deletes the device. 
		 * \return true if the corresponding device has been removed and we can delete the Shape.
		 */
		virtual bool DetachDevice ();
		virtual bool replaceSelfBy (MutOutputDeviceShape  * newshape);

		virtual bool CanHandleType (mutabor::DevType type) { return false; };

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

	private:
		DECLARE_ABSTRACT_CLASS(MutDeviceShape)
	};


}
#endif				/* OUTPUTDEVICESHAPE_H_PRECOMPILED */
#endif                          /* if 0 */
#endif				/* OUTPUTDEVICESHAPE_H */
/*
 * \}
 */
