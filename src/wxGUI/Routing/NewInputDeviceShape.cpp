// -*-C++ -*-

/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/NewInputDeviceShape.cpp,v 1.5 2011/09/30 18:07:06 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/09/30 18:07:06 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: NewInputDeviceShape.cpp,v $
 * Revision 1.5  2011/09/30 18:07:06  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.4  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-06-15 14:30:15  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.4  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.3  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.cpp,v
 * Revision 1.1.2.3  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
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
#include "NewInputDeviceShape.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxShape.h"

#include "src/kernel/routing/Route-inlines.h"


using namespace mutabor;

namespace mutaborGUI {

	void MutNewInputDeviceShape::InitializeDialog(InputDevDlg * in) const
	{
		in -> SetType(DTNotSet);
		in -> DisableRemove();
	}

	bool MutNewInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
	{
		MutRouteWnd * p = dynamic_cast<MutRouteWnd *> (m_parent);
		mutASSERT(p);
		// the "New device" icon won't be replaced, so we just append the device
		p->AddInputDevice(newshape,sizerFlags);
		return false;
	}



	IMPLEMENT_DYNAMIC_CLASS(MutNewInputDeviceShape, MutInputDeviceShape)

}
/*
 * \}
 */
