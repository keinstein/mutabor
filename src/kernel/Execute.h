/** \file 
 ********************************************************************
 * Execute tuning changes
 *
 * Copyright:   (c) 1998-2008 TU Dresden
 * \author  
 * R. Krauße, 
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ##################################################################
// Mutabor 3, Header execute file
// ##################################################################

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_EXECUTE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_EXECUTE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_EXECUTE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_EXECUTE_H_PRECOMPILED
#define MU32_EXECUTE_H_PRECOMPILED

// system headers which do seldom change
#include <stdio.h>

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

			struct mutabor_box_type;
			typedef struct mutabor_box_type mutabor_box_type;
			struct mutabor_logic_parsed;

			enum mutabor_changed_flags {
				mutabor_box_changed = 0x01,
				mutabor_logic_changed = 0x02,
				mutabor_keys_changed = 0x04,
				mutabor_action_changed = 0x08
			};


			typedef void mutabor_callback_update_type(mutabor_box_type * box,
								  unsigned int flags);
			typedef void mutabor_callback_midi_out_type (mutabor_box_type * box,
								     struct midiliste * outliste);
			typedef void mutabor_callback_error_message_type(mutabor_box_type * box,
									 bool iswarning,
									 const char * message);
			typedef void mutabor_callback_update_display(mutabor_box_type * box, int line_number);
			typedef void mutabor_callback_log_action(mutabor_box_type * box,
								  struct do_aktion * action);

			typedef void mutabor_callback_lock_logic(mutabor_logic_parsed * logic);


			struct mutabor_callback_type {
				mutabor_callback_update_type * update;
				mutabor_callback_midi_out_type * midi_out;
				mutabor_callback_error_message_type * error_message;
				mutabor_callback_update_display * update_display;
				mutabor_callback_log_action * log_action;
				mutabor_callback_lock_logic * lock_logic;
				mutabor_callback_lock_logic * unlock_logic;
			};

			extern struct mutabor_callback_type * mutabor_callbacks;

			inline void mutabor_update(mutabor_box_type * box, unsigned int flags) {
				mutabor_callbacks->update(box,flags);
			}

			inline void mutabor_midi_out(mutabor_box_type * box,
						     struct midiliste * outliste) {
				mutabor_callbacks->midi_out(box,outliste);
			}

			/* add a prototype as attributes are not allowed in the function definition */
			/* void mutabor_error_message(mutabor_box_type * box,
						   bool iswarning,
						   const char * message,
						   ...)  __attribute__ ((format(printf, 3, 4))) ;*/

			inline void mutabor_error_message(mutabor_box_type * box,
							  bool iswarning,
							  const char * message,
							  ...) {
				char * formatted;
				va_list args;
				va_start(args,message);
				if (vasprintf(&formatted,message,args) == -1) {
					formatted = (char *)_mut("Error in Error: Could not allocate buffer for error message.");
					if (!formatted) 
						formatted = 
							(char *) "Error in Error: Could not allocate buffer for error message.";
				}
				va_end(args);
				mutabor_callbacks->error_message(box,iswarning,formatted);
			}

			inline void show_line_number(mutabor_box_type * box, int line_number ) {
				mutabor_callbacks->update_display(box,line_number);
			}


			inline void mutabor_log_action(mutabor_box_type * box, struct do_aktion * action) {
				mutabor_callbacks->log_action(box,action);
			}

			inline void mutabor_lock_logic(mutabor_logic_parsed * logic) {
				mutabor_callbacks->lock_logic(logic);
			}

			inline void mutabor_unlock_logic(mutabor_logic_parsed * logic) {
				mutabor_callbacks->unlock_logic(logic);
			}




			/**
			 * Set the callbacks for the mutabor backend.
			 *
			 * \param callbacks pointer to the object that holds all calbacks that
			 * are needed for the backend to run;
			 *
			 * \return old callback object.
			 */
			mutabor_callback_type * mutabor_set_callbacks(mutabor_callback_type * callbacks);
			/**
			 * Get the currently active callback object.
			 *
			 *
			 * \return pointer to the currently active callback object
			 */
			mutabor_callback_type * mutabor_get_callbacks();


			void KeyboardIn(struct mutabor_box_type * box, const char *keys);


			void AddKey(mutabor_box_type * box, int taste, size_t id, size_t channel, void * userdata);
			void DeleteKey(mutabor_box_type * box, int taste, size_t id, size_t channel);
			void MidiAnalysis(mutabor_box_type * box, BYTE midiByte);

			void KeyboardAnalyse(mutabor_box_type * box, int taste, char isLogic);
			void KeyboardAnalyseSimple(mutabor_box_type * box, int taste);

//			void FlushUpdateUI();


/* interal definitions */


#if 0


#define FLUSH_UPDATE_UI FlushUpdateUI()

// berechnet die Tonigkeit einer Taste bzgl. tonsystem
inline int GET_INDEX(int key, tone_system * tonsystem) {
	mutASSERT(tonsystem);
	int retval = (key - tonsystem->anker) % tonsystem->breite;
	return retval < 0 ? retval + tonsystem->breite : retval;
}

// berechnet die 'Oktavlage' einer taste bzgl. tonsystem
inline int GET_ABSTAND(int taste, tone_system * tonsystem) {
	mutASSERT(tonsystem);
	int retval = (int)(taste - (tonsystem->anker % tonsystem->breite)) / tonsystem->breite;
	retval -= ((int)tonsystem->anker  / tonsystem->breite);
	return retval;
}
#endif

#if 0
#define GET_ABSTAND(taste,tonsystem)					\
	( (int)((taste)-( (tonsystem)->anker % (tonsystem)->breite ))	\
	  / (tonsystem)->breite -((int) (tonsystem)->anker		\
				  / (tonsystem)->breite ))
#endif

#ifdef __cplusplus
		} // extern "C"
	} // namespace hidden
} // namespace mutabor
#endif


#endif // precompiled
#endif



///\}
