#ifndef __ROUTETEST_H__
#define __ROUTETEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/Execute.h"
#include <iostream>

void initialize_box(mutabor_box_type *, int);

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
	mutabor_box_type boxes [7];
//	mutabor::Route route;

public:
	boxTest()
	{
	}

	virtual ~boxTest()
	{
	}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp() 
	{ 
		for (size_t i = 0; i < 7; i++) 
			initialize_box(&boxes[i], i);
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUG
//		debugFlags::flags.kernel_box = true;
//		debugFlags::flags.midifile = true;
#endif
//		RealTime = true;
	}
  
	void tearDown()
	{ 
#ifdef DEBUG
//		debugFlags::flags.kernel_box = false;
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
	

	void verifyLastKey(bool force = true)
	{
		for (int i = 0 ; i < 7 ; i++) {
			if (!boxes[i].key_count && !force) continue;
			CPPUNIT_ASSERT(boxes[i].key_count);
			CPPUNIT_ASSERT(boxes[i].key_count <= 5 * (MUT_BOX_MAX_KEY_INDEX+1));
			CPPUNIT_ASSERT(boxes[i].last_key < 5 * (MUT_BOX_MAX_KEY_INDEX+1));
			mutabor_key_type * key = mutabor_find_key_in_box(&boxes[i], boxes[i].last_key);
			CPPUNIT_ASSERT(key && (key != NULL));
			CPPUNIT_ASSERT(key -> next == MUTABOR_NO_NEXT);
		}
	}
	

	void testAddKey()
	{
		// fill using a pattern of coprime numbers. So that we can check correct assumption about filling.
		// group theory tells us that each modulus by division by MUT_BOX_MAX_KEY_INDEX+1 is contained an equal number of times.
		
		for (size_t i = 0 ; i < 7 * (MUT_BOX_MAX_KEY_INDEX+1) * 5; i++) {
			int box = i % 7;
			int keyidx = (i*5);
			size_t last = boxes[box].last_key;
			CPPUNIT_ASSERT( i >= 7 || last == 0);
			CPPUNIT_ASSERT(boxes[box].key_count == (i/7));
			mutabor_key_type * key = mutabor_create_key_in_box(&boxes[box]);
			CPPUNIT_ASSERT(key!=NULL);
			key->number = keyidx;
			key->id = i/7;
			CPPUNIT_ASSERT(boxes[box].key_count == (i/7) + 1);
			CPPUNIT_ASSERT( i >= 7 || last == 0);
			CPPUNIT_ASSERT(last != boxes[box].last_key || i < 7); // first row always returns 0 as well as empty box
			CPPUNIT_ASSERT(boxes[box].last_key == (i/7));
//			std::clog << i << std::endl;
			verifyLastKey(i >= 6); // i < 6 as last iteration fulfils the condition
		}
//		std::clog << "7 * (MUT_BOX_MAX_KEY_INDEX+1) * 5 = 7 * (" << MUT_BOX_MAX_KEY_INDEX << " + 1) * 5 = " 
//			  << 7 * (MUT_BOX_MAX_KEY_INDEX+1) * 5 << std::endl;

	}

	void verifyAddKey()
	{
		testAddKey();
		// checking
		for (size_t i = 0 ; i < 7 ; i++) {
			int mask[MUT_BOX_MAX_KEY_INDEX+1];
			for (size_t j = 0 ; j <= MUT_BOX_MAX_KEY_INDEX; j++) mask[j] = 0;
			size_t k = 0; 
			for (size_t j = 0 ; j < 5; j++) {
				size_t next_k = k + MUT_BOX_MAX_KEY_INDEX+1;
				for (; k< next_k ; k ++) {
					mutabor_key_type * key = mutabor_find_key_in_box(&boxes[i], k);
					CPPUNIT_ASSERT(key != NULL);
					mask[key->number % (MUT_BOX_MAX_KEY_INDEX+1)]++;
					CPPUNIT_ASSERT(key->id == k);
				}
			}
			for (size_t l  = 0  ;  l <= MUT_BOX_MAX_KEY_INDEX ; l++) {
				CPPUNIT_ASSERT(mask[l] == 5);
			}
		}
		verifyLastKey();
	}

	void testDeleteKey() 
	{
		verifyAddKey();
		// punch holes at every 5th point. That should hit every elemet that is divisible by 5
//		std::clog << "punch holes at every 5th point. That should hit every elemet that is divisible by 5" << std::endl;
		for (size_t i = 1 ; i <= MUT_BOX_MAX_KEY_INDEX+1; i++) {
			size_t last = boxes[0].last_key; // mix pointer and array to test the test
#if 0
			std::clog << i << ": "
				  << "-= " << ((5*i-1) % (MUT_BOX_MAX_KEY_INDEX+1) ) 
				  << " l=" << last
				  << std::flush;
#endif
			mutabor_delete_key_in_box(boxes, (5*i-1)  );
//			std::clog << "|" << std::endl;
			if (i != MUT_BOX_MAX_KEY_INDEX+1) 
				CPPUNIT_ASSERT(last == boxes[0].last_key);
			else 
				CPPUNIT_ASSERT(last != boxes[0].last_key);
			verifyLastKey();
		}
	}

	void testReaddKey() 
	{
		testDeleteKey();
//		std::clog << "testReaddkey" << std::endl;
		checkMask();
//		std::clog << "fill the gaps with 0 ... " << MUT_BOX_MAX_KEY_INDEX << std::endl;
		// fill the gaps with 0 ... MUT_BOX_MAX_KEY_INDEX
		for (size_t i = 0 ; i <= MUT_BOX_MAX_KEY_INDEX; i++) {
			mutabor_key_type * key = mutabor_create_key_in_box(&boxes[0]);
#if 0
			DEBUGLOG(kernel_box,_T("(%d,%d,%d) -> (%d,%d)"),
				 key->number,
				 key->number % (MUT_BOX_MAX_KEY_INDEX+1), 
				 key->id, i,i*5);
#endif
			key->number = i;
			key->id = i*5;
//			DEBUGLOG2(kernel_box,_T("%d == %d?"),boxes[0].last_key, (i+1)*5-1);
			CPPUNIT_ASSERT(boxes[0].last_key == (i+1)*5-1);
			verifyLastKey();
		}		
	}


	void checkMask()
	{
		int mask[MUT_BOX_MAX_KEY_INDEX+1];
		for (size_t j = 0 ; j <= MUT_BOX_MAX_KEY_INDEX; j++) mask[j] = 0;
		for (size_t j = 0 ; j < 5* (MUT_BOX_MAX_KEY_INDEX+1); j++) {
			mutabor_key_type * key = mutabor_find_key_in_box(boxes, j);
			CPPUNIT_ASSERT(key != NULL);
//			DEBUGLOG(kernel_box,_T("[%d, %d]"),key->number,key->number % (MUT_BOX_MAX_KEY_INDEX+1));
			mask[key->number % (MUT_BOX_MAX_KEY_INDEX+1)]++;
		}
			
		for (size_t l  = 0  ;  l <= MUT_BOX_MAX_KEY_INDEX ; l++) {
//			DEBUGLOG2(kernel_box,_T("mask[%d] = %d  == %d?"),l,mask[l],(l % 5 ? 6 : 1));
			CPPUNIT_ASSERT(mask[l] == (l % 5 ? 5 : 5));
		}
		
	}

	/* check adding and deleting of keys. As we must generate many pages for a sufficient check, we must add a huge number 
	   of entries.
	*/
	void testAddDeleteKey() 
	{
		testReaddKey();
		CPPUNIT_ASSERT(boxes[0].key_count == 5*(MUT_BOX_MAX_KEY_INDEX+1));
//		std::clog << "checking again" << std::endl;
		// checking again
		checkMask();
	}


	void test_init()
	{
		initialize_boxes();
		for (int i = 0 ; i< MAX_BOX ; i++) {
			CPPUNIT_ASSERT(mut_box[i].id == i);
			CPPUNIT_ASSERT(!mut_box[i].next_used);
			CPPUNIT_ASSERT(mut_box[i].userdata == NULL);
			CPPUNIT_ASSERT(mut_box[i].current_keys.next == NULL);
			for (int j = 0; j <= MUT_BOX_MAX_KEY_INDEX; j++) {
				CPPUNIT_ASSERT(mut_box[i].current_keys.key[j].number == 0);
				CPPUNIT_ASSERT(mut_box[i].current_keys.key[j].channel == 0);
				CPPUNIT_ASSERT(mut_box[i].current_keys.key[j].id == 0);
				CPPUNIT_ASSERT(mut_box[i].current_keys.key[j].userdata == NULL);
				CPPUNIT_ASSERT(mut_box[i].current_keys.key[j].next == MUTABOR_NO_NEXT);
			}
			CPPUNIT_ASSERT(mut_box[i].key_count == 0);
			CPPUNIT_ASSERT(mut_box[i].last_key == 0);
			CPPUNIT_ASSERT(mut_box[i].distance == 0);
			CPPUNIT_ASSERT(mut_box[i].anchor == 0);
			CPPUNIT_ASSERT(mut_box[i].anchor_node.value_field == &mut_box[i].anchor);
			CPPUNIT_ASSERT(mut_box[i].anchor_node.next == NULL);
			CPPUNIT_ASSERT(mut_box[i].distance_node.value_field == &mut_box[i].distance);
			CPPUNIT_ASSERT(mut_box[i].distance_node.next == &mut_box[i].anchor_node);
			CPPUNIT_ASSERT(mut_box[i].start_parameter_list = &mut_box[i].distance_node);
			for (int j = 0 ; j < MUTABOR_KEYRANGE_MAX_WIDTH; j++) {
				CPPUNIT_ASSERT(mut_box[i].pattern.tonigkeit[j] == 0);
			}
			CPPUNIT_ASSERT(mut_box[i].tonesystem == NULL);
			CPPUNIT_ASSERT(mut_box[i].last_tonesystem.anker == 0);
			CPPUNIT_ASSERT(mut_box[i].last_tonesystem.breite == 0);
			CPPUNIT_ASSERT(mut_box[i].last_tonesystem.periode == 0);
			for (int j = 0 ; j < MUTABOR_KEYRANGE_MAX_WIDTH; j++) {
				CPPUNIT_ASSERT(mut_box[i].last_tonesystem.ton[j] == 0);
			}
			CPPUNIT_ASSERT(mut_box[i].first_harmony == NULL);
			CPPUNIT_ASSERT(mut_box[i].last_global_harmony == NULL);
			CPPUNIT_ASSERT(mut_box[i].first_keyboard == NULL);
			CPPUNIT_ASSERT(mut_box[i].last_global_harmony == NULL);
			CPPUNIT_ASSERT(mut_box[i].first_midi == NULL);
			CPPUNIT_ASSERT(mut_box[i].last_global_midi == NULL);
			CPPUNIT_ASSERT(mut_box[i].cache_konstanten == NULL);
			CPPUNIT_ASSERT(!(mut_box[i].used));
			CPPUNIT_ASSERT(!(mut_box[i].keys_changed));
			CPPUNIT_ASSERT(!(mut_box[i].logic_changed));
			CPPUNIT_ASSERT(!(mut_box[i].action_changed));
			CPPUNIT_ASSERT(!(mut_box[i].tonesys_changed));
		}
	}

	void testFindKeyByKey()
	{
		mutabor_box_type * box = &boxes[0];
		AddKey (box,77,1,5,NULL);
		AddKey (box,78,3,5,NULL);
		AddKey (box,74,5,5,NULL);
		AddKey (box,95,8,5,NULL);
		AddKey (box,-2,1,5,NULL);
		AddKey (box,77,1,6,NULL);
		size_t index = mutabor_find_key_in_box_by_key(box,77,0);
		CPPUNIT_ASSERT(index == 0);
		mutabor_key_type * key = mutabor_find_key_in_box(box,index);
		CPPUNIT_ASSERT(key->number == 77);
		CPPUNIT_ASSERT(key != NULL);
		CPPUNIT_ASSERT(key->id == 1);
		CPPUNIT_ASSERT(key->channel == 5);
		index = mutabor_find_key_in_box_by_key(box,77,key->next);
		CPPUNIT_ASSERT(index == 5);
		key = mutabor_find_key_in_box(box,index);
		CPPUNIT_ASSERT(key != NULL);
		CPPUNIT_ASSERT(key->number == 77);
		CPPUNIT_ASSERT(key->id == 1);
		CPPUNIT_ASSERT(key->channel == 6);
		CPPUNIT_ASSERT(key->next == MUTABOR_NO_NEXT);
		mutabor_delete_key_in_box(box,0);
		key = mutabor_find_key_in_box(box,0);
		CPPUNIT_ASSERT(key != NULL);
		CPPUNIT_ASSERT(key->number == 78);
		CPPUNIT_ASSERT(key->id == 3);
		CPPUNIT_ASSERT(key->channel == 5);
		CPPUNIT_ASSERT(key->next == 2);
		/* check deleting key 0: 2 cases either with following keys or without, so we must empty all keys */
		while ((key = mutabor_find_key_in_box(box,0)) != NULL) {
			mutASSERT(box->key_count > 0);
			size_t count = 0; 
			for (mutabor_key_type * key2 = key; 
			     key2 != NULL; 
			     key2 = mutabor_find_key_in_box(box,key2->next))
				     count ++;
			     mutASSERT(box->key_count == count);
			mutabor_delete_key_in_box(box,0);
		}
		mutASSERT(box->key_count == 0);
	}

	void testBug1Permutation1 () {
		mutabor_box_type * box = &boxes[0];
		AddKey (box,77,1,5,NULL);
		AddKey (box,78,3,5,NULL);
		AddKey (box,74,5,5,NULL);
		size_t index = mutabor_find_key_in_box_by_key(box,78,0);
		CPPUNIT_ASSERT(index != MUTABOR_NO_NEXT);
		mutabor_delete_key_in_box(box,index);
		index = mutabor_find_key_in_box_by_key(box,78,0);
		CPPUNIT_ASSERT(index == MUTABOR_NO_NEXT);

		index = mutabor_find_key_in_box_by_key(box,74,0);
		CPPUNIT_ASSERT(index != MUTABOR_NO_NEXT);
		mutabor_delete_key_in_box(box,index);
		index = mutabor_find_key_in_box_by_key(box,74,0);
		CPPUNIT_ASSERT(index == MUTABOR_NO_NEXT);

		index = mutabor_find_key_in_box_by_key(box,77,0);
		CPPUNIT_ASSERT(index != MUTABOR_NO_NEXT);
		mutabor_delete_key_in_box(box,index);
		index = mutabor_find_key_in_box_by_key(box,77,0);
		CPPUNIT_ASSERT(index == MUTABOR_NO_NEXT);

		index = mutabor_find_key_in_box_by_key(box,78,0);
		CPPUNIT_ASSERT(index == MUTABOR_NO_NEXT);
		index = mutabor_find_key_in_box_by_key(box,74,0);
		CPPUNIT_ASSERT(index == MUTABOR_NO_NEXT);
		index = mutabor_find_key_in_box_by_key(box,77,0);
		CPPUNIT_ASSERT(index == MUTABOR_NO_NEXT);

		CPPUNIT_ASSERT(box->key_count == 0);
	}


	void testBug1Permutation2 () {
		mutabor_box_type * box = &boxes[0];
		/* second try (check all permutations) */
		/* deleting first 77 */
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,77,1,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,78,3,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 1);
		AddKey (box,74,5,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,77,1,5);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,78,3,5);
		CPPUNIT_ASSERT(box->last_key == 0);
		DeleteKey (box,74,5,5);
		CPPUNIT_ASSERT(box->last_key == 0);

		AddKey (box,77,1,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,78,3,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 1);
		AddKey (box,74,5,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,77,1,5);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,74,5,5);
		CPPUNIT_ASSERT(box->last_key == 0);
		DeleteKey (box,78,3,5);
		CPPUNIT_ASSERT(box->last_key == 0);

		/* 78 deleted first */
		AddKey (box,77,1,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,78,3,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 1);
		AddKey (box,74,5,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,78,3,5);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,77,1,5);
		CPPUNIT_ASSERT(box->last_key == 0);
		DeleteKey (box,74,5,5);
		CPPUNIT_ASSERT(box->last_key == 0);

		AddKey (box,77,1,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,78,3,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 1);
		AddKey (box,74,5,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,78,3,5);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,74,5,5);
		CPPUNIT_ASSERT(box->last_key == 0);
		DeleteKey (box,77,1,5);
		CPPUNIT_ASSERT(box->last_key == 0);

		/* 74 deleted first */
		AddKey (box,77,1,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,78,3,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 1);
		AddKey (box,74,5,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,74,5,5);
		CPPUNIT_ASSERT(box->last_key == 1);
		DeleteKey (box,77,1,5);
		CPPUNIT_ASSERT(box->last_key == 0);
		DeleteKey (box,78,3,5);
		CPPUNIT_ASSERT(box->last_key == 0);

		AddKey (box,77,1,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 0);
		AddKey (box,78,3,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 1);
		AddKey (box,74,5,5,NULL);
		CPPUNIT_ASSERT(box->last_key == 2);
		DeleteKey (box,74,5,5);
		CPPUNIT_ASSERT(box->last_key == 1);
		DeleteKey (box,78,3,5);
		CPPUNIT_ASSERT(box->last_key == 0);
		DeleteKey (box,77,1,5);
		CPPUNIT_ASSERT(box->last_key == 0);
	}
};

#endif
