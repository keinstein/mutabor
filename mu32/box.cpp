/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/box.cpp,v 1.3 2011/09/08 18:50:41 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/08 18:50:41 $
 * \version $Revision: 1.3 $
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
///\}
