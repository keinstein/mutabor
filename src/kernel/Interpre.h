/** \file 
 ********************************************************************
 * Interpreter for the logic at runtime.
 *
 * Copyright:   (c) 1997-2011 TU Dresden
 * \author  R.Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.9 $
 * \license GPL
 *

 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_INTERPRE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_INTERPRE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_INTERPRE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Global.h"

#ifndef MU32_INTERPRE_H_PRECOMPILED
#define MU32_INTERPRE_H_PRECOMPILED

// system headers which do seldom change


/* Zur Umrechnung in die Midi-Darstellung
   als Gleitpunktzahl in long.
   Erstes Byte Vorkommastellen, drei Bytes Nachkommastellen. */
#define DOUBLE_TO_LONG(x) ((long int) ((x) * (1L<<24)))

void message_tasten_liste( void );

/* Datenstrukturen: */

typedef struct TSYS
{
	int anker;
	int breite;
	long periode;
	long ton[MUTABOR_KEYRANGE_MAX_WIDTH];
} tone_system;

typedef struct PTRN
{
	int tonigkeit[MUTABOR_KEYRANGE_MAX_WIDTH];
} PATTERNN;

/*****************************
struct midiereignis { struct midiereignis * next;
                      int * first;
                      int * scanpos;
                      void (*aufruf)();
                      const char * name;
};

struct keyboardereignis { int taste;
                          struct keyboardereignis * next;
                          void (*aufruf)();
                          const char * name;
};

struct harmonieereignis { PATTERNN * pattern;
                          int ist_harmonieform;
                          int vortaste;
                          int nachtaste;
                          struct harmonieereignis * next;
                          void (*aufruf)();
                          const char * name;
};

********************/



/* Funktionsprototypen: */

void HARMONIE_analyse(int instr,PATTERNN * pattern);
void MIDI_analyse( int code );
void KEYB_analyse( int key );
void MAUS_analyse(int mx, int my);

void Add_Key(int instr, int key, int velo);
void Delete_Key(int instr, int key);

tone_system * lz_get_tonsystem(int instr);
PATTERNN * get_pattern(int instr);


/* Standardstrukturen zur Laufzeit f〉 den Interpreter */


enum ton_einstell_typ { einstell_stumm, einstell_gleich,
                        einstell_absolut, einstell_relativ };

struct ton_einstell
{
	enum ton_einstell_typ ton_einstell_typ;
	union {
		struct {
			long wert;
		} einstell_absolut;

		struct {
			long wert;
		} einstell_relativ;
	} u;
	struct ton_einstell * next;
};

struct case_element
{
	int case_wert;
	char is_default;
	struct do_aktion * case_aktion;
	struct case_element * next;
};


struct interpreter_parameter_list
{
	int * value_field;
	struct interpreter_parameter_list * next;
};



/*
typedef int * parameter_liste[16];
*/

enum aufruf_typ { aufruf_logik, aufruf_tonsystem,
                  aufruf_umst_taste_abs, aufruf_umst_breite_abs,
                  aufruf_umst_wiederholung_abs,
                  aufruf_umst_wiederholung_rel,
                  aufruf_umst_taste_rel,
                  aufruf_umst_breite_rel, aufruf_umst_toene_veraendert,
                  aufruf_umst_umst_bund, aufruf_umst_umst_case,
                  aufruf_midi_out };

struct do_aktion
{
	/*
	    parameter_liste * parameter;
	*/

	const char * name;
	enum aufruf_typ aufruf_typ;

	union
	{
		struct {
			struct do_aktion * einstimmung;
			struct harmonie_ereignis ** lokal_harmonie;
			struct keyboard_ereignis ** lokal_keyboard;
			struct midi_ereignis     ** lokal_midi;
		} aufruf_logik;

		struct {
			tone_system * tonsystem;
		} aufruf_tonsystem;

		struct {
			int * keynr;
		} aufruf_umst_taste_abs;

		struct {
			int * width;
		} aufruf_umst_breite_abs;

		struct {
			long faktor;
		} aufruf_umst_wiederholung_abs;

		struct {
			long faktor;
		} aufruf_umst_wiederholung_rel;

		struct {
			int * distance;
			char rechenzeichen;
		} aufruf_umst_taste_rel;

		struct {
			int * difference;
			char rechenzeichen;
		} aufruf_umst_breite_rel;

		struct {

			struct ton_einstell * tonliste;
		} aufruf_umst_toene_veraendert;

#if 0 
		struct {
		} aufruf_umst_umst_bund;
#endif

		struct {
			int * choice;
			struct case_element * umst_case;
		} aufruf_umst_umst_case;

		struct {
			struct midiliste * out_liste;
		} aufruf_midi_out;
	} u;
	struct do_aktion * next;
};



struct midi_ereignis
{
	int * first_pos;
	int * scan_pos;
	const char * name;
	struct do_aktion * aktion;
	struct logik * the_logik_to_expand;
	struct midi_ereignis * next;
};

struct keyboard_ereignis
{
	char taste;
	const char * name;
	struct do_aktion * aktion;
	struct logik * the_logik_to_expand;
	struct keyboard_ereignis * next;
};

struct harmonie_ereignis
{
	PATTERNN * pattern;
	char ist_harmonieform;
	int vortaste;
	int nachtaste;

	const char * name;
	struct do_aktion * aktion;
	struct logik * the_logik_to_expand;
	struct harmonie_ereignis * next;
};





extern int laufzeit_meldungen_erlaubt; /* Hier gibt es 2 Level:

                                          0=keine Meldungen,
                                          1=normale Meldungen */



/* moved to box.h 
int liegende_tasten[MAX_BOX][64];
int liegende_tasten_max[MAX_BOX];
long last_note_id[MAX_BOX];           // unused
int laufzeit_abstand[MAX_BOX];
int laufzeit_zentrum[MAX_BOX];
*/


#define SYNTHESIZER_TYP_KEINER    0
#define SYNTHESIZER_TYP_FB01      1
#define SYNTHESIZER_TYP_MULTI16   2
#define SYNTHESIZER_TYP_GIS       3
/* jedem Kanal seinen Synthesizer */

#endif /* precompiled */
#endif



///\}
