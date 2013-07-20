/** \file  -*- C -*-
 ********************************************************************
 * Calculations for the tunings depending on the box
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author  
 * R. Krauße,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
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
#include "src/kernel/Execute.h"
#include "box.h"
#include "GrafKern.h"
#include "src/kernel/MidiKern.h"
#include "Runtime.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/Route-inlines.h"
#include "wx/log.h"
#include "limits.h"

int protokollfunktionen_aktiv=0;
int protokollfunktion_aktionsausgabe=0;
int zeige_aktuelles_tonsystem=0;

//#define KEY_WATCH  //protokoll in keys_changed // alte Vaiante

// if no protocol wanted, set this macro to empty
#define KEY_CHANGED(box) { box->keys_changed = 1; keys_changed_sum = 1; }


tone_system tonesystem_memory[MAX_BOX+1];  /* save memory for extra data */

tone_system tonesystem_init =
        {60, 1, DOUBLE_TO_LONG(1), { DOUBLE_TO_LONG(60) }} ;


/* moved to box.h 
int liegende_tasten[MAX_BOX][64];
int liegende_tasten_max[MAX_BOX];
long last_note_id[MAX_BOX];           // 
int laufzeit_abstand[MAX_BOX]; // distance 
int laufzeit_zentrum[MAX_BOX]; // anchor
*/



char tempstring[255];

void MutResetKeys()
{
	for (int i = 0; i<MAX_BOX; i++) {
		if ( mut_box[i].last_global_harmony && *(mut_box[i].last_global_harmony) )
			*(mut_box[i].last_global_harmony) = NULL;

		if ( mut_box[i].last_global_keyboard && *(mut_box[i].last_global_keyboard) )
			*(mut_box[i].last_global_keyboard) = NULL;

		if ( mut_box[i].last_global_midi && *(mut_box[i].last_global_midi) )
			*(mut_box[i].last_global_midi)=NULL;


		/* we make no shortcuts, here to avoid errors and make them more easy to find */
		while (mutabor_find_key_in_box(&(mut_box[i]), 0) != NULL) {
			mutabor_delete_key_in_box(&(mut_box[i]), 0);
		}
		mut_box[i].key_count = 0;
		mut_box[i].current_keys.key[0].next = MUTABOR_NO_NEXT;

		for (int j = 0; j < MUTABOR_KEYRANGE_MAX_WIDTH; j++)
			mut_box[i].pattern.tonigkeit[j] = 0;

		mut_box[i].keys_changed = 0;
                mut_box[i].logic_changed = 0;
        }

	keys_changed_sum = 0;
}

/** 
* Reset boxes. 
* 
*/
/* This function uses tonsystem_memory which is just a set of tone systems
   that will be assigned to the boxes via pointers later. */
void GlobalReset()
{
#warning "tonesystem_memory should be box specific to be thread proof"
	for (int i = 0; i < MAX_BOX; i++) {
		tonesystem_memory[i] = tonesystem_init;
		mut_box[i].tonesystem = tonesystem_memory + i;
	}
	tonesystem_memory[MAX_BOX] = tonesystem_init;
	free_tonesystem = tonesystem_memory+MAX_BOX;

        MutResetKeys ();
}

// forwards
void update_pattern(mutabor_box_type  * box);
void change_breite(mutabor_box_type * box, int neu);
void change_anker(mutabor_box_type * box, int neu);
void keyboard_analyse( int taste );
void HarmonyAnalysis(mutabor_box_type * box, PATTERNN * pattern );

void execute_aktion (mutabor_box_type * box, struct do_aktion * aktion)
{
	bool WasNewLogic = false;
	mutASSERT(box);
	mutASSERT(box->tonesystem);
	TRACE;

	for ( ; aktion; aktion = aktion -> next)
	{
		AktionenMessage(box, aktion);
		switch (aktion->aufruf_typ) {
		case aufruf_logik:
			TRACE;
			execute_aktion (box, aktion->u.aufruf_logik.einstimmung);

			mutASSERT(box->last_global_keyboard);
			mutASSERT(box->last_global_harmony);
			mutASSERT(box->last_global_midi);

			*(box->last_global_keyboard) =
			        *aktion->u.aufruf_logik.lokal_keyboard;
			*(box->last_global_harmony) =
			        *aktion->u.aufruf_logik.lokal_harmonie;
			*(box->last_global_midi) = 
				*aktion->u.aufruf_logik.lokal_midi;
			WasNewLogic = true;
			break;

		case aufruf_tonsystem:
			TRACE;

			*(box -> tonesystem) =
			        *aktion->u.aufruf_tonsystem.tonsystem;
			update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
                        box->logic_changed = 1;
			break;

		case aufruf_umst_taste_abs:
			TRACE;
			change_anker(box,
			             *(aktion->u.aufruf_umst_taste_abs.keynr));

			update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
                        box->logic_changed = true;
			break;

		case aufruf_umst_breite_abs:
			TRACE;
			change_breite(box,
			              *(aktion->u.aufruf_umst_breite_abs.width));

			update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
                        box->logic_changed = true;
			break;

		case aufruf_umst_wiederholung_abs:
			TRACE;
			box->tonesystem->periode =
			        aktion->u.aufruf_umst_wiederholung_abs.faktor;

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        box->logic_changed = true;
			break;

		case aufruf_umst_wiederholung_rel:
			TRACE;
			box->tonesystem->periode +=
			        aktion->u.aufruf_umst_wiederholung_rel.faktor;

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);

#endif
			KEY_CHANGED(box);
                        box->logic_changed = true;
			break;

		case aufruf_umst_taste_rel: {
			int help;
			TRACE;
			help = box->tonesystem->anker;
			
			switch (aktion->u.aufruf_umst_taste_rel.rechenzeichen) {

			case '+':
				help += *(aktion->u.aufruf_umst_taste_rel.distance);

				break;

			case '-':
				help -= *(aktion->u.aufruf_umst_taste_rel.distance);

				break;
			}

			change_anker(box, help);

			update_pattern(box);
#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
                        box->logic_changed = true;
		}

			break;

		case aufruf_umst_breite_rel: {
			int help;
			TRACE;
			help = box->tonesystem->breite;

			switch (aktion->u.aufruf_umst_breite_rel.rechenzeichen) {

			case '+':
				help += *(aktion->u.aufruf_umst_breite_rel.difference);

				break;

			case '-':
				help -= *(aktion->u.aufruf_umst_breite_rel.difference);

				break;

			case '*':
				help *= *(aktion->u.aufruf_umst_breite_rel.difference);

				break;

			case '/':
				help /= *(aktion->u.aufruf_umst_breite_rel.difference);

				break;
			}

			change_breite(box, help);

			update_pattern(box);
#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(box);
#endif
			KEY_CHANGED(box);
		}
                        box->logic_changed = true;
		break;

		case aufruf_umst_toene_veraendert: {
			long * ton_zeiger;
			struct ton_einstell * lauf;
			TRACE;

			for (ton_zeiger = box->tonesystem->ton,
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
                        box->logic_changed = true;
		}
		break;

		case aufruf_umst_umst_bund:
			TRACE;
			/* nothing to be done here, this is only the head (containing the name) of the compound */
			break;

		case aufruf_umst_umst_case: {
			struct case_element * lauf;
			int i;
			TRACE;
			i=*(aktion->u.aufruf_umst_umst_case.choice);

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
			if (mutabor_midi_callback) {
				mutabor_midi_callback(box,aktion->u.aufruf_midi_out.out_liste);
			}
/*
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
*/
		}
		break;

		default:
			wxLogError(_("Unexpected action type: %d"), aktion->aufruf_typ);
			UNREACHABLE;
		}
	}

	// check harmonies instantly
	if ( WasNewLogic ) {
                // \todo Check, if this is necessary or used
		HarmonyAnalysis(box, &(box->pattern));
                box->logic_changed = true;
        }

#ifndef NOTES_CORRECT_SOFORT
	mutabor::NotesCorrect(box);
#endif
}

void update_pattern(mutabor_box_type * box)
{
	PATTERNN * temp_pattern = &(box->pattern);
	tone_system * tonsys = box->tonesystem;
	int i;
	TRACE;

	for (i=0;i<tonsys->breite;i++) temp_pattern->tonigkeit[i]=0;

	
	for (mutabor_key_type * key = mutabor_find_key_in_box(box,0);
	     key != NULL;
	     key = mutabor_find_key_in_box(box,key->next)) {
		(temp_pattern->tonigkeit[GET_INDEX( key->number, tonsys )])++;
	}
}

void change_anker(mutabor_box_type * box, int neu)
{
	tone_system * tonsys = box->tonesystem;
	tone_system * temp = tonsys;
	int i;
	TRACE;
	/** \todo why do we have two anchors? */
	box->anchor -= neu-tonsys->anker;

	while ( box->anchor < 0 )
		box->anchor += tonsys->breite;

	box->anchor %= tonsys->breite;

	while (neu< MUTABOR_KEYRANGE_MIN_KEY)
		neu += tonsys->breite;

	while (neu> MUTABOR_KEYRANGE_MAX_KEY)
		neu -= tonsys->breite;

	free_tonesystem->ton[0]=GET_FREQ(neu,tonsys);

	for (i=1; i<tonsys->breite; i++)
		free_tonesystem->ton[i] =
		        free_tonesystem->ton[0] + tonsys->ton[i]-tonsys->ton[0];

	free_tonesystem->anker=neu;
	free_tonesystem->breite=tonsys->breite;
	free_tonesystem->periode=tonsys->periode;
	box->tonesystem=free_tonesystem;
	free_tonesystem=temp;
}

void change_breite(mutabor_box_type * box, int neu)
{
	tone_system * tonsys = box->tonesystem;
	int i;
	
	DEBUGLOG2(kernel_exec,_T("Box %p got new width: %d"), (void*)box, neu);
	if ( neu <= 0 ) neu = 1;
	if ( neu > MUTABOR_KEYRANGE_MAX_WIDTH)
		neu = MUTABOR_KEYRANGE_MAX_WIDTH;
	if ( neu > tonsys->breite )
		for (i = tonsys->breite; i < neu; i++)
			tonsys->ton[i]=GET_FREQ((tonsys->anker+i),tonsys);
	tonsys->periode =
		GET_FREQ(tonsys->anker+neu,tonsys) - GET_FREQ(tonsys->anker,tonsys);
	tonsys->breite=neu;
}

/** return the smallest key pressed actually */
int tiefste_taste(mutabor_box_type *  box)
{
	size_t index = 0;
	mutabor_key_type * key;
	int cmp;
	
	int min = INT_MAX;

	if (!(box->key_count)) {
		return INT_MIN;
	}
	TRACE;
	
	do {
		key = mutabor_find_key_in_box(box,index);
		if (key == NULL) {
			UNREACHABLE;
			break;
		} else {
			cmp = key->number;
			if (cmp < min ) min = cmp;
			index = key->next;
		}	
	} while (index);
	return min;
}

/** return the largest key pressed actually */
int hoechste_taste(mutabor_box_type * box)
{
	size_t index = 0;
	mutabor_key_type * key;
	int cmp;
	
	int max = INT_MIN;

	if (!(box->key_count)) {
		return INT_MAX;
	}
	TRACE;
	
	do {
		key = mutabor_find_key_in_box(box,index);
		if (key == NULL) {
			UNREACHABLE;
			break;
		} else {
			cmp = key->number;
			if (cmp < max ) max = cmp;
			index = key->next;
		}	
	} while (index);
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


void HarmonyAnalysis(mutabor_box_type * box, PATTERNN * pattern )
{

	struct harmonie_ereignis *help;
	tone_system *tonsys = box->tonesystem;
	int i;
	TRACE;

	for (help = box->first_harmony; help; help=help->next ) {
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
							box->distance = box->anchor = i;
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


// die taste in box wird in die Listen (pattern, liegende_taste) aufgenommen
void AddKey( mutabor_box_type * box, int taste, size_t id, size_t channel, void * userdata)
{          
	mutabor_key_type *new_key = mutabor_create_key_in_box(box);
	new_key->number = taste;
	new_key->channel = channel;
	new_key->id = id;
	new_key->userdata = userdata;
	
	if (box->tonesystem && box->tonesystem != NULL) {
		box->pattern.tonigkeit[GET_INDEX(taste,box->tonesystem)]++;
		HarmonyAnalysis(box, &(box->pattern));
	}
	KEY_CHANGED(box);
}

// die taste in box wird aus den Listen (pattern, liegende_taste) gestrichen */
void DeleteKey( mutabor_box_type * box, int taste, size_t id, int channel)
{
	size_t index=0;
	TRACE;
	mutabor_key_type * key;
	while ((key = mutabor_find_key_in_box(box,index)) != NULL) {
		if (key->number == taste && key ->id == id && key -> channel == channel) 
			break;
		index = key->next;
	}

	if (key == NULL) return;
	mutabor_delete_key_in_box(box,index);
	
	if (box->tonesystem) {
		box->pattern.tonigkeit[GET_INDEX(taste,box->tonesystem)]--;
		HarmonyAnalysis(box, &(box->pattern));
	}
	KEY_CHANGED(box);

/* This code is a little bit slower than the old one but it preserves the order of the keys.*/
#if 0 
/* old code */

	for (int i=0; i<(box->last_key); i++)
		if ( liegende_tasten[box][i] == taste ) {
			liegende_tasten[box][i] =
			        liegende_tasten[box][--(box->last_key)];
			box->pattern.tonigkeit[GET_INDEX(taste,box->tonesystem)]--;
			HarmonyAnalysis(box, &(box->pattern));
			KEY_CHANGED(box);
			break;
		}
#endif
}

void KeyboardIn(mutabor_box_type * box, const mutChar *keys)
{
	TRACE;
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

void MidiAnalysis(mutabor_box_type * box, BYTE midiByte)
{
	struct midi_ereignis * lauf;
	if (!box) {
		UNREACHABLE;
		return;
	}
	TRACE;

	if ( midiByte & 0x80 )
		midiByte &= 0xF0;

	for (lauf = box->first_midi; lauf; lauf=lauf->next) {
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

void pascal _export KeyboardAnalyse(mutabor_box_type * box, int taste, char isLogic)
{
	TRACE;
	for (struct keyboard_ereignis *help = box->first_keyboard; 
	     help ; help=help->next)
		if ( toupper(taste)==help->taste && isLogic == 
		     ( help->the_logik_to_expand != NULL ) ) {
			execute_aktion(box, help->aktion);
			return;
		}
}

void pascal _export KeyboardAnalyseSimple(mutabor_box_type * box, int taste)
{
	TRACE;
	for (struct keyboard_ereignis *help = box->first_keyboard; 
	     help ; help=help->next)
		if ( toupper(taste)==help->taste ) {
			execute_aktion(box, help->aktion);
			return;
		}
}

#if 0


/************ Protokoll - Funktionen ****************/
/* these functions must be defined somewhere else */

void protokoll_aktuelles_tonsystem( mutabor_box_type * box )
{
	tone_system * tonsys = box->tonesystem;
	long freq;
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
			                   ((freq >> 0x10)& 0xff) +(((float)((freq >> 0x08)&0xff]/256.0)) );
		} else {
			laufzeit_protokoll("%2d : %%",i);
		}
	}

exit_laufzeit_protokoll( );
}

#define SHOW_CHANNEL
void protokoll_liegende_frequenzen( mutabor_box_type * box )
{
	tone_system * tonsys = box->tonesystem;
	int i, imax, lts[64], lt;
	long freq;
//	unsigned char * zugriff = (unsigned char*) & freq;
	TRACE;
	imax = (box->last_key);
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

void protokoll_aktuelle_relationen( mutabor_box_type * box )
{
	tone_system * tonsys = box->tonesystem;
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

void protokoll_liegende_relationen( mutabor_box_type * box )
{
	tone_system * tonsys = box->tonesystem;
	int i;
	TRACE;
	init_laufzeit_protokoll();
//  laufzeit_protokoll("Liegende Relationen (#%d):",box);

	for (i=0;i<((box->last_key)-1);i++) {
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


#endif
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
