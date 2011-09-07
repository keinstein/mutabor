/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/box.cpp,v 1.2 2011/09/07 13:06:50 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/07 13:06:50 $
 * \version $Revision: 1.2 $
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
///\}
