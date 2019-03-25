// -*-C++ -*-

/** \file
 ********************************************************************
 * Devices Basisklassen.
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
#include "NewInputDeviceShape.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxShape.h"

#include "src/kernel/routing/Route-inlines.h"


using namespace mutabor;

MUTABOR_NAMESPACE(mutaborGUI)

	void MutNewInputDeviceShape::InitializeDialog(InputDevDlg * in) const
	{
		in -> SetType(DTNotSet);
		in -> DisableRemove();
	}

	bool MutNewInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
	{
		auto parent = m_parent;
		MutRouteWnd * p = dynamic_cast<MutRouteWnd *> (m_parent);
		while (parent && !p) {
			parent = parent->GetParent();
			p = dynamic_cast<MutRouteWnd *> (m_parent);
		}

		mutASSERT(p);
		if (!p) {
			UNREACHABLEC;
			return false;
		}
		// the "New device" icon won't be replaced, so we just append the device
		p->AddInputDevice(newshape,sizerFlags);
		return false;
	}



	IMPLEMENT_DYNAMIC_CLASS(MutNewInputDeviceShape, MutInputDeviceShape)

MUTABOR_NAMESPACE_END(mutaborGUI)

/*
 * \}
 */
