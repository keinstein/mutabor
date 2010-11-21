// -*-C++ -*-

/** \file
********************************************************************
* New box shape for route window.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/NewBoxShape.cpp,v 1.2 2010/11/21 13:15:49 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 1998
* $Date: 2010/11/21 13:15:49 $
* \version $Revision: 1.2 $
*
* $Log: NewBoxShape.cpp,v $
* Revision 1.2  2010/11/21 13:15:49  keinstein
* merged experimental_tobias
*
* Revision 1.1.2.4  2010-06-15 14:30:15  keinstein
* allow deleting of input devices in route window
* several bug fixes
* rudimentary box deletion support
*
* Revision 1.1.2.3  2010/06/02 11:20:09  keinstein
* Route.h:
* 	new enum BoxType
* 	new box type NewBox
*
* IconShape.cpp:
* 	Hide shape in MutIconShape::DeleteSelf
*
* MutChild.h:
* 	Changes on the increment value for Clientsize
*
* MutLogicWnd:
* 	smaller whitespace fixes
*
* MutRouteWnd.cpp:
* 	save sizerflags for MutBoxShape too
*
* BoxChannelShape.cpp:
* 	rename CreateRouteShape to CreateRoutePanel
* 	replace some wxDynamicCast by dynamic_cast
* 	add Box “New Box“ if current box is not found
* 	delete Route if route panel is disabled
*
* BoxChannelShape.h:
* 	Update BoxShape layout  if necessary
*
* BoxDlg.cpp:
* 	RoutePanel::AddBox: allow NULL boxShape
* 	Fix Bug that didn't preselect GUIDO boxes and Through mode
*
* BoxShape.cpp:
* 	fix color mapping for box numbers (shift right by 1 bit).
* 	Add MutBoxShape::sizerFlags
* 	SetBoxId: New function
* 	Use SetBoxId for setting Box Id an Label in sync
* 	AddChannel: call Layout()
* 	implement replacement in DoLeftDblClick (enables New Box)
* 	ShowBoxDialog: use dynamic_cast
* 	ReadDialog: Add Channel only if new route is enabled (not deleted)
* 	ReplaceSelfBy: new function (Unreachable as only needed for
* 		class NewMutBoxShape)
*
* NewBoxShape.cpp/.h:
* 	replaceSelfBy: new function
* 	initialize Box id as NewBox
*
* *.po/mutabor.pot/ *.gmo
*  	Sync with sources
*
* Revision 1.1.2.2  2010/03/30 08:38:27  keinstein
* added rudimentary command line support
* changed debug system to allow selection of messages via command line
* further enhancements to the route dialogs
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
//#include "Defs.h"
//#include "wx/wx.h"
#include "NewBoxShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"

IMPLEMENT_CLASS(NewMutBoxShape, MutBoxShape)

MutIcon& NewMutBoxShape::GetMutIcon()
{

	DEBUGLOG (other, _T("Checking icon"));
	wxASSERT(NewBoxBitmap.IsOk ());
	return NewBoxBitmap;
}

void NewMutBoxShape::InitializeDialog(BoxDlg * dlg) const {
	wxASSERT(dlg);
	dlg->SetBoxType(Box0);
	dlg->SetBoxNumber(0);
	dlg->SetTitle(_("Create Box"));
	dlg->DisableRemove(true);
}

bool NewMutBoxShape::replaceSelfBy (MutBoxShape  * newshape)
{
	MutRouteWnd * p = dynamic_cast<MutRouteWnd *> (m_parent);
	wxASSERT(p);
	// the "New device" icon won't be replaced, so we just append the device
	p->AddBox(newshape,sizerFlags);
	return false;
}



/*
 * \}
 */
