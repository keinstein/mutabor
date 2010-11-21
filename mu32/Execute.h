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

