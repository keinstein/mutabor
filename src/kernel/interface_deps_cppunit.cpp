/** \file               -*- C++ -*-
********************************************************************
* Interface_dependent functions.
*
* Copyright:   (c) 2013 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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

#include <iostream>
#include "interface_deps.h"
#include <stdio.h>
#include "cppunit/Message.h"
#include "cppunit/Asserter.h"
#include "boost/format.hpp"
extern "C" {
	void mutabor_assert_fail(const char *file,
				 int line,
				 const char *func,
				 const char *cond,
				 const char *msg) {
		std::string assemsg 
			= boost::str(boost::format("%s:%d:%s\nFunction: %s; Expression: %s")
				     % file
				     % line
				     % (msg?msg:"")
				     % func
				     % cond);
		std::cerr << "assertion failed: \n" << assemsg ;
		CPPUNIT_NS::Message mesg( "assertion failed",
					  assemsg);
	
		CPPUNIT_NS::Asserter::fail(mesg,
					   CPPUNIT_NS::SourceLine(file,
								  line));
	}
}

///\}
