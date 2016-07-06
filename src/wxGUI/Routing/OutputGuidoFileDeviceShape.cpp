// -*-C++ -*-
/** \file
 ********************************************************************
 * Input device shape for reading GUIDO files in the route window.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
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
#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/OutputGuidoFileDeviceShape.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "OutputDevDlg.h"
//#include "Device.h"

using namespace mutabor;

namespace mutaborGUI {

	void MutOutputGuidoFileDeviceShape::InitializeDialog(OutputDevDlg * out) const
	{
		mutASSERT(device);
		mutASSERT(device->GetType() == DTGis);
		mutASSERT(out);
		out -> SetType(DTGis);
		out -> SetGUIDOFile(wxString::FromUTF8(device->GetName().c_str()));
	}

	bool MutOutputGuidoFileDeviceShape::readDialog (OutputDevDlg * out)
	{
		mutASSERT(device);
		mutASSERT(device->GetType() == DTGis);
		mutASSERT(out);
		mutASSERT (out -> GetType() == DTGis);
		DEBUGLOG (other, ("File %s"),  (out -> GetGUIDOFile()).c_str());
		device->SetName ((const char *)(out -> GetGUIDOFile().ToUTF8()));
		SetLabel (device->GetName());
		return true;
	}

	wxPanel * MutOutputGuidoFileDeviceShape::GetFilterPanel(wxWindow * parent, 
								      Route & route) const
	{
		mutUnused(route);
		GisOutputFilterPanel * panel = new GisOutputFilterPanel(parent);
		if (!panel) return NULL;
		// Room for actions
		return panel;
	}


	void MutOutputGuidoFileDeviceShape::ReadFilterPanel(wxWindow * panel, Route & route)
	{
		mutUnused(route);
		GisOutputFilterPanel * pan = dynamic_cast<GisOutputFilterPanel *> (panel);
		if (!pan) {
			UNREACHABLEC;
			return;
		}
		// Room for actions
	
	}



	IMPLEMENT_DYNAMIC_CLASS(MutOutputGuidoFileDeviceShape, MutOutputDeviceShape)
}
/*
 * \}
 */
