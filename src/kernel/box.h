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

#ifndef MU32_BOX_H_PRECOMPILED
#define MU32_BOX_H_PRECOMPILED

// system headers which do seldom change


enum BoxType
{
	NewBox = -3,
	NoBox,
	GmnBox,
	Box0 = 0
};
	

#define MIN_BOX NewBox

/** linked list containing key information. First is always 0 last has next == 0. */
typedef struct {
	int number;
	int channel;
	size_t id; /**< unique Id if the input device suports it */
	void * userdata;
	size_t next;
} mutabor_key_type;

#define MUT_BOX_MAX_KEY_INDEX_LOG (6)
#define MUT_BOX_MAX_KEY_INDEX ((1 << MUT_BOX_MAX_KEY_INDEX_LOG) - 1)
#define MUTABOR_NO_NEXT (~((size_t) 0))

typedef struct mutabor_key_index_type {
	mutabor_key_type key[1 << MUT_BOX_MAX_KEY_INDEX_LOG];
	struct mutabor_key_index_type * next;
	
} mutabor_key_index_type;

/** Cache of constant values.
 *   each value is stored only once (and equal for all boxes) 
 *
 *  As constants are usually parameters in functions that can be
 *  called with arbitrary parameters we use this to avoid the need of
 *  duplicate functions.
 */
struct cache_konstanten
{
	int konstante;
	struct cache_konstanten * next;
};


/** Mutabor box type. */
typedef struct {
        int id;
	int next_used;
	void * userdata;

	mutabor_key_index_type current_keys;
	size_t key_count;
	size_t last_key;
	int distance;
	int anchor;

	// pointer to anchor;
	struct interpreter_parameter_list anchor_node; 
	struct interpreter_parameter_list distance_node;
	struct interpreter_parameter_list * start_parameter_list;

	/** pattern structure in current box */
	PATTERNN pattern;
	

	/** tone system.  
	    we use pointers here, since this enables us
	    to quickly change the tone sytem. This saves us 
	    a copy operation.
	 */
	tone_system * tonesystem;
	tone_system last_tonesystem;


	/* Certain linked lists for events */
	struct harmonie_ereignis *  first_harmony;
	struct harmonie_ereignis ** last_global_harmony;
	struct harmonie_ereignis ** first_local_harmony;
	struct keyboard_ereignis *  first_keyboard;
	struct keyboard_ereignis ** last_global_keyboard;
	struct keyboard_ereignis ** first_local_keyboard;
	struct midi_ereignis     *  first_midi;
	struct midi_ereignis     ** last_global_midi;
	struct midi_ereignis     ** first_local_midi;

	/** cache constants see struct cach_konstanten. */
	struct cache_konstanten * cache_konstanten;
        // flags
        unsigned int used:1; //< box currently in use or wasting memory
        unsigned int keys_changed:1;
        unsigned int logic_changed:1;
        unsigned int action_changed:1;
	unsigned int tonesys_changed:1; //< Has tonesystem changed since last called. (still unsupported) \todo implement tonesys_changed */
} mutabor_box_type;


extern tone_system * free_tonesystem;
extern mutabor_box_type mut_box[MAX_BOX];
extern int laufzeit_meldungen_erlaubt;
extern int aktuelles_midi_instrument;
extern size_t minimal_box_used;

extern int keys_changed_sum;

void mutabor_initialize_box(mutabor_box_type * box, int id);
void initialize_boxes();
void mutabor_initialize_keyplane(mutabor_key_index_type * plane);
#ifdef DEBUG
void mutabor_check_key_count(mutabor_box_type * box);
#else
inline void mutabor_check_key_count(mutabor_box_type * box) {}
#endif

inline mutabor_key_type * mutabor_find_key_in_box(mutabor_box_type * box, size_t index) {
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
	mutabor_key_type * key  = mutabor_find_key_in_box(box,index);
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
	mutabor_key_type *last_key, *current_key, *next_key;

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


inline mutabor_key_type * mutabor_create_key_in_box (mutabor_box_type * box) {
	mutabor_key_type * last, *new_key = NULL;
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



#endif
#endif


///\}
