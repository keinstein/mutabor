/** \file 
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

#include "box.h"
#include "Parser.h"
#include "Execute.h"
#include "Hilfs.h"
#include "TabGen.h"

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

//tone_system *free_tonesystem = NULL;
//mutabor_box_type mut_box[MAX_BOX];
int laufzeit_meldungen_erlaubt = 0;
int aktuelles_midi_instrument = 0;
/* int aktuelle_keyboard_box = 0; */
size_t minimal_box_used = 0;
int keys_changed_sum = 0;

void mutabor_set_logic(struct mutabor_box_type * box, struct mutabor_logic_parsed * logic) {
	if (logic == box->file) return;
	if (logic) {
		mutabor_lock_logic(logic);
		logic->refcount++;
	}
	if (box->file) {
		mutabor_lock_logic(box->file);
		box->file->refcount--;
		if (!box->file->refcount) {
			loesche_syntax_speicher(box);
		} else {
			mutabor_unlock_logic(box->file);
		}
	}
	box->file = logic;
	if (logic) {
		mutabor_unlock_logic(logic);
	}
}


void mutabor_reset_keys(struct mutabor_box_type * box)
{
#if 0
	if ( box->last_global_harmony && *(box->last_global_harmony) )
		*(box->last_global_harmony) = NULL;

	if ( box->last_global_keyboard && *(box->last_global_keyboard) )
		*(box->last_global_keyboard) = NULL;

	if ( box->last_global_midi && *(box->last_global_midi) )
		*(box->last_global_midi)=NULL;

#endif
	box->current_logic = NULL;

	/* we make no shortcuts, here to avoid errors and make them more easy to find */
	while (mutabor_find_key_in_box(box, 0) != NULL) {
		mutabor_delete_key_in_box(box, 0);
	}
	box->key_count = 0;
	box->current_keys.key[0].next = MUTABOR_NO_NEXT;

	for (int j = 0; j < MUTABOR_KEYRANGE_MAX_WIDTH; j++)
		box->pattern.tonigkeit[j] = 0;
}



/* This function uses tonsystem_memory which is just a set of tone systems
   that will be assigned to the boxes via pointers later. */
void mutabor_reset_box(struct mutabor_box_type * box)
{
	static tone_system tonesystem_init =
		{0, 1, DOUBLE_TO_LONG(1), { DOUBLE_TO_LONG(60) }} ;
	if (!tonesystem_init.anker) {
		memset(&(tonesystem_init.ton[1]),
		       0, 
		       (MUTABOR_KEYRANGE_MAX_WIDTH-1) 
		       * sizeof(tonesystem_init.ton[1]));
		tonesystem_init.anker = 60;
	}

	for (size_t i = 0 ; i < 2 ; i++) {
		box->tonesystem_memory[i] = tonesystem_init;
	}
	box->tonesystem = &(box->tonesystem_memory[0]);
	box->last_tonesystem = tonesystem_init;
		
	mutabor_reset_keys (box);
}


void mutabor_initialize_box(mutabor_box_type * box, int id) 
{
/* C standard does not define NULL to be 0 */
	mutASSERT(box != NULL);
	memset(box,0,sizeof(mutabor_box_type));
	mutASSERT(box->current_keys.key != 0);

/* C standard does not define NULL to be 0 */
#if 0 != NULL
	box->userdata = NULL;
	box->anchor_node.next = NULL;
	box->first_harmony = NULL;
	box->last_global_harmony = NULL;
	box->first_keyboard = NULL;
	box->last_global_keyboard = NULL;
	box->first_midi = NULL;
	box->list_global_midi = NULL;
	box->cache_konstanten = NULL;
	box->protocol = NULL;
#endif
	mutabor_initialize_keyplane(&box->current_keys);
	box->anchor_node.value_field = &box->anchor;
	box->distance_node.next = &box->anchor_node;
	box->distance_node.value_field = &box->distance;
	box->start_parameter_list = &box->distance_node;
#if 0
	/* application is now responsible for logging actions */
	box->nextprotocol = &box->protocol;
#endif
	box->id = id;
	mutabor_reset_box(box);
}
			/*
/* This function uses tonsystem_memory which is just a set of tone systems
   that will be assigned to the boxes via pointers later. 
void GlobalReset()
{
#pragma message "tonesystem_memory should be box specific to be thread proof"
	for (int i = 0; i < MAX_BOX; i++) {
		tonesystem_memory[i] = tonesystem_init;
		mut_box[i].tonesystem = tonesystem_memory + i;
	}
	tonesystem_memory[MAX_BOX] = tonesystem_init;
	free_tonesystem = tonesystem_memory+MAX_BOX;

        MutResetKeys ();
}

			 */

/*
void initialize_boxes () 
{
	// use int here, as otherwise C++ doesn't find mutabor_initialize_box
	for (int i = 0 ; i < MAX_BOX; i++) {
		initialize_box( &mut_box[i],i);
	}
}
*/

void mutabor_initialize_keyplane(mutabor_key_index_type * plane)
{
	size_t i;
	mutabor_note_type *key;
	for (i = 0 ; i <= MUT_BOX_MAX_KEY_INDEX; i++) {
		key = &(plane->key[i]);
		key->userdata = NULL;
		key->next = MUTABOR_NO_NEXT;
	}
	plane->next = NULL;
}

#ifdef DEBUG
void mutabor_check_key_count(mutabor_box_type * box) {
	static bool checking = false;
	if (checking) return;
	checking = true;
	size_t index = 0;
	size_t count = 0;
	if (!box->key_count) { checking = false; return; }
	while (index != MUTABOR_NO_NEXT) {
		count++;
		mutabor_note_type * key = mutabor_find_key_in_box(box,index);
		if (!key) {
			UNREACHABLE;
			checking = false;
			return;
		}
		index = key->next;
	}
	mutASSERT(box->key_count == count);
	checking = false;
}

#endif

#ifdef __cplusplus 
		}
	}
}
#endif
///\}
