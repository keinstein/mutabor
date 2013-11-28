// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
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
 ********************************************************************
 *\addtogroup GUIroute
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutIcon.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/resourceload.h"
//#include "Device.h"


#ifndef MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"
namespace mutaborGUI {

	typedef GisOutputFilterPanelBase GisOutputFilterPanel;

	class MutOutputGuidoFileDeviceShape:public MutOutputDeviceShape
	{
		friend class GUIGisFactory;
	protected:
		MutOutputGuidoFileDeviceShape():MutOutputDeviceShape() {}
		MutOutputGuidoFileDeviceShape (wxWindow * parent,
					       wxWindowID id, 
					       mutabor::OutputDevice d):
			MutOutputDeviceShape() {
			Create (parent,id,d);
		}
	public:
		bool Create (wxWindow * parent, wxWindowID id, mutabor::OutputDevice d)
			{
				return MutOutputDeviceShape::Create(parent,id,d);
			}

		virtual MutIcon & GetMutIcon () 
			{
				TRACEC;
				return GuidoFileBitmap;
			}

		void SetLabel(const wxString & st ) {
			fileName = st;
			fileName.Normalize();
			MutOutputDeviceShape::SetLabel (fileName.GetFullName());
		}
	
		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						 mutabor::Route & route) const;
		virtual void ReadFilterPanel(wxWindow * panel, 
					     mutabor::Route & route);


	protected: 
		virtual void InitializeDialog(OutputDevDlg * out) const;
		virtual bool readDialog (OutputDevDlg * out);
		virtual bool CanHandleType (mutabor::DevType  type) { 
			return type == mutabor::DTGis; 
		}

		wxFileName fileName;

	private:
		DECLARE_DYNAMIC_CLASS(MutOutputGuidoFileDeviceShape)

	};
}
#endif				/* OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED */
#endif				/* OUTPUTGUIDOFILEDEVICESHAPE_H */
/*
 * \}
 */
