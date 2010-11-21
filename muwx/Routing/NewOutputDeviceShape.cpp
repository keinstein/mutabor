// -*-C++ -*-

/** \file
********************************************************************
* New output device shape for route window.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/NewOutputDeviceShape.cpp,v 1.2 2010/11/21 13:15:49 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 2009/11/23
* $Date: 2010/11/21 13:15:49 $
* \version $Revision: 1.2 $
*
* $Log: NewOutputDeviceShape.cpp,v $
* Revision 1.2  2010/11/21 13:15:49  keinstein
* merged experimental_tobias
*
* Revision 1.1.2.4  2010-05-07 11:40:28  keinstein
* actual_settings
*
* Revision 1.1.2.3  2010/03/30 08:40:15  keinstein
* added rudimentary command line support
* changed debug system to allow selection of messages via command line
* further enhancements to the route dialogs
*
* Revision 1.1.2.2  2010/01/14 18:14:20  keinstein
* fix usage of installation prefix
* MutInputDeviceShape/MutOutputDeviceShape:
*     use GetType for type checking in OnChoiceSelected
*     make InitalizeDialog const
* MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
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
#include "NewOutputDeviceShape.h"

void MutNewOutputDeviceShape::InitializeDialog(OutputDevDlg * out) const
{
	out -> SetType(DTNotSet);
}

bool MutNewOutputDeviceShape::replaceSelfBy (MutOutputDeviceShape  * newshape)
{
	MutRouteWnd * p = dynamic_cast<MutRouteWnd *> (m_parent);
	if (!p) UNREACHABLEC;
	// the "New device" icon won't be replaced, so we just append the device
	p->AddOutputDevice(newshape,sizerFlags);
	return false;
}



IMPLEMENT_DYNAMIC_CLASS(MutNewOutputDeviceShape, MutOutputDeviceShape)
/*
 * \}
 */
