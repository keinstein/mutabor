/** \file               -*- C++ -*-
 ********************************************************************
 * Inline routitnes for the device class
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Device-inlines.h,v 1.1 2011/09/27 20:36:18 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:36:18 $
 * \version $Revision: 1.1 $
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
 * $Log: Device-inlines.h,v $
 * Revision 1.1  2011/09/27 20:36:18  keinstein
 * add a missed file
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(HEADERFILENAME) && !defined(PRECOMPILE)) \
	|| (!defined(HEADERFILENAME_PRECOMPILED))
#ifndef PRECOMPILE
#define HEADERFILENAME
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Device.h"

#ifndef HEADERFILENAME_PRECOMPILED
#define HEADERFILENAME_PRECOMPILED

// system headers which do seldom change

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutabor {



}

#endif // precompiled
#endif // header loaded


///\}
