/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mutDebugFlags.h,v 1.8 2011/09/29 05:26:59 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/29 05:26:59 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: mutDebugFlags.h,v $
 * Revision 1.8  2011/09/29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.7  2011-09-05 06:42:47  keinstein
 * Added GUIBoxData.h
 *
 * Revision 1.6  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.5  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.4  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup debug
 * \{
 ********************************************************************/
/*
 *  MutDebugFlags.h
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 25.03.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */

DEBUGFLAG(other, _("Unspecified debug information"))
DEBUGFLAG(gui,   _("Other gui related debug information"))
DEBUGFLAG(dialog, _("Debug configuration and postprocessing of dialogs"))
DEBUGFLAG(routing, _("Debug the routing system"))
DEBUGFLAG(midiio, _("Debug the MIDI input/output system"))
DEBUGFLAG(midifile, _("Debug the MIDI file devices"))
DEBUGFLAG(mutparser, _("Debug the Mutabor file parser"))
DEBUGFLAG(config, _("Debug the config file parser"))
DEBUGFLAG(docview, _("Debug the Document/View framework"))
DEBUGFLAG(eventqueue, _("Print unhandled events in the queue"))
DEBUGFLAG(editor, _("Debug editor related functionality"))
DEBUGFLAG(smartptr, _("Debug smart pointer related functionality"))

///\}
