#ifndef __ROUTETEST_H__
#define __ROUTETEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Route.h"
#include "src/kernel/Runtime.h"

template<class route> 
class RouteTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( RouteTest );
	CPPUNIT_TEST( testDummy );
	CPPUNIT_TEST_SUITE_END();

protected:
//	mutabor::Route route;

public:
	RouteTest()
	{
	}

	virtual ~RouteTest()
	{
	}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp() 
	{ 
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
//		debugFlags::flags.timer = true;
//		debugFlags::flags.midifile = true;
#endif
//		RealTime = true;
	}
  
	void tearDown()
	{ 
#ifdef DEBUG
//		debugFlags::flags.timer = false;
//		debugFlags::flags.midifile = false;
#endif
//		in = NULL;
	}
  
	void testDummy() 
	{ 	  
	}
};

#endif
