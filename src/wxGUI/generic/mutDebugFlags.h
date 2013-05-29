/** \file 
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2008-2012 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/13 18:26:13 $
 * \version $Revision: 1.10 $
 * \license GPL
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
// the description is translated by wxWidgets
DEBUGFLAG(other, N_("Unspecified debug information"))
DEBUGFLAG(kernel_exec, N_("Debug Execute.cpp"))
DEBUGFLAG(kernel_tabgen, N_("Debug table generator"))
DEBUGFLAG(kernel_runtime, N_T("Debug other runtime functions of the kernel"))
DEBUGFLAG(kernel_parser, N_("Debug the parser of the Mutabor kernel"))
DEBUGFLAG(kernel_box, N_("Debug the parser of the Mutabor kernel"))
DEBUGFLAG(gmnfile, N_("Debug the GUIDO file devices"))
DEBUGFLAG(gui,   N_("Other gui related debug information"))
DEBUGFLAG(dialog, N_("Debug configuration and postprocessing of dialogs"))
DEBUGFLAG(routing, N_("Debug the routing system"))
DEBUGFLAG(routinggui, N_("Debug the routing system GUI"))
DEBUGFLAG(midiio, N_("Debug the MIDI input/output system"))
DEBUGFLAG(midifile, N_("Debug the MIDI file devices"))
DEBUGFLAG(mutparser, N_("Debug the Mutabor file parser"))
DEBUGFLAG(config, N_("Debug the config file parser"))
DEBUGFLAG(docview, N_("Debug the Document/View framework"))
DEBUGFLAG(eventqueue, N_("Print unhandled events in the queue"))
DEBUGFLAG(editor, N_("Debug editor related functionality"))
DEBUGFLAG(smartptr, N_("Debug smart pointer related functionality"))
DEBUGFLAG(trace, N_("Output some tracepoints"))
DEBUGFLAG(timer, N_("Trace thread timer problems"))
DEBUGFLAG(always, N_("Show messages that are always shown ;-). (for internal use only)"))

///\}
