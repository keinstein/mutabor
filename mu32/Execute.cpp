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
#include "Interpre.h"
#include "GrafKern.h"
#include "MidiKern.h"
#include "Runtime.h"

int protokollfunktionen_aktiv=0;
int protokollfunktion_aktionsausgabe=0;
int zeige_aktuelles_tonsystem=0;

//#define KEY_WATCH  //protokoll in keys_changed // alte Vaiante

// wenn kein Protokoll gew¸nscht, dann diese Definition auf "Leer" setzen
#define KEY_CHANGED(instrument) { keys_changed[instrument]=1; keys_changed_sum = 1; }

// in device.h :
void MidiOut(int box, DWORD data, char n);
void NotesCorrect(int box);
int  GetChannel(int box, int taste);

PATTERNN pattern[MAX_BOX];         /* Die momentan gespielte Harmonie */
ton_system tonsystem_memory[MAX_BOX+1];  /* Der Platz fÅr die tatsÑchlichen
												tonsysteme */

ton_system tonsystem_init =
        {60, 1, DOUBLE_TO_LONG(1), { DOUBLE_TO_LONG(60) }} ;

ton_system *tonsystem[MAX_BOX]       /* Verweise auf die aktuellen
                                    Tonsysteme (in tonsystem_memory) */
/*	  = { tonsystem_memory + 0,
         tonsystem_memory + 1,tonsystem_memory + 2,
         tonsystem_memory + 3,tonsystem_memory + 4,
         tonsystem_memory + 5,tonsystem_memory + 6,
         tonsystem_memory + 7,tonsystem_memory + 8,
         tonsystem_memory + 9,tonsystem_memory + 10,
         tonsystem_memory + 11,tonsystem_memory + 12,
         tonsystem_memory + 13,tonsystem_memory + 14,
         tonsystem_memory + 15 }*/;
ton_system * freies_tonsystem    /* Freizeiger auf das */
= tonsystem_memory + MAX_BOX;     /*   "17'te" tonsystem zum Rechnen */
/*   als Ringspeicher */

int liegende_tasten[MAX_BOX][64];
int liegende_tasten_max[MAX_BOX];
long last_note_id[MAX_BOX];           // (outinstr. << 8) + taste

int laufzeit_abstand[MAX_BOX];
int laufzeit_zentrum[MAX_BOX];

int laufzeit_meldungen_erlaubt=0;

int aktuelles_midi_instrument=0;
int aktuelles_keyboard_instrument=0;
char tempstring[255];

// Boxen zur¸cksetzen
void GlobalReset()
{
	int i;

	for (i = 0; i <= MAX_BOX; i++)
		tonsystem_memory[i] = tonsystem_init;

	for (i = 0; i<MAX_BOX; i++) {
		if ( last_global_harmonie[i] && *last_global_harmonie[i] )
			*last_global_harmonie[i] = NULL;

		if ( last_global_keyboard[i] && *last_global_keyboard[i] )
			*last_global_keyboard[i] = NULL;

		if ( last_global_midi[i] && *last_global_midi[i] )
			*last_global_midi[i]=NULL;

		liegende_tasten_max[i] = 0;

		for (int j = 0; j < MAX_BREITE; j++)
			pattern[i].tonigkeit[j] = 0;

//9    tonsystem[i] = tonsystem_memory + i;
		tonsystem[i] = &(tonsystem_memory[i]);

		keys_changed[i] = 0;
	}

	keys_changed_sum = 0;

	freies_tonsystem = &(tonsystem_memory[MAX_BOX]);
}

// forwards
void update_pattern(int instr);
void change_breite(int instr, int neu);
void change_anker(int instr, int neu);
void keyboard_analyse( int taste );
void HarmonyAnalysis(int box, PATTERNN * pattern );

void execute_aktion (int instrument, struct do_aktion * aktion)
{
	bool WasNewLogic = false;

	for ( ; aktion; aktion = aktion -> next)
	{
		AktionenMessage(instrument, aktion->name);

		switch (aktion->aufruf_typ) {

		case aufruf_logik:
			execute_aktion (instrument, aktion->u.aufruf_logik.einstimmung);

			* last_global_keyboard[instrument] =
			        * aktion->u.aufruf_logik.lokal_keyboard;

			* last_global_harmonie[instrument] =
			        * aktion->u.aufruf_logik.lokal_harmonie;

			* last_global_midi[instrument] =
			        * aktion->u.aufruf_logik.lokal_midi;

			WasNewLogic = true;

			break;

		case aufruf_tonsystem:
			* tonsystem[instrument] =
			        * aktion->u.aufruf_tonsystem.tonsystem;

			update_pattern(instrument);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);

#endif
			KEY_CHANGED(instrument);

			break;

		case aufruf_umst_taste_abs:
			change_anker(instrument,
			             aktion->u.aufruf_umst_taste_abs.wert[instrument]);

			update_pattern(instrument);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);

#endif
			KEY_CHANGED(instrument);

			break;

		case aufruf_umst_breite_abs:
			change_breite(instrument,
			              aktion->u.aufruf_umst_breite_abs.wert[instrument]);

			update_pattern(instrument);

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);

#endif
			KEY_CHANGED(instrument);

			break;

		case aufruf_umst_wiederholung_abs:
			tonsystem[instrument]->periode =
			        aktion->u.aufruf_umst_wiederholung_abs.faktor;

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);

#endif
			KEY_CHANGED(instrument);

			break;

		case aufruf_umst_wiederholung_rel:
			tonsystem[instrument]->periode +=
			        aktion->u.aufruf_umst_wiederholung_rel.faktor;

#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);

#endif
			KEY_CHANGED(instrument);

			break;

		case aufruf_umst_taste_rel: {
			int help;
			help = tonsystem[instrument]->anker;

			switch (aktion->u.aufruf_umst_taste_rel.rechenzeichen) {

			case '+':
				help += aktion->u.aufruf_umst_taste_rel.wert[instrument];

				break;

			case '-':
				help -= aktion->u.aufruf_umst_taste_rel.wert[instrument];

				break;
			}

			change_anker(instrument, help);

			update_pattern(instrument);
#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);
#endif
			KEY_CHANGED(instrument);
		}

		break;

		case aufruf_umst_breite_rel: {
			int help;
			help = tonsystem[instrument]->breite;

			switch (aktion->u.aufruf_umst_breite_rel.rechenzeichen) {

			case '+':
				help += aktion->u.aufruf_umst_breite_rel.wert[instrument];

				break;

			case '-':
				help -= aktion->u.aufruf_umst_breite_rel.wert[instrument];

				break;

			case '*':
				help *= aktion->u.aufruf_umst_breite_rel.wert[instrument];

				break;

			case '/':
				help /= aktion->u.aufruf_umst_breite_rel.wert[instrument];

				break;
			}

			change_breite(instrument, help);

			update_pattern(instrument);
#ifdef NOTES_CORRECT_SOFORT
			NotesCorrect(instrument);
#endif
			KEY_CHANGED(instrument);
		}

		break;

		case aufruf_umst_toene_veraendert: {
			long * ton_zeiger;

			struct ton_einstell * lauf;

			for (ton_zeiger = tonsystem[instrument]->ton,
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
			NotesCorrect(instrument);

#endif
			KEY_CHANGED(instrument);
		}

		break;

		case aufruf_umst_umst_case: {

			struct case_element * lauf;
			int i;
			i=aktion->u.aufruf_umst_umst_case.wert[instrument];

			for (lauf = aktion->u.aufruf_umst_umst_case.umst_case;
			                lauf;
			                lauf = lauf->next) {
				if ( (i == lauf->case_wert) || (lauf->is_default)) {
					execute_aktion (instrument, lauf->case_aktion);
					return;
				}
			}
		}

		break;

		case aufruf_midi_out: {

			struct midiliste * lauf;
			unsigned long data = 0, faktor = 1, n = 0;
			;

			for (lauf = aktion->u.aufruf_midi_out.out_liste;
			                lauf && faktor ;
			                lauf = lauf -> next) {
				data += faktor * (unsigned char) lauf->midi_code;
				faktor *= 0x100;
				n++;
			}

			MidiOut(instrument, data, n);
		}

		break;

		case aufruf_umst_umst_bund:
			wxLogWarning(_("Unhandled case path: aufruf_umst_umst_bund"));

			break;

		default:
			wxLogError(_("Unexpected action type: %d"), aktion->aufruf_typ);
		}
	}

	// evtl gleich HArmonien checken
	if ( WasNewLogic )
		HarmonyAnalysis(instrument, &pattern[instrument]);

#ifndef NOTES_CORRECT_SOFORT
	NotesCorrect(instrument);

#endif
}

void update_pattern(int instr)
{
	PATTERNN * temp_pattern = &pattern[instr];
	ton_system * tonsys = tonsystem[instr];
	int i;

	for (i=0;i<tonsys->breite;i++) temp_pattern->tonigkeit[i]=0;

	for (i=0;i<liegende_tasten_max[instr];i++)
		(temp_pattern->tonigkeit[GET_INDEX( liegende_tasten[instr][i]
		                                    ,tonsys )])++;
}

void change_anker(int instr, int neu)
{
	ton_system * tonsys = tonsystem[instr];
	ton_system * temp = tonsys;
	int i;
	laufzeit_zentrum[instr]-=neu-tonsys->anker;

	while ( laufzeit_zentrum[instr] < 0 )
		laufzeit_zentrum[instr] += tonsys->breite;

	laufzeit_zentrum[instr]%=tonsys->breite;

	while (neu<36)
		neu += tonsys->breite;

	while (neu>96)
		neu -= tonsys->breite;

	freies_tonsystem->ton[0]=GET_FREQ(neu,tonsys);

	for (i=1; i<tonsys->breite; i++)
		freies_tonsystem->ton[i] =
		        freies_tonsystem->ton[0] + tonsys->ton[i]-tonsys->ton[0];

	freies_tonsystem->anker=neu;

	freies_tonsystem->breite=tonsys->breite;

	freies_tonsystem->periode=tonsys->periode;

	tonsystem[instr]=freies_tonsystem;

	freies_tonsystem=temp;
}

void change_breite(int instr, int neu)
{
	ton_system * tonsys = tonsystem[instr];
	int i;

	if ( neu>0 && neu < MAX_BREITE ) {
		if ( neu > tonsys->breite )
			for (i = tonsys->breite; i < neu; i++)
				tonsys->ton[i]=GET_FREQ((tonsys->anker+i),tonsys);

		tonsys->periode =
		        GET_FREQ(tonsys->anker+neu,tonsys) - GET_FREQ(tonsys->anker,tonsys);

		tonsys->breite=neu;
	}
}

// ermittelt die tiefste liegende Taste bei instr
int tiefste_taste(int instr)
{
	int i, min = 9999;

	for (i = 0; i < liegende_tasten_max[instr]; i++)
		if ( liegende_tasten[instr][i] < min )
			min = liegende_tasten[instr][i];

	return min;
}

// ermittelt die hˆchste liegende Taste bei instr
int hoechste_taste(int instr)
{
	int i, max = 0;

	for (i = 0; i<liegende_tasten_max[instr]; i++)
		if ( liegende_tasten[instr][i] > max )
			max = liegende_tasten[instr][i];

	return max;
}

// vergleicht zwei PATTERNNs der Breite breite und beginnt mit dem Vergleich
// indexversetzt ab startindex (wg. Harmonieformanalyse)
int compare_harmonie(int breite, int startindex, PATTERNN * laufzeit, PATTERNN * vergleich)
{
	int i;

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
	ton_system *tonsys = tonsystem[box];
	int i;

	for (help = first_harmonie[box]; help; help=help->next ) {
		switch ( help->ist_harmonieform ) {

		case 0: // analysiere auf harmonie
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
			execute_aktion(box, help->aktion);

			break;
		}
	}
}

// die taste in box wird in die Listen (pattern, liegende_taste)	aufgenommen
void AddKey( int box, int taste, int id)
{
	liegende_tasten[box][liegende_tasten_max[box]++] = taste;
	pattern[box].tonigkeit[GET_INDEX(taste,tonsystem[box])]++;
	last_note_id[box] = (id << 16) + (box << 8) + taste;
	HarmonyAnalysis(box, &pattern[box]);
	last_note_id[box] = 0;
	KEY_CHANGED(box);
}

// die taste in box wird aus den Listen (pattern, liegende_taste)	gestrichen */
void DeleteKey( int box, int taste, int id)
{
	for (int i=0; i<liegende_tasten_max[box]; i++)
		if ( liegende_tasten[box][i] == taste ) {
			liegende_tasten[box][i] =
			        liegende_tasten[box][--liegende_tasten_max[box]];
			pattern[box].tonigkeit[GET_INDEX(taste,tonsystem[box])]--;
			last_note_id[box] = (id << 16) + (box << 8) +  taste;
			HarmonyAnalysis(box, &pattern[box]);
			last_note_id[box] = 0;
			KEY_CHANGED(box);
			break;
		}
}

void KeyboardIn(int box, const mutChar *keys)
{
	aktuelles_keyboard_instrument = box;
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

	for (struct keyboard_ereignis *help = first_keyboard[box]; help ; help=help->next)
		if ( toupper(taste)==help->taste && isLogic == ( help->the_logik_to_expand != NULL ) ) {
			execute_aktion(box, help->aktion);
			return;
		}
}

void keyboard_analyse( int taste )
{
	KeyboardAnalyseSimple(aktuelles_keyboard_instrument, taste);
}

void pascal _export KeyboardAnalyseSimple(int box, int taste)
{

	for (struct keyboard_ereignis *help = first_keyboard[box]; help ; help=help->next)
		if ( toupper(taste)==help->taste ) {
			execute_aktion(box, help->aktion);
			return;
		}
}

/************ Protokoll - Funktionen ****************/

void protokoll_aktuelles_tonsystem( int instr )
{
	ton_system * tonsys = tonsystem[instr];
	long freq;
	unsigned char * zugriff = (unsigned char*) & freq;
	int i;
	init_laufzeit_protokoll();
//  laufzeit_protokoll("Tonsystem: (#%d)",instr);
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
void protokoll_liegende_frequenzen( int instr )
{
	ton_system * tonsys = tonsystem[instr];
	int i, imax, lts[64], lt;
	long freq;
	unsigned char * zugriff = (unsigned char*) & freq;
	imax = liegende_tasten_max[instr];
	bcopy(liegende_tasten[instr], lts, imax*sizeof(int));
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
			                   (zugriff[3]+(((float)zugriff[2])/256.0)), GetChannel(instr, lt));
#endif
		} else {
			laufzeit_protokoll("%2d : %%",lt);
		}
	}

	exit_laufzeit_protokoll();
}

void protokoll_aktuelle_relationen( int instr )
{
	ton_system * tonsys = tonsystem[instr];
	int i,j;
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

void protokoll_liegende_relationen( int instr )
{
	ton_system * tonsys = tonsystem[instr];
	int i;
	init_laufzeit_protokoll();
//  laufzeit_protokoll("Liegende Relationen (#%d):",instr);

	for (i=0;i<(liegende_tasten_max[instr]-1);i++) {
		if ( (GET_FREQ( liegende_tasten[instr][i+1] , tonsys )) !=0 ) {
			laufzeit_protokoll("%.2f cent",
			                   LONG_TO_CENT( GET_FREQ(liegende_tasten[instr][i+1], tonsys ) -
			                                 GET_FREQ(liegende_tasten[instr][i], tonsys) ));
		} else {
			laufzeit_protokoll("  %%");
		}
	}

	exit_laufzeit_protokoll( );
}



void FlushUpdateUI()
{
	if ( keys_changed_sum && updateUIcallback ) {
		keys_changed_sum = 0;
		updateUIcallback();
	}
}

