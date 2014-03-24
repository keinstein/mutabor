/** \file 
 ********************************************************************
 * Runtime functions of the (mainly C) old kernel of Mutabor
 *
 * Copyright:   (c) 2008 TU Dresden
 *              changes after 2011-11 owned by the authors
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
 * \addtogroup runtime
 * \{
 ********************************************************************/
/* ------------------------------------------------------------------ */
/* Mutabor 2.win, 1997, R.Krauﬂe */
/* Laufzeitfunktionen der DLL */
/* ------------------------------------------------------------------ */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_RUNTIME_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_RUNTIME_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_RUNTIME_H
#endif

/* --------------------------------------------------------------------------- */
/* headers */
/* --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"

#ifndef MU32_RUNTIME_H_PRECOMPILED
#define MU32_RUNTIME_H_PRECOMPILED

/* system headers which do seldom change */

#include <setjmp.h>


extern jmp_buf weiter_gehts_nach_compilerfehler;


/*  void  InDeviceActionAll(char action); */
/*void  InDeviceAction(int inDevNr, enum mutabor::MutaborModeType action); */

#if 0
#include "wx/wxchar.h"
#if !defined(__WXMSW__)
#ifndef UINT
#define UINT unsigned int
#endif
#endif
#endif



#endif /* precompiled */
#endif



/** \} */
