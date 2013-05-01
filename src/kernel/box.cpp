/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/box.cpp,v 1.4 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log*
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

#include "box.h"

tone_system *free_tonesystem = NULL;
mutabor_box_type mut_box[MAX_BOX];
int laufzeit_meldungen_erlaubt = 0;
int aktuelles_midi_instrument = 0;
/* int aktuelle_keyboard_box = 0; */
size_t minimal_box_used = 0;
int keys_changed_sum = 0;



void initialize_box(mutabor_box_type * box, int id) 
{
/* C standard does not define NULL to be 0 */
	mutASSERT(box != NULL);
	memset(box,0,sizeof(mutabor_box_type));
	mutASSERT(box->current_keys.key != 0);

/* C standard does not define NULL to be 0 */
#if 0 != NULL
	box->userdata = NULL;
	box->anchor_node.next = NULL;
	box->tonesystem = NULL;
	box->first_harmony = NULL;
	box->last_global_harmony = NULL;
	box->first_keyboard = NULL;
	box->last_global_keyboard = NULL;
	box->first_midi = NULL;
	box->list_global_midi = NULL;
	box->cache_konstanten = NULL
#endif
	mutabor_initialize_keyplane(&box->current_keys);
	box->anchor_node.value_field = &box->anchor;
	box->distance_node.next = &box->anchor_node;
	box->distance_node.value_field = &box->distance;
	box->start_parameter_list = &box->distance_node;
	box->id = id;
}

void initialize_boxes () 
{
	// use int here, as otherwise C++ doesn't find mutabor_initialize_box
	for (int i = 0 ; i < MAX_BOX; i++) {
		initialize_box( &mut_box[i],i);
	}
}
void mutabor_initialize_keyplane(mutabor_key_index_type * plane)
{
	size_t i;
	mutabor_key_type *key;
	for (i = 0 ; i <= MUT_BOX_MAX_KEY_INDEX; i++) {
		key = &(plane->key[i]);
		key->userdata = NULL;
		key->next = MUTABOR_NO_NEXT;
	}
	plane->next = NULL;
}


///\}
