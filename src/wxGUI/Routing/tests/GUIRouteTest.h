/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:26 $
 * \version $Version$
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
 * \addtogroup tests
 * \{
 ********************************************************************/
#ifndef __TESTS_GUIROUTETEST_H__
#define __TESTS_GUIROUTETEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Route.h"
#include "src/kernel/Runtime.h"

class GUIRouteTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( GUIRouteTest );
	CPPUNIT_TEST( testConnect );
	CPPUNIT_TEST_SUITE_END();

protected:
//	mutabor::Route route;

public:
	GUIRouteTest()
	{
	}

	virtual ~GUIRouteTest()
	{
	}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp();
	void tearDown();

	void testConnect();
};

#endif
