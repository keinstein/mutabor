/** \file  -*- C -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Execute.cpp,v 1.14 2011/10/13 18:26:13 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/13 18:26:13 $
 * \version $Revision: 1.14 $
 * \license GPL
 *
 * $Log: Execute.cpp,v $
 * Revision 1.14  2011/10/13 18:26:13  keinstein
 * Fix a Bug in the kernel:
 * retuning case did not execute the following statements,
 * which lead to unexpected results
 *
 * Revision 1.13  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.12  2011-09-08 18:50:41  keinstein
 * Fix some further update bug
 *
 * Revision 1.11  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.10  2011-07-27 20:48:32  keinstein
 * started to move arrays using MAX_BOX into struct mutabor_box_type
 *
 * Revision 1.9  2011-03-06 13:15:40  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.8  2011-02-20 22:35:55  keinstein
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
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// Berechnungen der Stimmungen in den Boxen
// ------------------------------------------------------------------
#include "Defs.h"
#include <math.h>
#ifndef MUTWIN
#include <conio.h>
#endif

#include "Global.h"
#include "box.h"
#include "GrafKern.h"
#include "MidiKern.h"
#include "Runtime.h"
#include "src/kernel/routing/Device.h"
#include "wx/log.h"

int protokollfunktionen_aktiv=0;
int protokollfunktion_aktionsausgabe=0;
int zeige_aktuelles_tonsystem=0;

//#define KEY_WATCH  //protokoll in keys_changed // alte Vaiante

// if no protocol wanted, set this macro to empty
#define KEY_CHANGED(box) { mut_box[box].keys_changed=1; keys_changed_sum = 1; }


tone_system tonesystem_memory[MAX_BOX+1];  /* save memory for extra data */

tone_system tonesystem_init =
        {60, 1, DOUBLE_TO_LONG(1), { DOUBLE_TO_LONG(60) }} ;


int liegende_tasten[MAX_BOX][64];
int liegende_tasten_max[MAX_BOX];
long last_note_id[MAX_BOX];           // (outinstr. << 8) + taste

int laufzeit_abstand[MAX_BOX];
int laufzeit_zentrum[MAX_BOX];

char tempstring[255];

void MutResetKeys()
{
	for (int i = 0; i<MAX_BOX; i++) {
		if ( last_global_harmonie[i] && *last_global_harmonie[i] )
			*last_global_harmonie[i] = NULL;

		if ( last_global_keyboard[i] && *last_global_keyboard[i] )
			*last_global_keyboard[i] = NULL;

		if ( last_global_midi[i] && *last_global_midi[i] )
			*last_global_midi[i]=NULL;

		liegende_tasten_max[i] = 0;

		for (int j = 0; j < MAX_BREITE; j++)
			mut_box[i].pattern.tonigkeit[j] = 0;

		mut_box[i].keys_changed = 0;
                mut_box[i].logic_changed = 0;
        }

	keys_changed_sum = 0;
}

/* reset boxes */
void GlobalReset()
{
	for (int i = 0; i < MAX_BOX; i++) {
		tonesystem_memory[i] = tonesystem_init;
		mut_box[i].tonesystem = tonesystem_memory + i;
	}
	tonesystem_memory[MAX_BOX] = tonesystem_init;
	free_tonesystem = tonesystem_memory+MAX_BOX;

        MutResetKeys ();
}

// forwards
void update_pattern(int instr);
void change_breite(int instr, int neu);
void change_anker(int instr, int neu);
void keyboard_analyse( int taste );
void HarmonyAnalysis(int box, PATTERNN * pattern );

void execute_aktion (int box, struct do_aktion * aktion)
{
	bool WasNewLogic = false;
	TRACE;

	for ( ; aktion; aktion = aktion -> next)
	{
		AktionenMessage(box, aktion->name);
		switch (aktion->aufruf_typ) {
		case aufruf_logik:
			TRACE;
			execute_aktion (box, aktion->u.aufruf_logik.einstimmung);
			* last_global_keyboard[box] =
			        * aktion->u.aufruf_logik.lokal_keyboard;
			* last_global_harmonie[box] =
			        * aktion->u.aufruf_logik.lokal_harmonie;
			* last_global_midi[box] =
			        * aktion->u.aufruf_logik.lokal_midi;
			WasNewLogic = true;
			break;

		case aufruf_tonsystem:
			TRACE;
			* mut_box[box].tonesystem =
			        * aktion->u.aufruf_tonsystem.tonsystem;
			update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = 1;
			break;

		case aufruf_umst_taste_abs:
			TRACE;
			change_anker(box,
			             aktion->u.aufruf_umst_taste_abs.wert[box]);

			update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = true;
			break;

		case aufruf_umst_breite_abs:
			TRACE;
			change_breite(box,
			              aktion->u.aufruf_umst_breite_abs.wert[box]);

			update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = true;
			break;

		case aufruf_umst_wiederholung_abs:
			TRACE;
			mut_box[box].tonesystem->periode =
			        aktion->u.aufruf_umst_wiederholung_abs.faktor;

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = true;
			break;

		case aufruf_umst_wiederholung_rel:
			TRACE;
			mut_box[box].tonesystem->periode +=
			        aktion->u.aufruf_umst_wiederholung_rel.faktor;

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = true;
			break;

		case aufruf_umst_taste_rel: {
			int help;
			TRACE;
			help = mut_box[box].tonesystem->anker;
			
			switch (aktion->u.aufruf_umst_taste_rel.rechenzeichen) {

			case '+':
				help += aktion->u.aufruf_umst_taste_rel.wert[box];

				break;

			case '-':
				help -= aktion->u.aufruf_umst_taste_rel.wert[box];

				break;
			}

			change_anker(box, help);

			update_pattern(box);
#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = true;
		}

			break;

		case aufruf_umst_breite_rel: {
			int help;
			TRACE;
			help = mut_box[box].tonesystem->breite;

			switch (aktion->u.aufruf_umst_breite_rel.rechenzeichen) {

			case '+':
				help += aktion->u.aufruf_umst_breite_rel.wert[box];

				break;

			case '-':
				help -= aktion->u.aufruf_umst_breite_rel.wert[box];

				break;

			case '*':
				help *= aktion->u.aufruf_umst_breite_rel.wert[box];

				break;

			case '/':
				help /= aktion->u.aufruf_umst_breite_rel.wert[box];

				break;
			}

			change_breite(box, help);

			update_pattern(box);
#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
		}
                        mut_box[box].logic_changed = true;
		break;

		case aufruf_umst_toene_veraendert: {
			long * ton_zeiger;
			struct ton_einstell * lauf;
			TRACE;

			for (ton_zeiger = mut_box[box].tonesystem->ton,
			                lauf = aktion->u.aufruf_umst_toene_veraendert.tonliste;
			                lauf;
			                lauf = lauf->next, ton_zeiger ++) {

				switch (lauf->ton_einstell_typ) {

				case einstell_stumm:
					* ton_zeiger = 0;

					break;

				case einstell_gleich:
					/* nichts tun */
					break;

				case einstell_absolut:
					* ton_zeiger = lauf->u.einstell_absolut.wert;

					break;

				case einstell_relativ:
					* ton_zeiger += lauf->u.einstell_relativ.wert;

					break;

				}

			}

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        mut_box[box].logic_changed = true;
		}
		break;

		case aufruf_umst_umst_case: {
			struct case_element * lauf;
			int i;
			TRACE;
			i=aktion->u.aufruf_umst_umst_case.wert[box];

			for (lauf = aktion->u.aufruf_umst_umst_case.umst_case;
			                lauf;
			                lauf = lauf->next) {
				if ( (i == lauf->case_wert) || (lauf->is_default)) {
					execute_aktion (box, lauf->case_aktion);
					// return would break further execution
					break; 
				}
			}
		}
		break;

		case aufruf_midi_out: {
			struct midiliste * lauf;
			unsigned long data = 0, faktor = 1, n = 0;
			;
			TRACE;

			for (lauf = aktion->u.aufruf_midi_out.out_liste;
			                lauf && faktor ;
			                lauf = lauf -> next) {
				data += faktor * (unsigned char) lauf->midi_code;
				faktor *= 0x100;
				n++;
			}
			mutabor::MidiOut(box, data, n);
		}
		break;

		case aufruf_umst_umst_bund:
			TRACE;
			wxLogWarning(_("Unhandled case path: aufruf_umst_umst_bund"));
			UNREACHABLE;
			break;

		default:
			wxLogError(_("Unexpected action type: %d"), aktion->aufruf_typ);
			UNREACHABLE;
		}
	}

	// check harmonies instantly
	if ( WasNewLogic ) {
                // \todo Check, if this is necessary or used
		HarmonyAnalysis(box, &(mut_box[box].pattern));
                mut_box[box].logic_changed = true;
        }

#ifndef NOTES_CORRECT_SOFORT
	mutabor::NotesCorrect(box);
#endif
}

void update_pattern(int box)
{
	PATTERNN * temp_pattern = &(mut_box[box].pattern);
	tone_system * tonsys = mut_box[box].tonesystem;
	int i;
	TRACE;

	for (i=0;i<tonsys->breite;i++) temp_pattern->tonigkeit[i]=0;

	for (i=0;i<liegende_tasten_max[box];i++)
		(temp_pattern->tonigkeit[GET_INDEX( liegende_tasten[box][i]
		                                    ,tonsys )])++;
}

void change_anker(int box, int neu)
{
	tone_system * tonsys = mut_box[box].tonesystem;
	tone_system * temp = tonsys;
	int i;
	TRACE;
	laufzeit_zentrum[box]-=neu-tonsys->anker;

	while ( laufzeit_zentrum[box] < 0 )
		laufzeit_zentrum[box] += tonsys->breite;

	laufzeit_zentrum[box]%=tonsys->breite;

	while (neu<36)
		neu += tonsys->breite;

	while (neu>96)
		neu -= tonsys->breite;

	free_tonesystem->ton[0]=GET_FREQ(neu,tonsys);

	for (i=1; i<tonsys->breite; i++)
		free_tonesystem->ton[i] =
		        free_tonesystem->ton[0] + tonsys->ton[i]-tonsys->ton[0];

	free_tonesystem->anker=neu;
	free_tonesystem->breite=tonsys->breite;
	free_tonesystem->periode=tonsys->periode;
	mut_box[box].tonesystem=free_tonesystem;
	free_tonesystem=temp;
}

void change_breite(int box, int neu)
{
	tone_system * tonsys = mut_box[box].tonesystem;
	int i;
	
	DEBUGLOG2(kernel_exec,_T("Box %d got new width: %d"), box, neu);
	if ( neu>0 && neu < MAX_BREITE ) {
		if ( neu > tonsys->breite )
			for (i = tonsys->breite; i < neu; i++)
				tonsys->ton[i]=GET_FREQ((tonsys->anker+i),tonsys);
		tonsys->periode =
		        GET_FREQ(tonsys->anker+neu,tonsys) - GET_FREQ(tonsys->anker,tonsys);
		tonsys->breite=neu;
	}
}

// ermittelt die tiefste liegende Taste bei box
int tiefste_taste(int box)
{
	int i, min = 9999;
	TRACE;

	for (i = 0; i < liegende_tasten_max[box]; i++)
		if ( liegende_tasten[box][i] < min )
			min = liegende_tasten[box][i];

	return min;
}

// ermittelt die hˆchste liegende Taste bei box
int hoechste_taste(int box)
{
	int i, max = 0;
	TRACE;

	for (i = 0; i<liegende_tasten_max[box]; i++)
		if ( liegende_tasten[box][i] > max )
			max = liegende_tasten[box][i];
	return max;
}

// vergleicht zwei PATTERNNs der Breite breite und beginnt mit dem Vergleich
// indexversetzt ab startindex (wg. Harmonieformanalyse)
int compare_harmonie(int breite, int startindex, PATTERNN * laufzeit, PATTERNN * vergleich)
{
	int i;
	TRACE;

	for (i=0;i<breite; i++,startindex++) {
		if ( vergleich->tonigkeit[i] ) {
			/* Bedeutung: vergleich: 0(egal) 1(off)   2(on)
			              laufzeit:          0(off)  >0(on)   */

			if ( vergleich->tonigkeit[i]==1 &&
			                laufzeit->tonigkeit[startindex%breite] )
				/* vergleich = off, aber laufzeit != off */
				return 0 ;
			if ( vergleich->tonigkeit[i]!=1 &&
			                laufzeit->tonigkeit[startindex%breite]==0 )
				/* vergleich = on , aber laufzeit = off */
				return 0 ;
		}
	}
	return 1;
}


void HarmonyAnalysis(int box, PATTERNN * pattern )
{

	struct harmonie_ereignis *help;
	tone_system *tonsys = mut_box[box].tonesystem;
	int i;
	TRACE;

	for (help = first_harmonie[box]; help; help=help->next ) {
		switch ( help->ist_harmonieform ) {

		case 0: // analysiere auf harmonie
			TRACE;
			if ( help->vortaste>=0 &&
			                GET_INDEX(tiefste_taste(box),tonsys ) != help->vortaste ) {
				// failed
			} else {
				if ( help->nachtaste>=0 &&
				                GET_INDEX(hoechste_taste(box),tonsys)!=help->nachtaste ) {
					// failed
				} else {
					// teste_harmonie

					if ( compare_harmonie(tonsys->breite,0,pattern,help->pattern) ) {
						// PASST !!!
						execute_aktion(box,help->aktion);
						return;
					}
				}
			}

			break;

		case 1: // analysiere auf harmonieform
			TRACE;
			for (i=0; i<tonsys->breite; i++) {
				if ( help->vortaste>=0 &&
				                GET_INDEX(tiefste_taste(box)-i, tonsys) != help->vortaste ) {
					// failed
				} else {
					if ( help->nachtaste>=0 &&
					                GET_INDEX(hoechste_taste(box)-i, tonsys) != help->nachtaste ) {
						// failed
					} else {
						// teste_harmonie

						if (compare_harmonie(tonsys->breite, i, pattern, help->pattern)) {
							// PASST !!!
							laufzeit_abstand[box] =	laufzeit_zentrum[box] = i;
							execute_aktion(box, help->aktion);
							return;
						}
					}
				}
			}

			break;

		case 2: // default
			TRACE;
			execute_aktion(box, help->aktion);

			break;
		}
	}
}


/** \todo range check */
// die taste in box wird in die Listen (pattern, liegende_taste)	aufgenommen
void AddKey( int box, int taste, int id)
{          
	TRACE;
	liegende_tasten[box][liegende_tasten_max[box]++] = taste; 
	mut_box[box].pattern.tonigkeit[GET_INDEX(taste,mut_box[box].tonesystem)]++;
	last_note_id[box] = (id << 16) + (box << 8) + taste;
	HarmonyAnalysis(box, &mut_box[box].pattern);
	last_note_id[box] = 0;
	KEY_CHANGED(box);
}

// die taste in box wird aus den Listen (pattern, liegende_taste)	gestrichen */
void DeleteKey( int box, int taste, int id)
{
	TRACE;
	for (int i=0; i<liegende_tasten_max[box]; i++)
		if ( liegende_tasten[box][i] == taste ) {
			liegende_tasten[box][i] =
			        liegende_tasten[box][--liegende_tasten_max[box]];
			mut_box[box].pattern.tonigkeit[GET_INDEX(taste,mut_box[box].tonesystem)]--;
			last_note_id[box] = (id << 16) + (box << 8) +  taste;
			HarmonyAnalysis(box, &mut_box[box].pattern);
			last_note_id[box] = 0;
			KEY_CHANGED(box);
			break;
		}
}

void KeyboardIn(int box, const mutChar *keys)
{
	TRACE;
	aktuelle_keyboard_box = box;
	char TonSystem = 0;

	for (size_t i= 0; i < mutStrLen(keys); i++) {
		mutChar c = keys[i];

		if ( c == mutT('&') ) {
			TonSystem = 1;
			continue;
		}

		if ( mutT('0') <= c && c <= mutT('z') ) {
			if ( TonSystem )
				KeyboardAnalyse(box, (int) c, 0);
			else
				KeyboardAnalyseSimple(box, (int) c);
                }
		TonSystem = 0;
	}
}

void MidiAnalysis(int box, BYTE midiByte)
{
	struct midi_ereignis * lauf;
	TRACE;

	if ( midiByte & 0x80 )
		midiByte &= 0xF0;

	for (lauf = first_midi[box]; lauf; lauf=lauf->next) {
		if ( *(lauf->scan_pos) != midiByte )
			lauf->scan_pos = lauf->first_pos;
		else {
			lauf->scan_pos++;
			if ( *(lauf->scan_pos) == -1 )
				break;
		}
	}

	if ( lauf )
		execute_aktion( box, lauf->aktion);
}

void pascal _export KeyboardAnalyse(int box, int taste, char isLogic)
{
	TRACE;
	for (struct keyboard_ereignis *help = first_keyboard[box]; 
	     help ; help=help->next)
		if ( toupper(taste)==help->taste && isLogic == 
		     ( help->the_logik_to_expand != NULL ) ) {
			execute_aktion(box, help->aktion);
			return;
		}
}

void keyboard_analyse( int taste )
{
	TRACE;
	KeyboardAnalyseSimple(aktuelle_keyboard_box, taste);
}

void pascal _export KeyboardAnalyseSimple(int box, int taste)
{
	TRACE;
	for (struct keyboard_ereignis *help = first_keyboard[box]; 
	     help ; help=help->next)
		if ( toupper(taste)==help->taste ) {
			execute_aktion(box, help->aktion);
			return;
		}
}

/************ Protokoll - Funktionen ****************/

void protokoll_aktuelles_tonsystem( int box )
{
	tone_system * tonsys = mut_box[box].tonesystem;
	long freq;
	unsigned char * zugriff = (unsigned char*) & freq;
	int i;
	TRACE;
	init_laufzeit_protokoll();
//  laufzeit_protokoll("Tonsystem: (#%d)",box);
	laufzeit_protokoll("Anker= %d",tonsys->anker);
	laufzeit_protokoll("Breite= %d",tonsys->breite);
	laufzeit_protokoll("Periode= %.1f cent",
	                   LONG_TO_CENT(tonsys->periode));

	for (i=0;i<tonsys->breite;i++) {
		if ( (freq=tonsys->ton[i])!=0) {
			laufzeit_protokoll("%2d : %.1f Hz (%.2f)",
			                   i, LONG_TO_HERTZ(tonsys->ton[i]) ,
			                   (zugriff[3]+(((float)zugriff[2])/256.0)) );
		} else {
			laufzeit_protokoll("%2d : %%",i);
		}
	}

	exit_laufzeit_protokoll( );
}

#define SHOW_CHANNEL
void protokoll_liegende_frequenzen( int box )
{
	tone_system * tonsys = mut_box[box].tonesystem;
	int i, imax, lts[64], lt;
	long freq;
	unsigned char * zugriff = (unsigned char*) & freq;
	TRACE;
	imax = liegende_tasten_max[box];
	bcopy(liegende_tasten[box], lts, imax*sizeof(int));
	init_laufzeit_protokoll();

	for (i = 0; i < imax; i++) {
		lt = lts[i];

		if ( (freq=GET_FREQ( lt ,tonsys ))!=0) {
#ifndef SHOW_CHANNEL
			laufzeit_protokoll("%2d : %8.1f Hz (%6.2f)",
			                   lt,
			                   LONG_TO_HERTZ(freq),
			                   (zugriff[3]+(((float)zugriff[2])/256.0)) );
#else
			laufzeit_protokoll("%2d : %8.1f Hz (%6.2f)[ch: %d]",
			                   lt,
			                   LONG_TO_HERTZ(freq),
			                   (zugriff[3]+(((float)zugriff[2])/256.0)), mutabor::GetChannel(box, lt));
#endif
		} else {
			laufzeit_protokoll("%2d : %%",lt);
		}
	}

	exit_laufzeit_protokoll();
}

void protokoll_aktuelle_relationen( int box )
{
	tone_system * tonsys = mut_box[box].tonesystem;
	int i,j;
	TRACE;
	init_laufzeit_protokoll();

	for (i=0;i<tonsys->breite && tonsys->ton[i]==0;i++);

	/* sucht erstes Intervall != 0 */
	laufzeit_protokoll("Reference [%d]",i);

	for (j=i+1;j<tonsys->breite; j++) {
		if (tonsys->ton[j]!=0) {
			laufzeit_protokoll("%2d:%.1f cent",j,
			                   LONG_TO_CENT( tonsys->ton[j] -
			                                 tonsys->ton[i] ) );
		} else {
			laufzeit_protokoll("%2d:%%",j);
		}
	}

	exit_laufzeit_protokoll( );
}

void protokoll_liegende_relationen( int box )
{
	tone_system * tonsys = mut_box[box].tonesystem;
	int i;
	TRACE;
	init_laufzeit_protokoll();
//  laufzeit_protokoll("Liegende Relationen (#%d):",box);

	for (i=0;i<(liegende_tasten_max[box]-1);i++) {
		if ( (GET_FREQ( liegende_tasten[box][i+1] , tonsys )) !=0 ) {
			laufzeit_protokoll("%.2f cent",
			                   LONG_TO_CENT( GET_FREQ(liegende_tasten[box][i+1], tonsys ) -
			                                 GET_FREQ(liegende_tasten[box][i], tonsys) ));
		} else {
			laufzeit_protokoll("  %%");
		}
	}

	exit_laufzeit_protokoll( );
}



void FlushUpdateUI()
{
        int i = minimal_box_used;
        mutabor_box_type * box;
	TRACE;
	if ( keys_changed_sum && updatecallback ) {
                do {
                        box = &mut_box[i];
                        if (box->keys_changed) {
                                updatecallback(i,box -> logic_changed);
                                box -> keys_changed = 0;
                                box -> logic_changed = 0;
                        }
                        i = box -> next_used;
                } while(i);

                keys_changed_sum = 0;
	}
}




///\}
