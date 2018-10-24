// -*- C++ -*-
/** \file
 ********************************************************************
 * New input device shape for route window.
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_NEWINPUTDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_NEWINPUTDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_NEWINPUTDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DeviceShape.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_NEWINPUTDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_NEWINPUTDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

namespace mutaborGUI {


	class MutNewInputDeviceShape:public MutInputDeviceShape
	{

	public:
		MutNewInputDeviceShape():MutInputDeviceShape() {}

		MutNewInputDeviceShape (wxWindow * parent, wxWindowID id):MutInputDeviceShape() 
			{
				Create(parent, id);
			}

		bool Create (wxWindow * parent, wxWindowID id)
			{
				return MutInputDeviceShape::Create (parent,id,_("New Input device"));
			}

		MutIcon & GetMutIcon ()
			{
				return NewInputDevBitmap;
			}

		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						 mutabor::Route & route) const {
			mutUnused(route);
			UNREACHABLEC;
			return new wxPanel(parent);
		}
		virtual void ReadFilterPanel(wxWindow * panel, 
					     mutabor::Route & route) {
			mutUnused(panel);
			mutUnused(route);
			UNREACHABLEC;
		}
	protected:
		virtual void InitializeDialog(InputDevDlg * in) const;
		virtual bool replaceSelfBy (MutInputDeviceShape  * newshape);

	private:
		DECLARE_DYNAMIC_CLASS(MutInputDeviceShape)
	};

}
#endif				/* NEWINPUTDEVICESHAPE_H_PRECOMPILED */
#endif				/* NEWINPUTDEVICESHAPE_H */
/*
 * \}
 */
