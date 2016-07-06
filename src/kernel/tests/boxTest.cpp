/** \file               -*- C++ -*-
 ********************************************************************
 * Testsuite for BoxClass
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
#include "src/kernel/Defs.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include "src/kernel/box.h"
#ifdef DEBUG
#define YYDEBUG 1
namespace mutabor {
	namespace hidden {
		extern "C" {
#include "src/kernel/mut.hh"
		}
	}
}
#endif
#include "src/kernel/tests/boxTest.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/Execute.h"
#include "src/kernel/TabGen.h"
#include "src/kernel/Parser.h"
#include "src/kernel/Hilfs.h"
#include <iostream>

using namespace mutabor;
using namespace mutabor::hidden;

/* const int boxTest::MAX_BOX  = 7 ; */

void boxTest::setUp()
{
#ifdef DEBUG
	//		debugFlags::flags.kernel_box = true;
	//		debugFlags::flags.midifile = true;
#endif
	for (size_t i = 0; i < 7; i++)
		mutabor_initialize_box(&boxes[i], i);
	// change DEBUGA to DEBUG in case you need the debug output
	//		RealTime = true;
}

void boxTest::tearDown()
{
	for (size_t i = 0; i < 7; i++)
		mutabor_clear_box(&boxes[i]);
#ifdef DEBUG
	//		debugFlags::flags.kernel_box = false;
	//		debugFlags::flags.midifile = false;
#endif
	//		in = NULL;
}

void boxTest::testMUT_BOX_MAX_KEY_INDEX()
{
	int i = MUT_BOX_MAX_KEY_INDEX + 1;
	while (!(i & 1))  i = i >> 1;
	CPPUNIT_ASSERT(i == 1);
}


void boxTest::verifyLastKey(bool force)
{
	for (int i = 0 ; i < MAX_BOX ; i++) {
		if (!boxes[i].key_count && !force) continue;
		CPPUNIT_ASSERT(boxes[i].key_count);
		CPPUNIT_ASSERT(boxes[i].key_count <= 5 * (MUT_BOX_MAX_KEY_INDEX+1));
		CPPUNIT_ASSERT(boxes[i].last_key < 5 * (MUT_BOX_MAX_KEY_INDEX+1));
		mutabor_note_type * note = mutabor_find_key_in_box(&boxes[i], boxes[i].last_key);
		CPPUNIT_ASSERT(note && (note != NULL));
		CPPUNIT_ASSERT(note -> next == MUTABOR_NO_NEXT);
	}
}


void boxTest::testAddKey()
{
	// fill using a pattern of coprime numbers. So that we can check correct assumption about filling.
	// group theory tells us that each modulus by division by MUT_BOX_MAX_KEY_INDEX+1 is contained an equal number of times.

	for (size_t i = 0 ; i < 7 * (MUT_BOX_MAX_KEY_INDEX+1) * 5; i++) {
		int box = i % 7;
		int noteidx = (i*5);
		size_t last = boxes[box].last_key;
		CPPUNIT_ASSERT( i >= 7 || last == 0);
		CPPUNIT_ASSERT(boxes[box].key_count == (i/7));
		mutabor_note_type * note = mutabor_create_key_in_box(&boxes[box]);
		CPPUNIT_ASSERT(note!=NULL);
		note->number = noteidx;
		note->id = i/7;
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

void boxTest::verifyAddKey()
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
				mutabor_note_type * note = mutabor_find_key_in_box(&boxes[i], k);
				CPPUNIT_ASSERT(note != NULL);
				mask[note->number % (MUT_BOX_MAX_KEY_INDEX+1)]++;
				CPPUNIT_ASSERT(note->id == k);
			}
		}
		for (size_t l  = 0  ;  l <= MUT_BOX_MAX_KEY_INDEX ; l++) {
			CPPUNIT_ASSERT(mask[l] == 5);
		}
	}
	verifyLastKey();
}

void boxTest::testDeleteKey()
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

void boxTest::testReaddKey()
{
	testDeleteKey();
	//		std::clog << "testReaddkey" << std::endl;
	checkMask();
	//		std::clog << "fill the gaps with 0 ... " << MUT_BOX_MAX_KEY_INDEX << std::endl;
	// fill the gaps with 0 ... MUT_BOX_MAX_KEY_INDEX
	for (size_t i = 0 ; i <= MUT_BOX_MAX_KEY_INDEX; i++) {
		mutabor_note_type * note = mutabor_create_key_in_box(&boxes[0]);
#if 0
		DEBUGLOG(kernel_box,_T("(%d,%d,%d) -> (%d,%d)"),
			 note->number,
			 note->number % (MUT_BOX_MAX_KEY_INDEX+1),
			 note->id, i,i*5);
#endif
		note->number = i;
		note->id = i*5;
		//			DEBUGLOG2(kernel_box,_T("%d == %d?"),boxes[0].last_key, (i+1)*5-1);
		CPPUNIT_ASSERT(boxes[0].last_key == (i+1)*5-1);
		verifyLastKey();
	}
}


void boxTest::checkMask()
{
	int mask[MUT_BOX_MAX_KEY_INDEX+1];
	for (size_t j = 0 ; j <= MUT_BOX_MAX_KEY_INDEX; j++) mask[j] = 0;
	for (size_t j = 0 ; j < 5* (MUT_BOX_MAX_KEY_INDEX+1); j++) {
		mutabor_note_type * note = mutabor_find_key_in_box(boxes, j);
		CPPUNIT_ASSERT(note != NULL);
		//			DEBUGLOG(kernel_box,_T("[%d, %d]"),key->number,key->number % (MUT_BOX_MAX_KEY_INDEX+1));
		mask[note->number % (MUT_BOX_MAX_KEY_INDEX+1)]++;
	}

	for (size_t l  = 0  ;  l <= MUT_BOX_MAX_KEY_INDEX ; l++) {
		//			DEBUGLOG2(kernel_box,_T("mask[%d] = %d  == %d?"),l,mask[l],(l % 5 ? 6 : 1));
		CPPUNIT_ASSERT(mask[l] == (l % 5 ? 5 : 5));
	}

}

/* check adding and deleting of keys. As we must generate many pages for a sufficient check, we must add a huge number
   of entries.
*/
void boxTest::testAddDeleteKey()
{
	testReaddKey();
	CPPUNIT_ASSERT(boxes[0].key_count == 5*(MUT_BOX_MAX_KEY_INDEX+1));
	//		std::clog << "checking again" << std::endl;
	// checking again
	checkMask();
}


void boxTest::test_init()
{
	for (int i = 0 ; i < 7 ; i++) {
		CPPUNIT_ASSERT(boxes[i].id == i);
		//		CPPUNIT_ASSERT(!boxes[i].next_used);
		CPPUNIT_ASSERT(boxes[i].userdata == NULL);
		CPPUNIT_ASSERT(boxes[i].current_keys.next == NULL);
		for (int j = 0; j <= MUT_BOX_MAX_KEY_INDEX; j++) {
			CPPUNIT_ASSERT(boxes[i].current_keys.key[j].number == 0);
			CPPUNIT_ASSERT(boxes[i].current_keys.key[j].channel == 0);
			CPPUNIT_ASSERT(boxes[i].current_keys.key[j].id == 0);
			CPPUNIT_ASSERT(boxes[i].current_keys.key[j].userdata == NULL);
			CPPUNIT_ASSERT(boxes[i].current_keys.key[j].next == MUTABOR_NO_NEXT);
		}
		CPPUNIT_ASSERT(boxes[i].key_count == 0);
		CPPUNIT_ASSERT(boxes[i].last_key == 0);
		CPPUNIT_ASSERT(boxes[i].distance == 0);
  	        CPPUNIT_ASSERT(boxes[i].current_parameters == NULL);
  	        CPPUNIT_ASSERT(boxes[i].parameters == NULL);
  	        CPPUNIT_ASSERT(boxes[i].current_logic == NULL);

		for (int j = 0 ; j < MUTABOR_KEYRANGE_MAX_WIDTH; j++) {
			CPPUNIT_ASSERT(boxes[i].pattern.tonigkeit[j] == 0);
		}
		CPPUNIT_ASSERT(boxes[i].tonesystem == boxes[i].tonesystem_memory);
		for (int j = 0 ; j < 2 ; j++) {
			CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].anker == 60);
			CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].breite == 1);
			CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].periode.active
				       == hidden::mutabor_active_interval);
			CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].periode.value == 1 << 24);
			CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].ton[0].active
				       == hidden::mutabor_active_tone);
			CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].ton[0].value == 60 << 24);
			for (int k = 1 ; k < MUTABOR_KEYRANGE_MAX_WIDTH ; k++) {
				CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].ton[k].value == 0);
				CPPUNIT_ASSERT(boxes[i].tonesystem_memory[j].ton[k].active
					       == hidden::mutabor_invalid_tone);
			}
		}
		CPPUNIT_ASSERT(boxes[i].last_tonesystem.anker == 60);
		CPPUNIT_ASSERT(boxes[i].last_tonesystem.breite == 1);
		CPPUNIT_ASSERT(boxes[i].last_tonesystem.periode.active
			       == hidden::mutabor_active_interval);
		CPPUNIT_ASSERT(boxes[i].last_tonesystem.periode.value == 1 << 24);
		CPPUNIT_ASSERT(boxes[i].last_tonesystem.ton[0].active
			       == hidden::mutabor_active_tone);
		CPPUNIT_ASSERT(boxes[i].last_tonesystem.ton[0].value == 60 << 24);
		for (int j = 1 ; j < MUTABOR_KEYRANGE_MAX_WIDTH; j++) {
			CPPUNIT_ASSERT(boxes[i].last_tonesystem.ton[j].value == 0);
			CPPUNIT_ASSERT(boxes[i].last_tonesystem.ton[j].active
				       == hidden::mutabor_invalid_tone);
		}
#if 0
		CPPUNIT_ASSERT(boxes[i].first_harmony == NULL);
		CPPUNIT_ASSERT(boxes[i].last_global_harmony == NULL);
		CPPUNIT_ASSERT(boxes[i].first_local_harmony == NULL);
		CPPUNIT_ASSERT(boxes[i].first_keyboard == NULL);
		CPPUNIT_ASSERT(boxes[i].last_global_keyboard == NULL);
		CPPUNIT_ASSERT(boxes[i].first_local_keyboard == NULL);
		CPPUNIT_ASSERT(boxes[i].first_midi == NULL);
		CPPUNIT_ASSERT(boxes[i].last_global_midi == NULL);
		CPPUNIT_ASSERT(boxes[i].first_local_midi == NULL);
#endif
		CPPUNIT_ASSERT(boxes[i].runtime_heap == NULL);
		CPPUNIT_ASSERT(boxes[i].scanner == NULL);
		CPPUNIT_ASSERT(boxes[i].file == NULL);
#if 0
#warning the following fields should be superfluous, now
		CPPUNIT_ASSERT(!(boxes[i].used));
		CPPUNIT_ASSERT(!(boxes[i].keys_changed));
		CPPUNIT_ASSERT(!(boxes[i].logic_changed));
		CPPUNIT_ASSERT(!(boxes[i].action_changed));
		CPPUNIT_ASSERT(!(boxes[i].tonesys_changed));
#endif
		CPPUNIT_ASSERT(!(boxes[i].flags.local_harmony_before_global));
		CPPUNIT_ASSERT(!(boxes[i].flags.local_keyboard_before_global));
		CPPUNIT_ASSERT(!(boxes[i].flags.local_midi_before_global));
		CPPUNIT_ASSERT(!(boxes[i].flags.break_logic));
		CPPUNIT_ASSERT(!(boxes[i].flags.auto_reset_break_logic));
	}
}

void boxTest::testFindKeyByKey()
{
	mutabor_box_type * box = &boxes[0];
	loesche_syntax_speicher(box);
	mutabor_programm_einlesen(box,"");
	mutabor_clear_box_scanner(box);
	expand_decition_tree(box);
	AddKey (box,77,1,5,NULL);
	AddKey (box,78,3,5,NULL);
	AddKey (box,74,5,5,NULL);
	AddKey (box,95,8,5,NULL);
	AddKey (box,-2,1,5,NULL);
	AddKey (box,77,1,6,NULL);
	size_t index = mutabor_find_key_in_box_by_key(box,77,0);
	CPPUNIT_ASSERT(index == 0);
	mutabor_note_type * note = mutabor_find_key_in_box(box,index);
	CPPUNIT_ASSERT(note->number == 77);
	CPPUNIT_ASSERT(note != NULL);
	CPPUNIT_ASSERT(note->id == 1);
	CPPUNIT_ASSERT(note->channel == 5);
	index = mutabor_find_key_in_box_by_key(box,77,note->next);
	CPPUNIT_ASSERT(index == 5);
	note = mutabor_find_key_in_box(box,index);
	CPPUNIT_ASSERT(note != NULL);
	CPPUNIT_ASSERT(note->number == 77);
	CPPUNIT_ASSERT(note->id == 1);
	CPPUNIT_ASSERT(note->channel == 6);
	CPPUNIT_ASSERT(note->next == MUTABOR_NO_NEXT);
	mutabor_delete_key_in_box(box,0);
	note = mutabor_find_key_in_box(box,0);
	CPPUNIT_ASSERT(note != NULL);
	CPPUNIT_ASSERT(note->number == 78);
	CPPUNIT_ASSERT(note->id == 3);
	CPPUNIT_ASSERT(note->channel == 5);
	CPPUNIT_ASSERT(note->next == 2);
	/* check deleting note 0: 2 cases either with following notes or without, so we must empty all notes */
	while ((note = mutabor_find_key_in_box(box,0)) != NULL) {
		mutASSERT(box->key_count > 0);
		size_t count = 0;
		for (mutabor_note_type * note2 = note;
		     note2 != NULL;
		     note2 = mutabor_find_key_in_box(box,note2->next))
			count ++;
		mutASSERT(box->key_count == count);
		mutabor_delete_key_in_box(box,0);
	}
	mutASSERT(box->key_count == 0);
	mutabor_clear_box(box);
}

void boxTest::testBug1Permutation1 () {
	mutabor_box_type * box = &boxes[0];
	loesche_syntax_speicher(box);
	mutabor_programm_einlesen(box,"");
	mutabor_clear_box_scanner(box);
	expand_decition_tree(box);

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
	mutabor_clear_box(box);
}


void boxTest::testBug1Permutation2 () {
	mutabor_box_type * box = &boxes[0];

	loesche_syntax_speicher(box);
	mutabor_programm_einlesen(box,"");
	mutabor_clear_box_scanner(box);
	expand_decition_tree(box);
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
	mutabor_clear_box(box);
}


void boxTest::testHarmonic_form () {
	mutabor_box_type * box = &boxes[0];
#ifdef DEBUG
	yydebug = 0;
#endif
	const char * logic_string = "\
harmony\n\
    major = { 0, 4, 7, *10 }\n\
\n\
retuning \n\
	tune (testparam) =\n\
              	@+testparam []\n\
logic\n\
    harmony1logic form major =  tune (0) [ \n\
        form  4 ~ major         -> tune(1)\n\
        form      major ~  7    -> tune(2)\n\
        form  7 ~ major ~ 10    -> tune(3)\n\
        form  7 ~ major ~  2    -> tune(4)\n\
        form 61 ~ major         -> tune(5)\n\
        form      major ~ 80    -> tune(6)\n\
        form 60 ~ major ~ 79    -> tune(7)\n\
\n\
              0 ~ major         -> tune(11)\n\
                  major ~  4    -> tune(12)\n\
              7 ~ major ~ 10    -> tune(13)\n\
              7 ~ major ~  2    -> tune(14)\n\
             61 ~ major         -> tune(15)\n\
                  major ~ 80    -> tune(16)\n\
             60 ~ major ~ 79    -> tune(17)\n\
        ] \n\
";


	loesche_syntax_speicher(box);
	mutabor_programm_einlesen(box,logic_string);
	mutabor_clear_box_scanner(box);
	expand_decition_tree(box);

	CPPUNIT_ASSERT(box);
	CPPUNIT_ASSERT(box->file);
	std::cout << std::endl << "Refcount: " << box->file->refcount << std::endl;
	CPPUNIT_ASSERT(box->file->refcount == 1);
	struct harmonie_ereignis * current_harmony
		= box->file->global_harmonies;
	CPPUNIT_ASSERT(current_harmony);
	CPPUNIT_ASSERT(current_harmony -> pattern);
	int pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> vortaste == 0);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 0);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor::hidden::mutabor_harmony_nokey);
	struct do_aktion * action = current_harmony->aktion;
	CPPUNIT_ASSERT(!current_harmony->next);
	CPPUNIT_ASSERT(action);
	CPPUNIT_ASSERT(action->aufruf_typ == aufruf_logik);
	CPPUNIT_ASSERT(!action->arguments);
	CPPUNIT_ASSERT(action->calling.logic);
	struct logik * the_logic = current_harmony->aktion->calling.logic;
	CPPUNIT_ASSERT(the_logic);
	CPPUNIT_ASSERT(current_harmony->the_logik_to_expand == the_logic);
	CPPUNIT_ASSERT(!strcmp(the_logic->name,"harmony1logic"));
	CPPUNIT_ASSERT(the_logic->ausloeser);
	action = the_logic -> einstimmung;
	CPPUNIT_ASSERT(action);
	CPPUNIT_ASSERT(!strcmp(action -> name,"tune") );
	CPPUNIT_ASSERT(action -> aufruf_typ == aufruf_umst_taste_rel);
	CPPUNIT_ASSERT(action -> arguments);
	CPPUNIT_ASSERT(action -> arguments -> size == 1);
	CPPUNIT_ASSERT(action -> arguments -> types);
	CPPUNIT_ASSERT(action -> arguments -> types[0] == mutabor_argument_integer);
	CPPUNIT_ASSERT(action -> arguments -> data);
	CPPUNIT_ASSERT(action -> arguments -> data[0].constant == 0);

	ausloeser * trigger = the_logic->ausloeser;
	CPPUNIT_ASSERT(trigger -> u.ausloeser_harmonie_form.type == mutabor_harmony_nokey);
	CPPUNIT_ASSERT(!strcmp(trigger -> u.ausloeser_harmonie_form.name, "major"));
	current_harmony = the_logic->harmony_list;
	CPPUNIT_ASSERT(current_harmony);
	CPPUNIT_ASSERT(current_harmony -> pattern);
	// pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> ist_harmonieform == mutabor_is_harmonic_form);
	CPPUNIT_ASSERT(current_harmony -> vortaste == 4);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 0);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor_harmony_prekey);

	CPPUNIT_ASSERT((current_harmony = current_harmony->next)); //next
	CPPUNIT_ASSERT(current_harmony -> pattern);
	// pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> ist_harmonieform == mutabor_is_harmonic_form);
	CPPUNIT_ASSERT(current_harmony -> vortaste == 0);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 7);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor_harmony_postkey);


	CPPUNIT_ASSERT((current_harmony = current_harmony->next)); //next
	CPPUNIT_ASSERT(current_harmony -> pattern);
	// pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> ist_harmonieform == mutabor_is_harmonic_form);
	CPPUNIT_ASSERT(current_harmony -> vortaste == 7);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 10);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor_harmony_bothkey);

	CPPUNIT_ASSERT((current_harmony = current_harmony->next)); //next
	CPPUNIT_ASSERT(current_harmony -> pattern);
	// pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> ist_harmonieform == mutabor_is_no_harmonic_form);
	CPPUNIT_ASSERT(current_harmony -> vortaste == 0);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 0);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor_harmony_prekey);

	CPPUNIT_ASSERT((current_harmony = current_harmony->next)); //next
	CPPUNIT_ASSERT(current_harmony -> pattern);
	// pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> ist_harmonieform == mutabor_is_no_harmonic_form);
	CPPUNIT_ASSERT(current_harmony -> vortaste == 0);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 4);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor_harmony_postkey);

	CPPUNIT_ASSERT((current_harmony = current_harmony->next)); //next
	CPPUNIT_ASSERT(current_harmony -> pattern);
	// pattern[] = { 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 0, 1};
	for (int i = 0 ; i < 12 ; i++) {
		CPPUNIT_ASSERT(pattern[i] ==
			       current_harmony -> pattern->tonigkeit[i]);
	}
	CPPUNIT_ASSERT(current_harmony -> ist_harmonieform == mutabor_is_no_harmonic_form);
	CPPUNIT_ASSERT(current_harmony -> vortaste == 7);
	CPPUNIT_ASSERT(current_harmony -> nachtaste == 10);
	CPPUNIT_ASSERT(current_harmony -> type == mutabor_harmony_bothkey);
	CPPUNIT_ASSERT(!current_harmony -> next);

	CPPUNIT_ASSERT(box->key_count == 0);
	CPPUNIT_ASSERT(box->file->refcount == 1);
	mutabor_clear_box(box);
}



void boxTest::testCycles () {
	mutabor_box_type * box = &boxes[0];
#ifdef DEBUG
	yydebug = 0;
	mutabor_debug_flags.kernel_parser = true;
#endif
	const char * logic_string = "\
INTERVAL\n\
	a = a\n\
TONE\n\
	b = b\n\
\n\
TONESYSTEM\n\
	t = 60 [ b ] a\n\
\n\
RETUNING\n\
	r1 = { r1, l1 }\n\
	r2 = { l1 }\n\
\n\
LOGIC \n\
	l1 KEY l = r1 [\n\
	KEY R -> r2\n\
	]\n\
";


	loesche_syntax_speicher(box);
	mutabor_programm_einlesen(box,logic_string);
	mutabor_clear_box_scanner(box);
	CPPUNIT_ASSERT(box->file);
	CPPUNIT_ASSERT(box->file->list_of_intervalle);
	CPPUNIT_ASSERT(box->file->list_of_toene);
	CPPUNIT_ASSERT(box->file->list_of_tonsysteme);
	CPPUNIT_ASSERT(box->file->list_of_umstimmungen);
	CPPUNIT_ASSERT(box->file->list_of_umstimmungen->next);
	CPPUNIT_ASSERT(!box->file->list_of_harmonien);
	CPPUNIT_ASSERT(box->file->list_of_logiken);
	CPPUNIT_ASSERT(box->file->list_of_instrumente);
	CPPUNIT_ASSERT(!box->file->list_of_config_instrumente);
	CPPUNIT_ASSERT(box->file->ton_ohne_namen);
	CPPUNIT_ASSERT(box->file->ton_liste);
	expand_decition_tree(box);

	CPPUNIT_ASSERT(box->key_count == 0);
	mutabor_clear_box(box);
}


///\}
