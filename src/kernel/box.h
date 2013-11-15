/** \file 
 ********************************************************************
 * Description: Collect all properties, which are used by boxes
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.6 $
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
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/


/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_BOX_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_BOX_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_BOX_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Global.h"
#include "Interpre.h"
#include "Execute.h"

#ifndef MU32_BOX_H_PRECOMPILED
#define MU32_BOX_H_PRECOMPILED
#include <malloc.h>

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

// system headers which do seldom change



/** linked list containing key information for incoming keys or notes. First is always 0 last has next == 0. */
typedef struct {
	int number;
	size_t channel;
	size_t id; /**< unique Id if the input device suports it */
	void * userdata;
	size_t next;
} mutabor_note_type;

inline int mutabor_get_note_index(int note, tone_system * system) {
	if (!system) return INT_MIN;
	int retval = (note - system->anker) % system->breite;
		return retval < 0 ? retval + system->breite : retval;	
}

inline int mutabor_get_note_distance(int note, tone_system * system) {
	if (!system) return INT_MIN;
	int retval = (int)(note - (system->anker % system->breite)) / system->breite;
	retval -= ((int)system->anker  / system->breite);
	return retval;
}

inline long mutabor_get_note_frequency(int note, tone_system * system) {
	if (!system) return LONG_MIN;
	long retval = system->ton[mutabor_get_note_index(note, system)];
	if (!retval) return 0;
	return ((long)system->periode) * mutabor_get_note_distance(note,system) + retval;
}

#define MUT_BOX_MAX_KEY_INDEX_LOG (6)
#define MUT_BOX_MAX_KEY_INDEX ((1 << MUT_BOX_MAX_KEY_INDEX_LOG) - 1)
#define MUTABOR_NO_NEXT (~((size_t) 0))

typedef struct mutabor_key_index_type {
	mutabor_note_type key[1 << MUT_BOX_MAX_KEY_INDEX_LOG];
	struct mutabor_key_index_type * next;
	
} mutabor_key_index_type;

struct mutabor_scanner_data;
struct mutabor_logic_parsed;
struct mini_heap;

struct mutabor_box_flags {
	char local_harmony_before_global:1;
	char local_keyboard_before_global:1;
	char local_midi_before_global:1;
};

/** Mutabor box type. */
struct mutabor_box_type {
        int id;
//	int next_used;
	void * userdata;

	mutabor_key_index_type current_keys;
	size_t key_count;
	size_t last_key;

        /**
	 * Distance of the root of the harmony or harmonic form as it
	 * has been calculated during the last harmony analysis.
	 */
	int distance;
    
	/* parameter lists are arrays arranged in a linked list. Each
	   list element represents a maximal parameter vector. 
	   It doesn't have to be used completely. As we reuse old list elements 
	   after they became free all data vectors must have the same size.

	   Current_parameters refers to the parameters of the current call.
	   Parameters refers to the global box parameters such as distance 
	   and anchor.
	*/
	struct interpreter_parameter_list * current_parameters;  /*< currently active parameter list */
	struct interpreter_parameter_list * parameters; /*< pointer to the first parameter list */

	/** pattern structure in current box */
	PATTERNN pattern;
	

	/** tone system.  
	    we use pointers here, since this enables us
	    to quickly change the tone sytem. This saves us 
	    a copy operation.
	 */
	tone_system * tonesystem;
	tone_system tonesystem_memory[2];
	tone_system last_tonesystem;

	struct logik * current_logic;    /*< currently active logic */
	struct any_trigger last_trigger; /*< last trigger that has been matched */

#if 0
	/* Certain linked lists for events, 
	 either obsolete or moved to current_logic or file */
	struct harmonie_ereignis *  first_harmony;
	struct harmonie_ereignis ** last_global_harmony;
	struct harmonie_ereignis ** first_local_harmony;
	struct keyboard_ereignis *  first_keyboard;
	struct keyboard_ereignis ** last_global_keyboard;
	struct keyboard_ereignis ** first_local_keyboard;
	struct midi_ereignis     *  first_midi;
	struct midi_ereignis     ** last_global_midi;
	struct midi_ereignis     ** first_local_midi;

	/** protocol trace has been moved to the application code*/
	struct action_protocol * protocol;
	struct action_protocol ** nextprotocol;
#endif

	/** cache constants see struct cache_konstanten. */
	struct mini_heap * runtime_heap;
	struct mutabor_scanner_data * scanner;
	struct mutabor_logic_parsed * file;

	struct mutabor_box_flags flags;

#if 0
        // flags
        unsigned int used:1; //< box currently in use or wasting memory
        unsigned int keys_changed:1;
        unsigned int logic_changed:1;
        unsigned int action_changed:1;
	unsigned int tonesys_changed:1; /*< Has tonesystem changed since last called. (still unsupported) \todo implement tonesys_changed */
#endif
};
typedef struct mutabor_box_type mutabor_box_type;


//extern mutabor_box_type mut_box[MAX_BOX];
extern int laufzeit_meldungen_erlaubt;
extern int aktuelles_midi_instrument;
extern size_t minimal_box_used;

extern int keys_changed_sum;
void mutabor_set_logic(struct mutabor_box_type * box, struct mutabor_logic_parsed * logic);
void mutabor_reset_keys(struct mutabor_box_type * box);
void mutabor_reset_box(struct mutabor_box_type * box);

void mutabor_initialize_box(mutabor_box_type * box, int id);
void mutabor_initialize_boxes();
void mutabor_initialize_keyplane(mutabor_key_index_type * plane);
#ifdef DEBUG
void mutabor_check_key_count(mutabor_box_type * box);
#else
inline void mutabor_check_key_count(mutabor_box_type * box) {}
#endif

inline mutabor_note_type * mutabor_find_key_in_box(mutabor_box_type * box, size_t index) {
	mutabor_key_index_type *plane_ptr;
	size_t plane;
	mutabor_check_key_count(box);
	if (!box->key_count || index == MUTABOR_NO_NEXT) return NULL;
	plane = index >> MUT_BOX_MAX_KEY_INDEX_LOG;
	plane_ptr = &(box->current_keys);
	while (plane-- && plane_ptr) plane_ptr = plane_ptr->next;
	if (!plane_ptr) {
		return NULL;
	} 
	return &(plane_ptr->key[index & MUT_BOX_MAX_KEY_INDEX]);
}
/** 
 * Find a key in the given box.
 * 
 * \param box Box to be seached in.
 * \param key Key number to be found.
 * \param index Starting point. The first index to be checked is its successer. So you have to
 * check index number 0 yourself (which should be fast enough).
 * 
 * \return index of the key structure that has been found our 0
 * otherwise.
 */
inline size_t mutabor_find_key_in_box_by_key(mutabor_box_type * box, int key_number, size_t index) {
	size_t newidx=index;
	mutabor_note_type * key  = mutabor_find_key_in_box(box,index);
	if (key == NULL ) return MUTABOR_NO_NEXT;
	while (key != NULL && key->number != key_number) {
		newidx = key->next;
		key = mutabor_find_key_in_box(box,newidx);
	} ;
	if (key == NULL) return MUTABOR_NO_NEXT;
	return newidx;
}

/** 
 * Delete the key with the given index from the box.
 * 
 * \param box Box where the key shall be deleted.
 * \param index Index of the key in box->current_keys of the key that shall be deleted.
 */
inline void mutabor_delete_key_in_box(mutabor_box_type * box, size_t index) {
	mutabor_note_type *last_key, *current_key, *next_key;

	if (!box->key_count) return;

	current_key = mutabor_find_key_in_box(box,index);
	if (current_key == NULL) {
		UNREACHABLE;
		return;
	}

	if (!index) {
		
		if (current_key -> next != MUTABOR_NO_NEXT) {
			next_key = mutabor_find_key_in_box(box,current_key->next);
			if (current_key->next == box->last_key)
				box -> last_key = 0;
			*(current_key) = *(next_key);
			next_key->next = MUTABOR_NO_NEXT;
			next_key->userdata = NULL;
			box->key_count--;
			
		} else {
			mutASSERT(box->key_count == 1);
			current_key->userdata = NULL;
			box->key_count = 0;
		}
		return;
	}

	
	
	DEBUGLOG2(kernel_box,_T("index = %d"),(int)index);
	last_key = mutabor_find_key_in_box(box,0);
	size_t last_index = 0;
	while (last_key != NULL && last_key -> next != index) {
//		DEBUGLOG2(kernel_box,_T("last_key->next = %d"), last_key->next);
		last_index = last_key->next;
		last_key = mutabor_find_key_in_box(box,last_index);
	}
	if (last_key  == NULL || last_key -> next != index) {
 		mutabor_check_key_count(box);
		return;
	}
	if (index == box->last_key) {
		mutASSERT(last_index != box->last_key);
		box->last_key = last_index;
	}

	last_key->next = current_key->next;
	current_key -> next = MUTABOR_NO_NEXT;
	current_key -> userdata = NULL;
	box->key_count--;
	mutabor_check_key_count(box);
}


inline mutabor_note_type * mutabor_create_key_in_box (mutabor_box_type * box) {
	mutabor_note_type * last, *new_key = NULL;
	mutabor_key_index_type *plane;
	mutabor_key_index_type *oldplane;
	size_t index = 0;
	size_t planeidx = 0;
	size_t curridx = 0;
	bool found = false;

	mutASSERT(box);

	if (!box->key_count) {
		box->key_count = 1;
		mutASSERT(box->current_keys.key[0].userdata == NULL);
		mutASSERT(box->current_keys.key[0].next == MUTABOR_NO_NEXT);
		return &(box->current_keys.key[0]);
	}

	mutabor_check_key_count(box);

	last = mutabor_find_key_in_box(box,box->last_key);
	if (last == NULL) {
		UNREACHABLE;
		return NULL;
	}
	oldplane = plane = &(box->current_keys);
	
	while (plane != NULL && new_key == NULL) {
		size_t i;
		curridx = planeidx << MUT_BOX_MAX_KEY_INDEX_LOG;
		for (i = 0 ; i <= MUT_BOX_MAX_KEY_INDEX; i++) {
			if (i+curridx == box->last_key) {
				continue;
			}
			if (plane->key[i].next == MUTABOR_NO_NEXT) {
				index = i + curridx;
				new_key = &(plane->key[i]);
				found = true;
				break;
			}
		}
		if (found) break;
		planeidx++;
		oldplane = plane;
		plane = plane->next;
	}
	if (new_key == NULL) {
		plane = oldplane->next = (mutabor_key_index_type *)malloc(sizeof(mutabor_key_index_type));
		if (plane == NULL) {
			mutabor_check_key_count(box);
			return NULL;
		}
		mutabor_initialize_keyplane(plane);
		new_key = &(plane->key[0]);
		index = planeidx << MUT_BOX_MAX_KEY_INDEX_LOG;
	}

	box -> last_key = last -> next = index;
	new_key -> next = MUTABOR_NO_NEXT;
	box->key_count++;
	mutabor_check_key_count(box);
	return new_key;
}


#ifdef __cplusplus
		}
	}
}
#endif

#endif
#endif


///\}
