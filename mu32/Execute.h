/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Execute.h,v 1.5 2011/02/20 22:35:55 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:55 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Execute.h,v $
 * Revision 1.5  2011/02/20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ##################################################################
// Mutabor 3, Header execute file
// ##################################################################

#ifndef EXECUTE_H
#define EXECUTE_H

#include "Interpre.h"

void KeyboardIn(int box, const mutChar *keys);

void GlobalReset();

void AddKey(int box, int taste, int id);

void DeleteKey(int box, int taste, int id);

void MidiAnalysis(int box, BYTE midiByte);

extern ton_system *tonsystem[MAX_BOX];

void protokoll_aktuelles_tonsystem( int instr );

void protokoll_liegende_frequenzen( int instr );

void protokoll_aktuelle_relationen( int instr );

void protokoll_liegende_relationen( int instr );

void FlushUpdateUI();

#define FLUSH_UPDATE_UI FlushUpdateUI()
#endif



///\}
