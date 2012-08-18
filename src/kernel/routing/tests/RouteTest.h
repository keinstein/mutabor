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
	CPPUNIT_TEST( testGetNextFreeBox );
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
  
	void testGetNextFreeBox() 
	{ 	  
		mutabor::Route route0 = mutabor::RouteFactory::Create();
		route0->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route0->GetBox() == 0 );
		mutabor::Route route1 = mutabor::RouteFactory::Create();
		route1->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route1->GetBox() == 1 );
		mutabor::Route route2 = mutabor::RouteFactory::Create();
		route2->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route2->GetBox() == 2 );
		mutabor::Route route3 = mutabor::RouteFactory::Create();
		route3->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route3->GetBox() == 3 );
		route1->Destroy();
		route1=NULL;
		route2->Destroy();
		route2=NULL;
		route1 = mutabor::RouteFactory::Create();
		route1->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route1->GetBox() == 1 );
		route2 = mutabor::RouteFactory::Create();
		route2->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route2->GetBox() == 2 );
		mutabor::Route route4 = mutabor::RouteFactory::Create();
		route4->SetBox(mutabor::RouteClass::GetNextFreeBox());
		CPPUNIT_ASSERT( route4->GetBox() == 4 );
		route0->Destroy();
		route1->Destroy();
		route2->Destroy();
		route3->Destroy();
		route4->Destroy();
	}
};

#endif
