// -*- C++ -*-

/** \file
 ********************************************************************
 * Error handling for C++ parts.
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
 * \bug Chord hold currently holds all notes. It must be saved note specific.
 ********************************************************************
 *\addtogroup kernel
 *\{
 ********************************************************************/
#include "src/kernel/error.h"

MUTABOR_NAMESPACE(mutabor)

unhandled_exception_handler_t  unhandled_exception_handler;
unhandled_exception_handler_t * unhandled_exception_handler_t::handler=NULL;

MUTABOR_NAMESPACE_END(mutabor)

/** \} */
