/** \file               -*- C++ -*-
 ********************************************************************
 * Test suite for BoxClass
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
// availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview
#ifndef __ROUTETEST_H__
#define __ROUTETEST_H__

#include "src/kernel/Defs.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/Execute.h"
#include "src/kernel/box.h"
#include <iostream>

class boxTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( boxTest );
	CPPUNIT_TEST( test_init );
	CPPUNIT_TEST( testAddKey );
	CPPUNIT_TEST( verifyAddKey );
	CPPUNIT_TEST( testDeleteKey );
	CPPUNIT_TEST( testReaddKey );
	CPPUNIT_TEST( testAddDeleteKey );
	CPPUNIT_TEST( testMUT_BOX_MAX_KEY_INDEX );
	CPPUNIT_TEST( testFindKeyByKey );
	CPPUNIT_TEST( testBug1Permutation1 );
	CPPUNIT_TEST( testBug1Permutation2 );
	CPPUNIT_TEST( testHarmonic_form );
	CPPUNIT_TEST( testCycles );
	CPPUNIT_TEST_SUITE_END();

protected:
	static const int MAX_BOX = 7;
	mutabor::hidden::mutabor_box_type boxes [MAX_BOX];
//	mutabor::Route route;

public:
	boxTest() {}

	virtual ~boxTest() {}

	int countTestCases () const
	{
		return 1;
	}

	void setUp();
	void tearDown();

	void testMUT_BOX_MAX_KEY_INDEX();
	void verifyLastKey(bool force = true);
	void testAddKey();
	void verifyAddKey();
	void testDeleteKey();
	void testReaddKey();
	void checkMask();

	/** check adding and deleting of keys. As we must generate
	 *  many pages for a sufficient check, we must add a huge
	 *  number of entries.
	 */
	void testAddDeleteKey();
	void test_init();
	void testFindKeyByKey();
	void testBug1Permutation1 ();
	void testBug1Permutation2 ();
	void testHarmonic_form ();
	void testCycles ();
};

#endif

///\}
