/** \file 
 ********************************************************************
 * file input of gsp (GMN Soft Parser)
 *
 * Copyright:   (c) 2008 TU Dresden
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
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ##################################################################
// 
// ##################################################################

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_GMN_GSP_FILE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_GMN_GSP_FILE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_GMN_GSP_FILE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/gmn/GSP.h"

#ifndef MU32_ROUTING_GMN_GSP_FILE_H_PRECOMPILED
#define MU32_ROUTING_GMN_GSP_FILE_H_PRECOMPILED

// system headers which do seldom change


extern mutString CurrentLine; //[GSP_MAX_LINE];

extern size_t  CurrentPos;

extern int  Eof;

int OpenFile(const mutString &Name);

int CloseFile();

int ReadNewLine();

#endif /* precompile */
#endif


///\}
