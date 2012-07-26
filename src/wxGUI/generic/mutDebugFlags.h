/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/generic/mutDebugFlags.h,v 1.10 2011/10/13 18:26:13 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/13 18:26:13 $
 * \version $Revision: 1.10 $
 * \license GPL
 *
 * $Log: mutDebugFlags.h,v $
 * Revision 1.10  2011/10/13 18:26:13  keinstein
 * Fix a Bug in the kernel:
 * retuning case did not execute the following statements,
 * which lead to unexpected results
 *
 * Revision 1.9  2011-10-02 16:58:43  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.8  2011-09-29 05:26:59  keinstein
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
DEBUGFLAG(kernel_exec, _("Debug Execute.cpp"))
DEBUGFLAG(kernel_tabgen, _("Debug table generator"))
DEBUGFLAG(kernel_runtime, _("Debug other runtime functions of the kernel"))
DEBUGFLAG(kernel_parser, _("Debug the parser of the Mutabor kernel"))
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
DEBUGFLAG(trace, _("Output some tracepoints"))

///\}
