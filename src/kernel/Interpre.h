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

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

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

enum interpreter_parameter_indices {
	interpreter_parameter_distance = 0,
	interpreter_parameter_anchor,
	interpreter_parameter_first_parameter
};

struct interpreter_parameter_list
{
	size_t size; /**< size of the allocated memory */
	int * data;  /**< data fields */
	struct interpreter_parameter_list * next; /**< possibly next element */
};

union interpreter_argument {
	size_t index;
	int constant;
};

struct interpreter_argument_list
{
	size_t size;
	union interpreter_argument * data;
	enum argument_typ * types;
};
	

/*
typedef int * parameter_liste[16];
*/

enum aufruf_typ { aufruf_logik, aufruf_tonsystem,
                  aufruf_umst_taste_abs, 
		  aufruf_umst_breite_abs,
                  aufruf_umst_wiederholung_abs,
                  aufruf_umst_wiederholung_rel,
                  aufruf_umst_taste_rel,
                  aufruf_umst_breite_rel, 
		  aufruf_umst_toene_veraendert,
                  aufruf_umst_umst_bund, 
		  aufruf_umst_umst_case,
                  aufruf_midi_out,
		  aufruf_harmony_analysis
};

struct do_aktion
{
	/*
	    parameter_liste * parameter;
	*/

	const char * name;
	enum aufruf_typ aufruf_typ;
        struct interpreter_argument_list * arguments;

        union {
	    struct logik * logic;
	    struct umstimmung * retuning;
	} calling;

	union
	{
#if 0 
	    /* logic is handled in colling */
		struct {
		    struct logik * logic;
		/*
			  each list is stored only once
			  struct harmonie_ereignis ** lokal_harmonie;
			  struct keyboard_ereignis ** lokal_keyboard;
			  struct midi_ereignis     ** lokal_midi;
			*/
		} aufruf_logik;
#endif

		struct {
			tone_system * tonsystem;
		} aufruf_tonsystem;

#if 0
	    /* first argument */
	    struct {
		int * keynr;
	    } aufruf_umst_taste_abs;

	    /* first argument */
		struct {
			int * width;
		} aufruf_umst_breite_abs;
#endif

		struct {
			long faktor;
		} aufruf_umst_wiederholung_abs;

		struct {
			long faktor;
		} aufruf_umst_wiederholung_rel;

		struct {
#if 0
		    /* first argument */
			int * distance;
#endif
			char rechenzeichen;
		} aufruf_umst_taste_rel;

		struct {
#if 0
		    /* first argument */
			int * difference;
#endif
			char rechenzeichen;
		} aufruf_umst_breite_rel;
		struct {

			struct ton_einstell * tonliste;
		} aufruf_umst_toene_veraendert;

#if 0 
		// currently no data fields
		struct {
		} aufruf_umst_umst_bund;
#endif

		struct {
#if 0
		    // first argument
		    int * choice;
#endif
			struct case_element * umst_case;
		} aufruf_umst_umst_case;

		struct {
			struct midiliste * out_liste;
		} aufruf_midi_out;
#if 0
		struct {
		} aufruf_harmony_analysis;
#endif 
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

enum is_harmonic_form_collection {
	mutabor_is_no_harmonic_form = 0,
	mutabor_is_harmonic_form = 1,
	mutabor_is_else_path = 2
};

struct harmonie_ereignis
{
	PATTERNN * pattern;
	enum is_harmonic_form_collection ist_harmonieform;
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

#ifdef __cplusplus
		}
	}
}
#endif

#endif /* precompiled */
#endif



///\}
