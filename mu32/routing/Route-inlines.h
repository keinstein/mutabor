/** \file               -*- C++ -*-
 ********************************************************************
 * Inline functions from Route.h
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Route-inlines.h,v 1.1 2011/09/27 20:18:30 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:18:30 $
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
 * $Log: Route-inlines.h,v $
 * Revision 1.1  2011/09/27 20:18:30  keinstein
 * add a file missed during last commit
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_ROUTE_INLINES_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_ROUTE_INLINES_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Route.h"

#ifndef MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED
#define MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED

// system headers which do seldom change
#include "Device.h"


namespace mutabor {
	inline Route RouteFactory::Create(
		InputDevice in,
		OutputDevice out,
		RouteType type,
		int iFrom,
		int iTo,
		int box,
		bool active,
		int oFrom,
		int oTo,
		bool oNoDrum,
		Route next) {
		if (factory) 
			return factory->DoCreate(in,out,type,iFrom,iTo,
						 box,active,
						 oFrom,oTo,oNoDrum/*,next*/);
		else {
			UNREACHABLECT(RouteFactory);
			return NULL;
		}
			
	}
}


#endif // precompiled
#endif // header loaded


///\}
