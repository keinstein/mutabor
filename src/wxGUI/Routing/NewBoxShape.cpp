// -*-C++ -*-

/** \file
 ********************************************************************
 * New box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/NewBoxShape.cpp,v 1.6 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 *\addtogroup route
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

namespace mutaborGUI {

	IMPLEMENT_CLASS(NewMutBoxShape, MutBoxShape)

	MutIcon& NewMutBoxShape::GetMutIcon()
	{

		DEBUGLOG (other, _T("Checking icon"));
		mutASSERT(NewBoxBitmap.IsOk ());
		return NewBoxBitmap;
	}

	void NewMutBoxShape::InitializeDialog(BoxDlg * dlg) const {
		mutASSERT(dlg);
		mutASSERT(boxId == NewBox);
		dlg->SetBoxType(Box0);
		dlg->SetBoxNumber(RouteClass::GetNextFreeBox());
		dlg->SetTitle(_("Create Box"));
		dlg->DisableRemove(true);
	}

	bool NewMutBoxShape::replaceSelfBy (MutBoxShape  * newshape)
	{
		MutRouteWnd * p = dynamic_cast<MutRouteWnd *> (m_parent);
		mutASSERT(p);
		// the "New device" icon won't be replaced, so we just append the device
		p->AddBox(newshape,sizerFlags);
		return false;
	}

}

/*
 * \}
 */
