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

tone_system * free_tonesystem;

mutabor_box_type mut_box[MAX_BOX];
int laufzeit_meldungen_erlaubt = 0;
int aktuelles_midi_instrument = 0;
int aktuelle_keyboard_box = 0;
size_t minimal_box_used = 0;
int keys_changed_sum = 0;

void initialize_boxes () 
{
	for (size_t i = 0 ; i < MAX_BOX; i++) {
		mutabor_box_type * box = &(mut_box[i]);
		box->id = i;
		box->next_used = 0;
		box->tonesystem = NULL;
		box->used = 0;
		box->keys_changed = 0;
		box->logic_changed = 0;
		box->action_changed = 0;
	}
}
///\}
