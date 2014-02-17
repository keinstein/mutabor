/** \file  -*- C -*-
********************************************************************
* Calculations for the tunings depending on the box and other
* interface stuff for the C++ part
*
* Copyright:   (c) 1998-2011 TU Dresden
*              changes after 2011-11 (c) by the authors
* \author  R. Krauße,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \license GPL
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
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// Berechnungen der Stimmungen in den Boxen
// ------------------------------------------------------------------
#include "Defs.h"
#include <math.h>
#ifndef MUTWIN
#include <conio.h>
#endif

#include "src/kernel/Global.h"
#include "src/kernel/Execute.h"
#include "src/kernel/box.h"
//#include "src/kernel/GrafKern.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/Hilfs.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/Parser.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/Route-inlines.h"
#include "wx/log.h"
#include "limits.h"

#ifdef _
#undef _
#endif
#define _ _mut

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

		    const char * mutabor_error_type_to_string(mutabor_error_type type)
		    {
			switch (type) {
			case warning: return _("Warning");
			case compiler_warning: return _("Compiler warning");
			case runtime_warning: return _("Runtime warning");
			case error: return _("Error");
			case internal_error: return ("Internal error");
			case compiler_error: return ("Compiler error");
			case runtime_error: return ("Runtime error");
			default: return _("Unknown error");
			}
		    }


	static void mutabor_default_update(mutabor_box_type * box, unsigned int flags) {
		/* do nothing */
	}
	static void mutabor_default_midi_out(mutabor_box_type * box, struct midiliste * outliste) {
		/* do nothing */
	}
	static void mutabor_default_error_message(mutabor_box_type * box,
						  mutabor_error_type type,
						  const char * message)
	{
		fprintf(stderr,
			"%s: %s",
			mutabor_error_type_to_string(type),
			message);
	}
	static void mutabor_default_update_display(mutabor_box_type * box, int line_number) {
		/* do nothing */
	}
	static void mutabor_default_log_action(mutabor_box_type * box,
					       const char * action) {
		/* do nothing */
	}

	static void mutabor_default_lock(mutabor_logic_parsed * logic) {
		/* do nothing */
	}


	static struct mutabor_callback_type default_callbacks = {
		mutabor_default_update,
		mutabor_default_midi_out,
		mutabor_default_error_message,
		mutabor_default_update_display,
		mutabor_default_log_action,
		mutabor_default_lock,
		mutabor_default_lock          /* default unlock is empty if lock is empty */
	};

	mutabor_callback_type * mutabor_callbacks = & default_callbacks;

	mutabor_callback_type * mutabor_set_callbacks(mutabor_callback_type * callbacks) {
		mutabor_callback_type * old = mutabor_callbacks;
		mutabor_callbacks = callbacks;
		return old;
	}
	mutabor_callback_type * mutabor_get_callbacks() {
		return mutabor_callbacks;
	}


#if 0
			int protokollfunktionen_aktiv=0;
			int protokollfunktion_aktionsausgabe=0;
	int zeige_aktuelles_tonsystem=0;
#endif


	//#define KEY_WATCH  //protokoll in keys_changed // alte Vaiante

	// if no protocol wanted, set this macro to empty
#define KEY_CHANGED(box) mutabor_update(box, mutabor_keys_changed);


	//tone_system tonesystem_memory[MAX_BOX+1];  /* save memory for extra data */



	/* moved to box.h
	   int liegende_tasten[MAX_BOX][64];
	   int liegende_tasten_max[MAX_BOX];
	   long last_note_id[MAX_BOX];           //
	   int laufzeit_abstand[MAX_BOX]; // distance
	   int laufzeit_zentrum[MAX_BOX]; // anchor
	*/
#if 0
	inline long GET_FREQ(int key,tone_system * tonsystem) {
		mutASSERT(tonsystem);
		size_t index = GET_INDEX(key,tonsystem);
		if (tonsystem->ton[index]==0)
			return 0;
		return tonsystem->periode
			* GET_ABSTAND(key,(tonsystem))
			+ (tonsystem)->ton[index];
	}
#endif


	//char tempstring[255];


	/**
	 * Reset boxes.
	 *
	 */

	// forwards
	void update_pattern(mutabor_box_type  * box);
	void change_breite(mutabor_box_type * box, int neu);
	void change_anker(mutabor_box_type * box, int neu);
	void keyboard_analyse( int taste );
	void HarmonyAnalysis(mutabor_box_type * box, PATTERNN * pattern );

#if 0
	void mutabor_reset_action_trace(mutabor_box_type * box) {
		while (box->protocol != NULL) {
			struct action_protocol * tmp = box->protocol;
			box->pro1tocol = box->protocol->next;
			free(tmp);
		}
	}
#endif
void execute_aktion (mutabor_box_type * box,
		     struct do_aktion * aktion,
		     struct interpreter_parameter_list * parameters);

inline static void call_actions (mutabor_box_type * box,
				 struct do_aktion * aktion_list,
				 struct interpreter_parameter_list * parameters) {
	interpreter_parameter_list * current_parameters;
	interpreter_parameter_list * old_parameters = box->current_parameters;

	// check whether we must allocate memory
	if ((box->current_parameters == NULL && box->parameters == NULL)
	    || box->current_parameters->next == NULL) {
		current_parameters = (struct interpreter_parameter_list *)
			ymalloc(box,sizeof(struct interpreter_parameter_list));
		current_parameters->next = NULL;
		current_parameters->data = (int *)ycalloc(box,
							  box->file->parameter_count,
							  sizeof(int));
		if (box->parameters == NULL) {
			mutASSERT(box->current_parameters == NULL);
			box->current_parameters =
				box->parameters = current_parameters;
		} else {
			box->current_parameters->next = current_parameters;
		}

	}
	// we have a free parameter list
	else if ( box->current_parameters == NULL) {
		current_parameters = box->current_parameters = box->parameters;
	} else {
		current_parameters = box->current_parameters -> next;
		box->current_parameters = current_parameters;
	}
	for (struct do_aktion * aktion = aktion_list ;
	     aktion; aktion = aktion -> next) {
		interpreter_argument_list * arguments =
			aktion -> secondary_arguments ?
			aktion -> secondary_arguments :
			aktion -> arguments;
		size_t size;
		if (arguments == NULL) {
			execute_aktion (box, aktion, NULL);
			continue;
		}
		size = arguments->size;
		current_parameters -> size = size;
		mutASSERT(size <= box->file->parameter_count);
		for (size_t i = 0 ; i < size; i++) {
			switch (arguments->types[i]) {
			case mutabor_argument_integer:
				current_parameters->data[i] = arguments->data[i].constant;
				break;
			case mutabor_argument_parameter:
				current_parameters->data[i]
					= parameters->data[arguments->data[i].index];
				break;
			case mutabor_argument_distance:
				current_parameters->data[i]
					= box->distance;
				break;
			case mutabor_argument_anchor:
				current_parameters->data[i]
					= box->tonesystem->anker;
				break;
			case mutabor_argument_invalid:
				current_parameters->data[i] = -1;
				mutASSERT(arguments->types[i] != mutabor_argument_invalid);
				break;
			}

		}
		execute_aktion(box,
			       aktion,
			       current_parameters);
	}
	if (old_parameters != NULL)
		box->current_parameters = old_parameters;
}

	void execute_aktion (mutabor_box_type * box,
			     struct do_aktion * aktion,
			     struct interpreter_parameter_list * parameters)
	{
#if 0
		bool WasNewLogic = false;
#endif
		char * name = NULL;
		mutASSERT(box);
		mutASSERT(box->tonesystem);
		TRACE;

		//		for ( ; aktion; aktion = aktion -> next)
			{
				switch (aktion->aufruf_typ) {
				case aufruf_logik: {
					struct logik * logic = aktion->calling.logic;
					asprintf(&name, _("%s {logic}"),aktion->name?aktion->name:"");
					TRACE;

					mutASSERT(logic);
					box->current_logic = logic;
					call_actions (box,
						      logic->einstimmung,
						      parameters);

#if 0
					mutASSERT(box->last_global_keyboard);
					mutASSERT(box->last_global_harmony);
					mutASSERT(box->last_global_midi);

					*(box->last_global_keyboard) =
						*aktion->u.aufruf_logik.lokal_keyboard;
					*(box->last_global_harmony) =
						*aktion->u.aufruf_logik.lokal_harmonie;
					*(box->last_global_midi) =
						*aktion->u.aufruf_logik.lokal_midi;

					// This is left to the logic programmer
					HarmonyAnalysis(box, &(box->pattern));
#endif

					break;
				}
				case aufruf_tonsystem:
					asprintf(&name, _("%s {tone system}"),aktion->name?aktion->name:"");
					TRACE;
					*(box -> tonesystem) =
						*aktion->u.aufruf_tonsystem.tonsystem;
					update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);
#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
					break;

				case aufruf_umst_taste_abs:
					TRACE;
					if (!parameters ||
					    parameters->size != 1 ||
					    !parameters->data) {
					    mutabor_error_message(box,
								  internal_error,
								  _("Trying to set the anchor with incompatible parameters. Please report to the MUTABOR team."));
					    break;
					}

					asprintf(&name, _("%s:%d[]"),aktion->name?aktion->name:"",parameters->data[0]);

					change_anker(box, parameters->data[0]);

					update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);
#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
					break;

				case aufruf_umst_breite_abs:
					TRACE;
					if (!parameters ||
					    parameters->size != 1 ||
					    !parameters->data) {
					    mutabor_error_message(box,
								  internal_error,
								  _("Setting tone system width with incompatible parameters. Please report to the MUTABOR team."));
					    break;
					}

					asprintf(&name, _("%s:[<< %d >>]"),aktion->name?aktion->name:"",parameters->data[0]);

					change_breite(box, parameters->data[0]);
					update_pattern(box);

#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);
#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
					break;

				case aufruf_umst_wiederholung_abs: {
					TRACE;
					mutabor_interval period =
						aktion->u.aufruf_umst_wiederholung_abs.faktor;
					asprintf(&name, _("%s:[]%f HT"),aktion->name?aktion->name:"",
							       mutabor_convert_interval_to_pitch(period));

					box->tonesystem->periode = period;

#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);

#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
				}
					break;

				case aufruf_umst_wiederholung_rel: {
					TRACE;
					mutabor_interval period =
						aktion->u.aufruf_umst_wiederholung_abs.faktor;
					asprintf(&name, _("%s:[]@+%f HT"),aktion->name?aktion->name:"",
						 mutabor_convert_interval_to_pitch(period));

					box->tonesystem->periode += period;

#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);

#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
				}
					break;

				case aufruf_umst_taste_rel: {
					int help;
					TRACE;
					if (!parameters ||
					    parameters->size != 1 ||
					    !parameters->data) {
					    mutabor_error_message(box,
								  internal_error,
								  _("Changing anchor with incompatible parameters. Please report to the MUTABOR team."));
					    break;
					}
					asprintf(&name,_("%s:@%c%d[]"),aktion->name?aktion->name:"",
						 aktion->u.aufruf_umst_taste_rel.rechenzeichen,
						 parameters->data[0]);

					help = box->tonesystem->anker;

					switch (aktion->u.aufruf_umst_taste_rel.rechenzeichen) {

					case '+':
						help += parameters->data[0];

						break;

					case '-':
						help -= parameters->data[0];

						break;
					}

					change_anker(box, help);

					update_pattern(box);
#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);
#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
				}

					break;

				case aufruf_umst_breite_rel: {
					int help;
					TRACE;
					if (!parameters ||
					    parameters->size != 1 ||
					    !parameters->data) {
					    mutabor_error_message(box,
								  internal_error,
								  _("Changing tone system width with incompatible parameters. Please report to the MUTABOR team."));
					    break;
					}
					asprintf(&name, _("%s:[<<@%c%d>>]"),
							       name,
							       aktion->u.aufruf_umst_breite_rel.rechenzeichen,
							       parameters->data[0]);
					help = box->tonesystem->breite;

					switch (aktion->u.aufruf_umst_breite_rel.rechenzeichen) {

					case '+':
						help += parameters->data[0];
						break;

					case '-':
						help -= parameters->data[0];
						break;

					case '*':
						help *= parameters->data[0];
						break;

					case '/':
						help /= parameters->data[0];
						break;
					}

					change_breite(box, help);
					update_pattern(box);
#ifdef NOTES_CORRECT_SOFORT
					NotesCorrect(box);
#endif
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
				}
					break;

				case aufruf_umst_toene_veraendert: {
					long * ton_zeiger;
					struct ton_einstell * lauf;
					TRACE;
					asprintf(&name, _("%s:[.,.,.]"),
						 aktion->name?aktion->name:"");

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
					mutabor_update(box, mutabor_keys_changed || mutabor_box_changed);
				}
					break;

				case aufruf_umst_umst_bund: {
					TRACE;

					if (aktion->name) {
						char * params, * oldparams;
						if (parameters->size)
							asprintf(&params, "%d", parameters->data[0]);
						for (int i = 1; i < parameters->size; i++) {
							oldparams = params;
							asprintf(&params, _("%s,%d"),
								 oldparams,
								 parameters->data[i]);
							free(oldparams);
						}
						asprintf(&name, "%s(%s)",aktion->name,params);
					}

					/* nothing to be done here, this is only the head (containing the name) of the compound,
					 */
					break;
					     }
				case aufruf_umst_umst_case: {
					struct case_element * lauf;
					int i;
					TRACE;
					if (!parameters ||
					    parameters->size != 1 ||
					    !parameters->data) {
					    mutabor_error_message(box,
								  internal_error,
								  _("Switching cases with incompatible parameter list. Please report to the MUTABOR team."));
					    break;
					}
					i=parameters->data[0];
					asprintf(&name, "%s { %d:", aktion->name?aktion->name:"", i);
					mutabor_log_action(box, name);

					for (lauf = aktion->u.aufruf_umst_umst_case.umst_case;
					     lauf;
					     lauf = lauf->next) {
						if ( (i == lauf->case_wert) || (lauf->is_default)) {
							call_actions (box,
								      lauf->case_aktion,
								      parameters);
							// return would break further execution
							break;
						}
					}
					name = strdup("}");
				}
					break;

				case aufruf_midi_out: {
					char * parameters, * oldparameters;
					struct midiliste * i = aktion->u.aufruf_midi_out.out_liste;
					if (i) {
						asprintf(&parameters,"%x",i->midi_code);
						i = i->next;
					} else parameters = NULL;
					for (; i ;  i = i->next) {
						oldparameters = parameters;
						asprintf(&parameters, _("%s %x"),
							 oldparameters,
							 i -> midi_code);
						free(oldparameters);
					}
					if (parameters) {
						oldparameters = parameters;
						asprintf(& name,"%s: MidiOut(%s)",aktion->name?aktion->name:"",parameters);
						free(oldparameters);
					} else {
						name = strdup(aktion->name);
					}

					mutabor_midi_out(box, aktion->u.aufruf_midi_out.out_liste);
				}
					break;

				case aufruf_harmony_analysis:
					name=strdup("HarmonyAnalysis");
					HarmonyAnalysis(box, &(box->pattern));

				default:
					mutabor_error_message(box,
							      internal_error,
							      _("Unexpected action type: %d"), aktion->aufruf_typ);
					UNREACHABLE;
					name = strdup("???");
				}
				mutabor_log_action(box, name);
				free(name);
			}


#if 0
#ifndef NOTES_CORRECT_SOFORT
			mutabor::NotesCorrect(box);
#endif
#endif
	}

	void update_pattern(mutabor_box_type * box)
	{
		PATTERNN * temp_pattern = &(box->pattern);
		tone_system * tonsys = box->tonesystem;
		int i;
		TRACE;

		for (i=0;i<tonsys->breite;i++) temp_pattern->tonigkeit[i]=0;


		for (mutabor_note_type * key = mutabor_find_key_in_box(box,0);
		     key != NULL;
		     key = mutabor_find_key_in_box(box,key->next)) {
			(temp_pattern->tonigkeit[mutabor_get_note_index( key->number, tonsys )])++;
		}
	}

	void change_anker(mutabor_box_type * box, int neu)
	{
		tone_system * tonsys = box->tonesystem;
		tone_system * free_tonesystem =
			box->tonesystem == box->tonesystem_memory ?
			&(box->tonesystem_memory[1]) :
			&(box->tonesystem_memory[0]);
		int i;
		TRACE;
		/* update the distance parameter for logic calls */
		box->distance -= neu-tonsys->anker;

		while ( box->distance < 0 )
			box->distance += tonsys->breite;

		box->distance %= tonsys->breite;

		/* update the tone system */
		while (neu< MUTABOR_KEYRANGE_MIN_KEY)
			neu += tonsys->breite;

		while (neu> MUTABOR_KEYRANGE_MAX_KEY)
			neu -= tonsys->breite;

		free_tonesystem->ton[0]=mutabor_get_note_frequency(neu,tonsys);

		for (i=1; i<tonsys->breite; i++)
			free_tonesystem->ton[i] =
				free_tonesystem->ton[0] + tonsys->ton[i]-tonsys->ton[0];

		free_tonesystem->anker=neu;
		free_tonesystem->breite=tonsys->breite;
		free_tonesystem->periode=tonsys->periode;
		box->tonesystem = free_tonesystem;
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
				tonsys->ton[i]=mutabor_get_note_frequency((tonsys->anker+i),tonsys);
		tonsys->periode =
			mutabor_get_note_frequency(tonsys->anker+neu,tonsys) - mutabor_get_note_frequency(tonsys->anker,tonsys);
		tonsys->breite=neu;
	}

	/** return the smallest key pressed actually */
	int tiefste_taste(mutabor_box_type *  box)
	{
		size_t index = 0;
		mutabor_note_type * key;
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
		mutabor_note_type * key;
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

	inline bool local_harmony_analysis (mutabor_box_type * box,
					    struct harmonie_ereignis * trigger,
					    PATTERNN * harmony) {
		tone_system * tonesys = box->tonesystem;
		for (struct harmonie_ereignis * index = trigger;index; index=index->next) {
			switch ( index->ist_harmonieform ) {
			case mutabor_is_no_harmonic_form: // analysiere auf harmonie
				TRACE;
				if ( index->vortaste != MUTABOR_INVALID_KEY &&
				     index->vortaste != MUTABOR_NO_KEY &&
				     mutabor_get_note_index(tiefste_taste(box), tonesys) != index->vortaste ) {
					// failed
				} else {
					if ( index->nachtaste != MUTABOR_NO_KEY &&
					     index->nachtaste != MUTABOR_INVALID_KEY &&
					     mutabor_get_note_index(hoechste_taste(box),tonesys)!=index->nachtaste ) {
						// failed
					} else {
						// teste_harmonie

						if ( compare_harmonie(tonesys->breite,0,harmony,index->pattern) ) {
							// PASST !!!
							box->last_trigger.type            = any_trigger::harmony;
							box->last_trigger.harmony_trigger = index;
							call_actions(box,
								     index->aktion,
								     NULL);
							mutabor_update(box, mutabor_action_changed);
							return true;
						}
					}
				}

				break;

			case mutabor_is_harmonic_form: // analysiere auf harmonieform
				TRACE;
				for (int i=0; i<tonesys->breite; i++) {
					if (  index->vortaste != MUTABOR_INVALID_KEY &&
					      index->vortaste != MUTABOR_NO_KEY &&
					      mutabor_get_note_index(tiefste_taste(box)-i, tonesys) != index->vortaste ) {
						// failed
					} else {
						if ( index->nachtaste != MUTABOR_NO_KEY &&
						     index->nachtaste != MUTABOR_INVALID_KEY &&
					     	     mutabor_get_note_index(hoechste_taste(box)-i, tonesys) != index->nachtaste ) {
							// failed
						} else {
							// teste_harmonie

							if (compare_harmonie(tonesys->breite, i, harmony, index->pattern)) {
								// PASST !!!
								box->last_trigger.type            = any_trigger::harmony;
								box->last_trigger.harmony_trigger = index;

								box->distance = i;
								call_actions(box,
									     index->aktion,
									     NULL);
								mutabor_update (box,mutabor_action_changed);
								return true;
							}
						}
					}
				}
				break;

			case mutabor_is_else_path: // default
#warning This seems odd check, when mutabor is running
				TRACE;
				box->last_trigger.type            = any_trigger::harmony;
				box->last_trigger.harmony_trigger = index;

				call_actions(box, index->aktion, NULL);
				mutabor_update (box,mutabor_action_changed);
				return true;
			default:
				mutabor_error_message(box,
						      internal_error,
						      _("Undefined harmonic harmony class %d in HarmonyAnalysis().\n\
Please, report this error to the MUTABOR team."),
						      index->ist_harmonieform);
			}
		}
		return false;
	}


	void HarmonyAnalysis(mutabor_box_type * box, PATTERNN * pattern )
	{

		bool retval = false;
		struct harmonie_ereignis * first, * secound;

		mutASSERT(box);
		mutASSERT(box->file);

		if (!box || !box->file) {
			UNREACHABLE;
			return;
		}
		TRACE;

		if (box->flags.local_harmony_before_global) {
			first = box->current_logic != NULL?
				box->current_logic->harmony_list:
				NULL;
			secound = box->file->global_harmonies;
		} else {
			first = box->file->global_harmonies;
			secound = box->current_logic != NULL?
				box->current_logic->harmony_list:
				NULL;
		}

		retval = first != NULL ?
			local_harmony_analysis(box, first, pattern):
			false;
		if (!retval && secound)
			retval = local_harmony_analysis(box, secound, pattern);
	}


	// die taste in box wird in die Listen (pattern, liegende_taste) aufgenommen
	void AddKey( mutabor_box_type * box, int taste, size_t id, size_t channel, void * userdata)
	{
		mutabor_note_type *new_key = mutabor_create_key_in_box(box);
		new_key->number = taste;
		new_key->channel = channel;
		new_key->id = id;
		new_key->userdata = userdata;
		DEBUGLOG2(routing,_T("(key = %d, channel = %lu, id = %lu, userdata = %p)"),
			 taste,
			 (unsigned long)channel,
			 (unsigned long)id,
			 userdata);

		if (box->tonesystem && box->tonesystem != NULL) {
			box->pattern.tonigkeit[mutabor_get_note_index(taste,box->tonesystem)]++;
			HarmonyAnalysis(box, &(box->pattern));
		}
		KEY_CHANGED(box);
	}

	// die taste in box wird aus den Listen (pattern, liegende_taste) gestrichen */
	void DeleteKey( mutabor_box_type * box, int taste, size_t id, size_t channel)
	{
		size_t index=0;
		TRACE;
		mutabor_note_type * key;
		while ((key = mutabor_find_key_in_box(box,index)) != NULL) {
			if (key->number == taste && key ->id == id && key -> channel == channel)
				break;
			index = key->next;
		}

		if (key == NULL) return;
		mutabor_delete_key_in_box(box,index);
		DEBUGLOG2(routing,_T("(key = %d, channel = %lu, id = %lu)"),
			 taste,
			 (unsigned long)channel,
			 (unsigned long)id);

		if (box->tonesystem) {
			box->pattern.tonigkeit[mutabor_get_note_index(taste,box->tonesystem)]--;
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

	void KeyboardIn(mutabor_box_type * box, const char *keys)
	{
		TRACE;
		char TonSystem = 0;

		if (!keys) return;


		for (const char * ptr = keys; *ptr; ptr++) {
			char c = *ptr;

			if ( c == '&' ) {
				TonSystem = 1;
				continue;
			}

			if ( isalnum(c) )  {
				if ( TonSystem )
					KeyboardAnalyse(box, (int) c, 0);
				else
					KeyboardAnalyseSimple(box, (int) c);
			}
			TonSystem = 0;
		}
	}

	static inline bool local_midi_analysis(mutabor_box_type * box,
					       struct midi_ereignis * event,
					       const uint8_t * message,
					       size_t size)
	{
		struct midi_ereignis * index;
		int * scan_pos;
		const uint8_t * msg_pos, *msg_last = message + size;
		int current;
		if (!message || !size)
			return false;
		for (index = event;
		     index;
		     index=index->next) {
			msg_pos = message;

			for (scan_pos = index->first_pos;
			     *scan_pos != -1; ++scan_pos) {
				if (msg_pos == msg_last) break;
				current = *msg_pos;
				if ((current & 0x80) && ((current & 0xF0) != 0xF0))
					current &= 0xf0;
				if (current != *scan_pos) break;
				++msg_pos;
			}
			if (*scan_pos == -1) break;

#if 0
			/* warning: error in midi analysis: boxes must
			   not change the logic data this must be done
			   somehow else
			 */
			if ( *(index->scan_pos) != midiByte )
				index->scan_pos = index->first_pos;
			else {
				index->scan_pos++;
				if ( *(index->scan_pos) == -1 )
					break;
			}
#endif
		}

		if ( index ) {
			box->last_trigger.type = any_trigger::midi;
			box->last_trigger.midi_trigger = index;
			call_actions( box, index->aktion, NULL);
			mutabor_update(box,mutabor_action_changed);
			return true;
		}
		return false;
	}


	void MidiAnalysis(mutabor_box_type * box, const uint8_t * message, size_t size)
	{
		bool retval = false;
		struct midi_ereignis * first, * secound;

		mutASSERT(box);
		mutASSERT(box->file);

		if (!box || !box->file) {
			UNREACHABLE;
			return;
		}
		TRACE;

		if (box->flags.local_midi_before_global) {
			first = box->current_logic != NULL ?
				box->current_logic->midi_input_list:
				NULL;
			secound = box->file->global_midi_inputs;
		} else {
			first = box->file->global_midi_inputs;
			secound = box->current_logic != NULL ?
				box->current_logic->midi_input_list :
				NULL;
		}

		retval = first != NULL ?
			local_midi_analysis(box, first, message, size):
			false;
		if (!retval && secound != NULL)
			retval = local_midi_analysis(box, secound, message, size);
	}

	static inline bool local_keyboard_analysis(mutabor_box_type * box,
						   struct keyboard_ereignis * event,
						   int key,
						   char is_logic,
						   char is_simple)
	{
		for (struct keyboard_ereignis *help = event;
		     help ; help=help->next) {
			if ( toupper(key) == help->taste
			     && (is_simple
				 || is_logic == (help->the_logik_to_expand != NULL))) {
				box->last_trigger.type        = any_trigger::key;
				box->last_trigger.key_trigger = help;
				call_actions(box, help->aktion, NULL);
				mutabor_update (box,mutabor_action_changed);
				return true;
			}
		}
		return false;
	}


	static inline void generic_keyboard_analysis(mutabor_box_type * box,
						     int taste,
						     char isLogic,
						     char isSimple)
	{
		bool retval = false;
		struct keyboard_ereignis * first, * secound;

		mutASSERT(box);
		mutASSERT(box->file);

		if (!box || !box->file) {
			UNREACHABLE;
			return;
		}
		TRACE;

		if (box->flags.local_keyboard_before_global) {
			first = box->current_logic != NULL ?
				box->current_logic->keystroke_list :
				NULL;
			secound = box->file->global_keystrokes;
		} else {
			first = box->file->global_keystrokes;
			secound = box->current_logic != NULL ?
				box->current_logic->keystroke_list :
				NULL;
		}

		retval = first != NULL ?
			local_keyboard_analysis(box, first, taste, isLogic, isSimple) :
			false;
		if (!retval && secound != NULL)
			retval = local_keyboard_analysis(box, secound, taste, isLogic, isSimple);
	}

	void KeyboardAnalyse(mutabor_box_type * box, int taste, char isLogic)
	{
		generic_keyboard_analysis(box,taste,isLogic,false);
	}

	void KeyboardAnalyseSimple(mutabor_box_type * box, int taste)
	{
		generic_keyboard_analysis(box,taste,false,true);
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

#if 0
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
#endif

#ifdef __cplusplus
		}
	}
}
#endif

///\}
