/** \file 
 ********************************************************************
 * Debug flags for mutabor debug mode
 *
 * Copyright:   (c) 2008-2012 TU Dresden
 *               changes after 2011-11 (c) by the authors
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 ********************************************************************
 * \addtogroup debug
 * \{
 ********************************************************************/
// the description is translated by wxWidgets
DEBUGFLAG(other,          N_("Unspecified debug information"))
DEBUGFLAG(kernel_exec,    N_("Debug Execute.cpp"))
DEBUGFLAG(kernel_tabgen,  N_("Debug table generator"))
DEBUGFLAG(kernel_runtime, N_T("Debug other runtime functions of the kernel"))
DEBUGFLAG(kernel_parser,  N_("Debug the parser of the Mutabor kernel"))
DEBUGFLAG(kernel_box,     N_("Debug the parser of the Mutabor kernel"))
DEBUGFLAG(gmnfile,        N_("Debug the GUIDO file devices"))
DEBUGFLAG(gui,            N_("Other gui related debug information"))
DEBUGFLAG(dialog,         N_("Debug configuration and postprocessing of dialogs"))
DEBUGFLAG(routing,        N_("Debug the routing system"))
DEBUGFLAG(routinggui,     N_("Debug the routing system GUI"))
DEBUGFLAG(menu,           N_("Debug the menu handling and updating"))
DEBUGFLAG(midiio,         N_("Debug the MIDI input/output system"))
DEBUGFLAG(midifile,       N_("Debug the MIDI file devices"))
DEBUGFLAG(mutparser,      N_("Debug the Mutabor file parser"))
DEBUGFLAG(config,         N_("Debug the config file parser"))
DEBUGFLAG(docview,        N_("Debug the Document/View framework"))
DEBUGFLAG(eventqueue,     N_("Print unhandled events in the queue"))
DEBUGFLAG(editor,         N_("Debug editor related functionality"))
DEBUGFLAG(editlexer,      N_("Debug editor language lexer related functionality"))
DEBUGFLAG(smartptr,       N_("Debug smart pointer related functionality"))
DEBUGFLAG(trace,          N_("Output some tracepoints"))
DEBUGFLAG(timer,          N_("Trace thread timer problems"))
DEBUGFLAG(thread,         N_("Trace thread problems"))
DEBUGFLAG(always,         N_("Show messages that are always shown ;-). (for internal use only)"))

///\}
