// -*- C++ -*-

/** \file
 ********************************************************************
 * Devices base classes. Icons used in route Window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/RouteIcons.h,v 1.2 2010/11/21 13:15:50 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2010/11/21 13:15:50 $
 * \version $Revision: 1.2 $
 *
 * $Log: RouteIcons.h,v $
 * Revision 1.2  2010/11/21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2009-11-30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v 
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

#ifndef MUTROUTEICONS_H
#define MUTROUTEICONS_H

#include "Defs.h"
#include "MutIcon.h"

extern MutIcon NewInputDevBitmap;
extern MutIcon MidiInputDevBitmap;
extern MutIcon NewOutputDevBitmap;
extern MutIcon MidiOutputDevBitmap;
extern MutIcon MidiFileBitmap;
extern MutIcon GuidoFileBitmap;
extern MutIcon BoxBitmap;
extern MutIcon NewBoxBitmap;
extern MutIcon ActiveChannelBitmap;
extern MutIcon PassiveChannelBitmap;

bool initMutIconShapes();

#endif				/* MUTROUTEICONS_H */
/*
 * \}
 */
