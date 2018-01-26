/** \file
 ********************************************************************
 * Interpreter for the logic at runtime.
 *
 * Copyright:   (c) 1997-2011 TU Dresden
 * \author  R.Krauße
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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

/* --------------------------------------------------------------------------- */
/* headers */
/* --------------------------------------------------------------------------- */

#include "Defs.h"
#include "MidiKern.h"
#include "Global.h"

#ifndef MU32_INTERPRE_H_PRECOMPILED
#define MU32_INTERPRE_H_PRECOMPILED


/* system headers which do seldom change */
#include <limits.h>


MUTABOR_NAMESPACE(mutabor)
MUTABOR_NAMESPACE(hidden)
MUTABOR_EXTERN_C

/* Zur Umrechnung in die Midi-Darstellung
   als Gleitpunktzahl in long.
   Erstes Byte Vorkommastellen, drei Bytes Nachkommastellen. */
/*#define DOUBLE_TO_LONG(x) ((long int) ((x) * (1L<<24))) */

void message_tasten_liste( void );

enum mutabor_interval_type_constants {
	mutabor_invalid_interval = 0,
	mutabor_active_interval = 1,
	mutabor_empty_interval = 2,
	mutabor_invalid_tone = 0,
	mutabor_active_tone = 1,
	mutabor_empty_tone = 2
};


/* Datenstrukturen: */
typedef struct MUT_INTERVAL {
	enum mutabor_interval_type_constants active;
	mutint64 value;
} mutabor_interval;
			/*typedef long mutabor_interval; */
typedef mutabor_interval mutabor_tone;

typedef struct TSYS
{
	int anker;
	int breite;
	mutabor_interval periode;
	mutabor_tone ton[MUTABOR_KEYRANGE_MAX_WIDTH];
} tone_system;


/**
 * Check whether an interval has a defined value or is empty.
 *
 * \param interval interval to be checkd.
 *
 * \return true if the interval is not set or empty.
 */
inline enum mutabor_interval_type_constants
mutabor_get_interval_type(mutabor_interval interval) {
	return interval.active;
}
inline  enum mutabor_interval_type_constants
mutabor_get_tone_type(mutabor_tone tone) {
	return tone.active;
}

inline void mutabor_invalidate_interval(mutabor_interval *interval) {
	if (interval) interval->active = mutabor_invalid_interval;
}

inline void mutabor_invalidate_tone(mutabor_tone *tone) {
	if (tone) tone->active = mutabor_invalid_tone;
}
inline void mutabor_clear_interval(mutabor_interval *interval) {
	if (interval) interval->active = mutabor_empty_interval;
}

inline void mutabor_clear_tone(mutabor_tone *tone) {
	if (tone) tone->active = mutabor_empty_tone;
}

/**
 * Convert an interval to half tone based pitch according to MIDI pitch numbers.
 * The microtonal part is retained in the double return value.
 *
 * \param interval Interval in the internal representation of Mutabor.
 *
 * \return a double value that represents the interval.
 *         a half tone is represented as 1.00, and an octave as 12.00.
 */
static inline double mutabor_convert_interval_to_factor(mutabor_interval interval)
{
	switch(mutabor_get_interval_type(interval)) {
	case mutabor_empty_interval:
		return 0;
	case mutabor_invalid_interval:
		return -1;
	case mutabor_active_interval:
		return mutabor_convert_pitch_to_factor(((double) interval.value ) / (double) (0x01000000));
	default:
		UNREACHABLE;
		return -100;
	}
}

/**
 * Convert an interval from a frequecy factor.
 * The microtonal part can be given in the double value.
 *
 * \param interval a double value that represents the interval.
 *         a semitone is represented as 1.00, and an octave as 12.00
 *
 * \return interval in the internal representation of Mutabor.
 */
inline mutabor_interval mutabor_convert_factor_to_interval(double interval)
{
	mutabor_interval retval;
	retval.active = (interval > -1
			 ? (interval > 0
			    ? mutabor_active_interval
			    : mutabor_empty_interval)
			 : mutabor_invalid_interval);
	retval.value = (mutint64)(mutabor_convert_factor_to_pitch(interval ) * (double) (0x01000000));
	return retval;
}


/**
 * Convert an interval from half tone based pitch according to MIDI pitch numbers.
 * The microtonal part can be given in the double value.
 *
 * \param interval a double value that represents the interval.
 *         a semitone is represented as 1.00, and an octave as 12.00
 *
 * \return interval in the internal representation of Mutabor.
 *
 * \note The resulting interval is always a valid non-nil interval.
 */
inline mutabor_interval mutabor_get_interval_from_pitch(double pitch)
{
	mutabor_interval retval;
	retval.active = mutabor_active_interval;
	retval.value  = (mutint64)(pitch * (double) (0x01000000));
	return retval;
}

/**
 * Convert an interval from half tone based pitch according to MIDI pitch numbers.
 * The microtonal part can be given in the double value.
 *
 * \param interval in the internal representation of Mutabor.
 *
 * \return  a double value that represents the interval.
 *         a semitone is represented as 1.00, and an octave as 12.00
 *
 * \note The resulting interval is always a valid non-nil interval.
 */
inline double mutabor_get_pitch_from_interval(mutabor_interval interval)
{
	return (interval.value / (double) (0x01000000));
}

/**
 * Convert a tone to half tone based pitch according to MIDI pitch numbers.
 * The microtonal part is retained in the double return value.
 *
 * \param interval Interval in the internal representation of Mutabor.
 *
 * \return a double value that represents the tone a' is represented as 69.00
 */
static inline double mutabor_convert_tone_to_factor(mutabor_tone tone)
{
	return 0.0 + mutabor_convert_interval_to_factor(tone /* - 0 */);
}

/**
 * Convert a tone from half tone based pitch according to MIDI pitch numbers.
 * The microtonal part can be given in the double value.
 *
 * \param tone a double value that represents the tone.
 *         a' is represented as 69.00
 *
 * \return tone in the internal representation of Mutabor.
 */
inline mutabor_tone mutabor_convert_factor_to_tone(double tone)
{
	return /* 0 + */ mutabor_convert_factor_to_interval(tone /* - 0 */);
}

/**
 * Convert a tone from half tone based pitch according to MIDI pitch numbers.
 * The microtonal part can be given in the double value.
 *
 * \param frequency a double value that represents the tone.
 *         a' is represented as 440.00
 *
 * \return tone in the internal representation of Mutabor.
 */
inline mutabor_tone mutabor_convert_frequency_to_tone(double frequency)
{
	mutabor_interval retval;
	retval.active = (frequency > -1
			 ? (frequency > 0
			    ? mutabor_active_tone
			    : mutabor_empty_tone)
			 : mutabor_invalid_tone);
	retval.value  = (mutint64)(mutabor_convert_frequency_to_pitch(frequency ) * (double) (0x01000000));
	return retval;
}

/**
 * Convert an tone from half tone based pitch according to MIDI pitch numbers.
 * The microtonal part can be given in the double value.
 *
 * \param tone a double value that represents the interval.
 *         a semitone is represented as 1.00, and an octave as 12.00
 *
 * \return tone in the internal representation of Mutabor.
 *
 * \note The resulting interval is always a valid non-nil interval.
 */
inline mutabor_tone mutabor_get_tone_from_pitch(double pitch)
{
	mutabor_tone retval;
	retval.active = mutabor_active_tone;
	retval.value  = (mutint64)(pitch * (double) (0x01000000));
	return retval;
}

/**
 * Convert an tone from half tone based pitch according to MIDI pitch numbers.
 * The microtonal part can be given in the double value.
 *
 * \param tone in the internal representation of Mutabor.
 *
 * \return  a double value that represents the tone.
 *         a semitone is represented as 1.00, and an octave as 12.00
 *
 * \note The resulting interval is always a valid non-nil interval.
 */
inline double mutabor_get_pitch_from_tone(mutabor_tone tone)
{
	return (tone.value / (double) (0x01000000));
}



inline mutabor_tone mutabor_add_interval_to_tone(const mutabor_tone tone,
						 int count,
						 const mutabor_interval interval) {
	mutabor_tone retval;
	retval.active = tone.active;
	retval.value  = tone.value + ((mutint64) count) * interval.value;
	switch (interval.active) {
	case mutabor_empty_interval:
		if (tone.active == mutabor_invalid_interval)
			break;
		FALLTHROUGH;
	case mutabor_invalid_interval:
		retval.active = interval.active;
		break;
	case mutabor_active_interval:
		/* do nothing */
		break;
	}
	return retval;
}

inline mutabor_interval mutabor_tone_get_interval(const mutabor_tone t1,
						  const mutabor_tone t2) {
	mutabor_interval retval;
	retval.active = t1.active;
	retval.value  = t1.value - t2.value;
	switch (t2.active) {
	case mutabor_empty_tone:
		if (t1.active == mutabor_invalid_tone)
			break;
		FALLTHROUGH;
	case mutabor_invalid_tone:
		retval.active = t2.active;
		break;
	case mutabor_active_tone:
		/* do nothing */
		;
	}
	return retval;
}


inline mutabor_interval mutabor_add_intervals(const mutabor_interval interval1,
						 int count,
						 const mutabor_interval interval2) {
	mutabor_interval retval;
	retval.active = interval1.active;
	retval.value  = interval1.value + ((mutint64) count) * interval2.value;
	switch (interval2.active) {
	case mutabor_empty_interval:
		if (interval1.active == mutabor_invalid_interval)
			break;
		FALLTHROUGH;
	case mutabor_invalid_interval:
		retval.active = interval2.active;
		break;
	case mutabor_active_interval:
		/* do nothing */
		;
	}
	return retval;
}
/**
 * Add the distance of t1 - t2 to offset. This function transfers the
 * interval between two tones to two other tones.
 *
 * \param offset    new base tone
 * \param t1        old tone
 * \param t2        old base tone
 *
 * \return offset + (t1 - t2)
 */
inline mutabor_tone mutabor_tone_copy_distance(const mutabor_tone offset,
					       const mutabor_tone t1,
					       const mutabor_tone t2) {
	mutabor_tone retval;
	if (offset.active == mutabor_invalid_tone ||
	    t1.active == mutabor_invalid_tone ||
	    t2.active == mutabor_invalid_tone)
		retval.active = mutabor_invalid_tone;
	else if (offset.active == mutabor_empty_tone ||
		 t1.active == mutabor_empty_tone ||
		 t2.active == mutabor_empty_tone)
		retval.active = mutabor_empty_tone;
	else if (offset.active == mutabor_active_tone &&
		 t1.active == mutabor_active_tone &&
		 t2.active == mutabor_active_tone)
		retval.active = mutabor_active_tone;
	else
		retval.active = mutabor_invalid_tone;
	retval.value = offset.value + (t1.value - t2.value);
	return retval;
}

inline int mutabor_get_note_index(int note, tone_system * system) {
	int retval;
	if (!system) return INT_MIN;
	retval = (note - system->anker) % system->breite;
	if (retval < 0)  retval += system->breite;
	mutASSERT(0 <= retval);
	mutASSERT(retval < system->breite);
	return retval;
}

inline int mutabor_get_note_distance(int note, tone_system * system) {
	int delta, retval;
	if (!system) return INT_MIN;
	delta = (note - system->anker);
	retval = delta / system->breite;
	if (retval * system->breite > delta) 
		retval -= 1;
	mutASSERT(system -> anker + retval * system -> breite <= note);
	mutASSERT(system -> anker + (retval + 1) * system -> breite > note);
	return retval;
}

inline mutabor_interval mutabor_get_note_frequency(int note, tone_system * system) {
	int index = mutabor_get_note_index(note, system);
	if (index >= 0)
		return mutabor_add_interval_to_tone(system->ton[index],
						    mutabor_get_note_distance(note,system),
						    system->periode);
	else {
		mutabor_interval retval;
		mutabor_clear_interval(&retval);
		return retval;
	}
}


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


enum ton_einstell_typ {
	einstell_stumm,
	einstell_gleich,
	einstell_absolut,
	einstell_relativ
};

struct ton_einstell
{
	enum ton_einstell_typ ton_einstell_typ;
	union {
		mutabor_tone     tone;
		mutabor_interval interval;
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
        struct interpreter_argument_list * arguments, /**< normal argument list */
		*secondary_arguments;            /**< arguments of the retuning */

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
			mutabor_interval interval;
		} aufruf_umst_wiederholung_abs;

		struct {
			mutabor_interval interval;
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
		/* currently no data fields */
		struct {
		} aufruf_umst_umst_bund;
#endif

		struct {
#if 0
		    /* first argument */
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
	/*	int * scan_pos; */
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
	enum harmony_type type;
	int vortaste;
	int nachtaste;

	const char * name;
	struct do_aktion * aktion;
	struct logik * the_logik_to_expand;
	struct harmonie_ereignis * next;
};






/* moved to box.h
int liegende_tasten[MAX_BOX][64];
int liegende_tasten_max[MAX_BOX];
long last_note_id[MAX_BOX];           / * unused * /
int laufzeit_abstand[MAX_BOX];
int laufzeit_zentrum[MAX_BOX];
*/


#define SYNTHESIZER_TYP_KEINER    0
#define SYNTHESIZER_TYP_FB01      1
#define SYNTHESIZER_TYP_MULTI16   2
#define SYNTHESIZER_TYP_GIS       3
/* jedem Kanal seinen Synthesizer */

MUTABOR_EXTERN_C_END
MUTABOR_NAMESPACE_END(hidden)
MUTABOR_NAMESPACE_END(mutabor)

#endif /* precompiled */
#endif



/** \} */
