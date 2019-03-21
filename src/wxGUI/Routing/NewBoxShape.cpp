// -*-C++ -*-

/** \file
********************************************************************
* New box shape for route window.
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
#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/NewBoxShape.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxShape.h"

//#include "MutApp.h"
//#include "MutIcon.h"
//#include "InputDevDlg.h"
//#include "Device.h"

using namespace mutabor;

MUTABOR_NAMESPACE(mutaborGUI)

IMPLEMENT_CLASS(NewMutBoxShape, MutBoxShape)

MutIcon& NewMutBoxShape::GetMutIcon()
{

	DEBUGLOG (other, "Checking icon" );
	mutASSERT(NewBoxBitmap.IsOk ());
	return NewBoxBitmap;
}

void NewMutBoxShape::InitializeDialog(BoxDlg * dlg) const {
	mutASSERT(dlg);
	mutASSERT(box == NULL);
	dlg->SetBoxType(Box0);
	dlg->SetBoxNumber(BoxClass::GetNextFreeBox());
	dlg->SetTitle(_("Create Box"));
	dlg->DisableRemove(true);
}

bool NewMutBoxShape::replaceSelfBy (MutBoxShape  * newshape)
{
	MutRouteWnd * p = dynamic_cast<MutRouteWnd *> (m_parent);
	mutASSERT(p);

	/* make shure the shape has the correct size.  this
	   must be done here, as we could have added some
	   content to the control (e.g. BoxChannelShapes) */
	// newshape -> Layout(); // we call SetSize() from Fit(), and Layout() from OnSize();
	newshape -> Fit();

	// the "New device" icon won't be replaced, so we just append the device
	p->AddBox(newshape,sizerFlags);
	return false;
}

MUTABOR_NAMESPACE_END(mutaborGUI)


/*
 * \}
 */
