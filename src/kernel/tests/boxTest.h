#ifndef __ROUTETEST_H__
#define __ROUTETEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Route.h"
#include "src/kernel/Runtime.h"

class boxTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( boxTest );
	CPPUNIT_TEST( testAddDeleteKey );
	CPPUNIT_TEST( testMUT_BOX_MAX_KEY_INDEX );
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
  
	void testMUT_BOX_MAX_KEY_INDEX() 
	{
		int i = MUT_BOX_MAX_KEY_INDEX + 1;
		while (!(i & 1))  i = i >> 1;
		CPPUNIT_ASSERT(i == 1);
	}
	
	/* check adding and deleting of keys. As we must generate many pages for a sufficient check, we must add a huge number 
	   of entries.
	*/
	void testAddKey() 
	{
		mutabor_box_type boxes[7];
		
		// fill using a pattern of coprime numbers. So that we can check correct assumption about filling.
		// group theory tells us that each modulus by division by MUT_BOX_MAX_KEY_INDEX+1 is contained an equal number of times.
		
		for (size_t i = 0 ; i < 7 * (MUT_BOX_MAX_KEY_INDEX+1) * 5; i++) {
			int box = i % 7;
			int keyidx = (i*5);
			size_t last = boxes[box].last_key;
			CPPUNIT_ASSERT(boxes[box].key_count == (i/7));
			mutabor_key_type * key = mutabor_create_key_in_box(&boxes[box]);
			CPPUNIT_ASSERT(key!=NULL);
			key->number = keyidx;
			key->id = i/7;
			CPPUNIT_ASSERT(boxes[box].key_count == (i/7) + 1);
			CPPUNIT_ASSERT(last != boxes[box].last_key);
			CPPUNIT_ASSERT(boxes[box].last_key == (i/7));
		}
		// checking
		for (size_t i = 0 ; i < 7 ; i++) {
			int mask[MUT_BOX_MAX_KEY_INDEX+1];
			for (size_t j = 0 ; j <= MUT_BOX_MAX_KEY_INDEX; j++) mask[j] = 0;
			k = 0; 
			for (size_t j = 0 ; j < 5; j++) {
				size_t next_k = k + MUT_BOX_MAX_KEY_INDEX+1;
				for (; k< next_k ; k ++) {
					mutabor_key_type * key = mutabor_find_key_in_box(&boxes[i], k);
					CPPUNIT_ASSERT(key != NULL);
					mask[key->number % (MUT_BOX_MAX_KEY_INDEX+1)]++;
					CPPUNIT_ASSERT(key->id == k);
				}
				for (size_t l  = 0  ;  l <= MUT_BOX_MAX_KEY_INDEX ; l++) {
					CPPUNIT_ASSERT(mask[l] == 5);
				}
			}
		}
		// punch holes at every 5th point. That should hit every elemet that is divisible by 5
		for (size_t i = 1 ; i <= MUT_BOX_MAX_KEY_INDEX+1) {
			size_t last = boxes[0].last_key; // mix pointer and array to test the test
			mutabor_delete_key_in_box(boxes, 5*i-1);
			if (i != MUT_BOX_MAX_KEY_INDEX+1) 
				CPPUNIT_ASSERT(last == boxes[0].last_key);
			else 
				CPPUNIT_ASSERT(last != boxes[0].last_key);
		}
		// fill the gaps with 0 ... MUT_BOX_MAX_KEY_INDEX
		for (size_t i = 0 ; i <= MUT_BOX_MAX_KEY_INDEX) {
			mutabor_key_type * key = mutabor_create_key_in_box(&boxes[box]);
			key->number = i;
			key->id = 5*i;
			CPPUNIT_ASSERT(boxes[0].last_key == (i*5));
		}		
		// checking again
		{
			int mask[MUT_BOX_MAX_KEY_INDEX+1];
			for (size_t j = 0 ; j <= MUT_BOX_MAX_KEY_INDEX; j++) mask[j] = 0;
			k = 0; 
			for (size_t j = 0 ; j < 5* (MUT_BOX_MAX_KEY_INDEX+1); j++) {
				mutabor_key_type * key = mutabor_find_key_in_box(boxes, j);
				CPPUNIT_ASSERT(key != NULL);
				mask[key->number % (MUT_BOX_MAX_KEY_INDEX+1)]++;
			}
			
			for (size_t l  = 0  ;  l <= MUT_BOX_MAX_KEY_INDEX ; l++) {
				CPPUNIT_ASSERT(mask[l] == (l % 5 ? 1 : 6));
			}
		}
	}
};

#endif
