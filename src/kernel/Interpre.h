/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Interpre.h,v 1.9 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: Interpre.h,v $
 * Revision 1.9  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.8  2011-07-27 20:48:32  keinstein
 * started to move arrays using MAX_BOX into struct mutabor_box_type
 *
 * Revision 1.7  2011-03-06 13:15:41  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.6  2011-02-20 22:35:55  keinstein
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
// Mutabor 2.win, 1997, R.Krauﬂe
// Interpretation der Logiken zur Laufzeit
// ------------------------------------------------------------------

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
	long ton[MAX_BREITE];
} tone_system;

typedef struct PTRN
{
	int tonigkeit[MAX_BREITE];
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


/* Standardstrukturen zur Laufzeit fÅr den Interpreter */


enum ton_einstell_typ { einstell_stumm, einstell_gleich,
                        einstell_absolut, einstell_relativ };

struct ton_einstell
{
	enum ton_einstell_typ ton_einstell_typ;
	union {

		struct {
			long wert;
		}

		einstell_absolut;

		struct {
			long wert;
		}

		einstell_relativ;
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


struct interpreter_parameter_liste
{
	int (* werte_feld) [MAX_BOX];

	struct interpreter_parameter_liste * next;
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
		}

		aufruf_logik;

		struct {
			tone_system * tonsystem;
		}

		aufruf_tonsystem;

		struct {
			int * wert;
		}

		aufruf_umst_taste_abs;

		struct {
			int * wert;
		}

		aufruf_umst_breite_abs;

		struct {
			long faktor;
		}

		aufruf_umst_wiederholung_abs;

		struct {
			long faktor;
		}

		aufruf_umst_wiederholung_rel;

		struct {
			int * wert;
			char rechenzeichen;
		}

		aufruf_umst_taste_rel;

		struct {
			int * wert;
			char rechenzeichen;
		}

		aufruf_umst_breite_rel;

		struct {

			struct ton_einstell * tonliste;
		}

		aufruf_umst_toene_veraendert;

		struct {
			int * wert;

			struct case_element * umst_case;
		}

		aufruf_umst_umst_case;

		struct {

			struct midiliste * out_liste;
		}

		aufruf_midi_out;
	}

	u;

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




/* Globale Listen: */

extern struct harmonie_ereignis *  first_harmonie[MAX_BOX];

extern struct harmonie_ereignis ** last_global_harmonie[MAX_BOX];

extern struct harmonie_ereignis ** first_lokal_harmonie;

extern struct keyboard_ereignis *  first_keyboard[MAX_BOX];

extern struct keyboard_ereignis ** last_global_keyboard[MAX_BOX];

extern struct keyboard_ereignis ** first_lokal_keyboard;

extern struct midi_ereignis     *  first_midi[MAX_BOX];

extern struct midi_ereignis     ** last_global_midi[MAX_BOX];

extern struct midi_ereignis     ** first_lokal_midi;

extern int laufzeit_abstand[256];

extern int laufzeit_zentrum[256];

extern int laufzeit_meldungen_erlaubt; /* Hier gibt es 2 Level:

                                          0=keine Meldungen,
                                          1=normale Meldungen */

extern int aktuelle_keyboard_box;

extern int liegende_tasten[MAX_BOX][64];

extern int liegende_tasten_max[MAX_BOX];

#define SYNTHESIZER_TYP_KEINER    0
#define SYNTHESIZER_TYP_FB01      1
#define SYNTHESIZER_TYP_MULTI16   2
#define SYNTHESIZER_TYP_GIS       3
/* jedem Kanal seinen Synthesizer */

#endif /* precompiled */
#endif



///\}
