/** \file               -*- C++ -*-
 ********************************************************************
 * Interface_dependent functions.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
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
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// availlable groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute

#include "interface_deps.h"
#include "stdio.h"
#include "stdlib.h"
void mutabor_assert_fail(const char *file,
			 int line,
			 const char *func,
			 const char *cond,
			 const char *msg) {
	fprintf(stderr,
		"%s:%d:%s:\n Assertion failed: %s\n%s",
		file,
		line,
		func,
		cond,
		msg);
	abort();
}


///\}
