// -*-C++ -*-

/** \file
********************************************************************
* New output device shape for route window.
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
#ifdef __cplusplus
#else
dturiaedtr
#endif
#include "NewOutputDeviceShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"

using namespace mutabor;
MUTABOR_NAMESPACE(mutaborGUI)


void MutNewOutputDeviceShape::InitializeDialog(OutputDevDlg * out) const
{
	out -> SetType(DTNotSet);
}

bool MutNewOutputDeviceShape::replaceSelfBy (MutOutputDeviceShape  * newshape)
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
	p->AddOutputDevice(newshape,sizerFlags);
	return false;
}



IMPLEMENT_DYNAMIC_CLASS(MutNewOutputDeviceShape, MutOutputDeviceShape)

MUTABOR_NAMESPACE_END(mutaborGUI)

/*
 * \}
 */
