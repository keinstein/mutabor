/** \file
 ********************************************************************
 * Interpretation der Logiken zur Laufzeit 
 *
 * $Id: interpreter.h,v 1.2 2006/03/27 16:54:05 keinstein Exp $
 * \author R.Krauße, Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date $Date: 2006/03/27 16:54:05 $
 * \version $Revision: 1.2 $
 * \todo Auskommentierten Kram überprüfen
 *
 * $Log: interpreter.h,v $
 * Revision 1.2  2006/03/27 16:54:05  keinstein
 * Charset conversion to UTF8
 * prevent warning about comments
 *
 * Revision 1.1  2005/11/03 13:54:28  keinstein
 * New file.
 *
 ********************************************************************/

#if ! defined (__INTERPRETER_H_INCLUDED)
#define __INTERPRETER_H_INCLUDED

#include "bad_decl.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

/*****************************
#define SYNTHESIZER_TYP_KEINER    0
#define SYNTHESIZER_TYP_FB01      1
#define SYNTHESIZER_TYP_MULTI16   2
#define SYNTHESIZER_TYP_GIS       3

struct midiereignis { struct midiereignis * next;
                      int * first;
                      int * scanpos;
                      void (*aufruf)();
                      char * name;
};

struct keyboardereignis { int taste;
                          struct keyboardereignis * next;
                          void (*aufruf)();
                          char * name;
};

struct harmonieereignis { PATTERNN * pattern;
                          int ist_harmonieform;
                          int vortaste;
                          int nachtaste;
                          struct harmonieereignis * next;
                          void (*aufruf)();
                          char * name;
};




/ Funktionsprototypen: /

void HARMONIE_analyse(int instr,PATTERNN * pattern);
void MIDI_analyse( int code );
void KEYB_analyse( int key );
void MAUS_analyse(int mx, int my);

void Add_Key(int instr, int key, int velo);
void Delete_Key(int instr, int key);

TONSYSTEM * lz_get_tonsystem(int instr);
PATTERNN * get_pattern(int instr);

********************/

/* Globale Listen: */

extern int laufzeit_abstand[MAX_BOX];
extern int laufzeit_zentrum[MAX_BOX];
extern int laufzeit_meldungen_erlaubt; /* Hier gibt es 2 Level:
                                          0=keine Meldungen,
                                          1=normale Meldungen */
extern int aktuelles_keyboard_instrument;
extern int liegende_tasten[MAX_BOX][64];
extern int liegende_tasten_max[MAX_BOX];

/* jedem Kanal seinen Synthesizer */

int (* get_cache_konstante (int wert) ) [MAX_BOX];

#ifdef __cplusplus
  }
}
#endif

#endif /* __INTERPRETER_H_INCLUDED */
