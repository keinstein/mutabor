#ifndef __ROUTETEST_H__
#define __ROUTETEST_H__

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
};

#endif

///\}
